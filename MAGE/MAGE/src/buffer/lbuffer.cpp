//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\lbuffer.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LBuffer::LBuffer()
		: m_device_context(GetImmediateDeviceContext()),
		m_light_buffer(),
		m_directional_lights_buffer(3),
		m_omni_lights_buffer(32),
		m_spot_lights_buffer(32) {}

	void LBuffer::Update(const PassBuffer *scene, const CameraNode *node) {

		Assert(scene);
		Assert(node);

		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessLights(scene->m_directional_lights,               world_to_view);
		ProcessLights(scene->m_omni_lights, world_to_projection, world_to_view);
		ProcessLights(scene->m_spot_lights, world_to_projection, world_to_view);
		ProcessLightsData(scene);
	}

	void LBuffer::BindToGraphicsPipeline() const noexcept {
		ID3D11ShaderResourceView * const srvs[3] = {
			m_directional_lights_buffer.Get(),
			m_omni_lights_buffer.Get(),
			m_spot_lights_buffer.Get()
		};

		PS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_LIGHTING,
			m_light_buffer.Get());
		PS::BindSRVs(m_device_context,
			SLOT_SRV_LIGHTS_START,
			_countof(srvs), srvs);
	}

	void LBuffer::BindToComputePipeline() const noexcept {
		ID3D11ShaderResourceView * const srvs[3] = {
			m_directional_lights_buffer.Get(),
			m_omni_lights_buffer.Get(),
			m_spot_lights_buffer.Get()
		};

		CS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_LIGHTING,
			m_light_buffer.Get());
		CS::BindSRVs(m_device_context,
			SLOT_SRV_LIGHTS_START,
			_countof(srvs), srvs);
	}

	void LBuffer::ProcessLightsData(const PassBuffer *scene) noexcept {

		LightBuffer buffer;
		buffer.m_Ia                             = scene->m_ambient_light;
		buffer.m_nb_directional_lights          = static_cast< uint32_t >(m_directional_lights_buffer.size());
		buffer.m_nb_omni_lights                 = static_cast< uint32_t >(m_omni_lights_buffer.size());
		buffer.m_nb_spot_lights                 = static_cast< uint32_t >(m_spot_lights_buffer.size());
		buffer.m_fog_color                      = scene->m_fog->GetIntensity();
		buffer.m_fog_distance_falloff_start     = scene->m_fog->GetStartDistanceFalloff();
		buffer.m_fog_distance_falloff_inv_range = 1.0f / scene->m_fog->GetRangeDistanceFalloff();

		// Update the light buffer.
		m_light_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBuffer::ProcessLights(
		const vector< const DirectionalLightNode * > &lights,
		FXMMATRIX world_to_view) noexcept {

		vector< DirectionalLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode    * const transform = node->GetTransform();
			const DirectionalLight * const light = node->GetLight();

			// Transform to view space.
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a directional light buffer.
			DirectionalLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_neg_d, -d);
			light_buffer.m_I = light->GetIntensity();

			// Add directional light buffer to directional light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the directional lights buffer.
		m_directional_lights_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBuffer::ProcessLights(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection,
		FXMMATRIX world_to_view) noexcept {

		vector< OmniLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light = node->GetLight();
			const XMMATRIX object_to_world = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);

			// Create an omni light buffer.
			OmniLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			light_buffer.m_I = light->GetIntensity();
			light_buffer.m_distance_falloff_end = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();

			// Add omni light buffer to omni light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the omni lights buffer.
		m_omni_lights_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBuffer::ProcessLights(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection,
		FXMMATRIX world_to_view) noexcept {

		vector< SpotLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode  * const transform = node->GetTransform();
			const SpotLight      * const light = node->GetLight();
			const XMMATRIX object_to_world = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetAABB())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a spotlight buffer.
			SpotLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			XMStoreFloat3(&light_buffer.m_neg_d, -d);
			light_buffer.m_I = light->GetIntensity();
			light_buffer.m_exponent_property = light->GetExponentProperty();
			light_buffer.m_distance_falloff_end = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();
			light_buffer.m_cos_umbra = light->GetEndAngularCutoff();
			light_buffer.m_cos_inv_range = 1.0f / light->GetRangeAngularCutoff();

			// Add spotlight buffer to spotlight buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the spotlights buffer.
		m_spot_lights_buffer.UpdateData(m_device_context, buffer);
	}
}