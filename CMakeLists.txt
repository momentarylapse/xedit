# created by xmake

cmake_minimum_required(VERSION 3.21)
project(xhui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE
	src/lib/any/any.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/image/color.cpp
	src/lib/image/image.cpp
	src/lib/image/image_bmp.cpp
	src/lib/image/image_jpg.cpp
	src/lib/image/image_png.cpp
	src/lib/image/image_tga.cpp
	src/lib/image/ImagePainter.cpp
	src/lib/math/complex.cpp
	src/lib/math/interpolation.cpp
	src/lib/math/mat3.cpp
	src/lib/math/mat4.cpp
	src/lib/math/math.cpp
	src/lib/math/plane.cpp
	src/lib/math/quaternion.cpp
	src/lib/math/random.cpp
	src/lib/math/ray.cpp
	src/lib/math/rect.cpp
	src/lib/math/vec2.cpp
	src/lib/math/vec3.cpp
	src/lib/math/vec4.cpp
	src/lib/nix/nix.cpp
	src/lib/nix/nix_buffer.cpp
	src/lib/nix/nix_draw.cpp
	src/lib/nix/nix_framebuffer.cpp
	src/lib/nix/nix_light.cpp
	src/lib/nix/nix_shader.cpp
	src/lib/nix/nix_textures.cpp
	src/lib/nix/nix_vertexbuffer.cpp
	src/lib/nix/nix_view.cpp
	src/lib/os/CommandLineParser.cpp
	src/lib/os/config.cpp
	src/lib/os/date.cpp
	src/lib/os/file.cpp
	src/lib/os/filesystem.cpp
	src/lib/os/formatter.cpp
	src/lib/os/msg.cpp
	src/lib/os/path.cpp
	src/lib/os/stream.cpp
	src/lib/os/terminal.cpp
	src/lib/os/time.cpp
	src/lib/xhui/controls/Button.cpp
	src/lib/xhui/controls/CheckBox.cpp
	src/lib/xhui/controls/Control.cpp
	src/lib/xhui/controls/DrawingArea.cpp
	src/lib/xhui/controls/Edit.cpp
	src/lib/xhui/controls/Grid.cpp
	src/lib/xhui/controls/HeaderBar.cpp
	src/lib/xhui/controls/Label.cpp
	src/lib/xhui/controls/ListView.cpp
	src/lib/xhui/draw/font.cpp
	src/lib/xhui/Painter.cpp
	src/lib/xhui/Panel.cpp
	src/lib/xhui/Theme.cpp
	src/lib/xhui/Window.cpp
	src/lib/xhui/xhui.cpp
	src/main.cpp
)

add_executable(xhui ${SOURCE})

find_package(PkgConfig REQUIRED)


# lib: zlib mandatory
pkg_check_modules(ZLIB REQUIRED zlib)
target_include_directories(xhui PUBLIC ${ZLIB_INCLUDE_DIRS})
target_link_directories(xhui PUBLIC ${ZLIB_LIBRARY_DIRS})
list(APPEND DEPS ${ZLIB_LIBRARIES})
target_compile_options(xhui PUBLIC ${ZLIB_CFLAGS_OTHER})
target_compile_definitions(xhui PUBLIC HAS_LIB_ZLIB=1)

# lib: gl mandatory
pkg_check_modules(GL REQUIRED gl)
target_include_directories(xhui PUBLIC ${GL_INCLUDE_DIRS})
target_link_directories(xhui PUBLIC ${GL_LIBRARY_DIRS})
list(APPEND DEPS ${GL_LIBRARIES})
target_compile_options(xhui PUBLIC ${GL_CFLAGS_OTHER})
target_compile_definitions(xhui PUBLIC HAS_LIB_GL=1)

# lib: glfw mandatory
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(xhui PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_directories(xhui PUBLIC ${GLFW_LIBRARY_DIRS})
list(APPEND DEPS ${GLFW_LIBRARIES})
target_compile_options(xhui PUBLIC ${GLFW_CFLAGS_OTHER})
target_compile_definitions(xhui PUBLIC HAS_LIB_GLFW=1)

# lib: freetype2 mandatory
pkg_check_modules(FREETYPE2 REQUIRED freetype2)
target_include_directories(xhui PUBLIC ${FREETYPE2_INCLUDE_DIRS})
target_link_directories(xhui PUBLIC ${FREETYPE2_LIBRARY_DIRS})
list(APPEND DEPS ${FREETYPE2_LIBRARIES})
target_compile_options(xhui PUBLIC ${FREETYPE2_CFLAGS_OTHER})
target_compile_definitions(xhui PUBLIC HAS_LIB_FREETYPE2=1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)

target_link_libraries(xhui PRIVATE ${DEPS})

target_compile_definitions(xhui PUBLIC INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

install(TARGETS xhui DESTINATION bin)
install(FILES "static/OpenSans-Regular.ttf" DESTINATION share/xhui)