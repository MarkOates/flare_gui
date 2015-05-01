#ifndef __AF_PIANO_KEYBOAD_HEADER
#define __AF_PIANO_KEYBOAD_HEADER



#include <allegro_flare/allegro_flare.h>
//#include <allegro_flare/midi_win.h> // this was stripped out, but will need to be implemented in a comprehensive way




class PianoKeyboardKey
{
public:
	float x, y, w, h;
	bool mouse_over;
	int midi_key_num;
	bool triggered;
	bool black_key;

	PianoKeyboardKey();

	bool collide(float mouse_x, float mouse_y);

	void set(float x, float y, float w, float h, int midi_key_num, bool black_key);

	void on_mouse_leave();
	void on_mouse_enter();
	void on_mouse_move(float mouse_x, float mouse_y);
	void on_mouse_down();
	void on_mouse_up();

	void switch_out();

	void draw();

	void trigger();
	void release();
};






class PianoControlButton
{
public:
	float x, y, w, h;
	bool mouse_over;

	bool collide(float mouse_x, float mouse_y);
	virtual void switch_out();
	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_mouse_click();
	virtual void on_mouse_down();
	virtual void on_mouse_up();
	void on_mouse_move(float mouse_x, float mouse_y);
	virtual void draw();
};




class PianoKeyboardScreen : public Screen
{
public:
	Display *display;
	placement2d placement;
	Motion motion_manager;
	vec2d mouse_screen, mouse_world;
	#define NUM_KEYS 48

	PianoKeyboardKey keys[NUM_KEYS];
	float w, h;

	PianoKeyboardScreen(Display *display);

	bool is_black_key(int num, std::vector<int> &set);

	void set_keys_to_diatonic();
	void set_keys_to_octatonic1();
	void set_keys_to_pentatonic();
	void set_keys_to_whole_tone();
	void set_keys_to_scale(int *set_array, int size);
	void set_keys_to_scale(std::vector<int> &set);

	void primary_timer_func() override;
	void mouse_axes_func() override;
	void mouse_down_func() override;
	void mouse_up_func() override;
};







#endif















//#include <allegro_flare_screens/piano_keyboard.h>




PianoKeyboardKey::PianoKeyboardKey()
	: mouse_over(false)
	, x(0)
	, y(0)
	, w(0)
	, h(0)
	, midi_key_num(0)
	, triggered(false)
	, black_key(false)
{}

void PianoKeyboardKey::set(float x, float y, float w, float h, int midi_key_num, bool black_key)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->midi_key_num = midi_key_num;
	this->black_key = black_key;
}

bool PianoKeyboardKey::collide(float mouse_x, float mouse_y)
{
	if (mouse_x < x) return false;
	if (mouse_y < y) return false;
	if (mouse_x >= x+w) return false;
	if (mouse_y >= y+h) return false;
	return true;
}

void PianoKeyboardKey::draw()
{
	al_draw_filled_rectangle(x, y, x+w, y+h, mouse_over ? color::deeppink : black_key ? color::hex("171720") : color::hex("f2f2f0"));
	al_draw_rounded_rectangle(x, y, x+w, y+h, black_key ? 0.5 : 2, black_key ? 0.5 : 2, color::black, 1.5);
	if (black_key)
	{
		al_draw_filled_rounded_rectangle(x+2, y, x+w-2, y+h-7, 2, 2, color::color(color::white, 0.1));
		al_draw_line(x+2, y+h-7, x+w-2, y+h-7, color::color(color::white, 0.25), 1.0);
	}
	if (midi_key_num==0) al_draw_filled_circle(x+w/2, y+h, w/5, color::dodgerblue);
	else if (midi_key_num%12 == 0) al_draw_circle(x+w/2, y+h, w/5, color::dodgerblue, 1.0);
}

void PianoKeyboardKey::on_mouse_leave()
{
	if (triggered) release();
}

void PianoKeyboardKey::on_mouse_enter()
{
}

