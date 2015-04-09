




#include <flare_gui/widget_parent.h>

#include <allegro_flare/allegro_flare.h>





FGUIParent::FGUIParent(FGUIParent *parent, FGUICollisionArea *collision_area)
	: FGUIWidget(parent, collision_area)
	, mouse_blocked(false)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIParent");
	attr.set(FGUI_ATTR__FGUI_IS_PARENT, "true");
	attr.set("id", "Parent" + tostring(widget_count));
	no_focus = true;

	//std::cout << "FGUIParent()" << std::endl;
}



#include <iostream>

FGUIParent::~FGUIParent()
	// ?
{
	children.delete_all();
}







void FGUIParent::draw_func()
{
	FGUIWidget::draw_func();

	place.start_transform();

	children.draw_all();

	place.restore_transform();
}




void FGUIParent::primary_timer_func()
{
	FGUIWidget::primary_timer_func();

	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->primary_timer_func();
}






void FGUIParent::receive_message(std::string message) {};




void FGUIParent::mouse_axes_func(float mx, float my, float mdx, float mdy)
{
	float tmx = mx;
	float tmy = my;
	float tmdx = mdx;
	float tmdy = mdy;

	collision_area->placement.transform_coordinates(&tmx, &tmy);
	collision_area->placement.transform_coordinates(&tmdx, &tmdy);

	if (parent && parent->mouse_blocked) mouse_blocked = true;
	else mouse_blocked = false;

	for (int i=(int)children.children.size()-1; i>=0; i--)
		children.children[i]->mouse_axes_func(tmx, tmy, mdx, mdy);

	FGUIWidget::mouse_axes_func(mx, my, mdx, mdy);
}



void FGUIParent::mouse_down_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->mouse_down_func();
	FGUIWidget::mouse_down_func();
}



void FGUIParent::mouse_up_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->mouse_up_func();
	FGUIWidget::mouse_up_func();
}



void FGUIParent::key_down_func() // should these be key_down_funcs() ?
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->key_down_func();
	FGUIWidget::key_down_func();
}



void FGUIParent::key_up_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->key_up_func();
	FGUIWidget::key_up_func();
}



void FGUIParent::key_char_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->key_char_func();
	FGUIWidget::key_char_func();
}



void FGUIParent::joy_down_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->joy_down_func();
	FGUIWidget::joy_down_func();
}



void FGUIParent::joy_up_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->joy_up_func();
	FGUIWidget::joy_up_func();
}



void FGUIParent::joy_axis_func()
{
	for (unsigned i=0; i<children.children.size(); i++)
		children.children[i]->joy_axis_func();
	FGUIWidget::joy_axis_func();
}



bool FGUIParent::set_focus_to(FGUIWidget *child)
	// returns true if the child was set from an unfocused state to a focused state
	// TODO: allow NULL as a parameter
{
	// check that this parent has this child
	if (!children.has_child(child)) return false;

	// make sure the child is not already focused
	if (child->is_focused()) return false;

	// if there are other widgets that have focus, blur them
	for (unsigned i=0; i<children.children.size(); i++)
	{
		if (children.children[i]->is_focused())
		{
			children.children[i]->set_as_unfocused();
		}
	}

	if (child)
	{
		child->focused = true;
		child->on_focus();
	}

	return true;
}





void FGUIParent::jump_focus_to_next_direct_descendent()
{
	jump_focus_to_direct_descendent_by_delta(1);
}

void FGUIParent::jump_focus_to_previous_direct_descendent()
{
	jump_focus_to_direct_descendent_by_delta(-1);
}

#include <flare_gui/widget_screen.h>
void FGUIParent::jump_focus_to_direct_descendent_by_delta(int offset)
{
	if (children.children.empty()) return;


	// get the currently focused child
	int focused_widget_index = -1;
	for (unsigned i=0; i<children.children.size(); i++)
	{
		if (children.children[i]->is_focused())
		{
			focused_widget_index = i;
			break;
		}
	}


	// calculate the next widget to focus
	int widget_to_focus = -1;
	if (focused_widget_index < 0)
	{
		// no widget is focused
		widget_to_focus = 0;
	}
	else
	{
		while (focused_widget_index < (int)children.children.size()) focused_widget_index += children.children.size(); // to avoid a weird negative offset bug
		widget_to_focus = (focused_widget_index + offset) % children.children.size();
	}


	// execute the focus and reposition the mouse cursor
	if (widget_to_focus < (int)children.children.size()) // this might not be necessairy... parent contains no children is checked at the beginning
	{
		//TODO: maybe find a better way to solve this interesting inelegence in this block of code
		ALLEGRO_DISPLAY *al_display = gimmie_super_screen()->display->display;  // < requires access to super screen, and a display... :/
		children.children[widget_to_focus]->set_as_focused();
		//if (hide_mouse_cursor_on_widget_jump)
		//{
		//		al_hide_mouse_cursor(al_display);
		//}
		//else
		{
			al_set_mouse_xy(al_display, children.children[widget_to_focus]->place.position.x, children.children[widget_to_focus]->place.position.y);
		}
	}
}





