#ifndef FGUI_WIDGET_HEADER
#define FGUI_WIDGET_HEADER




#include <flare_gui/collision_area.h>
#include <allegro_flare/data_attr.h>
#include <allegro_flare/clipboard_win.h> // this should eventually be replaced with a cross-platform clipboard solution
#include <allegro_flare/color.h>

#include <allegro_flare/bit_flags.h>

#include <flare_gui/family.h>


class FGUIParent;
class FGUIScreen;
class FGUIFamily;
class Motion;
class FontBin;
class SampleBin;


/*
enum WIDGET_FLAGS
{
	// states
	FGUI_FLAG_MOUSE_OVER = 0x01,
	FGUI_FLAG_MOUSE_DOWN_ON_OVER = 0x02,
	FGUI_FLAG_FOCUSED = 0x04,
	FGUI_FLAG_CAN_BE_DELETED = 0x08,
	FGUI_FLAG_ANIMATING_DELETE = 0x10,
	FGUI_FLAG_SOMETHING_ELSE = 0x20,

	// behaviors
	FGUI_FLAG_BRING_TO_FRONT_ON_FOCUS = 0x40
};
*/




#define FGUI_ATTR__FGUI_WIDGET_TYPE "FGUI_WIDGET_TYPE"
#define FGUI_ATTR__FGUI_IS_PARENT "FGUI_IS_PARENT"



class FGUIWidget
{
private:
	static int num_active_widgets; // holds the number of widgets that are currently being managed

protected:

	friend class FGUIParent;
	friend class FGUIScreen;
	friend class FGUIChildren;
	friend class FGUIFamily;
	friend class FGUIScrollView;
	
	FGUIFamily family;
	FGUIFamily &children; // this is exactly the same as family, but for dev-deprec purposes children is here and will removed eventually

	//FGUIParent *parent;
	static int widget_count; // a counter for numbering new widget ids
	bool mouse_over, mouse_down_on_over, focused, dragging, no_focus; // should implement a flag system instead ;)
		// ^^^ will need to add: skip_on_tab_focus (or no_focus), no_jumpout_on_tab

	// widget *developer* functions:
	virtual void draw_func();
	virtual void primary_timer_func();
	virtual void mouse_axes_func(float x, float y, float dx, float dy);
	virtual void mouse_down_func();
	virtual void mouse_up_func();
	virtual void key_down_func();
	virtual void key_up_func();
	virtual void key_char_func();
	virtual void joy_down_func();
	virtual void joy_up_func();
	virtual void joy_axis_func();

public:
	//BitFlags<int16_t> flags;    // << this should be added eventually
	bool delete_me;
	bool mouse_is_blocked; // was a part of FGUIParent
	DataAttr attr;

	FGUICollisionArea *collision_area;
	placement2d &place;

	FGUIWidget(FGUIWidget *parent, FGUICollisionArea *collision_area);
	virtual ~FGUIWidget();


	// convience (these might become depreciated)
	FGUIWidget *gimmie_super_parent();
	FGUIScreen *gimmie_super_screen();


	// ordering
	void bring_to_front();
	void send_message_to_parent(std::string message);
	virtual void receive_message(std::string message);


	// retrieval
	bool is_mouse_over();
	bool is_focused();
	void set_as_focused();
	void set_as_unfocused();


	///
	// widget behavior functions
	///

	virtual void on_focus();
	virtual void on_blur();

	// mouse
	virtual void on_mouse_enter();
	virtual void on_mouse_leave();
	virtual void on_mouse_move(float x, float y, float dx, float dy);
	virtual void on_mouse_down();
	virtual void on_mouse_up();
	virtual void on_mouse_wheel();
	virtual void on_click();
	virtual void on_drag(float x, float y, float dx, float dy);
	virtual void on_drop();

	// keybaord
	virtual void on_key_down();
	virtual void on_key_up();
	virtual void on_key_char();

	// joystick
	virtual void on_joy_down();
	virtual void on_joy_up();
	virtual void on_joy_axis();

	// other
	virtual void on_timer();
	virtual void on_draw();

	// state
	virtual void on_change();


	// static functions
	static int get_num_created_widgets();
	static int get_num_active_widgets();

public:
	// Down here are some static functions for drawing basic graphic elements for the GUI.
	// Insets (textarea, textinput, group frames), outsets (buttons, window bodys, etc)
	// and any other graphic elements that might be needed.  This design technique might
	// eventually be replaced with a more robust and configurable styling method.  But
	// for now, this simple solution is intended to be the first steps to detaching style
	// from widget drawing - if the user want it.

	void FGUIWidget::draw_inset(float x, float y, float w, float h);
	void FGUIWidget::draw_outset(float x, float y, float w, float h, ALLEGRO_COLOR col=color::hex("575962"));
};





#endif

