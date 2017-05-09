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

	const CombinedShader CreateDiffuseBumpShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBumpVertexShader(
			device, device_context, CreateCompiledTransformVertexShader());
		SharedPtr< PixelShader >  ps = factory->CreateBumpPixelShader(
			device, device_context, CreateCompiledDiffusePixelShader());
		return CombinedShader(vs, ps);
	}

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
			device, device_context, CreateCompiledLambertianPixelShader());
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
			device, device_context, CreateCompiledPhongPixelShader());
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
			device, device_context, CreateCompiledBlinnPhongPixelShader());
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
			device, device_context, CreateCompiledModifiedBlinnPhongPixelShader());
		return CombinedShader(vs, ps);
	}
}