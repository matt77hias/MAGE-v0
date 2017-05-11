//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "mesh\vertex.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader CreateEmissiveShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledEmissivePixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateLambertianShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledLambertianPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledPhongPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledModifiedPhongPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledBlinnPhongPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledModifiedBlinnPhongPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledWardPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledWardDuerPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, CreateCompiledCookTorrancePixelShader());
		return CombinedShader(vs, ps);
	}
}