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
#define MAGE_MTL_TOKEN_XYZ "xyz"
#define MAGE_MTL_TOKEN_SPECTRAL "spectral"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------

	static XMFLOAT3 XYZ_to_RGB(const XMFLOAT3 &xyz) {
		return xyz;
	}

	static XMFLOAT3 ParseMTLSpectrum(char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_MTL_DELIMITER, context);
		char *float_context = nullptr;

		if (!token) {
			printf("No spectrum found.");
			return XMFLOAT3();
		}

		if (str_equals(token, MAGE_MTL_TOKEN_XYZ)) {
			const char *token_x = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_x) {
				Error("No x-component found in xyz spectrum.");
				return XYZ_to_RGB(XMFLOAT3());
			}
			const float vector3_x = strtof(token_x, &float_context);
			if (float_context == token_x) {
				Error("x-component in xyz spectrum does not represent a floating point value.");
				return XYZ_to_RGB(XMFLOAT3());
			}

			const char *token_y = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_y) {
				return XYZ_to_RGB(XMFLOAT3(vector3_x, vector3_x, vector3_x));
			}
			const float vector3_y = strtof(token_y, &float_context);
			if (float_context == token_y) {
				Error("y-component in xyz spectrum does not represent a floating point value.");
				return XYZ_to_RGB(XMFLOAT3());
			}

			const char *token_z = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_z) {
				Error("No z-component found in xyz spectrum.");
				return XYZ_to_RGB(XMFLOAT3());
			}
			const float vector3_z = strtof(token_z, &float_context);
			if (float_context == token_z) {
				Error("z-component in xyz spectrum does not represent a floating point value.");
				return XYZ_to_RGB(XMFLOAT3());
			}

			return XYZ_to_RGB(XMFLOAT3(vector3_x, vector3_y, vector3_z));
		}
		
		if (str_equals(token, MAGE_MTL_TOKEN_SPECTRAL)) {
			Warning("Only rgb and xyz spectra are supported.");

			const char *token_rfl = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_rfl) {
				Error("No .rfl file found in spectrum.");
				return XMFLOAT3();
			}
			if (!str_contains(token_rfl, ".rfl")) {
				Error("No .rfl file found in spectrum.");
				return XMFLOAT3();
			}

			const char *token_factor = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
			if (!token_factor) {
				return XMFLOAT3();
			}
			const float factor = strtof(token_factor, &float_context);
			if (float_context == token_factor) {
				Error("factor in spectrum does not represent a floating point value.");
				return XMFLOAT3();
			}

			return XMFLOAT3();
		}
		
		const char *token_x = token;
		if (!token_x) {
			Error("No r-component found in rgb spectrum.");
			return XMFLOAT3();
		}
		const float vector3_x = strtof(token_x, &float_context);
		if (float_context == token_x) {
			Error("r-component in rgb spectrum does not represent a floating point value.");
			return XMFLOAT3();
		}

		const char *token_y = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
		if (!token_y) {
			return XMFLOAT3(vector3_x, vector3_x, vector3_x);
		}
		const float vector3_y = strtof(token_y, &float_context);
		if (float_context == token_y) {
			Error("g-component in rgb spectrum does not represent a floating point value.");
			return XMFLOAT3();
		}

		const char *token_z = strtok_s(nullptr, MAGE_MTL_DELIMITER, context);
		if (!token_z) {
			Error("No b-component found in rgb spectrum.");
			return XMFLOAT3();
		}
		const float vector3_z = strtof(token_z, &float_context);
		if (float_context == token_z) {
			Error("b-component in rgb spectrum does not represent a floating point value.");
			return XMFLOAT3();
		}

		return XMFLOAT3(vector3_x, vector3_y, vector3_z);
	}

	static XMFLOAT3 ParseMTLKa(char **context, char *str = nullptr) {
		return ParseMTLSpectrum(context, str);
	}
	static XMFLOAT3 ParseMTLKd(char **context, char *str = nullptr) {
		return ParseMTLSpectrum(context, str);
	}
	static XMFLOAT3 ParseMTLKs(char **context, char *str = nullptr) {
		return ParseMTLSpectrum(context, str);
	}
	static XMFLOAT3 ParseMTLTf(char **context, char *str = nullptr) {
		return ParseMTLSpectrum(context, str);
	}
	static XMFLOAT3 ParseMTLNs(char **context, char *str = nullptr) {
		return ParseMTLSpectrum(context, str);
	}
}