
- goals from 0.6.2, and...

- remove boost dependency in text_box.cpp




// note: the following comments below are goals from the previous version (0.6.2)

the constructor of FGUIButton needs to have the ALLEGRO_FONT parameter removed.  Get it from the parent (somehow)

Make a FGUITextButton (text only)... maybe it inherits FGUIButton or something.

maaaaybe ... Make a FGUIIconButton (for awesome font icons) :/

(possibly) a Globals data store, for something like settings, maybe font names or something

the Globals might include some generated content, like a gradient image, a noise image, a diagonal lines texture image, a standard GUI font.

fix the need for a gradient bitmap in some of the widgets.
	- button
	- checkbox
	
there's an issue with alignment of buttons and other gui objects.  About half the time I want to align the thing left, the other time center.  I think this is going to turn into a style sheet kind of thing.

blank widget constructors (that can receive parameters through a string)

Widgets should no longer be an instanciation of DataAttr, but have a DataAttr element called "attr";

the FGUIWiddget::attach_widget()-detach_widget()-ownership-Parent-construction-registration relationship isn't very clear.  Who registers what?  When is an object removable and how is a child properly created and deleted?

remove the boost dependency in FGUITextBox

I'm also unclear *which* function(s) I should be overloading when making widgets.  What access level am I using?  mouse_axes_func()?  on_mouse_move()?







// DONE:
// DONE:
// DONE:


make FGUIChildren (it's basically a container)
{
	std::vector<FGUIWidget *> children;
	bool has()
	bool get()
	bool get_by_id();
	// etc.
}

so FGUIParent would have an element
{
	FGUIChildren children;
	children.register(child);
	children.remove(child);
}