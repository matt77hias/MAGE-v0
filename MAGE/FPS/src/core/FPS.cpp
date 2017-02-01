#include "stdafx.h"
#include <windows.h>

#include "core\engine.hpp"
#include "camera\perspective_camera.hpp"
#include "mesh\mesh.hpp"
#include "shader\pixel_shader.hpp"
#include "shader\vertex_shader.hpp"
#include <d3dcompiler.h>

using namespace mage;

class TestState : public State {

	PerspectiveCamera *camera;
	Mesh *mesh;
	VertexShader *vs;
	PixelShader *ps;

	virtual void Load() {
		const float width  = (float)g_device_enumeration->GetDisplayMode()->Width;
		const float height = (float)g_device_enumeration->GetDisplayMode()->Height;
		camera = new PerspectiveCamera(width, height);
		
		ComPtr< ID3D11Device2 > device = g_engine->GetRenderer().GetDevice();
		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();

		mesh = new Mesh(device, L"cube.obj", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/");
		mesh->BindBuffers(device_context);
		vs = new VertexShader(device, vertex_input_element_desc, _countof(vertex_input_element_desc), L"effect_VS.cso", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/");
		ps = new PixelShader(device, L"effect_PS.cso", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/");
	};

	virtual void Close() {
		delete camera;
		delete mesh;
		delete vs;
		delete ps;
	}

	virtual void Update(double elapsed_time) override {
		UNUSED(elapsed_time);

		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();
	
		CameraTransformBuffer ct;
		ModelTransformBuffer mt;

		const XMVECTOR p_eye   = XMVectorSet(0.0f, 3.0f, -6.0f, 1.0f);
		const XMVECTOR p_focus = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		const XMVECTOR d_up    = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		ct.world_to_view       = XMMatrixTranspose(XMMatrixLookAtLH(p_eye, p_focus, d_up));
		ct.view_to_projection  = XMMatrixTranspose(camera->GetViewToProjectionMatrix());
		mt.model_to_world      = XMMatrixRotationY((float)elapsed_time);

		vs->Update(device_context, ct, mt);
		ps->Update(device_context);
		mesh->Draw(device_context);

		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_Q)) {
			//PostQuitMessage(0);

			VariableScript s(L"script_test.mage", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/");
			s.ExportScript(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/output.mage");
		}
	};
};

class SmallTestState : public State {

	Camera *camera;
	Mesh *mesh;
	VertexShader *vs;
	PixelShader  *ps;
	ID3D11Buffer *m_vertex_buffer;
	ID3D11Buffer *m_index_buffer;

	virtual void Load() override {

		const float width  = (float)g_device_enumeration->GetDisplayMode()->Width;
		const float height = (float)g_device_enumeration->GetDisplayMode()->Height;
		camera = new PerspectiveCamera(width, height, XM_PIDIV4);

		ComPtr< ID3D11Device2 > device = g_engine->GetRenderer().GetDevice();
		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();

		vs = new VertexShader(device, vertex_input_element_desc, _countof(vertex_input_element_desc), L"effect_VS.cso", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/");
		ps = new PixelShader(device, L"effect_PS.cso", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/");

		//mesh = new Mesh(device, L"cube.obj", L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/");
		//mesh->BindBuffers(device_context);

		// Vertex buffer setup
		{
			const Vertex vertices[] = {
				{ Point3(-1.0f,  1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ Point3(1.0f,  1.0f, -1.0f),  XMFLOAT2(0.0f, 0.0f) },
				{ Point3(1.0f,  1.0f,  1.0f),  XMFLOAT2(0.0f, 1.0f) },
				{ Point3(-1.0f,  1.0f,  1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ Point3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ Point3(1.0f, -1.0f, -1.0f),  XMFLOAT2(1.0f, 0.0f) },
				{ Point3(1.0f, -1.0f,  1.0f),  XMFLOAT2(1.0f, 1.0f) },
				{ Point3(-1.0f, -1.0f,  1.0f), XMFLOAT2(0.0f, 1.0f) },
				{ Point3(-1.0f, -1.0f,  1.0f), XMFLOAT2(0.0f, 1.0f) },
				{ Point3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ Point3(-1.0f,  1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ Point3(-1.0f,  1.0f,  1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ Point3(1.0f, -1.0f,  1.0f),  XMFLOAT2(1.0f, 1.0f) },
				{ Point3(1.0f, -1.0f, -1.0f),  XMFLOAT2(0.0f, 1.0f) },
				{ Point3(1.0f,  1.0f, -1.0f),  XMFLOAT2(0.0f, 0.0f) },
				{ Point3(1.0f,  1.0f,  1.0f),  XMFLOAT2(1.0f, 0.0f) },
				{ Point3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
				{ Point3(1.0f, -1.0f, -1.0f),  XMFLOAT2(1.0f, 1.0f) },
				{ Point3(1.0f,  1.0f, -1.0f),  XMFLOAT2(1.0f, 0.0f) },
				{ Point3(-1.0f,  1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ Point3(-1.0f, -1.0f,  1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ Point3(1.0f, -1.0f,  1.0f),  XMFLOAT2(0.0f, 1.0f) },
				{ Point3(1.0f,  1.0f,  1.0f),  XMFLOAT2(0.0f, 0.0f) },
				{ Point3(-1.0f,  1.0f,  1.0f), XMFLOAT2(1.0f, 0.0f) }
			};

			D3D11_BUFFER_DESC buffer_desc;
			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.ByteWidth = sizeof(vertices);
			buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer_desc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA init_data;
			ZeroMemory(&init_data, sizeof(init_data));
			init_data.pSysMem = vertices;

			const HRESULT result_vertex_buffer = device->CreateBuffer(&buffer_desc, &init_data, &m_vertex_buffer);
			if (FAILED(result_vertex_buffer)) {
				return throw 10;;
			}
		}
		// Index buffer setup
		{
			const WORD indices[] = {
				3,  1,  0,
				2,  1,  3,
				6,  4,  5,
				7,  4,  6,
				11,  9,  8,
				10,  9, 11,
				14, 12, 13,
				15, 12, 14,
				19, 17, 16,
				18, 17, 19,
				22, 20, 21,
				23, 20, 22
			};

			D3D11_BUFFER_DESC buffer_desc;
			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.ByteWidth = sizeof(indices);
			buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			buffer_desc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA init_data;
			ZeroMemory(&init_data, sizeof(init_data));
			init_data.pSysMem = indices;

			const HRESULT result_index_buffer = device->CreateBuffer(&buffer_desc, &init_data, &m_index_buffer);
			if (FAILED(result_index_buffer)) {
				return throw 10;;
			}
		}

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		device_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
		device_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R16_UINT, 0);
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	virtual void Close() override {
		delete camera;
		delete mesh;
		delete vs;
		delete ps;
	}

	virtual void Update(double elapsed_time) override {
		ComPtr< ID3D11DeviceContext2 > device_context = g_engine->GetRenderer().GetDeviceContext();

		CameraTransformBuffer ct;
		ModelTransformBuffer mt;

		const XMVECTOR p_eye   = XMVectorSet(0.0f, 3.0f, -6.0f, 1.0f);
		const XMVECTOR p_focus = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		const XMVECTOR d_up    = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		ct.world_to_view       = XMMatrixTranspose(XMMatrixLookAtLH(p_eye, p_focus, d_up));
		ct.view_to_projection  = XMMatrixTranspose(camera->GetViewToProjectionMatrix());
		mt.model_to_world      = XMMatrixIdentity();

		vs->Update(device_context, ct, mt);
		ps->Update(device_context);
		//mesh->Draw(device_context);
		device_context->DrawIndexed(36, 0, 0);
	}
};

void StateSetup() {
	g_engine->GetStateManager().AddState(new SmallTestState(), true);
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

	//Renderer *renderer = g_engine->GetRenderer();
	//Model model(renderer->GetDevice(), "cube.obj", "C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/");
	//model.BindBuffers(renderer->GetDeviceContext());

	g_engine->Run(nCmdShow);
	delete g_engine;

	return 0;
}

