#ifndef __FGUI_CHILDREN_HEADER
#define __FGUI_CHILDREN_HEADER




#include <deque>
#include <vector>

//#include <flare_gui/widget.h>
class FGUIWidget;
class FGUIParent;


class FGUIChildren
{
private:
	static int _index_count; // used internally for counting nodes in the tree

public:
	std::deque<FGUIWidget *> children; // hmm... some type of protection eventually maybe (not public)?

public:
	bool has_child(FGUIWidget *widget);
	void register_as_child(FGUIWidget *widget);
	void unregister_as_child(FGUIWidget *widget);
	static bool assign_child_to_new_parent(FGUIWidget *child_widget, FGUIParent *new_parent); // warning, this function may require some 
																				   // safety usage guidelines
																				   // reassigning a parent in the middle of
																				   // a loop in the children could cause
																				   // unintended consequences, for example
	void unfocus_all();
	void delete_all();
	void draw_all();
	void draw_all_except(FGUIWidget *widget); // hmm... a solution to a scroll-view and/or portal view draw-func access problem.
											  // I'm not sure about the appropriate solution to this one.

	// selection:
	FGUIWidget *get_element_by_id(std::string id);
	FGUIWidget *get_1st_element_with_attr(std::string key); // not tested
	FGUIWidget *get_1st_element_with_attr_val(std::string key, std::string val); // not tested

	// deep functions: these select recursively through the children's children
	FGUIWidget *get_nth_child_d(int n);
	int get_num_of_widgets_d();

private:
	// these are recursive search functions, they're entirely intended for internal use
	static FGUIWidget *__get_nth_child_recursive(FGUIChildren &children, int n);
	static int __get_num_widgets_recursive(FGUIChildren &children);
};




#endif