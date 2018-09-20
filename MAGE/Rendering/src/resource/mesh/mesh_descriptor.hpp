#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of mesh descriptors.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT = U32 >
	class MeshDescriptor {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mesh descriptor.

		 @param[in]		invert_handedness
						A flag indicating whether the mesh coordinate system
						handness should be inverted.
		 @param[in]		clockwise_order
						A flag indicating whether the face vertices should be
						defined in clockwise order or not (i.e.
						counterclockwise order).
		 */
		constexpr explicit MeshDescriptor(
			bool invert_handedness = false,
			bool clockwise_order   = true) noexcept
			: m_invert_handedness(invert_handedness),
			m_clockwise_order(clockwise_order) {}

		/**
		 Constructs a mesh descriptor from the given mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to copy.
		 */
		constexpr MeshDescriptor(const MeshDescriptor& desc) noexcept = default;

		/**
		 Constructs a mesh descriptor by moving the given mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to move.
		 */
		constexpr MeshDescriptor(MeshDescriptor&& desc) noexcept = default;

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
		MeshDescriptor& operator=(const MeshDescriptor& desc) noexcept = default;

		/**
		 Moves the given mesh descriptor to this mesh descriptor.

		 @param[in]		desc
						A reference to the mesh descriptor to move.
		 @return		A reference to the moved mesh descriptor (i.e. this
						mesh descriptor).
		 */
		MeshDescriptor& operator=(MeshDescriptor&& desc) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether the mesh coordinate system handness should be inverted
		 or not according to this mesh descriptor.

		 @return		@c true if the mesh coordinate system handness should
						be inverted. @c false otherwise.
		 */
		[[nodiscard]]
		constexpr bool InvertHandness() const noexcept {
			return m_invert_handedness;
		}

		/**
		 Checks whether the face vertices should be defined in clockwise order
		 or not (i.e. counterclockwise order) according to this mesh
		 descriptor.

		 @return		@c true if the face vertices should be defined in
						clockwise order. @c false otherwise.
		 */
		[[nodiscard]]
		constexpr bool ClockwiseOrder() const noexcept {
			return m_clockwise_order;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether the mesh coordinate system handness should
		 be inverted or not for this mesh descriptor.
		 */
		bool m_invert_handedness;

		/**
		 A flag indicating whether the face vertices should be defined in
		 clockwise order or not (i.e. counterclockwise order) for this mesh
		 descriptor.
		 */
		bool m_clockwise_order;
	};
}