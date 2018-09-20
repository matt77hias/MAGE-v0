#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline VertexShaderPtr CreateVS(ResourceManager& resource_manager,
									ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< VertexShader >(
								std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline HullShaderPtr CreateHS(ResourceManager& resource_manager,
								  ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< HullShader >(
								std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline DomainShaderPtr CreateDS(ResourceManager& resource_manager,
									ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< DomainShader >(
								std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline GeometryShaderPtr CreateGS(ResourceManager& resource_manager,
									  ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< GeometryShader >(
								std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline PixelShaderPtr CreatePS(ResourceManager& resource_manager,
								   ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< PixelShader >(
								std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	[[nodiscard]]
	inline ComputeShaderPtr CreateCS(ResourceManager& resource_manager,
									 ConstructorArgsT&&... args) {

		return resource_manager.GetOrCreate< ComputeShader >(
								std::forward< ConstructorArgsT >(args)...);
	}
}