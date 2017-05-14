//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering_utils.hpp"
#include "texture\dds\dds_loader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Macros
//--------------------------------------------------------------------------------------
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
				((uint32_t)(uint8_t)(ch0) | \
				((uint32_t)(uint8_t)(ch1) << 8) | \
				((uint32_t)(uint8_t)(ch2) << 16) | \
				((uint32_t)(uint8_t)(ch3) << 24 ))
#endif

#pragma pack(push,1)

namespace mage {

	const uint32_t DDS_MAGIC = 0x20534444; // "DDS "

	struct DDS_PIXELFORMAT {
		uint32_t    size;
		uint32_t    flags;
		uint32_t    fourCC;
		uint32_t    RGBBitCount;
		uint32_t    RBitMask;
		uint32_t    GBitMask;
		uint32_t    BBitMask;
		uint32_t    ABitMask;
	};

#define DDS_FOURCC      0x00000004  // DDPF_FOURCC
#define DDS_RGB         0x00000040  // DDPF_RGB
#define DDS_LUMINANCE   0x00020000  // DDPF_LUMINANCE
#define DDS_ALPHA       0x00000002  // DDPF_ALPHA

#define DDS_HEADER_FLAGS_VOLUME         0x00800000  // DDSD_DEPTH

#define DDS_HEIGHT 0x00000002 // DDSD_HEIGHT
#define DDS_WIDTH  0x00000004 // DDSD_WIDTH

#define DDS_CUBEMAP_POSITIVEX 0x00000600 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX
#define DDS_CUBEMAP_NEGATIVEX 0x00000a00 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEX
#define DDS_CUBEMAP_POSITIVEY 0x00001200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEY
#define DDS_CUBEMAP_NEGATIVEY 0x00002200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEY
#define DDS_CUBEMAP_POSITIVEZ 0x00004200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEZ
#define DDS_CUBEMAP_NEGATIVEZ 0x00008200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEZ

#define DDS_CUBEMAP_ALLFACES ( DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX |\
							   DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY |\
							   DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ )

#define DDS_CUBEMAP 0x00000200 // DDSCAPS2_CUBEMAP

	enum DDS_MISC_FLAGS2 {
		DDS_MISC_FLAGS2_ALPHA_MODE_MASK = 0x7L
	};

	struct DDS_HEADER {
		uint32_t        size;
		uint32_t        flags;
		uint32_t        height;
		uint32_t        width;
		uint32_t        pitch_or_linear_size;
		uint32_t        depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
		uint32_t        mip_map_count;
		uint32_t        reserved1[11];
		DDS_PIXELFORMAT ddspf;
		uint32_t        caps;
		uint32_t        caps2;
		uint32_t        caps3;
		uint32_t        caps4;
		uint32_t        reserved2;
	};

	struct DDS_HEADER_DXT10 {
		DXGI_FORMAT     dxgi_format;
		uint32_t        resource_dimension;
		uint32_t        misc_flag; // see D3D11_RESOURCE_MISC_FLAG
		uint32_t        array_size;
		uint32_t        misc_flags2;
	};

#pragma pack(pop)

	template< UINT TNameLength >
	inline void SetDebugObjectName(_In_ ID3D11DeviceChild *resource, _In_ const char(&name)[TNameLength]) {
#if defined(_DEBUG) || defined(PROFILE)
		resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#else
		UNREFERENCED_PARAMETER(resource);
		UNREFERENCED_PARAMETER(name);
#endif
	}

