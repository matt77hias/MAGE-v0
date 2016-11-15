#pragma once

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
		VariableScript(const string &name, const string &path = "./")
			: Resource(name, path), m_variables(list< Variable * >()) {
			ImportScript();
		}

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript() {
			m_variables.clear();
		}

		/**
		 Imports this variable script from its associated file.

		 @param[in]		filename
						A reference to the filename.
		 */
		void ImportScript(const string &filename = "");

		/**
		 Exports this variable script to the file with the given filename.

		 @param[in]		filename
						A reference to the filename.
		 */
		void ExportScript(const string &filename = "");

		/**
		 Checks wether this variable script is empty.

		 @return		@c true if this variable script is empty.
						@c false otherwise.
		 */
		bool IsEmpty() const {
			return GetNbOfVariables() == 0;
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
		void AddVariable(const string &name, VariableType type, const T *value) {
			m_variables.push_back(new Variable(name, type, value));
		}

		/**
		 Removes the given variable from this variable script.

		 @param[in]		name
						The name of the variable.
		 */
		void RemoveVariable(const string &name) {
			// Iterate the variables looking for the specified variable.
			Variable *target = nullptr;
			for (list< Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
				if ((*it)->GetName() == name) {
					target = *it;
					break;
				}
			}
			SAFE_DELETE(target);
		}

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
		const T *GetValueOfVariable(const string &name) const {
			// Iterate the states looking for the specified variable.
			for (list< Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
				if ((*it)->GetName() == name) {
					return (T *)((*it)->GetValue());
				}
			}

			return nullptr;
		}

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
		void SetValueOfVariable(const string &name, const T *value) {
			// Iterate the variables looking for the specified variable.
			for (list< Variable * >::iterator it = m_variables.begin(); it != m_variables.end(); ++it) {
				if ((*it)->GetName() == name) {
					(*it)->SetValue(value);
					return;
				}
			}
			Warning("Variable %s not found.", name.c_str());
		}

	protected:

		/**
		 Import the given variable from the given file to this variable script.

		 @pre			No variable with the name @a name
						exists in this variable script.
		 @param[in]		name
						The name of the variable.
		 @param[in]		file
						A pointer to a file used for importing.
		 */
		void ImportVariable(const string &name, FILE *file);

		/**
		 Export the given variable from this variable script to the given file.

		 @param[in]		variable
						A pointer to the variable variable.
		 @param[in]		file
						A pointer to a file used for exporting.
		*/
		void ExportVariable(const Variable *variable, FILE *file);

		/**
		 Linked list containing the variables in this variable script.
		 */
		list< Variable * > m_variables;
	};
}