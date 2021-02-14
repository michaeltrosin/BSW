//
// Created by Michael on 09.02.2021.
//

#include <bsw.h>
#include <core/render/gl_render.h>
#include <core/window/window.h>

#include <core/render/renderer2d.h>

#include "engine.h"

namespace bsw {

Single<Engine> Engine::k_instance_;

Engine &Engine::Create(const WindowProps &props) {
  Engine::k_instance_ = CreateSingle<Engine>();

  Engine::k_instance_->main_window_ = CreateSingle<Window>(props);
  Engine::k_instance_->Initialize();

  Engine::k_instance_->screen_handler_ = CreateSingle<ScreenHandler>();

  return *Engine::k_instance_;
}

Engine::~Engine() {
  main_window_->Shutdown();
  Renderer2D::Shutdown();
};

void Engine::Initialize() {
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!status) {
    std::cout << "Error initializing GLAD" << std::endl;
    ASSERT_NOT_REACHED_NO_MSG();
  }
  main_window_->Initialize();
  main_window_->SetEventCallback(MAKE_EVENT_CALLBACK(OnEvent));

  GLRenderer::Init();
  Renderer2D::Init();
}

void Engine::OnEvent(Event &event) {
  screen_handler_->OnEvent(event);

  if (event.Is<WindowResizeEvent>()) {
    auto e = dynamic_cast<WindowResizeEvent *>(&event);
    GLRenderer::SetViewport(0, 0, e->GetWidth(), e->GetHeight());
  }
}

int Engine::Run() {
  double last_time = glfwGetTime();
  double timer = last_time;
  double delta_time = 0;
  double now_time;
  int frames = 0;
  int updates = 0;

  int current_fps = 0;
  int current_updates = 0;

  while (!main_window_->ShouldClose()) {
    GLRenderer::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    GLRenderer::Clear();

    now_time = glfwGetTime();
    delta_time += (now_time - last_time) / (1.0 / fps_limit_);
    last_time = now_time;

    while (delta_time >= 1.0) {
      screen_handler_->OnUpdate((float)delta_time);
      updates++;
      delta_time--;
    }
    screen_handler_->OnRender();
    frames++;

    main_window_->GuiHandler()->Begin();
#ifdef DEBUG
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("FPS: %d", current_fps);
    ImGui::Text("Updates: %d", current_updates);
    ImGui::Dummy({0, 5});
    ImGui::End();
#endif
    screen_handler_->OnImGuiRender();

    main_window_->GuiHandler()->End();
    main_window_->SwapBuffers();
    // - Reset after one second
    if (glfwGetTime() - timer > 1.0) {
      timer++;
      current_fps = frames;
      current_updates = updates;
      std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
      updates = 0, frames = 0;
    }
  }
  return 0;
}
void Engine::ChangeTitle(const std::string &title) {
  main_window_->SetTitle(title);
}
float Engine::GetTime() const { return glfwGetTime(); }
} // namespace bsw
