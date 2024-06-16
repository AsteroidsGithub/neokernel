#ifndef CONSTANTS_H
#define CONSTANTS_H

#define gfxColor(r, g, b) ((r << 16) | (g << 8) | (b << 0))
#define gfxColorHex(hex) gfxColor(((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), ((hex >> 0) & 0xFF))

#define COLOR_BLUE gfxColorHex(0x0D98BA)
#define COLOR_GREEN gfxColorHex(0x0A5E3A)
#define COLOR_RED gfxColorHex(0xD93A3B)
#define COLOR_YELLOW gfxColorHex(0xF7CB15)
#define COLOR_WHITE gfxColorHex(0xFFFFFF)
#define COLOR_BLACK gfxColorHex(0x000000)

#endif