void PianoKeyboardKey::switch_out()
{
	if (mouse_over) on_mouse_leave();
	mouse_over = false;
}

void PianoKeyboardKey::on_mouse_move(float mouse_x, float mouse_y)
{
	bool collide_now = collide(mouse_x, mouse_y);
	if (collide_now && !mouse_over) on_mouse_enter();
	if (!collide_now && mouse_over) on_mouse_leave();
	mouse_over = collide_now;
}

void PianoKeyboardKey::trigger()
{
	//midi_note_on(0, midi_key_num+60, 64);
	std::cout << "note triggered!" << std::endl;
	triggered = true;
}

void PianoKeyboardKey::release()
{
	//midi_note_off(0, midi_key_num+60);
	std::cout << "note released!" << std::endl;
	triggered = false;
}

void PianoKeyboardKey::on_mouse_down()
{
	if (mouse_over) trigger();
}

void PianoKeyboardKey::on_mouse_up()
{
	if (mouse_over) release();
}








/*
class PianoSignals
{
private:
	static std::vector<PianoSignals *> instances;
public:
	PianoSignals()
	{
		instances.push_back(this);
	}
	~PianoSignals()
	{
		std::vector<PianoSignals *>::iterator it = std::find(instances.begin(), instances.end(), this);
		if (it != instances.end()) instances.erase(it);
	}
	static void send_signal(int signal, void *data)
	{
		for (std::vector<PianoSignals *>::iterator it=instances.begin(); it!=instances.end(); it++)
			(*it)->recieve_signal(signal, data);
	}
	virtual void recieve_signal(int signal, void *data) {}
};
std::vector<PianoSignals *> PianoSignals::instances;
*/







bool PianoControlButton::collide(float mouse_x, float mouse_y)
{
	if (mouse_x < x) return false;
	if (mouse_y < y) return false;
	if (mouse_x >= x+w) return false;
	if (mouse_y >= y+h) return false;
	return true;
}

void PianoControlButton::switch_out()
{
	if (mouse_over) on_mouse_leave();
	mouse_over = false;
}

void PianoControlButton::on_mouse_enter() {}

void PianoControlButton::on_mouse_leave() {}

void PianoControlButton::on_mouse_click() {}

void PianoControlButton::on_mouse_down() {}

void PianoControlButton::on_mouse_up() {}

void PianoControlButton::on_mouse_move(float mouse_x, float mouse_y)
{
	bool collide_now = collide(mouse_x, mouse_y);
	if (collide_now && !mouse_over) on_mouse_enter();
	if (!collide_now && mouse_over) on_mouse_leave();
	mouse_over = collide_now;
}

void PianoControlButton::draw()
{
}









PianoKeyboardScreen::PianoKeyboardScreen(Display *display)
	: Screen(display)
	, motion_manager()
{
	set_keys_to_pentatonic();
	//init_midi();
	//if (!midi_out_device.empty()) { open_midi_device(midi_out_device[0]); }

	//camera.x = w/2 + 0.5;
	//camera.scale_x = 1.25;
	//camera.scale_y = 1.25;
	//camera.rotation = 0.1;
}

bool PianoKeyboardScreen::is_black_key(int num, std::vector<int> &set)
{
	for (std::vector<int>::iterator it=set.begin(); it!=set.end(); it++)
		if ((*it) == num) return false;
	return true;
}

void PianoKeyboardScreen::set_keys_to_diatonic()
{
	int myints[] = {0, 2, 4, 5, 7, 9, 11};
	std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
	set_keys_to_scale(set);
}

void PianoKeyboardScreen::set_keys_to_whole_tone()
{
	int myints[] = {0, 2, 4, 6, 8, 10};
	std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
	set_keys_to_scale(set);
}

void PianoKeyboardScreen::set_keys_to_octatonic1()
{
	int myints[] = {0, 1, 3, 4, 6, 7, 9, 10};
	std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
	set_keys_to_scale(set);
}

