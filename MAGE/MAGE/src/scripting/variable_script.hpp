#pragma once

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
		VariableScript(const string &name, const string &path = "./");

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript() {
			m_variables.clear();
		}

		/**
		 Saves this variable script with the given filename.

		 @param[in]		filename
						A reference to the filename.
		 */
		void SaveScript(const string &filename = "");

		/**
		 Import the given variable from the given file to this variable script .

		 @pre			No variable with the name @a name
						exists in this variable script.
		 @param[in]		name
						The name of the variable.
		 @param[in, out]	file
						A pointer to a file containing the value of the variable.
		 */
		void ImportVariable(const string &name, FILE *file);

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
			for (list< Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
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
		 @return		@c NULL if no variable with the name @a name
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

			return NULL;
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
					const VariableType type = (*it)->GetType();
					m_variables.remove(*it);
					AddVariable(name, type, value);
					return;
				}
			}
		}

	private:

		/**
		 Linked list containing the variables in this variable script.
		 */
		list< Variable * > m_variables;
	};
}