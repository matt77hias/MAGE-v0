#pragma once

namespace mage {

	class Renderer {

	public:

		Renderer() {}

		virtual ~Renderer() {}

	private:

		IDXGIDevice3 *m_device;
	};

}