//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3dcompiler.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment (lib, "d3dcompiler.lib")

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	[[nodiscard]]
	HRESULT CompileShaderFromFile(const wstring& fname, 
								  const  string& entry_point, 
								  const  string& shader_target, 
								  NotNull< ID3DBlob** > output_blob) {
		
		#ifndef _DEBUG
		const DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;
		#else  // _DEBUG
		const DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS 
			                     | D3DCOMPILE_DEBUG 
			                     | D3DCOMPILE_SKIP_OPTIMIZATION;
		#endif // _DEBUG

		// Compiles Microsoft High Level Shader Language (HLSL) code into 
		// bytecode for a given target.
		// 1. A pointer to a constant null-terminated string that contains the 
		//    name of the file that contains the shader code.
		// 2. An optional array of D3D_SHADER_MACRO structures that define 
		//    shader macros.
		// 3. An optional pointer to an ID3DInclude interface that the compiler 
		//    uses to handle include files.
		// 4. A pointer to a constant null-terminated string that contains the 
		//    name of the shader entry point function where shader execution 
		//    begins.
		// 5. A pointer to a constant null-terminated string that specifies the 
		//    shader target or set of shader features to compile against. 
		// 6. A combination of shader compile options.
		// 7. A combination of effect compile options.
		// 8. A pointer to a variable that receives a pointer to the ID3DBlob 
		//    interface that you can use to access the compiled code.
		// 9. An optional pointer to a variable that receives a pointer to the 
		//    ID3DBlob interface that you can use to access compiler error 
		//    messages.
		ComPtr< ID3DBlob > error_blob;
		const HRESULT result = D3DCompileFromFile(fname.c_str(), 
												  nullptr, 
												  nullptr, 
												  entry_point.c_str(), 
												  shader_target.c_str(), 
												  shader_flags, 
												  0u, 
												  output_blob, 
												  error_blob.GetAddressOf());
		
		if (FAILED(result)) {
			if (error_blob) {
				// Sends a string to the debugger for display.
				OutputDebugStringA(reinterpret_cast< const char* >(
					               error_blob->GetBufferPointer()));
			}
			return result;
		}

		return S_OK;
	}
}