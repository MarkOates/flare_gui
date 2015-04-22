Goals and Desired Features
==========================


* Widget constructor that takes a list of parameters in string format

* Change DataAttr to Attributes (this is actually an AllegroFlare feature)


Unimplemented goals since version (0.6.2)
-----------------------------------------

* The constructor of FGUIButton needs to have the ALLEGRO_FONT parameter removed.  Get it from the parent (somehow)

* Make a FGUIIconButton (for awesome font icons) :/

* A Globals data store, for something like settings, maybe font names or something.  The Globals might include some generated content, like a gradient image, a noise image, a diagonal lines texture image, a standard GUI font.

* fix the dependency for a gradient bitmap in some of the widgets.
	
* Decide on a design strategy involving the default alignment of buttons and other gui objects.  About half the time I want to align the thing left, the other time center.  I think this is going to turn into a style sheet kind of thing.


Documentation
-------------

* clarify the FGUIWiddget::attach_widget()-detach_widget()-ownership-Parent-construction-registration.  Who registers what?  When is an object removable and how is a child properly created and deleted?

* clarify which function should be overloaded when making widgets.  Only the FGUIWidget should use mouse_axes_func().  If you're creating a widget, overload the on_* functions (`on_key_down()` `on_focus()` `on_mouse_move(..)` etc)






