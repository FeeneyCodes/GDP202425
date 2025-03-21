#include "CGLColourHelper.h"
#include <algorithm>



CGLColourHelper::CColour::CColour( std::string sName, CGLColourHelper::enumColours colourEnum, glm::vec3 initRGB )
{
	this->enumName = colourEnum;
	this->name = sName;
	this->rgb = initRGB;
	return;
}

CGLColourHelper::CColour::CColour( std::string sName, CGLColourHelper::enumColours colourEnum, float r, float g, float b )
{
	this->enumName = colourEnum;
	this->name = sName;
	this->rgb.r = r;
	this->rgb.g = g;
	this->rgb.b = b;
	return;
}

//static 
CGLColourHelper* CGLColourHelper::m_p_theInstance = 0;

//static 
CGLColourHelper* CGLColourHelper::getInstance( void )
{
	if ( CGLColourHelper::m_p_theInstance == 0 )
	{
		CGLColourHelper::m_p_theInstance = new CGLColourHelper();
	}
	return CGLColourHelper::m_p_theInstance;
}

CGLColourHelper::CGLColourHelper()
{
	this->m_mapColours[ COLOUR_ALICE_BLUE ] = CGLColourHelper::CColour( "AliceBlue", COLOUR_ALICE_BLUE, 0.941f, 0.973f, 1.000f);
	this->m_mapColours[ COLOUR_ANTIQUE_WHITE ] = CGLColourHelper::CColour( "AntiqueWhite", COLOUR_ANTIQUE_WHITE, 0.980f, 0.922f, 0.843f);
	this->m_mapColours[ COLOUR_AQUA ] = CGLColourHelper::CColour( "Aqua", COLOUR_AQUA, 0.000f, 1.000f, 1.000f);
	this->m_mapColours[ COLOUR_AQUAMARINE ] = CGLColourHelper::CColour( "Aquamarine", COLOUR_AQUAMARINE, 0.498f, 1.000f, 0.831f);
	this->m_mapColours[ COLOUR_AZURE ] = CGLColourHelper::CColour( "Azure", COLOUR_AZURE, 0.941f, 1.000f, 1.000f);
	this->m_mapColours[ COLOUR_BEIGE ] = CGLColourHelper::CColour( "Beige", COLOUR_BEIGE, 0.961f, 0.961f, 0.863f);
	this->m_mapColours[ COLOUR_BISQUE ] = CGLColourHelper::CColour( "Bisque", COLOUR_BISQUE, 1.000f, 0.894f, 0.769f);
	this->m_mapColours[ COLOUR_BLACK ] = CGLColourHelper::CColour( "Black", COLOUR_BLACK, 0.000f, 0.000f, 0.000f);
	this->m_mapColours[ COLOUR_BLANCHED_ALMOND ] = CGLColourHelper::CColour( "BlanchedAlmond", COLOUR_BLANCHED_ALMOND, 1.000f, 0.922f, 0.804f);
	this->m_mapColours[ COLOUR_BLUE ] = CGLColourHelper::CColour( "Blue", COLOUR_BLUE, 0.000f, 0.000f, 1.000f);
	this->m_mapColours[ COLOUR_BLUE_VIOLET ] = CGLColourHelper::CColour( "BlueViolet", COLOUR_BLUE_VIOLET, 0.541f, 0.169f, 0.886f);
	this->m_mapColours[ COLOUR_BROWN ] = CGLColourHelper::CColour( "Brown", COLOUR_BROWN, 0.647f, 0.165f, 0.165f);
	this->m_mapColours[ COLOUR_BURLY_WOOD ] = CGLColourHelper::CColour( "BurlyWood", COLOUR_BURLY_WOOD, 0.871f, 0.722f, 0.529f);
	this->m_mapColours[ COLOUR_CADET_BLUE ] = CGLColourHelper::CColour( "CadetBlue", COLOUR_CADET_BLUE, 0.373f, 0.620f, 0.627f);
	this->m_mapColours[ COLOUR_CHARTREUSE ] = CGLColourHelper::CColour( "Chartreuse", COLOUR_CHARTREUSE, 0.498f, 1.000f, 0.000f);
	this->m_mapColours[ COLOUR_CHOCOLATE ] = CGLColourHelper::CColour( "Chocolate", COLOUR_CHOCOLATE, 0.824f, 0.412f, 0.118f);
	this->m_mapColours[ COLOUR_CORAL ] = CGLColourHelper::CColour( "Coral", COLOUR_CORAL, 1.000f, 0.498f, 0.314f);
	this->m_mapColours[ COLOUR_CORNFLOWER_BLUE ] = CGLColourHelper::CColour( "CornflowerBlue", COLOUR_CORNFLOWER_BLUE, 0.392f, 0.584f, 0.929f);
	this->m_mapColours[ COLOUR_CORNSILK ] = CGLColourHelper::CColour( "Cornsilk", COLOUR_CORNSILK, 1.000f, 0.973f, 0.863f);
	this->m_mapColours[ COLOUR_CRIMSON ] = CGLColourHelper::CColour( "Crimson", COLOUR_CRIMSON, 0.863f, 0.078f, 0.235f);
	this->m_mapColours[ COLOUR_CYAN ] = CGLColourHelper::CColour( "Cyan", COLOUR_CYAN, 0.000f, 1.000f, 1.000f);
	this->m_mapColours[ COLOUR_DARK_BLUE ] = CGLColourHelper::CColour( "DarkBlue", COLOUR_DARK_BLUE, 0.000f, 0.000f, 0.545f);
	this->m_mapColours[ COLOUR_DARK_CYAN ] = CGLColourHelper::CColour( "DarkCyan", COLOUR_DARK_CYAN, 0.000f, 0.545f, 0.545f);
	this->m_mapColours[ COLOUR_DARK_GOLDEN_ROD ] = CGLColourHelper::CColour( "DarkGoldenRod", COLOUR_DARK_GOLDEN_ROD, 0.722f, 0.525f, 0.043f);
	this->m_mapColours[ COLOUR_DARK_GRAY ] = CGLColourHelper::CColour( "DarkGray", COLOUR_DARK_GRAY, 0.663f, 0.663f, 0.663f);
	this->m_mapColours[ COLOUR_DARK_GREEN ] = CGLColourHelper::CColour( "DarkGreen", COLOUR_DARK_GREEN, 0.000f, 0.392f, 0.000f);
	this->m_mapColours[ COLOUR_DARK_KHAKI ] = CGLColourHelper::CColour( "DarkKhaki", COLOUR_DARK_KHAKI, 0.741f, 0.718f, 0.420f);
	this->m_mapColours[ COLOUR_DARK_MAGENTA ] = CGLColourHelper::CColour( "DarkMagenta", COLOUR_DARK_MAGENTA, 0.545f, 0.000f, 0.545f);
	this->m_mapColours[ COLOUR_DARK_OLIVE_GREEN ] = CGLColourHelper::CColour( "DarkOliveGreen", COLOUR_DARK_OLIVE_GREEN, 0.333f, 0.420f, 0.184f);
	this->m_mapColours[ COLOUR_DARK_ORANGE ] = CGLColourHelper::CColour( "DarkOrange", COLOUR_DARK_ORANGE, 1.000f, 0.549f, 0.000f);
	this->m_mapColours[ COLOUR_DARK_ORCHID ] = CGLColourHelper::CColour( "DarkOrchid", COLOUR_DARK_ORCHID, 0.600f, 0.196f, 0.800f);
	this->m_mapColours[ COLOUR_DARK_RED ] = CGLColourHelper::CColour( "DarkRed", COLOUR_DARK_RED, 0.545f, 0.000f, 0.000f);
	this->m_mapColours[ COLOUR_DARK_SALMON ] = CGLColourHelper::CColour( "DarkSalmon", COLOUR_DARK_SALMON, 0.914f, 0.588f, 0.478f);
	this->m_mapColours[ COLOUR_DARK_SEA_GREEN ] = CGLColourHelper::CColour( "DarkSeaGreen", COLOUR_DARK_SEA_GREEN, 0.561f, 0.737f, 0.561f);
	this->m_mapColours[ COLOUR_DARK_SLATE_BLUE ] = CGLColourHelper::CColour( "DarkSlateBlue", COLOUR_DARK_SLATE_BLUE, 0.282f, 0.239f, 0.545f);
	this->m_mapColours[ COLOUR_DARK_SLATE_GRAY ] = CGLColourHelper::CColour( "DarkSlateGray", COLOUR_DARK_SLATE_GRAY, 0.184f, 0.310f, 0.310f);
	this->m_mapColours[ COLOUR_DARK_TURQUOISE ] = CGLColourHelper::CColour( "DarkTurquoise", COLOUR_DARK_TURQUOISE, 0.000f, 0.808f, 0.820f);
	this->m_mapColours[ COLOUR_DARK_VIOLET ] = CGLColourHelper::CColour( "DarkViolet", COLOUR_DARK_VIOLET, 0.580f, 0.000f, 0.827f);
	this->m_mapColours[ COLOUR_DEEP_PINK ] = CGLColourHelper::CColour( "DeepPink", COLOUR_DEEP_PINK, 1.000f, 0.078f, 0.576f);
	this->m_mapColours[ COLOUR_DEEP_SKY_BLUE ] = CGLColourHelper::CColour( "DeepSkyBlue", COLOUR_DEEP_SKY_BLUE, 0.000f, 0.749f, 1.000f);
	this->m_mapColours[ COLOUR_DIM_GRAY ] = CGLColourHelper::CColour( "DimGray", COLOUR_DIM_GRAY, 0.412f, 0.412f, 0.412f);
	this->m_mapColours[ COLOUR_DODGER_BLUE ] = CGLColourHelper::CColour( "DodgerBlue", COLOUR_DODGER_BLUE, 0.118f, 0.565f, 1.000f);
	this->m_mapColours[ COLOUR_FIRE_BRICK ] = CGLColourHelper::CColour( "FireBrick", COLOUR_FIRE_BRICK, 0.698f, 0.133f, 0.133f);
	this->m_mapColours[ COLOUR_FLORAL_WHITE ] = CGLColourHelper::CColour( "FloralWhite", COLOUR_FLORAL_WHITE, 1.000f, 0.980f, 0.941f);
	this->m_mapColours[ COLOUR_FOREST_GREEN ] = CGLColourHelper::CColour( "ForestGreen", COLOUR_FOREST_GREEN, 0.133f, 0.545f, 0.133f);
	this->m_mapColours[ COLOUR_FUCHSIA ] = CGLColourHelper::CColour( "Fuchsia", COLOUR_FUCHSIA, 1.000f, 0.000f, 1.000f);
	this->m_mapColours[ COLOUR_GAINSBORO ] = CGLColourHelper::CColour( "Gainsboro", COLOUR_GAINSBORO, 0.863f, 0.863f, 0.863f);
	this->m_mapColours[ COLOUR_GHOST_WHITE ] = CGLColourHelper::CColour( "GhostWhite", COLOUR_GHOST_WHITE, 0.973f, 0.973f, 1.000f);
	this->m_mapColours[ COLOUR_GOLD ] = CGLColourHelper::CColour( "Gold", COLOUR_GOLD, 1.000f, 0.843f, 0.000f);
	this->m_mapColours[ COLOUR_GOLDEN_ROD ] = CGLColourHelper::CColour( "GoldenRod", COLOUR_GOLDEN_ROD, 0.855f, 0.647f, 0.125f);
	this->m_mapColours[ COLOUR_GRAY ] = CGLColourHelper::CColour( "Gray", COLOUR_GRAY, 0.502f, 0.502f, 0.502f);
	this->m_mapColours[ COLOUR_GREEN ] = CGLColourHelper::CColour( "Green", COLOUR_GREEN, 0.000f, 0.502f, 0.000f);
	this->m_mapColours[ COLOUR_GREEN_YELLOW ] = CGLColourHelper::CColour( "GreenYellow", COLOUR_GREEN_YELLOW, 0.678f, 1.000f, 0.184f);
	this->m_mapColours[ COLOUR_HONEY_DEW ] = CGLColourHelper::CColour( "HoneyDew", COLOUR_HONEY_DEW, 0.941f, 1.000f, 0.941f);
	this->m_mapColours[ COLOUR_HOT_PINK ] = CGLColourHelper::CColour( "HotPink", COLOUR_HOT_PINK, 1.000f, 0.412f, 0.706f);
	this->m_mapColours[ COLOUR_INDIAN_RED ] = CGLColourHelper::CColour( "IndianRed", COLOUR_INDIAN_RED, 0.804f, 0.361f, 0.361f);
	this->m_mapColours[ COLOUR_INDIGO ] = CGLColourHelper::CColour( "Indigo", COLOUR_INDIGO, 0.294f, 0.000f, 0.510f);
	this->m_mapColours[ COLOUR_IVORY ] = CGLColourHelper::CColour( "Ivory", COLOUR_IVORY, 1.000f, 1.000f, 0.941f);
	this->m_mapColours[ COLOUR_KHAKI ] = CGLColourHelper::CColour( "Khaki", COLOUR_KHAKI, 0.941f, 0.902f, 0.549f);
	this->m_mapColours[ COLOUR_LAVENDER ] = CGLColourHelper::CColour( "Lavender", COLOUR_LAVENDER, 0.902f, 0.902f, 0.980f);
	this->m_mapColours[ COLOUR_LAVENDER_BLUSH ] = CGLColourHelper::CColour( "LavenderBlush", COLOUR_LAVENDER_BLUSH, 1.000f, 0.941f, 0.961f);
	this->m_mapColours[ COLOUR_LAWN_GREEN ] = CGLColourHelper::CColour( "LawnGreen", COLOUR_LAWN_GREEN, 0.486f, 0.988f, 0.000f);
	this->m_mapColours[ COLOUR_LEMON_CHIFFON ] = CGLColourHelper::CColour( "LemonChiffon", COLOUR_LEMON_CHIFFON, 1.000f, 0.980f, 0.804f);
	this->m_mapColours[ COLOUR_LIGHT_BLUE ] = CGLColourHelper::CColour( "LightBlue", COLOUR_LIGHT_BLUE, 0.678f, 0.847f, 0.902f);
	this->m_mapColours[ COLOUR_LIGHT_CORAL ] = CGLColourHelper::CColour( "LightCoral", COLOUR_LIGHT_CORAL, 0.941f, 0.502f, 0.502f);
	this->m_mapColours[ COLOUR_LIGHT_CYAN ] = CGLColourHelper::CColour( "LightCyan", COLOUR_LIGHT_CYAN, 0.878f, 1.000f, 1.000f);
	this->m_mapColours[ COLOUR_LIGHT_GOLDEN_ROD_YELLOW ] = CGLColourHelper::CColour( "LightGoldenRodYellow", COLOUR_LIGHT_GOLDEN_ROD_YELLOW, 0.980f, 0.980f, 0.824f);
	this->m_mapColours[ COLOUR_LIGHT_GRAY ] = CGLColourHelper::CColour( "LightGray", COLOUR_LIGHT_GRAY, 0.827f, 0.827f, 0.827f);
	this->m_mapColours[ COLOUR_LIGHT_GREEN ] = CGLColourHelper::CColour( "LightGreen", COLOUR_LIGHT_GREEN, 0.565f, 0.933f, 0.565f);
	this->m_mapColours[ COLOUR_LIGHT_PINK ] = CGLColourHelper::CColour( "LightPink", COLOUR_LIGHT_PINK, 1.000f, 0.714f, 0.757f);
	this->m_mapColours[ COLOUR_LIGHT_SALMON ] = CGLColourHelper::CColour( "LightSalmon", COLOUR_LIGHT_SALMON, 1.000f, 0.627f, 0.478f);
	this->m_mapColours[ COLOUR_LIGHT_SEA_GREEN ] = CGLColourHelper::CColour( "LightSeaGreen", COLOUR_LIGHT_SEA_GREEN, 0.125f, 0.698f, 0.667f);
	this->m_mapColours[ COLOUR_LIGHT_SKY_BLUE ] = CGLColourHelper::CColour( "LightSkyBlue", COLOUR_LIGHT_SKY_BLUE, 0.529f, 0.808f, 0.980f);
	this->m_mapColours[ COLOUR_LIGHT_SLATE_GRAY ] = CGLColourHelper::CColour( "LightSlateGray", COLOUR_LIGHT_SLATE_GRAY, 0.467f, 0.533f, 0.600f);
	this->m_mapColours[ COLOUR_LIGHT_STEEL_BLUE ] = CGLColourHelper::CColour( "LightSteelBlue", COLOUR_LIGHT_STEEL_BLUE, 0.690f, 0.769f, 0.871f);
	this->m_mapColours[ COLOUR_LIGHT_YELLOW ] = CGLColourHelper::CColour( "LightYellow", COLOUR_LIGHT_YELLOW, 1.000f, 1.000f, 0.878f);
	this->m_mapColours[ COLOUR_LIME ] = CGLColourHelper::CColour( "Lime", COLOUR_LIME, 0.000f, 1.000f, 0.000f);
	this->m_mapColours[ COLOUR_LIME_GREEN ] = CGLColourHelper::CColour( "LimeGreen", COLOUR_LIME_GREEN, 0.196f, 0.804f, 0.196f);
	this->m_mapColours[ COLOUR_LINEN ] = CGLColourHelper::CColour( "Linen", COLOUR_LINEN, 0.980f, 0.941f, 0.902f);
	this->m_mapColours[ COLOUR_MAGENTA ] = CGLColourHelper::CColour( "Magenta", COLOUR_MAGENTA, 1.000f, 0.000f, 1.000f);
	this->m_mapColours[ COLOUR_MAROON ] = CGLColourHelper::CColour( "Maroon", COLOUR_MAROON, 0.502f, 0.000f, 0.000f);
	this->m_mapColours[ COLOUR_MEDIUM_AQUA_MARINE ] = CGLColourHelper::CColour( "MediumAquaMarine", COLOUR_MEDIUM_AQUA_MARINE, 0.400f, 0.804f, 0.667f);
	this->m_mapColours[ COLOUR_MEDIUM_BLUE ] = CGLColourHelper::CColour( "MediumBlue", COLOUR_MEDIUM_BLUE, 0.000f, 0.000f, 0.804f);
	this->m_mapColours[ COLOUR_MEDIUM_ORCHID ] = CGLColourHelper::CColour( "MediumOrchid", COLOUR_MEDIUM_ORCHID, 0.729f, 0.333f, 0.827f);
	this->m_mapColours[ COLOUR_MEDIUM_PURPLE ] = CGLColourHelper::CColour( "MediumPurple", COLOUR_MEDIUM_PURPLE, 0.576f, 0.439f, 0.859f);
	this->m_mapColours[ COLOUR_MEDIUM_SEA_GREEN ] = CGLColourHelper::CColour( "MediumSeaGreen", COLOUR_MEDIUM_SEA_GREEN, 0.235f, 0.702f, 0.443f);
	this->m_mapColours[ COLOUR_MEDIUM_SLATE_BLUE ] = CGLColourHelper::CColour( "MediumSlateBlue", COLOUR_MEDIUM_SLATE_BLUE, 0.482f, 0.408f, 0.933f);
	this->m_mapColours[ COLOUR_MEDIUM_SPRING_GREEN ] = CGLColourHelper::CColour( "MediumSpringGreen", COLOUR_MEDIUM_SPRING_GREEN, 0.000f, 0.980f, 0.604f);
	this->m_mapColours[ COLOUR_MEDIUM_TURQUOISE ] = CGLColourHelper::CColour( "MediumTurquoise", COLOUR_MEDIUM_TURQUOISE, 0.282f, 0.820f, 0.800f);
	this->m_mapColours[ COLOUR_MEDIUM_VIOLET_RED ] = CGLColourHelper::CColour( "MediumVioletRed", COLOUR_MEDIUM_VIOLET_RED, 0.780f, 0.082f, 0.522f);
	this->m_mapColours[ COLOUR_MIDNIGHT_BLUE ] = CGLColourHelper::CColour( "MidnightBlue", COLOUR_MIDNIGHT_BLUE, 0.098f, 0.098f, 0.439f);
	this->m_mapColours[ COLOUR_MINT_CREAM ] = CGLColourHelper::CColour( "MintCream", COLOUR_MINT_CREAM, 0.961f, 1.000f, 0.980f);
	this->m_mapColours[ COLOUR_MISTY_ROSE ] = CGLColourHelper::CColour( "MistyRose", COLOUR_MISTY_ROSE, 1.000f, 0.894f, 0.882f);
	this->m_mapColours[ COLOUR_MOCCASIN ] = CGLColourHelper::CColour( "Moccasin", COLOUR_MOCCASIN, 1.000f, 0.894f, 0.710f);
	this->m_mapColours[ COLOUR_NAVAJO_WHITE ] = CGLColourHelper::CColour( "NavajoWhite", COLOUR_NAVAJO_WHITE, 1.000f, 0.871f, 0.678f);
	this->m_mapColours[ COLOUR_NAVY ] = CGLColourHelper::CColour( "Navy", COLOUR_NAVY, 0.000f, 0.000f, 0.502f);
	this->m_mapColours[ COLOUR_OLD_LACE ] = CGLColourHelper::CColour( "OldLace", COLOUR_OLD_LACE, 0.992f, 0.961f, 0.902f);
	this->m_mapColours[ COLOUR_OLIVE ] = CGLColourHelper::CColour( "Olive", COLOUR_OLIVE, 0.502f, 0.502f, 0.000f);
	this->m_mapColours[ COLOUR_OLIVE_DRAB ] = CGLColourHelper::CColour( "OliveDrab", COLOUR_OLIVE_DRAB, 0.420f, 0.557f, 0.137f);
	this->m_mapColours[ COLOUR_ORANGE ] = CGLColourHelper::CColour( "Orange", COLOUR_ORANGE, 1.000f, 0.647f, 0.000f);
	this->m_mapColours[ COLOUR_ORANGE_RED ] = CGLColourHelper::CColour( "OrangeRed", COLOUR_ORANGE_RED, 1.000f, 0.271f, 0.000f);
	this->m_mapColours[ COLOUR_ORCHID ] = CGLColourHelper::CColour( "Orchid", COLOUR_ORCHID, 0.855f, 0.439f, 0.839f);
	this->m_mapColours[ COLOUR_PALE_GOLDEN_ROD ] = CGLColourHelper::CColour( "PaleGoldenRod", COLOUR_PALE_GOLDEN_ROD, 0.933f, 0.910f, 0.667f);
	this->m_mapColours[ COLOUR_PALE_GREEN ] = CGLColourHelper::CColour( "PaleGreen", COLOUR_PALE_GREEN, 0.596f, 0.984f, 0.596f);
	this->m_mapColours[ COLOUR_PALE_TURQUOISE ] = CGLColourHelper::CColour( "PaleTurquoise", COLOUR_PALE_TURQUOISE, 0.686f, 0.933f, 0.933f);
	this->m_mapColours[ COLOUR_PALE_VIOLET_RED ] = CGLColourHelper::CColour( "PaleVioletRed", COLOUR_PALE_VIOLET_RED, 0.859f, 0.439f, 0.576f);
	this->m_mapColours[ COLOUR_PAPAYA_WHIP ] = CGLColourHelper::CColour( "PapayaWhip", COLOUR_PAPAYA_WHIP, 1.000f, 0.937f, 0.835f);
	this->m_mapColours[ COLOUR_PEACH_PUFF ] = CGLColourHelper::CColour( "PeachPuff", COLOUR_PEACH_PUFF, 1.000f, 0.855f, 0.725f);
	this->m_mapColours[ COLOUR_PERU ] = CGLColourHelper::CColour( "Peru", COLOUR_PERU, 0.804f, 0.522f, 0.247f);
	this->m_mapColours[ COLOUR_PINK ] = CGLColourHelper::CColour( "Pink", COLOUR_PINK, 1.000f, 0.753f, 0.796f);
	this->m_mapColours[ COLOUR_PLUM ] = CGLColourHelper::CColour( "Plum", COLOUR_PLUM, 0.867f, 0.627f, 0.867f);
	this->m_mapColours[ COLOUR_POWDER_BLUE ] = CGLColourHelper::CColour( "PowderBlue", COLOUR_POWDER_BLUE, 0.690f, 0.878f, 0.902f);
	this->m_mapColours[ COLOUR_PURPLE ] = CGLColourHelper::CColour( "Purple", COLOUR_PURPLE, 0.502f, 0.000f, 0.502f);
	this->m_mapColours[ COLOUR_REBECCA_PURPLE ] = CGLColourHelper::CColour( "RebeccaPurple", COLOUR_REBECCA_PURPLE, 0.400f, 0.200f, 0.600f);
	this->m_mapColours[ COLOUR_RED ] = CGLColourHelper::CColour( "Red", COLOUR_RED, 1.000f, 0.000f, 0.000f);
	this->m_mapColours[ COLOUR_ROSY_BROWN ] = CGLColourHelper::CColour( "RosyBrown", COLOUR_ROSY_BROWN, 0.737f, 0.561f, 0.561f);
	this->m_mapColours[ COLOUR_ROYAL_BLUE ] = CGLColourHelper::CColour( "RoyalBlue", COLOUR_ROYAL_BLUE, 0.255f, 0.412f, 0.882f);
	this->m_mapColours[ COLOUR_SADDLE_BROWN ] = CGLColourHelper::CColour( "SaddleBrown", COLOUR_SADDLE_BROWN, 0.545f, 0.271f, 0.075f);
	this->m_mapColours[ COLOUR_SALMON ] = CGLColourHelper::CColour( "Salmon", COLOUR_SALMON, 0.980f, 0.502f, 0.447f);
	this->m_mapColours[ COLOUR_SANDY_BROWN ] = CGLColourHelper::CColour( "SandyBrown", COLOUR_SANDY_BROWN, 0.957f, 0.643f, 0.376f);
	this->m_mapColours[ COLOUR_SEA_GREEN ] = CGLColourHelper::CColour( "SeaGreen", COLOUR_SEA_GREEN, 0.180f, 0.545f, 0.341f);
	this->m_mapColours[ COLOUR_SEA_SHELL ] = CGLColourHelper::CColour( "SeaShell", COLOUR_SEA_SHELL, 1.000f, 0.961f, 0.933f);
	this->m_mapColours[ COLOUR_SIENNA ] = CGLColourHelper::CColour( "Sienna", COLOUR_SIENNA, 0.627f, 0.322f, 0.176f);
	this->m_mapColours[ COLOUR_SILVER ] = CGLColourHelper::CColour( "Silver", COLOUR_SILVER, 0.753f, 0.753f, 0.753f);
	this->m_mapColours[ COLOUR_SKY_BLUE ] = CGLColourHelper::CColour( "SkyBlue", COLOUR_SKY_BLUE, 0.529f, 0.808f, 0.922f);
	this->m_mapColours[ COLOUR_SLATE_BLUE ] = CGLColourHelper::CColour( "SlateBlue", COLOUR_SLATE_BLUE, 0.416f, 0.353f, 0.804f);
	this->m_mapColours[ COLOUR_SLATE_GRAY ] = CGLColourHelper::CColour( "SlateGray", COLOUR_SLATE_GRAY, 0.439f, 0.502f, 0.565f);
	this->m_mapColours[ COLOUR_SNOW ] = CGLColourHelper::CColour( "Snow", COLOUR_SNOW, 1.000f, 0.980f, 0.980f);
	this->m_mapColours[ COLOUR_SPRING_GREEN ] = CGLColourHelper::CColour( "SpringGreen", COLOUR_SPRING_GREEN, 0.000f, 1.000f, 0.498f);
	this->m_mapColours[ COLOUR_STEEL_BLUE ] = CGLColourHelper::CColour( "SteelBlue", COLOUR_STEEL_BLUE, 0.275f, 0.510f, 0.706f);
	this->m_mapColours[ COLOUR_TAN ] = CGLColourHelper::CColour( "Tan", COLOUR_TAN, 0.824f, 0.706f, 0.549f);
	this->m_mapColours[ COLOUR_TEAL ] = CGLColourHelper::CColour( "Teal", COLOUR_TEAL, 0.000f, 0.502f, 0.502f);
	this->m_mapColours[ COLOUR_THISTLE ] = CGLColourHelper::CColour( "Thistle", COLOUR_THISTLE, 0.847f, 0.749f, 0.847f);
	this->m_mapColours[ COLOUR_TOMATO ] = CGLColourHelper::CColour( "Tomato", COLOUR_TOMATO, 1.000f, 0.388f, 0.278f);
	this->m_mapColours[ COLOUR_TURQUOISE ] = CGLColourHelper::CColour( "Turquoise", COLOUR_TURQUOISE, 0.251f, 0.878f, 0.816f);
	this->m_mapColours[ COLOUR_VIOLET ] = CGLColourHelper::CColour( "Violet", COLOUR_VIOLET, 0.933f, 0.510f, 0.933f);
	this->m_mapColours[ COLOUR_WHEAT ] = CGLColourHelper::CColour( "Wheat", COLOUR_WHEAT, 0.961f, 0.871f, 0.702f);
	this->m_mapColours[ COLOUR_WHITE ] = CGLColourHelper::CColour( "White", COLOUR_WHITE, 1.000f, 1.000f, 1.000f);
	this->m_mapColours[ COLOUR_WHITE_SMOKE ] = CGLColourHelper::CColour( "WhiteSmoke", COLOUR_WHITE_SMOKE, 0.961f, 0.961f, 0.961f);
	this->m_mapColours[ COLOUR_YELLOW ] = CGLColourHelper::CColour( "Yellow", COLOUR_YELLOW, 1.000f, 1.000f, 0.000f);
	this->m_mapColours[ COLOUR_YELLOW_GREEN ] = CGLColourHelper::CColour( "YellowGreen", COLOUR_YELLOW_GREEN, 0.604f, 0.804f, 0.196f);

	this->m_mapColourNameToEnum[ "AliceBlue" ] = COLOUR_ALICE_BLUE;
	this->m_mapColourNameToEnum[ "AntiqueWhite" ] = COLOUR_ANTIQUE_WHITE;
	this->m_mapColourNameToEnum[ "Aqua" ] = COLOUR_AQUA;
	this->m_mapColourNameToEnum[ "Aquamarine" ] = COLOUR_AQUAMARINE;
	this->m_mapColourNameToEnum[ "Azure" ] = COLOUR_AZURE;
	this->m_mapColourNameToEnum[ "Beige" ] = COLOUR_BEIGE;
	this->m_mapColourNameToEnum[ "Bisque" ] = COLOUR_BISQUE;
	this->m_mapColourNameToEnum[ "Black" ] = COLOUR_BLACK;
	this->m_mapColourNameToEnum[ "BlanchedAlmond" ] = COLOUR_BLANCHED_ALMOND;
	this->m_mapColourNameToEnum[ "Blue" ] = COLOUR_BLUE;
	this->m_mapColourNameToEnum[ "BlueViolet" ] = COLOUR_BLUE_VIOLET;
	this->m_mapColourNameToEnum[ "Brown" ] = COLOUR_BROWN;
	this->m_mapColourNameToEnum[ "BurlyWood" ] = COLOUR_BURLY_WOOD;
	this->m_mapColourNameToEnum[ "CadetBlue" ] = COLOUR_CADET_BLUE;
	this->m_mapColourNameToEnum[ "Chartreuse" ] = COLOUR_CHARTREUSE;
	this->m_mapColourNameToEnum[ "Chocolate" ] = COLOUR_CHOCOLATE;
	this->m_mapColourNameToEnum[ "Coral" ] = COLOUR_CORAL;
	this->m_mapColourNameToEnum[ "CornflowerBlue" ] = COLOUR_CORNFLOWER_BLUE;
	this->m_mapColourNameToEnum[ "Cornsilk" ] = COLOUR_CORNSILK;
	this->m_mapColourNameToEnum[ "Crimson" ] = COLOUR_CRIMSON;
	this->m_mapColourNameToEnum[ "Cyan" ] = COLOUR_CYAN;
	this->m_mapColourNameToEnum[ "DarkBlue" ] = COLOUR_DARK_BLUE;
	this->m_mapColourNameToEnum[ "DarkCyan" ] = COLOUR_DARK_CYAN;
	this->m_mapColourNameToEnum[ "DarkGoldenRod" ] = COLOUR_DARK_GOLDEN_ROD;
	this->m_mapColourNameToEnum[ "DarkGray" ] = COLOUR_DARK_GRAY;
	this->m_mapColourNameToEnum[ "DarkGreen" ] = COLOUR_DARK_GREEN;
	this->m_mapColourNameToEnum[ "DarkKhaki" ] = COLOUR_DARK_KHAKI;
	this->m_mapColourNameToEnum[ "DarkMagenta" ] = COLOUR_DARK_MAGENTA;
	this->m_mapColourNameToEnum[ "DarkOliveGreen" ] = COLOUR_DARK_OLIVE_GREEN;
	this->m_mapColourNameToEnum[ "DarkOrange" ] = COLOUR_DARK_ORANGE;
	this->m_mapColourNameToEnum[ "DarkOrchid" ] = COLOUR_DARK_ORCHID;
	this->m_mapColourNameToEnum[ "DarkRed" ] = COLOUR_DARK_RED;
	this->m_mapColourNameToEnum[ "DarkSalmon" ] = COLOUR_DARK_SALMON;
	this->m_mapColourNameToEnum[ "DarkSeaGreen" ] = COLOUR_DARK_SEA_GREEN;
	this->m_mapColourNameToEnum[ "DarkSlateBlue" ] = COLOUR_DARK_SLATE_BLUE;
	this->m_mapColourNameToEnum[ "DarkSlateGray" ] = COLOUR_DARK_SLATE_GRAY;
	this->m_mapColourNameToEnum[ "DarkTurquoise" ] = COLOUR_DARK_TURQUOISE;
	this->m_mapColourNameToEnum[ "DarkViolet" ] = COLOUR_DARK_VIOLET;
	this->m_mapColourNameToEnum[ "DeepPink" ] = COLOUR_DEEP_PINK;
	this->m_mapColourNameToEnum[ "DeepSkyBlue" ] = COLOUR_DEEP_SKY_BLUE;
	this->m_mapColourNameToEnum[ "DimGray" ] = COLOUR_DIM_GRAY;
	this->m_mapColourNameToEnum[ "DodgerBlue" ] = COLOUR_DODGER_BLUE;
	this->m_mapColourNameToEnum[ "FireBrick" ] = COLOUR_FIRE_BRICK;
	this->m_mapColourNameToEnum[ "FloralWhite" ] = COLOUR_FLORAL_WHITE;
	this->m_mapColourNameToEnum[ "ForestGreen" ] = COLOUR_FOREST_GREEN;
	this->m_mapColourNameToEnum[ "Fuchsia" ] = COLOUR_FUCHSIA;
	this->m_mapColourNameToEnum[ "Gainsboro" ] = COLOUR_GAINSBORO;
	this->m_mapColourNameToEnum[ "GhostWhite" ] = COLOUR_GHOST_WHITE;
	this->m_mapColourNameToEnum[ "Gold" ] = COLOUR_GOLD;
	this->m_mapColourNameToEnum[ "GoldenRod" ] = COLOUR_GOLDEN_ROD;
	this->m_mapColourNameToEnum[ "Gray" ] = COLOUR_GRAY;
	this->m_mapColourNameToEnum[ "Green" ] = COLOUR_GREEN;
	this->m_mapColourNameToEnum[ "GreenYellow" ] = COLOUR_GREEN_YELLOW;
	this->m_mapColourNameToEnum[ "HoneyDew" ] = COLOUR_HONEY_DEW;
	this->m_mapColourNameToEnum[ "HotPink" ] = COLOUR_HOT_PINK;
	this->m_mapColourNameToEnum[ "IndianRed" ] = COLOUR_INDIAN_RED;
	this->m_mapColourNameToEnum[ "Indigo" ] = COLOUR_INDIGO;
	this->m_mapColourNameToEnum[ "Ivory" ] = COLOUR_IVORY;
	this->m_mapColourNameToEnum[ "Khaki" ] = COLOUR_KHAKI;
	this->m_mapColourNameToEnum[ "Lavender" ] = COLOUR_LAVENDER;
	this->m_mapColourNameToEnum[ "LavenderBlush" ] = COLOUR_LAVENDER_BLUSH;
	this->m_mapColourNameToEnum[ "LawnGreen" ] = COLOUR_LAWN_GREEN;
	this->m_mapColourNameToEnum[ "LemonChiffon" ] = COLOUR_LEMON_CHIFFON;
	this->m_mapColourNameToEnum[ "LightBlue" ] = COLOUR_LIGHT_BLUE;
	this->m_mapColourNameToEnum[ "LightCoral" ] = COLOUR_LIGHT_CORAL;
	this->m_mapColourNameToEnum[ "LightCyan" ] = COLOUR_LIGHT_CYAN;
	this->m_mapColourNameToEnum[ "LightGoldenRodYellow" ] = COLOUR_LIGHT_GOLDEN_ROD_YELLOW;
	this->m_mapColourNameToEnum[ "LightGray" ] = COLOUR_LIGHT_GRAY;
	this->m_mapColourNameToEnum[ "LightGreen" ] = COLOUR_LIGHT_GREEN;
	this->m_mapColourNameToEnum[ "LightPink" ] = COLOUR_LIGHT_PINK;
	this->m_mapColourNameToEnum[ "LightSalmon" ] = COLOUR_LIGHT_SALMON;
	this->m_mapColourNameToEnum[ "LightSeaGreen" ] = COLOUR_LIGHT_SEA_GREEN;
	this->m_mapColourNameToEnum[ "LightSkyBlue" ] = COLOUR_LIGHT_SKY_BLUE;
	this->m_mapColourNameToEnum[ "LightSlateGray" ] = COLOUR_LIGHT_SLATE_GRAY;
	this->m_mapColourNameToEnum[ "LightSteelBlue" ] = COLOUR_LIGHT_STEEL_BLUE;
	this->m_mapColourNameToEnum[ "LightYellow" ] = COLOUR_LIGHT_YELLOW;
	this->m_mapColourNameToEnum[ "Lime" ] = COLOUR_LIME;
	this->m_mapColourNameToEnum[ "LimeGreen" ] = COLOUR_LIME_GREEN;
	this->m_mapColourNameToEnum[ "Linen" ] = COLOUR_LINEN;
	this->m_mapColourNameToEnum[ "Magenta" ] = COLOUR_MAGENTA;
	this->m_mapColourNameToEnum[ "Maroon" ] = COLOUR_MAROON;
	this->m_mapColourNameToEnum[ "MediumAquaMarine" ] = COLOUR_MEDIUM_AQUA_MARINE;
	this->m_mapColourNameToEnum[ "MediumBlue" ] = COLOUR_MEDIUM_BLUE;
	this->m_mapColourNameToEnum[ "MediumOrchid" ] = COLOUR_MEDIUM_ORCHID;
	this->m_mapColourNameToEnum[ "MediumPurple" ] = COLOUR_MEDIUM_PURPLE;
	this->m_mapColourNameToEnum[ "MediumSeaGreen" ] = COLOUR_MEDIUM_SEA_GREEN;
	this->m_mapColourNameToEnum[ "MediumSlateBlue" ] = COLOUR_MEDIUM_SLATE_BLUE;
	this->m_mapColourNameToEnum[ "MediumSpringGreen" ] = COLOUR_MEDIUM_SPRING_GREEN;
	this->m_mapColourNameToEnum[ "MediumTurquoise" ] = COLOUR_MEDIUM_TURQUOISE;
	this->m_mapColourNameToEnum[ "MediumVioletRed" ] = COLOUR_MEDIUM_VIOLET_RED;
	this->m_mapColourNameToEnum[ "MidnightBlue" ] = COLOUR_MIDNIGHT_BLUE;
	this->m_mapColourNameToEnum[ "MintCream" ] = COLOUR_MINT_CREAM;
	this->m_mapColourNameToEnum[ "MistyRose" ] = COLOUR_MISTY_ROSE;
	this->m_mapColourNameToEnum[ "Moccasin" ] = COLOUR_MOCCASIN;
	this->m_mapColourNameToEnum[ "NavajoWhite" ] = COLOUR_NAVAJO_WHITE;
	this->m_mapColourNameToEnum[ "Navy" ] = COLOUR_NAVY;
	this->m_mapColourNameToEnum[ "OldLace" ] = COLOUR_OLD_LACE;
	this->m_mapColourNameToEnum[ "Olive" ] = COLOUR_OLIVE;
	this->m_mapColourNameToEnum[ "OliveDrab" ] = COLOUR_OLIVE_DRAB;
	this->m_mapColourNameToEnum[ "Orange" ] = COLOUR_ORANGE;
	this->m_mapColourNameToEnum[ "OrangeRed" ] = COLOUR_ORANGE_RED;
	this->m_mapColourNameToEnum[ "Orchid" ] = COLOUR_ORCHID;
	this->m_mapColourNameToEnum[ "PaleGoldenRod" ] = COLOUR_PALE_GOLDEN_ROD;
	this->m_mapColourNameToEnum[ "PaleGreen" ] = COLOUR_PALE_GREEN;
	this->m_mapColourNameToEnum[ "PaleTurquoise" ] = COLOUR_PALE_TURQUOISE;
	this->m_mapColourNameToEnum[ "PaleVioletRed" ] = COLOUR_PALE_VIOLET_RED;
	this->m_mapColourNameToEnum[ "PapayaWhip" ] = COLOUR_PAPAYA_WHIP;
	this->m_mapColourNameToEnum[ "PeachPuff" ] = COLOUR_PEACH_PUFF;
	this->m_mapColourNameToEnum[ "Peru" ] = COLOUR_PERU;
	this->m_mapColourNameToEnum[ "Pink" ] = COLOUR_PINK;
	this->m_mapColourNameToEnum[ "Plum" ] = COLOUR_PLUM;
	this->m_mapColourNameToEnum[ "PowderBlue" ] = COLOUR_POWDER_BLUE;
	this->m_mapColourNameToEnum[ "Purple" ] = COLOUR_PURPLE;
	this->m_mapColourNameToEnum[ "RebeccaPurple" ] = COLOUR_REBECCA_PURPLE;
	this->m_mapColourNameToEnum[ "Red" ] = COLOUR_RED;
	this->m_mapColourNameToEnum[ "RosyBrown" ] = COLOUR_ROSY_BROWN;
	this->m_mapColourNameToEnum[ "RoyalBlue" ] = COLOUR_ROYAL_BLUE;
	this->m_mapColourNameToEnum[ "SaddleBrown" ] = COLOUR_SADDLE_BROWN;
	this->m_mapColourNameToEnum[ "Salmon" ] = COLOUR_SALMON;
	this->m_mapColourNameToEnum[ "SandyBrown" ] = COLOUR_SANDY_BROWN;
	this->m_mapColourNameToEnum[ "SeaGreen" ] = COLOUR_SEA_GREEN;
	this->m_mapColourNameToEnum[ "SeaShell" ] = COLOUR_SEA_SHELL;
	this->m_mapColourNameToEnum[ "Sienna" ] = COLOUR_SIENNA;
	this->m_mapColourNameToEnum[ "Silver" ] = COLOUR_SILVER;
	this->m_mapColourNameToEnum[ "SkyBlue" ] = COLOUR_SKY_BLUE;
	this->m_mapColourNameToEnum[ "SlateBlue" ] = COLOUR_SLATE_BLUE;
	this->m_mapColourNameToEnum[ "SlateGray" ] = COLOUR_SLATE_GRAY;
	this->m_mapColourNameToEnum[ "Snow" ] = COLOUR_SNOW;
	this->m_mapColourNameToEnum[ "SpringGreen" ] = COLOUR_SPRING_GREEN;
	this->m_mapColourNameToEnum[ "SteelBlue" ] = COLOUR_STEEL_BLUE;
	this->m_mapColourNameToEnum[ "Tan" ] = COLOUR_TAN;
	this->m_mapColourNameToEnum[ "Teal" ] = COLOUR_TEAL;
	this->m_mapColourNameToEnum[ "Thistle" ] = COLOUR_THISTLE;
	this->m_mapColourNameToEnum[ "Tomato" ] = COLOUR_TOMATO;
	this->m_mapColourNameToEnum[ "Turquoise" ] = COLOUR_TURQUOISE;
	this->m_mapColourNameToEnum[ "Violet" ] = COLOUR_VIOLET;
	this->m_mapColourNameToEnum[ "Wheat" ] = COLOUR_WHEAT;
	this->m_mapColourNameToEnum[ "White" ] = COLOUR_WHITE;
	this->m_mapColourNameToEnum[ "WhiteSmoke" ] = COLOUR_WHITE_SMOKE;
	this->m_mapColourNameToEnum[ "Yellow" ] = COLOUR_YELLOW;
	this->m_mapColourNameToEnum[ "YellowGreen" ] = COLOUR_YELLOW_GREEN;

	// Generate the random lookup
	for ( std::map< CGLColourHelper::enumColours, CGLColourHelper::CColour >::iterator itColour = this->m_mapColours.begin();
		  itColour != this->m_mapColours.end(); itColour++ )
	{
		this->m_vecRandomColourEnumLookup.push_back( itColour->first );
	}
	// Scramble them
	std::random_shuffle( this->m_vecRandomColourEnumLookup.begin(), this->m_vecRandomColourEnumLookup.begin() );
	// Start the 'next' loop up at the start of the vector
	this->m_nextRandomIndex = 0;

		static const float DEFAULT_FLOAT_EPSION_COMPARE; // = 0.001f;
	this->floatEpsilonCompare = CGLColourHelper::DEFAULT_FLOAT_EPSION_COMPARE;// = DEFAULT_EPSION_COMPARE


	return;
}

