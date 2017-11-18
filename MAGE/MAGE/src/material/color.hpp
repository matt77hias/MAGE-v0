#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

namespace mage::color {

    extern const __declspec(selectany) SRGB AliceBlue            = { 0.941176534f, 0.972549081f, 1.000000000f };
    extern const __declspec(selectany) SRGB AntiqueWhite         = { 0.980392218f, 0.921568692f, 0.843137324f };
    extern const __declspec(selectany) SRGB Aqua                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB Aquamarine           = { 0.498039246f, 1.000000000f, 0.831372619f };
    extern const __declspec(selectany) SRGB Azure                = { 0.941176534f, 1.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB Beige                = { 0.960784376f, 0.960784376f, 0.862745166f };
    extern const __declspec(selectany) SRGB Bisque               = { 1.000000000f, 0.894117713f, 0.768627524f };
    extern const __declspec(selectany) SRGB Black                = { 0.000000000f, 0.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB BlanchedAlmond       = { 1.000000000f, 0.921568692f, 0.803921640f };
    extern const __declspec(selectany) SRGB Blue                 = { 0.000000000f, 0.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB BlueViolet           = { 0.541176498f, 0.168627456f, 0.886274576f };
    extern const __declspec(selectany) SRGB Brown                = { 0.647058845f, 0.164705887f, 0.164705887f };
    extern const __declspec(selectany) SRGB BurlyWood            = { 0.870588303f, 0.721568644f, 0.529411793f };
    extern const __declspec(selectany) SRGB CadetBlue            = { 0.372549027f, 0.619607866f, 0.627451003f };
    extern const __declspec(selectany) SRGB Chartreuse           = { 0.498039246f, 1.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB Chocolate            = { 0.823529482f, 0.411764741f, 0.117647067f };
    extern const __declspec(selectany) SRGB Coral                = { 1.000000000f, 0.498039246f, 0.313725501f };
    extern const __declspec(selectany) SRGB CornflowerBlue       = { 0.392156899f, 0.584313750f, 0.929411829f };
    extern const __declspec(selectany) SRGB Cornsilk             = { 1.000000000f, 0.972549081f, 0.862745166f };
    extern const __declspec(selectany) SRGB Crimson              = { 0.862745166f, 0.078431375f, 0.235294133f };
    extern const __declspec(selectany) SRGB Cyan                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB DarkBlue             = { 0.000000000f, 0.000000000f, 0.545098066f };
    extern const __declspec(selectany) SRGB DarkCyan             = { 0.000000000f, 0.545098066f, 0.545098066f };
    extern const __declspec(selectany) SRGB DarkGoldenrod        = { 0.721568644f, 0.525490224f, 0.043137256f };
    extern const __declspec(selectany) SRGB DarkGray             = { 0.662745118f, 0.662745118f, 0.662745118f };
    extern const __declspec(selectany) SRGB DarkGreen            = { 0.000000000f, 0.392156899f, 0.000000000f };
    extern const __declspec(selectany) SRGB DarkKhaki            = { 0.741176486f, 0.717647076f, 0.419607878f };
    extern const __declspec(selectany) SRGB DarkMagenta          = { 0.545098066f, 0.000000000f, 0.545098066f };
    extern const __declspec(selectany) SRGB DarkOliveGreen       = { 0.333333343f, 0.419607878f, 0.184313729f };
    extern const __declspec(selectany) SRGB DarkOrange           = { 1.000000000f, 0.549019635f, 0.000000000f };
    extern const __declspec(selectany) SRGB DarkOrchid           = { 0.600000024f, 0.196078449f, 0.800000072f };
    extern const __declspec(selectany) SRGB DarkRed              = { 0.545098066f, 0.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB DarkSalmon           = { 0.913725555f, 0.588235319f, 0.478431404f };
    extern const __declspec(selectany) SRGB DarkSeaGreen         = { 0.560784340f, 0.737254918f, 0.545098066f };
    extern const __declspec(selectany) SRGB DarkSlateBlue        = { 0.282352954f, 0.239215702f, 0.545098066f };
    extern const __declspec(selectany) SRGB DarkSlateGray        = { 0.184313729f, 0.309803933f, 0.309803933f };
    extern const __declspec(selectany) SRGB DarkTurquoise        = { 0.000000000f, 0.807843208f, 0.819607913f };
    extern const __declspec(selectany) SRGB DarkViolet           = { 0.580392182f, 0.000000000f, 0.827451050f };
    extern const __declspec(selectany) SRGB DeepPink             = { 1.000000000f, 0.078431375f, 0.576470613f };
    extern const __declspec(selectany) SRGB DeepSkyBlue          = { 0.000000000f, 0.749019623f, 1.000000000f };
    extern const __declspec(selectany) SRGB DimGray              = { 0.411764741f, 0.411764741f, 0.411764741f };
    extern const __declspec(selectany) SRGB DodgerBlue           = { 0.117647067f, 0.564705908f, 1.000000000f };
    extern const __declspec(selectany) SRGB Firebrick            = { 0.698039234f, 0.133333340f, 0.133333340f };
    extern const __declspec(selectany) SRGB FloralWhite          = { 1.000000000f, 0.980392218f, 0.941176534f };
    extern const __declspec(selectany) SRGB ForestGreen          = { 0.133333340f, 0.545098066f, 0.133333340f };
    extern const __declspec(selectany) SRGB Fuchsia              = { 1.000000000f, 0.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB Gainsboro            = { 0.862745166f, 0.862745166f, 0.862745166f };
    extern const __declspec(selectany) SRGB GhostWhite           = { 0.972549081f, 0.972549081f, 1.000000000f };
    extern const __declspec(selectany) SRGB Gold                 = { 1.000000000f, 0.843137324f, 0.000000000f };
    extern const __declspec(selectany) SRGB Goldenrod            = { 0.854902029f, 0.647058845f, 0.125490203f };
    extern const __declspec(selectany) SRGB Gray                 = { 0.501960814f, 0.501960814f, 0.501960814f };
    extern const __declspec(selectany) SRGB Green                = { 0.000000000f, 0.501960814f, 0.000000000f };
    extern const __declspec(selectany) SRGB GreenYellow          = { 0.678431392f, 1.000000000f, 0.184313729f };
    extern const __declspec(selectany) SRGB Honeydew             = { 0.941176534f, 1.000000000f, 0.941176534f };
    extern const __declspec(selectany) SRGB HotPink              = { 1.000000000f, 0.411764741f, 0.705882370f };
    extern const __declspec(selectany) SRGB IndianRed            = { 0.803921640f, 0.360784322f, 0.360784322f };
    extern const __declspec(selectany) SRGB Indigo               = { 0.294117659f, 0.000000000f, 0.509803951f };
    extern const __declspec(selectany) SRGB Ivory                = { 1.000000000f, 1.000000000f, 0.941176534f };
    extern const __declspec(selectany) SRGB Khaki                = { 0.941176534f, 0.901960850f, 0.549019635f };
    extern const __declspec(selectany) SRGB Lavender             = { 0.901960850f, 0.901960850f, 0.980392218f };
    extern const __declspec(selectany) SRGB LavenderBlush        = { 1.000000000f, 0.941176534f, 0.960784376f };
    extern const __declspec(selectany) SRGB LawnGreen            = { 0.486274540f, 0.988235354f, 0.000000000f };
    extern const __declspec(selectany) SRGB LemonChiffon         = { 1.000000000f, 0.980392218f, 0.803921640f };
    extern const __declspec(selectany) SRGB LightBlue            = { 0.678431392f, 0.847058892f, 0.901960850f };
    extern const __declspec(selectany) SRGB LightCoral           = { 0.941176534f, 0.501960814f, 0.501960814f };
    extern const __declspec(selectany) SRGB LightCyan            = { 0.878431439f, 1.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f };
    extern const __declspec(selectany) SRGB LightGreen           = { 0.564705908f, 0.933333397f, 0.564705908f };
    extern const __declspec(selectany) SRGB LightGray            = { 0.827451050f, 0.827451050f, 0.827451050f };
    extern const __declspec(selectany) SRGB LightPink            = { 1.000000000f, 0.713725507f, 0.756862819f };
    extern const __declspec(selectany) SRGB LightSalmon          = { 1.000000000f, 0.627451003f, 0.478431404f };
    extern const __declspec(selectany) SRGB LightSeaGreen        = { 0.125490203f, 0.698039234f, 0.666666687f };
    extern const __declspec(selectany) SRGB LightSkyBlue         = { 0.529411793f, 0.807843208f, 0.980392218f };
    extern const __declspec(selectany) SRGB LightSlateGray       = { 0.466666698f, 0.533333361f, 0.600000024f };
    extern const __declspec(selectany) SRGB LightSteelBlue       = { 0.690196097f, 0.768627524f, 0.870588303f };
    extern const __declspec(selectany) SRGB LightYellow          = { 1.000000000f, 1.000000000f, 0.878431439f };
    extern const __declspec(selectany) SRGB Lime                 = { 0.000000000f, 1.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB LimeGreen            = { 0.196078449f, 0.803921640f, 0.196078449f };
    extern const __declspec(selectany) SRGB Linen                = { 0.980392218f, 0.941176534f, 0.901960850f };
    extern const __declspec(selectany) SRGB Magenta              = { 1.000000000f, 0.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB Maroon               = { 0.501960814f, 0.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB MediumAquamarine     = { 0.400000036f, 0.803921640f, 0.666666687f };
    extern const __declspec(selectany) SRGB MediumBlue           = { 0.000000000f, 0.000000000f, 0.803921640f };
    extern const __declspec(selectany) SRGB MediumOrchid         = { 0.729411781f, 0.333333343f, 0.827451050f };
    extern const __declspec(selectany) SRGB MediumPurple         = { 0.576470613f, 0.439215720f, 0.858823597f };
    extern const __declspec(selectany) SRGB MediumSeaGreen       = { 0.235294133f, 0.701960802f, 0.443137288f };
    extern const __declspec(selectany) SRGB MediumSlateBlue      = { 0.482352972f, 0.407843173f, 0.933333397f };
    extern const __declspec(selectany) SRGB MediumSpringGreen    = { 0.000000000f, 0.980392218f, 0.603921592f };
    extern const __declspec(selectany) SRGB MediumTurquoise      = { 0.282352954f, 0.819607913f, 0.800000072f };
    extern const __declspec(selectany) SRGB MediumVioletRed      = { 0.780392230f, 0.082352944f, 0.521568656f };
    extern const __declspec(selectany) SRGB MidnightBlue         = { 0.098039225f, 0.098039225f, 0.439215720f };
    extern const __declspec(selectany) SRGB MintCream            = { 0.960784376f, 1.000000000f, 0.980392218f };
    extern const __declspec(selectany) SRGB MistyRose            = { 1.000000000f, 0.894117713f, 0.882353008f };
    extern const __declspec(selectany) SRGB Moccasin             = { 1.000000000f, 0.894117713f, 0.709803939f };
    extern const __declspec(selectany) SRGB NavajoWhite          = { 1.000000000f, 0.870588303f, 0.678431392f };
    extern const __declspec(selectany) SRGB Navy                 = { 0.000000000f, 0.000000000f, 0.501960814f };
    extern const __declspec(selectany) SRGB OldLace              = { 0.992156923f, 0.960784376f, 0.901960850f };
    extern const __declspec(selectany) SRGB Olive                = { 0.501960814f, 0.501960814f, 0.000000000f };
    extern const __declspec(selectany) SRGB OliveDrab            = { 0.419607878f, 0.556862772f, 0.137254909f };
    extern const __declspec(selectany) SRGB Orange               = { 1.000000000f, 0.647058845f, 0.000000000f };
    extern const __declspec(selectany) SRGB OrangeRed            = { 1.000000000f, 0.270588249f, 0.000000000f };
    extern const __declspec(selectany) SRGB Orchid               = { 0.854902029f, 0.439215720f, 0.839215755f };
    extern const __declspec(selectany) SRGB PaleGoldenrod        = { 0.933333397f, 0.909803987f, 0.666666687f };
    extern const __declspec(selectany) SRGB PaleGreen            = { 0.596078455f, 0.984313786f, 0.596078455f };
    extern const __declspec(selectany) SRGB PaleTurquoise        = { 0.686274529f, 0.933333397f, 0.933333397f };
    extern const __declspec(selectany) SRGB PaleVioletRed        = { 0.858823597f, 0.439215720f, 0.576470613f };
    extern const __declspec(selectany) SRGB PapayaWhip           = { 1.000000000f, 0.937254965f, 0.835294187f };
    extern const __declspec(selectany) SRGB PeachPuff            = { 1.000000000f, 0.854902029f, 0.725490212f };
    extern const __declspec(selectany) SRGB Peru                 = { 0.803921640f, 0.521568656f, 0.247058839f };
    extern const __declspec(selectany) SRGB Pink                 = { 1.000000000f, 0.752941251f, 0.796078503f };
    extern const __declspec(selectany) SRGB Plum                 = { 0.866666734f, 0.627451003f, 0.866666734f };
    extern const __declspec(selectany) SRGB PowderBlue           = { 0.690196097f, 0.878431439f, 0.901960850f };
    extern const __declspec(selectany) SRGB Purple               = { 0.501960814f, 0.000000000f, 0.501960814f };
    extern const __declspec(selectany) SRGB Red                  = { 1.000000000f, 0.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB RosyBrown            = { 0.737254918f, 0.560784340f, 0.560784340f };
    extern const __declspec(selectany) SRGB RoyalBlue            = { 0.254901975f, 0.411764741f, 0.882353008f };
    extern const __declspec(selectany) SRGB SaddleBrown          = { 0.545098066f, 0.270588249f, 0.074509807f };
    extern const __declspec(selectany) SRGB Salmon               = { 0.980392218f, 0.501960814f, 0.447058856f };
    extern const __declspec(selectany) SRGB SandyBrown           = { 0.956862807f, 0.643137276f, 0.376470625f };
    extern const __declspec(selectany) SRGB SeaGreen             = { 0.180392161f, 0.545098066f, 0.341176480f };
    extern const __declspec(selectany) SRGB SeaShell             = { 1.000000000f, 0.960784376f, 0.933333397f };
    extern const __declspec(selectany) SRGB Sienna               = { 0.627451003f, 0.321568638f, 0.176470593f };
    extern const __declspec(selectany) SRGB Silver               = { 0.752941251f, 0.752941251f, 0.752941251f };
    extern const __declspec(selectany) SRGB SkyBlue              = { 0.529411793f, 0.807843208f, 0.921568692f };
    extern const __declspec(selectany) SRGB SlateBlue            = { 0.415686309f, 0.352941185f, 0.803921640f };
    extern const __declspec(selectany) SRGB SlateGray            = { 0.439215720f, 0.501960814f, 0.564705908f };
    extern const __declspec(selectany) SRGB Snow                 = { 1.000000000f, 0.980392218f, 0.980392218f };
    extern const __declspec(selectany) SRGB SpringGreen          = { 0.000000000f, 1.000000000f, 0.498039246f };
    extern const __declspec(selectany) SRGB SteelBlue            = { 0.274509817f, 0.509803951f, 0.705882370f };
    extern const __declspec(selectany) SRGB Tan                  = { 0.823529482f, 0.705882370f, 0.549019635f };
    extern const __declspec(selectany) SRGB Teal                 = { 0.000000000f, 0.501960814f, 0.501960814f };
    extern const __declspec(selectany) SRGB Thistle              = { 0.847058892f, 0.749019623f, 0.847058892f };
    extern const __declspec(selectany) SRGB Tomato               = { 1.000000000f, 0.388235331f, 0.278431386f };
    extern const __declspec(selectany) SRGB Turquoise            = { 0.250980407f, 0.878431439f, 0.815686345f };
    extern const __declspec(selectany) SRGB Violet               = { 0.933333397f, 0.509803951f, 0.933333397f };
    extern const __declspec(selectany) SRGB Wheat                = { 0.960784376f, 0.870588303f, 0.701960802f };
    extern const __declspec(selectany) SRGB White                = { 1.000000000f, 1.000000000f, 1.000000000f };
    extern const __declspec(selectany) SRGB WhiteSmoke           = { 0.960784376f, 0.960784376f, 0.960784376f };
    extern const __declspec(selectany) SRGB Yellow               = { 1.000000000f, 1.000000000f, 0.000000000f };
    extern const __declspec(selectany) SRGB YellowGreen          = { 0.603921592f, 0.803921640f, 0.196078449f };
}

#pragma endregion