//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\shader_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT CompileShaderFromFile(LPCWSTR fname, LPCSTR entry_point, LPCSTR shader_target, ID3DBlob **output_blob) {

		DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in the release configuration of this program.
		shader_flags |= D3DCOMPILE_DEBUG;
		// Disable optimizations to further improve shader debugging.
		shader_flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		// Compiles Microsoft High Level Shader Language (HLSL) code into bytecode for a given target.
		// 1. A pointer to a constant null-terminated string that contains the name of the file that contains the shader code.
		// 2. An optional array of D3D_SHADER_MACRO structures that define shader macros.
		// 3. An optional pointer to an ID3DInclude interface that the compiler uses to handle include files.
		// 4. A pointer to a constant null-terminated string that contains the name of the shader entry point function where shader execution begins.
		// 5. A pointer to a constant null-terminated string that specifies the shader target or set of shader features to compile against. 
		// 6. A combination of shader compile options.
		// 7. A combination of effect compile options.
		// 8. A pointer to a variable that receives a pointer to the ID3DBlob interface that you can use to access the compiled code.
		// 9. An optional pointer to a variable that receives a pointer to the ID3DBlob interface that you can use to access compiler error messages.
		ID3DBlob *error_blob = nullptr;
		const HRESULT result_compile = D3DCompileFromFile(fname, nullptr, nullptr, entry_point, shader_target, shader_flags, 0, output_blob, &error_blob);
		if (FAILED(result_compile)) {
			if (error_blob) {
				// Sends a string to the debugger for display.
				OutputDebugStringA(reinterpret_cast<const char *>(error_blob->GetBufferPointer()));
				error_blob->Release();
			}
			return result_compile;
		}
		// Release the error blob if existing.
		if (error_blob) {
			error_blob->Release();
		}

		return S_OK;
	}
}