void PianoKeyboardScreen::set_keys_to_pentatonic()
{
	int myints[] = {0, 2, 4, 7, 9 };
	std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
	set_keys_to_scale(set);
}

void PianoKeyboardScreen::set_keys_to_scale(int *set_array, int size)
{
	std::vector<int> set(set_array, set_array + size / sizeof(int));
	set_keys_to_scale(set);
}

void PianoKeyboardScreen::set_keys_to_scale(std::vector<int> &set)
{
	float key_width = 20;
	float key_height = 100;
	float keyboard_padding[4] = { 4, 4, 4, 4 };

	// create keys here:
	for (int i=0; i<NUM_KEYS; i++)
		keys[i].set(i, 0, 1, 1, i-24, false);

	float x_cursor = 0;

	for (int i=0; i<NUM_KEYS; i++)
	{
		int val = i%12;
		if (is_black_key(val, set)) //val==1 || val==3 || val==6 || val==7 || val==8 || val==10)
			keys[i].black_key = true;
		else keys[i].black_key = false;

		if (keys[i].black_key)
		{
			keys[i].w = 0.5;
			keys[i].h = 0.6;
		}
		else
		{
			keys[i].w = 1.0;
			keys[i].h = 1.0;
		}

		if (i==0)
		{
			// don't move the cursor forward
		}
		else
		{
			bool previous_key_white = !keys[i-1].black_key;
			bool this_key_white = !keys[i].black_key;

			if (previous_key_white && this_key_white) x_cursor += 1.0;
			else if (previous_key_white && !this_key_white) x_cursor += 0.75;
			else if (!previous_key_white && !this_key_white) x_cursor += 0.5;
			else if (!previous_key_white && this_key_white) x_cursor += 0.25;
		}
		keys[i].x = x_cursor;

		if (i==(NUM_KEYS-1))
			x_cursor += keys[i].black_key ? 0.5 : 1.0;



		keys[i].x *= key_width;
		keys[i].y *= key_height;
		keys[i].w *= key_width;
		keys[i].h *= key_height;

		keys[i].x += keyboard_padding[3];
		keys[i].y += keyboard_padding[1];
	}

	w = x_cursor * key_width + keyboard_padding[3] + keyboard_padding[1];
	h = key_height + keyboard_padding[0] + keyboard_padding[2];
}

void PianoKeyboardScreen::primary_timer_func()
{
	motion_manager.update(af::time_now);
	placement.start_transform();

	al_draw_filled_rectangle(0, 0, w, h, color::hex("876833")); // dark tan
	//al_draw_filled_rectangle(0, 0, w, h, color::hex("172b43")); // dark blue

	for (int i=0; i<NUM_KEYS; i++)
		if (!keys[i].black_key) keys[i].draw();

	al_draw_filled_rectangle(0, 0, w, 2, color::hex("800818")); // red felt

	for (int i=0; i<NUM_KEYS; i++)
		if (keys[i].black_key) keys[i].draw();

	placement.restore_transform();
}

void PianoKeyboardScreen::mouse_axes_func()
{
	mouse_screen = vec2d(af::current_event->mouse.x, af::current_event->mouse.y);
	mouse_world = mouse_screen;
	placement.transform_coordinates(&mouse_world.x, &mouse_world.y);
		
	bool collided = false;
	for (int i=0; i<NUM_KEYS; i++)
	{
		if (keys[i].black_key)
		{
			if (collided) keys[i].switch_out();
			else
			{
				keys[i].on_mouse_move(mouse_world.x, mouse_world.y);
				if (keys[i].mouse_over) collided = true;
			}
		}
	}
	for (int i=0; i<NUM_KEYS; i++)
	{
		if (!keys[i].black_key)
		{
			if (collided) keys[i].switch_out();
			else
			{
				keys[i].on_mouse_move(mouse_world.x, mouse_world.y);
				if (keys[i].mouse_over) collided = true;
			}
		}
	}
}

