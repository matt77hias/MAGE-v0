#pragma once

//-----------------------------------------------------------------------------
// Engine Type Definitions
//-----------------------------------------------------------------------------
#pragma region

typedef XMFLOAT3 float3;
typedef XMFLOAT4 float4;
typedef XMFLOAT4 colour;

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
	 A struct of variables.
	 */
	struct Variable final {

		/**
		 Constructs a variable.

		 @param[in]		name
						The name.
		 @param[in]		type
						The (scripting) type of the value.
		 @param[in]		value
						A pointer to the value.
		 */
		Variable(const string &name, VariableType type, const void *value) : m_name(name), m_type(type), m_value(value) {}

		/**
		 Destructs this variable.
		 */
		~Variable() {
			delete m_value;
		}
		
		/**
		 Returns the name of this variable.

		 @return		A reference to the name of this variable.
		 */
		const string &GetName() const {
			return m_name;
		}

		/**
		 Returns the type of this value.

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
			return m_value;
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
		 A pointer to the value of this variable.
		 */
		const void *m_value;
	};
}