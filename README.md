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
* FGUIIntSpinner
* FGUIListSpinner
* FGUIMusicNotation
* FGUIProgressBar
* FGUIScaledText
* FGUIScreen
* FGUIScrollArea
* FGUIScrollBar
* FGUISpinner
* FGUIVerticalSlider
* FGUIText
* FGUITextArea
* FGUITextBox
* FGUITextInput
* FGUITextList
* FGUIToggleButton
* FGUIXYController
* FGUIWidget
* FGUIWindow


Build Instructions
------------------

FlareGUI requires Allegro 5.1.10 or greater and AllegroFlare 0.8.5.

#### 1. Clone the repo

```bash
$ git clone https://github.com/MarkOates/flare_gui
```

#### 2. Make the project

If you're building with `g++`, you might want to use the makefile.  Before running `make`, open `Makefile` and modify `ALLEGRO_DIR`, `ALLEGRO_FLARE_DIR`, and `FGUI_DIR` to point to the respective project's directories.  After you've done that, then run `make` from the command line.

```bash
$ cd flare_gui
$ make
```

#### 3. Make the example

FlareGUI comes with some cool example programs in the `examples/` directory.  They're great for getting a feel of how a typical FlareGUI program might work.  Build the examples by typing `make examples` while still in the project's root folder.

```bash
$ make examples
```

#### 4. (optional) Use the the [`flare_bootstrap`](https://github.com/MarkOates/flare_bootstrap) project on GitHub

After you have the libraries ready, you might want to try the [`flare_bootstrap`](https://github.com/MarkOates/flare_bootstrap) project, which has basic boilerplate project code for AllegroFlare, FlareGUI, and vanilla Allegro projects along with a Makefile.  Also included is a boilerplate project that combines AllegroFlare and FlareGUI into a 3D Pipeline.  Get that here:

```bash
$ git clone https://github.com/MarkOates/flare_bootstrap
```
