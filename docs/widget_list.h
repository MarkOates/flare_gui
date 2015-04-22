



//
// Standard Widgets in FGUI
// 

FGUICheckbox(FGUIParent *parent, float x, float y, float size);

FGUIButton(FGUIParent *parent, float x, float y, float w, float h, std::string text);

FGUIFramedWindow(FGUIParent *parent, float x, float y, float w, float h);

FGUIImage(FGUIParent *parent, float x, float y, ALLEGRO_BITMAP *bitmap);

FGUIMusicNotation(FGUIParent *parent, float x, float y);

FGUINotificationBubble(FGUIParent *parent, std::string text, float x, float y)/////

FGUIProgressBar(FGUIParent *parent, float x, float y, float w, float h, float val);

FGUIScaledText(FGUIParent *parent, float x, float y, std::string text);

FGUIScrollView(FGUIParent *parent, float x, float y, float w, float h, FGUIParent *content_parent);

FGUIVerticalSlider(FGUIParent *parent, float x, float y, float w, float h);

FGUIText(FGUIParent *parent, float x, float y, std::string text);

FGUITextArea(FGUIParent *parent, std::string text, float x, float y, float w, float h);/////

FGUITextBox(FGUIParent *parent, std::string text, float x, float y, float width, float height);/////

FGUITextInput(FGUIParent *parent, std::string initial_text, float x, float y, float w, float h);/////

FGUITextList(FGUIParent *parent, float x, float y, float w);

FGUIWindow(FGUIParent *parent, float x, float y, float w, float h);





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