void PianoKeyboardScreen::mouse_down_func()
{
	for (int i=0; i<NUM_KEYS; i++)
		keys[i].on_mouse_down();
}

void PianoKeyboardScreen::mouse_up_func()
{
	for (int i=0; i<NUM_KEYS; i++)
		keys[i].on_mouse_up();
}


























class Project : public Screen
{
public:
	Display *display;
	ALLEGRO_FONT *font;
	Project(Display *display)
		: Screen(display)
		, font(al_load_font("data/fonts/DroidSans.ttf", -20, ALLEGRO_FLAGS_EMPTY))
	{}
	void timer_func()
	{
		al_draw_text(font, color::white, 200, 100, ALLEGRO_ALIGN_CENTRE, "Project Screen active");
	}
};






int main(int argc, char *argv[])
{
	af::initialize();
	Display *display = af::create_display(1280, 800, false);

	Project *project = new Project(display);

	std::vector<int> major7;  major7.push_back(0); major7.push_back(4); major7.push_back(7); major7.push_back(11);


	PianoKeyboardScreen *piano_keyboard1 = new PianoKeyboardScreen(display);
	piano_keyboard1->placement.position.x = -200 + display->width()/2;
	piano_keyboard1->placement.position.y = display->height()/2;
	piano_keyboard1->placement.scale.x = 0.7;
	piano_keyboard1->placement.scale.y = 0.7;

	PianoKeyboardScreen *piano_keyboard5 = new PianoKeyboardScreen(display);
	piano_keyboard5->set_keys_to_scale(major7);
	piano_keyboard5->placement.position.y = 300 + display->height()/2;
	piano_keyboard5->placement.position.x = -200 + display->width()/2;
	piano_keyboard5->placement.scale.x = 0.7;
	piano_keyboard5->placement.scale.y = 0.7;

	PianoKeyboardScreen *piano_keyboard4 = new PianoKeyboardScreen(display);
	piano_keyboard4->set_keys_to_whole_tone();
	piano_keyboard4->placement.position.y = 150 + display->height()/2;
	piano_keyboard4->placement.position.x = -200 + display->width()/2;
	piano_keyboard4->placement.scale.x = 0.7;
	piano_keyboard4->placement.scale.y = 0.7;
	
	PianoKeyboardScreen *piano_keyboard2 = new PianoKeyboardScreen(display);
	piano_keyboard2->set_keys_to_diatonic();
	piano_keyboard2->placement.position.y = -150 + display->height()/2;
	piano_keyboard2->placement.position.x = -200 + display->width()/2;
	piano_keyboard2->placement.scale.x = 0.7;
	piano_keyboard2->placement.scale.y = 0.7;

	PianoKeyboardScreen *piano_keyboard3 = new PianoKeyboardScreen(display);
	piano_keyboard3->set_keys_to_octatonic1();
	piano_keyboard3->placement.position.y = -300 + display->height()/2;
	piano_keyboard3->placement.position.x = -200 + display->width()/2;
	piano_keyboard3->placement.scale.x = 0.7;
	piano_keyboard3->placement.scale.y = 0.7;

	std::vector<int> this_set; this_set.push_back(0); this_set.push_back(4); this_set.push_back(6);
		this_set.push_back(10); this_set.push_back(11);
	PianoKeyboardScreen *piano_keyboard6 = new PianoKeyboardScreen(display);
	piano_keyboard6->set_keys_to_scale(this_set);
	piano_keyboard6->placement.position.x = 250 + display->width()/2;
	piano_keyboard6->placement.position.y = 200 + display->height()/2;
	piano_keyboard6->placement.rotation = 0.2;
	piano_keyboard6->placement.scale.x = 0.7;
	piano_keyboard6->placement.scale.y = 0.7;
	//piano_keyboard5->camera.x -= 200;


//	SoftwareKeyboardScreen *software_keyboard = new SoftwareKeyboardScreen(display);

	af::run_loop();
}




