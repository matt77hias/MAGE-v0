#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template<>
	inline const S8 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);
		
		return BytesBigEndianTo< S8 >(bytes);
	}
	
	template<>
	inline const U8 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);
		
		return bytes[0];
	}
	
	template<>
	inline const S16 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianTo< S16 >(reversed_bytes);
	}
	
	template<>
	inline const U16 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianTo< U16 >(reversed_bytes);
	}
	
	template<>
	inline const S32 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< S32 >(reversed_bytes);
	}
	
	template<>
	inline const U32 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< U32 >(reversed_bytes);
	}
	
	template<>
	inline const S64 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< S64 >(reversed_bytes);
	}
	
	template<>
	inline const U64 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< U64 >(reversed_bytes);
	}
	
	template<>
	inline const F32 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);
		
		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< F32 >(reversed_bytes);
	}
	
	template<>
	inline const F64 BytesLittleEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);
		
		const U8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianTo< F64 >(reversed_bytes);
	}
}