#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct TransformNode final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		TransformNode(Transform *transform)
			: m_transform(transform), m_transform_nodes() {}
		TransformNode(const TransformNode &transform_node) = delete;
		TransformNode(TransformNode &&transform_node) = default;
		~TransformNode() {
			m_transform_nodes.clear();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		TransformNode &operator=(const TransformNode &transform_node) = delete;
		TransformNode &operator=(TransformNode &&transform_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this transform node to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->SetTranslationX(x);
			});
		}

		/**
		 Sets the y-value of the translation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->SetTranslationY(y);
			});
		}

		/**
		 Sets the z-value of the translation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->SetTranslationZ(z);
			});
		}

		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(float x, float y, float z) {
			ForEachTransform([x, y, z](Transform *transform) {
				transform->SetTranslation(x, y, z);
			});
		}

		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT3 &translation) {
			ForEachTransform([&translation](Transform *transform) {
				transform->SetTranslation(translation);
			});
		}

		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMVECTOR &translation) {
			ForEachTransform([&translation](Transform *transform) {
				transform->SetTranslation(translation);
			});
		}

		/**
		 Adds the given x-value to the translation component of this transform node.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->AddTranslationX(x);
			});
		}

		/**
		 Adds the given y-value to the translation component of this transform node.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->AddTranslationY(y);
			});
		}

		/**
		 Adds the given z-value to the translation component of this transform node.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->AddTranslationZ(z);
			});
		}

		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(float x, float y, float z) {
			ForEachTransform([x, y, z](Transform *transform) {
				transform->AddTranslation(x, y, z);
			});
		}

		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) {
			ForEachTransform([&translation](Transform *transform) {
				transform->AddTranslation(translation);
			});
		}

		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMVECTOR &translation) {
			ForEachTransform([&translation](Transform *transform) {
				transform->AddTranslation(translation);
			});
		}

		/**
		 Returns the x-value of the translation component of this transform node.

		 @return		The x-value of the translation component of this transform node.
		 */
		float GetTranslationX() const {
			return m_transform->GetTranslationX();
		}

		/**
		 Returns the y-value of the translation component of this transform node.

		 @return		The y-value of the translation component of this transform node.
		 */
		float GetTranslationY() const {
			return m_transform->GetTranslationY();
		}

		/**
		 Returns the z-value of the translation component of this transform node.

		 @return		The z-value of the translation component of this transform node.
		 */
		float GetTranslationZ() const {
			return m_transform->GetTranslationZ();
		}

		/**
		 Returns the translation component of this transform node.

		 @return		The translation component of this transform node.
		 */
		const XMFLOAT3 GetTranslation() const {
			return m_transform->GetTranslation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation component of this transform node to the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->SetRotationX(x);
			});
		}

		/**
		 Sets the y-value of the rotation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->SetRotationY(y);
			});
		}

		/**
		 Sets the z-value of the rotation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->SetRotationZ(z);
			});
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(float x, float y, float z) {
			ForEachTransform([x, y, z](Transform *transform) {
				transform->SetRotation(x, y, z);
			});
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMFLOAT3 &rotation) {
			ForEachTransform([&rotation](Transform *transform) {
				transform->SetRotation(rotation);
			});
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMVECTOR &rotation) {
			ForEachTransform([&rotation](Transform *transform) {
				transform->SetRotation(rotation);
			});
		}

		/**
		 Sets the rotation component to a rotation of the given angle around the given normal.

		 @param[in]		normal
						A reference to the normal.
		 @param[in]		angle
						The angle.
		 */
		void SetRotationAroundDirection(const XMVECTOR &normal, float angle) {
			ForEachTransform([&normal, angle](Transform *transform) {
				transform->SetRotationAroundDirection(normal, angle);
			});
		}

		/**
		 Adds the given x-value to the rotation component of this transform node.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->AddRotationX(x);
			});
		}

		/**
		 Adds the given y-value to the rotation component of this transform node.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->AddRotationY(y);
			});
		}

		/**
		 Adds the given z-value to the rotation component of this transform node.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->AddRotationZ(z);
			});
		}

		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(float x, float y, float z) {
			ForEachTransform([x, y, z](Transform *transform) {
				transform->AddRotation(x, y, z);
			});
		}

		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) {
			ForEachTransform([&rotation](Transform *transform) {
				transform->AddRotation(rotation);
			});
		}

		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMVECTOR &rotation) {
			ForEachTransform([&rotation](Transform *transform) {
				transform->AddRotation(rotation);
			});
		}

		/**
		 Returns the x-value of the rotation component of this transform node.

		 @return		The x-value of the rotation component of this transform node.
		 */
		float GetRotationX() const {
			return m_transform->GetRotationX();
		}

		/**
		 Returns the y-value of the rotation component of this transform node.

		 @return		The y-value of the rotation component of this transform node.
		 */
		float GetRotationY() const {
			return m_transform->GetRotationY();
		}

		/**
		 Returns the z-value of the rotation component of this transform node.

		 @return		The z-value of the rotation component of this transform node.
		 */
		float GetRotationZ() const {
			return m_transform->GetRotationZ();
		}

		/**
		 Returns the rotation component of this transform node.

		 @return		The rotation component of this transform node.
		 */
		const XMFLOAT3 GetRotation() const {
			return m_transform->GetRotation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this transform node to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->SetScaleX(x);
			});
		}

		/**
		 Sets the y-value of the scale component of this transform node to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->SetScaleY(y);
			});
		}

		/**
		 Sets the z-value of the scale component of this transform node to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->SetScaleZ(z);
			});
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(float s) {
			ForEachTransform([s](Transform *transform) {
				transform->SetScale(s);
			});
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(float x, float y, float z) {
			ForEachTransform([=](Transform *transform) {
				transform->SetScale(x, y, z);
			});
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT3 &scale) {
			ForEachTransform([&scale](Transform *transform) {
				transform->SetScale(scale);
			});
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMVECTOR &scale) {
			ForEachTransform([&scale](Transform *transform) {
				transform->SetScale(scale);
			});
		}

		/**
		 Adds the given x-value to the scale component of this transform node.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) {
			ForEachTransform([x](Transform *transform) {
				transform->AddScaleX(x);
			});
		}

		/**
		 Adds the given y-value to the scale component of this transform node.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) {
			ForEachTransform([y](Transform *transform) {
				transform->AddScaleY(y);
			});
		}

		/**
		 Adds the given z-value to the scale component of this transform node.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) {
			ForEachTransform([z](Transform *transform) {
				transform->AddScaleZ(z);
			});
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(float s) {
			ForEachTransform([s](Transform *transform) {
				transform->AddScale(s);
			});
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(float x, float y, float z) {
			ForEachTransform([x, y, z](Transform *transform) {
				transform->AddScale(x, y, z);
			});
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) {
			ForEachTransform([&scale](Transform *transform) {
				transform->AddScale(scale);
			});
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMVECTOR &scale) {
			ForEachTransform([&scale](Transform *transform) {
				transform->AddScale(scale);
			});
		}

		/**
		 Returns the x-value of the scale component of this transform node.

		 @return		The x-value of the scale component of this transform node.
		 */
		float GetScaleX() const {
			return m_transform->GetScaleX();
		}

		/**
		 Returns the y-value of the scale component of this transform node.

		 @return		The y-value of the scale component of this transform node.
		 */
		float GetScaleY() const {
			return m_transform->GetScaleY();
		}

		/**
		 Returns the z-value of the scale component of this transform node.

		 @return		The z-value of the scale component of this transform node.
		 */
		float GetScaleZ() const {
			return m_transform->GetScaleZ();
		}

		/**
		 Returns the scale component of this transform node.

		 @return		The scale component of this transform node.
		 */
		const XMFLOAT3 GetScale() const {
			return m_transform->GetScale();
		}

		//---------------------------------------------------------------------
		// Member Methods: Scene Graph
		//---------------------------------------------------------------------

		void AddTransform(TransformNode *transform) {
			m_transform_nodes.push_back(transform);

			transform->ForEachTransform([this](Transform *subtransform) {
				subtransform->SetTranslation(GetTranslation());
				subtransform->SetRotation(GetRotation());
				subtransform->SetScale(GetScale());
			});
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods: Scene Graph
		//---------------------------------------------------------------------

		template< typename ActionT >
		void ForEachTransform(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		Transform * const m_transform;
		vector< TransformNode * > m_transform_nodes;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.tpp"

#pragma endregion