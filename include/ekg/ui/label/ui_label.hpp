/*
* MIT License
* 
* Copyright (c) 2022-2023 Rina Wilk / vokegpu@gmail.com
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef EKG_UI_LABEL_H
#define EKG_UI_LABEL_H

#include "ekg/ui/abstract/ui_abstract.hpp"
#include "ekg/util/aspect.hpp"

namespace ekg::ui {
    class label : public ekg::ui::abstract {
    protected:
        std::string text {};
        uint16_t dock_text {};
        ekg::font font_size {};
    public:
        ekg::ui::label *set_font_size(ekg::font font);
        ekg::font get_font_size();

        ekg::ui::label *set_place(uint16_t dock);
        int32_t get_scaled_height();

        ekg::ui::label *set_width(float w);
        float get_width();

        ekg::ui::label *set_scaled_height(int32_t h);
        float get_height();

        ekg::ui::label *set_text(std::string_view text);
        std::string get_text();

        ekg::ui::label *set_text_align(uint16_t dock);
        uint16_t get_text_align();
    };
}

#endif