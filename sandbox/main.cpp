//
// Created by Michael on 10.02.2021.
//
#include <engine.h>
#include <utils/assertion.h>
#include <utils/file.h>

#include <core/screen/screen.h>
#include <core/screen/screen_handler.h>

#include "screens/mainmenu_screen.h"
#include "screens/settings_screen.h"

using namespace bsw;

int main() {
  auto &engine = Engine::Create(WindowProps{"bsw"});

  engine.GetScreenHandler()->AddScreen<MainMenu>("main");
  engine.GetScreenHandler()->AddScreen<SettingsScreen>("settings");
  engine.GetScreenHandler()->SwitchScreen("main");

  // std::filesystem::temp_directory_path()

  return engine.Run();
}