FlareGUI
========

FlareGUI is a GUI extension for AllegroFlare.


```cpp
#include <flare_gui/flare_gui.h>


class Project : public FGUIScreen
{
public:
	Project(Display *display) : FGUIScreen(display)
	{
		new FGUIText(this, 100, 100, "This is a normal text box.");
		new FGUIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
		new FGUICheckbox(this, 100, 200, 20);
		new FGUIButton(this, 150, 250, 100, 40, "Click Me!");
		new FGUIVerticalSlider(this, 110, 340, 20, 80);
		new FGUIVerticalSlider(this, 140, 340, 20, 80);
		new FGUIVerticalSlider(this, 170, 340, 20, 80);
		new FGUITextInput(this, 250, 450, 360, 40, "Input some text here");
	}
};


void main()
{
	af::initialize();
	Display *display = af::create_display(800, 600, NULL);
	Project *project = new Project(display);
	af::run_loop();
}
```



Standard Widgets
----------------

* FGUIButton
* FGUICheckbox
* FGUIDial
* FGUIFramedWindow
* FGUIImage
* FGUIMusicNotation
* FGUIProgressBar
* FGUIScaledText
* FGUIScreen
* FGUIScrollArea
* FGUIVerticalSlider
* FGUIText
* FGUITextArea
* FGUITextBox
* FGUITextInput
* FGUITextList
* FGUIToggleButton
* FGUIWidget
* FGUIWindow


Build Instructions
------------------

FlareGUI requires Allegro 5.1.8 or greater and Allegro Flare 0.8.5.

#### 1. Clone the repo

`git clone https://github.com/MarkOates/allegro_flare`

#### 2. Make the project

If you're building with `g++`, you might want to use the makefile.  Before using, open `Makefile` and modify `ALLEGRO_DIR`, `ALLEGRO_FLARE_DIR`, and `FGUI_DIR` to point to the respective project's directories.  You will also need to create two folders, `lib/` and `obj/`, in your `flare_gui` directory.  Then run `make` from the command line.

`make`

#### 3. Make the example

`make examples`

#### 4. Clone the flare_gui_bootstrap project on GitHub (optional)

The [`flare_gui_bootstrap`](https://github.com/MarkOates/flare_gui_bootstrap) comes with basic empty project and a Makefile.  Get that here:

`git clone https://github.com/MarkOates/flare_gui_bootstrap`
