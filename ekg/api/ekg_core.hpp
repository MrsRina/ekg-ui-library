#pragma once
#ifndef EKG_CORE_H
#define EKG_CORE_H

#include <ekg/impl/ekg_ui_element_abstract.hpp>
#include "ekg_font.hpp"
#include <array>

/**
 * Core of EKG, where everything is processed.
 */
class ekg_core {
protected:
    // For work with modern GPU we need to modify all buffers safe (thinks in performance).
    ekg_gpu_data_handler gpu_handler;

    // Font manager to handle and display (draw) chars at screen.
    ekg_font font_manager;

    // Instances of SDL2.
    SDL_Window* sdl_window_instance;

    // Buffers to we handle in game.
    std::array<ekg_element*, 512> render_buffer;
    std::vector<ekg_element*> data_invisible_to_memory;
    std::vector<ekg_element*> data;

    uint16_t sizeof_render_buffer = 0;
    uint32_t last_id_used = 0;

    uint32_t focused_element_id;
    uint32_t last_focused_element_id;
    uint32_t forced_focused_element_id;

    // Concurrent buffers to prevent memory leak/segment fault or invalid elements.
    std::vector<ekg_element*> concurrent_buffer;

    // 0 refresh; 1 fix stack;
    uint16_t todo_flags;

    /*
     * Pass new modified buffers to update buffers.
     */
    void swap_buffers();

    /*
     * Reload and move correctly the positions of GUI layout (stack).
     */
    void fix_stack();
public:
    /*
     * Force to fix stack (reorder).
     */
    void force_reorder_stack(uint32_t &id);

    /*
     * Dispatch an event in core.
     */
    void dispatch_todo_event(uint8_t flag);

    /*
     * Access core EKG GPU handler.
     */
    ekg_gpu_data_handler &get_gpu_handler();

    /*
     * Get the main font manager.
     */
    ekg_font &get_font_manager();

    /*
     * Init core of EKG.
     */
    void init();

    /*
     * Shutdown EKG core.
     */
    void quit();

    /*
     * Set concurrent SDL window instance.
     */
    void set_instances(SDL_Window* &sdl_window);

    /*
     * Add element into EKG context.
     */
    void add_element(ekg_element* &element);

    /*
     * Find for element in GUI context.
     */
    bool find_element(ekg_element* &element, uint32_t id);

    /*
     * Poll events in EKG.
     */
    void process_event_section(SDL_Event &event);

    /*
     * Update the GUI.
     */
    void process_update_section();

    /*
     * Draw the all EKG elements.
     */
    void process_render_section();
};

#endif