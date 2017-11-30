#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Sprite Transform Utilities
	//-------------------------------------------------------------------------

	/**
	 Converts the given normalized screen x-value to absolute screen x-value.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		x
					The normalized screen x-value.
	 */
	F32 ConvertNormalizedToAbsoluteScreenX(F32 x);

	/**
	 Converts the given normalized screen y-value to absolute screen y-value.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		y
					The normalized screen y-value.
	 */
	F32 ConvertNormalizedToAbsoluteScreenY(F32 y);
	
	/**
	 Converts the given normalized screen values to absolute screen values.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		x
					The normalized screen x-value.
	 @param[in]		y
					The normalized screen y-value.
	 */
	inline const F32x2 ConvertNormalizedToAbsoluteScreen(F32 x, F32 y) {
		return F32x2(ConvertNormalizedToAbsoluteScreenX(x), 
			         ConvertNormalizedToAbsoluteScreenY(y));
	}
	
	/**
	 Converts the given normalized screen position to absolute screen position.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		position
					A reference to the normalized screen position.
	 */
	inline const F32x2 ConvertNormalizedToAbsoluteScreen(
		const F32x2 &position) {
		
		return ConvertNormalizedToAbsoluteScreen(position.m_x, position.m_y);
	}
	
	/**
	 Converts the given normalized screen position to absolute screen position.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		position
					The normalized screen position.
	 */
	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(
		FXMVECTOR position);

	/**
	 Converts the given absolute screen x-value to normalized screen x-value.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		x
					The absolute screen x-value.
	 */
	F32 ConvertAbsoluteToNormalizedScreenX(F32 x);

	/**
	 Converts the given absolute screen y-value to normalized screen y-value.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		y
					The absolute screen y-value.
	 */
	F32 ConvertAbsoluteToNormalizedScreenY(F32 y);
	
	/**
	 Converts the given absolute screen values to normalized screen values.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		x
					The absolute screen x-value.
	 @param[in]		y
					The absolute screen y-value.
	 */
	inline const F32x2 ConvertAbsoluteToNormalizedScreen(F32 x, F32 y) {
		return F32x2(ConvertAbsoluteToNormalizedScreenX(x), 
			         ConvertAbsoluteToNormalizedScreenY(y));
	}
	
	/**
	 Converts the given absolute screen position to normalized screen position.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		position
					A reference to the absolute screen position.
	 */
	inline const F32x2 ConvertAbsoluteToNormalizedScreen(
		const F32x2 &position) {
		
		return ConvertAbsoluteToNormalizedScreen(position.m_x, position.m_y);
	}
	
	/**
	 Converts the given absolute screen position to normalized screen position.

	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		position
					The absolute screen position.
	 */
	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(
		FXMVECTOR position);

	//-------------------------------------------------------------------------
	// SpriteTransform
	//-------------------------------------------------------------------------

	/**
	 A class of sprite transforms.
	 */
	class alignas(16) SpriteTransform final {

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
		explicit SpriteTransform(
			F32x2 translation     = { 0.0f, 0.0f }, 
			F32 depth             = 0.0f,
			F32 rotation          = 0.0f, 
			F32x2 rotation_origin = { 0.0f, 0.0f }, 
			F32x2 scale           = { 1.0f, 1.0f })
			: m_translation(std::move(translation)), 
			m_depth(depth), 
			m_rotation(rotation), 
			m_rotation_origin(std::move(rotation_origin)), 
			m_scale(std::move(scale)) {
			
			SetDirty();
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
		explicit SpriteTransform(
			FXMVECTOR translation, 
			F32 depth,
			F32 rotation, 
			FXMVECTOR rotation_origin, 
			FXMVECTOR scale)
			: m_translation(), 
			m_depth(depth),
			m_rotation(rotation), 
			m_rotation_origin(), 
			m_scale() {
			
			SetTranslation(translation);
			SetRotationOrigin(rotation_origin);
			SetScale(scale);
		}

		/**
		 Constructs a sprite transform from the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to copy.
		 */
		SpriteTransform(const SpriteTransform &transform) = default;

		/**
		 Constructs a sprite transform by moving the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to move.
		 */
		SpriteTransform(SpriteTransform &&transform) = default;

		/**
		 Destructs this sprite transform.
		 */
		~SpriteTransform() = default;

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
		SpriteTransform &operator=(const SpriteTransform &transform) = default;

		/**
		 Moves the given sprite transform to this sprite transform.

		 @param[in]		transform
						The sprite transform to copy.
		 @return		A reference to the moved sprite transform (i.e. this 
						sprite transform).
		 */
		SpriteTransform &operator=(SpriteTransform &&transform) = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this sprite transform 
		 to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation.m_x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the translation component of this sprite transform 
		 to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation.m_y = y;
			SetDirty();
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
			m_translation.m_x = x;
			m_translation.m_y = y;
			SetDirty();
		}

		/**
		 Sets the translation component of this sprite transform to the given 
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x2 translation) noexcept {
			m_translation = std::move(translation);
			SetDirty();
		}

		/**
		 Sets the translation component of this sprite transform to the given 
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			XMStoreFloat2(&m_translation, translation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the translation component of this sprite 
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			m_translation.m_x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the translation component of this sprite 
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			m_translation.m_y += y;
			SetDirty();
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
			m_translation.m_x += x;
			m_translation.m_y += y;
			SetDirty();
		}

		/**
		 Adds the given translation component to the translation component of 
		 this sprite transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x2 &translation) noexcept {
			AddTranslation(translation.m_x, translation.m_y);
		}

		/**
		 Adds the given translation component to the translation component of 
		 this sprite transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			AddTranslation(XMVectorGetX(translation), 
				           XMVectorGetY(translation));
		}

		/**
		 Returns the x-value of the translation component of this sprite 
		 transform.

		 @return		The x-value of the translation component of this 
						sprite transform.
		 */
		F32 GetTranslationX() const noexcept {
			return m_translation.m_x;
		}

		/**
		 Returns the y-value of the translation component of this sprite 
		 transform.

		 @return		The y-value of the translation component of this 
						sprite transform.
		 */
		F32 GetTranslationY() const noexcept {
			return m_translation.m_y;
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		const F32x2 GetTranslation() const noexcept {
			return m_translation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Normalized Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this sprite transform 
		 to the given normalized value.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component.
		 */
		void SetNormalizedTranslationX(F32 x) {
			SetTranslationX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Sets the y-value of the translation component of this sprite transform 
		 to the given normalized value.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		y
						The y-value of the normalized translation component.
		 */
		void SetNormalizedTranslationY(F32 y) {
			SetTranslationY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Sets the translation component of this sprite transform to the given 
		 normalized translation component.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component.
		 @param[in]		y
						The y-value of the normalized translation component.
		 */
		void SetNormalizedTranslation(F32 x, F32 y) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Sets the translation component of this sprite transform to the given 
		 normalized translation component.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		translation
						A reference to the normalized translation component.
		 */
		void SetNormalizedTranslation(const F32x2 &translation) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Sets the translation component of this sprite transform to the given 
		 normalized translation component.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		translation
						The normalized translation component.
		 */
		void XM_CALLCONV SetNormalizedTranslation(FXMVECTOR translation) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Adds the given x-value to the normalized translation component of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component to 
						add.
		 */
		void AddNormalizedTranslationX(F32 x) {
			AddTranslationX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Adds the given y-value to the normalized translation component of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		y
						The y-value of the normalized translation component to 
						add.
		 */
		void AddNormalizedTranslationY(F32 y) {
			AddTranslationY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Adds the given translation component to the normalized translation 
		 component of this sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component to 
						add.
		 @param[in]		y
						The y-value of the normalized translation component to 
						add.
		 */
		void AddNormalizedTranslation(F32 x, F32 y) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Adds the given translation component to the normalized translation 
		 component of this sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		translation
						A reference to the normalized translation component to 
						add.
		 */
		void AddNormalizedTranslation(const F32x2 &translation) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Adds the given translation component to the normalized translation 
		 component of this sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		translation
						The normalized translation component to add.
		 */
		void XM_CALLCONV AddNormalizedTranslation(FXMVECTOR translation) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Returns the x-value of the normalized translation component of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The x-value of the normalized translation component of 
						this sprite transform.
		 */
		F32 GetNormalizedTranslationX() const {
			return ConvertAbsoluteToNormalizedScreenX(GetTranslationX());
		}

		/**
		 Returns the y-value of the normalized translation component of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The y-value of the normalized translation component of 
						this sprite transform.
		 */
		F32 GetNormalizedTranslationY() const {
			return ConvertAbsoluteToNormalizedScreenY(GetTranslationY());
		}

		/**
		 Returns the normalized translation component of this sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The normalized translation component of this sprite 
						transform.
		 */
		const F32x2 GetNormalizedTranslation() const {
			return ConvertAbsoluteToNormalizedScreen(GetTranslation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Depth
		//---------------------------------------------------------------------

		/**
		 Sets the depth component of this sprite transform to the given depth 
		 component.

		 @param[in]		depth
						The depth component.
		 */
		void SetDepth(F32 depth) noexcept {
			m_depth = depth;
			SetDirty();
		}

		/**
		 Adds the given depth component to the depth component of this sprite 
		 transform.

		 @param[in]		depth
						The depth component to add.
		 */
		void AddDepth(F32 depth) noexcept {
			m_depth += depth;
			SetDirty();
		}

		/**
		 Returns the depth component of this sprite transform.

		 @return		The depth component of this sprite transform.
		 */
		F32 GetDepth() const noexcept {
			return m_depth;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the rotation component of this sprite transform to the given r
		 otation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32 rotation) noexcept {
			m_rotation = rotation;
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 sprite transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(F32 rotation) noexcept {
			m_rotation += rotation;
			SetDirty();
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
		void AddAndClampRotation(
			F32 rotation, F32 min_angle, F32 max_angle) noexcept {
			
			m_rotation = ClampAngleRadians(m_rotation + rotation, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Returns the rotation component of this sprite transform.

		 @return		The rotation component of this sprite transform.
		 */
		F32 GetRotation() const noexcept {
			return m_rotation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation origin of this sprite transform to 
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(F32 x) noexcept {
			m_rotation_origin.m_x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to 
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(F32 y) noexcept {
			m_rotation_origin.m_y = y;
			SetDirty();
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
			m_rotation_origin.m_x = x;
			m_rotation_origin.m_y = y;
			SetDirty();
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation 
		 origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void SetRotationOrigin(F32x2 rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
			SetDirty();
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation 
		 origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			XMStoreFloat2(&m_rotation_origin, rotation_origin);
			SetDirty();
		}

		/**
		 Adds the given x-value to the rotation origin of this sprite 
		 transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 */
		void AddRotationOriginX(F32 x) noexcept {
			m_rotation_origin.m_x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the rotation origin of this sprite 
		 transform.

		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOriginY(F32 y) noexcept {
			m_rotation_origin.m_y += y;
			SetDirty();
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite 
		 transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOrigin(F32 x, F32 y) noexcept {
			m_rotation_origin.m_x += x;
			m_rotation_origin.m_y += y;
			SetDirty();
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite 
		 transform.

		 @param[in]		rotation_origin
						A reference to the rotation origin to add.
		 */
		void AddRotationOrigin(const F32x2 &rotation_origin) noexcept {
			AddRotationOrigin(rotation_origin.m_x, rotation_origin.m_y);
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite 
		 transform.

		 @param[in]		rotation_origin
						The rotation origin to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			AddRotationOrigin(XMVectorGetX(rotation_origin), 
				              XMVectorGetY(rotation_origin));
		}

		/**
		 Returns the x-value of the rotation origin of this sprite transform.

		 @return		The x-value of the rotation origin of this sprite 
						transform.
		 */
		F32 GetRotationOriginX() const noexcept {
			return m_rotation_origin.m_x;
		}

		/**
		 Returns the y-value of the rotation origin of this sprite transform.

		 @return		The y-value of the rotation origin of this sprite 
						transform.
		 */
		F32 GetRotationOriginY() const noexcept {
			return m_rotation_origin.m_y;
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
		 */
		const F32x2 GetRotationOrigin() const noexcept {
			return m_rotation_origin;
		}

		//---------------------------------------------------------------------
		// Member Methods: Normalized Rotation Origin
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation origin of this sprite transform to 
		 the given normalized value.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOriginX(F32 x) {
			SetRotationOriginX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to 
		 the given normalized value.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		y
						The y-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOriginY(F32 y) {
			SetRotationOriginY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given 
		 normalized rotation origin.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin.
		 @param[in]		y
						The y-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOrigin(F32 x, F32 y) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given 
		 normalized rotation origin.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		rotation_origin
						A reference to the normalized rotation origin.
		 */
		void SetNormalizedRotationOrigin(const F32x2 &rotation_origin) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(rotation_origin));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given 
		 normalized rotation origin.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		rotation_origin
						The normalized rotation origin.
		 */
		void XM_CALLCONV SetNormalizedRotationOrigin(FXMVECTOR rotation_origin) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(rotation_origin));
		}

		/**
		 Adds the given x-value to the normalized rotation origin of this sprite 
		 transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOriginX(F32 x) {
			AddRotationOriginX(ConvertAbsoluteToNormalizedScreenX(x));
		}

		/**
		 Adds the given y-value to the normalized rotation origin of this sprite 
		 transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		y
						The y-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOriginY(F32 y) {
			AddRotationOriginY(ConvertAbsoluteToNormalizedScreenY(y));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin to add.
		 @param[in]		y
						The y-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOrigin(F32 x, F32 y) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(x, y));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		rotation_origin
						A reference to the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOrigin(const F32x2 &rotation_origin) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(rotation_origin));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this 
		 sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @param[in]		rotation_origin
						The normalized rotation origin to add.
		 */
		void XM_CALLCONV AddNormalizedRotationOrigin(FXMVECTOR rotation_origin) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(rotation_origin));
		}

		/**
		 Returns the x-value of the normalized rotation origin of this sprite 
		 transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The x-value of the normalized rotation origin of this 
						sprite transform.
		 */
		F32 GetNormalizedRotationOriginX() const {
			return ConvertAbsoluteToNormalizedScreenX(GetRotationOriginX());
		}

		/**
		 Returns the y-value of the normalized rotation origin of this sprite 
		 transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The y-value of the normalized rotation origin of this 
						sprite transform.
		 */
		F32 GetNormalizedRotationOriginY() const {
			return ConvertAbsoluteToNormalizedScreenY(GetRotationOriginY());
		}

		/**
		 Returns the normalized rotation origin of this sprite transform.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		The normalized rotation origin of this sprite 
						transform.
		 */
		const F32x2 GetNormalizedRotationOrigin() const {
			return ConvertAbsoluteToNormalizedScreen(GetRotationOrigin());
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this sprite transform to 
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale.m_x = x;
			SetDirty();
		}

		/**
		 Sets the y-value of the scale component of this sprite transform to 
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale.m_y = y;
			SetDirty();
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
			m_scale.m_x = x;
			m_scale.m_y = y;
			SetDirty();
		}

		/**
		 Sets the scale component of this sprite transform to the given scale 
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x2 scale) noexcept {
			m_scale = std::move(scale);
			SetDirty();
		}

		/**
		 Sets the scale component of this sprite transform to the given scale 
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			XMStoreFloat2(&m_scale, scale);
			SetDirty();
		}

		/**
		 Adds the given x-value to the scale component of this sprite 
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			m_scale.m_x += x;
			SetDirty();
		}

		/**
		 Adds the given y-value to the scale component of this sprite 
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			m_scale.m_y += y;
			SetDirty();
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
			m_scale.m_x += x;
			m_scale.m_y += y;
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this sprite 
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x2 &scale) noexcept {
			AddScale(scale.m_x, scale.m_y);
		}

		/**
		 Adds the given scale component to the scale component of this sprite 
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			AddScale(XMVectorGetX(scale), 
				     XMVectorGetY(scale));
		}

		/**
		 Returns the x-value of the scale component of this sprite transform.

		 @return		The x-value of the scale component of this sprite 
						transform.
		 */
		F32 GetScaleX() const noexcept {
			return m_scale.m_x;
		}

		/**
		 Returns the y-value of the scale component of this sprite transform.

		 @return		The y-value of the scale component of this sprite 
						transform.
		 */
		F32 GetScaleY() const noexcept {
			return m_scale.m_y;
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
		 */
		const F32x2 GetScale() const noexcept {
			return m_scale;
		}

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------

		/**
		 Returns the (object-to-parent) matrix of this sprite transform.

		 @return		The (object-to-parent) matrix of this sprite transform.
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
		 Sets this sprite transform to dirty.
		 */
		void SetDirty() const noexcept {
			m_dirty_transform = true;
		}

		/**
		 Updates the (object-to-parent) transform matrix of this sprite 
		 transform if dirty.
		 */
		void UpdateObjectToParentMatrix() const noexcept {
			if (m_dirty_transform) {
				
				const F32 s = sin(m_rotation);
				const F32 c = cos(m_rotation);
				const F32 sSx = s * m_scale.m_x;
				const F32 sSy = s * m_scale.m_y;
				const F32 cSx = c * m_scale.m_x;
				const F32 cSy = c * m_scale.m_y;

				const F32 tx = (1.0f - cSx) * m_rotation_origin.m_x + sSy * m_rotation_origin.m_y + m_translation.m_x;
				const F32 ty = (1.0f - cSy) * m_rotation_origin.m_y - sSx * m_rotation_origin.m_x + m_translation.m_y;

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
		 The translation component of this sprite transform.
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
		 The rotation origin of this sprite transform.
		 */
		F32x2 m_rotation_origin;

		/**
		 The scale component of this sprite transform.
		 */
		F32x2 m_scale;

		/**
		 The cached (object-to-parent) transform matrix of this sprite 
		 transform.
		 */
		mutable XMMATRIX m_transform;

		/**
		 A flag indicating whether the (object-to-parent) transform matrix of 
		 this sprite transform is dirty.
		 */
		mutable bool m_dirty_transform;
	};
}