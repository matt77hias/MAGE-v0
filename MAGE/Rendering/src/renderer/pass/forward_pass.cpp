//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\forward_pass.hpp"
#include "resource\shader\shader_factory.hpp"
#include "resource\texture\texture_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	ForwardPass::ForwardPass(ID3D11Device& device,
							 ID3D11DeviceContext& device_context,
							 StateManager& state_manager,
							 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_resource_manager(resource_manager),
		m_vs(CreateTransformVS(resource_manager)),
		m_uv(CreateReferenceTexture(resource_manager)),
		m_color_buffer(device) {}

	ForwardPass::ForwardPass(ForwardPass&& pass) noexcept = default;

	ForwardPass::~ForwardPass() = default;

	ForwardPass& ForwardPass::operator=(ForwardPass&& pass) noexcept = default;

	void ForwardPass::BindFixedOpaqueState() const noexcept {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::CounterClockwiseCulling);
		// OM: Bind the depth-stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::LessEqualDepthReadWrite);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::GreaterEqualDepthReadWrite);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Opaque);
	}

	void ForwardPass::BindFixedTransparentState() const noexcept {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::CounterClockwiseCulling);
		// OM: Bind the depth-stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::LessDepthReadWrite);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::GreaterDepthReadWrite);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Transparency);
	}

	void ForwardPass::BindFixedWireframeState() const noexcept {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::Wireframe);
		// OM: Bind the depth-stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::LessEqualDepthReadWrite);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::GreaterEqualDepthReadWrite);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Opaque);
	}

	void ForwardPass::BindColor(const RGBA& color) {
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		m_color_buffer.Bind< Pipeline::PS >(m_device_context, SLOT_CBUFFER_COLOR);
	}

	void XM_CALLCONV ForwardPass::Render(const World& world, 
										 FXMMATRIX world_to_projection, 
										 BRDF brdf, bool vct) const {
		// Bind the fixed opaque state.
		BindFixedOpaqueState();

		constexpr bool transparency = false;
		
		//---------------------------------------------------------------------
		// All emissive models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateForwardEmissivePS(m_resource_manager, 
															  transparency);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			
			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.IsEmissive()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with no TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = false;
			const PixelShaderPtr ps = CreateForwardPS(m_resource_manager, 
													  brdf, transparency, vct, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr != material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = true;
			const PixelShaderPtr ps = CreateForwardPS(m_resource_manager, 
													  brdf, transparency, vct, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr == material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderSolid(const World& world, 
											  FXMMATRIX world_to_projection) const {
		// Bind the fixed opaque state.
		BindFixedOpaqueState();

		//---------------------------------------------------------------------
		// All models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateForwardSolidPS(m_resource_manager);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			if (State::Active != model.GetState()) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderGBuffer(const World& world, 
												FXMMATRIX world_to_projection) const {
		// Bind the fixed opaque state.
		BindFixedOpaqueState();
		
		//---------------------------------------------------------------------
		// All models with no TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = false;
			const PixelShaderPtr ps = CreateGBufferPS(m_resource_manager, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr != material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = true;
			const PixelShaderPtr ps = CreateGBufferPS(m_resource_manager, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr == material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderEmissive(const World& world, 
												 FXMMATRIX world_to_projection) const {
		constexpr bool transparency = false;

		// Bind the fixed opaque state.
		BindFixedOpaqueState();

		//---------------------------------------------------------------------
		// All emissive models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateForwardEmissivePS(m_resource_manager, 
															  transparency);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.IsEmissive()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderTransparent(const World& world, 
													FXMMATRIX world_to_projection, 
													BRDF brdf, 
													bool vct) const {
		// Bind the fixed transparent state.
		BindFixedTransparentState();

		constexpr bool transparency = true;
		
		//---------------------------------------------------------------------
		// All transparent emissive models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateForwardEmissivePS(m_resource_manager, 
															  transparency);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			
			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.IsEmissive()
				|| !material.IsTransparant()
				|| material.GetBaseColor()[3] < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All transparent models with no TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = false;
			const PixelShaderPtr ps = CreateForwardPS(m_resource_manager, 
													  brdf, transparency, vct, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr != material.GetNormalSRV()
				|| !material.IsTransparant()
				|| material.GetBaseColor()[3] < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All transparent models with TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = true;
			const PixelShaderPtr ps = CreateForwardPS(m_resource_manager, 
													  brdf, transparency, vct, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr == material.GetNormalSRV()
				|| !material.IsTransparant()
				|| material.GetBaseColor()[3] < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderFalseColor(const World& world, 
												   FXMMATRIX world_to_projection, 
												   FalseColor false_color) const {
		// Bind the fixed opaque state.
		BindFixedOpaqueState();

		if (FalseColor::UV == false_color) {
			m_uv->Bind< Pipeline::PS >(m_device_context, SLOT_SRV_TEXTURE);
		}

		//---------------------------------------------------------------------
		// All models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateFalseColorPS(m_resource_manager, 
														 false_color);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			if (State::Active != model.GetState()) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::RenderWireframe(const World& world, 
												  FXMMATRIX world_to_projection) {
		// Bind the fixed opaque state.
		BindFixedWireframeState();

		constexpr RGBA color = { 0.0f, 0.0f, 1.0f, 1.0f };
		// PS: Bind the color data.
		BindColor(color);

		//---------------------------------------------------------------------
		// All models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateFalseColorPS(m_resource_manager, 
														 FalseColor::ConstantColor);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			if (State::Active != model.GetState()) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV ForwardPass::Render(const Model& model, 
										 FXMMATRIX world_to_projection) const noexcept {

		const auto& transform            = model.GetOwner()->GetTransform();
		const auto  object_to_world      = transform.GetObjectToWorldMatrix();
		const auto  object_to_projection = object_to_world * world_to_projection;

		// Apply view frustum culling.
		if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) { 
			return;
		}

		const auto& material             = model.GetMaterial();

		// Bind the constant buffer of the model.
		model.BindBuffer< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		model.BindBuffer< Pipeline::PS >(m_device_context, SLOT_CBUFFER_MODEL);
		// Bind the SRVs of the model.
		static_assert(SLOT_SRV_MATERIAL == SLOT_SRV_BASE_COLOR + 1);
		static_assert(SLOT_SRV_NORMAL   == SLOT_SRV_BASE_COLOR + 2);
		ID3D11ShaderResourceView* const srvs[] = {
			material.GetBaseColorSRV(),
			material.GetMaterialSRV(),
			material.GetNormalSRV()
		};
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_BASE_COLOR, 
							   static_cast< U32 >(std::size(srvs)), srvs);
		// Bind the mesh of the model.
		model.BindMesh(m_device_context);
		// Draw the model.
		model.Draw(m_device_context);
	}
}