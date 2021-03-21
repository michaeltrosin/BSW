//
// Created by Michael on 09.02.2021.
//

#include "engine.h"

#include <bsw.h>
#include <core/render/gl_render.h>
#include <core/render/renderer2d.h>

Scoped<bsw::Engine> bsw::Engine::m_instance;

bsw::Engine &bsw::Engine::create(const WindowProps &props, const char **argv) {
    Engine::m_instance = create_scoped<Engine>();
    AssetManager::init(argv[0]);

    Engine::m_instance->m_main_window = create_scoped<Window>(props);
    Engine::m_instance->initialize();

    Engine::m_instance->m_screen_handler = create_scoped<ScreenHandler>();

    return *Engine::m_instance;
}

bsw::Engine::~Engine() {
    m_main_window->shutdown();
    Renderer2D::shutdown();
};

void bsw::Engine::initialize() {
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (!status) {
        std::cout << "Error initializing GLAD" << std::endl;
        ASSERT_NOT_REACHED_NO_MSG();
    }
    m_main_window->initialize();
    m_main_window->set_event_callback(MAKE_EVENT_CALLBACK(on_event));

    GlRenderer::init();
    Renderer2D::init();
}

void bsw::Engine::on_event(Event &event) {
    m_screen_handler->on_event(event);

    if (event.is<WindowResizeEvent>()) {
        auto e = dynamic_cast<WindowResizeEvent *>(&event);
        GlRenderer::set_viewport(0, 0, e->get_width(), e->get_height());
    }
}

uint32_t bsw::Engine::get_window_width() { return m_main_window->get_width(); }
uint32_t bsw::Engine::get_window_height() { return m_main_window->get_height(); }

int bsw::Engine::run() {
    double last_time = glfwGetTime();
    double timer = last_time;
    double delta_time = 0;
    double now_time;
    int frames = 0;
    int updates = 0;

    int current_fps = 0;
    int current_updates = 0;

    while (!m_main_window->should_close()) {
        GlRenderer::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
        GlRenderer::clear();

        now_time = glfwGetTime();
        delta_time += (now_time - last_time) / (1.0 / m_fps_limit);
        last_time = now_time;

        while (delta_time >= 1.0) {
            m_screen_handler->on_update((float) delta_time);
            updates++;
            delta_time--;
        }
        m_screen_handler->on_render();
        frames++;

        m_main_window->gui_handler()->begin();

#ifndef NO_DEBUG_DRAW
        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %d", current_fps);
        ImGui::Text("Updates: %d", current_updates);
        ImGui::Dummy({0, 5});

        auto stats = Renderer2D::get_stats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.draw_calls);
        ImGui::Text("Quads: %d", stats.quad_count);
        ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
        ImGui::Text("Indices: %d", stats.get_total_index_count());
        ImGui::End();
#endif
        m_screen_handler->on_im_gui_render();

        m_main_window->gui_handler()->end();
        m_main_window->swap_buffers();
        // - Reset after one second
        if (glfwGetTime() - timer > 1.0) {
            timer++;
            current_fps = frames;
            current_updates = updates;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }
    }

    File::cleanup_temp_files();
    return 0;
}

float bsw::Engine::get_runtime() const { return (float) glfwGetTime(); }

const Scoped<bsw::Window> &bsw::Engine::get_window_handle() const { return m_main_window; }
