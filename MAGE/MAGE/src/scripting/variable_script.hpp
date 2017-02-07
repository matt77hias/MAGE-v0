#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp" 
#include "resource\resource.hpp" 
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_SCRIPT_BEGIN_TOKEN "#begin"
#define MAGE_SCRIPT_END_TOKEN "#end"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of variable scripts.
	 */
	class VariableScript : public Resource {

	public:

		/**
		 Constructs a variable script.

		 @param[in]		name
						A reference to the name of the variable script.
		 @param[in]		path
						A reference to the path of the variable script.
		*/
		VariableScript(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript();

		/**
		 Imports this variable script from its associated file.

		 @param[in]		fname
						A reference to the filename.
		 @return		A success/error value.
		 */
		HRESULT ImportScript(const wstring &fname = L"");

		/**
		 Exports this variable script to the file with the given filename.

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
		size_t GetNbOfVariables() const {
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

	protected:

		/**
		 Import the given variable from the given file to this variable script.

		 @pre			No variable with the name @a name
						exists in this variable script.
		 @param[in]		name
						The name of the variable.
		 @param[in]		file
						A pointer to a file used for importing.
		 @return		A success/error value.
		 */
		HRESULT ImportVariable(const string &name, FILE *file);

		/**
		 Export the given variable from this variable script to the given file.

		 @param[in]		variable
						A pointer to the variable variable.
		 @param[in]		file
						A pointer to a file used for exporting.
		 @return		A success/error value.
		*/
		HRESULT ExportVariable(const Variable *variable, FILE *file);

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
		list< Variable * > m_variables;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.tpp"

#pragma endregion