#ifndef __ILI9341_H__
#define __ILI9341_H__

#include "stm32f1xx_hal.h"
#include "stdlib.h"
#include "./fonts/bitmap_typedefs.h"

#define ILI_RD_ACTIVE GPIOA->BSRR = (GPIO_PIN_6 << 16u)
#define ILI_RD_IDLE GPIOA->BSRR = GPIO_PIN_6

#define ILI_DC_CMD GPIOC->BSRR = (GPIO_PIN_14 << 16u)
#define ILI_DC_DAT GPIOC->BSRR = GPIO_PIN_14
#define ILI_CS_ACTIVE GPIOC->BSRR = (GPIO_PIN_13 << 16u)
#define ILI_CS_IDLE GPIOC->BSRR = GPIO_PIN_13
#define ILI_RST_ACTIVE GPIOB->BSRR = (GPIO_PIN_9 << 16u)
#define ILI_RST_IDLE GPIOB->BSRR = GPIO_PIN_9

#define ILI_NOP 0x00
#define ILI_SWRESET 0x01
#define ILI_RDDID 0xD3
#define ILI_RDDST 0x09

#define ILI_SLPIN 0x10
#define ILI_SLPOUT 0x11
#define ILI_PTLON 0x12
#define ILI_NORON 0x13

#define ILI_RDMODE 0x0A
#define ILI_RDMADCTL 0x0B
#define ILI_RDPIXFMT 0x0C
#define ILI_RDIMGFMT 0x0D
#define ILI_RDSELFDIAG 0x0F

#define ILI_INVOFF 0x20
#define ILI_INVON 0x21
#define ILI_GAMMASET 0x26
#define ILI_DISPOFF 0x28
#define ILI_DISPON 0x29

#define ILI_CASET 0x2A
#define ILI_PASET 0x2B
#define ILI_RAMWR 0x2C
#define ILI_RAMRD 0x2E

#define ILI_PTLAR 0x30
#define ILI_MADCTL 0x36
#define ILI_PIXFMT 0x3A

#define ILI_FRMCTR1 0xB1
#define ILI_FRMCTR2 0xB2
#define ILI_FRMCTR3 0xB3
#define ILI_INVCTR 0xB4
#define ILI_DFUNCTR 0xB6

#define ILI_PWCTR1 0xC0
#define ILI_PWCTR2 0xC1
#define ILI_PWCTR3 0xC2
#define ILI_PWCTR4 0xC3
#define ILI_PWCTR5 0xC4
#define ILI_VMCTR1 0xC5
#define ILI_VMCTR2 0xC7

#define ILI_RDID1 0xDA
#define ILI_RDID2 0xDB
#define ILI_RDID3 0xDC
#define ILI_RDID4 0xDD

#define ILI_GMCTRP1 0xE0
#define ILI_GMCTRN1 0xE1

#define ILI_WR_STROBE  \
    {                  \
        ILI_WR_ACTIVE; \
        ILI_WR_IDLE;   \
    }
#define ILI_RD_STROBE  \
    {                  \
        ILI_RD_ACTIVE; \
        ILI_RD_IDLE;   \
    }

#define ILI_WRITE_8BIT(d)                                  \
    {                                                      \
        GPIOB->BSRR = (uint32_t)(0x00FF0000 | ((d)&0xFF)); \
        ILI_WR_STROBE;                                     \
    }
#define ILI_READ_8BIT(d)                  \
    {                                     \
        d = (uint8_t)GPIOB->IDR & 0x00FF; \
    }

#define ILI_R_POS_RGB 11 // Red last bit position for RGB display
#define ILI_G_POS_RGB 5  // Green last bit position for RGB display
#define ILI_B_POS_RGB 0  // Blue last bit position for RGB display

#define ILI_RGB(R, G, B)                     \
    (((uint16_t)(R >> 3) << ILI_R_POS_RGB) | \
     ((uint16_t)(G >> 2) << ILI_G_POS_RGB) | \
     ((uint16_t)(B >> 3) << ILI_B_POS_RGB))

