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
	src/lib/xhui/Controls/Button.cpp
	src/lib/xhui/Controls/Control.cpp
	src/lib/xhui/Controls/DrawingArea.cpp
	src/lib/xhui/Controls/Edit.cpp
	src/lib/xhui/Controls/Grid.cpp
	src/lib/xhui/Controls/HeaderBar.cpp
	src/lib/xhui/Controls/Label.cpp
	src/lib/xhui/draw/font.cpp
	src/lib/xhui/Painter.cpp
	src/lib/xhui/Theme.cpp
	src/lib/xhui/Window.cpp
	src/lib/xhui/xhui.cpp
	src/main.cpp
		src/lib/xhui/Controls/CheckBox.cpp
		src/lib/xhui/Controls/CheckBox.h
		src/lib/xhui/Controls/ListView.cpp
		src/lib/xhui/Controls/ListView.h
)

add_executable(xhui ${SOURCE})


# lib: zlib mandatory
find_package(ZLIB REQUIRED)
list(APPEND DEPS ZLIB::ZLIB)
add_compile_definitions(HAS_LIB_ZLIB=1)


# lib: gl mandatory
find_package(OpenGL REQUIRED)
list(APPEND DEPS OpenGL::OpenGL)
add_compile_definitions(HAS_LIB_GL=1)


# lib: glfw mandatory
find_package(glfw3 REQUIRED)
list(APPEND DEPS glfw)
add_compile_definitions(HAS_LIB_GLFW=1)


# lib: freetype2 mandatory
find_package(Freetype REQUIRED)
list(APPEND DEPS Freetype::Freetype)
add_compile_definitions(HAS_LIB_FREETYPE2=1)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(xhui PRIVATE Threads::Threads ${DEPS})

add_compile_definitions(INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

install(TARGETS xhui DESTINATION bin)

