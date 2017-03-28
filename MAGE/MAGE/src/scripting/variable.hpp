#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "string\string.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Type Definitions
//-----------------------------------------------------------------------------
#pragma region

namespace mage {

	typedef XMINT2 int2;
	typedef XMINT3 int3;
	typedef XMFLOAT2 float2;
	typedef XMFLOAT3 float3;
	typedef XMFLOAT4 float4;
	typedef XMFLOAT4 color;
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
		Int2Type,
		Int3Type,
		FloatType,
		Float2Type,
		Float3Type,
		Float4Type,
		ColorType,
		StringType,
		UnknownType
	};

	/**
	 A struct of (immutable) variables.
	 */
	struct Variable final {

	public:

		/**
		 Constructs a variable.

		 @tparam		T
						The (storage) type of the value.
		 @param[in]		type
						The (scripting) type of the value.
		 @param[in]		name
						The name.
		 @param[in]		value
						A pointer to the value.
		 */
		template< typename T >
		Variable(VariableType type, const string &name, const T *value) 
			: m_type(type), m_name(name), m_value(new Value< T >(value)) {}

		/**
		 Destructs this variable.
		 */
		~Variable() = default;
		
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
			m_value.reset(new Value< T >(value));
		}

	private:

		/**
		 Constructs a variable from the given variable.

		 @param[in]		variable
						A reference to the variable.
		 */
		Variable(const Variable &variable) = delete;

		/**
		 Constructs a variable from the given variable.

		 @param[in]		variable
						A reference to the variable.
		 */
		Variable(Variable &&variable) = delete;

		/**
		 Copies the given variable to this variable.

		 @param[in]		variable
						A reference to the variable to copy from.
		 @return		A reference to the copy of the given variable
						(i.e. this variable).
		 */
		Variable &operator=(const Variable &variable) = delete;

		/**
		 Copies the given variable to this variable.

		 @param[in]		variable
						A reference to the variable to copy from.
		 @return		A reference to the copy of the given variable
						(i.e. this variable).
		 */
		Variable &operator=(Variable &&variable) = delete;

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
			virtual ~AbstractValue() = default;

			/**
			 Returns the value of this value.

			 @return		A pointer to the value of this value.
			 */
			virtual const void *GetValue() const = 0;

		protected:

			/**
			 Constructs an abstract value.
			 */
			AbstractValue() = default;

			/**
			 Constructs an abstract value from the given abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value.
			 */
			AbstractValue(const AbstractValue &abstract_value) = default;

			/**
			 Constructs an abstract value from the given abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value.
			 */
			AbstractValue(AbstractValue &&abstract_value) = default;

		private:

			/**
			 Copies the given abstract value to this abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to copy from.
			 @return		A reference to the copy of the given abstract value
							(i.e. this abstract value).
			 */
			AbstractValue &operator=(const AbstractValue &abstract_value) = delete;

			/**
			 Copies the given abstract value to this abstract value.

			 @param[in]		abstract_value
							A reference to the abstract value to copy from.
			 @return		A reference to the copy of the given abstract value
							(i.e. this abstract value).
			 */
			AbstractValue &operator=(AbstractValue &&abstract_value) = delete;
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
			Value(const T *value)
				: AbstractValue(), m_value(value) {}

			/**
			 Destructs this value.
			 */
			virtual ~Value() = default;

			/**
			 Returns the value of this value.

			 @return		A pointer to the value of this value.
			 */
			virtual const void *GetValue() const override {
				return (void *)m_value.get();
			}

		private:

			/**
			 Constructs a value from the given value.

			 @param[in]		value
							A reference to the value.
			 */
			Value(const Value &value)
				: AbstractValue(value), m_value(value.m_value) {}

			/**
			 Constructs a value from the given value.

			 @param[in]		value
							A reference to the value.
			 */
			Value(Value &&value)
				: AbstractValue(value), m_value(value.m_value) {
				value.m_data = nullptr;
			}

			/**
			 Copies the given value to this value.

			 @param[in]		value
							A reference to the value to copy from.
			 @return		A reference to the copy of the given value
							(i.e. this value).
			 */
			Value &operator=(const Value &value) = delete;

			/**
			 Copies the given value to this value.

			 @param[in]		value
							A reference to the value to copy from.
			 @return		A reference to the copy of the given value
							(i.e. this value).
			 */
			Value &operator=(Value &&value) = delete;

			/**
			 A pointer to the value of this value.
			 */
			UniquePtr< const T > m_value;
		};

		/**
		 A pointer to the value of this variable.
		 */
		UniquePtr< const AbstractValue > m_value;
	};
}