/*static*/ const float CGLColourHelper::DEFAULT_FLOAT_EPSION_COMPARE = 0.001f;

CGLColourHelper::enumColours CGLColourHelper::getRandomColourEnum(void)
{
	CGLColourHelper::enumColours randColourEnum = this->m_vecRandomColourEnumLookup[this->m_nextRandomIndex];
	this->m_nextRandomIndex++;
	if ( this->m_nextRandomIndex >= this->m_vecRandomColourEnumLookup.size() )
	{
		this->m_nextRandomIndex = 0;
	}
	return randColourEnum;
}

CGLColourHelper::CColour CGLColourHelper::getRandomColour(void)
{
	CColour randColour;
	randColour.rgb.r = this->getRand(0.0f, 1.0f);
	randColour.rgb.g = this->getRand(0.0f, 1.0f);
	randColour.rgb.b = this->getRand(0.0f, 1.0f);
	randColour.enumName = COLOUR_CUSTOM;
	return randColour;
}

glm::vec3 CGLColourHelper::getRandomColourRGB(void)
{
	return this->getRandomColour().rgb;
}

glm::vec4 CGLColourHelper::getRandomColourRGBA(void)
{
	return glm::vec4( this->getRandomColourRGB(), 1.0f );
}


void CGLColourHelper::ShuffleRandomColours(void)
{
	std::random_shuffle( this->m_vecRandomColourEnumLookup.begin(), this->m_vecRandomColourEnumLookup.begin() );
	return;
}


