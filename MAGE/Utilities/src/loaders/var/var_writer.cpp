//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_writer.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\logging.hpp"

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
								std::size_t buffer_size) noexcept
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

			template< typename T >
			void operator()(const T& value) const;

		private:

			const std::string& m_key;

			NotNull< zstring > m_buffer;

			std::size_t m_buffer_size;
		};

		template< typename T >
		void VARVisitor::operator()(const T& value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} {}", 
					g_var_token< T >, m_key, value);
		}

		template<>
		void VARVisitor::operator()(const bool& value) const {
			if (value) {
				WriteTo(m_buffer, m_buffer_size, "{} {} true", 
						g_var_token< bool >, m_key);
			}
			else {
				WriteTo(m_buffer, m_buffer_size, "{} {} false", 
						g_var_token< bool >, m_key);
			}
		}

		template<>
		void VARVisitor::operator()(const std::string& value) const {
			WriteTo(m_buffer, m_buffer_size, "{} {} \"{}\"", 
					g_var_token< std::string >, m_key, value);
		}
	}

	VARWriter::VARWriter(const ValueMap& variable_buffer)
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