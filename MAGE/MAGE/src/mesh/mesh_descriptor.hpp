#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	struct MeshDescriptor final {

	public:

		/**
		 Constructs a mesh descriptor.

		 @param[in]		invert_handedness
						Flag indicating whether the handness of the
						coordinate system of the mesh should be inverted.
		 @param[in]		clockwise_order
						Flag indicating whether the vertices of triangles
						should be in clockwise order.
		 */
		MeshDescriptor(bool invert_handedness = false, bool clockwise_order = true)
			: m_invert_handedness(invert_handedness), m_clockwise_order(clockwise_order) {}
		MeshDescriptor(const MeshDescriptor< VertexT > &desc) = default;
		MeshDescriptor(MeshDescriptor< VertexT > &&desc) = default;
		~MeshDescriptor() = default;

		MeshDescriptor &operator=(const MeshDescriptor< VertexT > &desc) = default;
		MeshDescriptor &operator=(MeshDescriptor< VertexT > &&desc) = default;

		bool InvertHandness() const {
			return m_invert_handedness;
		}
		bool ClockwiseOrder() const {
			return m_clockwise_order;
		}

	private:

		bool m_invert_handedness;
		bool m_clockwise_order;
	};
}