int FGUIParent::_index_count = 0;

int FGUIParent::get_num_ancestors()
{
	_index_count = 0;
	return __count_ancestors_recursive();
}

int FGUIParent::__count_ancestors_recursive()
{
	for (unsigned i=0; i<children.children.size(); i++)
	{
		_index_count++;
		if (children.children[i]->attr.matches(FGUI_ATTR__FGUI_IS_PARENT, "true"))
		{
			FGUIParent *p = static_cast<FGUIParent *>(children.children[i]);
			p->__count_ancestors_recursive();
		}
	}
	return _index_count;
}





FGUIWidget *FGUIParent::get_nth_ancestor(int n)
{
	_index_count = -1;
	return __get_nth_ancestor_recursive(n);
}

FGUIWidget *FGUIParent::__get_nth_ancestor_recursive(int n)
{
	for (unsigned i=0; i<children.children.size(); i++)
	{
		_index_count++;
		if (n == _index_count) return children.children[i];
		if (children.children[i]->attr.matches(FGUI_ATTR__FGUI_IS_PARENT, "true"))
		{
			FGUIParent *p = static_cast<FGUIParent *>(children.children[i]);
			FGUIWidget *widget = p->__get_nth_ancestor_recursive(n);
			if (widget) return widget;
		}
	}
	return NULL;
}

void FGUIParent::jump_focus_to_ancestor_by_delta(bool going_backward) //TODO: instead of "offset", now actually means direction. should be a bool
{
	int num_ancestors = get_num_ancestors();

	if (num_ancestors == 0) return;



	// get the currently focused child
	int currently_focused_ancestor = 0;

	for (int i=0; i<num_ancestors; i++)
	{
		FGUIWidget *ancestor = get_nth_ancestor(i);
		if (ancestor && ancestor->is_focused())
		{
			currently_focused_ancestor = i;
			break;
		}
	}


	
	// calculate the next widget to focus
	int next_widget_to_focus = 0;
	FGUIWidget *found_widget = NULL;
	//bool found = false;

	for(int offset_index = 1; offset_index < num_ancestors; offset_index++)
	{
		next_widget_to_focus = (currently_focused_ancestor + (going_backward ? -offset_index : offset_index));
		while (next_widget_to_focus < 0) next_widget_to_focus += num_ancestors; // to make a negative number positive
		next_widget_to_focus = next_widget_to_focus % num_ancestors;

		std::cout << next_widget_to_focus << " ";
		found_widget = get_nth_ancestor(next_widget_to_focus);
		if (found_widget->no_focus)
		{
			found_widget = NULL;
			std::cout << "notification[FGUIParent::jump_focus_to_ancestor_by_delta()] skipping a no_focus widget." << std::endl;
		}
		else { break; }
	}



	if (!found_widget)
	{
		std::cout << "could not jump to another widget." << std::endl;
		return;
	}


	// unselect anything else and and reposition the mouse
	unselect_all_ancestors_except(next_widget_to_focus);
	found_widget->set_as_focused();
	al_set_mouse_xy(al_get_current_display(), found_widget->place.position.x, found_widget->place.position.y);
}


void FGUIParent::unselect_all_ancestors_except(int n)
	// TODO: this is nasty and is like O(log n * log n) or something
	// you can make it much better
{
	int num_ancestors = get_num_ancestors();
	FGUIWidget *widget = NULL;

	for (int i=0; i<num_ancestors; i++)
	{
		widget = get_nth_ancestor(i);
		if (!widget) continue;
		if (i==n)
		{
			if (!widget->is_focused()) widget->set_as_focused();
		}
		else
		{
			if (widget->is_focused()) widget->set_as_unfocused();
		}
	}
}
