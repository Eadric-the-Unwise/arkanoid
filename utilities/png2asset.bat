@REM C:\c_code\gbdk\bin\png2mtspr C:\c_code\projects\detective\detective_metasprite\tiles\tile_detectivewalk.png -sh 16 -spr8x8 -c C:\c_code\projects\detective\detective_metasprite\tiles\tile_detectivewalk.c

@REM C:\c_code\gbdk\bin\png2mtspr C:\c_code\projects\detective\detective_metasprite\tiles\cig_shine.png -sh 16 -spr8x8 -c C:\c_code\projects\detective\detective_metasprite\tiles\cig_shine.c


@REM C:\c_code\gbdk\bin\png2mtspr C:\c_code\projects\detective\detective_metasprite\tiles\smoke.png -sh 16 -spr8x8 -c C:\c_code\projects\detective\detective_metasprite\tiles\smoke.c

@REM C:\c_code\gbdk\bin\png2mtspr ..\tiles\smoke.png -sw 16 -sh 16 -spr8x16 -sp 0x10

@REM C:\c_code\gbdk\bin\png2mtspr ..\tiles\smoke.png -sw 16 -sh 16 -spr8x16

@REM C:\c_code\gbdk\bin\png2mtspr ..\tiles\tile_detectivewalk.png -sw 16 -sh 16 -spr8x16

@REM C:\c_code\gbdk\bin\png2mtspr ..\tiles\cig_shine.png -sw 16 -sh 16 -spr8x16 -sp 0x10

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\detective.png -sw 16 -sh 16 -spr8x16

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\detective_large_stand.png -sw 24 -sh 32 -spr8x16

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\detective_platform_stand.png -sw 24 -sh 32 -spr8x16

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\detective_large.png -sw 24 -sh 32 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\elevator.png -sw 48 -sh 16 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\NPC_electric.png -sw 16 -sh 16 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\detective_16.png -sw 16 -sh 16 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\lady1.png -sw 16 -sh 16 -sp 0x10 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\thug1.png -sw 16 -sh 16 -sp 0x10 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\homeless.png -sw 16 -sh 16 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\larry.png -sw 16 -sh 16 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2mtspr res\tiles\staff1.png -sw 16 -sh 16 -sp 0x10 -spr8x16 -b 200

@REM C:\c_code\gbdk\bin\png2asset res\tiles\bubble_exlamation_V1.png -sw 16 -sh 16 -sp -spr8x16 -b 200 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\bubble_question_V1.png -sw 16 -sh 16 -sp -spr8x16 -b 200 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\tileset.png -sw 16 -sh 16 -sp -spr8x16 -b 1 
@REM C:\c_code\gbdk\bin\png2asset res\tiles\bullet.png -px -8 -py -16 -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order
@REM C:\c_code\gbdk\bin\png2asset res\tiles\galaga.png -px -8 -py -16 -sw 16 -sh 16 -sp 0x00 -spr8x16 -b 1 -keep_palette_order

@REM C:\c_code\gbdk\bin\png2asset res\tiles\frogger.png -px -8 -py -16 -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order 
@REM C:\c_code\gbdk\bin\png2asset res\tiles\frogger.png -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\log_frog.png -px -8 -py -16 -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\paddle.png -px -8 -py -16 -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\ball.png -px -8 -py -16 -sw 16 -sh 16 -sp -spr8x16 -b 1 0x00 -keep_palette_order 

@REM C:\c_code\gbdk\bin\png2asset res\tiles\paddle.png -sw 24 -sh 8 -px -8 -py -16 -spr8x8 -b 1 0x00 -keep_palette_order 

C:\c_code\gbdk\bin\png2asset res\tiles\ball.png -sw 8 -sh 8 -px -8 -py -16 -spr8x8 -b 1 0x00 -keep_palette_order 


@REM (-px -8 -py -16 seems to fix offset issues on both 8x8y and 28x8y)
@REM -c ouput file (default: <png file>.c)
@REM -sw <width> metasprites width size (default: png width)
@REM -sh <height> metasprites height size (default: png height)
@REM -sp <props> change default for sprite OAM property bytes (in hex) (default: 0x00)
@REM -px <x coord> metasprites pivot x coordinate (default: metasprites width / 2)
@REM -py <y coord> metasprites pivot y coordinate (default: metasprites height / 2)
@REM -pw <width> metasprites collision rect width (default: metasprites width)
@REM -ph <height> metasprites collision rect height (default: metasprites height)
@REM -spr8x8 use SPRITES_8x8
@REM -spr8x16 use SPRITES_8x16 (this is the default)
@REM -spr16x16msx use SPRITES_16x16
@REM -b <bank> bank (default 0)
@REM -keep_palette_order use png palette
@REM -noflip disable tile flip
@REM -map Export as map (tileset + bg)
@REM -use_map_attributes Use CGB BG Map attributes
@REM -use_nes_attributes Use NES BG Map attributes
@REM -use_nes_colors Convert RGB color values to NES PPU colors
@REM -use_structs Group the exported info into structs (default: false) (used by ZGB Game Engine)
@REM -bpp bits per pixel: 1, 2, 4 (default: 2)
@REM -max_palettes max number of palettes allowed (default: 8)
@REM (note: max colors = max_palettes x num colors per palette)
@REM -pack_mode gb, sgb, sms, 1bpp (default: gb)
@REM -tile_origin tile index offset for maps (default: 0)
@REM -tiles_only export tile data only
@REM -maps_only export map tilemap only
@REM -metasprites_only export metasprite descriptors only
@REM -source_tileset use source tileset (image with common tiles)
@REM -keep_duplicate_tiles do not remove duplicate tiles (default: not enabled)
@REM -bin export to binary format
@REM -transposed export transposed (column-by-column instead of row-by-row)