glm::vec3 CGLColourHelper::getColourRGB( CGLColourHelper::enumColours colourEnum )
{
	CColour theColour = this->getColour( colourEnum );
	return theColour.rgb;
}

glm::vec3 CGLColourHelper::getColourRGB( std::string colourName )
{
	CGLColourHelper::CColour returnColour = this->getColour( colourName );
	return returnColour.rgb;
}

glm::vec4 CGLColourHelper::getColourRGBA( CGLColourHelper::enumColours colourEnum )
{
	return glm::vec4( this->getColourRGB( colourEnum), 1.0f );
}

glm::vec4 CGLColourHelper::getColourRGBA( std::string colourName )
{
	return glm::vec4( this->getColourRGB( colourName ), 1.0f );
}

CGLColourHelper::CColour CGLColourHelper::getColour( std::string colourName )
{
	CGLColourHelper::enumColours colourEnum = this->getColourEnumFromName( colourName );
	if ( colourEnum == CGLColourHelper::COLOUR_UNKNOWN )
	{	// Didn't find it
		return this->m_getUnknownColour();
	}
	// Look up the colour
	CGLColourHelper::CColour returnColour = this->getColour( colourEnum );
	return returnColour;
}

CGLColourHelper::CColour CGLColourHelper::getColour( CGLColourHelper::enumColours colourEnum )
{
	// 
	std::map< CGLColourHelper::enumColours, CGLColourHelper::CColour >::iterator itColour = m_mapColours.find( colourEnum );
	if ( itColour == this->m_mapColours.end() )
	{	// Didn't find a match (should "never" happen as it's an enum... but you could pass an int, I suppose
		return this->m_getUnknownColour();
	}
	// Found it
	return itColour->second;
}

