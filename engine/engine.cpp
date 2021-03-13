//
// Created by Michael on 09.02.2021.
//

#include "engine.h"

#include <bsw.h>
#include <core/font/font_manager.h>
#include <core/render/gl_render.h>

Single<bsw::Engine> bsw::Engine::m_instance;

bsw::Engine &bsw::Engine::create(const WindowProps &props, const char** argv) {
    Engine::m_instance = create_single<Engine>();
    AssetManager::init(argv[0]);

    Engine::m_instance->m_main_window = create_single<Window>(props);
    Engine::m_instance->initialize();

    Engine::m_instance->m_screen_handler = create_single<ScreenHandler>();


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

    FontManager::init();
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

#ifdef BUILD_DEBUG
        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %d", current_fps);
        ImGui::Text("Updates: %d", current_updates);
        ImGui::Dummy({0, 5});
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

    FontManager::shutdown();
    File::cleanup_temp_files();
    return 0;
}

float bsw::Engine::get_runtime() const { return (float) glfwGetTime(); }

const Single<bsw::Window> &bsw::Engine::get_window_handle() const { return m_main_window; }
