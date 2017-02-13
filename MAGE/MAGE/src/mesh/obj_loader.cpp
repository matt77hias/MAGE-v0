//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.hpp"
#include "material\mtl_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	string ParseOBJString(uint32_t line_number, char **context, char *str) {
		const char *token = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		if (!token) {
			Error("No string value found in OBJ specification at line %u.", line_number);
			return "";
		}
		return string(token);
	}
	static float ParseOBJFloat(uint32_t line_number, char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		if (!token) {
			Error("No floating point value found in OBJ specification at line %u.", line_number);
			return 0.0f;
		}

		char *float_context = nullptr;
		const float result = strtof(token, &float_context);
		if (float_context == token) {
			Error("No floating point value found in OBJ specification at line %u: %s.", line_number, token);
			return 0.0f;
		}

		return result;
	}
	static XMFLOAT2 ParseOBJFloat2(uint32_t line_number, char **context, char *str = nullptr) {
		const float vector3_x = ParseOBJFloat(line_number, context, str);
		const float vector3_y = ParseOBJFloat(line_number, context);
		return XMFLOAT2(vector3_x, vector3_y);
	}
	static XMFLOAT3 ParseOBJFloat3(uint32_t line_number, char **context, char *str = nullptr) {
		const float vector3_x = ParseOBJFloat(line_number, context, str);
		const float vector3_y = ParseOBJFloat(line_number, context);
		const float vector3_z = ParseOBJFloat(line_number, context);
		return XMFLOAT3(vector3_x, vector3_y, vector3_z);
	}

	static Point3 ParseOBJVertexCoordinates(uint32_t line_number, char **context, char *str = nullptr) {
		return (Point3)ParseOBJFloat3(line_number, context, str);
	}
	static Normal3 ParseOBJVertexNormalCoordinates(uint32_t line_number, char **context, char *str = nullptr) {
		return (Normal3)ParseOBJFloat3(line_number, context, str);
	}
	static UV ParseOBJVertexTextureCoordinates(uint32_t line_number, char **context, char *str = nullptr) {
		return (UV)ParseOBJFloat2(line_number, context, str);
	}
	XMUINT3 ParseOBJVertexIndices(uint32_t line_number, char **context, char *str) {
		const char *token = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		if (!token) {
			Error("No vertex index value found in OBJ specification at line %u.", line_number);
			return XMUINT3();
		}

		char *int_context = nullptr;
		const uint32_t vertex_index = (uint32_t)strtol(token, &int_context, 10);
		if (int_context == token) {
			Error("No integer index value found in OBJ specification at line %u: %s.", line_number, token);
			return XMUINT3();
		}
		
		uint32_t texture_index = 0;
		uint32_t normal_index = 0;

		if (str_contains(token, "//")) {
			//... v1//vn1 ...
			const char *normal_part = strchr(token, '/') + 2;
			normal_index = (uint32_t)strtol(normal_part, &int_context, 10);
			if (int_context == normal_part) {
				Error("No normal index value found in OBJ specification at line %u: %s.", line_number, normal_part);
				return XMUINT3();
			}
		}
		else if (str_contains(token, "/")) {
			//... v1/vt1 ...
			const char *texture_part = strchr(token, '/') + 1;
			texture_index = (uint32_t)strtol(texture_part, &int_context, 10);
			if (int_context == texture_part) {
				Error("No texture index value found in OBJ specification at line %u: %s.", line_number, texture_part);
				return XMUINT3();
			}
			if (str_contains(texture_part, "/")) {
				//... v1/vt1/vn1 ...
				const char *normal_part = strchr(texture_part, '/') + 1;
				normal_index = (uint32_t)strtol(normal_part, &int_context, 10);
				if (int_context == normal_part) {
					Error("No normal index value found in OBJ specification at line %u: %s.", line_number, normal_part);
					return XMUINT3();
				}
			}
		}

		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	void ParseOBJVertex(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc) {
		Point3 vertex = ParseOBJVertexCoordinates(line_number, context);
		if (mesh_desc.InvertHandness()) {
			vertex.z = -vertex.z;
		}

		buffer.vertex_coordinates.push_back(vertex);
	}
	void ParseOBJVertexTexture(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc) {
		UV texture = ParseOBJVertexTextureCoordinates(line_number, context);
		if (mesh_desc.InvertHandness()) {
			texture.y = 1.0f - texture.y;
		}
		
		buffer.vertex_texture_coordinates.push_back(texture);
	}
	void ParseOBJVertexNormal(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc) {
		Normal3 normal = ParseOBJVertexNormalCoordinates(line_number, context);
		if (mesh_desc.InvertHandness()) {
			normal.z = -normal.z;
		}
		const XMVECTOR v = XMLoadFloat3(&normal);
		const XMVECTOR normal_v = XMVector3Normalize(v);
		XMLoadFloat3(&normal);

		buffer.vertex_normal_coordinates.push_back(normal);
	}
}