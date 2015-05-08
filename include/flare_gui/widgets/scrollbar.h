#ifndef __FGUI_SCROLLBAR_HEADER
#define __FGUI_SCROLLBAR_HEADER




#include <flare_gui/widgets/button.h>




class FGUIScrollBar : public FGUIWidget
{
private:

	class ScrollUpButton : public FGUIButton
	{
	public:
		ScrollUpButton(FGUIWidget *parent, float x, float y, float w, float h);
		void on_click() override;
	};

	class ScrollDownButton : public FGUIButton
	{
	public:
		ScrollDownButton(FGUIWidget *parent, float x, float y, float w, float h);
		void on_click() override;
	};

	class ScrollRail : public FGUIWidget
	{
	public:
		float current_mouse_y;
		ScrollRail(FGUIWidget *parent, float x, float y, float w, float h);
		void on_draw() override;
		void on_mouse_move(float x, float y, float dx, float dy) override;
		void on_click();
	};

	class ScrollHandle : public FGUIWidget
	{
	private:
		float min_y, max_y;
	public:
		ScrollHandle(FGUIWidget *parent, float x, float y, float w, float h);
		void set_min_max_coordinate_position(float min_val, float max_val);
		void on_drag(float x, float y, float dx, float dy);
		void on_draw();
		float get_position();
		void set_position(float position_in_unit_value);
	};

	ScrollRail *rail;
	ScrollHandle *handle;
	ScrollUpButton *up_button;
	ScrollDownButton *down_button;

public:

	FGUIScrollBar(FGUIWidget *parent, float x, float y, float w, float h);
	float get_position();
	void jump_down();
	void jump_up();
	void step_up();
	void step_down();
	void set_position(float position_in_unit_value);
	void on_key_down(); 
	void on_draw();
};



#endif
