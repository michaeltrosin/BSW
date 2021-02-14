//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <core/screen/screen.h>
#include <core/event/events.h>

class MainMenu : public bsw::Screen {
 public:
   void OnUpdate(float delta_time) override;

   void OnRender() override;

   void OnImGuiRender() override;

   void OnEvent(bsw::Event &event) override;
};



