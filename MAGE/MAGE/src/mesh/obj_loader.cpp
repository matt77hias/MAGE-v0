//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------

	static XMFLOAT2 ParseOBJFloat2(char **context, char *str = nullptr) {
		const char *token_x   = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		const float vector3_x = strtof(token_x, nullptr);
		const char *token_y   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_y = strtof(token_y, nullptr);
		return XMFLOAT2(vector3_x, vector3_y);
	}

	static XMFLOAT3 ParseOBJFloat3(char **context, char *str = nullptr) {
		const char *token_x   = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		const float vector3_x = strtof(token_x, nullptr);
		const char *token_y   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_y = strtof(token_y, nullptr);
		const char *token_z   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_z = strtof(token_z, nullptr);
		return XMFLOAT3(vector3_x, vector3_y, vector3_z);
	}

	static Point3 ParseOBJVertexCoordinates(char **context, char *str = nullptr, bool invert_handedness = false) {
		XMFLOAT3 result = ParseOBJFloat3(context, str);
		if (invert_handedness) {
			result.z = -result.z;
		}
		return (Point3)result;
	}

	static Normal3 ParseOBJVertexNormalCoordinates(char **context, char *str = nullptr, bool invert_handedness = false) {
		XMFLOAT3 result = ParseOBJFloat3(context, str);
		if (invert_handedness) {
			result.z = -result.z;
		}
		const XMVECTOR result_v = XMLoadFloat3(&result);
		const XMVECTOR normal_v = XMVector3Normalize(result_v);
		Normal3 normal;
		XMLoadFloat3(&normal);
		return normal;
	}

	static UV ParseOBJVertexTextureCoordinates(char **context, char *str = nullptr, bool invert_handedness = false) {
		XMFLOAT2 result = ParseOBJFloat2(context, str);
		if (invert_handedness) {
			result.y = 1.0f - result.y;
		}
		return (UV)result;
	}

	XMUINT3 ParseOBJVertexIndices(char **context, char *str) {
		const char *token = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		const uint32_t vertex_index = atoi(token);
		uint32_t texture_index = 0;
		uint32_t normal_index = 0;

		if (str_contains(token, "//")) {
			//... v1//vn1 ...
			const char *normal_part = strchr(token, '/') + 2;
			normal_index = atoi(normal_part);
		}
		else if (str_contains(token, "/")) {
			//... v1/vt1 ...
			const char *texture_part = strchr(token, '/') + 1;
			texture_index = atoi(strchr(token, '/') + 1);
			if (str_contains(texture_part, "/")) {
				//... v1/vt1/vn1 ...
				const char *normal_part = strchr(texture_part, '/') + 1;
				normal_index = atoi(normal_part);
			}
		}
		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	void ParseOBJVertex(char **context, OBJBuffer &buffer, bool invert_handedness) {
		const Point3 vertex = ParseOBJVertexCoordinates(context, nullptr, invert_handedness);
		buffer.vertex_coordinates.push_back(vertex);
	}

	void ParseOBJVertexTexture(char **context, OBJBuffer &buffer, bool invert_handedness) {
		const UV texture = ParseOBJVertexTextureCoordinates(context, nullptr, invert_handedness);
		buffer.vertex_texture_coordinates.push_back(texture);
	}
	
	void ParseOBJVertexNormal(char **context, OBJBuffer &buffer, bool invert_handedness) {
		const Normal3 normal = ParseOBJVertexNormalCoordinates(context, nullptr, invert_handedness);
		buffer.vertex_normal_coordinates.push_back(normal);
	}
}