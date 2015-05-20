

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
		new FGUIDial(this, 400, 300, 80);
		new FGUIXYController(this, 600, 400, 200, 200);
	}
};




int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display();
	Project *project = new Project(display);
	af::run_loop();
	return 0;
}


