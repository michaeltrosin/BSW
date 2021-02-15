cmake_minimum_required(VERSION 3.17)
project(BSW)

set(CMAKE_CXX_STANDARD 17)

set(DEP_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_compile_definitions(DEBUG)

set(ENGINE BSWCore)
set(SANDBOX Sandbox)
# set(AUDIO AudioEngine)

add_executable(${SANDBOX}
        sandbox/main.cpp
        sandbox/screens/mainmenu_screen.cpp
        sandbox/screens/mainmenu_screen.h
        sandbox/screens/settings_screen.cpp
        sandbox/screens/settings_screen.h
        )

target_link_libraries(${SANDBOX} ${ENGINE})

# add_library(${AUDIO})
# Builds Engine as a library
add_library(${ENGINE}
        ${DEP_FOLDER}/glad/src/glad.c

        include/vendor/stb_image/stb_image.h
        include/vendor/stb_image/stb_image.cpp
        include/vendor/imgui/imconfig.h
        include/vendor/imgui/imgui.cpp
        include/vendor/imgui/imgui.h
        include/vendor/imgui/imgui_demo.cpp
        include/vendor/imgui/imgui_draw.cpp
        include/vendor/imgui/imgui_impl_glfw.cpp
        include/vendor/imgui/imgui_impl_glfw.h
        include/vendor/imgui/imgui_impl_opengl3.cpp
        include/vendor/imgui/imgui_impl_opengl3.h
        include/vendor/imgui/imgui_internal.h
        include/vendor/imgui/imgui_tables.cpp
        include/vendor/imgui/imgui_widgets.cpp
        include/vendor/imgui/imstb_rectpack.h
        include/vendor/imgui/imstb_textedit.h
        include/vendor/imgui/imstb_truetype.h

        engine/engine.cpp
        engine/engine.h
        engine/bsw.h

        engine/utils/imgui_utils.cpp
        engine/utils/imgui_utils.h
        engine/utils/file.h
        engine/utils/file.cpp
        engine/utils/timing.h
        engine/utils/macros.h
        engine/utils/mathf.h
        engine/utils/math/easing.h
        engine/utils/assertion.h

        engine/core/window/window.cpp
        engine/core/imgui/imgui_handler.h
        engine/core/imgui/imgui_handler.cpp
        engine/core/screen/screen_handler.cpp
        engine/core/screen/screen_handler.h
        engine/core/screen/screen.h
        engine/core/input/key_codes.h
        engine/core/input/mouse_codes.h
        engine/core/window/window.h
        engine/core/screen/screen_stack.cpp
        engine/core/screen/screen_stack.h
        engine/core/render/renderer2d.cpp
        engine/core/render/renderer2d.h
        engine/core/event/event.h
        engine/core/event/mouse_events.h
        engine/core/event/key_events.h
        engine/core/event/events.h
        engine/core/event/window_events.h
        engine/core/event/event_handler.cpp
        engine/core/event/event_handler.h
        engine/core/render/shader.cpp
        engine/core/render/shader.h
        engine/core/render/buffer/vertex_buffer.cpp
        engine/core/render/buffer/vertex_buffer.h
        engine/core/render/buffer/index_buffer.cpp
        engine/core/render/buffer/index_buffer.h
        engine/core/render/buffer/buffer_layout.h
        engine/core/render/vertex_array.cpp
        engine/core/render/vertex_array.h
        engine/core/render/texture/texture2d.cpp
        engine/core/render/texture/texture2d.h
        engine/core/render/gl_render.cpp
        engine/core/render/gl_render.h
        engine/core/event/screen_events.h
        engine/core/render/font/font.cpp
        engine/core/render/font/font.h)

include_directories(engine)
include_directories(include/vendor)

include_directories(${DEP_FOLDER}/glad/include)
set_target_properties(${ENGINE} PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(${DEP_FOLDER}/glfw-3.3.2)
include_directories(${DEP_FOLDER}/glfw-3.3.2/include)

add_subdirectory(${DEP_FOLDER}/freetype-2.10.4)
include_directories(${DEP_FOLDER}/freetype-2.10.4/include)
# add_subdirectory(${DEP_FOLDER}/zlib)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${ENGINE} opengl32 glfw freetype)