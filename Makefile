

# This is a makefile for FlareGUI that builds into a static library
# For information about FlareGUI see the README.md file in the root directory
# FlareGUI is a GUI extension of Allegro Flare



# ENVIRONMENT

ALLEGRO_DIR=/users/markoates/Repos/allegro
ALLEGRO_FLARE_DIR=/users/markoates/Repos/allegro_flare
FGUI_DIR=/users/markoates/Repos/flare_gui


# BUILD TREE

FGUI_SRC_DIR=source
OBJ_DIR=obj
OBJ_EXT=.o
EXE_EXTENSION=
# EXE_EXTENSION=.exe
FGUI_LIB_DIR=$(FGUI_DIR)/lib


# LINKED LIBRARIES
# these are the names of the libs you are linking in the example programs

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro
ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-clang-7.0.2
FGUI_LIB=flare_gui-0.6.6-mingw-4.8.1



# GENERATED

FGUI_LIB_NAME=lib$(FGUI_LIB).a



# COMPILER SETTINGS

CFLAGS=-c -std=gnu++11



# CORE FILES

WIDGET_ITEMS=style_assets button checkbox console dial draggable_region family framed_window image int_spinner labeled_checkbox list_spinner music_notation progress_bar scaled_text scroll_area scrollbar slider spinner surface_area text text_area text_box text_input text_list toggle_button widget gui_screen window xy_controller 
SURFACE_AREA_ITEMS=bitmap box box_padded circle column row

WIDGET_OBJ_FILES=$(WIDGET_ITEMS:%=obj/%$(OBJ_EXT))
SURFACE_AREA_OBJ_FILES=$(SURFACE_AREA_ITEMS:%=obj/%$(OBJ_EXT))



# MAKE

.PHONY: all clean_win clean_linux



# all builds the static library

all: $(WIDGET_OBJ_FILES) $(SURFACE_AREA_OBJ_FILES)
	make lib	

lib: $(OBJ_DIR)/*$(OBJ_EXT)
	ar rvs $(FGUI_LIB_DIR)/$(FGUI_LIB_NAME) $(OBJ_DIR)/*$(OBJ_EXT)	




# below are the build targets for the objects

$(WIDGET_OBJ_FILES): obj/%$(OBJ_EXT) : source/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include

$(SURFACE_AREA_OBJ_FILES): obj/%$(OBJ_EXT) : source/surface_areas/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< -I$(ALLEGRO_DIR)/include -I$(ALLEGRO_FLARE_DIR)/include -I$(FGUI_DIR)/include




# and the clean

clean_win:
	del $(OBJ_DIR)\*$(OBJ_EXT)

clean_linux:
	rm $(OBJ_DIR)/*$(OBJ_EXT)



#
# Example Programs
# ==========================
#


EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%$(EXE_EXTENSION))

examples: $(EXAMPLE_OBJS)

bin/%$(EXE_EXTENSION): examples/%.cpp lib/lib$(FGUI_LIB).a
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I$(FGUI_DIR)/include -L$(FGUI_DIR)/lib -l$(FGUI_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -l$(ALLEGRO_FLARE_LIB) -L$(ALLEGRO_DIR)/lib $(ALLEGRO_LIBS) 



