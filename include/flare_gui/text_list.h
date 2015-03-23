#ifndef __AF_TEXT_LIST_HEADER
#define __AF_TEXT_LIST_HEADER





#include <string>
#include <vector>

#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/vec2d.h>

#include <flare_gui/widget.h>





class FGUIListItem // TODO: maybe.. abstract FGUITextList into a FGUIList<T> template 
{
private:
	std::string item;
public:
	FGUIListItem();
	virtual vec2d draw_item(vec2d position) = 0; // returns the width/height of the item
};





class FGUITextList : public FGUIWidget
{
public:
	int currently_selected_item;
	std::vector<std::string> items;
	FontBin fonts;

public:
	FGUITextList(FGUIParent *parent, float x, float y, float w);

	// TODO: clean up this nasty beast :x

	void add_item(std::string item);
	void select_item(int index);
	std::string *get_item(int index);
	std::string *get_selected_item();
	void move_selected_item(int delta);
	void on_key_char() override;
	float get_item_height(int index);
	int get_item_index_at(float x, float y);
	virtual void on_select();
	bool select_at(float x, float y);
	bool select_at_mouse_cursor();
	void joy_down_func();
	void mouse_down_func();
	virtual void draw_item(vec2d position, int index);
	void on_draw() override;
};




#endif