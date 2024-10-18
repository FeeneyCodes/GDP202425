@REM You may have to update the directory for the source PNG and the exe
@REM
"../../../x64/Release/SpritePNGtoCubePixelHelper.exe"  "../../textures/Donkey Kong/Sprites (isolated)/DonkeyKong_Level_0_with_items.png" pixelSize:1 setBackgroundColour:0:0:0 cropToBackgroundColour noBackgroundColourBlocks
"../../../x64/Release/SpritePNGtoCubePixelHelper.exe"  "../../textures/Donkey Kong/Sprites (isolated)/DonkeyKong_Level_1_with_items.png" pixelSize:1 setBackgroundColour:0:0:0 cropToBackgroundColour noBackgroundColourBlocks
"../../../x64/Release/SpritePNGtoCubePixelHelper.exe"  "../../textures/Donkey Kong/Sprites (isolated)/DonkeyKong_Level_2_with_items.png" pixelSize:1 setBackgroundColour:0:0:0 cropToBackgroundColour noBackgroundColourBlocks
"../../../x64/Release/SpritePNGtoCubePixelHelper.exe"  "../../textures/Donkey Kong/Sprites (isolated)/DonkeyKong_Level_3_with_items.png" pixelSize:1 setBackgroundColour:0:0:0 cropToBackgroundColour noBackgroundColourBlocks
copy "..\..\textures\Donkey Kong\Sprites (isolated)\*.ply" "*.ply"
del "..\..\textures\Donkey Kong\Sprites (isolated)\*.ply"
pause