CGLColourHelper::CColour CGLColourHelper::m_getUnknownColour(void)
{
	CGLColourHelper::CColour unknownColour = CGLColourHelper::CColour();
	unknownColour.enumName = COLOUR_UNKNOWN;
	unknownColour.name = "Unknown";
	unknownColour.rgb = glm::vec3( 0.0f, 0.0f, 0.0f );
	return unknownColour;
}


std::string CGLColourHelper::getColourNameFromEnum( CGLColourHelper::enumColours colourEnum )
{
	CGLColourHelper::CColour returnColour = this->getColour( colourEnum );
	return returnColour.name;
}

CGLColourHelper::enumColours CGLColourHelper::getColourEnumFromName( std::string sColour )
{
	std::map< std::string, CGLColourHelper::enumColours >::iterator itColour = this->m_mapColourNameToEnum.find( sColour );
	if ( itColour == this->m_mapColourNameToEnum.end() )
	{	// Didn't find it
		return CGLColourHelper::COLOUR_UNKNOWN;
	}
	return itColour->second;
}

glm::vec3 CGLColourHelper::getHSLfromRGB(glm::vec3 RGB)
{
	// Taken from: http://www.easyrgb.com/index.php?X=MATH&H=18#text18
	
	//var_R = ( R / 255 )                     //RGB from 0 to 255
	//var_G = ( G / 255 )
	//var_B = ( B / 255 )

	float H = 0.0f;
	float S = 0.0f;
	float L = 0.0f;


	float var_Min = glm::min( RGB.r, glm::min( RGB.g, RGB.b ) );	// Min. value of RGB
	float var_Max = glm::max( RGB.r, glm::max( RGB.g, RGB.b ) );	//Max. value of RGB
	float del_Max = var_Max - var_Min;			//Delta RGB value

	L = ( var_Max + var_Min ) / 2.0f;

	if ( this->floatIsZero( del_Max ) )                    //This is a gray, no chroma...
	{
		H = 0.0f;                                //HSL results from 0 to 1
		S = 0.0f;
	}
	else                                    //Chromatic data...
	{
		if ( L < 0.5f ) 
		{
			S = del_Max / ( var_Max + var_Min );
		}
		else           
		{
			S = del_Max / ( 2.0f - var_Max - var_Min );
		}

		float del_R = ( ( ( var_Max - RGB.r ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
		float del_G = ( ( ( var_Max - RGB.g ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
		float del_B = ( ( ( var_Max - RGB.b ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;

		if ( floatIsEqual( RGB.r, var_Max ) )		{	H = del_B - del_G; }
		else if ( floatIsEqual( RGB.g, var_Max ) )	{	H = ( 1.0f / 3.0f ) + del_R - del_B;	}
		else if ( floatIsEqual( RGB.b, var_Max ) ) 	{	H = ( 2.0f / 3.0f ) + del_G - del_R;	}

		if ( H < 0.0f ) { H += 1.0f; }
		if ( H > 1.0f ) { H -= 1.0f; }
	}

	if ( this->floatIsZero(H) ) { H = 0.0f; }
	if ( this->floatIsZero(S) ) { S = 0.0f; }
	if ( this->floatIsZero(L) ) { L = 0.0f; }

	// return HSL
	return glm::vec3( H, S, L );	
}
	
// The alpha value is ignored
glm::vec4 CGLColourHelper::getHSLfromRGBA(glm::vec4 RGBA)
{
	glm::vec3 HSL = this->getHSLfromRGB( glm::vec3( RGBA ) );
	return glm::vec4( HSL, 1.0f );
}
	
glm::vec3 CGLColourHelper::getRBGfromHSL(glm::vec3 HSL)
{
	// Taken from: http://www.easyrgb.com/index.php?X=MATH&H=18#text18

	float H = HSL.x;
	float S = HSL.y;
	float L = HSL.z;

	glm::vec3 RGB;

	if ( this->floatIsEqual( S, 0.0f ) )                      //HSL from 0 to 1
	{
		RGB.r = L;                      //RGB results from 0 to 255
		RGB.g = L;
		RGB.b = L;
	}
	else
	{
		float var_2;
		if ( L < 0.5f ) 
		{
			var_2 = L * ( 1.0f + S );
		}
		else           
		{
			var_2 = ( L + S ) - ( S * L );
		}

		float var_1 = 2.0f * L - var_2;

		RGB.r = this->getRGBfromHue( var_1, var_2, H + ( 1.0f / 3.0f ) ); 
		RGB.g = this->getRGBfromHue( var_1, var_2, H );
		RGB.b = this->getRGBfromHue( var_1, var_2, H - ( 1.0f / 3.0f ) );
	}

	if ( this->floatIsZero( RGB.r ) ) { RGB.r = 0.0f; }	// clamp to zero
	if ( this->floatIsZero( RGB.g ) ) { RGB.g = 0.0f; } // clamp to zero
	if ( this->floatIsZero( RGB.b ) ) { RGB.b = 0.0f; } // clamp to zero

	return RGB;
}

// Hue_2_RGB( v1, v2, vH )     //Function Hue_2_RGB
float CGLColourHelper::getRGBfromHue( float v1, float v2, float vH )
{
	// Taken from: http://www.easyrgb.com/index.php?X=MATH&H=18#text18

	if ( vH < 0.0f ) { vH += 1.0f; }
	if ( vH > 1.0f ) { vH -= 1.0f; }
	if ( ( 6.0f * vH ) < 1.0f ) 
	{
		return ( v1 + ( v2 - v1 ) * 6.0f * vH );
	}
	if ( ( 2.0f * vH ) < 1.0f ) 
	{
		return ( v2 );
	}
	if ( ( 3.0f * vH ) < 2.0f ) 
	{
		return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );
	}
	return ( v1 );
}

// The alpha value is ignored
glm::vec4 CGLColourHelper::getRBGAfromHSL(glm::vec3 HSL)
{
	return glm::vec4( this->getRBGfromHSL( HSL ), 1.0f );
}


glm::vec3 CGLColourHelper::getComplimentaryRGB(glm::vec3 RGB)
{
	// Taken from: http://serennu.com/colour/colourcalculator.php

	glm::vec3 HSL = this->getHSLfromRGB( RGB );
	HSL.x = HSL.x + 0.5f;	// 180 degrees "opposite"
	if ( HSL.x > 1.0f )	
	{  
		HSL.x -= 1.0f; 
	}
	return this->getRBGfromHSL( HSL );
}

// The alpha value is ignored
glm::vec4 CGLColourHelper::getComplimentaryRGBA(glm::vec4 RGBA)
{
	return glm::vec4( glm::vec3( RGBA.r, RGBA.g, RGBA.b ), 1.0f );
}
