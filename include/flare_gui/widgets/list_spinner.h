#ifndef __FGUI_LIST_SPINNER_HEADER
#define __FGUI_LIST_SPINNER_HEADER



#include <flare_gui/widgets/spinner.h>



class FGUIListSpinner : public FGUISpinner
{
private:
	std::vector<std::string> items;
	std::vector<std::string>::iterator it;

public:
	FGUIListSpinner(FGUIWidget *parent, float x, float y, float w, float h);

	int add_item(std::string item);
	void sort();

	std::string get_val();
	void set_val(std::string strval) override;
	void increment() override;
	void decrement() override;
};



#endif