static HRESULT LoadTextureDataFromFile(_In_z_ const wchar_t *file_name, std::unique_ptr<uint8_t[]> &dds_data, DDS_HEADER **header, uint8_t **bit_data, size_t *bit_size) {
	if (!header || !bit_data || !bit_size) {
		return E_POINTER;
	}

	// open the file
	UniqueHandle hfile(SafeHandle(CreateFile2(file_name, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr)));


	if (!hfile) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Get the file size
	LARGE_INTEGER file_size = { 0 };

	FILE_STANDARD_INFO file_info;
	if (!GetFileInformationByHandleEx(hfile.get(), FileStandardInfo, &file_info, sizeof(file_info))) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	file_size = file_info.EndOfFile;

	// File is too big for 32-bit allocation, so reject read
	if (file_size.HighPart > 0) {
		return E_FAIL;
	}

	// Need at least enough data to fill the header and magic number to be a valid DDS
	if (file_size.LowPart < (sizeof(DDS_HEADER) + sizeof(uint32_t))) {
		return E_FAIL;
	}

	// create enough space for the file data
	dds_data.reset(new (std::nothrow) uint8_t[file_size.LowPart]);
	if (!dds_data) {
		return E_OUTOFMEMORY;
	}

	// read the data in
	DWORD nb_bytes_read = 0;
	if (!ReadFile(hfile.get(), dds_data.get(), file_size.LowPart, &nb_bytes_read, nullptr)) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (nb_bytes_read < file_size.LowPart) {
		return E_FAIL;
	}

	// DDS files always start with the same magic number ("DDS ")
	uint32_t dw_magic_number = *(const uint32_t*)(dds_data.get());
	if (dw_magic_number != DDS_MAGIC) {
		return E_FAIL;
	}

	auto hdr = reinterpret_cast<DDS_HEADER*>(dds_data.get() + sizeof(uint32_t));

	// Verify header to validate DDS file
	if (hdr->size != sizeof(DDS_HEADER) || hdr->ddspf.size != sizeof(DDS_PIXELFORMAT)) {
		return E_FAIL;
	}

	// Check for DX10 extension
	bool bDXT10Header = false;
	if ((hdr->ddspf.flags & DDS_FOURCC) && (MAKEFOURCC('D', 'X', '1', '0') == hdr->ddspf.fourCC)) {
		// Must be long enough for both headers and magic value
		if (file_size.LowPart < (sizeof(DDS_HEADER) + sizeof(uint32_t) + sizeof(DDS_HEADER_DXT10))) {
			return E_FAIL;
		}

		bDXT10Header = true;
	}

	// setup the pointers in the process request
	*header = hdr;
	ptrdiff_t offset = sizeof(uint32_t) + sizeof(DDS_HEADER) + (bDXT10Header ? sizeof(DDS_HEADER_DXT10) : 0);
	*bit_data = dds_data.get() + offset;
	*bit_size = file_size.LowPart - offset;

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Get surface information for a particular format
//--------------------------------------------------------------------------------------
static void GetSurfaceInfo(_In_ size_t width,
	_In_ size_t height,
	_In_ DXGI_FORMAT fmt,
	_Out_opt_ size_t* out_nb_bytes,
	_Out_opt_ size_t* out_row_bytes,
	_Out_opt_ size_t* out_nb_rows) {
	size_t nb_bytes = 0;
	size_t nb_row_bytes = 0;
	size_t nb_rows = 0;

	bool bc = false;
	bool packed = false;
	bool planar = false;
	size_t bpe = 0;
	switch (fmt) {
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
		bc = true;
		bpe = 8;
		break;

	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
	case DXGI_FORMAT_BC6H_TYPELESS:
	case DXGI_FORMAT_BC6H_UF16:
	case DXGI_FORMAT_BC6H_SF16:
	case DXGI_FORMAT_BC7_TYPELESS:
	case DXGI_FORMAT_BC7_UNORM:
	case DXGI_FORMAT_BC7_UNORM_SRGB:
		bc = true;
		bpe = 16;
		break;

	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
	case DXGI_FORMAT_YUY2:
		packed = true;
		bpe = 4;
		break;

	case DXGI_FORMAT_Y210:
	case DXGI_FORMAT_Y216:
		packed = true;
		bpe = 8;
		break;

	case DXGI_FORMAT_NV12:
	case DXGI_FORMAT_420_OPAQUE:
		planar = true;
		bpe = 2;
		break;

	case DXGI_FORMAT_P010:
	case DXGI_FORMAT_P016:
		planar = true;
		bpe = 4;
		break;
	}

	if (bc) {
		size_t nb_blocks_wide = 0;
		if (width > 0) {
			nb_blocks_wide = std::max<size_t>(1, (width + 3) / 4);
		}
		size_t nb_blocks_high = 0;
		if (height > 0) {
			nb_blocks_high = std::max<size_t>(1, (height + 3) / 4);
		}
		nb_row_bytes = nb_blocks_wide * bpe;
		nb_rows = nb_blocks_high;
		nb_bytes = nb_row_bytes * nb_blocks_high;
	}
	else if (packed) {
		nb_row_bytes = ((width + 1) >> 1) * bpe;
		nb_rows = height;
		nb_bytes = nb_row_bytes * height;
	}
	else if (fmt == DXGI_FORMAT_NV11) {
		nb_row_bytes = ((width + 3) >> 2) * 4;
		nb_rows = height * 2; // Direct3D makes this simplifying assumption, although it is larger than the 4:1:1 data
		nb_bytes = nb_row_bytes * nb_rows;
	}
	else if (planar) {
		nb_row_bytes = ((width + 1) >> 1) * bpe;
		nb_bytes = (nb_row_bytes * height) + ((nb_row_bytes * height + 1) >> 1);
		nb_rows = height + ((height + 1) >> 1);
	}
	else {
		size_t bpp = BitsPerPixel(fmt);
		nb_row_bytes = (width * bpp + 7) / 8; // round up to nearest byte
		nb_rows = height;
		nb_bytes = nb_row_bytes * height;
	}

	if (out_nb_bytes) {
		*out_nb_bytes = nb_bytes;
	}
	if (out_row_bytes) {
		*out_row_bytes = nb_row_bytes;
	}
	if (out_nb_rows) {
		*out_nb_rows = nb_rows;
	}
}

#define ISBITMASK( r,g,b,a ) ( ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a )

static DXGI_FORMAT GetDXGIFormat(const DDS_PIXELFORMAT &ddpf) {
	if (ddpf.flags & DDS_RGB) {
		// Note that sRGB formats are written using the "DX10" extended header

		switch (ddpf.RGBBitCount) {
		case 32:
			if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)) {
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			}

			if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000)) {
				return DXGI_FORMAT_B8G8R8A8_UNORM;
			}

			if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000)) {
				return DXGI_FORMAT_B8G8R8X8_UNORM;
			}

			// No DXGI format maps to ISBITMASK(0x000000ff,0x0000ff00,0x00ff0000,0x00000000) aka D3DFMT_X8B8G8R8

			// Note that many common DDS reader/writers (including D3DX) swap the
			// the RED/BLUE masks for 10:10:10:2 formats. We assumme
			// below that the 'backwards' header mask is being used since it is most
			// likely written by D3DX. The more robust solution is to use the 'DX10'
			// header extension and specify the DXGI_FORMAT_R10G10B10A2_UNORM format directly

			// For 'correct' writers, this should be 0x000003ff,0x000ffc00,0x3ff00000 for RGB data
			if (ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000)) {
				return DXGI_FORMAT_R10G10B10A2_UNORM;
			}

			// No DXGI format maps to ISBITMASK(0x000003ff,0x000ffc00,0x3ff00000,0xc0000000) aka D3DFMT_A2R10G10B10

			if (ISBITMASK(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000)) {
				return DXGI_FORMAT_R16G16_UNORM;
			}

			if (ISBITMASK(0xffffffff, 0x00000000, 0x00000000, 0x00000000)) {
				// Only 32-bit color channel format in D3D9 was R32F
				return DXGI_FORMAT_R32_FLOAT; // D3DX writes this out as a FourCC of 114
			}
			break;

		case 24:
			// No 24bpp DXGI formats aka D3DFMT_R8G8B8
			break;

		case 16:
			if (ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x8000)) {
				return DXGI_FORMAT_B5G5R5A1_UNORM;
			}
			if (ISBITMASK(0xf800, 0x07e0, 0x001f, 0x0000)) {
				return DXGI_FORMAT_B5G6R5_UNORM;
			}

			// No DXGI format maps to ISBITMASK(0x7c00,0x03e0,0x001f,0x0000) aka D3DFMT_X1R5G5B5

			if (ISBITMASK(0x0f00, 0x00f0, 0x000f, 0xf000)) {
				return DXGI_FORMAT_B4G4R4A4_UNORM;
			}

			// No DXGI format maps to ISBITMASK(0x0f00,0x00f0,0x000f,0x0000) aka D3DFMT_X4R4G4B4

			// No 3:3:2, 3:3:2:8, or paletted DXGI formats aka D3DFMT_A8R3G3B2, D3DFMT_R3G3B2, D3DFMT_P8, D3DFMT_A8P8, etc.
			break;
		}
	}
	else if (ddpf.flags & DDS_LUMINANCE) {
		if (8 == ddpf.RGBBitCount) {
			if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x00000000)) {
				return DXGI_FORMAT_R8_UNORM; // D3DX10/11 writes this out as DX10 extension
			}

			// No DXGI format maps to ISBITMASK(0x0f,0x00,0x00,0xf0) aka D3DFMT_A4L4
		}

		if (16 == ddpf.RGBBitCount) {
			if (ISBITMASK(0x0000ffff, 0x00000000, 0x00000000, 0x00000000)) {
				return DXGI_FORMAT_R16_UNORM; // D3DX10/11 writes this out as DX10 extension
			}
			if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00)) {
				return DXGI_FORMAT_R8G8_UNORM; // D3DX10/11 writes this out as DX10 extension
			}
		}
	}
	else if (ddpf.flags & DDS_ALPHA) {
		if (8 == ddpf.RGBBitCount) {
			return DXGI_FORMAT_A8_UNORM;
		}
	}
	else if (ddpf.flags & DDS_FOURCC) {
		if (MAKEFOURCC('D', 'X', 'T', '1') == ddpf.fourCC) {
			return DXGI_FORMAT_BC1_UNORM;
		}
		if (MAKEFOURCC('D', 'X', 'T', '3') == ddpf.fourCC) {
			return DXGI_FORMAT_BC2_UNORM;
		}
		if (MAKEFOURCC('D', 'X', 'T', '5') == ddpf.fourCC) {
			return DXGI_FORMAT_BC3_UNORM;
		}

		// While pre-mulitplied alpha isn't directly supported by the DXGI formats,
		// they are basically the same as these BC formats so they can be mapped
		if (MAKEFOURCC('D', 'X', 'T', '2') == ddpf.fourCC) {
			return DXGI_FORMAT_BC2_UNORM;
		}
		if (MAKEFOURCC('D', 'X', 'T', '4') == ddpf.fourCC) {
			return DXGI_FORMAT_BC3_UNORM;
		}

		if (MAKEFOURCC('A', 'T', 'I', '1') == ddpf.fourCC) {
			return DXGI_FORMAT_BC4_UNORM;
		}
		if (MAKEFOURCC('B', 'C', '4', 'U') == ddpf.fourCC) {
			return DXGI_FORMAT_BC4_UNORM;
		}
		if (MAKEFOURCC('B', 'C', '4', 'S') == ddpf.fourCC) {
			return DXGI_FORMAT_BC4_SNORM;
		}

		if (MAKEFOURCC('A', 'T', 'I', '2') == ddpf.fourCC) {
			return DXGI_FORMAT_BC5_UNORM;
		}
		if (MAKEFOURCC('B', 'C', '5', 'U') == ddpf.fourCC) {
			return DXGI_FORMAT_BC5_UNORM;
		}
		if (MAKEFOURCC('B', 'C', '5', 'S') == ddpf.fourCC) {
			return DXGI_FORMAT_BC5_SNORM;
		}

		// BC6H and BC7 are written using the "DX10" extended header

		if (MAKEFOURCC('R', 'G', 'B', 'G') == ddpf.fourCC) {
			return DXGI_FORMAT_R8G8_B8G8_UNORM;
		}
		if (MAKEFOURCC('G', 'R', 'G', 'B') == ddpf.fourCC) {
			return DXGI_FORMAT_G8R8_G8B8_UNORM;
		}

		if (MAKEFOURCC('Y', 'U', 'Y', '2') == ddpf.fourCC) {
			return DXGI_FORMAT_YUY2;
		}

		// Check for D3DFORMAT enums being set here
		switch (ddpf.fourCC) {
		case 36: // D3DFMT_A16B16G16R16
			return DXGI_FORMAT_R16G16B16A16_UNORM;
		case 110: // D3DFMT_Q16W16V16U16
			return DXGI_FORMAT_R16G16B16A16_SNORM;
		case 111: // D3DFMT_R16F
			return DXGI_FORMAT_R16_FLOAT;
		case 112: // D3DFMT_G16R16F
			return DXGI_FORMAT_R16G16_FLOAT;
		case 113: // D3DFMT_A16B16G16R16F
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case 114: // D3DFMT_R32F
			return DXGI_FORMAT_R32_FLOAT;
		case 115: // D3DFMT_G32R32F
			return DXGI_FORMAT_R32G32_FLOAT;
		case 116: // D3DFMT_A32B32G32R32F
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

static DXGI_FORMAT MakeSRGB(_In_ DXGI_FORMAT format) {
	switch (format) {
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	case DXGI_FORMAT_BC1_UNORM:
		return DXGI_FORMAT_BC1_UNORM_SRGB;
	case DXGI_FORMAT_BC2_UNORM:
		return DXGI_FORMAT_BC2_UNORM_SRGB;
	case DXGI_FORMAT_BC3_UNORM:
		return DXGI_FORMAT_BC3_UNORM_SRGB;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
	case DXGI_FORMAT_BC7_UNORM:
		return DXGI_FORMAT_BC7_UNORM_SRGB;
	default:
		return format;
	}
}

static HRESULT FillInitData(_In_ size_t width,
	_In_ size_t height,
	_In_ size_t depth,
	_In_ size_t mip_count,
	_In_ size_t array_size,
	_In_ DXGI_FORMAT format,
	_In_ size_t maxsize,
	_In_ size_t bit_size,
	_In_reads_bytes_(bit_size) const uint8_t *bit_data,
	_Out_ size_t &twidth,
	_Out_ size_t &theight,
	_Out_ size_t &tdepth,
	_Out_ size_t &skip_mip,
	_Out_writes_(mip_count*array_size) D3D11_SUBRESOURCE_DATA *init_data) {
	
	if (!bit_data || !init_data) {
		return E_POINTER;
	}

	skip_mip = 0;
	twidth = 0;
	theight = 0;
	tdepth = 0;

	size_t nb_bytes = 0;
	size_t row_bytes = 0;
	const uint8_t* src_bits = bit_data;
	const uint8_t* end_bits = bit_data + bit_size;

	size_t index = 0;
	for (size_t j = 0; j < array_size; ++j) {
		size_t w = width;
		size_t h = height;
		size_t d = depth;
		for (size_t i = 0; i < mip_count; ++i) {
			GetSurfaceInfo(w, h, format, &nb_bytes, &row_bytes, nullptr);

			if ((mip_count <= 1) || !maxsize || (w <= maxsize && h <= maxsize && d <= maxsize)) {
				if (!twidth) {
					twidth  = w;
					theight = h;
					tdepth  = d;
				}

				Assert(index < mip_count * array_size);
				_Analysis_assume_(index < mip_count * array_size);
				init_data[index].pSysMem = (const void*)src_bits;
				init_data[index].SysMemPitch = static_cast<UINT>(row_bytes);
				init_data[index].SysMemSlicePitch = static_cast<UINT>(nb_bytes);
				++index;
			}
			else if (!j) {
				// Count number of skipped mipmaps (first item only)
				++skip_mip;
			}

			if (src_bits + (nb_bytes*d) > end_bits) {
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
			}

			src_bits += nb_bytes * d;

			w = w >> 1;
			h = h >> 1;
			d = d >> 1;
			if (w == 0) {
				w = 1;
			}
			if (h == 0) {
				h = 1;
			}
			if (d == 0) {
				d = 1;
			}
		}
	}

	return (index > 0) ? S_OK : E_FAIL;
}

static HRESULT CreateD3DResources(_In_ ID3D11Device2 *device,
	_In_ uint32_t res_dim,
	_In_ size_t width,
	_In_ size_t height,
	_In_ size_t depth,
	_In_ size_t mip_count,
	_In_ size_t array_size,
	_In_ DXGI_FORMAT format,
	_In_ D3D11_USAGE usage,
	_In_ uint32_t bindFlags,
	_In_ uint32_t cpu_access_flags,
	_In_ uint32_t misc_flags,
	_In_ bool forceSRGB,
	_In_ bool is_cube_map,
	_In_reads_opt_(mip_count*array_size) D3D11_SUBRESOURCE_DATA *init_data,
	_Outptr_opt_ ID3D11Resource **texture,
	_Outptr_opt_ ID3D11ShaderResourceView **texture_view) {
	
	if (!device) {
		return E_POINTER;
	}

	HRESULT hr = E_FAIL;

	if (forceSRGB) {
		format = MakeSRGB(format);
	}

	switch (res_dim) {
	case D3D11_RESOURCE_DIMENSION_TEXTURE1D: {
		D3D11_TEXTURE1D_DESC desc;
		desc.Width = static_cast<UINT>(width);
		desc.MipLevels = static_cast<UINT>(mip_count);
		desc.ArraySize = static_cast<UINT>(array_size);
		desc.Format = format;
		desc.Usage = usage;
		desc.BindFlags = bindFlags;
		desc.CPUAccessFlags = cpu_access_flags;
		desc.MiscFlags = misc_flags & ~D3D11_RESOURCE_MISC_TEXTURECUBE;

		ID3D11Texture1D* tex = nullptr;
		hr = device->CreateTexture1D(&desc, init_data, &tex);
		if (SUCCEEDED(hr) && tex != 0) {
			if (texture_view != 0) {
				D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view;
				memset(&shader_resource_view, 0, sizeof(shader_resource_view));
				shader_resource_view.Format = format;

				if (array_size > 1) {
					shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
					shader_resource_view.Texture1DArray.MipLevels = (!mip_count) ? -1 : desc.MipLevels;
					shader_resource_view.Texture1DArray.ArraySize = static_cast<UINT>(array_size);
				}
				else {
					shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
					shader_resource_view.Texture1D.MipLevels = (!mip_count) ? -1 : desc.MipLevels;
				}

				hr = device->CreateShaderResourceView(tex, &shader_resource_view, texture_view);
				if (FAILED(hr)) {
					tex->Release();
					return hr;
				}
			}

			if (texture != 0) {
				*texture = tex;
			}
			else {
				SetDebugObjectName(tex, "DDSTextureLoader");
				tex->Release();
			}
		}
	}
	break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE2D: {
		D3D11_TEXTURE2D_DESC desc;
		desc.Width = static_cast<UINT>(width);
		desc.Height = static_cast<UINT>(height);
		desc.MipLevels = static_cast<UINT>(mip_count);
		desc.ArraySize = static_cast<UINT>(array_size);
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = usage;
		desc.BindFlags = bindFlags;
		desc.CPUAccessFlags = cpu_access_flags;
		if (is_cube_map) {
			desc.MiscFlags = misc_flags | D3D11_RESOURCE_MISC_TEXTURECUBE;
		}
		else {
			desc.MiscFlags = misc_flags & ~D3D11_RESOURCE_MISC_TEXTURECUBE;
		}

		ID3D11Texture2D *tex = nullptr;
		hr = device->CreateTexture2D(&desc, init_data, &tex);
		if (SUCCEEDED(hr) && tex != 0) {
			if (texture_view != 0) {
				D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view;
				memset(&shader_resource_view, 0, sizeof(shader_resource_view));
				shader_resource_view.Format = format;

				if (is_cube_map) {
					if (array_size > 6) {
						shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
						shader_resource_view.TextureCubeArray.MipLevels = (!mip_count) ? -1 : desc.MipLevels;

						// Earlier we set array_size to (NumCubes * 6)
						shader_resource_view.TextureCubeArray.NumCubes = static_cast<UINT>(array_size / 6);
					}
					else {
						shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
						shader_resource_view.TextureCube.MipLevels = (!mip_count) ? -1 : desc.MipLevels;
					}
				}
				else if (array_size > 1) {
					shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
					shader_resource_view.Texture2DArray.MipLevels = (!mip_count) ? -1 : desc.MipLevels;
					shader_resource_view.Texture2DArray.ArraySize = static_cast<UINT>(array_size);
				}
				else {
					shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					shader_resource_view.Texture2D.MipLevels = (!mip_count) ? -1 : desc.MipLevels;
				}

				hr = device->CreateShaderResourceView(tex, &shader_resource_view,texture_view);
				if (FAILED(hr)) {
					tex->Release();
					return hr;
				}
			}

			if (texture != 0)
			{
				*texture = tex;
			}
			else
			{
				SetDebugObjectName(tex, "DDSTextureLoader");
				tex->Release();
			}
		}
	}
	break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE3D: {
		D3D11_TEXTURE3D_DESC desc;
		desc.Width = static_cast<UINT>(width);
		desc.Height = static_cast<UINT>(height);
		desc.Depth = static_cast<UINT>(depth);
		desc.MipLevels = static_cast<UINT>(mip_count);
		desc.Format = format;
		desc.Usage = usage;
		desc.BindFlags = bindFlags;
		desc.CPUAccessFlags = cpu_access_flags;
		desc.MiscFlags = misc_flags & ~D3D11_RESOURCE_MISC_TEXTURECUBE;

		ID3D11Texture3D *tex = nullptr;
		hr = device->CreateTexture3D(&desc, init_data, &tex);
		if (SUCCEEDED(hr) && tex != 0) {
			if (texture_view != 0) {
				D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view;
				memset(&shader_resource_view, 0, sizeof(shader_resource_view));
				shader_resource_view.Format = format;

				shader_resource_view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
				shader_resource_view.Texture3D.MipLevels = (!mip_count) ? -1 : desc.MipLevels;

				hr = device->CreateShaderResourceView(tex, &shader_resource_view, texture_view);
				if (FAILED(hr)) {
					tex->Release();
					return hr;
				}
			}

			if (texture != 0) {
				*texture = tex;
			}
			else {
				SetDebugObjectName(tex, "DDSTextureLoader");
				tex->Release();
			}
		}
	}
	break;
	}

	return hr;
}

static HRESULT CreateTextureFromDDS(_In_ ID3D11Device2 *device,
	_In_opt_ ID3D11DeviceContext *device_context,
	_In_ const DDS_HEADER *header,
	_In_reads_bytes_(bit_size) const uint8_t *bit_data,
	_In_ size_t bit_size,
	_In_ size_t maxsize,
	_In_ D3D11_USAGE usage,
	_In_ uint32_t bindFlags,
	_In_ uint32_t cpu_access_flags,
	_In_ uint32_t misc_flags,
	_In_ bool forceSRGB,
	_Outptr_opt_ ID3D11Resource **texture,
	_Outptr_opt_ ID3D11ShaderResourceView **texture_view) {
		
	HRESULT hr = S_OK;

	size_t width = header->width;
	size_t height = header->height;
	size_t depth = header->depth;

	uint32_t res_dim = D3D11_RESOURCE_DIMENSION_UNKNOWN;
	size_t array_size = 1;
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
	bool is_cube_map = false;

	size_t mip_count = header->mip_map_count;
	if (0 == mip_count) {
		mip_count = 1;
	}

	if ((header->ddspf.flags & DDS_FOURCC) && (MAKEFOURCC('D', 'X', '1', '0') == header->ddspf.fourCC)) {
		auto d3d10ext = reinterpret_cast<const DDS_HEADER_DXT10*>((const char*)header + sizeof(DDS_HEADER));

		array_size = d3d10ext->array_size;
		if (array_size == 0) {
			return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
		}

		switch (d3d10ext->dxgi_format) {
		case DXGI_FORMAT_AI44:
		case DXGI_FORMAT_IA44:
		case DXGI_FORMAT_P8:
		case DXGI_FORMAT_A8P8:
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);

		default:
			if (BitsPerPixel(d3d10ext->dxgi_format) == 0) {
				return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
			}
		}

		format = d3d10ext->dxgi_format;

		switch (d3d10ext->resource_dimension) {
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			// D3DX writes 1D textures with a fixed Height of 1
			if ((header->flags & DDS_HEIGHT) && height != 1) {
				return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
			}
			height = depth = 1;
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			if (d3d10ext->misc_flag & D3D11_RESOURCE_MISC_TEXTURECUBE) {
				array_size *= 6;
				is_cube_map = true;
			}
			depth = 1;
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			if (!(header->flags & DDS_HEADER_FLAGS_VOLUME)) {
				return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
			}

			if (array_size > 1) {
				return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
			}
			break;

		default:
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
		}

		res_dim = d3d10ext->resource_dimension;
	}
	else {
		format = GetDXGIFormat(header->ddspf);

		if (format == DXGI_FORMAT_UNKNOWN) {
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
		}

		if (header->flags & DDS_HEADER_FLAGS_VOLUME) {
			res_dim = D3D11_RESOURCE_DIMENSION_TEXTURE3D;
		}
		else {
			if (header->caps2 & DDS_CUBEMAP) {
				// We require all six faces to be defined
				if ((header->caps2 & DDS_CUBEMAP_ALLFACES) != DDS_CUBEMAP_ALLFACES) {
					return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
				}

				array_size = 6;
				is_cube_map = true;
			}

			depth = 1;
			res_dim = D3D11_RESOURCE_DIMENSION_TEXTURE2D;

			// Note there's no way for a legacy Direct3D 9 DDS to express a '1D' texture
		}

		Assert(BitsPerPixel(format) != 0);
	}

	// Bound sizes (for security purposes we don't trust DDS file metadata larger than the D3D 11.x hardware requirements)
	if (mip_count > D3D11_REQ_MIP_LEVELS) {
		return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
	}

	switch (res_dim) {
	case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
		if ((array_size > D3D11_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION) || (width > D3D11_REQ_TEXTURE1D_U_DIMENSION)) {
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
		}
		break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
		if (is_cube_map) {
			// This is the right bound because we set array_size to (NumCubes*6) above
			if ((array_size > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
				(width > D3D11_REQ_TEXTURECUBE_DIMENSION) ||
				(height > D3D11_REQ_TEXTURECUBE_DIMENSION)) {
				return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
			}
		}
		else if ((array_size > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
				 (width > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION) ||
				 (height > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)) {
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
		}
		break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
		if ((array_size > 1) ||
			(width > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
			(height > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
			(depth > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION)) {
			return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
		}
		break;
	}

	bool autogen = false;
	if (mip_count == 1 && device_context != 0 && texture_view != 0) {// Must have context and shader-view to auto generate mipmaps
		// See if format is supported for auto-gen mipmaps (varies by feature level)
		UINT fmtSupport = 0;
		hr = device->CheckFormatSupport(format, &fmtSupport);
		if (SUCCEEDED(hr) && (fmtSupport & D3D11_FORMAT_SUPPORT_MIP_AUTOGEN)) {
			// 10level9 feature levels do not support auto-gen mipgen for volume textures
			if ((res_dim != D3D11_RESOURCE_DIMENSION_TEXTURE3D) || (device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_10_0)) {
				autogen = true;
			}
		}
	}

	if (autogen) {
		// Create texture with auto-generated mipmaps
		ID3D11Resource *tex = nullptr;
		hr = CreateD3DResources(device, res_dim, width, height, depth, 0, array_size,
			format, usage,
			bindFlags | D3D11_BIND_RENDER_TARGET,
			cpu_access_flags,
			misc_flags | D3D11_RESOURCE_MISC_GENERATE_MIPS, forceSRGB,
			is_cube_map, nullptr, &tex, texture_view);
		if (SUCCEEDED(hr)) {
			size_t nb_bytes = 0;
			size_t nb_row_bytes = 0;
			GetSurfaceInfo(width, height, format, &nb_bytes, &nb_row_bytes, nullptr);

			if (nb_bytes > bit_size) {
				(*texture_view)->Release();
				*texture_view = nullptr;
				tex->Release();
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
			}

			if (array_size > 1) {
				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				(*texture_view)->GetDesc(&desc);

				UINT mipLevels = 1;

				switch (desc.ViewDimension) {
				case D3D_SRV_DIMENSION_TEXTURE1D:       mipLevels = desc.Texture1D.MipLevels; break;
				case D3D_SRV_DIMENSION_TEXTURE1DARRAY:  mipLevels = desc.Texture1DArray.MipLevels; break;
				case D3D_SRV_DIMENSION_TEXTURE2D:       mipLevels = desc.Texture2D.MipLevels; break;
				case D3D_SRV_DIMENSION_TEXTURE2DARRAY:  mipLevels = desc.Texture2DArray.MipLevels; break;
				case D3D_SRV_DIMENSION_TEXTURECUBE:     mipLevels = desc.TextureCube.MipLevels; break;
				case D3D_SRV_DIMENSION_TEXTURECUBEARRAY:mipLevels = desc.TextureCubeArray.MipLevels; break;
				default:
					(*texture_view)->Release();
					*texture_view = nullptr;
					tex->Release();
					return E_UNEXPECTED;
				}

				const uint8_t* src_bits = bit_data;
				const uint8_t* end_bits = bit_data + bit_size;
				for (UINT item = 0; item < array_size; ++item) {
					if ((src_bits + nb_bytes) > end_bits) {
						(*texture_view)->Release();
						*texture_view = nullptr;
						tex->Release();
						return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
					}

					UINT res = D3D11CalcSubresource(0, item, mipLevels);
					device_context->UpdateSubresource(tex, res, nullptr, src_bits, static_cast<UINT>(nb_row_bytes), static_cast<UINT>(nb_bytes));
					src_bits += nb_bytes;
				}
			}
			else {
				device_context->UpdateSubresource(tex, 0, nullptr, bit_data, static_cast<UINT>(nb_row_bytes), static_cast<UINT>(nb_bytes));
			}

			device_context->GenerateMips(*texture_view);

			if (texture) {
				*texture = tex;
			}
			else {
				tex->Release();
			}
		}
	}
	else {
		// Create the texture
		std::unique_ptr<D3D11_SUBRESOURCE_DATA[]> init_data(new (std::nothrow) D3D11_SUBRESOURCE_DATA[mip_count * array_size]);
		if (!init_data) {
			return E_OUTOFMEMORY;
		}

		size_t skip_mip = 0;
		size_t twidth = 0;
		size_t theight = 0;
		size_t tdepth = 0;
		hr = FillInitData(width, height, depth, mip_count, array_size, format, maxsize, bit_size, bit_data,
							twidth, theight, tdepth, skip_mip, init_data.get());

		if (SUCCEEDED(hr)) {
			hr = CreateD3DResources(device, res_dim, twidth, theight, tdepth, mip_count - skip_mip, array_size,
									format, usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB,
									is_cube_map, init_data.get(), texture, texture_view);

			if (FAILED(hr) && !maxsize && (mip_count > 1)) {
				// Retry with a maxsize determined by feature level
				switch (device->GetFeatureLevel()) {
				case D3D_FEATURE_LEVEL_9_1:
				case D3D_FEATURE_LEVEL_9_2:
					if (is_cube_map) {
						maxsize = 512 /*D3D_FL9_1_REQ_TEXTURECUBE_DIMENSION*/;
					}
					else {
						maxsize = (res_dim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
							? 256 /*D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION*/
							: 2048 /*D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
					}
					break;

				case D3D_FEATURE_LEVEL_9_3:
					maxsize = (res_dim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
						? 256 /*D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION*/
						: 4096 /*D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
					break;

				default: // D3D_FEATURE_LEVEL_10_0 & D3D_FEATURE_LEVEL_10_1
					maxsize = (res_dim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
						? 2048 /*D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION*/
						: 8192 /*D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
					break;
				}

				hr = FillInitData(width, height, depth, mip_count, array_size, format, maxsize, bit_size, bit_data,
									twidth, theight, tdepth, skip_mip, init_data.get());
				if (SUCCEEDED(hr)) {
					hr = CreateD3DResources(device, res_dim, twidth, theight, tdepth, mip_count - skip_mip, array_size,
											format, usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB,
											is_cube_map, init_data.get(), texture, texture_view);
				}
			}
		}
	}

	return hr;
}

static DDS_ALPHA_MODE GetAlphaMode(_In_ const DDS_HEADER *header) {
	if (header->ddspf.flags & DDS_FOURCC) {
		if (MAKEFOURCC('D', 'X', '1', '0') == header->ddspf.fourCC) {
			auto d3d10ext = reinterpret_cast<const DDS_HEADER_DXT10*>((const char*)header + sizeof(DDS_HEADER));
			auto mode = static_cast<DDS_ALPHA_MODE>(d3d10ext->misc_flags2 & DDS_MISC_FLAGS2_ALPHA_MODE_MASK);
			switch (mode) {
			case DDS_ALPHA_MODE_STRAIGHT:
			case DDS_ALPHA_MODE_PREMULTIPLIED:
			case DDS_ALPHA_MODE_OPAQUE:
			case DDS_ALPHA_MODE_CUSTOM:
				return mode;
			}
		}
		else if ((MAKEFOURCC('D', 'X', 'T', '2') == header->ddspf.fourCC)
			  || (MAKEFOURCC('D', 'X', 'T', '4') == header->ddspf.fourCC)) {
			return DDS_ALPHA_MODE_PREMULTIPLIED;
		}
	}

	return DDS_ALPHA_MODE_UNKNOWN;
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromMemory(ID3D11Device2 *device,
	const uint8_t *dds_data,
	size_t dds_dataSize,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	size_t maxsize,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromMemoryEx(device, nullptr, dds_data, dds_dataSize, maxsize,
										D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromMemory(ID3D11Device2 *device,
	ID3D11DeviceContext *device_context,
	const uint8_t *dds_data,
	size_t dds_dataSize,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	size_t maxsize,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromMemoryEx(device, device_context, dds_data, dds_dataSize, maxsize,
										D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromMemoryEx(ID3D11Device2 *device,
	const uint8_t *dds_data,
	size_t dds_dataSize,
	size_t maxsize,
	D3D11_USAGE usage,
	uint32_t bindFlags,
	uint32_t cpu_access_flags,
	uint32_t misc_flags,
	bool forceSRGB,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromMemoryEx(device, nullptr, dds_data, dds_dataSize, maxsize,
										usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromMemoryEx(ID3D11Device2 *device,
	ID3D11DeviceContext *device_context,
	const uint8_t *dds_data,
	size_t dds_dataSize,
	size_t maxsize,
	D3D11_USAGE usage,
	uint32_t bindFlags,
	uint32_t cpu_access_flags,
	uint32_t misc_flags,
	bool forceSRGB,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	DDS_ALPHA_MODE *alpha_mode) {
   
	if (texture) {
		*texture = nullptr;
	}
	if (texture_view) {
		*texture_view = nullptr;
	}
	if (alpha_mode) {
		*alpha_mode = DDS_ALPHA_MODE_UNKNOWN;
	}

	if (!device || !dds_data || (!texture && !texture_view)) {
		return E_INVALIDARG;
	}

	// Validate DDS file in memory
	if (dds_dataSize < (sizeof(uint32_t) + sizeof(DDS_HEADER))) {
		return E_FAIL;
	}

	uint32_t dw_magic_number = *(const uint32_t*)(dds_data);
	if (dw_magic_number != DDS_MAGIC) {
		return E_FAIL;
	}

	auto header = reinterpret_cast<const DDS_HEADER*>(dds_data + sizeof(uint32_t));

	// Verify header to validate DDS file
	if (header->size != sizeof(DDS_HEADER) || header->ddspf.size != sizeof(DDS_PIXELFORMAT)) {
		return E_FAIL;
	}

	// Check for DX10 extension
	bool bDXT10Header = false;
	if ((header->ddspf.flags & DDS_FOURCC) && (MAKEFOURCC('D', 'X', '1', '0') == header->ddspf.fourCC)) {
		// Must be long enough for both headers and magic value
		if (dds_dataSize < (sizeof(DDS_HEADER) + sizeof(uint32_t) + sizeof(DDS_HEADER_DXT10))) {
			return E_FAIL;
		}

		bDXT10Header = true;
	}

	ptrdiff_t offset = sizeof(uint32_t) + sizeof(DDS_HEADER) + (bDXT10Header ? sizeof(DDS_HEADER_DXT10) : 0);

	HRESULT hr = CreateTextureFromDDS(device, device_context, header,
										dds_data + offset, dds_dataSize - offset, maxsize,
										usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB,
										texture, texture_view);
	if (SUCCEEDED(hr)) {
		if (texture != 0 && *texture != 0) {
			SetDebugObjectName(*texture, "DDSTextureLoader");
		}

		if (texture_view != 0 && *texture_view != 0) {
			SetDebugObjectName(*texture_view, "DDSTextureLoader");
		}

		if (alpha_mode) {
			*alpha_mode = GetAlphaMode(header);
		}
	}

	return hr;
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromFile(ID3D11Device2 *device,
	const wchar_t *file_name,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	size_t maxsize,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromFileEx(device, nullptr, file_name, maxsize,
										D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromFile(ID3D11Device2 *device,
	ID3D11DeviceContext *device_context,
	const wchar_t *file_name,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	size_t maxsize,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromFileEx(device, device_context, file_name, maxsize,
										D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromFileEx(ID3D11Device2 *device,
	const wchar_t *file_name,
	size_t maxsize,
	D3D11_USAGE usage,
	uint32_t bindFlags,
	uint32_t cpu_access_flags,
	uint32_t misc_flags,
	bool forceSRGB,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	DDS_ALPHA_MODE *alpha_mode) {
	return CreateDDSTextureFromFileEx(device, nullptr, file_name, maxsize,
										usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB,
										texture, texture_view, alpha_mode);
}

_Use_decl_annotations_
HRESULT CreateDDSTextureFromFileEx(ID3D11Device2 *device,
	ID3D11DeviceContext *device_context,
	const wchar_t *file_name,
	size_t maxsize,
	D3D11_USAGE usage,
	uint32_t bindFlags,
	uint32_t cpu_access_flags,
	uint32_t misc_flags,
	bool forceSRGB,
	ID3D11Resource **texture,
	ID3D11ShaderResourceView **texture_view,
	DDS_ALPHA_MODE *alpha_mode) {
	
	if (texture) {
		*texture = nullptr;
	}
	if (texture_view) {
		*texture_view = nullptr;
	}
	if (alpha_mode) {
		*alpha_mode = DDS_ALPHA_MODE_UNKNOWN;
	}

	if (!device || !file_name || (!texture && !texture_view)) {
		return E_INVALIDARG;
	}

	DDS_HEADER* header = nullptr;
	uint8_t* bit_data = nullptr;
	size_t bit_size = 0;

	std::unique_ptr<uint8_t[]> dds_data;
	HRESULT hr = LoadTextureDataFromFile(file_name, dds_data, &header, &bit_data, &bit_size);
	if (FAILED(hr)) {
		return hr;
	}

	hr = CreateTextureFromDDS(device, device_context, header, bit_data, bit_size, maxsize, usage, bindFlags, cpu_access_flags, misc_flags, forceSRGB, texture, texture_view);

	if (SUCCEEDED(hr)) {
#if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
		if (texture != 0 || texture_view != 0) {
			CHAR strFileA[MAX_PATH];
			int result = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, file_name, -1, strFileA, MAX_PATH, nullptr, FALSE);

			if (result > 0) {
				const CHAR* pstrName = strrchr(strFileA, '\\');
				if (!pstrName) {
					pstrName = strFileA;
				}
				else {
					++pstrName;
				}

				if (texture != 0 && *texture != 0) {
					(*texture)->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(strnlen_s(pstrName, MAX_PATH)), pstrName);
				}
				if (texture_view != 0 && *texture_view != 0) {
					(*texture_view)->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(strnlen_s(pstrName, MAX_PATH)), pstrName);
				}
			}
		}
#endif
		if (alpha_mode) {
			*alpha_mode = GetAlphaMode(header);
		}
	}

	return hr;
}
}