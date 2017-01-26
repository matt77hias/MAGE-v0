//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"
#include "mesh\mesh_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	FlatMesh::FlatMesh(ID3D11Device2 *device, const string &name, const string &path)
		: Mesh(name, path), m_vertex_buffer(nullptr) {
		
		const HRESULT result_buffers = InitializeBuffers(device);
		if (FAILED(result_buffers)) {
			Warning("Buffers initialization failed: %ld.", result_buffers);
		}
	}

	FlatMesh::~FlatMesh() {
		const HRESULT result_buffers = UninitializeBuffers();
		if (FAILED(result_buffers)) {
			Warning("Buffers uninitialization failed: %ld.", result_buffers);
		}
	}

	HRESULT FlatMesh::InitializeBuffers(ID3D11Device2 *device) {

		const string &fname = GetFilename();
		vector< Vertex > vertices;
		const HRESULT result_load = LoadMeshFromFile(fname, vertices);
		if (FAILED(result_load)) {
			Warning("FlatMesh loading failed: %ld.", result_load);
			return result_load;
		}

		const HRESULT result_vertex_buffer = SetupVertexBuffer(device, &vertices[0], vertices.size());
		if (FAILED(result_vertex_buffer)) {
			Warning("Vertex buffer initialization failed: %ld.", result_vertex_buffer);
			return result_vertex_buffer;
		}

		return S_OK;
	}

	HRESULT FlatMesh::UninitializeBuffers() {
		SAFE_RELEASE(m_vertex_buffer);
		return S_OK;
	}

	HRESULT FlatMesh::SetupVertexBuffer(ID3D11Device2 *device, const Vertex *vertices, size_t nb_vertices) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = (UINT)(nb_vertices * sizeof(Vertex));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem          = vertices;

		// Create the vertex buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		const HRESULT result_vertex_buffer = device->CreateBuffer(&buffer_desc, &init_data, &m_vertex_buffer);
		if (FAILED(result_vertex_buffer)) {
			Warning("CreateBuffer failed: %ld.", result_vertex_buffer);
			return result_vertex_buffer;
		}

		return S_OK;
	}

	HRESULT FlatMesh::BindBuffers(ID3D11DeviceContext2 *device_context) {
		// Set the vertex buffer.
		UINT stride = sizeof(Vertex);	// The size (in bytes) of the elements that are to be used from a vertex buffer.
		UINT offset = 0;				// The number of bytes between the first element of a vertex buffer and the first element that will be used.
										// 1. The first input slot for binding.
										// 2. The number of vertex buffers in the array.
										// 3. A pointer to an array of vertex buffers.
										// 4. A pointer to an array of stride values.
										// 5. A pointer to an array of offset values.
		device_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

		// Bind information about the primitive type, and data order that describes input data for the input assembler stage.
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return S_OK;
	}
}