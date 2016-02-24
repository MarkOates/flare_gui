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


   // add a new item to the end of the list
   int add_item(std::string item);

   // add a new item to the end of the list
   int add_items(std::vector<std::string> new_items);

   // sorts the list of elements in alphabetical order
   void sort();


   // returns the currently selected item in the spinner
   std::string get_val();

   //(currently not implemented)
   void set_val(std::string strval) override;

   // sets the currently selected item to the next one in the list
   void increment() override;

   // sets the currently selected item to the previous one in the list
   void decrement() override;
};



#endif

