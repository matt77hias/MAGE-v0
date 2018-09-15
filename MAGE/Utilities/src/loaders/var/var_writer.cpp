//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_writer.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\error.hpp"
#include "string\format.hpp"

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
								NotNull< zstring > buffer,
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

			NotNull< zstring > m_buffer;

			size_t m_buffer_size;
		};

		void VARVisitor::operator()(bool value) const {
			if (value) {
				WriteTo(m_buffer, m_buffer_size, "{} {} true", 
						GetVarToken< decltype(value) >(), m_key);
			}
			else {
				WriteTo(m_buffer, m_buffer_size, "{} {} false", 
						GetVarToken< decltype(value) >(), m_key);
			}
		}

		void VARVisitor::operator()(F32 value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} {}", 
					GetVarToken< decltype(value) >(), m_key, value);
		}

		void VARVisitor::operator()(F32x2 value) const {
			const auto [x, y] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y);
		}

		void VARVisitor::operator()(F32x3 value) const {
			const auto [x, y, z] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y, z);
		}

		void VARVisitor::operator()(F32x4 value) const {
			const auto [x, y, z, w] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {} {}",
					  GetVarToken< decltype(value) >(), m_key, x, y, z, w);
		}

		void VARVisitor::operator()(S32 value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} {}", 
					GetVarToken< decltype(value) >(), m_key, value);
		}

		void VARVisitor::operator()(S32x2 value) const {
			const auto [x, y] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y);
		}

		void VARVisitor::operator()(S32x3 value) const {
			const auto [x, y, z] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y, z);
		}

		void VARVisitor::operator()(S32x4 value) const {
			const auto [x, y, z, w] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y, z, w);
		}

		void VARVisitor::operator()(U32 value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} {}", 
					GetVarToken< decltype(value) >(), m_key, value);
		}

		void VARVisitor::operator()(U32x2 value) const {
			const auto [x, y] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y);
		}

		void VARVisitor::operator()(U32x3 value) const {
			const auto [x, y, z] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y, z);
		}

		void VARVisitor::operator()(U32x4 value) const {
			const auto [x, y, z, w] = value;
			WriteTo(m_buffer, m_buffer_size, "{} {} {} {} {} {}", 
					GetVarToken< decltype(value) >(), m_key, x, y, z, w);
		}

		void VARVisitor::operator()(const std::string& value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} \"{}\"", 
					GetVarToken< std::string >(), m_key, value);
		}
	}

	VARWriter::VARWriter(const std::map< std::string, Value >& variable_buffer)
		: Writer(), 
		m_variable_buffer(variable_buffer) {}

	VARWriter::VARWriter(VARWriter&& writer) noexcept = default;

	VARWriter::~VARWriter() = default;

	void VARWriter::Write() {
		char buffer[MAX_PATH];
		const auto not_null_buffer = NotNull< zstring >(buffer);

		for (const auto& [key, value] : m_variable_buffer) {
			const VARVisitor visitor(key, not_null_buffer, std::size(buffer));
			std::visit(visitor, value);
			WriteStringLine(not_null_buffer);
		}
	}
}