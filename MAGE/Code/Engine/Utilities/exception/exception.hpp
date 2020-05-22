#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <exception>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Exception
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of formatted exceptions.
	 */
	class Exception : public std::exception {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a formatted exception.
		 */
		Exception();

		/**
		 Constructs a formatted exception.

		 @tparam		ArgsT
						The format argument types.
		 @param[in]		format_str
						The format string.
		 @param[in]		args
						A reference to the format arguments.
		 */
		template< typename... ArgsT >
		explicit Exception(std::string_view format_str, const ArgsT&... args);

		/**
		 Constructs a formatted exception from the given formatted exception.

		 @param[in]		exception
						A reference to a formatted exception to copy.
		 */
		Exception(const Exception& exception);

		/**
		 Constructs a formatted exception by moving the given formatted
		 exception.

		 @param[in]		exception
						A reference to a formatted exception to move.
		 */
		Exception(Exception&& exception);

		/**
		 Destructs this formatted exception.
		 */
		virtual ~Exception();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given formatted exception to this formatted exception.

		 @param[in]		exception
						A reference to a formatted exception to copy.
		 @return		A reference to the copy of the given formatted
						exception (i.e. this formatted exception).
		 */
		Exception& operator=(const Exception& exception);

		/**
		 Moves the given formatted exception to this formatted exception.

		 @param[in]		exception
						A reference to a formatted exception to move.
		 @return		A reference to the moved formatted exception (i.e.
						this formatted exception).
		 */
		Exception& operator=(Exception&& exception);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns a null-terminated byte string that may be used to identify the
		 exception.

		 @return		A null-terminated byte string that may be used to
						identify the exception.
		 */
		virtual const char* what() const noexcept override;

	private:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The buffer size of exceptions.
		 */
		static constexpr std::size_t s_buffer_size = 2048u;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The text buffer of this formatted exception.
		 */
		char m_text[s_buffer_size];
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Exception: Utilities
	//-------------------------------------------------------------------------
	#pragma region

	static_assert(!std::is_same< bool, BOOL >::value,
				  "MAGE/Windows primitive type mismatch");
	static_assert(!std::is_same< BOOL, HRESULT >::value,
				  "MAGE/Windows primitive type mismatch");

	/**
	 Throws if the given result correspond to a failure.

	 @param[in]		result
					The result value.
	 @throws		Exception
					@a result is @c false.
	 */
	void ThrowIfFailed(bool result);

	/**
	 Throws if the given result correspond to a failure.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		result
					The result value.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 @throws		Exception
					@a result is @c false.
	 */
	template< typename... ArgsT >
	void ThrowIfFailed(bool result,
					   std::string_view format_str, const ArgsT&... args);

	/**
	 Throws if the given result correspond to a failure.

	 @param[in]		result
					The result value.
	 @throws		Exception
					@a result is @c FALSE.
	 */
	void ThrowIfFailed(BOOL result);

	/**
	 Throws if the given result correspond to a failure.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		result
					The result value.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 @throws		Exception
					@a result is @c FALSE.
	 */
	template< typename... ArgsT >
	void ThrowIfFailed(BOOL result,
					   std::string_view format_str, const ArgsT&... args);

	/**
	 Throws if the given result correspond to a failure.

	 @param[in]		result
					The result value.
	 @throws		Exception
					The given result corresponds to a failure.
	 */
	void ThrowIfFailed(HRESULT result);

	/**
	 Throws if the given result correspond to a failure.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		result
					The result value.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 @throws		Exception
					The given result corresponds to a failure.
	 */
	template< typename... ArgsT >
	void ThrowIfFailed(HRESULT result,
					   std::string_view format_str, const ArgsT&... args);

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.tpp"

#pragma endregion