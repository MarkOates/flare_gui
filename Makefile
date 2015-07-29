

# This is a makefile for FlareGUI that builds into a static library
# For information about FlareGUI see the README.md file in the root directory
# FlareGUI is a GUI extension of Allegro Flare



# ENVIRONMENT

ALLEGRO_DIR=E:/allegro-5.1.11-mingw-edgar
ALLEGRO_FLARE_DIR=E:/allegro_flare
FGUI_DIR=E:/flare_gui


# BUILD TREE

FGUI_SRC_DIR=source
OBJ_DIR=obj
OBJ_EXT=o
FGUI_LIB_DIR=$(FGUI_DIR)/lib


# LINKED LIBRARIES
# these are the names of the libs you are linking in the example programs
ALLEGRO_MONOLITH_LIB=allegro_monolith-debug.dll
ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-mingw-4.8.1
FGUI_LIB=flare_gui-0.6.6-mingw-4.8.1


# GENERATED

FGUI_LIB_NAME=lib$(FGUI_LIB).a

# COMPILER SETTINGS

CFLAGS=-c -std=gnu++11


# MAKE

.PHONY: all clean_win clean_linux



# all builds the static library

all: style_assets.o button.o checkbox.o console.o dial.o draggable_region.o family.o framed_window.o image.o music_notation.o progress_bar.o scaled_text.o scroll_area.o scrollbar.o slider.o surface_area.o text.o text_area.o text_box.o text_input.o text_list.o toggle_button.o widget.o gui_screen.o window.o xy_controller.o bitmap.o box.o box_padded.o circle.o column.o row.o
	make lib	

lib: $(OBJ_DIR)/*.o
	ar rvs $(FGUI_LIB_DIR)/$(FGUI_LIB_NAME) $(OBJ_DIR)/*.$(OBJ_EXT)	


# below are the build targets for the individual objects, listed in alphabetical order by filename

style_assets.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

button.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

checkbox.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

console.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

dial.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

draggable_region.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

family.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

framed_window.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

image.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

music_notation.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

progress_bar.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

scaled_text.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

scroll_area.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

scrollbar.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

slider.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

surface_area.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

text.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

text_area.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

text_box.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

text_input.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

text_list.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

toggle_button.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

widget.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

gui_screen.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

window.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

xy_controller.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

# surface areas

bitmap.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

box.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

box_padded.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

circle.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

column.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

row.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/surface_areas/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include




# and the clean

clean_win:
	del $(OBJ_DIR)\*.$(OBJ_EXT)

clean_linux:
	rm $(OBJ_DIR)/*.$(OBJ_EXT)



#
# Example Programs
# ==========================
#


EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%.exe)

examples: $(EXAMPLE_OBJS)

bin/%.exe: examples/%.cpp
	g++ -std=gnu++11 $< -o $@ -IE:/allegro_flare/include -IE:/allegro-5.1.11-mingw-edgar/include -IE:/flare_gui/include -LE:/flare_gui/lib -lflare_gui-0.6.6-mingw-4.8.1 -LE:/allegro_flare/lib -lallegro_flare-0.8.6-mingw-4.8.1 -LE:/allegro-5.1.11-mingw-edgar/lib -lallegro_monolith-debug.dll