#define ILI_R_POS_BGR 0  // Red last bit position for BGR display
#define ILI_G_POS_BGR 5  // Green last bit position for BGR display
#define ILI_B_POS_BGR 11 // Blue last bit position for BGR display

#define ILI_BGR(R, G, B)                     \
    (((uint16_t)(R >> 3) << ILI_R_POS_BGR) | \
     ((uint16_t)(G >> 2) << ILI_G_POS_BGR) | \
     ((uint16_t)(B >> 3) << ILI_B_POS_BGR))

#define ILI_COLOR_BLACK       ILI_BGR(0,     0,   0)
    #define ILI_COLOR_NAVY        ILI_BGR(0,     0, 123)
    #define ILI_COLOR_DARKGREEN   ILI_BGR(0,   125,   0)
    #define ILI_COLOR_DARKCYAN    ILI_BGR(0,   125, 123)
    #define ILI_COLOR_MAROON      ILI_BGR(123,   0,   0)
    #define ILI_COLOR_PURPLE      ILI_BGR(123,   0, 123)
    #define ILI_COLOR_OLIVE       ILI_BGR(123, 125,   0)
    #define ILI_COLOR_LIGHTGREY   ILI_BGR(198, 195, 198)
    #define ILI_COLOR_DARKGREY    ILI_BGR(123, 125, 123)
    #define ILI_COLOR_BLUE        ILI_BGR(0,     0, 255)
    #define ILI_COLOR_GREEN       ILI_BGR(0,   255,   0)
    #define ILI_COLOR_CYAN        ILI_BGR(0,   255, 255)
    #define ILI_COLOR_RED         ILI_BGR(255,   0,   0)
    #define ILI_COLOR_MAGENTA     ILI_BGR(255,   0, 255)
    #define ILI_COLOR_YELLOW      ILI_BGR(255, 255,   0)
    #define ILI_COLOR_WHITE       ILI_BGR(255, 255, 255)
    #define ILI_COLOR_ORANGE      ILI_BGR(255, 165,   0)
    #define ILI_COLOR_GREENYELLOW ILI_BGR(173, 255,  41)
    #define ILI_COLOR_PINK        ILI_BGR(255, 130, 198)

#ifdef USER_DEFAULT_PLATFORM
    // Color definitions
    #define ILI_COLOR_BLACK       ILI_RGB(0,     0,   0)
    #define ILI_COLOR_NAVY        ILI_RGB(0,     0, 123)
    #define ILI_COLOR_DARKGREEN   ILI_RGB(0,   125,   0)
    #define ILI_COLOR_DARKCYAN    ILI_RGB(0,   125, 123)
    #define ILI_COLOR_MAROON      ILI_RGB(123,   0,   0)
    #define ILI_COLOR_PURPLE      ILI_RGB(123,   0, 123)
    #define ILI_COLOR_OLIVE       ILI_RGB(123, 125,   0)
    #define ILI_COLOR_LIGHTGREY   ILI_RGB(198, 195, 198)
    #define ILI_COLOR_DARKGREY    ILI_RGB(123, 125, 123)
    #define ILI_COLOR_BLUE        ILI_RGB(0,     0, 255)
    #define ILI_COLOR_GREEN       ILI_RGB(0,   255,   0)
    #define ILI_COLOR_CYAN        ILI_RGB(0,   255, 255)
    #define ILI_COLOR_RED         ILI_RGB(255,   0,   0)
    #define ILI_COLOR_MAGENTA     ILI_RGB(255,   0, 255)
    #define ILI_COLOR_YELLOW      ILI_RGB(255, 255,   0)
    #define ILI_COLOR_WHITE       ILI_RGB(255, 255, 255)
    #define ILI_COLOR_ORANGE      ILI_RGB(255, 165,   0)
    #define ILI_COLOR_GREENYELLOW ILI_RGB(173, 255,  41)
    #define ILI_COLOR_PINK        ILI_RGB(255, 130, 198)
#endif
/*
* function prototypes
*/

/**
 * Set an area for drawing on the display with start row,col and end row,col.
 * User don't need to call it usually, call it only before some functions who don't call it by default.
 * @param x1 start column address.
 * @param y1 start row address.
 * @param x2 end column address.
 * @param y2 end row address.
 */
