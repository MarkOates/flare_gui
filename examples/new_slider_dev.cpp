



#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>





class NewSlider : public FGUIParent
{
private:

	class ScrollButton : public FGUIButton
	{
	public:
		ScrollButton(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIButton(parent, "", af::fonts["DroidSans.ttf -16"], x, y, w, h)
		{
		}
	};

	class ScrollHandle : public FGUIWidget
	{
	private:
		float min_y, max_y;
	public:
		ScrollHandle(FGUIParent *parent, float x, float y, float w, float h)
			: FGUIWidget(parent, new FGUICollisionBox(x, y, w, h))
		{
		}
		void set_min_max_coordinate_position(float min, float max)
		{
			min_y = min;
			max_y = max;
		}
		void on_drag(float x, float y, float dx, float dy) override
		{
			//place.position.x += dx;
			place.position.y = limit<float>(min_y+place.size.y/2, max_y-place.size.y/2, place.position.y+dy);
		}
		void on_draw() override
		{
			FGUIWidget::draw_outset(0, 0, place.size.x, place.size.y);
		}
		float get_position()
		{
			return (max_y - min_y) / place.position.y;
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



