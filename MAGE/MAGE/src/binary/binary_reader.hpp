#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"
#include "memory\memory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class BinaryReader {

	public:

		BinaryReader()
			: m_pos(nullptr), m_end(nullptr) {}
		virtual ~BinaryReader() = default;

		HRESULT ReadFromFile(const wstring &fname, bool big_endian);
		HRESULT ReadFromMemory(const uint8_t *input, size_t size, bool big_endian);

		const wstring &GetFilename() const {
			return m_fname;
		}
		bool HasCharsLeft() const {
			return m_pos < m_end;
		}

	protected:

		virtual HRESULT Process() = 0;

		const char *ReadChars(size_t size);
		int8_t ReadInt8();
		uint8_t ReadUInt8();
		int16_t ReadInt16();
		uint16_t ReadUInt16();
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		int64_t ReadInt64();
		uint64_t ReadUInt64();
		float ReadFloat();
		double ReadDouble();

	private:

		BinaryReader(const BinaryReader &reader) = delete;
		BinaryReader &operator=(const BinaryReader &reader) = delete;

		wstring m_fname;
		bool m_big_endian;
		const uint8_t *m_pos;
		const uint8_t *m_end;
	};
}