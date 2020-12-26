BIN = ../xhui
CPP = g++
GLOBALFLAGS = -fno-omit-frame-pointer -O2 -g -std=c++17  -DHAS_LIB_ZLIB=1 -DHAS_LIB_GL=1 -DHAS_LIB_GLFW=1
CXXFLAGS =   $(GLOBALFLAGS)
CXXFLAGSLINKING =   -lz -lGL -lglfw $(GLOBALFLAGS)
prefix = /usr/local

OBJ = lib/base/array.o \
 lib/base/pointer.o \
 lib/base/strings.o \
 lib/file/file.o \
 lib/file/file_op.o \
 lib/file/msg.o \
 lib/file/path.o \
 lib/image/color.o \
 lib/image/image.o \
 lib/image/image_bmp.o \
 lib/image/image_jpg.o \
 lib/image/image_png.o \
 lib/image/image_tga.o \
 lib/image/ImagePainter.o \
 lib/math/complex.o \
 lib/math/interpolation.o \
 lib/math/math.o \
 lib/math/matrix.o \
 lib/math/matrix3.o \
 lib/math/plane.o \
 lib/math/quaternion.o \
 lib/math/random.o \
 lib/math/ray.o \
 lib/math/rect.o \
 lib/math/vector.o \
 lib/nix/nix.o \
 lib/nix/nix_draw.o \
 lib/nix/nix_light.o \
 lib/nix/nix_shader.o \
 lib/nix/nix_textures.o \
 lib/nix/nix_vertexbuffer.o \
 lib/nix/nix_view.o \
 lib/xhui/Window.o \
 lib/xhui/xhui.o

$(BIN) : $(OBJ) main.o
	$(CPP) $(OBJ) main.o -o $(BIN) $(CXXFLAGSLINKING)

all : $(BIN)

lib/base/array.o : lib/base/array.cpp lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h
	$(CPP) -c lib/base/array.cpp -o $@ $(CXXFLAGS)

lib/base/pointer.o : lib/base/pointer.cpp lib/base/pointer.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/msg.h
	$(CPP) -c lib/base/pointer.cpp -o $@ $(CXXFLAGS)

lib/base/strings.o : lib/base/strings.cpp lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h
	$(CPP) -c lib/base/strings.cpp -o $@ $(CXXFLAGS)

lib/file/file.o : lib/file/file.cpp lib/file/file.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/file/file.cpp -o $@ $(CXXFLAGS)

lib/file/file_op.o : lib/file/file_op.cpp lib/file/file.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/file/file_op.cpp -o $@ $(CXXFLAGS)

lib/file/msg.o : lib/file/msg.cpp lib/file/file.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/file/msg.cpp -o $@ $(CXXFLAGS)

lib/file/path.o : lib/file/path.cpp lib/file/path.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file_op.h
	$(CPP) -c lib/file/path.cpp -o $@ $(CXXFLAGS)

lib/image/color.o : lib/image/color.cpp lib/image/color.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/math/math.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/image/color.cpp -o $@ $(CXXFLAGS)

lib/image/image.o : lib/image/image.cpp lib/image/image.h lib/config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/image/image_bmp.h lib/image/image_tga.h lib/image/image_jpg.h lib/image/image_png.h lib/image/ImagePainter.h lib/image/Painter.h
	$(CPP) -c lib/image/image.cpp -o $@ $(CXXFLAGS)

lib/image/image_bmp.o : lib/image/image_bmp.cpp lib/image/image.h lib/config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/image/image_bmp.cpp -o $@ $(CXXFLAGS)

lib/image/image_jpg.o : lib/image/image_jpg.cpp lib/image/image.h lib/config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/image/image_jpg.cpp -o $@ $(CXXFLAGS)

lib/image/image_png.o : lib/image/image_png.cpp lib/image/image.h lib/config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/image/image_png.cpp -o $@ $(CXXFLAGS)

lib/image/image_tga.o : lib/image/image_tga.cpp lib/image/image.h lib/config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/image/image_tga.cpp -o $@ $(CXXFLAGS)

