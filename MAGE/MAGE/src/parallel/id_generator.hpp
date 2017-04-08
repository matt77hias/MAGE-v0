#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel\atomic.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of id generators.
	 */
	struct IdGenerator final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an id generator.

		 @param[in]		first_id
						The first id of this id_generator
		 */
		explicit IdGenerator(uint32_t first_id = 0) 
			: m_current_id(first_id) {}

		/**
		 Constructs an id generator from the given id generator.

		 @param[in]		id_generator
						The id generator.
		 */
		IdGenerator(const IdGenerator &id_generator) = delete;

		/**
		 Constructs an id generator from the given id generator.

		 @param[in]		id_generator
						The id generator.
		 */
		IdGenerator(IdGenerator &&id_generator) = default;

		/**
		 Destructs this id generator.
		 */
		~IdGenerator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		id_generator
						The id generator to copy from.
		 @return		A reference to the copy of the given id generator
						(i.e. this id generator).
		 */
		IdGenerator &operator=(const IdGenerator &id_generator) = delete;

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		id_generator
						The id generator to copy from.
		 @return		A reference to the copy of the given id generator
						(i.e. this id generator).
		 */
		IdGenerator &operator=(IdGenerator &&id_generator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next id of this id generator.

		 @return		The next id of this id generator.
		 */
		inline uint32_t GetNextId() {
			return static_cast< uint32_t >(AtomicAdd(&m_current_id, 1));
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current id of this id generator.
		 */
		AtomicInt32 m_current_id;
	};
}