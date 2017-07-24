#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Converts the given normalized screen x-value to absolute screen x-value.

	 @pre			The current engine must be loaded.
	 @param[in]		x
					The normalized screen x-value.
	 */
	float ConvertNormalizedToAbsoluteScreenX(float x);

	/**
	 Converts the given normalized screen y-value to absolute screen y-value.

	 @pre			The current engine must be loaded.
	 @param[in]		y
					The normalized screen y-value.
	 */
	float ConvertNormalizedToAbsoluteScreenY(float y);
	
	/**
	 Converts the given normalized screen values to absolute screen values.

	 @pre			The current engine must be loaded.
	 @param[in]		x
					The normalized screen x-value.
	 @param[in]		y
					The normalized screen y-value.
	 */
	inline const XMFLOAT2 ConvertNormalizedToAbsoluteScreen(float x, float y) {
		return XMFLOAT2(ConvertNormalizedToAbsoluteScreenX(x), ConvertNormalizedToAbsoluteScreenY(y));
	}
	
	/**
	 Converts the given normalized screen position to absolute screen position.

	 @pre			The current engine must be loaded.
	 @param[in]		position
					A reference to the normalized screen position.
	 */
	inline const XMFLOAT2 ConvertNormalizedToAbsoluteScreen(const XMFLOAT2 &position) {
		return ConvertNormalizedToAbsoluteScreen(position.x, position.y);
	}
	
	/**
	 Converts the given normalized screen position to absolute screen position.

	 @pre			The current engine must be loaded.
	 @param[in]		position
					The normalized screen position.
	 */
	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(FXMVECTOR position);

	/**
	 Converts the given absolute screen x-value to normalized screen x-value.

	 @pre			The current engine must be loaded.
	 @param[in]		x
					The absolute screen x-value.
	 */
	float ConvertAbsoluteToNormalizedScreenX(float x);

	/**
	 Converts the given absolute screen y-value to normalized screen y-value.

	 @pre			The current engine must be loaded.
	 @param[in]		y
					The absolute screen y-value.
	 */
	float ConvertAbsoluteToNormalizedScreenY(float y);
	
	/**
	 Converts the given absolute screen values to normalized screen values.

	 @pre			The current engine must be loaded.
	 @param[in]		x
					The absolute screen x-value.
	 @param[in]		y
					The absolute screen y-value.
	 */
	inline const XMFLOAT2 ConvertAbsoluteToNormalizedScreen(float x, float y) {
		return XMFLOAT2(ConvertAbsoluteToNormalizedScreenX(x), ConvertAbsoluteToNormalizedScreenY(y));
	}
	
	/**
	 Converts the given absolute screen position to normalized screen position.

	 @pre			The current engine must be loaded.
	 @param[in]		position
					A reference to the absolute screen position.
	 */
	inline const XMFLOAT2 ConvertAbsoluteToNormalizedScreen(const XMFLOAT2 &position) {
		return ConvertAbsoluteToNormalizedScreen(position.x, position.y);
	}
	
	/**
	 Converts the given absolute screen position to normalized screen position.

	 @pre			The current engine must be loaded.
	 @param[in]		position
					The absolute screen position.
	 */
	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(FXMVECTOR position);

	/**
	 A struct of sprite transforms.
	 */
	__declspec(align(16)) struct SpriteTransform final : public AlignedData< SpriteTransform > {

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite transform from the given translation, depth, 
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		depth
						The depth component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		explicit SpriteTransform(
			const XMFLOAT2 &translation = { 0.0f, 0.0f }, 
			float depth = 0.0f,
			float rotation = 0.0f, 
			const XMFLOAT2 &rotation_origin = { 0.0f, 0.0f }, 
			const XMFLOAT2 &scale = { 1.0f, 1.0f })
			: m_translation(translation), 
			m_depth(depth), 
			m_rotation(rotation), 
			m_rotation_origin(rotation_origin), 
			m_scale(scale) {}

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
			float depth,
			float rotation, 
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
		 @return		A reference to the moved sprite transform
						(i.e. this sprite transform).
		 */
		SpriteTransform &operator=(SpriteTransform &&transform) = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this sprite transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) noexcept {
			m_translation.x = x;
		}

		/**
		 Sets the y-value of the translation component of this sprite transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) noexcept {
			m_translation.y = y;
		}

		/**
		 Sets the translation component of this sprite transform to the given translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslation(float x, float y) noexcept {
			m_translation.x = x;
			m_translation.y = y;
		}

		/**
		 Sets the translation component of this sprite transform to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT2 &translation) noexcept {
			m_translation = translation;
		}

		/**
		 Sets the translation component of this sprite transform to the given translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			XMStoreFloat2(&m_translation, translation);
		}

		/**
		 Adds the given x-value to the translation component of this sprite transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) noexcept {
			m_translation.x += x;
		}

		/**
		 Adds the given y-value to the translation component of this sprite transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) noexcept {
			m_translation.y += y;
		}

		/**
		 Adds the given translation component to the translation component of this sprite transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslation(float x, float y) noexcept {
			m_translation.x += x;
			m_translation.y += y;
		}

		/**
		 Adds the given translation component to the translation component of this sprite transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT2 &translation) noexcept {
			AddTranslation(translation.x, translation.y);
		}

		/**
		 Adds the given translation component to the translation component of this sprite transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			AddTranslation(XMVectorGetX(translation), XMVectorGetY(translation));
		}

		/**
		 Returns the x-value of the translation component of this sprite transform.

		 @return		The x-value of the translation component of this sprite transform.
		 */
		float GetTranslationX() const noexcept {
			return m_translation.x;
		}

		/**
		 Returns the y-value of the translation component of this sprite transform.

		 @return		The y-value of the translation component of this sprite transform.
		 */
		float GetTranslationY() const noexcept {
			return m_translation.y;
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		const XMFLOAT2 GetTranslation() const noexcept {
			return m_translation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Normalized Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this sprite transform to the given normalized value.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component.
		 */
		void SetNormalizedTranslationX(float x) {
			SetTranslationX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Sets the y-value of the translation component of this sprite transform to the given normalized value.

		 @pre			The current engine must be loaded.
		 @param[in]		y
						The y-value of the normalized translation component.
		 */
		void SetNormalizedTranslationY(float y) {
			SetTranslationY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Sets the translation component of this sprite transform to the given normalized translation component.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component.
		 @param[in]		y
						The y-value of the normalized translation component.
		 */
		void SetNormalizedTranslation(float x, float y) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Sets the translation component of this sprite transform to the given normalized translation component.

		 @pre			The current engine must be loaded.
		 @param[in]		translation
						A reference to the normalized translation component.
		 */
		void SetNormalizedTranslation(const XMFLOAT2 &translation) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Sets the translation component of this sprite transform to the given normalized translation component.

		 @pre			The current engine must be loaded.
		 @param[in]		translation
						The normalized translation component.
		 */
		void XM_CALLCONV SetNormalizedTranslation(FXMVECTOR translation) {
			SetTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Adds the given x-value to the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component to add.
		 */
		void AddNormalizedTranslationX(float x) {
			AddTranslationX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Adds the given y-value to the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		y
						The y-value of the normalized translation component to add.
		 */
		void AddNormalizedTranslationY(float y) {
			AddTranslationY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Adds the given translation component to the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized translation component to add.
		 @param[in]		y
						The y-value of the normalized translation component to add.
		 */
		void AddNormalizedTranslation(float x, float y) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Adds the given translation component to the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		translation
						A reference to the normalized translation component to add.
		 */
		void AddNormalizedTranslation(const XMFLOAT2 &translation) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Adds the given translation component to the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		translation
						The normalized translation component to add.
		 */
		void XM_CALLCONV AddNormalizedTranslation(FXMVECTOR translation) {
			AddTranslation(ConvertNormalizedToAbsoluteScreen(translation));
		}

		/**
		 Returns the x-value of the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The x-value of the normalized translation component of this sprite transform.
		 */
		float GetNormalizedTranslationX() const {
			return ConvertAbsoluteToNormalizedScreenX(GetTranslationX());
		}

		/**
		 Returns the y-value of the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The y-value of the normalized translation component of this sprite transform.
		 */
		float GetNormalizedTranslationY() const {
			return ConvertAbsoluteToNormalizedScreenY(GetTranslationY());
		}

		/**
		 Returns the normalized translation component of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The normalized translation component of this sprite transform.
		 */
		const XMFLOAT2 GetNormalizedTranslation() const {
			return ConvertAbsoluteToNormalizedScreen(GetTranslation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Depth
		//---------------------------------------------------------------------

		/**
		 Sets the depth component of this sprite transform to the given depth component.

		 @param[in]		depth
						The depth component.
		 */
		void SetDepth(float depth) noexcept {
			m_depth = depth;
		}

		/**
		 Adds the given depth component to the depth component of this sprite transform.

		 @param[in]		depth
						The depth component to add.
		 */
		void AddDepth(float depth) noexcept {
			m_depth += depth;
		}

		/**
		 Returns the depth component of this sprite transform.

		 @return		The depth component of this sprite transform.
		 */
		float GetDepth() const noexcept {
			return m_depth;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the rotation component of this sprite transform to the given rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(float rotation) noexcept {
			m_rotation = rotation;
		}

		/**
		 Adds the given rotation component to the rotation component of this sprite transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(float rotation) noexcept {
			m_rotation += rotation;
		}

		/**
		 Returns the rotation component of this sprite transform.

		 @return		The rotation component of this sprite transform.
		 */
		float GetRotation() const noexcept {
			return m_rotation;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation origin of this sprite transform to the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(float x) noexcept {
			m_rotation_origin.x = x;
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(float y) noexcept {
			m_rotation_origin.y = y;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(float x, float y) noexcept {
			m_rotation_origin.x = x;
			m_rotation_origin.y = y;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation origin.

		 @param[in]		rotation_origin
						A reference to the rotation origin.
		 */
		void SetRotationOrigin(const XMFLOAT2 &rotation_origin) noexcept {
			m_rotation_origin = rotation_origin;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation origin.

		 @param[in]		rotation_origin
						A reference to the rotation origin.
		 */
		void SetRotationOrigin(XMFLOAT2 &&rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			XMStoreFloat2(&m_rotation_origin, rotation_origin);
		}

		/**
		 Adds the given x-value to the rotation origin of this sprite transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 */
		void AddRotationOriginX(float x) noexcept {
			m_rotation_origin.x += x;
		}

		/**
		 Adds the given y-value to the rotation origin of this sprite transform.

		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOriginY(float y) noexcept {
			m_rotation_origin.y += y;
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite transform.

		 @param[in]		x
						The x-value of the rotation origin to add.
		 @param[in]		y
						The y-value of the rotation origin to add.
		 */
		void AddRotationOrigin(float x, float y) noexcept {
			m_rotation_origin.x += x;
			m_rotation_origin.y += y;
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite transform.

		 @param[in]		rotation_origin
						A reference to the rotation origin to add.
		 */
		void AddRotationOrigin(const XMFLOAT2 &rotation_origin) noexcept {
			AddRotationOrigin(rotation_origin.x, rotation_origin.y);
		}

		/**
		 Adds the given rotation origin to the rotation origin of this sprite transform.

		 @param[in]		rotation_origin
						The rotation origin to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			AddRotationOrigin(XMVectorGetX(rotation_origin), XMVectorGetY(rotation_origin));
		}

		/**
		 Returns the x-value of the rotation origin of this sprite transform.

		 @return		The x-value of the rotation origin of this sprite transform.
		 */
		float GetRotationOriginX() const noexcept {
			return m_rotation_origin.x;
		}

		/**
		 Returns the y-value of the rotation origin of this sprite transform.

		 @return		The y-value of the rotation origin of this sprite transform.
		 */
		float GetRotationOriginY() const noexcept {
			return m_rotation_origin.y;
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
		 */
		const XMFLOAT2 GetRotationOrigin() const noexcept {
			return m_rotation_origin;
		}

		//---------------------------------------------------------------------
		// Member Methods: Normalized Rotation Origin
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation origin of this sprite transform to the given normalized value.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOriginX(float x) {
			SetRotationOriginX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to the given normalized value.

		 @pre			The current engine must be loaded.
		 @param[in]		y
						The y-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOriginY(float y) {
			SetRotationOriginY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given normalized rotation origin.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin.
		 @param[in]		y
						The y-value of the normalized rotation origin.
		 */
		void SetNormalizedRotationOrigin(float x, float y) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(x, y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given normalized rotation origin.

		 @pre			The current engine must be loaded.
		 @param[in]		rotation_origin
						A reference to the normalized rotation origin.
		 */
		void SetNormalizedRotationOrigin(const XMFLOAT2 &rotation_origin) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(rotation_origin));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given normalized rotation origin.

		 @pre			The current engine must be loaded.
		 @param[in]		rotation_origin
						The normalized rotation origin.
		 */
		void XM_CALLCONV SetNormalizedRotationOrigin(FXMVECTOR rotation_origin) {
			SetRotationOrigin(ConvertNormalizedToAbsoluteScreen(rotation_origin));
		}

		/**
		 Adds the given x-value to the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOriginX(float x) {
			AddRotationOriginX(ConvertAbsoluteToNormalizedScreenX(x));
		}

		/**
		 Adds the given y-value to the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		y
						The y-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOriginY(float y) {
			AddRotationOriginY(ConvertAbsoluteToNormalizedScreenY(y));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		x
						The x-value of the normalized rotation origin to add.
		 @param[in]		y
						The y-value of the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOrigin(float x, float y) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(x, y));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		rotation_origin
						A reference to the normalized rotation origin to add.
		 */
		void AddNormalizedRotationOrigin(const XMFLOAT2 &rotation_origin) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(rotation_origin));
		}

		/**
		 Adds the given rotation origin to the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @param[in]		rotation_origin
						The normalized rotation origin to add.
		 */
		void XM_CALLCONV AddNormalizedRotationOrigin(FXMVECTOR rotation_origin) {
			AddRotationOrigin(ConvertAbsoluteToNormalizedScreen(rotation_origin));
		}

		/**
		 Returns the x-value of the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The x-value of the normalized rotation origin of this sprite transform.
		 */
		float GetNormalizedRotationOriginX() const {
			return ConvertAbsoluteToNormalizedScreenX(GetRotationOriginX());
		}

		/**
		 Returns the y-value of the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The y-value of the normalized rotation origin of this sprite transform.
		 */
		float GetNormalizedRotationOriginY() const {
			return ConvertAbsoluteToNormalizedScreenY(GetRotationOriginY());
		}

		/**
		 Returns the normalized rotation origin of this sprite transform.

		 @pre			The current engine must be loaded.
		 @return		The normalized rotation origin of this sprite transform.
		 */
		const XMFLOAT2 GetNormalizedRotationOrigin() const {
			return ConvertAbsoluteToNormalizedScreen(GetRotationOrigin());
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this sprite transform to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(float x) noexcept {
			m_scale.x = x;
		}

		/**
		 Sets the y-value of the scale component of this sprite transform to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) noexcept {
			m_scale.y = y;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(float s) noexcept {
			SetScale(s, s);
		}

		/**
		 Sets the scale component of this sprite transform to the given scale component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScale(float x, float y) noexcept {
			m_scale.x = x;
			m_scale.y = y;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT2 &scale) noexcept {
			m_scale = scale;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			XMStoreFloat2(&m_scale, scale);
		}

		/**
		 Adds the given x-value to the scale component of this sprite transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) noexcept {
			m_scale.x += x;
		}

		/**
		 Adds the given y-value to the scale component of this sprite transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) noexcept {
			m_scale.y += y;
		}

		/**
		 Adds the given scale component to the scale component of this sprite transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(float s) noexcept {
			AddScale(s, s);
		}

		/**
		 Adds the given scale component to the scale component of this sprite transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScale(float x, float y) noexcept {
			m_scale.x += x;
			m_scale.y += y;
		}

		/**
		 Adds the given scale component to the scale component of this sprite transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT2 &scale) noexcept {
			AddScale(scale.x, scale.y);
		}

		/**
		 Adds the given scale component to the scale component of this sprite transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			AddScale(XMVectorGetX(scale), XMVectorGetY(scale));
		}

		/**
		 Returns the x-value of the scale component of this sprite transform.

		 @return		The x-value of the scale component of this sprite transform.
		 */
		float GetScaleX() const noexcept {
			return m_scale.x;
		}

		/**
		 Returns the y-value of the scale component of this sprite transform.

		 @return		The y-value of the scale component of this sprite transform.
		 */
		float GetScaleY() const noexcept {
			return m_scale.y;
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
		 */
		const XMFLOAT2 GetScale() const noexcept {
			return m_scale;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this sprite transform.
		 */
		XMFLOAT2 m_translation;

		/**
		 The depth component of this sprite transform.
		 */
		float m_depth;

		/**
		 The rotation component (in radians) of this sprite transform.
		 */
		float m_rotation;

		/**
		 The rotation origin of this sprite transform.
		 */
		XMFLOAT2 m_rotation_origin;

		/**
		 The scale component of this sprite transform.
		 */
		XMFLOAT2 m_scale;
	};
}