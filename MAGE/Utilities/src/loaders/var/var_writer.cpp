//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_writer.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	namespace {

		class VARVisitor {

		public:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			explicit VARVisitor(const std::string& key, 
								char* buffer, 
								size_t buffer_size) noexcept
				: m_key(key), 
				m_buffer(buffer), 
				m_buffer_size(buffer_size) {}
			
			VARVisitor(const VARVisitor& visitor) noexcept = default;
			
			VARVisitor(VARVisitor&& visitor) noexcept = default;
			
			~VARVisitor() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------
			
			VARVisitor& operator=(const VARVisitor& visitor) = delete;
			
			VARVisitor& operator=(VARVisitor&& visitor) = delete;

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			void operator()(bool value) const;

			void operator()(F32 value) const;

			void operator()(F32x2 value) const;

			void operator()(F32x3 value) const;

			void operator()(F32x4 value) const;

			void operator()(S32 value) const;

			void operator()(S32x2 value) const;

			void operator()(S32x3 value) const;

			void operator()(S32x4 value) const;

			void operator()(U32 value) const;

			void operator()(U32x2 value) const;

			void operator()(U32x3 value) const;

			void operator()(U32x4 value) const;

			void operator()(const std::string& value) const;

		private:

			const std::string& m_key;

			char* m_buffer;

			size_t m_buffer_size;
		};

		void VARVisitor::operator()(bool value) const {
			if (value) {
				sprintf_s(m_buffer, m_buffer_size, "%s %s true",
						  GetVarToken< decltype(value) >(), m_key.c_str());
			}
			else {
				sprintf_s(m_buffer, m_buffer_size, "%s %s false", 
						  GetVarToken< decltype(value) >(), m_key.c_str());
			}
		}

		void VARVisitor::operator()(F32 value) const {
			sprintf_s(m_buffer, m_buffer_size, "%s %s %f", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  value);
		}

		void VARVisitor::operator()(F32x2 value) const {
			const auto [x, y] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %f %f", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y);
		}

		void VARVisitor::operator()(F32x3 value) const {
			const auto [x, y, z] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %f %f %f", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z);
		}

		void VARVisitor::operator()(F32x4 value) const {
			const auto [x, y, z, w] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %f %f %f %f", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z, w);
		}

		void VARVisitor::operator()(S32 value) const {
			sprintf_s(m_buffer, m_buffer_size, "%s %s %d", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  value);
		}

		void VARVisitor::operator()(S32x2 value) const {
			const auto [x, y] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %d %d", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y);
		}

		void VARVisitor::operator()(S32x3 value) const {
			const auto [x, y, z] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %d %d %d", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z);
		}

		void VARVisitor::operator()(S32x4 value) const {
			const auto [x, y, z, w] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %d %d %d %d", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z, w);
		}

		void VARVisitor::operator()(U32 value) const {
			sprintf_s(m_buffer, m_buffer_size, "%s %s %u", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  value);
		}

		void VARVisitor::operator()(U32x2 value) const {
			const auto [x, y] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %u %u",
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y);
		}

		void VARVisitor::operator()(U32x3 value) const {
			const auto [x, y, z] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %u %u %u", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z);
		}

		void VARVisitor::operator()(U32x4 value) const {
			const auto [x, y, z, w] = value;
			sprintf_s(m_buffer, m_buffer_size, "%s %s %u %u %u %u", 
					  GetVarToken< decltype(value) >(), m_key.c_str(), 
					  x, y, z, w);
		}

		void VARVisitor::operator()(const std::string& value) const {
			sprintf_s(m_buffer, m_buffer_size, "%s %s \"%s\"", 
					  GetVarToken< std::string >(), m_key.c_str(), 
					  value.c_str());
		}
	}

	VARWriter::VARWriter(const std::map< std::string, Value >& variable_buffer)
		: Writer(), 
		m_variable_buffer(variable_buffer) {}

	VARWriter::VARWriter(VARWriter&& writer) noexcept = default;

	VARWriter::~VARWriter() = default;

	void VARWriter::Write() {
		char buffer[MAX_PATH];
		const auto not_null_buffer = NotNull< const_zstring >(buffer);

		for (const auto& [key, value] : m_variable_buffer) {
			const VARVisitor visitor(key, buffer, std::size(buffer));
			std::visit(visitor, value);
			WriteStringLine(not_null_buffer);
		}
	}
}