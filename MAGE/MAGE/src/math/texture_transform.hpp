#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of texture transforms.
	 */
	__declspec(align(16)) struct TextureTransform final 
		: public AlignedData< TextureTransform > {

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a texture transform from the given translation, depth, 
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		explicit TextureTransform(
			const XMFLOAT2 &translation = { 0.0f, 0.0f }, 
			f32 rotation = 0.0f, 
			const XMFLOAT2 &rotation_origin = { 0.0f, 0.0f }, 
			const XMFLOAT2 &scale = { 1.0f, 1.0f })
			: m_translation(translation), 
			
			m_rotation(rotation), 
			m_rotation_origin(rotation_origin), 
			m_scale(scale) {

			SetDirty();
		}

		/**
		 Constructs a texture transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit TextureTransform(
			FXMVECTOR translation, 
			f32 rotation, 
			FXMVECTOR rotation_origin, 
			FXMVECTOR scale)
			: m_translation(), 
			m_rotation(rotation), 
			m_rotation_origin(), 
			m_scale() {
			
			SetTranslation(translation);
			SetRotationOrigin(rotation_origin);
			SetScale(scale);
		}

		/**
		 Constructs a texture transform from the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to copy.
		 */
		TextureTransform(const TextureTransform &transform) = default;

		/**
		 Constructs a texture transform by moving the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to move.
		 */
		TextureTransform(TextureTransform &&transform) = default;

		/**
		 Destructs this texture transform.
		 */
		~TextureTransform() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given texture transform to this texture transform.

		 @param[in]		transform
						The texture transform to move.
		 @return		A reference to the copy of the given texture transform
						(i.e. this texture transform).
		 */
		TextureTransform &operator=(
			const TextureTransform &transform) = default;

		/**
		 Moves the given texture transform to this texture transform.

		 @param[in]		transform
						The texture transform to copy.
		 @return		A reference to the moved texture transform (i.e. this 
						texture transform).
		 */
		TextureTransform &operator=(
			TextureTransform &&transform) = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this texture 
		 transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(f32 x) noexcept {
			m_translation.x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the translation component of this texture 
		 transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(f32 y) noexcept {
			m_translation.y = y;
			SetDirty();
		}

		/**
		 Sets the translation component of this texture transform to the given 
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslation(f32 x, f32 y) noexcept {
			m_translation.x = x;
			m_translation.y = y;
			SetDirty();
		}

		/**
		 Sets the translation component of this texture transform to the given 
		 translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT2 &translation) noexcept {
			m_translation = translation;
			SetDirty();
		}

		/**
		 Sets the translation component of this texture transform to the given 
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			XMStoreFloat2(&m_translation, translation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the translation component of this texture 
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(f32 x) noexcept {
			m_translation.x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the translation component of this texture 
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(f32 y) noexcept {
			m_translation.y += y;
			SetDirty();
		}

		/**
		 Adds the given translation component to the translation component of 
		 this texture transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslation(f32 x, f32 y) noexcept {
			m_translation.x += x;
			m_translation.y += y;
			SetDirty();
		}

		/**
		 Adds the given translation component to the translation component of 
		 this texture transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT2 &translation) noexcept {
			AddTranslation(translation.x, translation.y);
		}

		/**
		 Adds the given translation component to the translation component of 
		 this texture transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			AddTranslation(XMVectorGetX(translation), XMVectorGetY(translation));
		}

		/**
		 Returns the x-value of the translation component of this texture 
		 transform.

		 @return		The x-value of the translation component of this 
						texture transform.
		 */
		f32 GetTranslationX() const noexcept {
			return m_translation.x;
		}

		/**
		 Returns the y-value of the translation component of this texture 
		 transform.

		 @return		The y-value of the translation component of this 
						texture transform.
		 */
		f32 GetTranslationY() const noexcept {
			return m_translation.y;
		}

		/**
		 Returns the translation component of this texture transform.

		 @return		The translation component of this texture transform.
		 */
		const XMFLOAT2 GetTranslation() const noexcept {
			return m_translation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the rotation component of this texture transform to the given 
		 rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(f32 rotation) noexcept {
			m_rotation = rotation;
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 texture transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(f32 rotation) noexcept {
			m_rotation += rotation;
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 texture transform and clamps the resulting rotation component of this 
		 texture transform between the given values.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		rotation
						The rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddAndClampRotation(
			f32 rotation, f32 min_angle, f32 max_angle) noexcept {
			
			m_rotation = ClampAngleRadians(m_rotation + rotation, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Returns the rotation component of this texture transform.

		 @return		The rotation component of this texture transform.
		 */
		f32 GetRotation() const noexcept {
			return m_rotation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation origin of this texture transform to 
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(f32 x) noexcept {
			m_rotation_origin.x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the rotation origin of this texture transform to 
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(f32 y) noexcept {
			m_rotation_origin.y = y;
			SetDirty();
		}

		/**
		 Sets the rotation origin of this texture transform to the given 
		 rotation origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(f32 x, f32 y) noexcept {
			m_rotation_origin.x = x;
			m_rotation_origin.y = y;
			SetDirty();
		}

		/**
		 Sets the rotation origin of this texture transform to the given 
		 rotation origin.

		 @param[in]		rotation_origin
						A reference to the rotation origin.
		 */
		void SetRotationOrigin(const XMFLOAT2 &rotation_origin) noexcept {
			m_rotation_origin = rotation_origin;
			SetDirty();
		}

		/**
		 Sets the rotation origin of this texture transform to the given 
		 rotation origin.

		 @param[in]		rotation_origin
						A reference to the rotation origin.
		 */
		void SetRotationOrigin(XMFLOAT2 &&rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
			SetDirty();
		}

		/**
		 Sets the rotation origin of this texture transform to the given 
		 rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			XMStoreFloat2(&m_rotation_origin, rotation_origin);
			SetDirty();
		}

		/**
		 Adds the given x-value to the rotation origin of this texture 
		 transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 */
		void AddRotationOriginX(f32 x) noexcept {
			m_rotation_origin.x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the rotation origin of this texture 
		 transform.

		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOriginY(f32 y) noexcept {
			m_rotation_origin.y += y;
			SetDirty();
		}

		/**
		 Adds the given rotation origin to the rotation origin of this texture 
		 transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOrigin(f32 x, f32 y) noexcept {
			m_rotation_origin.x += x;
			m_rotation_origin.y += y;
			SetDirty();
		}

		/**
		 Adds the given rotation origin to the rotation origin of this texture 
		 transform.

		 @param[in]		rotation_origin
						A reference to the rotation origin to add.
		 */
		void AddRotationOrigin(const XMFLOAT2 &rotation_origin) noexcept {
			AddRotationOrigin(rotation_origin.x, rotation_origin.y);
		}

		/**
		 Adds the given rotation origin to the rotation origin of this texture 
		 transform.

		 @param[in]		rotation_origin
						The rotation origin to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			AddRotationOrigin(
				XMVectorGetX(rotation_origin), 
				XMVectorGetY(rotation_origin));
		}

		/**
		 Returns the x-value of the rotation origin of this texture transform.

		 @return		The x-value of the rotation origin of this texture 
						transform.
		 */
		f32 GetRotationOriginX() const noexcept {
			return m_rotation_origin.x;
		}

		/**
		 Returns the y-value of the rotation origin of this texture transform.

		 @return		The y-value of the rotation origin of this texture 
						transform.
		 */
		f32 GetRotationOriginY() const noexcept {
			return m_rotation_origin.y;
		}

		/**
		 Returns the rotation origin of this texture transform.

		 @return		The rotation origin of this texture transform.
		 */
		const XMFLOAT2 GetRotationOrigin() const noexcept {
			return m_rotation_origin;
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this texture transform to 
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(f32 x) noexcept {
			m_scale.x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the scale component of this texture transform to 
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(f32 y) noexcept {
			m_scale.y = y;
			SetDirty();
		}

		/**
		 Sets the scale component of this texture transform to the given scale 
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(f32 s) noexcept {
			SetScale(s, s);
		}

		/**
		 Sets the scale component of this texture transform to the given scale 
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScale(f32 x, f32 y) noexcept {
			m_scale.x = x;
			m_scale.y = y;
			SetDirty();
		}

		/**
		 Sets the scale component of this texture transform to the given scale 
		 component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT2 &scale) noexcept {
			m_scale = scale;
			SetDirty();
		}

		/**
		 Sets the scale component of this texture transform to the given scale 
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			XMStoreFloat2(&m_scale, scale);
			SetDirty();
		}

		/**
		 Adds the given x-value to the scale component of this texture 
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(f32 x) noexcept {
			m_scale.x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the scale component of this texture 
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(f32 y) noexcept {
			m_scale.y += y;
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this texture 
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(f32 s) noexcept {
			AddScale(s, s);
		}

		/**
		 Adds the given scale component to the scale component of this texture 
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScale(f32 x, f32 y) noexcept {
			m_scale.x += x;
			m_scale.y += y;
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this texture 
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT2 &scale) noexcept {
			AddScale(scale.x, scale.y);
		}

		/**
		 Adds the given scale component to the scale component of this texture 
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			AddScale(XMVectorGetX(scale), XMVectorGetY(scale));
			SetDirty();
		}

		/**
		 Returns the x-value of the scale component of this texture transform.

		 @return		The x-value of the scale component of this texture 
						transform.
		 */
		f32 GetScaleX() const noexcept {
			return m_scale.x;
		}

		/**
		 Returns the y-value of the scale component of this texture transform.

		 @return		The y-value of the scale component of this texture 
						transform.
		 */
		f32 GetScaleY() const noexcept {
			return m_scale.y;
		}

		/**
		 Returns the scale component of this texture transform.

		 @return		The scale component of this texture transform.
		 */
		const XMFLOAT2 GetScale() const noexcept {
			return m_scale;
		}

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------

		/**
		 Returns the (object-to-parent) matrix of this texture transform.

		 @return		The (object-to-parent) matrix of this texture 
						transform.
		 */
		const XMMATRIX GetTransformMatrix() const noexcept {
			UpdateObjectToParentMatrix();
			return m_transform;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets this texture transform to dirty.
		 */
		void SetDirty() const noexcept {
			m_dirty_transform = true;
		}

		/**
		 Updates the (object-to-parent) transform matrix of this texture 
		 transform if dirty.
		 */
		void UpdateObjectToParentMatrix() const noexcept {
			if (m_dirty_transform) {
				
				const f32 s = sin(m_rotation);
				const f32 c = cos(m_rotation);
				const f32 sSx = s * m_scale.x;
				const f32 sSy = s * m_scale.y;
				const f32 cSx = c * m_scale.x;
				const f32 cSy = c * m_scale.y;

				const f32 tx = (1.0f - cSx) * m_rotation_origin.x + sSy * m_rotation_origin.y + m_translation.x;
				const f32 ty = (1.0f - cSy) * m_rotation_origin.y - sSx * m_rotation_origin.x + m_translation.y;

				m_transform = XMMATRIX {
					 cSx,  sSx, 0.0f, 0.0f,
					-sSy,  cSy, 0.0f, 0.0f,
					 tx,    ty, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f
				};
				m_dirty_transform = false;
			}
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this texture transform.
		 */
		XMFLOAT2 m_translation;

		/**
		 The rotation component (in radians) of this texture transform.
		 */
		f32 m_rotation;

		/**
		 A flag indicating whether the (object-to-parent) transform matrix of 
		 this texture transform is dirty.
		 */
		mutable bool m_dirty_transform;

		/**
		 The rotation origin of this texture transform.
		 */
		XMFLOAT2 m_rotation_origin;

		/**
		 The scale component of this texture transform.
		 */
		XMFLOAT2 m_scale;

		/**
		 The cached (object-to-parent) transform matrix of this texture 
		 transform.
		 */
		mutable XMMATRIX m_transform;
	};
}