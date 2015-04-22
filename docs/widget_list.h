



//
// Standard Widgets in FGUI
// 

FGUICheckbox(FGUIParent *parent, float x, float y, float size);

FGUIButton(FGUIParent *parent, std::string text, float x, float y, float w, float h);

FGUIFramedWindow(FGUIParent *parent, float x, float y, float w, float h);

FGUIImage(FGUIParent *parent, ALLEGRO_BITMAP *bitmap, float x, float y);

FGUIMusicNotation(FGUIParent *parent, float x, float y);

FGUINotificationBubble(FGUIParent *parent, std::string text, float x=300, float y=200)

// this might be (val, x, y, w, h)
FGUIProgressBar(FGUIParent *parent, float x, float y, float w=300, float h=26, float val=0.6);

// this might be (font_filename, font_size, text, x, y)
FGUIScaledText(FGUIParent *parent, float x, float y, std::string text);

// might be (content_parent, x, y, w, h)
FGUIScrollView(FGUIParent *parent, float x, float y, float w, float h, FGUIParent *content_parent);

FGUIVerticalSlider(FGUIParent *parent, float x, float y, float w, float h);

// might be (text, x, y)
FGUIText(FGUIParent *parent, float x, float y, std::string text);

FGUITextArea(FGUIParent *parent, std::string text, float x, float y, float w, float h);

FGUITextBox(FGUIParent *parent, std::string text, float x, float y, float width, float height);

explicit FGUITextInput(FGUIParent *parent, std::string initial_text, float x, float y, float w, float h);

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




