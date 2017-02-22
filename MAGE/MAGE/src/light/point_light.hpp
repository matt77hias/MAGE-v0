#pragma once

#include "string\string.hpp"
#include "material\spectrum.hpp"

namespace mage {

	struct PointLight {

	public:

		PointLight(const string name) 
			: m_name(name) {}
		PointLight(const PointLight &light) = default;
		virtual ~PointLight() = default;

		PointLight &operator=(const PointLight &light) = default;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}

	private:

		string m_name;
	};
}