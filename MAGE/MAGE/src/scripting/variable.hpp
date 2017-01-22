#pragma once

//-----------------------------------------------------------------------------
// Engine Type Definitions
//-----------------------------------------------------------------------------
#pragma region

namespace mage {

	typedef XMFLOAT3 float3;
	typedef XMFLOAT4 float4;
	typedef XMFLOAT4 colour;

}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Enumeration of variable types.
	 */
	enum VariableType {
		BoolType,
		IntType,
		FloatType,
		Float3Type,
		Float4Type,
		ColourType,
		StringType,
		UnknownType
	};

	/**
	 A struct of (immutable) variables.
	 */
	struct Variable final {

		/**
		 Constructs a variable.

		 @tparam		T
						The (storage) type of the value.
		 @param[in]		name
						The name.
		 @param[in]		type
						The (scripting) type of the value.
		 @param[in]		value
						A pointer to the value.
		 */
		template< typename T >
		Variable(const string &name, VariableType type, const T *value) : m_name(name), m_type(type), m_value(new Value< T >(value)) {}

		/**
		 Destructs this variable.
		 */
		~Variable() {
			delete m_value;
		}
		
		/**
		 Checks whether the given variable is equal to this variable.

		 @param[in]		variable
						A reference to the variable to compare with.
		 @return		@c true if and only if this variable and @a variable
						have the same name.
						@c false otherwise.
		 */
		bool operator==(const Variable &variable) const {
			return m_name == variable.m_name;
		}

		/**
		 Checks whether the given variable is not equal to this variable.

		 @param[in]		variable
						A reference to the variable to compare with.
		 @return		@c true if and only if this variable and @a variable
						have not the same name.
						@c false otherwise.
		 */
		bool operator!=(const Variable &variable) const {
			return m_name != variable.m_name;
		}

		/**
		 Returns the name of this variable.

		 @return		A reference to the name of this variable.
		 */
		const string &GetName() const {
			return m_name;
		}

		/**
		 Returns the scripting type of this value.

		 @return		The type of this value.
		 */
		const VariableType &GetType() const {
			return m_type;
		}

		/**
		 Returns the value of this variable.

		 @return		A pointer to the value of this variable.
		 */
		const void *GetValue() const {
			return m_value->GetValue();
		}

		/**
		 Sets the value of this variable.
	
		 @tparam		T
						The (storage) type of the value.
		 @param[in]		value
						A pointer to the value.
		 */
		template< typename T >
		void SetValue(const T *value) {
			delete m_value;
			m_value = new Value< T >(value);
		}

	private:

		/**
		 The name of this variable.
		 */
		const string m_name;

		/**
		 The type of this value.

		 @note			It is not possible to use typeid(T).name() since this assumes
						a bijection between the scripting types and the storage types,
						which is not the case. Thus the type needs to be stored explicitly.
		 */
		const VariableType m_type;

		/**
		 A struct of immutable abstract values.

		 @note			This is an example of the Type Erasure pattern for templates.
						We need to keep the original type to ensure the right destructor
						can be called in case of non-primitive types.
		 */
		struct AbstractValue {

		public:

			/**
			 Destructs this value.
			 */
			virtual ~AbstractValue() {}

			/**
			 Returns the value of this value.

			 @return		A pointer to the value of this value.
			 */
			virtual const void *GetValue() const = 0;
		};

		/**
		 A struct of immutable values.
		 @tparam		T
						The type of the value.
		 */
		template < typename T >
		struct Value : public AbstractValue {

		public:

			/**
			 Constructs a value.

			 @param[in]		value
							A pointer to the value.
			 */
			Value(const T *value) : m_value(value) {}

			/**
			 Destructs this value.
			 */
			virtual ~Value() {
				delete m_value;
			}

			/**
			 Returns the value of this value.

			 @return		A pointer to the value of this value.
			 */
			virtual const void *GetValue() const {
				return (void *)m_value;
			}

		private:

			/**
			 A pointer to the value of this value.
			 */
			const T *m_value;
		};

		/**
		A pointer to the value of this variable.
		*/
		const AbstractValue *m_value;
	};
}