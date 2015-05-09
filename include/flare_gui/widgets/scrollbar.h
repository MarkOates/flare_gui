#ifndef __FGUI_SCROLLBAR_HEADER
#define __FGUI_SCROLLBAR_HEADER




#include <flare_gui/widget.h>




class FGUIScrollBar : public FGUIWidget
{
private:

	class UpButton : public FGUIWidget
	{
	public:
		UpButton(FGUIWidget *parent, float x, float y, float w, float h);
		void on_click() override;
		void on_draw() override;
	};

	class DownButton : public FGUIWidget
	{
	public:
		DownButton(FGUIWidget *parent, float x, float y, float w, float h);
		void on_click() override;
		void on_draw() override;
	};

	class Rail : public FGUIWidget
	{
	public:
		float current_mouse_y;
		Rail(FGUIWidget *parent, float x, float y, float w, float h);
		void on_draw() override;
		void on_mouse_move(float x, float y, float dx, float dy) override;
		void on_click();
	};

	class Handle : public FGUIWidget
	{
	private:
		float min_y, max_y;
	public:
		Handle(FGUIWidget *parent, float x, float y, float w, float h);
		void set_min_max_coordinate_position(float min_val, float max_val);
		void on_drag(float x, float y, float dx, float dy);
		void on_draw();
		float get_position();
		void set_position(float position_in_unit_value);
	};

	Rail *rail;
	Handle *handle;
	UpButton *up_button;
	DownButton *down_button;

public:
	FGUIScrollBar(FGUIWidget *parent, float x, float y, float w, float h);

	void step_up();
	void step_down();
	void jump_down();
	void jump_up();
	float get_position();
	void set_position(float position_in_unit_value);

	void on_key_down() override;
	void on_draw() override;
};



#endif

