#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct3d11.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 Compiles Microsoft High Level Shader Language (HLSL) code into bytecode 
	 for a given shader target.

	 @param[in]		fname
					A pointer to a constant null-terminated string that 
					contains the name of the file that contains the shader 
					code.
	 @param[in]		entry_point
					A pointer to a constant null-terminated string that 
					contains the name of the shader entry point function where 
					shader execution begins.
	 @param[in]		shader_target
					A pointer to a constant null-terminated string that 
					specifies the shader target or set of shader features to 
					compile against.
	 @param[out]	output_blob
					A pointer to a variable that receives a pointer to the 
					@c ID3DBlob interface that you can use to access the 
					compiled code.
	 */
	[[nodiscard]]
	HRESULT CompileShaderFromFile(const wstring& fname, 
								  const  string& entry_point, 
								  const  string& shader_target, 
								  NotNull< ID3DBlob** > output_blob);
}