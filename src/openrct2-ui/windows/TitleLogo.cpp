/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <openrct2-ui/interface/Widget.h>
#include <openrct2-ui/windows/Windows.h>
#include <openrct2/SpriteIds.h>
#include <openrct2/core/String.hpp>
#include <openrct2/drawing/Drawing.h>
#include <openrct2/drawing/Rectangle.h>
#include <openrct2/interface/Colour.h>
#include <openrct2/interface/ColourWithFlags.h>
#include <openrct2/ui/WindowManager.h>

namespace OpenRCT2::Ui::Windows
{
    static constexpr ScreenSize kWindowSize = { 16 * 16, 16 * 16 };

    enum
    {
        WIDX_LOGO
    };

    static constexpr auto _titleLogoWidgets = makeWidgets(
        makeWidget({ 0, 0 }, kWindowSize, WidgetType::imgBtn, WindowColour::primary));

    class TitleLogoWindow final : public Window
    {
    public:
        /**
         * Creates the window containing the logo and the expansion packs on the title screen.
         *  rct2: 0x0066B679 (part of 0x0066B3E8)
         */
        void onOpen() override
        {
            setWidgets(_titleLogoWidgets);
        }

        /**
         *
         *  rct2: 0x0066B872
         */
        void onDraw(Drawing::RenderTarget& rt) override
        {
            for (int y = 0; y < 16; y++)
            {
                for (int x = 0; x < 16; x++)
                {
                    auto screenPos = windowPos + ScreenCoordsXY{ x * 16, y * 16 };
                    auto colour = x + y * 16;
                    Drawing::Rectangle::fill(rt, ScreenRect{ screenPos, screenPos + ScreenCoordsXY{ 16, 16 } }, colour);

                    auto str = String::stdFormat("%02X", colour);
                    DrawText(rt, screenPos + ScreenCoordsXY{ 8, 3 }, { TextAlignment::centre }, str.c_str(), true);
                }
            }
        }
    };

    WindowBase* TitleLogoOpen()
    {
        auto* windowMgr = GetWindowManager();
        auto* window = windowMgr->BringToFrontByClass(WindowClass::titleLogo);
        if (window == nullptr)
        {
            window = windowMgr->Create<TitleLogoWindow>(
                WindowClass::titleLogo, ScreenCoordsXY(0, 0), kWindowSize,
                { WindowFlag::stickToBack, WindowFlag::transparent, WindowFlag::noTitleBar });
        }
        return window;
    }
} // namespace OpenRCT2::Ui::Windows
