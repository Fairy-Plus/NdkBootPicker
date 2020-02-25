//
//  NdkBootPicker.h
//
//
//  Created by N-D-K on 1/24/20.
//

#ifndef NdkBootPicker_h
#define NdkBootPicker_h

#define NDK_BOOTPICKER_VERSION   "0.1.1"

STATIC
BOOLEAN
mAllowSetDefault;

STATIC
UINTN
mDefaultEntry;

STATIC
BOOLEAN
mHideAuxiliary;

/*========== Graphic UI Begin ==========*/

typedef struct _NDK_UI_IMAGE {
  UINT16                          Width;
  UINT16                          Height;
  BOOLEAN                         IsAlpha;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL   *Bitmap;
} NDK_UI_IMAGE;

STATIC
EFI_GRAPHICS_OUTPUT_PROTOCOL *
mGraphicsOutput;

STATIC
EFI_UGA_DRAW_PROTOCOL *
mUgaDraw;

STATIC
INTN
mScreenWidth;

STATIC
INTN
mScreenHeight;

STATIC
INTN
mFontWidth = 9;

STATIC
INTN
mFontHeight = 18;

STATIC
INTN
mTextHeight = 19;

STATIC
INTN
mTextScale = 0;  // not actual scale, will be set after getting screen resolution. (16 will be no scaling, 28 will be for 4k screen)

STATIC
INTN
mUiScale = 0;

STATIC
UINTN
mIconSpaceSize;  // Default 136 pixels space to contain icons with size 128x128.

STATIC
UINTN
mIconPaddingSize;

STATIC
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *
mFileSystem = NULL;

NDK_UI_IMAGE *
mFontImage = NULL;

BOOLEAN
mProportional = TRUE;

BOOLEAN
mDarkMode = TRUE;

STATIC
NDK_UI_IMAGE *
mBackgroundImage = NULL;

STATIC
NDK_UI_IMAGE *
mMenuImage = NULL;

BOOLEAN
mSelectorUsed = TRUE;

BOOLEAN
mAlphaEffect = TRUE;

STATIC
INTN
mMenuFadeIntensity = 150;     // ranging from 0 to 255 0 = completely disappear, 255 = no fading.

/* Colors are now customized by the optional small 16x16 pixels png color example files in icons folder (Can be anysize only 1st pixels will be used for color setting).
   font_color.png (Entry discription color and selection color)
   font_color_alt.png (All other text on screen)
   background_color.png (Background color)
   Background.png (Wallpaper bacground instead, preferly matching with screen resolution setting.)
 
   Background.png will be checked first, will use it if found in icons foler, if not found, then background_color.png will be checked,
   if not found then 1st pixel color (top/left pixel) of fontn.
 */

/*=========== Default colors settings ==============*/

EFI_GRAPHICS_OUTPUT_BLT_PIXEL mTransparentPixel  = {0x00, 0x00, 0x00, 0x00};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL mBlackPixel  = {0x00, 0x00, 0x00, 0xff};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL mLowWhitePixel  = {0xb8, 0xbd, 0xbf, 0xff};

// Selection and Entry's description font color
EFI_GRAPHICS_OUTPUT_BLT_PIXEL *mFontColorPixel = &mLowWhitePixel;

// Background color
EFI_GRAPHICS_OUTPUT_BLT_PIXEL *mBackgroundPixel = &mBlackPixel;

//
// Text Rendering
//

#define ALIGN_64 __attribute__((__aligned__(8)))
#define DEFINE_DATA(font) UINT8 ALIGN_64 const font[] =
#define DEFINE_SIZE(font) UINTN const font##_size = sizeof (font);
#define ACCESS_DATA(font) ((UINT8*) font)
#define ACCESS_SIZE(font) font##_size
#define CHAR_WIDTH (9)

