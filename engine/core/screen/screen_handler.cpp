//
// Created by Michael on 11.02.2021.
//

#include "screen_handler.h"

#include <core/event/event.h>

namespace bsw {

void ScreenHandler::SwitchScreen(const std::string &name) {
  if (current_screen_)
    current_screen_->OnClose();
  current_screen_ = (*screen_stack_)[name];
  ASSERT(current_screen_, "Screen is null!");

  current_screen_->OnShow();
}

void ScreenHandler::SwitchScreen(int index) {
  if (current_screen_)
    current_screen_->OnClose();
  current_screen_ = (*screen_stack_)[index];
  ASSERT(current_screen_, "Screen is null!");

  current_screen_->OnShow();
}

ScreenHandler::ScreenHandler() { screen_stack_ = CreateSingle<ScreenStack>(); }

void ScreenHandler::OnRender() {
  if (current_screen_)
    current_screen_->OnRender();
}

void ScreenHandler::OnImGuiRender() {
  if (current_screen_)
    current_screen_->OnImGuiRender();
}

void ScreenHandler::OnUpdate(float delta_time) {
  if (current_screen_)
    current_screen_->OnUpdate(delta_time);
}

void ScreenHandler::OnEvent(Event &event) {
  if (current_screen_)
    current_screen_->OnEvent(event);
}
} // namespace bsw