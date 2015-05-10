

# This is a makefile for FlareGUI that builds into a static library
# For information about FlareGUI see the README.md file in the root directory
# FlareGUI is a GUI extension of Allegro Flare



# ENVIRONMENT

ALLEGRO_DIR=E:/allegro-5.1.8-mingw-4.7.0
ALLEGRO_FLARE_DIR=E:/allegro_flare
FGUI_DIR=E:/flare_gui


# BUILD TREE

FGUI_SRC_DIR=source
OBJ_DIR=obj
OBJ_EXT=o
FGUI_LIB_DIR=$(FGUI_DIR)/lib
FGUI_LIB_NAME=libflare_gui-0.6.5-mingw-4.8.1.a


# COMPILER SETTINGS

CFLAGS=-c -std=gnu++11


# MAKE

.PHONY: all clean_win clean_linux



# all builds the static library

all: button.o checkbox.o collision_area.o collision_bitmap.o collision_box.o collision_box_padded.o collision_circle.o collision_column.o collision_row.o console.o dial.o draggable_region.o family.o framed_window.o image.o music_notation.o progress_bar.o scaled_text.o scroll_area.o scrollbar.o slider.o text.o text_area.o text_box.o text_input.o text_list.o toggle_button.o widget.o gui_screen.o window.o
	make lib	

lib: $(OBJ_DIR)/*.o
	ar rvs $(FGUI_LIB_DIR)/$(FGUI_LIB_NAME) $(OBJ_DIR)/*.$(OBJ_EXT)	


# below are the build targets for the individual objects, listed in alphabetical order by filename

button.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

checkbox.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_area.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_bitmap.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_box.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_box_padded.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_circle.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_column.o:
	g++ $(CFLAGS) $(FGUI_SRC_DIR)/$(basename $@).cpp -o $(OBJ_DIR)/$(basename $@).$(OBJ_EXT) -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

collision_row.o:
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




# and the clean

clean_win:
	del $(OBJ_DIR)\*.$(OBJ_EXT)

clean_linux:
	rm $(OBJ_DIR)/*.$(OBJ_EXT)





#
# example programs
#

examples: dev_automation_controller.exe dev_clock_widget.exe dev_piano_keyboard.exe dev_software_keyboard.exe ex_calculator.exe ex_flare_gui.exe ex_framed_window.exe ex_function_parser.exe ex_keyboard_joystick_modes.exe ex_music_calculator.exe ex_scroll_area.exe ex_scrollbar.exe ex_skeleton.exe ex_text_list.exe ex_widget_inspector.exe ex_widgets.exe dev_notification_bubble.exe

EXAMPLESDIR=./examples

# these are the names of the libs you are linking
ALLEGRO_MONOLITH_LIB=allegro-5.1.8-monolith-md
ALLEGRO_FLARE_LIB=allegro_flare-0.8.5-mingw-4.8.1
FGUI_LIB=flare_gui-0.6.5-mingw-4.8.1

dev_automation_controller.exe: ./examples/dev_automation_controller.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

dev_clock_widget.exe: ./examples/dev_clock_widget.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

dev_piano_keyboard.exe: ./examples/dev_piano_keyboard.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

dev_software_keyboard.exe: ./examples/dev_software_keyboard.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_calculator.exe: ./examples/ex_calculator.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_flare_gui.exe: ./examples/ex_flare_gui.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_framed_window.exe: ./examples/ex_framed_window.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_function_parser.exe: ./examples/ex_function_parser.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_keyboard_joystick_modes.exe: ./examples/ex_keyboard_joystick_modes.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_music_calculator.exe: ./examples/ex_music_calculator.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_scroll_area.exe: ./examples/ex_scroll_area.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_scrollbar.exe: ./examples/ex_scrollbar.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_skeleton.exe: ./examples/ex_skeleton.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_text_list.exe: ./examples/ex_text_list.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_widget_inspector.exe: ./examples/ex_widget_inspector.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

ex_widgets.exe: ./examples/ex_widgets.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib

dev_notification_bubble.exe: ./examples/dev_notification_bubble.cpp
	g++ $(CFLAGS) $(EXAMPLESDIR)/$(basename $@).cpp -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include
	g++ $(basename $@).o -o $(EXAMPLESDIR)/$(basename $@).exe -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib -L$(FGUI_DIR)/lib




