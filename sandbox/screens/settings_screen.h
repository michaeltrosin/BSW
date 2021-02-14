//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <core/screen/screen.h>
#include <core/event/events.h>

class SettingsScreen : public bsw::Screen {
public:
  void OnRender() override;

  void OnImGuiRender() override;
};
