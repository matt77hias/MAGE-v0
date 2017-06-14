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

	const CombinedShader CreateLambertianTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledLambertianTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledPhongTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledModifiedPhongTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledBlinnPhongTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledModifiedBlinnPhongTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledWardTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledWardDuerTSNMPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceTSNMShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateTSNMVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateTSNMPixelShader(
			device, device_context, CreateCompiledCookTorranceTSNMPixelShader());
		return CombinedShader(vs, ps);
	}
}