void ili_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * Fills `len` number of pixels with `color`.
 * Call ili_set_address_window() before calling this function.
 * @param color 16-bit RGB565 color value
 * @param len 32-bit number of pixels
 */
void ili_fill_color(uint16_t color, uint32_t len);

/**
 * Draw a line from (x0,y0) to (x1,y1) with `width` and `color`.
 * @param x0 start column address.
 * @param y0 start row address.
 * @param x1 end column address.
 * @param y1 end row address.
 * @param width width or thickness of the line
 * @param color 16-bit RGB565 color of the line
 */
void ili_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/**
 * Experimental
 * Draw a rectangle without filling it
 * @param x start column address.
 * @param y start row address
 * @param w Width of rectangle
 * @param h height of rectangle
 */
void ili_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color);

/**
 * Rotate the display clockwise or anti-clockwie set by `rotation`
 * @param rotation Type of rotation. Supported values 0, 1, 2, 3
 */
void ili_rotate_display(uint8_t rotation);

/**
 * Initialize the display driver
 */
void ili_init();

/**
 * Fills a rectangular area with `color`.
 * Before filling, performs area bound checking
 * @param x Start col address
 * @param y Start row address
 * @param w Width of rectangle
 * @param h Height of rectangle
 * @param color 16-bit RGB565 color
 */
void ili_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/*
 * Same as `ili_fill_rect()` but does not do bound checking, so it's slightly faster
 */
void ili_fill_rect_fast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * Fill the entire display (screen) with `color`
 * @param color 16-bit RGB565 color
 */
void ili_fill_screen(uint16_t color);

/*
 * Render a character glyph on the display. Called by `ili_draw_string_main()`
 * User need NOT call it
 */
void _ili_render_glyph(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg);

/**
 * Renders a string by drawing each character glyph from the passed string.
 * Called by `ili_draw_string()` and `ili_draw_string_withbg()`.
 * Text is wrapped automatically if it hits the screen boundary.
 * x_padding and y_padding defines horizontal and vertical distance (in px) between two characters
 * is_bg=1 : Text will habe background color,   is_bg=0 : Text will have transparent background
 * User need NOT call it.
 */
void _ili_draw_string_main(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, const tFont *font, uint8_t is_bg);

/**
 * Draws a string on the display with `font` and `color` at given position.
 * Background of this string is transparent
 * @param x Start col address
 * @param y Start y address
 * @param str pointer to the string to be drawn
 * @param color 16-bit RGB565 color of the string
 * @param font Pointer to the font of the string
 */
void ili_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color, const tFont *font);

/**
 * Draws a string on the display with `font`, `fore_color`, and `back_color` at given position.
 * The string has background color
 * @param x Start col address
 * @param y Start y address
 * @param str pointer to the string to be drawn
 * @param foe_color 16-bit RGB565 color of the string
 * @param back_color 16-bit RGB565 color of the string's background
 * @param font Pointer to the font of the string
 */
void ili_draw_string_withbg(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, const tFont *font);

/**
 * Draws a character at a given position, fore color, back color.
 * @param x Start col address
 * @param y Start row address
 * @param character the ASCII character to be drawn
 * @param fore_color foreground color
 * @param back_color background color
 * @param font Pointer to the font of the character
 * @param is_bg Defines if character has background or not (transparent)
 */
void ili_draw_char(uint16_t x, uint16_t y, char character, uint16_t fore_color, uint16_t back_color, const tFont *font, uint8_t is_bg);

/**
 * Draw a bitmap image on the display
 * @param x Start col address
 * @param y Start row address
 * @param bitmap Pointer to the image data to be drawn
 */
void ili_draw_bitmap(uint16_t x, uint16_t y, const tImage *bitmap);
//void ili_draw_bitmap_old(uint16_t x, uint16_t y, const tImage16bit *bitmap);

/**
 * Draw a pixel at a given position with `color`
 * @param x Start col address
 * @param y Start row address
 */
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void MX_GPIO_Init(void);
#endif