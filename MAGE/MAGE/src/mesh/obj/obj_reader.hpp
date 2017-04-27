#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "model\model_output.hpp"
#include "mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of OBJ file readers for reading meshes.

	 @tparam		VertexT
					The vertex type.
	 */
	template < typename VertexT >
	class OBJReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an OBJ reader.

		 @param[in]		model_output
						A reference to a model output for storing the read data from file.
		 @param[in]		mesh_desc
						A reference to a mesh descriptor.
		 */
		explicit OBJReader(ModelOutput< VertexT > &model_output, const MeshDescriptor< VertexT > &mesh_desc)
			: LineReader(), 
			m_vertex_coordinates(), m_vertex_texture_coordinates(),
			m_vertex_normal_coordinates(), m_mapping(),
			m_model_output(model_output), m_mesh_desc(mesh_desc) {}
		
		/**
		 Constructs an OBJ reader from the given OBJ reader.

		 @param[in]		reader
						A reference to the OBJ reader to copy.
		 */
		OBJReader(const OBJReader &reader) = delete;

		/**
		 Constructs an OBJ reader by moving the given OBJ reader.

		 @param[in]		reader
						A reference to the OBJ reader to move.
		 */
		OBJReader(OBJReader &&reader) = delete;

		/**
		 Destructs this OBJ reader.
		 */
		virtual ~OBJReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given OBJ reader to this OBJ reader.

		 @param[in]		reader
						A reference to a OBJ reader to copy.
		 @return		A reference to the copy of the given OBJ reader
						(i.e. this OBJ reader).
		 */
		OBJReader &operator=(const OBJReader &reader) = delete;

		/**
		 Moves the given OBJ reader to this OBJ reader.

		 @param[in]		reader
						A reference to a OBJ reader to move.
		 @return		A reference to the moved OBJ reader
						(i.e. this OBJ reader).
		 */
		OBJReader &operator=(OBJReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Pre-process before reading the current file of this OBJ reader.

		 @throws		FormattedException
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess() override;

		/**
		 Reads the given line.

		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						Failed to read the given line.
		 */
		virtual void ReadLine(char *line) override;

		/**
		 Post-process after reading the current file of this OBJ reader.

		 @throws		FormattedException
						Failed to finish post-processing successfully.
		 */
		virtual void Postprocess() override;

		/**
		 Reads a Material Library Include definition.

		 @throws		FormattedException
						Failed to read a Material Library Include definition.
		 */
		void ReadOBJMaterialLibrary();

		/**
		 Reads a Material Usage definition.

		 @throws		FormattedException
						Failed to read a Material Usage definition.
		 */
		void ReadOBJMaterialUse();

		/**
		 Reads a Group definition.

		 @throws		FormattedException
						Failed to read a Group definition.
		 */
		void ReadOBJGroup();

		/**
		 Reads an Object definition.

		 @throws		FormattedException
						Failed to read a Object definition.
		 */
		void ReadOBJObject();

		/**
		 Reads a Smoothing Group definition.

		 @throws		FormattedException
						Failed to read a Smoothing Group definition.
		 */
		void ReadOBJSmoothingGroup();

		/**
		 Reads a Vertex Position Coordinates definition.

		 @throws		FormattedException
						Failed to read a Vertex Position Coordinates definition.
		 */
		void ReadOBJVertex();

		/**
		 Reads a Vertex Texture Coordinates definition.

		 @note			Only UV texture coordinates are supported,
						The W component of UVW texture coordinates
						is, if present, silently ignored.
		 @throws		FormattedException
						Failed to read a Vertex Texture Coordinates definition.
		 */
		void ReadOBJVertexTexture();

		/**
		 Reads a Vertex Normal Coordinates definition.

		 @throws		FormattedException
						Failed to read a Vertex Normal Coordinates definition.
		 */
		void ReadOBJVertexNormal();

		/**
		 Reads a Face definition.

		 @throws		FormattedException
						Failed to read a Face definition.
		 */
		void ReadOBJFace();

		/**
		 Reads the vertex position coordinates.

		 @return		The @c Point3 represented by the next token
						of this OBJ reader (modified according to
						the mesh descriptor of this OBj reader).
		 @throws		FormattedException
						Failed to read a @c Point3.
		 */
		const Point3 ReadOBJVertexCoordinates();

		/**
		 Reads the vertex normal coordinates.

		 @return		The @c Normal3 represented by the next token
						of this OBJ reader (modified according to
						the mesh descriptor of this OBj reader).
		 @throws		FormattedException
						Failed to read a @c Normal3.
		 */
		const Normal3 ReadOBJVertexNormalCoordinates();

		/**
		 Reads the vertex texture coordinates.

		 @return		The @c UV represented by the next token 
						of this OBJ reader (modified according to
						the mesh descriptor of this OBj reader).
		 @throws		FormattedException
						Failed to read a @c UV.
		 */
		const UV ReadOBJVertexTextureCoordinates();

		/**
		 Reads the face indices.

		 @return		The face indices represented by the next token 
						of this OBJ reader.	A zero indicates the absence
						of a component.
		 @throws		FormattedException
						Failed to read a Bool variable.
		 */
		const XMUINT3 ReadOBJVertexIndices();
		
		/**
		 Constructs or retrieves (if already existing) the vertex matching 
		 the given vertex indices.

		 @param[in]		vertex_indices
						A reference to the vertex indices.
		 @return		The vertex matching the given vertex indices @a vertex_indices.
		 */
		const VertexT ConstructVertex(const XMUINT3 &vertex_indices);

		/**
		 A struct of @c XMUINT3 comparators for OBJ vertex indices.
		 */
		struct OBJComparatorXMUINT3 {

		public:

			/**
			 Compares the two given @c XMUINT3 vectors against each other.

			 @param[in]		a
							A reference to the first vector.
			 @param[in]		b
							A reference to the second vector.
			 @return		@c true if the @a a is smaller than @a b.
							@c false otherwise.
			 */
			bool operator()(const XMUINT3& a, const XMUINT3& b) const {
				return (a.x == b.x) ? ((a.y == b.y) ? (a.z < b.z) : (a.y < b.y)) : (a.x < b.x);
			}
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector containing the read vertex position coordinates of this OBJ reader.
		 */
		vector< Point3 >  m_vertex_coordinates;

		/**
		 A vector containing the read vertex texture coordinates of this OBJ reader.
		 */
		vector< UV > m_vertex_texture_coordinates;

		/**
		 A vector containing the read normal texture coordinates of this OBJ reader.
		 */
		vector< Normal3 > m_vertex_normal_coordinates;

		/**
		 A mapping between vertex position/texture/normal coordinates' indices
		 and the index of a vertex in the vertex buffer (@c m_model_output)
		 of this OBJ reader.
		 */
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > m_mapping;
		
		/**
		 A reference to a model output containing the read data of this OBJ reader.
		 */
		ModelOutput< VertexT > &m_model_output;

		/**
		 A reference to a mesh descriptor for this OBJ reader.
		 */
		const MeshDescriptor< VertexT > &m_mesh_desc;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_reader.tpp"

#pragma endregion