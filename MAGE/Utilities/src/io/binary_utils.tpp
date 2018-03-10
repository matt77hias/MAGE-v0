#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template<>
	[[nodiscard]]
	inline const S8 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		return BytesBigEndianTo< S8 >(bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const U8 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		return bytes.get()[0];
	}
	
	template<>
	[[nodiscard]]
	inline const S16 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { bytes_array[1], bytes_array[0] };
		
		return BytesBigEndianTo< S16 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const U16 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { bytes_array[1], bytes_array[0] };
		
		return BytesBigEndianTo< U16 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const S32 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< S32 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const U32 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< U32 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const S64 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[7], bytes_array[6], bytes_array[5], bytes_array[4],
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< S64 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const U64 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[7], bytes_array[6], bytes_array[5], bytes_array[4],
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< U64 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const F32 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< F32 >(reversed_bytes);
	}
	
	template<>
	[[nodiscard]]
	inline const F64 BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept {
		const auto bytes_array = bytes.get();
		
		const U8 reversed_bytes[] = { 
			bytes_array[7], bytes_array[6], bytes_array[5], bytes_array[4],
			bytes_array[3], bytes_array[2], bytes_array[1], bytes_array[0]
		};
		
		return BytesBigEndianTo< F64 >(reversed_bytes);
	}
}