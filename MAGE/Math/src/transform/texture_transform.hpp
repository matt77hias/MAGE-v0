//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "transform\transform_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of 2D texture transforms supporting non-uniform scaling, rotation
	 and translation.
	 */
	class TextureTransform2D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

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
		explicit TextureTransform2D(F32x2 translation     = { 0.0f, 0.0f },
			                        F32   rotation        =   0.0f,
			                        F32x2 rotation_origin = { 0.0f, 0.0f },
			                        F32x2 scale           = { 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_padding{},
			m_rotation(),
			m_rotation_origin(std::move(rotation_origin)),
			m_scale(std::move(scale)) {

			SetRotation(rotation);
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
		explicit TextureTransform2D(FXMVECTOR translation,
									F32       rotation,
									FXMVECTOR rotation_origin,
									FXMVECTOR scale) noexcept
			: TextureTransform2D(XMStore< F32x2 >(translation),
								 rotation,
								 XMStore< F32x2 >(rotation_origin),
								 XMStore< F32x2 >(scale)) {}

		/**
		 Constructs a texture transform from the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to copy.
		 */
		TextureTransform2D(const TextureTransform2D& transform) noexcept = default;

		/**
		 Constructs a texture transform by moving the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to move.
		 */
		TextureTransform2D(TextureTransform2D&& transform) noexcept = default;

		/**
		 Destructs this texture transform.
		 */
		~TextureTransform2D() = default;

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
		TextureTransform2D& operator=(
			const TextureTransform2D& transform) noexcept = default;

		/**
		 Moves the given texture transform to this texture transform.

		 @param[in]		transform
						The texture transform to copy.
		 @return		A reference to the moved texture transform (i.e. this
						texture transform).
		 */
		TextureTransform2D& operator=(
			TextureTransform2D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this texture
		 transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this texture
		 transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y) noexcept {
			SetTranslation(F32x2(x, y));
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x2 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x2 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this texture
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this texture
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y) noexcept {
			AddTranslation(F32x2(x, y));
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x2& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this texture
		 transform.

		 @return		The x-value of the translation component of this
						texture transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this texture
		 transform.

		 @return		The y-value of the translation component of this
						texture transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the translation component of this texture transform.

		 @return		The translation component of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this texture transform.

		 @return		The translation component of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this texture transform to the given
		 rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32 rotation) noexcept {
			m_rotation = WrapAngleRadians(rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 texture transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(F32 rotation) noexcept {
			SetRotation(GetRotation() + rotation);
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
		void AddRotation(F32 rotation, F32 min_angle, F32 max_angle) noexcept {
			m_rotation = ClampAngleRadians(GetRotation() + rotation,
										   min_angle, max_angle);
		}

		/**
		 Returns the rotation component of this texture transform.

		 @return		The rotation component of this texture transform.
		 */
		[[nodiscard]]
		F32 GetRotation() const noexcept {
			return m_rotation;
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation origin of this texture transform to
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(F32 x) noexcept {
			m_rotation_origin[0u] = x;
		}

		/**
		 Sets the y-value of the rotation origin of this texture transform to
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(F32 y) noexcept {
			m_rotation_origin[1u] = y;
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(F32 x, F32 y) noexcept {
			SetRotationOrigin(F32x2(x, y));
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void SetRotationOrigin(F32x2 rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			SetRotationOrigin(XMStore< F32x2 >(rotation_origin));
		}

		/**
		 Adds the given x-value to the rotation origin of this texture
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 */
		void AddRotationOriginX(F32 x) noexcept {
			SetRotationOriginX(GetRotationOriginX() + x);
		}

		/**
		 Adds the given y-value to the rotation origin of this texture
		 transform.

		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOriginY(F32 y) noexcept {
			SetRotationOriginY(GetRotationOriginY() + y);
		}

		/**
		 Adds the given offsets to the rotation origin of this texture
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOrigin(F32 x, F32 y) noexcept {
			AddRotationOrigin(F32x2(x, y));
		}

		/**
		 Adds the given offset to the rotation origin of this texture
		 transform.

		 @param[in]		offset
						The offset to add.
		 */
		void AddRotationOrigin(const F32x2& offset) noexcept {
			AddRotationOrigin(XMLoad(offset));
		}

		/**
		 Adds the given offset to the rotation origin of this texture
		 transform.

		 @param[in]		offset
						The offset to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR offset) noexcept {
			SetRotationOrigin(GetRotationOrigin() + offset);
		}

		/**
		 Returns the x-value of the rotation origin of this texture transform.

		 @return		The x-value of the rotation origin of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginX() const noexcept {
			return m_rotation_origin[0u];
		}

		/**
		 Returns the y-value of the rotation origin of this texture transform.

		 @return		The y-value of the rotation origin of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginY() const noexcept {
			return m_rotation_origin[1u];
		}

		/**
		 Returns the rotation origin of this texture transform.

		 @return		The rotation origin of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetRotationOriginView() const noexcept {
			return m_rotation_origin;
		}

		/**
		 Returns the rotation origin of this texture transform.

		 @return		The rotation origin of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotationOrigin() const noexcept {
			return XMLoad(m_rotation_origin);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this texture transform to
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this texture transform to
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
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
		void SetScale(F32 x, F32 y) noexcept {
			SetScale(F32x2(x, y));
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x2 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x2 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this texture
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this texture
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
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
		void AddScale(F32 x, F32 y) noexcept {
			AddScale(F32x2(x, y));
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x2& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this texture transform.

		 @return		The x-value of the scale component of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this texture transform.

		 @return		The y-value of the scale component of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the scale component of this texture transform.

		 @return		The scale component of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this texture transform.

		 @return		The scale component of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScale() const noexcept {
			return XMLoad(m_scale);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the transformation matrix of this texture transform.

		 @return		The transformation matrix of this texture transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetTransformMatrix() const noexcept {
			return XMMatrixAffineTransformation2D(GetScale(),
												  GetRotationOrigin(),
												  GetRotation(),
												  GetTranslation());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component (in UV coordinates) of this texture
		 transform.
		 */
		F32x2 m_translation;

		/**
		 The padding of this texture transform.
		 */
		F32 m_padding;

		/**
		 The rotation component (in radians) of this texture transform.
		 */
		F32 m_rotation;

		/**
		 The rotation origin (in UV coordinates) of this texture transform.
		 */
		F32x2 m_rotation_origin;

		/**
		 The scale component of this texture transform.
		 */
		F32x2 m_scale;
	};

	static_assert(32u == sizeof(TextureTransform2D));
}