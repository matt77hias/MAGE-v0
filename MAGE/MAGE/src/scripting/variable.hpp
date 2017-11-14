#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different (scripting) variable types.

	 This contains:
	 @c Bool,
	 @c Int,
	 @c Int2,
	 @c Int3,
	 @c Float,
	 @c Float2,
	 @c Float3,
	 @c Float4,
	 @c Color and
	 @c VariableType::String.
	 */
	enum struct VariableType {
		Bool,
		Int,
		Int2,
		Int3,
		Float,
		Float2,
		Float3,
		Float4,
		Color,
		String
	};

	/**
	 A struct of (immutable) variables.
	 */
	struct Variable final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable.

		 @tparam		T
						The (storage) type of the value.
		 @param[in]		type
						The (scripting) type of the value.
		 @param[in]		name
						The name.
		 @param[in]		value
						A reference to the value.
		 */
		template< typename T >
		Variable(VariableType type, string name, const T &value) 
			: m_type(type), m_name(std::move(name)), 
			m_value(MakeUnique< Value< T > >(value)) {}

		/**
		 Constructs a variable from the given variable.

		 @param[in]		variable
						A reference to the variable to copy.
		 */
		Variable(const Variable &variable) 
			: m_type(variable.m_type), 
			m_name(variable.m_name), 
			m_value(variable.m_value->Clone()) {}

		/**
		 Constructs a variable by moving the given variable.

		 @param[in]		variable
						A reference to the variable to move.
		 */
		Variable(Variable &&variable) = default;

		/**
		 Destructs this variable.
		 */
		~Variable() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable to this variable.

		 @param[in]		variable
						A reference to the variable to copy.
		 @return		A reference to the copy of the given variable (i.e. 
						this variable).
		 */
		Variable &operator=(const Variable &variable) = default;

		/**
		 Moves the given variable to this variable.

		 @param[in]		variable
						A reference to the variable to copy.
		 @return		A reference to the moved variable (i.e. this variable).
		 */
		Variable &operator=(Variable &&variable) = default;
		
		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the scripting type of this value.

		 @return		The type of this value.
		 */
		VariableType GetType() const noexcept {
			return m_type;
		}

		/**
		 Returns the name of this variable.

		 @return		A reference to the name of this variable.
		 */
		const string &GetName() const noexcept {
			return m_name;
		}

		/**
		 Returns the value of this variable.

		 @return		A pointer to the value of this variable.
		 */
		const void *GetValue() const noexcept {
			return m_value->GetValue();
		}

		/**
		 Sets the value of this variable.
	
		 @tparam		T
						The (storage) type of the value.
		 @param[in]		value
						A reference to the value.
		 */
		template< typename T >
		void SetValue(const T &value) {
			m_value = MakeUnique< Value< T > >(value);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The type of this value.

		 @note			It is not possible to use typeid(T).name() since this 
						assumes a bijection between the scripting types and the 
						storage types, which is not the case. Thus the type 
						needs to be stored explicitly.
		 */
		const VariableType m_type;

		/**
		 The name of this variable.
		 */
		const string m_name;

		/**
		 A struct of immutable abstract values.

		 @note			This is an example of the Type Erasure pattern for 
						templates. We need to keep the original type to ensure the 
						right destructor can be called.
		 */
		struct AbstractValue {

		public:

			//---------------------------------------------------------------------
			// Destructors
			//---------------------------------------------------------------------

			/**
			 Destructs this value.
			 */
			virtual ~AbstractValue() = default;

			//---------------------------------------------------------------------
			// Assignment Operators
			//---------------------------------------------------------------------	

			/**
			 Copies the given abstract value to this abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to copy.
			 @return		A reference to the copy of the given abstract value 
							(i.e. this abstract value).
			 */
			AbstractValue &operator=(const AbstractValue &abstract_value) = delete;

			/**
			 Moves the given abstract value to this abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to move.
			 @return		A reference to the moved abstract value (i.e. this 
							abstract value).
			 */
			AbstractValue &operator=(AbstractValue &&abstract_value) = delete;

			//---------------------------------------------------------------------
			// Member Methods
			//---------------------------------------------------------------------

			/**
			 Clones this abstract value.

			 @return		A pointer to a clone of this abstract value.
			 */
			virtual AbstractValue *Clone() const = 0;

			/**
			 Returns the value of this abstract value.

			 @return		A pointer to the value of this abstract value.
			 */
			virtual const void *GetValue() const noexcept = 0;

		protected:

			//---------------------------------------------------------------------
			// Constructors
			//---------------------------------------------------------------------

			/**
			 Constructs an abstract value.
			 */
			AbstractValue() = default;

			/**
			 Constructs an abstract value from the given abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to copy.
			 */
			AbstractValue(const AbstractValue &abstract_value) = default;

			/**
			 Constructs an abstract value by moving the given abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to move.
			 */
			AbstractValue(AbstractValue &&abstract_value) = default;
		};

		/**
		 A struct of immutable values.

		 @tparam		T
						The type of the value.
		 */
		template < typename T >
		struct Value final : public AbstractValue {

		public:

			//---------------------------------------------------------------------
			// Constructors and Destructors
			//---------------------------------------------------------------------

			/**
			 Constructs a value.

			 @param[in]		value
							A reference to the value.
			 */
			explicit Value(const T &value)
				: AbstractValue(), m_value(value) {}

			/**
			 Constructs a value from the given value.

			 @param[in]		value
							A reference to the value to copy.
			 */
			Value(const Value &value) = default;

			/**
			 Constructs a value by moving the given value.

			 @param[in]		value
							A reference to the value to move.
			 */
			Value(Value &&value) = default;

			/**
			 Destructs this value.
			 */
			virtual ~Value() = default;

			//---------------------------------------------------------------------
			// Assignment Operators
			//---------------------------------------------------------------------	

			/**
			 Copies the given value to this value.

			 @param[in]		value
							A reference to the value to copy.
			 @return		A reference to the copy of the given value (i.e. this 
							value).
			 */
			Value &operator=(const Value &value) = delete;

			/**
			 Moves the given value to this value.

			 @param[in]		value
							A reference to the value to move.
			 @return		A reference to the moved value (i.e. this value).
			 */
			Value &operator=(Value &&value) = delete;

			//---------------------------------------------------------------------
			// Member Methods
			//---------------------------------------------------------------------

			/**
			 Clones this value.

			 @return		A pointer to a clone of this value.
			 */
			virtual Value *Clone() const {
				return new Value(*this);
			}

			/**
			 Returns the value of this value.

			 @return		A pointer to the value of this value.
			 */
			virtual const void *GetValue() const noexcept override {
				return (void *)&m_value;
			}

		private:

			//---------------------------------------------------------------------
			// Member Variables
			//---------------------------------------------------------------------

			/**
			 The value of this value.
			 */
			const T m_value;
		};

		/**
		 A pointer to the value of this variable.
		 */
		UniquePtr< const AbstractValue > m_value;
	};
}