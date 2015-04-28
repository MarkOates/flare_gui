



#include <allegro_flare/allegro_flare.h>

#include <flare_gui/widgets/text_list.h>
#include <flare_gui/collision_box.h>
#include <flare_gui/widget_screen.h>





FGUIListItem::FGUIListItem() {};







FGUITextList::FGUITextList(FGUIWidget *parent, float x, float y, float w)
	: FGUIWidget(parent, new FGUICollisionBox(x, y, w, 20))
	, currently_selected_item(0)
{
	attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUITextList");
	attr.set("id", "TextList" + tostring(get_num_created_widgets()));
}



void FGUITextList::add_item(std::string item)
{
	// TODO: insert()
	// also, change selection if the new added item is before or after this item, k? :)
	items.push_back(item);
}



void FGUITextList::select_item(int index)
{
	std::string *item = get_item(index);
	if (!item) { std::cout << "FGUIList["<< attr.get("id") << "] cannot select item at index " << index; return; }
	else currently_selected_item = index;
}



std::string *FGUITextList::get_item(int index)
{
	if (index < 0 || index >= (int)items.size()) return NULL;
	return &items[index];
}



std::string *FGUITextList::get_selected_item()
{
	return get_item(currently_selected_item);
}



void FGUITextList::move_selected_item(int delta)
{
	currently_selected_item += delta;
	while (currently_selected_item < 0) currently_selected_item += items.size();
	currently_selected_item = currently_selected_item % items.size();
}



void FGUITextList::on_key_char()
{
	if (!is_focused()) return;
	switch(af::current_event->keyboard.keycode)
	{
	case ALLEGRO_KEY_DOWN:
		move_selected_item(1);
		break;
	case ALLEGRO_KEY_UP:
		move_selected_item(-1);
		break;
	}
}



float FGUITextList::get_item_height(int index)
{
	float item_padding = 5;
	float item_height = 20;
	return item_height + item_padding*2;
}



int FGUITextList::get_item_index_at(float x, float y)
{
	float item_padding = 5;
	float item_height = 20;
	float padding_x = 16*2, padding_y = 8*2;

	// transform the coordin
	float cursor_y = padding_y;
	for (unsigned i=0; i<items.size(); i++)
	{
		//draw_item(cursor, i);
		cursor_y += get_item_height(i);
		if (y < cursor_y) return i;
	}
	return -1;
}



void FGUITextList::on_select() {}



bool FGUITextList::select_at(float x, float y)
{
	int item_at = get_item_index_at(x, y);
	if (item_at == -1 || item_at == currently_selected_item) return false;
	currently_selected_item = item_at;
	on_select();
	return true;
}



bool FGUITextList::select_at_mouse_cursor() // need to eventually account for multiple mouse cursors.
{
	ALLEGRO_MOUSE_STATE mouse_state;
	al_get_mouse_state(&mouse_state);
	float x = mouse_state.x, y = mouse_state.y;
	place.transform_coordinates(&x, &y);

	return select_at(x, y);
}



void FGUITextList::joy_down_func()
{
	FGUIWidget::joy_down_func();
	if (!mouse_over) return;

	if (af::current_event->joystick.button == 0) // TODO: this should not be a hard-coded "0"
	{
		select_at_mouse_cursor();
	}
}



void FGUITextList::mouse_down_func()
{
	FGUIWidget::mouse_down_func();
	if (!mouse_over) return;

	//std::cout << "(" << mouse_state.x << ", " << mouse_state.y << ") -> (" << x << ", " << y << ")" << std::endl;
	select_at_mouse_cursor();
}



void FGUITextList::draw_item(vec2d position, int index)
	// returns the height of this item in the list
{
	if (index < 0 || index >= (int)items.size()) return;

	float item_padding = 5;
	position.y += item_padding;
	bool item_is_selected = index == (this->currently_selected_item);

	ALLEGRO_FONT *font = af::fonts["DroidSans.ttf 18"];

	if (item_is_selected)
	{
		//font = fonts["DroidSans-Bold_0.ttf 24"];

		float width = al_get_text_width(font, items[index].c_str());
		float height = al_get_font_line_height(font);

		float text_center = position.x + width/2;
		float text_middle = position.y + height/2;

		width += 22;
		height += 4;
		al_draw_filled_rounded_rectangle(text_center - width/2, text_middle - height/2,
			text_center + width/2, text_middle + height/2, 3, 3, color::color(gimmie_super_screen()->focused_outline_color, 0.2));
	}

	al_draw_text(font, color::color(color::black, item_is_selected ? 1.0 : 0.3), position.x, position.y+2, NULL, items[index].c_str());
	al_draw_text(font, item_is_selected ? color::mix(color::white, color::yellow, 0.0) : color::white, position.x, position.y, NULL, items[index].c_str());
}



void FGUITextList::on_draw()
{
	this->draw_inset(0, 0, place.size.x, place.size.y);
	float padding_x = 16*2, padding_y = 8*2;

	vec2d cursor = vec2d(padding_x, padding_y);
	for (unsigned i=0; i<items.size(); i++)
	{
		draw_item(cursor, i);
		cursor.y += get_item_height(i);
	}

	cursor += vec2d(padding_x, padding_y);
	place.size.y = cursor.y;
}
