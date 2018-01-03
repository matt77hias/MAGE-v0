#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\parallel\atomic.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of id generators.
	 */
	class IdGenerator final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next guid.

		 @return		The next guid.
		 */
		static S32 GetNextGuid() noexcept {
			return s_guid_generator.GetNextId();
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an id generator.

		 @param[in]		first_id
						The first id of this id_generator
		 */
		constexpr explicit IdGenerator(S32 first_id = 0) noexcept
			: m_current_id(first_id) {}

		/**
		 Constructs an id generator from the given id generator.

		 @param[in]		generator
						A reference to the id generator to copy.
		 */
		constexpr IdGenerator(const IdGenerator &generator) noexcept = delete;

		/**
		 Constructs an id generator by moving the given id generator.

		 @param[in]		generator
						A reference to the id generator to move.
		 */
		constexpr IdGenerator(IdGenerator &&generator) noexcept = default;

		/**
		 Destructs this id generator.
		 */
		~IdGenerator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		generator
						The id generator to copy.
		 @return		A reference to the copy of the given id generator (i.e. 
						this id generator).
		 */
		IdGenerator &operator=(const IdGenerator &generator) noexcept = default;

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		generator
						The id generator to move.
		 @return		A reference to the moved id generator (i.e. this id 
						generator).
		 */
		IdGenerator &operator=(IdGenerator &&generator) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next id of this id generator.

		 @return		The next id of this id generator.
		 */
		S32 GetNextId() noexcept {
			return AtomicAdd(&m_current_id, 1);
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 The guid generator.
		 */
		static IdGenerator s_guid_generator;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current id of this id generator.
		 */
		AtomicS32 m_current_id;
	};
}