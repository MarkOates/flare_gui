#ifndef FGUI_WIDGET_PARENT_HEADER
#define FGUI_WIDGET_PARENT_HEADER




#include <flare_gui/widget.h>
#include <flare_gui/children.h>




class FGUIParent : public FGUIWidget
{
public:
	bool mouse_blocked;
	//FGUIChildren children;
	// FGUISignalSlots slots;  // < gotta do this eventually, I imagine.  dang...

	FGUIParent(FGUIParent *parent, FGUICollisionArea *collision_area);
	virtual ~FGUIParent(); //?


	// widget communication
	virtual void receive_message(std::string message);


	// if the use wishes to overload these, be sure to call
	// these functions in this class as well.
	// (I'm not sure exactly what the correct usage for
	// overloading/ignoring these functions should be)
	void draw_func();
	void primary_timer_func();
	void mouse_axes_func(float mx, float my, float mdx, float mdy);
	void mouse_down_func();
	void mouse_up_func(); // TODO: should these all be key_down_funcs() ? ... is there some long looping going on?
	void key_down_func();
	void key_up_func();
	void key_char_func();
	void joy_down_func();
	void joy_up_func();
	void joy_axis_func();




	// these are used
	//void on_focus(); //<< this should only be in the FGUIWidget, not the FGUIParent

	//bool set_focus_to(FGUIWidget *child); // TODO: implement this in FGUIChildren
	//void unfocus_all(); // <- this is implemented in "FGUIChildren children"
//	bool has_child(FGUIWidget *widget);

/*
	void jump_focus_to_next_direct_descendent(); // for the most part, these should be considered depreciated...
	void jump_focus_to_previous_direct_descendent();
	void jump_focus_to_direct_descendent_by_delta(int offset);

	int get_num_ancestors();
	FGUIWidget *get_nth_ancestor(int n);
	void jump_focus_to_ancestor_by_delta(bool going_backward=false); // this skipps no_focus elements
	void unselect_all_ancestors_except(int n); // this is dirty and could be optimized

private:
	static int _index_count; // used for counting down the tree
	int __count_ancestors_recursive(); 
	FGUIWidget *__get_nth_ancestor_recursive(int n);
	//void 
*/
};









#endif