lib/image/ImagePainter.o : lib/image/ImagePainter.cpp lib/image/ImagePainter.h lib/image/Painter.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/rect.h lib/image/image.h lib/config.h lib/math/complex.h
	$(CPP) -c lib/image/ImagePainter.cpp -o $@ $(CXXFLAGS)

lib/math/complex.o : lib/math/complex.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/complex.cpp -o $@ $(CXXFLAGS)

lib/math/interpolation.o : lib/math/interpolation.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/math/interpolation.cpp -o $@ $(CXXFLAGS)

lib/math/math.o : lib/math/math.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/math.cpp -o $@ $(CXXFLAGS)

lib/math/matrix.o : lib/math/matrix.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/math/matrix.cpp -o $@ $(CXXFLAGS)

lib/math/matrix3.o : lib/math/matrix3.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/math/matrix3.cpp -o $@ $(CXXFLAGS)

lib/math/plane.o : lib/math/plane.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/plane.cpp -o $@ $(CXXFLAGS)

lib/math/quaternion.o : lib/math/quaternion.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/math/quaternion.cpp -o $@ $(CXXFLAGS)

lib/math/random.o : lib/math/random.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h
	$(CPP) -c lib/math/random.cpp -o $@ $(CXXFLAGS)

lib/math/ray.o : lib/math/ray.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/ray.cpp -o $@ $(CXXFLAGS)

lib/math/rect.o : lib/math/rect.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/rect.cpp -o $@ $(CXXFLAGS)

lib/math/vector.o : lib/math/vector.cpp lib/math/math.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h
	$(CPP) -c lib/math/vector.cpp -o $@ $(CXXFLAGS)

lib/nix/nix.o : lib/nix/nix.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h
	$(CPP) -c lib/nix/nix.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_draw.o : lib/nix/nix_draw.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h
	$(CPP) -c lib/nix/nix_draw.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_light.o : lib/nix/nix_light.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h
	$(CPP) -c lib/nix/nix_light.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_shader.o : lib/nix/nix_shader.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h
	$(CPP) -c lib/nix/nix_shader.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_textures.o : lib/nix/nix_textures.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h lib/image/image.h
	$(CPP) -c lib/nix/nix_textures.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_vertexbuffer.o : lib/nix/nix_vertexbuffer.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h
	$(CPP) -c lib/nix/nix_vertexbuffer.cpp -o $@ $(CXXFLAGS)

lib/nix/nix_view.o : lib/nix/nix_view.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/nix/nix_common.h lib/image/image.h
	$(CPP) -c lib/nix/nix_view.cpp -o $@ $(CXXFLAGS)

lib/xhui/Window.o : lib/xhui/Window.cpp lib/xhui/Window.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/xhui/xhui.h
	$(CPP) -c lib/xhui/Window.cpp -o $@ $(CXXFLAGS)

lib/xhui/xhui.o : lib/xhui/xhui.cpp lib/xhui/xhui.h lib/xhui/Window.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h
	$(CPP) -c lib/xhui/xhui.cpp -o $@ $(CXXFLAGS)

main.o : main.cpp lib/nix/nix.h lib/config.h lib/nix/nix_config.h lib/base/base.h lib/base/macros.h lib/base/array.h lib/base/strings.h lib/file/file.h lib/file/msg.h lib/file/file_op.h lib/file/path.h lib/math/math.h lib/image/color.h lib/math/vector.h lib/math/matrix.h lib/math/matrix3.h lib/math/quaternion.h lib/math/plane.h lib/math/rect.h lib/math/complex.h lib/math/interpolation.h lib/math/random.h lib/math/ray.h lib/nix/nix_draw.h lib/nix/nix_light.h lib/nix/nix_vertexbuffer.h lib/nix/nix_shader.h lib/nix/nix_view.h lib/nix/nix_textures.h lib/xhui/xhui.h lib/xhui/Window.h
	$(CPP) -c main.cpp -o $@ $(CXXFLAGS)

install :
	mkdir -p $(prefix)/share/xhui
	cp $(BIN) $(prefix)/bin

clean :
	rm -f $(BIN)
	find . -name "*.o" -exec rm -f {} \;
	find . -name "*.a" -exec rm -f {} \;

