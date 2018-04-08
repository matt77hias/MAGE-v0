#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::color {

    constexpr RGB AliceBlue            = { 0.941176534f, 0.972549081f, 1.000000000f };
    constexpr RGB AntiqueWhite         = { 0.980392218f, 0.921568692f, 0.843137324f };
    constexpr RGB Aqua                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB Aquamarine           = { 0.498039246f, 1.000000000f, 0.831372619f };
    constexpr RGB Azure                = { 0.941176534f, 1.000000000f, 1.000000000f };
    constexpr RGB Beige                = { 0.960784376f, 0.960784376f, 0.862745166f };
    constexpr RGB Bisque               = { 1.000000000f, 0.894117713f, 0.768627524f };
    constexpr RGB Black                = { 0.000000000f, 0.000000000f, 0.000000000f };
    constexpr RGB BlanchedAlmond       = { 1.000000000f, 0.921568692f, 0.803921640f };
    constexpr RGB Blue                 = { 0.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB BlueViolet           = { 0.541176498f, 0.168627456f, 0.886274576f };
    constexpr RGB Brown                = { 0.647058845f, 0.164705887f, 0.164705887f };
    constexpr RGB BurlyWood            = { 0.870588303f, 0.721568644f, 0.529411793f };
    constexpr RGB CadetBlue            = { 0.372549027f, 0.619607866f, 0.627451003f };
    constexpr RGB Chartreuse           = { 0.498039246f, 1.000000000f, 0.000000000f };
    constexpr RGB Chocolate            = { 0.823529482f, 0.411764741f, 0.117647067f };
    constexpr RGB Coral                = { 1.000000000f, 0.498039246f, 0.313725501f };
    constexpr RGB CornflowerBlue       = { 0.392156899f, 0.584313750f, 0.929411829f };
    constexpr RGB Cornsilk             = { 1.000000000f, 0.972549081f, 0.862745166f };
    constexpr RGB Crimson              = { 0.862745166f, 0.078431375f, 0.235294133f };
    constexpr RGB Cyan                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB DarkBlue             = { 0.000000000f, 0.000000000f, 0.545098066f };
    constexpr RGB DarkCyan             = { 0.000000000f, 0.545098066f, 0.545098066f };
    constexpr RGB DarkGoldenrod        = { 0.721568644f, 0.525490224f, 0.043137256f };
    constexpr RGB DarkGray             = { 0.662745118f, 0.662745118f, 0.662745118f };
    constexpr RGB DarkGreen            = { 0.000000000f, 0.392156899f, 0.000000000f };
    constexpr RGB DarkKhaki            = { 0.741176486f, 0.717647076f, 0.419607878f };
    constexpr RGB DarkMagenta          = { 0.545098066f, 0.000000000f, 0.545098066f };
    constexpr RGB DarkOliveGreen       = { 0.333333343f, 0.419607878f, 0.184313729f };
    constexpr RGB DarkOrange           = { 1.000000000f, 0.549019635f, 0.000000000f };
    constexpr RGB DarkOrchid           = { 0.600000024f, 0.196078449f, 0.800000072f };
    constexpr RGB DarkRed              = { 0.545098066f, 0.000000000f, 0.000000000f };
    constexpr RGB DarkSalmon           = { 0.913725555f, 0.588235319f, 0.478431404f };
    constexpr RGB DarkSeaGreen         = { 0.560784340f, 0.737254918f, 0.545098066f };
    constexpr RGB DarkSlateBlue        = { 0.282352954f, 0.239215702f, 0.545098066f };
    constexpr RGB DarkSlateGray        = { 0.184313729f, 0.309803933f, 0.309803933f };
    constexpr RGB DarkTurquoise        = { 0.000000000f, 0.807843208f, 0.819607913f };
    constexpr RGB DarkViolet           = { 0.580392182f, 0.000000000f, 0.827451050f };
    constexpr RGB DeepPink             = { 1.000000000f, 0.078431375f, 0.576470613f };
    constexpr RGB DeepSkyBlue          = { 0.000000000f, 0.749019623f, 1.000000000f };
    constexpr RGB DimGray              = { 0.411764741f, 0.411764741f, 0.411764741f };
    constexpr RGB DodgerBlue           = { 0.117647067f, 0.564705908f, 1.000000000f };
    constexpr RGB Firebrick            = { 0.698039234f, 0.133333340f, 0.133333340f };
    constexpr RGB FloralWhite          = { 1.000000000f, 0.980392218f, 0.941176534f };
    constexpr RGB ForestGreen          = { 0.133333340f, 0.545098066f, 0.133333340f };
    constexpr RGB Fuchsia              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB Gainsboro            = { 0.862745166f, 0.862745166f, 0.862745166f };
    constexpr RGB GhostWhite           = { 0.972549081f, 0.972549081f, 1.000000000f };
    constexpr RGB Gold                 = { 1.000000000f, 0.843137324f, 0.000000000f };
    constexpr RGB Goldenrod            = { 0.854902029f, 0.647058845f, 0.125490203f };
    constexpr RGB Gray                 = { 0.501960814f, 0.501960814f, 0.501960814f };
    constexpr RGB Green                = { 0.000000000f, 0.501960814f, 0.000000000f };
    constexpr RGB GreenYellow          = { 0.678431392f, 1.000000000f, 0.184313729f };
    constexpr RGB Honeydew             = { 0.941176534f, 1.000000000f, 0.941176534f };
    constexpr RGB HotPink              = { 1.000000000f, 0.411764741f, 0.705882370f };
    constexpr RGB IndianRed            = { 0.803921640f, 0.360784322f, 0.360784322f };
    constexpr RGB Indigo               = { 0.294117659f, 0.000000000f, 0.509803951f };
    constexpr RGB Ivory                = { 1.000000000f, 1.000000000f, 0.941176534f };
    constexpr RGB Khaki                = { 0.941176534f, 0.901960850f, 0.549019635f };
    constexpr RGB Lavender             = { 0.901960850f, 0.901960850f, 0.980392218f };
    constexpr RGB LavenderBlush        = { 1.000000000f, 0.941176534f, 0.960784376f };
    constexpr RGB LawnGreen            = { 0.486274540f, 0.988235354f, 0.000000000f };
    constexpr RGB LemonChiffon         = { 1.000000000f, 0.980392218f, 0.803921640f };
    constexpr RGB LightBlue            = { 0.678431392f, 0.847058892f, 0.901960850f };
    constexpr RGB LightCoral           = { 0.941176534f, 0.501960814f, 0.501960814f };
    constexpr RGB LightCyan            = { 0.878431439f, 1.000000000f, 1.000000000f };
    constexpr RGB LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f };
    constexpr RGB LightGreen           = { 0.564705908f, 0.933333397f, 0.564705908f };
    constexpr RGB LightGray            = { 0.827451050f, 0.827451050f, 0.827451050f };
    constexpr RGB LightPink            = { 1.000000000f, 0.713725507f, 0.756862819f };
    constexpr RGB LightSalmon          = { 1.000000000f, 0.627451003f, 0.478431404f };
    constexpr RGB LightSeaGreen        = { 0.125490203f, 0.698039234f, 0.666666687f };
    constexpr RGB LightSkyBlue         = { 0.529411793f, 0.807843208f, 0.980392218f };
    constexpr RGB LightSlateGray       = { 0.466666698f, 0.533333361f, 0.600000024f };
    constexpr RGB LightSteelBlue       = { 0.690196097f, 0.768627524f, 0.870588303f };
    constexpr RGB LightYellow          = { 1.000000000f, 1.000000000f, 0.878431439f };
    constexpr RGB Lime                 = { 0.000000000f, 1.000000000f, 0.000000000f };
    constexpr RGB LimeGreen            = { 0.196078449f, 0.803921640f, 0.196078449f };
    constexpr RGB Linen                = { 0.980392218f, 0.941176534f, 0.901960850f };
    constexpr RGB Magenta              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB Maroon               = { 0.501960814f, 0.000000000f, 0.000000000f };
    constexpr RGB MediumAquamarine     = { 0.400000036f, 0.803921640f, 0.666666687f };
    constexpr RGB MediumBlue           = { 0.000000000f, 0.000000000f, 0.803921640f };
    constexpr RGB MediumOrchid         = { 0.729411781f, 0.333333343f, 0.827451050f };
    constexpr RGB MediumPurple         = { 0.576470613f, 0.439215720f, 0.858823597f };
    constexpr RGB MediumSeaGreen       = { 0.235294133f, 0.701960802f, 0.443137288f };
    constexpr RGB MediumSlateBlue      = { 0.482352972f, 0.407843173f, 0.933333397f };
    constexpr RGB MediumSpringGreen    = { 0.000000000f, 0.980392218f, 0.603921592f };
    constexpr RGB MediumTurquoise      = { 0.282352954f, 0.819607913f, 0.800000072f };
    constexpr RGB MediumVioletRed      = { 0.780392230f, 0.082352944f, 0.521568656f };
    constexpr RGB MidnightBlue         = { 0.098039225f, 0.098039225f, 0.439215720f };
    constexpr RGB MintCream            = { 0.960784376f, 1.000000000f, 0.980392218f };
    constexpr RGB MistyRose            = { 1.000000000f, 0.894117713f, 0.882353008f };
    constexpr RGB Moccasin             = { 1.000000000f, 0.894117713f, 0.709803939f };
    constexpr RGB NavajoWhite          = { 1.000000000f, 0.870588303f, 0.678431392f };
    constexpr RGB Navy                 = { 0.000000000f, 0.000000000f, 0.501960814f };
    constexpr RGB OldLace              = { 0.992156923f, 0.960784376f, 0.901960850f };
    constexpr RGB Olive                = { 0.501960814f, 0.501960814f, 0.000000000f };
    constexpr RGB OliveDrab            = { 0.419607878f, 0.556862772f, 0.137254909f };
    constexpr RGB Orange               = { 1.000000000f, 0.647058845f, 0.000000000f };
    constexpr RGB OrangeRed            = { 1.000000000f, 0.270588249f, 0.000000000f };
    constexpr RGB Orchid               = { 0.854902029f, 0.439215720f, 0.839215755f };
    constexpr RGB PaleGoldenrod        = { 0.933333397f, 0.909803987f, 0.666666687f };
    constexpr RGB PaleGreen            = { 0.596078455f, 0.984313786f, 0.596078455f };
    constexpr RGB PaleTurquoise        = { 0.686274529f, 0.933333397f, 0.933333397f };
    constexpr RGB PaleVioletRed        = { 0.858823597f, 0.439215720f, 0.576470613f };
    constexpr RGB PapayaWhip           = { 1.000000000f, 0.937254965f, 0.835294187f };
    constexpr RGB PeachPuff            = { 1.000000000f, 0.854902029f, 0.725490212f };
    constexpr RGB Peru                 = { 0.803921640f, 0.521568656f, 0.247058839f };
    constexpr RGB Pink                 = { 1.000000000f, 0.752941251f, 0.796078503f };
    constexpr RGB Plum                 = { 0.866666734f, 0.627451003f, 0.866666734f };
    constexpr RGB PowderBlue           = { 0.690196097f, 0.878431439f, 0.901960850f };
    constexpr RGB Purple               = { 0.501960814f, 0.000000000f, 0.501960814f };
    constexpr RGB Red                  = { 1.000000000f, 0.000000000f, 0.000000000f };
    constexpr RGB RosyBrown            = { 0.737254918f, 0.560784340f, 0.560784340f };
    constexpr RGB RoyalBlue            = { 0.254901975f, 0.411764741f, 0.882353008f };
    constexpr RGB SaddleBrown          = { 0.545098066f, 0.270588249f, 0.074509807f };
    constexpr RGB Salmon               = { 0.980392218f, 0.501960814f, 0.447058856f };
    constexpr RGB SandyBrown           = { 0.956862807f, 0.643137276f, 0.376470625f };
    constexpr RGB SeaGreen             = { 0.180392161f, 0.545098066f, 0.341176480f };
    constexpr RGB SeaShell             = { 1.000000000f, 0.960784376f, 0.933333397f };
    constexpr RGB Sienna               = { 0.627451003f, 0.321568638f, 0.176470593f };
    constexpr RGB Silver               = { 0.752941251f, 0.752941251f, 0.752941251f };
    constexpr RGB SkyBlue              = { 0.529411793f, 0.807843208f, 0.921568692f };
    constexpr RGB SlateBlue            = { 0.415686309f, 0.352941185f, 0.803921640f };
    constexpr RGB SlateGray            = { 0.439215720f, 0.501960814f, 0.564705908f };
    constexpr RGB Snow                 = { 1.000000000f, 0.980392218f, 0.980392218f };
    constexpr RGB SpringGreen          = { 0.000000000f, 1.000000000f, 0.498039246f };
    constexpr RGB SteelBlue            = { 0.274509817f, 0.509803951f, 0.705882370f };
    constexpr RGB Tan                  = { 0.823529482f, 0.705882370f, 0.549019635f };
    constexpr RGB Teal                 = { 0.000000000f, 0.501960814f, 0.501960814f };
    constexpr RGB Thistle              = { 0.847058892f, 0.749019623f, 0.847058892f };
    constexpr RGB Tomato               = { 1.000000000f, 0.388235331f, 0.278431386f };
    constexpr RGB Turquoise            = { 0.250980407f, 0.878431439f, 0.815686345f };
    constexpr RGB Violet               = { 0.933333397f, 0.509803951f, 0.933333397f };
    constexpr RGB Wheat                = { 0.960784376f, 0.870588303f, 0.701960802f };
    constexpr RGB White                = { 1.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB WhiteSmoke           = { 0.960784376f, 0.960784376f, 0.960784376f };
    constexpr RGB Yellow               = { 1.000000000f, 1.000000000f, 0.000000000f };
    constexpr RGB YellowGreen          = { 0.603921592f, 0.803921640f, 0.196078449f };
}