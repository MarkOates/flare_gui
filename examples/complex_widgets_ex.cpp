#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>






class FGUIButtonSet : public FGUIWidget
{
public:
	void add_button_option(std::string text)
	{

	}
};





class Project : public FGUIScreen
{
public:
	Project(Display *display)
		: FGUIScreen(display)
	{
		new FGUIText(this, 100, 100, af::fonts["DroidSans.ttf 20"], "This is a normal text box.");
		new FGUIScaledText(this, 100, 150, "DroidSans.ttf", 20, "This is a scaled text box.  It renders smoothly when in motion.");
		new FGUICheckbox(this, 100, 200, 20);
		new FGUIButton(this, "Click Me!", 150, 250, 100, 40);
		new FGUIVerticalSlider(this, 110, 340, 20, 80);
		new FGUIVerticalSlider(this, 140, 340, 20, 80);
		new FGUIVerticalSlider(this, 170, 340, 20, 80);
		new FGUITextInput(this, af::fonts["DroidSans.ttf 20"], "Input some text here", 250, 450, 360, 40);
		//new FGUIScaledText(this, 100, 300, "DroidSans.ttf", 20, "This is a scaled text box.  It renders smoothly when in motion.");
	}
};




void main()
{
	af::initialize();
	Display *display = af::create_display(800, 600, NULL);
	Project *project = new Project(display);
	af::run_loop();
}
