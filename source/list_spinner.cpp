



#include <flare_gui/widgets/list_spinner.h>

#include <flare_gui/widgets/text_input.h>
#include <flare_gui/widgets/button.h>





FGUIListSpinner::FGUIListSpinner(FGUIWidget *parent, float x, float y, float w, float h)
	: FGUISpinner(parent, x, y, w, h)
	, it(items.begin())
{}




int FGUIListSpinner::add_item(std::string item)
{
	items.push_back(item);
	it = items.begin();
	text_input->set_text(*it);
	return items.size();
}




void FGUIListSpinner::sort()
{
	std::sort(items.begin(), items.end());
}




void FGUIListSpinner::set_val(std::string strval)
{
	// the behavior of this function will do nothing
}




void FGUIListSpinner::increment()
{
	if (items.empty()) return;

	it--;
	if (it < items.begin()) it = items.end()-1;
	text_input->set_text(*it);
	on_change();
}




void FGUIListSpinner::decrement()
{
	if (items.empty()) return;

	it++;
	if (it >= items.end()) it = items.begin();
	text_input->set_text(*it);
	on_change();
}	





