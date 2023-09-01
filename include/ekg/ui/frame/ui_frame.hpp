/*
 * VOKEGPU EKG LICENSE
 *
 * Respect ekg license policy terms, please take a time and read it.
 * 1- Any "skidd" or "stole" is not allowed.
 * 2- Forks and pull requests should follow the license policy terms.
 * 3- For commercial use, do not sell without give credit to vokegpu ekg.
 * 4- For ekg users and users-programmer, we do not care, free to use in anything (utility, hacking, cheat, game, software).
 * 5- Malware, rat and others virus. We do not care.
 * 6- Do not modify this license under any instance.
 *
 * @VokeGpu 2023 all rights reserved.
 */

#ifndef EKG_UI_FRAME_H
#define EKG_UI_FRAME_H

#include "ekg/ui/abstract/ui_abstract.hpp"
#include "ekg/util/geometry.hpp"
#include <vector>

namespace ekg::ui {
    class frame : public ekg::ui::abstract {
    protected:
        uint16_t dock_resize {};
        uint16_t dock_drag {};

        ekg::rect rect_initial {};
        std::string tag {};
        ekg::vec2 scale_factor {};
    public:
        ekg::ui::frame *set_place(uint16_t dock);

        ekg::ui::frame *set_scale_factor(float x, float y);
        ekg::vec2 get_scale_factor();

        ekg::ui::frame *set_drag(uint16_t dock);
        uint16_t get_drag_dock();

        ekg::ui::frame *set_resize(uint16_t dock);
        uint16_t get_resize_dock();

        ekg::ui::frame *set_pos_initial(float x, float y);
        ekg::vec2 get_pos_initial();

        ekg::ui::frame *set_size_initial(float x, float y);
        ekg::vec2 get_size_initial();

        ekg::ui::frame *set_initial_width(float w);
        float get_initial_width();

        ekg::ui::frame *set_initial_height(float h);
        float get_initial_height();

        ekg::ui::frame *set_size(float w, float h);
        ekg::vec2 get_size();

        ekg::ui::frame *set_pos(float x, float y);
        ekg::vec2 get_pos();

        ekg::ui::frame *set_width(float w);
        float get_width();

        ekg::ui::frame *set_height(float h);
        float get_height();
    };
}

#endif