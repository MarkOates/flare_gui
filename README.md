FlareGUI
========

FlareGUI is an extension for AllegroFlare that adds GUI functionality.


```cpp
#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>


class Project : public FGUIScreen
{
public:
	Project(Display *display)
		: FGUIScreen(display)
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

* FGUICheckbox
* FGUIButton
* FGUIFramedWindow
* FGUIImage
* FGUIMusicNotation
* FGUINotificationBubble
* FGUIProgressBar
* FGUIScaledText
* FGUIScrollView
* FGUIVerticalSlider
* FGUIText
* FGUITextArea
* FGUITextBox
* FGUITextInput
* FGUITextList
* FGUIWindow


Base Widgets
------------

* FGUIWidget
* FGUIScreen


Build Instructions
------------------

FlareGUI requires Allegro 5.1.8 or greater and Allegro Flare 0.8.5.

If you're building with `g++`, you might want to use the makefile.  Before using, open `Makefile` and modify `ALLEGRO_DIR`, `ALLEGRO_FLARE_DIR`, and `FGUI_DIR` to point to the respective project's directories.  You will also need to create two folders, `lib/` and `obj/`, in your `allegro_flare` directory.  Then run `make` from the command line.


