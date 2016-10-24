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
	 A struct of variables.
	 */
	struct Variable final {

		/**
		 Constructs a variable.

		 @tparam		T
						The type of the value.
		 @param[in]		name
						The name.
		 @param[in]		value
						A pointer to the value.
		 */
		template< typename T >
		Variable(const string &name, const T *value) : m_name(name), m_value(new Value< T >(value)) {}

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
		 Returns the value of this variable.

		 @return		A pointer to the value of this variable.
		 */
		const void *GetValue() const {
			return m_value->GetValue();
		}

	private:

		/**
		 The name of this variable.
		 */
		const string m_name;

		/**
		 A struct of abstract values.

		 @note			This is an example of the Type Erasure pattern for templates.
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
		 A struct of values.

		 @tparam		T
						The type of the value.
		 */
		template < typename T >
		struct Value : AbstractValue {

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
				return m_value ;
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