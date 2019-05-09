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
	 A class of 2D sprite transforms supporting non-uniform scaling, rotation
	 and translation (incl. depth).
	 */
	class SpriteTransform2D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		depth
						The depth component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SpriteTransform2D(F32x2 translation     = { 0.0f, 0.0f },
			                       F32   depth           =   0.0f,
			                       F32   rotation        =   0.0f,
			                       F32x2 rotation_origin = { 0.0f, 0.0f },
			                       F32x2 scale           = { 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_depth(depth),
			m_rotation(),
			m_rotation_origin(std::move(rotation_origin)),
			m_scale(std::move(scale)) {

			SetRotation(rotation);
		}

		/**
		 Constructs a sprite transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		depth
						The depth component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SpriteTransform2D(FXMVECTOR translation,
			                       F32       depth,
			                       F32       rotation,
			                       FXMVECTOR rotation_origin,
			                       FXMVECTOR scale) noexcept
			: SpriteTransform2D(XMStore< F32x2 >(translation),
								depth, rotation,
								XMStore< F32x2 >(rotation_origin),
								XMStore< F32x2 >(scale)) {}

		/**
		 Constructs a sprite transform from the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to copy.
		 */
		SpriteTransform2D(const SpriteTransform2D& transform) noexcept = default;

		/**
		 Constructs a sprite transform by moving the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to move.
		 */
		SpriteTransform2D(SpriteTransform2D&& transform) noexcept = default;

		/**
		 Destructs this sprite transform.
		 */
		~SpriteTransform2D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite transform to this sprite transform.

		 @param[in]		transform
						The sprite transform to move.
		 @return		A reference to the copy of the given sprite transform
						(i.e. this sprite transform).
		 */
		SpriteTransform2D& operator=(
			const SpriteTransform2D& transform) noexcept = default;

		/**
		 Moves the given sprite transform to this sprite transform.

		 @param[in]		transform
						The sprite transform to copy.
		 @return		A reference to the moved sprite transform (i.e. this
						sprite transform).
		 */
		SpriteTransform2D& operator=(
			SpriteTransform2D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this sprite transform
		 to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this sprite transform
		 to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the translation component of this sprite transform to the given
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
		 Sets the translation component of this sprite transform to the given
		 translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const F32x2& translation) noexcept {
			m_translation = translation;
		}

		/**
		 Sets the translation component of this sprite transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x2 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this sprite
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this sprite
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given translation component to the translation component of
		 this sprite transform.

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
		 this sprite transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x2& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this sprite transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this sprite
		 transform.

		 @return		The x-value of the translation component of this
						sprite transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this sprite
		 transform.

		 @return		The y-value of the translation component of this
						sprite transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Depth
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the depth component of this sprite transform to the given depth
		 component.

		 @param[in]		depth
						The depth component.
		 */
		void SetDepth(F32 depth) noexcept {
			m_depth = depth;
		}

		/**
		 Adds the given depth component to the depth component of this sprite
		 transform.

		 @param[in]		depth
						The depth component to add.
		 */
		void AddDepth(F32 depth) noexcept {
			SetDepth(GetDepth() + depth);
		}

		/**
		 Returns the depth component of this sprite transform.

		 @return		The depth component of this sprite transform.
		 */
		[[nodiscard]]
		F32 GetDepth() const noexcept {
			return m_depth;
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this sprite transform to the given r
		 otation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32 rotation) noexcept {
			m_rotation = WrapAngleRadians(rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 sprite transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(F32 rotation) noexcept {
			SetRotation(GetRotation() + rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 sprite transform and clamps the resulting rotation component of this
		 sprite transform between the given values.

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
		 Returns the rotation component of this sprite transform.

		 @return		The rotation component of this sprite transform.
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
		 Sets the x-value of the rotation origin of this sprite transform to
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(F32 x) noexcept {
			m_rotation_origin[0u] = x;
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(F32 y) noexcept {
			m_rotation_origin[1u] = y;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(F32 x, F32 y) noexcept {
			SetRotationOrigin(F32x2(x, y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		rotation_origin
						A reference to the rotation origin.
		 */
		void SetRotationOrigin(const F32x2& rotation_origin) noexcept {
			m_rotation_origin = rotation_origin;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			SetRotationOrigin(XMStore< F32x2 >(rotation_origin));
		}

		/**
		 Adds the given x-value to the rotation origin of this sprite
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 */
		void AddRotationOriginX(F32 x) noexcept {
			SetRotationOriginX(GetRotationOriginX() + x);
		}

		/**
		 Adds the given y-value to the rotation origin of this sprite
		 transform.

		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOriginY(F32 y) noexcept {
			SetRotationOriginY(GetRotationOriginY() + y);
		}

		/**
		 Adds the given offsets to the rotation origin of this sprite
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
		 Adds the given offset to the rotation origin of this sprite transform.

		 @param[in]		offset
						The offset to add.
		 */
		void AddRotationOrigin(const F32x2& offset) noexcept {
			AddRotationOrigin(XMLoad(offset));
		}

		/**
		 Adds the given offset to the rotation origin of this sprite transform.

		 @param[in]		offset
						The offset to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR offset) noexcept {
			SetRotationOrigin(GetRotationOrigin() + offset);
		}

		/**
		 Returns the x-value of the rotation origin of this sprite transform.

		 @return		The x-value of the rotation origin of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginX() const noexcept {
			return m_rotation_origin[0u];
		}

		/**
		 Returns the y-value of the rotation origin of this sprite transform.

		 @return		The y-value of the rotation origin of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginY() const noexcept {
			return m_rotation_origin[1u];
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetRotationOriginView() const noexcept {
			return m_rotation_origin;
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
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
		 Sets the x-value of the scale component of this sprite transform to
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this sprite transform to
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s);
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
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
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const F32x2& scale) noexcept {
			m_scale = scale;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x2 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this sprite
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this sprite
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s);
		}

		/**
		 Adds the given scale component to the scale component of this sprite
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
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x2& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this sprite transform.

		 @return		The x-value of the scale component of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this sprite transform.

		 @return		The y-value of the scale component of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
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
		 Returns the transformation matrix of this sprite transform.

		 @return		The transformation matrix of this sprite transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetTransformMatrix() const noexcept {
			auto transformation = GetAffineTransformationMatrix(GetRotationOrigin(),
																GetScale(),
																GetRotation(),
																GetTranslation());
			transformation.r[3u] = XMVectorSetZ(transformation.r[3], GetDepth());

			return transformation;
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component (in pixels) of this sprite transform.
		 */
		F32x2 m_translation;

		/**
		 The depth component of this sprite transform.
		 */
		F32 m_depth;

		/**
		 The rotation component (in radians) of this sprite transform.
		 */
		F32 m_rotation;

		/**
		 The rotation origin (in texels) of this sprite transform.
		 */
		F32x2 m_rotation_origin;

		/**
		 The scale component of this sprite transform.
		 */
		F32x2 m_scale;
	};

	static_assert(32u == sizeof(SpriteTransform2D));
}