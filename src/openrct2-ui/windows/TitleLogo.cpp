#pragma region Copyright (c) 2014-2017 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include <openrct2-ui/windows/Window.h>

#include <openrct2/localisation/Localisation.h>
#include <openrct2/sprites.h>
#include <openrct2-ui/interface/Widget.h>
#include <openrct2/interface/Colour.h>
#include <openrct2/drawing/Drawing.h>
#include <openrct2/core/String.hpp>

// clang-format off
static rct_widget window_title_logo_widgets[] = {
    { WIDGETS_END },
};

static void window_title_logo_paint(rct_window *w, rct_drawpixelinfo *dpi);

static rct_window_event_list window_title_logo_events = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    window_title_logo_paint,
    nullptr
};
// clang-format on

/**
 * Creates the window containing the logo and the expansion packs on the title screen.
 *  rct2: 0x0066B679 (part of 0x0066B3E8)
 */
rct_window * window_title_logo_open()
{
    rct_window * window = window_create(0,
                                        0,
                                        16 * 16,
                                        16 * 16,
                                        &window_title_logo_events,
                                        WC_TITLE_LOGO,
                                        WF_STICK_TO_BACK | WF_TRANSPARENT);
    window->widgets = window_title_logo_widgets;
    window_init_scroll_widgets(window);
    window->colours[0] = TRANSLUCENT(COLOUR_GREY);
    window->colours[1] = TRANSLUCENT(COLOUR_GREY);
    window->colours[2] = TRANSLUCENT(COLOUR_GREY);

    return window;
}

/**
*
*  rct2: 0x0066B872
*/
static void window_title_logo_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            int _x = w->x + x * 16;
            int _y = w->y + y * 16;
            gfx_fill_rect(dpi, _x, _y, _x + 15, _y + 15, x + y * 16);
            utf8* str = String::Format("%02X", x +y*16);
            gCurrentFontSpriteBase = FONT_SPRITE_BASE_SMALL;
            gfx_draw_string_centred(dpi, STR_STRING, _x + 8, _y+3, COLOUR_WHITE, &str);
        }
    }
}