// size = 1549;
DEFINE_DATA(font_data) {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x01, 0x20,
  0x01, 0x03, 0x00, 0x00, 0x00, 0x2e, 0x68, 0x6b, 0xea, 0x00, 0x00, 0x00,
  0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc, 0x61,
  0x05, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce,
  0x1c, 0xe9, 0x00, 0x00, 0x00, 0x06, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x55, 0xc2, 0xd3, 0x7e, 0x00, 0x00, 0x05, 0x94,
  0x49, 0x44, 0x41, 0x54, 0x58, 0xc3, 0xed, 0x98, 0xbf, 0x6f, 0x1b, 0x37,
  0x14, 0xc7, 0x1f, 0x79, 0xb4, 0x8e, 0x97, 0x26, 0x39, 0x5a, 0x30, 0x0a,
  0x01, 0x0d, 0x2c, 0x2a, 0x51, 0x5d, 0x07, 0xe8, 0x10, 0x14, 0x1d, 0x3c,
  0xb8, 0x11, 0x4f, 0xd5, 0xa0, 0x74, 0xd2, 0xd0, 0x66, 0x2c, 0x0c, 0x74,
  0xed, 0x90, 0xd1, 0x83, 0x20, 0x50, 0x3f, 0x06, 0x0f, 0x19, 0x3c, 0x76,
  0xe8, 0xe0, 0xb1, 0x7f, 0xc6, 0x25, 0x53, 0xff, 0x8c, 0xfb, 0x13, 0x34,
  0x6a, 0x08, 0x8a, 0xbe, 0x47, 0xf2, 0x74, 0x27, 0x4b, 0x6e, 0x0b, 0xa4,
  0x68, 0xec, 0x22, 0x37, 0xf8, 0xa8, 0x0f, 0xde, 0x91, 0x7c, 0x8f, 0xfc,
  0xf2, 0xf1, 0x19, 0xe0, 0x8e, 0x3e, 0xed, 0xa8, 0x18, 0xa7, 0xd3, 0xe5,
  0xf3, 0x38, 0x5f, 0xb5, 0xf1, 0x27, 0x36, 0x01, 0x9b, 0x1f, 0x02, 0x7f,
  0x7c, 0xfe, 0x7a, 0x75, 0xaa, 0xe6, 0x87, 0xc0, 0x77, 0xe1, 0x69, 0x02,
  0x18, 0x7c, 0xa9, 0x4d, 0x6a, 0x9b, 0xc2, 0x9a, 0xaf, 0x98, 0x55, 0x9c,
  0x95, 0x48, 0x12, 0xee, 0x8a, 0xe9, 0xf2, 0x3b, 0x6e, 0xb4, 0x00, 0x5b,
  0xc7, 0x20, 0x66, 0xc3, 0xaf, 0xb9, 0xc1, 0x1f, 0x26, 0x60, 0xe5, 0x70,
  0xfa, 0xd6, 0x08, 0x66, 0x09, 0x77, 0x79, 0x0d, 0x8b, 0x99, 0x91, 0x11,
  0x7d, 0x6a, 0x5a, 0x1e, 0x6b, 0x8f, 0xa7, 0x4b, 0x29, 0xae, 0x08, 0x4f,
  0x52, 0x0b, 0xbd, 0x12, 0xa7, 0xf9, 0x50, 0x09, 0x53, 0xb3, 0xf6, 0x63,
  0x08, 0x3b, 0xfc, 0xd4, 0xe3, 0x6e, 0x85, 0xdd, 0x4c, 0x9e, 0x22, 0xf6,
  0x13, 0x34, 0xc0, 0xdc, 0xdb, 0xf5, 0x7d, 0x14, 0x5d, 0x81, 0x77, 0xa7,
  0xc4, 0x55, 0x67, 0xde, 0xe9, 0x5a, 0x00, 0xcc, 0xed, 0x5d, 0xb1, 0x14,
  0xcc, 0x69, 0x6c, 0x65, 0x8f, 0xe5, 0xef, 0x52, 0x56, 0x04, 0x78, 0x0e,
  0xca, 0xe6, 0x7d, 0x69, 0x5a, 0x9a, 0x83, 0x50, 0x33, 0xe5, 0x62, 0x2d,
  0x60, 0x01, 0x6a, 0x6a, 0x10, 0x1f, 0xe3, 0x8a, 0x05, 0xac, 0x81, 0x23,
  0xde, 0xb7, 0x86, 0x83, 0x19, 0x22, 0x96, 0x88, 0x15, 0xb6, 0x7b, 0x0c,
  0x71, 0xd3, 0x1a, 0x11, 0xd9, 0x0b, 0xdc, 0xbd, 0x32, 0xe5, 0x84, 0x31,
  0x26, 0x56, 0xc2, 0x81, 0x35, 0x12, 0x32, 0xc9, 0x84, 0x56, 0x0a, 0x4f,
  0x1e, 0xa0, 0x28, 0x1a, 0x05, 0x2d, 0x8b, 0x7f, 0xb2, 0x95, 0xc3, 0xd6,
  0x2d, 0x6d, 0x0f, 0xf0, 0xad, 0xac, 0xd1, 0xd2, 0x90, 0xb5, 0xf6, 0xd8,
  0xb8, 0x0f, 0x10, 0x1b, 0xc4, 0x1d, 0x87, 0x35, 0xf6, 0x4d, 0x33, 0x51,
  0x90, 0xb2, 0xe5, 0x04, 0xdd, 0x39, 0x8c, 0x72, 0x9d, 0xb2, 0x5c, 0x71,
  0x37, 0x6f, 0x75, 0xdd, 0x69, 0x71, 0x67, 0x4e, 0x1f, 0x56, 0x8c, 0xe3,
  0x69, 0xd1, 0x8b, 0x8b, 0x73, 0x35, 0xcd, 0x1f, 0xca, 0x0c, 0x32, 0xa1,
  0xcf, 0x41, 0xcf, 0x54, 0x5f, 0x66, 0x0a, 0xe3, 0xbd, 0x50, 0xd6, 0x0a,
  0x39, 0x85, 0x9f, 0x84, 0x5e, 0xc0, 0x17, 0x0e, 0xcb, 0x12, 0x27, 0x0c,
  0x7e, 0x20, 0x7c, 0x4c, 0x98, 0x11, 0xb6, 0x84, 0xef, 0x31, 0x78, 0xd1,
  0xf0, 0x78, 0x8c, 0x18, 0x57, 0xdf, 0xb6, 0x11, 0xdf, 0x67, 0x90, 0xed,
  0x11, 0x9e, 0x2f, 0x83, 0xf5, 0xaf, 0x2a, 0x60, 0x71, 0xb5, 0x80, 0xa7,
  0xeb, 0x4e, 0x16, 0xa1, 0x93, 0x4c, 0x9c, 0x2d, 0xe0, 0x68, 0x63, 0xc8,
  0x41, 0x42, 0x18, 0x3b, 0xd1, 0xbc, 0x3e, 0xc1, 0x01, 0x4e, 0xd0, 0xe1,
  0x36, 0x0e, 0x49, 0xee, 0x08, 0x20, 0x77, 0x4e, 0x64, 0xb6, 0x72, 0xee,
  0xdc, 0xc5, 0x87, 0x95, 0xab, 0x33, 0x5f, 0x75, 0x44, 0x47, 0xa8, 0x85,
  0x9a, 0xc4, 0x0c, 0x1e, 0x71, 0xdc, 0xe2, 0x8a, 0x62, 0x62, 0x4c, 0xc0,
  0x5c, 0x30, 0x10, 0x78, 0x86, 0x78, 0x0c, 0x0e, 0x27, 0x5c, 0x73, 0x5c,
  0x0d, 0xb7, 0x0d, 0x37, 0xb1, 0xa8, 0xe3, 0xd8, 0x3a, 0xdc, 0x60, 0x46,
  0x0a, 0x30, 0x0e, 0xb7, 0xb9, 0x1a, 0x03, 0xf6, 0xcd, 0x33, 0xd1, 0xc0,
  0xe5, 0x2c, 0xb1, 0xe2, 0x6a, 0xe4, 0x71, 0x37, 0x01, 0x8b, 0x61, 0xd7,
  0x25, 0x1e, 0x4a, 0x87, 0xbf, 0x47, 0x6c, 0x2a, 0x3c, 0x1a, 0x10, 0x66,
  0xd3, 0xd7, 0xb8, 0x3a, 0x88, 0x95, 0xc7, 0xac, 0xa0, 0x21, 0x0f, 0xd9,
  0x54, 0x20, 0x9e, 0xc4, 0xa0, 0x1e, 0x55, 0xc7, 0xef, 0xb5, 0xe7, 0xdd,
  0x87, 0x88, 0xf9, 0x0d, 0xb2, 0xe5, 0x37, 0x7e, 0x60, 0x5c, 0x46, 0x29,
  0xd0, 0x01, 0x14, 0x09, 0xe4, 0x1b, 0x98, 0x41, 0xc0, 0x66, 0x1b, 0x43,
  0x95, 0x7b, 0x68, 0x89, 0xed, 0xea, 0x30, 0xce, 0xc7, 0x6d, 0x66, 0xef,
  0x63, 0xd4, 0x26, 0x71, 0x4e, 0x3b, 0xd6, 0x6d, 0xfb, 0x0e, 0x0b, 0x02,
  0xb4, 0xe6, 0x05, 0xed, 0x6f, 0x60, 0x4e, 0x3b, 0x25, 0x4e, 0x20, 0x60,
  0xee, 0xb4, 0xd3, 0x0b, 0xf8, 0xe1, 0x26, 0xd6, 0xbb, 0xac, 0xb3, 0x35,
  0xae, 0xf5, 0xed, 0x66, 0xc2, 0x60, 0x8c, 0xda, 0xc1, 0xf5, 0x2b, 0x5e,
  0x6c, 0x6a, 0x87, 0xa2, 0x33, 0xd8, 0x8e, 0x01, 0x99, 0x9c, 0xdc, 0x2e,
  0xed, 0x34, 0xf4, 0x56, 0x62, 0x64, 0xd6, 0xb4, 0x92, 0x6d, 0x8c, 0x99,
  0x44, 0xc8, 0x7c, 0x27, 0xf6, 0xc7, 0xe3, 0xf2, 0xc7, 0xf8, 0xcd, 0xd2,
  0x29, 0x6d, 0xa6, 0x26, 0x25, 0xc6, 0xf6, 0x59, 0x90, 0x14, 0x36, 0x51,
  0x52, 0x86, 0x07, 0x6c, 0x3c, 0xee, 0x26, 0x5c, 0xc9, 0x9a, 0xb5, 0x21,
  0xa5, 0xa1, 0x76, 0x1a, 0x2e, 0x4b, 0x55, 0xb8, 0x94, 0x14, 0x57, 0xfa,
  0x3a, 0x66, 0xd3, 0x2e, 0x35, 0x3d, 0xd6, 0x34, 0x13, 0x93, 0xda, 0x13,
  0xdc, 0x23, 0x2b, 0xcc, 0x69, 0x13, 0x72, 0x87, 0xb0, 0xaa, 0x6b, 0x47,
  0xd5, 0x5a, 0x55, 0x7b, 0x9d, 0x74, 0x3f, 0xde, 0xa8, 0x3f, 0xde, 0xa8,
  0xb7, 0x4f, 0x30, 0xb9, 0x13, 0xdb, 0x1b, 0xb0, 0x7a, 0xff, 0xd5, 0xf1,
  0xf5, 0xe0, 0x56, 0x04, 0xff, 0x7b, 0x7c, 0x87, 0x9e, 0x57, 0xbb, 0x6f,
  0x08, 0x17, 0xc9, 0xfa, 0xe8, 0x3d, 0xaf, 0x61, 0x9b, 0x44, 0x4b, 0x77,
  0x96, 0xc4, 0x85, 0x2f, 0x14, 0x22, 0xa6, 0x30, 0x65, 0x9c, 0x81, 0x90,
  0x2e, 0xe1, 0x4a, 0xe5, 0xb1, 0xb0, 0xc5, 0x63, 0x06, 0x97, 0x20, 0x7e,
  0xef, 0xf2, 0x6c, 0x05, 0x9f, 0x5c, 0xfa, 0xb3, 0x43, 0x30, 0x85, 0x65,
  0xd6, 0x05, 0xec, 0x1d, 0x77, 0x05, 0xee, 0x83, 0x7b, 0x23, 0x67, 0x7d,
  0x8a, 0xf8, 0xc0, 0x61, 0x79, 0x9a, 0x80, 0xec, 0x79, 0x6b, 0xfb, 0x12,
  0x31, 0x5e, 0xe1, 0x86, 0x68, 0x8d, 0xc5, 0x19, 0x5a, 0x7b, 0x3c, 0x12,
  0x50, 0x48, 0x06, 0xcf, 0xb0, 0x6f, 0xc0, 0x49, 0x96, 0x9d, 0x8c, 0xd0,
  0xfa, 0x39, 0x43, 0x33, 0x4c, 0x8b, 0xc2, 0xae, 0x67, 0x82, 0xd6, 0x80,
  0xd6, 0x17, 0x10, 0x2d, 0x01, 0xeb, 0xb2, 0x72, 0xde, 0x2f, 0xf1, 0x56,
  0xf3, 0x7c, 0xcb, 0x79, 0x7b, 0x9a, 0xe6, 0xbb, 0xc2, 0xa1, 0x6e, 0xc7,
  0x52, 0x3d, 0x0c, 0x25, 0xa2, 0xf7, 0x61, 0x9d, 0x18, 0x3f, 0xc3, 0x76,
  0x03, 0x13, 0x8c, 0xcb, 0x41, 0xf6, 0xe7, 0x12, 0xef, 0x83, 0x3d, 0x8e,
  0xf1, 0x4d, 0x98, 0x59, 0xcc, 0xae, 0x56, 0xc7, 0xf8, 0x31, 0xe2, 0x16,
  0x96, 0x9c, 0x1d, 0x6f, 0x3d, 0x68, 0x32, 0xdb, 0x79, 0x40, 0x49, 0x20,
  0x2a, 0x9e, 0x09, 0x87, 0x91, 0xdb, 0x71, 0x02, 0x17, 0x4f, 0x22, 0x37,
  0xa4, 0xa5, 0x71, 0x3a, 0x31, 0x62, 0x96, 0x9f, 0x08, 0x7b, 0x79, 0xb4,
  0x77, 0xa6, 0xcb, 0x12, 0xb1, 0xc3, 0x7c, 0xda, 0xe3, 0xe6, 0xea, 0x4b,
  0xc8, 0xd7, 0x29, 0xb0, 0xc4, 0x58, 0x98, 0xb6, 0xd9, 0xd5, 0x3a, 0xf3,
  0x3d, 0x09, 0x38, 0x81, 0x5f, 0x3e, 0x8f, 0xf0, 0xfe, 0x0d, 0x91, 0xf3,
  0xe3, 0x9b, 0x80, 0x9b, 0xec, 0x38, 0x6b, 0xe0, 0x6d, 0x3d, 0x3c, 0xba,
  0xba, 0x05, 0xf0, 0x07, 0xc5, 0xeb, 0x6d, 0x2c, 0xd1, 0x9b, 0xf3, 0x7f,
  0x70, 0xc5, 0xfa, 0x77, 0x0a, 0x26, 0xa6, 0x77, 0xf3, 0x6a, 0xbf, 0xa4,
  0xa4, 0xff, 0x7c, 0xd9, 0x4b, 0xf4, 0x39, 0x5d, 0x80, 0xd9, 0x5b, 0xd9,
  0x89, 0xf2, 0x77, 0x98, 0x74, 0x01, 0x6f, 0x4a, 0x4a, 0x27, 0x7a, 0x81,
  0x78, 0xc0, 0xbf, 0x6d, 0x75, 0xe8, 0x4a, 0xb4, 0x89, 0x87, 0xa2, 0xff,
  0x9b, 0xc7, 0xf3, 0xc2, 0xe1, 0x3d, 0x23, 0xf6, 0x67, 0xcf, 0x46, 0xa2,
  0x3f, 0x0c, 0xd6, 0x54, 0xef, 0xa8, 0xd3, 0xc8, 0x9e, 0x34, 0x67, 0xa3,
  0x33, 0xd1, 0x97, 0xbd, 0x50, 0x93, 0x94, 0xd6, 0x07, 0xb3, 0x4b, 0xc2,
  0xa5, 0x75, 0xe8, 0x5b, 0xb4, 0xe6, 0x6a, 0xb4, 0x8d, 0xc3, 0x90, 0xbb,
  0xf0, 0x60, 0x8d, 0xe7, 0xc5, 0x58, 0x46, 0xab, 0xd2, 0x1d, 0xd9, 0x27,
  0x77, 0xc2, 0xea, 0x70, 0x79, 0xeb, 0x73, 0xcf, 0x8e, 0x6a, 0xf4, 0x0f,
  0x99, 0x2d, 0xc9, 0xb5, 0xee, 0xe2, 0x32, 0x57, 0x19, 0x1c, 0xca, 0x7c,
  0x4c, 0xce, 0x2b, 0xe9, 0x83, 0x8c, 0xd8, 0x20, 0x46, 0x05, 0x2c, 0x4a,
  0xdc, 0xac, 0x30, 0xf3, 0x18, 0x6a, 0x78, 0x7c, 0x98, 0x2d, 0xeb, 0xf8,
  0xbe, 0xc7, 0xfd, 0xfd, 0x4c, 0xa6, 0x84, 0xdb, 0x58, 0xc1, 0xc7, 0x6f,
  0x09, 0x8f, 0x03, 0x66, 0xa9, 0xc6, 0x21, 0xa9, 0xb0, 0x77, 0x9d, 0x88,
  0x12, 0x27, 0xfa, 0x80, 0xea, 0x9d, 0x6d, 0xdc, 0x2d, 0x71, 0xa7, 0xc2,
  0x38, 0xc1, 0x01, 0xd5, 0x3b, 0x2a, 0x9e, 0x2e, 0x3b, 0x78, 0x1a, 0xb7,
  0xe7, 0x2b, 0x9a, 0x09, 0xba, 0xb3, 0xa8, 0x9c, 0x57, 0xe1, 0x1f, 0x52,
  0x3b, 0x0e, 0xb2, 0x5b, 0xb9, 0x76, 0xac, 0x38, 0xd9, 0xa5, 0x34, 0x5e,
  0xab, 0x0a, 0xf2, 0xdd, 0x18, 0xea, 0x02, 0x1c, 0x52, 0x95, 0x11, 0x76,
  0x6c, 0x14, 0x04, 0x08, 0xa8, 0x1d, 0x70, 0x61, 0xf3, 0xfb, 0x3b, 0x08,
  0x30, 0x45, 0x13, 0xc2, 0xa8, 0x9d, 0x0d, 0x01, 0x52, 0xed, 0x3a, 0x95,
  0x3d, 0x54, 0x1a, 0x36, 0x5f, 0xa1, 0x00, 0x7b, 0x95, 0x48, 0xa4, 0x5e,
  0x5b, 0xd7, 0xb5, 0x23, 0xaf, 0x6b, 0x27, 0x9d, 0xfb, 0xca, 0x0b, 0x67,
  0x82, 0x37, 0x82, 0x4d, 0xed, 0xdc, 0x14, 0xff, 0xe5, 0xff, 0xeb, 0xa6,
  0xfc, 0x37, 0x02, 0x3c, 0xdb, 0x2d, 0x40, 0x5d, 0x09, 0xb0, 0xae, 0xb4,
  0xd3, 0xc3, 0xac, 0xb8, 0xa6, 0x34, 0x92, 0xd4, 0xe3, 0xfd, 0x4c, 0xa5,
  0x4e, 0x52, 0x6b, 0x6b, 0x11, 0xb0, 0xd7, 0xce, 0xba, 0xef, 0x12, 0x3b,
  0xed, 0xb4, 0x49, 0x3b, 0x6f, 0x4a, 0xed, 0x50, 0xdf, 0x4e, 0x3b, 0x2e,
  0xc9, 0x9b, 0x2d, 0xed, 0xd0, 0xaf, 0xd8, 0xbe, 0x9f, 0x76, 0xfe, 0x04,
  0xae, 0xea, 0x99, 0x53, 0x52, 0xda, 0xe6, 0x3f, 0x00, 0x00, 0x00, 0x00,
  0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
DEFINE_SIZE(font_data)
#endif /* NdkBootPicker_h */
