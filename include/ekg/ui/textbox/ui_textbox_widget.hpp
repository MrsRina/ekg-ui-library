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

#ifndef EKG_UI_TEXT_BOX_WIDGET_H
#define EKG_UI_TEXT_BOX_WIDGET_H

#include "ekg/ui/abstract/ui_abstract_widget.hpp"
#include "ekg/ui/scroll/ui_scroll_embedded_widget.hpp"
#include <unordered_map>

#define ekg_textbox_clamp_text_chunk_size(text_chunk_list, max_size) if (text_chunk_list.size() > max_size) text_chunk_list.erase(text_chunk_list.begin() + max_size, text_chunk_list.end())
#define ekg_textbox_clamp_line(line, max_size) if (line.size() > max_size) line = line.substr(0, max_size)

namespace ekg::ui {
    class textbox_widget : public ekg::ui::abstract_widget {
    public:
        enum action {
            add_text,
            erase_text,
            break_line
        };
        
        struct cursor_pos {
        public:
            int64_t index {};
            int64_t select_index {};
            int64_t chunk_index {};
            int64_t text_index {};
            int64_t last_text_index {};
        public:
            inline bool operator>(ekg::ui::textbox_widget::cursor_pos &r) {
                return this->index > r.index && this->chunk_index > r.chunk_index;
            }

            inline bool operator<(ekg::ui::textbox_widget::cursor_pos &r) {
                return this->index < r.index && this->chunk_index < r.chunk_index;
            }

            inline bool operator>=(ekg::ui::textbox_widget::cursor_pos &r) {
                return this->index >= r.index && this->chunk_index >= r.chunk_index;
            }

            inline bool operator<=(ekg::ui::textbox_widget::cursor_pos &r) {
                return this->index <= r.index && this->chunk_index <= r.chunk_index;
            }

            inline bool operator==(ekg::ui::textbox_widget::cursor_pos &r) {
                return this->index == r.index && this->chunk_index == r.chunk_index;
            }

            inline bool operator!=(ekg::ui::textbox_widget::cursor_pos &r) {
                return !(*this == r);
            }
        };

        struct cursor {
        public:
            /*
             * pos[0] is the cursor position A,
             * pos[1] is the cursor position B,
             * pos[2] is the initial select position,
             * pos[3] is the select target side.
             */
            ekg::ui::textbox_widget::cursor_pos pos[4] {};
        };
    public:
        std::vector<std::string> text_chunk_list {};
        std::vector<ekg::rect> cursor_draw_data_list {};
        std::string widget_side_text {};
        std::vector<ekg::ui::textbox_widget::cursor> loaded_multi_cursor_list {
            ekg::ui::textbox_widget::cursor()
        };
        
        ekg::rect rect_text {};
        ekg::rect rect_cursor {};
        ekg::ui::scroll_embedded_widget embedded_scroll {};

        float cursor_char_wsize[3] {};
        float text_offset {};
        float text_height {};
        
        bool redraw_cursor {};
        bool is_ui_enabled {};
        bool is_action_modifier_enable {};
        bool is_action_select_enable {};

        bool is_clipboard_copy {};
        bool is_clipboard_cut {};
        bool is_clipboard_paste {};

        int64_t total_utf_chars {};
        std::string cached_tab_size {};
        uint64_t visible_text[4] {};
    public:
        std::string &get_cursor_emplace_text(ekg::ui::textbox_widget::cursor_pos &cursor);
        int32_t find_cursor(ekg::ui::textbox_widget::cursor &target_cursor, int64_t total_it, int64_t it_chunk, bool last_line_utf_char_index);

        void check_cursor_text_bounding(ekg::ui::textbox_widget::cursor &cursor, bool reset_second_cursor_pos);
        void process_text(ekg::ui::textbox_widget::cursor &cursor, std::string_view text, ekg::ui::textbox_widget::action action, int64_t direction);
        void move_cursor(ekg::ui::textbox_widget::cursor_pos &cursor, int64_t x, int64_t y);
        void update_cpu_side_batching_cursor();
        void check_nearest_word(ekg::ui::textbox_widget::cursor &cursor, int64_t &x, int64_t &y);
        void move_target_cursor(ekg::ui::textbox_widget::cursor &cursor, int64_t x, int64_t y);
        void clamp_text_chunk_size();
    public:
        void on_destroy() override;
        void on_reload() override;
        void on_pre_event(SDL_Event &sdl_event) override;
        void on_event(SDL_Event &sdl_event) override;
        void on_post_event(SDL_Event &sdl_event) override;
        void on_update() override;
        void on_draw_refresh() override;
    };
}

#endif