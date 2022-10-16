#include "ekg/ui/label/ui_label.hpp"
#include "ekg/util/util_ui.hpp"

void ekg::ui::label::set_dock(uint16_t flags) {
    this->dock = flags;
}

void ekg::ui::label::set_text(std::string_view string) {
    if (this->text != string) {
        this->text = string;
        ekg::reload(this->id);
    }
}

std::string_view ekg::ui::label::get_text() {
    return this->text;
}

void ekg::ui::label::set_text(uint16_t flags) {
    this->dock_text = flags;
}

uint16_t ekg::ui::label::get_text_dock() {
    return this->dock_text;
}

void ekg::ui::label::set_width(float width) {
    if (this->sync_ui.w != width) {
        this->sync_ui.h = width;
        this->set_sync_with_ui(true);
    }
}

float ekg::ui::label::get_width() {
    return this->rect_widget.w;
}

void ekg::ui::label::set_scaled_height(int32_t scaled_factor_height) {
    if (this->scaled_height != scaled_factor_height) {
        this->scaled_height = scaled_factor_height;
        ekg::reload(this->id);
    }
}

float ekg::ui::label::get_height() {
    return this->rect_widget.h;
}

int32_t ekg::ui::label::get_scaled_height() {
    return this->scaled_height;
}

void ekg::ui::label::set_font_size(ekg::font font) {
    if (this->font_size != font) {
        this->font_size = font;
        ekg::reload(this->id);
    }
}

ekg::font ekg::ui::label::get_font_size() {
    return this->font_size;
}
