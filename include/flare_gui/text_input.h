#ifndef FGUI_TEXT_INPUT_HEADER
#define FGUI_TEXT_INPUT_HEADER



#include <flare_gui/widget.h>
#include <flare_gui/widget_parent.h>
#include <allegro5/allegro_font.h>



class FGUITextInput : public FGUIWidget
{
protected:
	float mouse_cursor_x, mouse_cursor_y;
	void _insert_text(const char *str);
	void _handle_erase();
	std::string text;
	int cursor_pos;
	int cursor_end;
	float cursor_blink_counter;
	ALLEGRO_FONT *font;
	int text_x_offset;
	ALLEGRO_COLOR font_color;
	float padding;

	ALLEGRO_BITMAP *_text_render;
	void _update_text_and_selection_render(float len_to_cursor, float len_to_cursor_end);

public:
	explicit FGUITextInput(FGUIParent *parent, ALLEGRO_FONT *font, std::string initial_text, float x, float y, float w, float h);
	~FGUITextInput();

	void set_text(std::string text);
	std::string get_text();
	std::string get_selection();
	void set_font(ALLEGRO_FONT *font);
	ALLEGRO_FONT *get_font();
	void set_font_color(ALLEGRO_COLOR col);
	bool selection_active();
	void insert_text(std::string text);
	void clear_selection();

	void on_click() override;
	void on_mouse_move(float x, float y, float dx, float dy);
	void on_key_char();
	void on_draw();
	virtual void on_change();
	virtual void on_submit(); // usually instigated by the ENTER key
};






#endif