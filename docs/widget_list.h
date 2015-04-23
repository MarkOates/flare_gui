



//
// Standard Widgets in FGUI
// 


// Text

FGUIText(FGUIParent *parent, float x, float y, std::string text);
FGUIScaledText(FGUIParent *parent, float x, float y, std::string text);
FGUITextBox(FGUIParent *parent, float x, float y, float w, float h, std::string text);
FGUINotificationBubble(FGUIParent *parent, float x, float y, std::string text);
FGUITextList(FGUIParent *parent, float x, float y, float w);


// Containers and Frames

FGUIWindow(FGUIParent *parent, float x, float y, float w, float h);
FGUIFramedWindow(FGUIParent *parent, float x, float y, float w, float h);
FGUIScrollView(FGUIParent *parent, float x, float y, float w, float h, FGUIParent *content_parent);


// Inputs and Controls

FGUITextArea(FGUIParent *parent, float x, float y, float w, float h, std::string text);
FGUITextInput(FGUIParent *parent, float x, float y, float w, float h, std::string initial_text);
FGUIButton(FGUIParent *parent, float x, float y, float w, float h, std::string text);
FGUICheckbox(FGUIParent *parent, float x, float y, float size);
FGUIVerticalSlider(FGUIParent *parent, float x, float y, float w, float h);


// Graphics and Data Visualization

FGUIImage(FGUIParent *parent, float x, float y, ALLEGRO_BITMAP *bitmap);
FGUIMusicNotation(FGUIParent *parent, float x, float y);
FGUIProgressBar(FGUIParent *parent, float x, float y, float w, float h, float val);






//
// Base Widgets in FGUI
//

FGUIWidget(FGUIParent *parent, FGUICollisionArea *collision_area);
FGUIParent(FGUIParent *parent, FGUICollisionArea *collision_area);
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

FGUIDraggableRegion(FGUIParent *parent, float x, float y, float w, float h);




