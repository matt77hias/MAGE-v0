#include "stdafx.h"

#include "core\engine.hpp"
#include "camera\perspective_camera.hpp"
#include "model\model.hpp"
#include "shader\pixel_shader.hpp"
#include "shader\vertex_shader.hpp"

using namespace mage;

class TestState : public State {
	UniquePtr< Camera > m_camera;
	UniquePtr< Model< VertexPositionNormalTexture > > m_model;
	UniquePtr< VertexShader< VertexPositionNormalTexture > > m_vs;
	UniquePtr< PixelShader > m_ps;

	virtual void Load() override {
		const float width  = (float)g_device_enumeration->GetDisplayMode()->Width;
		const float height = (float)g_device_enumeration->GetDisplayMode()->Height;
		m_camera = make_unique< PerspectiveCamera >(width, height);

		ComPtr< ID3D11Device2 > device = g_engine->GetRenderer().GetDevice();
		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();

		m_vs = make_unique< VertexShader< VertexPositionNormalTexture > >(device, L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/effect_VS.cso");
		m_ps = make_unique< PixelShader >(device, L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/effect_PS.cso");
		
		MeshDescriptor desc(true, true);
		m_model = make_unique< Model < VertexPositionNormalTexture > >("Teapot", device, L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/teapot.obj", desc);
	}

	virtual void Update(double elapsed_time) override {
		m_model->GetTransform().AddRotationY((float)elapsed_time);
		
		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();

		CameraTransformBuffer ct;
		ModelTransformBuffer mt;
		const XMVECTOR p_eye   = XMVectorSet(0.0f, 3.0f, -6.0f, 1.0f);
		const XMVECTOR p_focus = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		const XMVECTOR d_up    = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		ct.world_to_view       = XMMatrixTranspose(XMMatrixLookAtLH(p_eye, p_focus, d_up));
		ct.view_to_projection  = XMMatrixTranspose(m_camera->GetViewToProjectionMatrix());
		mt.model_to_world      = XMMatrixTranspose(m_model->GetTransform().GetObjectToWorldMatrix());

		m_vs->Update(device_context, ct, mt);
		m_ps->Update(device_context);
		m_model->Update(device_context);

		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/script_test.mage");
			s.ExportScript(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/output.mage");
		}
	}
};

void StateSetup() {
	g_engine->GetStateManager().AddState(new TestState(), true);
}

/**
The user-provided entry point for MAGE.

 @param[in]		hinstance
				A handle to the current instance of the application.
 @param[in]		hPrevInstance
				A handle to the previous instance of the application.
				This parameter is always @c nullptr.
 @param[in]		lpCmdLine
				The command line for the application, excluding the program name.
 @param[in]		nCmdShow
				Controls how the window is to be shown.
 @return		If the function succeeds, terminating when it receives a WM_QUIT message, 
				it returns the exit value contained in that message's @c wParam parameter. 
				If the function terminates before entering the message loop, it returns 0.
 */
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int nCmdShow) {

	// Create the engine setup structure.
	EngineSetup setup(hinstance, L"Engine Control Test", StateSetup);

	// Create the engine, then run it.
	g_engine = new Engine(setup);
	g_engine->Run(nCmdShow);
	delete g_engine;

	return 0;
}
