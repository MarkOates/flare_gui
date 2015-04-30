



//
// Standard Widgets in FGUI
// 


// Text

FGUIText(FGUIWidget *parent, float x, float y, std::string text);
FGUIScaledText(FGUIWidget *parent, float x, float y, std::string text);
FGUITextBox(FGUIWidget *parent, float x, float y, float w, float h, std::string text);
FGUINotificationBubble(FGUIWidget *parent, float x, float y, std::string text);
FGUITextList(FGUIWidget *parent, float x, float y, float w);


// Containers and Frames

FGUIWindow(FGUIWidget *parent, float x, float y, float w, float h);
FGUIFramedWindow(FGUIWidget *parent, float x, float y, float w, float h);
FGUIScrollView(FGUIWidget *parent, float x, float y, float w, float h, FGUIWidget *content_parent);


// Inputs and Controls

FGUITextArea(FGUIWidget *parent, float x, float y, float w, float h, std::string text);
FGUITextInput(FGUIWidget *parent, float x, float y, float w, float h, std::string initial_text);
FGUIButton(FGUIWidget *parent, float x, float y, float w, float h, std::string text);
FGUICheckbox(FGUIWidget *parent, float x, float y, float size);
FGUIVerticalSlider(FGUIWidget *parent, float x, float y, float w, float h);


// Graphics and Data Visualization

FGUIImage(FGUIWidget *parent, float x, float y, ALLEGRO_BITMAP *bitmap);
FGUIMusicNotation(FGUIWidget *parent, float x, float y);
FGUIProgressBar(FGUIWidget *parent, float x, float y, float w, float h, float val);






//
// Base Widgets in FGUI
//

FGUIWidget(FGUIWidget *parent, FGUICollisionArea *collision_area);
FGUIScreen(Display *display);






//
// FGUI Widget Components and Composition Elements
//

FGUICollisionBox(float x, float y, float w, float h);
FGUICollisionArea(float x, float y, float w, float h);
FGUICollisionBitmap(float x, float y, ALLEGRO_BITMAP *bitmap);
FGUICollisionBox(float x, float y, float w, float h);
FGUICollisionBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl);
FGUICollisionCircle(float x, float y, float r);
FGUICollisionColumn(float x, float w);
FGUICollisionRow(float y, float h);

FGUIChildren();

FGUIDraggableRegion(FGUIWidget *parent, float x, float y, float w, float h);




