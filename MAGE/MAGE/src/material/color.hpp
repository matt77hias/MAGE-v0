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

    constexpr SRGB AliceBlue            = { 0.941176534f, 0.972549081f, 1.000000000f };
    constexpr SRGB AntiqueWhite         = { 0.980392218f, 0.921568692f, 0.843137324f };
    constexpr SRGB Aqua                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr SRGB Aquamarine           = { 0.498039246f, 1.000000000f, 0.831372619f };
    constexpr SRGB Azure                = { 0.941176534f, 1.000000000f, 1.000000000f };
    constexpr SRGB Beige                = { 0.960784376f, 0.960784376f, 0.862745166f };
    constexpr SRGB Bisque               = { 1.000000000f, 0.894117713f, 0.768627524f };
    constexpr SRGB Black                = { 0.000000000f, 0.000000000f, 0.000000000f };
    constexpr SRGB BlanchedAlmond       = { 1.000000000f, 0.921568692f, 0.803921640f };
    constexpr SRGB Blue                 = { 0.000000000f, 0.000000000f, 1.000000000f };
    constexpr SRGB BlueViolet           = { 0.541176498f, 0.168627456f, 0.886274576f };
    constexpr SRGB Brown                = { 0.647058845f, 0.164705887f, 0.164705887f };
    constexpr SRGB BurlyWood            = { 0.870588303f, 0.721568644f, 0.529411793f };
    constexpr SRGB CadetBlue            = { 0.372549027f, 0.619607866f, 0.627451003f };
    constexpr SRGB Chartreuse           = { 0.498039246f, 1.000000000f, 0.000000000f };
    constexpr SRGB Chocolate            = { 0.823529482f, 0.411764741f, 0.117647067f };
    constexpr SRGB Coral                = { 1.000000000f, 0.498039246f, 0.313725501f };
    constexpr SRGB CornflowerBlue       = { 0.392156899f, 0.584313750f, 0.929411829f };
    constexpr SRGB Cornsilk             = { 1.000000000f, 0.972549081f, 0.862745166f };
    constexpr SRGB Crimson              = { 0.862745166f, 0.078431375f, 0.235294133f };
    constexpr SRGB Cyan                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr SRGB DarkBlue             = { 0.000000000f, 0.000000000f, 0.545098066f };
    constexpr SRGB DarkCyan             = { 0.000000000f, 0.545098066f, 0.545098066f };
    constexpr SRGB DarkGoldenrod        = { 0.721568644f, 0.525490224f, 0.043137256f };
    constexpr SRGB DarkGray             = { 0.662745118f, 0.662745118f, 0.662745118f };
    constexpr SRGB DarkGreen            = { 0.000000000f, 0.392156899f, 0.000000000f };
    constexpr SRGB DarkKhaki            = { 0.741176486f, 0.717647076f, 0.419607878f };
    constexpr SRGB DarkMagenta          = { 0.545098066f, 0.000000000f, 0.545098066f };
    constexpr SRGB DarkOliveGreen       = { 0.333333343f, 0.419607878f, 0.184313729f };
    constexpr SRGB DarkOrange           = { 1.000000000f, 0.549019635f, 0.000000000f };
    constexpr SRGB DarkOrchid           = { 0.600000024f, 0.196078449f, 0.800000072f };
    constexpr SRGB DarkRed              = { 0.545098066f, 0.000000000f, 0.000000000f };
    constexpr SRGB DarkSalmon           = { 0.913725555f, 0.588235319f, 0.478431404f };
    constexpr SRGB DarkSeaGreen         = { 0.560784340f, 0.737254918f, 0.545098066f };
    constexpr SRGB DarkSlateBlue        = { 0.282352954f, 0.239215702f, 0.545098066f };
    constexpr SRGB DarkSlateGray        = { 0.184313729f, 0.309803933f, 0.309803933f };
    constexpr SRGB DarkTurquoise        = { 0.000000000f, 0.807843208f, 0.819607913f };
    constexpr SRGB DarkViolet           = { 0.580392182f, 0.000000000f, 0.827451050f };
    constexpr SRGB DeepPink             = { 1.000000000f, 0.078431375f, 0.576470613f };
    constexpr SRGB DeepSkyBlue          = { 0.000000000f, 0.749019623f, 1.000000000f };
    constexpr SRGB DimGray              = { 0.411764741f, 0.411764741f, 0.411764741f };
    constexpr SRGB DodgerBlue           = { 0.117647067f, 0.564705908f, 1.000000000f };
    constexpr SRGB Firebrick            = { 0.698039234f, 0.133333340f, 0.133333340f };
    constexpr SRGB FloralWhite          = { 1.000000000f, 0.980392218f, 0.941176534f };
    constexpr SRGB ForestGreen          = { 0.133333340f, 0.545098066f, 0.133333340f };
    constexpr SRGB Fuchsia              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr SRGB Gainsboro            = { 0.862745166f, 0.862745166f, 0.862745166f };
    constexpr SRGB GhostWhite           = { 0.972549081f, 0.972549081f, 1.000000000f };
    constexpr SRGB Gold                 = { 1.000000000f, 0.843137324f, 0.000000000f };
    constexpr SRGB Goldenrod            = { 0.854902029f, 0.647058845f, 0.125490203f };
    constexpr SRGB Gray                 = { 0.501960814f, 0.501960814f, 0.501960814f };
    constexpr SRGB Green                = { 0.000000000f, 0.501960814f, 0.000000000f };
    constexpr SRGB GreenYellow          = { 0.678431392f, 1.000000000f, 0.184313729f };
    constexpr SRGB Honeydew             = { 0.941176534f, 1.000000000f, 0.941176534f };
    constexpr SRGB HotPink              = { 1.000000000f, 0.411764741f, 0.705882370f };
    constexpr SRGB IndianRed            = { 0.803921640f, 0.360784322f, 0.360784322f };
    constexpr SRGB Indigo               = { 0.294117659f, 0.000000000f, 0.509803951f };
    constexpr SRGB Ivory                = { 1.000000000f, 1.000000000f, 0.941176534f };
    constexpr SRGB Khaki                = { 0.941176534f, 0.901960850f, 0.549019635f };
    constexpr SRGB Lavender             = { 0.901960850f, 0.901960850f, 0.980392218f };
    constexpr SRGB LavenderBlush        = { 1.000000000f, 0.941176534f, 0.960784376f };
    constexpr SRGB LawnGreen            = { 0.486274540f, 0.988235354f, 0.000000000f };
    constexpr SRGB LemonChiffon         = { 1.000000000f, 0.980392218f, 0.803921640f };
    constexpr SRGB LightBlue            = { 0.678431392f, 0.847058892f, 0.901960850f };
    constexpr SRGB LightCoral           = { 0.941176534f, 0.501960814f, 0.501960814f };
    constexpr SRGB LightCyan            = { 0.878431439f, 1.000000000f, 1.000000000f };
    constexpr SRGB LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f };
    constexpr SRGB LightGreen           = { 0.564705908f, 0.933333397f, 0.564705908f };
    constexpr SRGB LightGray            = { 0.827451050f, 0.827451050f, 0.827451050f };
    constexpr SRGB LightPink            = { 1.000000000f, 0.713725507f, 0.756862819f };
    constexpr SRGB LightSalmon          = { 1.000000000f, 0.627451003f, 0.478431404f };
    constexpr SRGB LightSeaGreen        = { 0.125490203f, 0.698039234f, 0.666666687f };
    constexpr SRGB LightSkyBlue         = { 0.529411793f, 0.807843208f, 0.980392218f };
    constexpr SRGB LightSlateGray       = { 0.466666698f, 0.533333361f, 0.600000024f };
    constexpr SRGB LightSteelBlue       = { 0.690196097f, 0.768627524f, 0.870588303f };
    constexpr SRGB LightYellow          = { 1.000000000f, 1.000000000f, 0.878431439f };
    constexpr SRGB Lime                 = { 0.000000000f, 1.000000000f, 0.000000000f };
    constexpr SRGB LimeGreen            = { 0.196078449f, 0.803921640f, 0.196078449f };
    constexpr SRGB Linen                = { 0.980392218f, 0.941176534f, 0.901960850f };
    constexpr SRGB Magenta              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr SRGB Maroon               = { 0.501960814f, 0.000000000f, 0.000000000f };
    constexpr SRGB MediumAquamarine     = { 0.400000036f, 0.803921640f, 0.666666687f };
    constexpr SRGB MediumBlue           = { 0.000000000f, 0.000000000f, 0.803921640f };
    constexpr SRGB MediumOrchid         = { 0.729411781f, 0.333333343f, 0.827451050f };
    constexpr SRGB MediumPurple         = { 0.576470613f, 0.439215720f, 0.858823597f };
    constexpr SRGB MediumSeaGreen       = { 0.235294133f, 0.701960802f, 0.443137288f };
    constexpr SRGB MediumSlateBlue      = { 0.482352972f, 0.407843173f, 0.933333397f };
    constexpr SRGB MediumSpringGreen    = { 0.000000000f, 0.980392218f, 0.603921592f };
    constexpr SRGB MediumTurquoise      = { 0.282352954f, 0.819607913f, 0.800000072f };
    constexpr SRGB MediumVioletRed      = { 0.780392230f, 0.082352944f, 0.521568656f };
    constexpr SRGB MidnightBlue         = { 0.098039225f, 0.098039225f, 0.439215720f };
    constexpr SRGB MintCream            = { 0.960784376f, 1.000000000f, 0.980392218f };
    constexpr SRGB MistyRose            = { 1.000000000f, 0.894117713f, 0.882353008f };
    constexpr SRGB Moccasin             = { 1.000000000f, 0.894117713f, 0.709803939f };
    constexpr SRGB NavajoWhite          = { 1.000000000f, 0.870588303f, 0.678431392f };
    constexpr SRGB Navy                 = { 0.000000000f, 0.000000000f, 0.501960814f };
    constexpr SRGB OldLace              = { 0.992156923f, 0.960784376f, 0.901960850f };
    constexpr SRGB Olive                = { 0.501960814f, 0.501960814f, 0.000000000f };
    constexpr SRGB OliveDrab            = { 0.419607878f, 0.556862772f, 0.137254909f };
    constexpr SRGB Orange               = { 1.000000000f, 0.647058845f, 0.000000000f };
    constexpr SRGB OrangeRed            = { 1.000000000f, 0.270588249f, 0.000000000f };
    constexpr SRGB Orchid               = { 0.854902029f, 0.439215720f, 0.839215755f };
    constexpr SRGB PaleGoldenrod        = { 0.933333397f, 0.909803987f, 0.666666687f };
    constexpr SRGB PaleGreen            = { 0.596078455f, 0.984313786f, 0.596078455f };
    constexpr SRGB PaleTurquoise        = { 0.686274529f, 0.933333397f, 0.933333397f };
    constexpr SRGB PaleVioletRed        = { 0.858823597f, 0.439215720f, 0.576470613f };
    constexpr SRGB PapayaWhip           = { 1.000000000f, 0.937254965f, 0.835294187f };
    constexpr SRGB PeachPuff            = { 1.000000000f, 0.854902029f, 0.725490212f };
    constexpr SRGB Peru                 = { 0.803921640f, 0.521568656f, 0.247058839f };
    constexpr SRGB Pink                 = { 1.000000000f, 0.752941251f, 0.796078503f };
    constexpr SRGB Plum                 = { 0.866666734f, 0.627451003f, 0.866666734f };
    constexpr SRGB PowderBlue           = { 0.690196097f, 0.878431439f, 0.901960850f };
    constexpr SRGB Purple               = { 0.501960814f, 0.000000000f, 0.501960814f };
    constexpr SRGB Red                  = { 1.000000000f, 0.000000000f, 0.000000000f };
    constexpr SRGB RosyBrown            = { 0.737254918f, 0.560784340f, 0.560784340f };
    constexpr SRGB RoyalBlue            = { 0.254901975f, 0.411764741f, 0.882353008f };
    constexpr SRGB SaddleBrown          = { 0.545098066f, 0.270588249f, 0.074509807f };
    constexpr SRGB Salmon               = { 0.980392218f, 0.501960814f, 0.447058856f };
    constexpr SRGB SandyBrown           = { 0.956862807f, 0.643137276f, 0.376470625f };
    constexpr SRGB SeaGreen             = { 0.180392161f, 0.545098066f, 0.341176480f };
    constexpr SRGB SeaShell             = { 1.000000000f, 0.960784376f, 0.933333397f };
    constexpr SRGB Sienna               = { 0.627451003f, 0.321568638f, 0.176470593f };
    constexpr SRGB Silver               = { 0.752941251f, 0.752941251f, 0.752941251f };
    constexpr SRGB SkyBlue              = { 0.529411793f, 0.807843208f, 0.921568692f };
    constexpr SRGB SlateBlue            = { 0.415686309f, 0.352941185f, 0.803921640f };
    constexpr SRGB SlateGray            = { 0.439215720f, 0.501960814f, 0.564705908f };
    constexpr SRGB Snow                 = { 1.000000000f, 0.980392218f, 0.980392218f };
    constexpr SRGB SpringGreen          = { 0.000000000f, 1.000000000f, 0.498039246f };
    constexpr SRGB SteelBlue            = { 0.274509817f, 0.509803951f, 0.705882370f };
    constexpr SRGB Tan                  = { 0.823529482f, 0.705882370f, 0.549019635f };
    constexpr SRGB Teal                 = { 0.000000000f, 0.501960814f, 0.501960814f };
    constexpr SRGB Thistle              = { 0.847058892f, 0.749019623f, 0.847058892f };
    constexpr SRGB Tomato               = { 1.000000000f, 0.388235331f, 0.278431386f };
    constexpr SRGB Turquoise            = { 0.250980407f, 0.878431439f, 0.815686345f };
    constexpr SRGB Violet               = { 0.933333397f, 0.509803951f, 0.933333397f };
    constexpr SRGB Wheat                = { 0.960784376f, 0.870588303f, 0.701960802f };
    constexpr SRGB White                = { 1.000000000f, 1.000000000f, 1.000000000f };
    constexpr SRGB WhiteSmoke           = { 0.960784376f, 0.960784376f, 0.960784376f };
    constexpr SRGB Yellow               = { 1.000000000f, 1.000000000f, 0.000000000f };
    constexpr SRGB YellowGreen          = { 0.603921592f, 0.803921640f, 0.196078449f };
}

#pragma endregion