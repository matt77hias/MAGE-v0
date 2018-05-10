#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "resource\script\variable_value.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of variable scripts.
	 */
	class VariableScript : public Resource< VariableScript > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable script.

		 @param[in]		fname
						The filename (the globally unique identifier).
		 @param[in]		import
						Flag indicating whether the variables of the variable 
						script need to be imported.
		 @throws		Exception
						Failed to import the variable script from file (only 
						possible if @a import is equal to @c true).
		 */
		explicit VariableScript(wstring fname, bool import = true);

		/**
		 Constructs a variable script from the given variable script.

		 @param[in]		variable_script
						A reference to the variable script to copy.
		 */
		VariableScript(const VariableScript& variable_script) = delete;

		/**
		 Constructs a variable script by moving the given variable script.

		 @param[in]		variable_script
						A reference to the variable script to move.
		 */
		VariableScript(VariableScript&& variable_script) noexcept;

		/**
		 Destruct this variable script.
		 */
		virtual ~VariableScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable script to this variable script.

		 @param[in]		variable_script
						A reference to the variable script to copy.
		 @return		A reference to the copy of the given variable script
						(i.e. this variable script).
		 */
		VariableScript& operator=(const VariableScript& variable_script) = delete;

		/**
		 Moves the given variable script to this variable script.

		 @param[in]		variable_script
						A reference to the variable script to move.
		 @return		A reference to the moved variable script (i.e. this 
						variable script).
		 */
		VariableScript& operator=(VariableScript&& variable_script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Imports this variable script from the file of this variable script.

		 @throws		Exception
						Failed to import the variable script from file.
		 */
		void ImportScript() {
			ImportScript(GetPath());
		}

		/**
		 Imports this variable script from the file associated with the given 
		 path.

		 @param[in]		path
						A reference to the path.
		 @throws		Exception
						Failed to import the variable script from file.
		 */
		void ImportScript(const std::filesystem::path& path);

		/**
		 Exports this variable script to the file of this variable script.

		 @throws		Exception
						Failed to export the variable script to file.
		 */
		void ExportScript() const {
			ExportScript(GetPath());
		}

		/**
		 Exports this variable script to the file associated with the given 
		 path.

		 @param[in]		path
						A reference to the path.
		 @throws		Exception
						Failed to export the variable script to file.
		 */
		void ExportScript(const std::filesystem::path& path) const;

		/**
		 Checks whether this variable script is empty.

		 @return		@c true if this variable script is empty. @c false 
						otherwise.
		 */
		[[nodiscard]]
		bool empty() const noexcept {
			using std::empty;
			return empty(m_variables);
		}

		/**
		 Returns the number of variables in this variable script.

		 @return		The number of variables in this variable script.
		 */
		[[nodiscard]]
		size_t size() const noexcept {
			using std::size;
			return size(m_variables);
		}

		/**
		 Checks whether this variable script contains a variable with the given 
		 name and type (if specified).

		 @tparam		T
						The type of the variable.
		 @param[in]		name
						A reference to the name of the variable.
		 @return		@c true if this variable script has a variable with the 
						given name. @c false otherwise.
		 */
		template< typename T = void >
		[[nodiscard]]
		bool Contains(const string& name) const noexcept;

		/**
		 Adds the given variable to this variable script.

		 @tparam		T
						The type of the variable.
		 @param[in]		name
						The name of the variable.
		 @param[in]		value
						The value of the variable.
		 */
		template< typename T >
		void Add(string name, T value);

		/**
		 Removes the given variable from this variable script.

		 @param[in]		name
						A reference to the name of the variable.
		 */
		void Remove(const string& name);

		/**
		 Removes all variables from this variable script.
		 */
		void RemoveAll() noexcept {
			m_variables.clear();
		}

		/**
		 Returns the value of the given variable of this variable script.

		 @tparam		T
						The type of the variable.
		 @param[in]		name
						A reference to the name of the variable.
		 @return		@c nullptr if this variable script does not contain a 
						variable corresponding to the given name.
		 @return		A pointer to the value of the variable.
		 @throws		std::bad_variant_access
						The variable corresponding to the given name has a 
						different type.
		 */
		template< typename T >
		[[nodiscard]]
		const T* GetValue(const string& name) const;

		/**
		 Sets the value of the given variable in this variable script.

		 @tparam		T
						The type of the variable.
		 @param[in]		name
						A reference to the name of the variable.
		 @param[in]		value
						The value of the variable.
		 @note			Nothing happens if this variable script does not 
						contain a variable corresponding to the given name.
		 */
		template< typename T >
		void SetValue(const string& name, T value);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A map containing the variables of this variable script.
		 */
		std::map< string, Value > m_variables;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\script\variable_script.tpp"

#pragma endregion