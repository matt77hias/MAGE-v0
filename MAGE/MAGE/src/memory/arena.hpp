#pragma once

namespace mage {

	//-----------------------------------------------------------------------------
	// MemoryArena
	//-----------------------------------------------------------------------------
	class MemoryArena {

	public:
		MemoryArena(uint32_t block_size = 32768) : m_block_size(block_size), m_current_block_pos(0) {
			m_current_block = AllocAligned<char>(m_block_size);
		}
		~MemoryArena() {
			FreeAligned(m_current_block);
			for (size_t i = 0; i < m_used_blocks.size(); ++i) {
				FreeAligned(m_used_blocks[i]);
			}
			for (size_t i = 0; i < m_available_blocks.size(); ++i) {
				FreeAligned(m_available_blocks[i]);
			}
		}

		void FreeAll() {
			m_current_block_pos = 0;
			while (m_used_blocks.size()) {
				m_available_blocks.push_back(m_used_blocks.back());
				m_used_blocks.pop_back();
			}
		}

		void *Alloc(uint32_t size) {
			// Round up _sz_ to minimum machine alignment
			size = ((size + 15) & (~15));
			if (m_current_block_pos + size > m_block_size) {
				// Get new block of memory for this MemoryArena
				m_used_blocks.push_back(m_current_block);
				if (m_available_blocks.size() && size <= m_block_size) {
					m_current_block = m_available_blocks.back();
					m_available_blocks.pop_back();
				}
				else {
					m_current_block = AllocAligned<char>(max(size, m_block_size));
				}
				m_current_block_pos = 0;
			}
			void *ptr = m_current_block + m_current_block_pos;
			m_current_block_pos += size;
			return ptr;
		}

		template<typename T>
		T *Alloc(uint32_t count = 1) {
			T *ptr = (T *)Alloc(count * sizeof(T));
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) T();
			}
			return ptr;
		}

	private:
		// MemoryArena Private Data
		uint32_t m_current_block_pos, m_block_size;
		char *m_current_block;
		vector<char *> m_used_blocks, m_available_blocks;
	};
}
