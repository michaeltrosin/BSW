cmake_minimum_required(VERSION 3.17)
project(BSW)

set(CMAKE_CXX_STANDARD 17)

set(DEP_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#TODO: Remove on release build!!
add_compile_definitions(DEBUG)

set(ENGINE BSWCore)
set(UILIB BSWUI)
set(SANDBOX Sandbox)
# set(AUDIO AudioEngine)

add_executable(${SANDBOX}
        sandbox/main.cpp
        sandbox/screens/test2d.cpp
        sandbox/screens/test2d.h
        )

target_link_libraries(${SANDBOX} ${ENGINE}
        ${UILIB}
        )

# add_library(${AUDIO})
add_library(${UILIB} uilib/ui_button.cpp uilib/ui_button.h)
target_link_libraries(${UILIB} ${ENGINE})

# Builds Engine as a library
add_library(${ENGINE}
        ${DEP_FOLDER}/glad/src/glad.c

        ${DEP_FOLDER}/include/vendor/stb_image/stb_image.h
        ${DEP_FOLDER}/include/vendor/stb_image/stb_image.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imconfig.h
        ${DEP_FOLDER}/include/vendor/imgui/imgui.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui.h
        ${DEP_FOLDER}/include/vendor/imgui/imgui_demo.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui_draw.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui_impl_glfw.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui_impl_glfw.h
        ${DEP_FOLDER}/include/vendor/imgui/imgui_impl_opengl3.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui_impl_opengl3.h
        ${DEP_FOLDER}/include/vendor/imgui/imgui_internal.h
        ${DEP_FOLDER}/include/vendor/imgui/imgui_tables.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imgui_widgets.cpp
        ${DEP_FOLDER}/include/vendor/imgui/imstb_rectpack.h
        ${DEP_FOLDER}/include/vendor/imgui/imstb_textedit.h
        ${DEP_FOLDER}/include/vendor/imgui/imstb_truetype.h

        engine/engine.cpp
        engine/engine.h
        engine/bsw.h

        engine/utils/imgui_utils.cpp
        engine/utils/imgui_utils.h
        engine/utils/file.h
        engine/utils/file.cpp
        engine/utils/timing.h
        engine/utils/macros.h
        engine/math/mathf.h
        engine/utils/assertion.h

        engine/core/window/window.h
        engine/core/window/window.cpp
        engine/core/imgui/imgui_handler.h
        engine/core/imgui/imgui_handler.cpp
        engine/core/screen/screen_handler.h
        engine/core/screen/screen_handler.cpp
        engine/core/screen/screen.h
        engine/core/screen/screen.cpp
        engine/core/input/key_codes.h
        engine/core/input/mouse_codes.h
        engine/core/screen/screen_stack.h
        engine/core/screen/screen_stack.cpp
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
        engine/core/font/font.cpp
        engine/core/font/font.h
        engine/core/font/font_manager.cpp
        engine/core/font/font_manager.h
        engine/math/color.cpp
        engine/math/color.h
        engine/core/render/camera.h
        engine/core/input/input.h
        engine/core/input/input.cpp
        engine/math/mathf.cpp
        engine/core/render/texture/texture_atlas.cpp
        engine/core/render/texture/texture_atlas.h
        engine/core/assets/asset_manager.cpp
        engine/core/assets/asset_manager.h
        )

include_directories(engine)
include_directories(uilib)
include_directories(${DEP_FOLDER}/include/vendor)

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

#
#   Copy resource folder to output
#
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY resources
   DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)