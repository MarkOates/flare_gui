



#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>





class NewSlider : public FGUIParent
{
private:

	class ScrollButton : public FGUIButton
	{
	public:
		ScrollButton(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIButton(parent, "", af::fonts["DroidSans.ttf -16"], x, y, w, h) {}
		void on_click() override
		{
			FGUIButton::on_click();
			//static_cast<NewSlider *>(parent)->step_up();
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
			static_cast<NewSlider *>(parent)->on_change();
		}
		void on_draw() override
		{
			FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
		}
		float get_position()
		{
			return (place.position.y - min_y - place.size.y/2.0) / (max_y - min_y - place.size.y);
		}
		float set_position(float position_in_unit_value)
		{
			// TODO: check and see if an on_change is necessairy
			// float previous_pos = place.position.y;

			float new_pos = position_in_unit_value * (max_y - min_y - place.size.y) + (min_y + place.size.y/3.0);
			
			place.position.y = new_pos;

			// calculate the position of the scroll_handle
			//float non_unit_val = 

			//if (place.position.y != previous_pos) static_cast<NewSlider *>(parent)->on_change();
		}
		void on_key_down() override
		{
			std::cout << "min(" << min_y << ") max(" << max_y << ")" << std::endl;
			std::cout << "pos(" << place.position.y << ")" << std::endl;
		}
	};

	ScrollHandle *handle;

public:

	NewSlider(FGUIParent *parent, float x, float y, float w, float h)
		: FGUIParent(parent, new FGUICollisionBox(x, y, w, h))
	{
		new ScrollButton(this, w/2, w/2, w, w);
		new ScrollButton(this, w/2, h-w/2, w, w);

		handle = new ScrollHandle(this, w/2, h/2, w, w);
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
/*
	void set_position(float position_unit_val)
	{
		handle->set_position(limit<float>(0.0, 1.0, position_unit_val));
		// this->on_change() happens from the handle
	}
	void step_up()
	{
		float step_rate = 0.01;
		handle->set_position(handle->get_position() + step_rate);
	}
	void step_down()
	{
		float step_rate = 0.01;
		handle->set_position(handle->get_position() - step_rate);
	}
*/
	virtual void on_change() {}
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



