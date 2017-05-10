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

	const CombinedShader CreateLambertianBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledLambertianBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledPhongBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledModifiedPhongBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledBlinnPhongBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledModifiedBlinnPhongBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledWardBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledWardDuerBumpPixelShader());
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledCookTorranceBumpPixelShader());
		return CombinedShader(vs, ps);
	}
}