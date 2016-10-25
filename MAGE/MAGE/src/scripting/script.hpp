#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of scripts.
	 */
	class Script : public Resource {

	public:

		/**
		 Constructs a script.

		 @param[in]		name
						A reference to the name of the script.
		 @param[in]		path
						A reference to the path of the script.
		*/
		Script(const string &name, const string &path = "./");

		/**
		 Destruct this script.
		 */
		virtual ~Script() {
			delete m_variables;
		}

		/**
		 Saves this script with the given filename.

		 @param[in]		filename
						A reference to the filename.
		 */
		void SaveScript(const string &filename = "");

		/**
		 Import the given variable from the given file to this script .

		 @pre			No variable with the name @a name
						exists in this script.
		 @param[in]		name
						The name of the variable.
		 @param[in, out]	file
						A pointer to a file containing the value of the variable.
		 */
		void ImportVariable(const string &name, FILE *file);

		/**
		 Adds the given variable to this script.

		 @pre			No variable with the name @a name
						exists in this script.
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
			m_variables->Add(new Variable(name, type, (void *)value));
		}

		/**
		 Removes the given variable from this script.

		 @param[in]		name
						The name of the variable.
		 @return		@c true if a variable with the name @a name
						exists in this script prior to removal.
		 */
		bool RemoveVariable(const string &name);

		/**
		 Returns the value of the given variable in this script.

		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name of the variable.
		 @return		@c NULL if no variable with the name @a name
						exists in this script.
		 @return		A pointer to the value of the variable.
		*/
		template < typename T >
		const T *GetValueOfVariable(const string &name) const;

		/**
		 Sets the value of the given variable in this script.

		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name of the variable.
		 @param[in]		value
						A pointer to the value of the variable.
		 @note			Nothing happens if no variable with the name @a name
						exists in this script.
		 */
		template < typename T >
		void SetValueOfVariable(const string &name, const T *value);

	private:

		/**
		 Linked list containing the variables in this script.
		 */
		LinkedList< Variable > *m_variables;
	};
}