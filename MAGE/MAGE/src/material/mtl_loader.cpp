//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl_loader.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MTL_DELIMITER " \t\n\r"
#define MAGE_MTL_COMMENT_CHAR '#'
#define MAGE_MTL_TOKEN_MATERIAL_DECLARATION "newmtl"
#define MAGE_MTL_TOKEN_XYZ "xyz"
#define MAGE_MTL_TOKEN_SPECTRAL "spectral"
#define MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY "Ka"
#define MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY "Kd"
#define MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY "Ks"
#define MAGE_MTL_TOKEN_TRANSMISSION_FILTER "Tf"
#define MAGE_MTL_TOKEN_SPECULAR_EXPONENT "Ns"
#define MAGE_MTL_TOKEN_OPTICAL_DENSITY "Ni"
#define MAGE_MTL_TOKEN_DISSOLVE "d"
#define MAGE_MTL_TOKEN_DISSOLVE_HALO "-halo"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	static RGBSpectrum ParseMTLSpectrum(uint32_t line_number, char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_MTL_DELIMITER, context);
		char *float_context = nullptr;

		// No spectrum
		if (!token) {
			Error("No spectrum found in MTL specification at line %u.", line_number);
			return RGBSpectrum();
		}

		// XYZ spectrum
		if (str_equals(token, MAGE_MTL_TOKEN_XYZ)) {
			// x component
			const char *token_x = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_x) {
				Error("No x component found in xyz spectrum in MTL specification at line %u.", line_number);
				return RGBSpectrum();
			}
			const float vector3_x = strtof(token_x, &float_context);
			if (float_context == token_x) {
				Error("x component in xyz spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_x);
				return RGBSpectrum();
			}

			// y component
			const char *token_y = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_y) {
				return RGBSpectrum(XYZSpectrum(vector3_x, vector3_x, vector3_x));
			}
			const float vector3_y = strtof(token_y, &float_context);
			if (float_context == token_y) {
				Error("y component in xyz spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_y);
				return RGBSpectrum();
			}

			// z component
			const char *token_z = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_z) {
				Error("No z component found in xyz spectrum in MTL specification at line %u.", line_number);
				return RGBSpectrum();
			}
			const float vector3_z = strtof(token_z, &float_context);
			if (float_context == token_z) {
				Error("z component in xyz spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_z);
				return RGBSpectrum();
			}

			return RGBSpectrum(XYZSpectrum(vector3_x, vector3_y, vector3_z));
		}
		
		// Custom spectrum
		if (str_equals(token, MAGE_MTL_TOKEN_SPECTRAL)) {
			Warning("Unsupported custom spectrum in MTL specification at line %u.", line_number);

			// rfl
			const char *token_rfl = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_rfl) {
				Error("No file found in custom spectrum in MTL specification at line %u.", line_number);
				return RGBSpectrum();
			}
			if (!str_contains(token_rfl, ".rfl")) {
				Error("No .rfl file found in custom spectrum in MTL specification at line %u.", line_number);
				return RGBSpectrum();
			}

			// factor
			const char *token_factor = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_factor) {
				return RGBSpectrum();
			}
			const float factor = strtof(token_factor, &float_context);
			if (float_context == token_factor) {
				Error("factor in spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_factor);
				return RGBSpectrum();
			}

			return RGBSpectrum();
		}
		
		// RGB spectrum

		// r component
		const char *token_x = token;
		if (!token_x) {
			Error("No r component found in rgb spectrum in MTL specification at line %u.", line_number);
			return RGBSpectrum();
		}
		const float vector3_x = strtof(token_x, &float_context);
		if (float_context == token_x) {
			Error("r component in rgb spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_x);
			return RGBSpectrum();
		}

		// g component
		const char *token_y = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
		if (!token_y) {
			return RGBSpectrum(vector3_x, vector3_x, vector3_x);
		}
		const float vector3_y = strtof(token_y, &float_context);
		if (float_context == token_y) {
			Error("g component in rgb spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_y);
			return RGBSpectrum();
		}

		// b component
		const char *token_z = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
		if (!token_z) {
			Error("No b component found in rgb spectrum in MTL specification at line %u.", line_number);
			return RGBSpectrum();
		}
		const float vector3_z = strtof(token_z, &float_context);
		if (float_context == token_z) {
			Error("b component in rgb spectrum does not represent a floating point value in MTL specification at line %u: %s.", line_number, token_z);
			return RGBSpectrum();
		}

		return RGBSpectrum(vector3_x, vector3_y, vector3_z);
	}
	static float ParseMTLFloat(uint32_t line_number, char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_MTL_DELIMITER, context);
		if (!token) {
			Error("No floating point value found in MTL specification at line %u.", line_number);
			return 0.0f;
		}
		
		char *float_context = nullptr;
		const float result = strtof(token, &float_context);
		if (float_context == token) {
			Error("No floating point value found in MTL specification at line %u: %s.", line_number, token);
			return 0.0f;
		}

		return result;
	}

	static string ParseMTLMaterialName(uint32_t line_number, char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_MTL_DELIMITER, context);
		if (!token) {
			Error("No string value found in MTL specification at line %u.", line_number);
			return "none";
		}
		return string(token);
	}
	static RGBSpectrum ParseMTLAmbientReflectivity(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLSpectrum(line_number, context, str);
	}
	static RGBSpectrum ParseMTLDiffuseReflectivity(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLSpectrum(line_number, context, str);
	}
	static RGBSpectrum ParseMTLSpecularReflectivity(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLSpectrum(line_number, context, str);
	}
	static RGBSpectrum ParseMTLTransmissionFilter(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLSpectrum(line_number, context, str);
	}
	static float ParseMTLSpecularExponent(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLFloat(line_number, context, str);
	}
	static float ParseMTLOpticalDensity(uint32_t line_number, char **context, char *str = nullptr) {
		return ParseMTLFloat(line_number, context, str);
	}
	static float ParseMTLDissolve(uint32_t line_number, char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_MTL_DELIMITER, context);
		if (!token) {
			Error("No floating point value found in MTL specification at line %u.", line_number);
			return 0.0f;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE_HALO)) {
			Warning("Unsupported halo effect in MTL specification at line %u.", line_number);

			return ParseMTLFloat(line_number, context, str);
		}
		else {
			char *float_context = nullptr;
			const float result = strtof(token, &float_context);
			if (float_context == token) {
				Error("No floating point value found in MTL specification at line %u.", line_number);
				return 0.0f;
			}

			return result;
		}
	}

	static void ParseMTLLine(const string &fname, char *line, uint32_t line_number, 
		vector < Material > &material_buffer) {

		UNUSED(fname);

		char *context = nullptr;
		const char *token = strtok_s(line, MAGE_MTL_DELIMITER, &context);

		if (!token || token[0] == MAGE_MTL_COMMENT_CHAR) {
			return;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_DECLARATION)) {
			material_buffer.push_back(Material());
				material_buffer.back().m_name = ParseMTLMaterialName(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY)) {
			material_buffer.back().m_ambient_reflectivity = ParseMTLAmbientReflectivity(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY)) {
			material_buffer.back().m_diffuse_reflectivity = ParseMTLDiffuseReflectivity(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY)) {
			material_buffer.back().m_specular_reflectivity = ParseMTLSpecularReflectivity(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_TRANSMISSION_FILTER)) {
			material_buffer.back().m_transmission_filter = ParseMTLTransmissionFilter(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_EXPONENT)) {
			material_buffer.back().m_specular_exponent = ParseMTLSpecularExponent(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_OPTICAL_DENSITY)) {
			material_buffer.back().m_index_of_refraction = ParseMTLOpticalDensity(line_number, &context);
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE)) {
			material_buffer.back().m_dissolve = ParseMTLDissolve(line_number, &context);
		}
		else {
			Warning("Unsupported keyword in MTL specification at line %u: %s.", line_number, token);
		}

		char *next_token = strtok_s(nullptr, MAGE_MTL_DELIMITER, &context);
		while (next_token) {
			Warning("Unused token in MTL specification at line %u: %s.", line_number, next_token);
			next_token = strtok_s(nullptr, MAGE_MTL_DELIMITER, &context);
		}
	}

	HRESULT LoadMTLMaterialFromFile(const string &fname, vector< Material > &material_buffer) {
		// Open the .mtl file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = fopen_s(&file, fname.c_str(), "r");
		if (result_fopen_s) {
			Error("Could not import .mtl file: %s.", fname.c_str());
			return E_FAIL;
		}

		// Parse the .obj file while populating the material buffer.
		char current_line[MAX_PATH];
		uint32_t line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {

			ParseMTLLine(fname, current_line, line_number, material_buffer);

			++line_number;
		}

		// Close the script file.
		fclose(file);

		return S_OK;
	}
}