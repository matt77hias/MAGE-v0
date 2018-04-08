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

    constexpr RGB AliceBlue            = { 0.871367252f, 0.938685863f, 1.000000000f };
    constexpr RGB AntiqueWhite         = { 0.955973489f, 0.830770009f, 0.679542595f };
    constexpr RGB Aqua                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB Aquamarine           = { 0.212230785f, 1.000000000f, 0.658374942f };
    constexpr RGB Azure                = { 0.871367252f, 1.000000000f, 1.000000000f };
    constexpr RGB Beige                = { 0.913098786f, 0.913098786f, 0.715693628f };
    constexpr RGB Bisque               = { 1.000000000f, 0.775822348f, 0.552011519f };
    constexpr RGB Black                = { 0.000000000f, 0.000000000f, 0.000000000f };
    constexpr RGB BlanchedAlmond       = { 1.000000000f, 0.830770009f, 0.610495693f };
    constexpr RGB Blue                 = { 0.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB BlueViolet           = { 0.254152122f, 0.024157634f, 0.760524633f };
    constexpr RGB Brown                = { 0.376262151f, 0.023153367f, 0.023153367f };
    constexpr RGB BurlyWood            = { 0.730460868f, 0.479320208f, 0.242281151f };
    constexpr RGB CadetBlue            = { 0.114435379f, 0.341914453f, 0.351532627f };
    constexpr RGB Chartreuse           = { 0.212230785f, 1.000000000f, 0.000000000f };
    constexpr RGB Chocolate            = { 0.644479806f, 0.141263317f, 0.012983034f };
    constexpr RGB Coral                = { 1.000000000f, 0.212230785f, 0.080219826f };
    constexpr RGB CornflowerBlue       = { 0.127437705f, 0.300543822f, 0.846873364f };
    constexpr RGB Cornsilk             = { 1.000000000f, 0.938685863f, 0.715693628f };
    constexpr RGB Crimson              = { 0.715693628f, 0.006995410f, 0.045186210f };
    constexpr RGB Cyan                 = { 0.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB DarkBlue             = { 0.000000000f, 0.000000000f, 0.258182881f };
    constexpr RGB DarkCyan             = { 0.000000000f, 0.258182881f, 0.258182881f };
    constexpr RGB DarkGoldenrod        = { 0.479320208f, 0.238397601f, 0.003346536f };
    constexpr RGB DarkGray             = { 0.396755257f, 0.396755257f, 0.396755257f };
    constexpr RGB DarkGreen            = { 0.000000000f, 0.127437705f, 0.000000000f };
    constexpr RGB DarkKhaki            = { 0.508881344f, 0.473531521f, 0.147027292f };
    constexpr RGB DarkMagenta          = { 0.258182881f, 0.000000000f, 0.258182881f };
    constexpr RGB DarkOliveGreen       = { 0.090841717f, 0.147027292f, 0.028426041f };
    constexpr RGB DarkOrange           = { 1.000000000f, 0.262250686f, 0.000000000f };
    constexpr RGB DarkOrchid           = { 0.318546806f, 0.031896038f, 0.603827461f };
    constexpr RGB DarkRed              = { 0.258182881f, 0.000000000f, 0.000000000f };
    constexpr RGB DarkSalmon           = { 0.814846703f, 0.304987342f, 0.194617858f };
    constexpr RGB DarkSeaGreen         = { 0.274677340f, 0.502886482f, 0.258182881f };
    constexpr RGB DarkSlateBlue        = { 0.064803273f, 0.046665092f, 0.258182881f };
    constexpr RGB DarkSlateGray        = { 0.028426041f, 0.078187428f, 0.078187428f };
    constexpr RGB DarkTurquoise        = { 0.000000000f, 0.617206684f, 0.637596996f };
    constexpr RGB DarkViolet           = { 0.296138299f, 0.000000000f, 0.651405761f };
    constexpr RGB DeepPink             = { 1.000000000f, 0.006995410f, 0.291770677f };
    constexpr RGB DeepSkyBlue          = { 0.000000000f, 0.520995597f, 1.000000000f };
    constexpr RGB DimGray              = { 0.141263317f, 0.141263317f, 0.141263317f };
    constexpr RGB DodgerBlue           = { 0.012983034f, 0.278894291f, 1.000000000f };
    constexpr RGB Firebrick            = { 0.445201221f, 0.015996295f, 0.015996295f };
    constexpr RGB FloralWhite          = { 1.000000000f, 0.955973489f, 0.871367252f };
    constexpr RGB ForestGreen          = { 0.015996295f, 0.258182881f, 0.015996295f };
    constexpr RGB Fuchsia              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB Gainsboro            = { 0.715693628f, 0.715693628f, 0.715693628f };
    constexpr RGB GhostWhite           = { 0.938685863f, 0.938685863f, 1.000000000f };
    constexpr RGB Gold                 = { 1.000000000f, 0.679542595f, 0.000000000f };
    constexpr RGB Goldenrod            = { 0.701102018f, 0.376262151f, 0.014443845f };
    constexpr RGB Gray                 = { 0.215860528f, 0.215860528f, 0.215860528f };
    constexpr RGB Green                = { 0.000000000f, 0.215860528f, 0.000000000f };
    constexpr RGB GreenYellow          = { 0.417885097f, 1.000000000f, 0.028426041f };
    constexpr RGB Honeydew             = { 0.871367252f, 1.000000000f, 0.871367252f };
    constexpr RGB HotPink              = { 1.000000000f, 0.141263317f, 0.456411048f };
    constexpr RGB IndianRed            = { 0.610495693f, 0.107023108f, 0.107023108f };
    constexpr RGB Indigo               = { 0.070360101f, 0.000000000f, 0.223227985f };
    constexpr RGB Ivory                = { 1.000000000f, 1.000000000f, 0.871367252f };
    constexpr RGB Khaki                = { 0.871367252f, 0.791298071f, 0.262250686f };
    constexpr RGB Lavender             = { 0.791298071f, 0.791298071f, 0.955973489f };
    constexpr RGB LavenderBlush        = { 1.000000000f, 0.871367252f, 0.913098786f };
    constexpr RGB LawnGreen            = { 0.201556281f, 0.973445425f, 0.000000000f };
    constexpr RGB LemonChiffon         = { 1.000000000f, 0.955973489f, 0.610495693f };
    constexpr RGB LightBlue            = { 0.417885097f, 0.686685438f, 0.791298071f };
    constexpr RGB LightCoral           = { 0.871367252f, 0.215860528f, 0.215860528f };
    constexpr RGB LightCyan            = { 0.745404337f, 1.000000000f, 1.000000000f };
    constexpr RGB LightGoldenrodYellow = { 0.955973489f, 0.955973489f, 0.644479806f };
    constexpr RGB LightGreen           = { 0.278894291f, 0.854992740f, 0.278894291f };
    constexpr RGB LightGray            = { 0.651405761f, 0.651405761f, 0.651405761f };
    constexpr RGB LightPink            = { 1.000000000f, 0.467783821f, 0.533276521f };
    constexpr RGB LightSalmon          = { 1.000000000f, 0.351532627f, 0.194617858f };
    constexpr RGB LightSeaGreen        = { 0.014443845f, 0.445201221f, 0.401977807f };
    constexpr RGB LightSkyBlue         = { 0.242281151f, 0.617206684f, 0.955973489f };
    constexpr RGB LightSlateGray       = { 0.184475021f, 0.246201354f, 0.318546806f };
    constexpr RGB LightSteelBlue       = { 0.434153662f, 0.552011519f, 0.730460868f };
    constexpr RGB LightYellow          = { 1.000000000f, 1.000000000f, 0.745404337f };
    constexpr RGB Lime                 = { 0.000000000f, 1.000000000f, 0.000000000f };
    constexpr RGB LimeGreen            = { 0.031896038f, 0.610495693f, 0.031896038f };
    constexpr RGB Linen                = { 0.955973489f, 0.871367252f, 0.791298071f };
    constexpr RGB Magenta              = { 1.000000000f, 0.000000000f, 1.000000000f };
    constexpr RGB Maroon               = { 0.215860528f, 0.000000000f, 0.000000000f };
    constexpr RGB MediumAquamarine     = { 0.132868347f, 0.610495693f, 0.401977807f };
    constexpr RGB MediumBlue           = { 0.000000000f, 0.000000000f, 0.610495693f };
    constexpr RGB MediumOrchid         = { 0.491020874f, 0.090841717f, 0.651405761f };
    constexpr RGB MediumPurple         = { 0.291770677f, 0.162029402f, 0.708375906f };
    constexpr RGB MediumSeaGreen       = { 0.045186210f, 0.450785808f, 0.165132221f };
    constexpr RGB MediumSlateBlue      = { 0.198069347f, 0.138431641f, 0.854992740f };
    constexpr RGB MediumSpringGreen    = { 0.000000000f, 0.955973489f, 0.323143237f };
    constexpr RGB MediumTurquoise      = { 0.064803273f, 0.637596996f, 0.603827461f };
    constexpr RGB MediumVioletRed      = { 0.571124949f, 0.007499032f, 0.234550610f };
    constexpr RGB MidnightBlue         = { 0.009721219f, 0.009721219f, 0.162029402f };
    constexpr RGB MintCream            = { 0.913098786f, 1.000000000f, 0.955973489f };
    constexpr RGB MistyRose            = { 1.000000000f, 0.775822348f, 0.752942346f };
    constexpr RGB Moccasin             = { 1.000000000f, 0.775822348f, 0.462077025f };
    constexpr RGB NavajoWhite          = { 1.000000000f, 0.730460868f, 0.417885097f };
    constexpr RGB Navy                 = { 0.000000000f, 0.000000000f, 0.215860528f };
    constexpr RGB OldLace              = { 0.982250686f, 0.913098786f, 0.791298071f };
    constexpr RGB Olive                = { 0.215860528f, 0.215860528f, 0.000000000f };
    constexpr RGB OliveDrab            = { 0.147027292f, 0.270497820f, 0.016807377f };
    constexpr RGB Orange               = { 1.000000000f, 0.376262151f, 0.000000000f };
    constexpr RGB OrangeRed            = { 1.000000000f, 0.059511244f, 0.000000000f };
    constexpr RGB Orchid               = { 0.701102018f, 0.162029402f, 0.672443281f };
    constexpr RGB PaleGoldenrod        = { 0.854992740f, 0.806952389f, 0.401977807f };
    constexpr RGB PaleGreen            = { 0.313988741f, 0.964686383f, 0.313988741f };
    constexpr RGB PaleTurquoise        = { 0.428690523f, 0.854992740f, 0.854992740f };
    constexpr RGB PaleVioletRed        = { 0.708375906f, 0.162029402f, 0.291770677f };
    constexpr RGB PapayaWhip           = { 1.000000000f, 0.863157345f, 0.665387423f };
    constexpr RGB PeachPuff            = { 1.000000000f, 0.701102018f, 0.485149964f };
    constexpr RGB Peru                 = { 0.610495693f, 0.234550610f, 0.049706572f };
    constexpr RGB Pink                 = { 1.000000000f, 0.527115242f, 0.597201909f };
    constexpr RGB Plum                 = { 0.723055256f, 0.351532627f, 0.723055256f };
    constexpr RGB PowderBlue           = { 0.434153662f, 0.745404337f, 0.791298071f };
    constexpr RGB Purple               = { 0.215860528f, 0.000000000f, 0.215860528f };
    constexpr RGB Red                  = { 1.000000000f, 0.000000000f, 0.000000000f };
    constexpr RGB RosyBrown            = { 0.502886482f, 0.274677340f, 0.274677340f };
    constexpr RGB RoyalBlue            = { 0.052860653f, 0.141263317f, 0.752942346f };
    constexpr RGB SaddleBrown          = { 0.258182881f, 0.059511244f, 0.006512091f };
    constexpr RGB Salmon               = { 0.955973489f, 0.215860528f, 0.168269426f };
    constexpr RGB SandyBrown           = { 0.904661307f, 0.371237707f, 0.116970692f };
    constexpr RGB SeaGreen             = { 0.027320893f, 0.258182881f, 0.095307472f };
    constexpr RGB SeaShell             = { 1.000000000f, 0.913098786f, 0.854992740f };
    constexpr RGB Sienna               = { 0.351532627f, 0.084376217f, 0.026241223f };
    constexpr RGB Silver               = { 0.527115242f, 0.527115242f, 0.527115242f };
    constexpr RGB SkyBlue              = { 0.242281151f, 0.617206684f, 0.830770009f };
    constexpr RGB SlateBlue            = { 0.144128496f, 0.102241738f, 0.610495693f };
    constexpr RGB SlateGray            = { 0.162029402f, 0.215860528f, 0.278894291f };
    constexpr RGB Snow                 = { 1.000000000f, 0.955973489f, 0.955973489f };
    constexpr RGB SpringGreen          = { 0.000000000f, 1.000000000f, 0.212230785f };
    constexpr RGB SteelBlue            = { 0.061246060f, 0.223227985f, 0.456411048f };
    constexpr RGB Tan                  = { 0.644479806f, 0.456411048f, 0.262250686f };
    constexpr RGB Teal                 = { 0.000000000f, 0.215860528f, 0.215860528f };
    constexpr RGB Thistle              = { 0.686685438f, 0.520995597f, 0.686685438f };
    constexpr RGB Tomato               = { 1.000000000f, 0.124771842f, 0.063010024f };
    constexpr RGB Turquoise            = { 0.051269464f, 0.745404337f, 0.630757259f };
    constexpr RGB Violet               = { 0.854992740f, 0.223227985f, 0.854992740f };
    constexpr RGB Wheat                = { 0.913098786f, 0.730460868f, 0.450785808f };
    constexpr RGB White                = { 1.000000000f, 1.000000000f, 1.000000000f };
    constexpr RGB WhiteSmoke           = { 0.913098786f, 0.913098786f, 0.913098786f };
    constexpr RGB Yellow               = { 1.000000000f, 1.000000000f, 0.000000000f };
    constexpr RGB YellowGreen          = { 0.323143237f, 0.610495693f, 0.031896038f };
}