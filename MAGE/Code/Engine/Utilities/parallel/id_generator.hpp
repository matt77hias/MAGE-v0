#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\atomic_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the next guid.

	 @return		The next guid.
	 */
	U64 GetNextGuid() noexcept;

	/**
	 A class of id generators.
	 */
	template< typename T, typename = std::enable_if_t< std::is_integral_v< T > > >
	class IdGenerator {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an id generator.

		 @param[in]		first_id
						The first id of this id_generator
		 */
		constexpr explicit IdGenerator(T first_id = T(0)) noexcept
			: m_current_id(first_id) {}

		/**
		 Constructs an id generator from the given id generator.

		 @param[in]		generator
						A reference to the id generator to copy.
		 */
		IdGenerator(const IdGenerator& generator) = delete;

		/**
		 Constructs an id generator by moving the given id generator.

		 @param[in]		generator
						A reference to the id generator to move.
		 */
		IdGenerator(IdGenerator&& generator) = delete;

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
		IdGenerator& operator=(const IdGenerator& generator) = delete;

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		generator
						The id generator to move.
		 @return		A reference to the moved id generator (i.e. this id
						generator).
		 */
		IdGenerator& operator=(IdGenerator&& generator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next id of this id generator.

		 @return		The next id of this id generator.
		 */
		T GetNextId() noexcept {
			return m_current_id++;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current id of this id generator.
		 */
		std::atomic< T > m_current_id;
	};
}
