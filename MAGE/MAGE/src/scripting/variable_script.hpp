#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "resource\resource.hpp"
#include "collection\collection.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of variable scripts.
	 */
	class VariableScript : public FileResource {

	public:

		/**
		 Constructs a variable script.

		 @param[in]		fname
						A reference to the filename of the variable script.
		 @param[in]		import
						Flag indicating whether the variables of the variable script
						need to be imported.
		 */
		VariableScript(const wstring &fname, bool import = true);

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript();

		/**
		 Imports this variable script from the file with the given filename.
		 If the filename is not specified the associated filename of this variable script is used.

		 @param[in]		fname
						A reference to the filename.
		 @return		A success/error value.
		 */
		HRESULT ImportScript(const wstring &fname = L"");

		/**
		 Exports this variable script to the file with the given filename.
		 If the filename is not specified the associated filename of this variable script is used.

		 @param[in]		fname
						A reference to the filename.
		 @return		A success/error value.
		 */
		HRESULT ExportScript(const wstring &fname = L"");

		/**
		 Checks wether this variable script is empty.

		 @return		@c true if this variable script is empty.
						@c false otherwise.
		 */
		bool IsEmpty() const {
			return m_variables.empty();
		}

		/**
		 Returns the number of variables in this variable script.

		 @return		The number of variables in this variable script.
		 */
		size_t GetNumberOfVariables() const {
			return m_variables.size();
		}

		/**
		 Adds the given variable to this variable script.

		 @pre			No variable with the name @a name
						exists in this variable script.
		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name of the variable.
		 @param[in]		type
						The type of the variable.
		 @param[in]		value
						A pointer to the value of the variable.
		 */
		template < typename T >
		void AddVariable(const string &name, VariableType type, const T *value);

		/**
		 Removes and destructs the given variable from this variable script.

		 @param[in]		name
						The name of the variable.
		 */
		void RemoveVariable(const string &name);

		/**
		 Removes and destructs all variables from this variable script.
		 */
		void RemoveAllVariables();

		/**
		 Returns the value of the given variable in this variable script.

		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name of the variable.
		 @return		@c nullptr if no variable with the name @a name
						exists in this variable script.
		 @return		A pointer to the value of the variable.
		*/
		template < typename T >
		const T *GetValueOfVariable(const string &name) const;

		/**
		 Sets the value of the given variable in this variable script.

		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name of the variable.
		 @param[in]		value
						A pointer to the value of the variable.
		 @note			Nothing happens if no variable with the name @a name
						exists in this variable script.
		 */
		template < typename T >
		void SetValueOfVariable(const string &name, const T *value);

	private:

		/**
		 Constructs a variable script from the given variable script.

		 @param[in]		variable_script
						A reference to the variable script.
		 */
		VariableScript(const VariableScript &variable_script) = delete;

		/**
		Copies the given variable script to this variable script.

		 @param[in]		variable_script
						A reference to the variable script to copy from.
		 @return		A reference to the copy of the given variable script
						(i.e. this variable script).
		 */
		VariableScript &operator=(const VariableScript &variable_script) = delete;

		/**
		 Linked list containing the variables in this variable script.
		 */
		map< string, Variable * > m_variables;
	};

	/**
	 Creates a variable script.

	 @param[in]		fname
					A reference to the filename of the variable script.
	 @param[in]		import
					Flag indicating whether the variables of the variable script
					need to be imported.
	 @return		A pointer to the variable script.
	 */
	SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import = true);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.tpp"

#pragma endregion