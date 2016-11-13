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
			: Resource(name, path), m_variables(list< const Variable * >()) {
			ImportScript();
		}

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript() {
			m_variables.clear();
		}

		/**
		 Exports this variable script to the file with the given filename.

		 @param[in]		filename
						A reference to the filename.
		 */
		void ExportScript(const string &filename = "");

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
			for (list< const Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
				if ((*it)->GetName() == name) {
					m_variables.remove(*it);
					return;
				}
			}
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
			for (list< const Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
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
			for (list< const Variable * >::iterator it = m_variables.begin(); it != m_variables.end(); ++it) {
				if ((*it)->GetName() == name) {
					const VariableType type = (*it)->GetType();
					m_variables.remove(*it);
					AddVariable(name, type, value);
					return;
				}
			}
		}

	protected:

		/**
		 Imports this variable script from its associated file.
		 */
		void ImportScript();

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
		list< const Variable * > m_variables;
	};
}