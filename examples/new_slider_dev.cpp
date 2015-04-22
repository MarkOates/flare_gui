



#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>





class NewSlider : public FGUIParent
{
private:

	class ScrollUpButton : public FGUIButton
	{
	public:
		ScrollUpButton(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIButton(parent, "", af::fonts["DroidSans.ttf -16"], x, y, w, h) {}
		void on_click() override
		{
			FGUIButton::on_click();
			static_cast<NewSlider *>(parent)->step_up();
		}
	};

	class ScrollDownButton : public FGUIButton
	{
	public:
		ScrollDownButton(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIButton(parent, "", af::fonts["DroidSans.ttf -16"], x, y, w, h) {}
		void on_click() override
		{
			FGUIButton::on_click();
			static_cast<NewSlider *>(parent)->step_down();
		}
	};

	class ScrollHandle : public FGUIWidget
	{
	private:
		float min_y, max_y;
	public:
		ScrollHandle(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
			, min_y(0)
			, max_y(0)
		{
		}
		void set_min_max_coordinate_position(float min_val, float max_val)
		{
			min_y = min_val;
			max_y = max_val;
		}
		void on_drag(float x, float y, float dx, float dy) override
		{
			place.position.y = limit<float>(min_y+place.size.y/2, max_y-place.size.y/2, place.position.y+dy);
			parent->on_change();
		}
		void on_draw() override
		{
			FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
		}
		float get_position()
		{
			return (place.position.y - min_y - place.size.y/2.0) / (max_y - min_y - place.size.y);
		}
		void set_position(float position_in_unit_value)
		{
			// TODO: check and see if an on_change is necessairy
			// float previous_pos = place.position.y;

			float previous_pos = place.position.y;

			position_in_unit_value = limit<float>(0.0, 1.0, position_in_unit_value);
			float new_pos = position_in_unit_value * (max_y - min_y - place.size.y) + (min_y + place.size.y/2.0);
			place.position.y = new_pos; 

			if (place.position.y != previous_pos) parent->on_change();
		}
	};

	ScrollHandle *handle;
   ScrollUpButton *up_button;
	ScrollDownButton *down_button;

public:

	NewSlider(FGUIParent *parent, float x, float y, float w, float h)
		: FGUIParent(parent, new FGUICollisionBox(x, y, w, h))
		, handle(NULL)
		, up_button(NULL)
		, down_button(NULL)
	{
		up_button = new ScrollUpButton(this, w/2, w/2, w, w);
		down_button = new ScrollDownButton(this, w/2, h-w/2, w, w);

		handle = new ScrollHandle(this, w/2, h/2, w, w*3);
		handle->set_min_max_coordinate_position(w, h-w);
	}
	void on_draw() override
	{
		al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::gray);
	}
	float get_position()
	{
		return handle->get_position();
	}
	void step_up()
	{
		float step_rate = 0.1;
		handle->set_position(handle->get_position() - step_rate);
	}
	void step_down()
	{
		float step_rate = 0.1;
		handle->set_position(handle->get_position() + step_rate);
	}
	void set_position(float position_in_unit_value)
	{
		handle->set_position(position_in_unit_value);
	}
	void on_key_down() override
	{
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_DOWN) step_down();
		else if (af::current_event->keyboard.keycode == ALLEGRO_KEY_UP) step_up();
	}
};






class Project : public FGUIScreen
{
public:
	FGUIText *position_text;
	NewSlider *slider;
	Project(Display *display)
		: FGUIScreen(display)
		, position_text(NULL)
		, slider(NULL)
	{
		this->draw_focused_outline = false;

		slider = new NewSlider(this, 200, 200, 20, 200);

		position_text = new FGUIText(this, 250, display->height()/2, af::fonts["DroidSans.ttf 20"], "(position)");
	}
	void on_timer() override
	{
		position_text->set_text(tostring(slider->get_position()));
	}
};






int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display();
	Project *proj = new Project(display);
	af::run_loop();
}



