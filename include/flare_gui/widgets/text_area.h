#ifndef __AF_TEXT_AREA_HEADER
#define __AF_TEXT_AREA_HEADER




#include <allegro5/allegro_font.h>

#include <flare_gui/widget.h>




class FGUITextArea : public FGUIWidget
{
private:
	class Cursor
	{
	private:
		int head_pos;
		int _anchor_pos;
		bool anchor_down;
	public:
		Cursor(int head_pos, int anchor_pos);

		void move(int delta);
		void move(int delta, int min, int max);
		void move_to(int pos);
		void move_to(int pos, int min, int max);
		void move_anchor_to_cursor();

		int pos();
		int anchor_pos();
		int get_start();
		int get_end();
		int get_selection_length();

		void set_anchor_down();
		void set_anchor_up();
		bool is_anchor_down();
		bool selection_active();
	};

private:
	std::string full_text;
	ALLEGRO_FONT *font;
	float cursor_blink_counter;
	Cursor cursor;

public:

	FGUITextArea(FGUIWidget *parent, float x, float y, float w, float h, std::string text);

	void move_cursor(int delta);
	void move_cursor_to(int pos);
	void move_cursor_to_next_of(std::string chars); // not fully implemented, mostly used for internal
	void move_cursor_to_previous_not_of(std::string chars); // not fully implemented, mostly used for internal
	void erase_selection();

	void set_text(std::string text);
	std::string get_text();
	std::string get_selection();
	void insert_text(std::string text);

	void on_draw() override;
	void on_key_down() override;
	void on_key_up() override;
	void on_key_char() override;
};






#endif
