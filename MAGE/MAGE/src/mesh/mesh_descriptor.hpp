#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of mesh descriptors.

	 @tparam		VertexT
					the vertex type.
	 */
	template < typename VertexT >
	struct MeshDescriptor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mesh descriptor.

		 @param[in]		invert_handedness
						A flag indicating whether the mesh coordinate system handness 
						should be inverted.
		 @param[in]		clockwise_order
						A flag indicating whether the face vertices should be 
						defined in clockwise order or not (i.e. counterclockwise order).
		 */
		explicit MeshDescriptor(
			bool invert_handedness = false, 
			bool clockwise_order   = true)
			: m_invert_handedness(invert_handedness), 
			m_clockwise_order(clockwise_order) {}
		
		/**
		 Constructs a mesh descriptor from the given mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to copy.
		 */
		MeshDescriptor(const MeshDescriptor< VertexT > &desc) = default;
		
		/**
		 Constructs a mesh descriptor by moving the given mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to move.
		 */
		MeshDescriptor(MeshDescriptor< VertexT > &&desc) = default;
		
		/**
		 Destructs this mesh descriptor.
		 */
		~MeshDescriptor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given mesh descriptor to this mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to copy.
		 @return		A reference to the copy of the given mesh descriptor
						(i.e. this mesh descriptor).
		 */
		MeshDescriptor &operator=(const MeshDescriptor< VertexT > &desc) = default;

		/**
		 Moves the given mesh descriptor to this mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to move.
		 @return		A reference to the moved mesh descriptor
						(i.e. this mesh descriptor).
		 */
		MeshDescriptor &operator=(MeshDescriptor< VertexT > &&desc) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether the mesh coordinate system handness should be inverted
		 or not according to this mesh descriptor.
 
		 @return		@c true if the mesh coordinate system handness should be inverted.
						@c false otherwise.
		 */
		bool InvertHandness() const noexcept {
			return m_invert_handedness;
		}

		/**
		 Checks whether the face vertices should be defined in clockwise order
		 or not (i.e. counterclockwise order) according to this mesh descriptor.

		 @return		@c true if the face vertices should be defined in clockwise order.
						@c false otherwise.
		 */
		bool ClockwiseOrder() const noexcept {
			return m_clockwise_order;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether the mesh coordinate system handness should be inverted
		 or not for this mesh descriptor.
		 */
		bool m_invert_handedness;

		/**
		 A flag indicating whether the face vertices should be defined in clockwise order
		 or not (i.e. counterclockwise order) for this mesh descriptor.
		 */
		bool m_clockwise_order;
	};
}