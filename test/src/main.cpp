#include "ekg/ekg.hpp"

#include "test_feature.hpp"
#include "ekg/util/util_virtual_thread.hpp"

std::string test::name {};

/*
 * Test ekg ui library.
 *
 * -- result A = Approved - No problems passed.
 * -- result B = Partial  - No problems but not totally done.
 * -- result F = Reproved - Problems or not working correct.
 *
 * All tests were ran in Linux.
 */
int main(int argv, char** argc) {
    ekg::log("Initialising demo showcase");

    float root_width {1280.0f};
    float root_height {800.0f};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* sdl_win {SDL_CreateWindow("ekg showcase", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, root_width, root_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)};

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GLContext sdl_gl_context {SDL_GL_CreateContext(sdl_win)};
    bool running {true};

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        ekg::log("Failed to initialise GLEW OpenGL context!");
    } else {
        ekg::log("GLEW initialised");
    }

    ekg::gpu::init_opengl_context();
    ekg::init(sdl_win, "JetBrainsMono-Bold.ttf");
    ekg::log("OpenGL 4 context created");

    ekg::timing mainloop_timing {};
    ekg::timing fps_timing {};

    SDL_Event sdl_event {};

    // z-depth testing.
    glEnable(GL_DEPTH_TEST);

    uint64_t fps = 60;
    uint64_t fps_ms_interval {1000 / fps};
    uint64_t last_ticked_frames {};
    uint64_t ticked_frames {};

    /* Start of virtual threads test. */
    test::run("Virtual threads");

    ekg::process(ekg::env::redraw, ekg::thread::start);
    test::check("process redraw", test::result::a);

    ekg::process(ekg::env::update, ekg::thread::start);
    test::check("process update", test::result::a);

    ekg::process(ekg::env::reset, ekg::thread::start);
    test::check("process reset", test::result::a);

    ekg::process(ekg::env::swap, ekg::thread::start);
    test::check("process swap", test::result::a);

    test::end();
    /* End of virtual threads test. */

    /*
     * Mainloop.
     */
    while (running) {
        /*
         * Handle ticked loop each frame (1s).
         */
        if (ekg::reach(mainloop_timing, fps_ms_interval)) {
            ekg::reset(mainloop_timing);
            ekg::display::dt = static_cast<float>(mainloop_timing.current_ticks) / 100;

            if (ekg::reach(fps_timing, 1000)) {
                ekg::reset(fps_timing);

                last_ticked_frames = ticked_frames;
                ticked_frames = 0;
            }

            while (SDL_PollEvent(&sdl_event)) {
                switch (sdl_event.type) {
                    case SDL_QUIT: {
                        running = false;
                        break;
                    }

                    default: {
                        ekg::event(sdl_event);
                        break;
                    }
                }
            }

            ekg::update();

            glViewport(0, 0, static_cast<int32_t>(root_width), static_cast<int32_t>(root_height));
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

            ekg::render();

            // Count the FPS.
            ticked_frames++;

            // Swap buffers.
            SDL_GL_SwapWindow(sdl_win);
        }
    }

    ekg::quit();

    return 0;
}