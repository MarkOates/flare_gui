

FGUIScreen and FGUIWidget
======================================


FGUIWidget
----------

FGUIWidget is the base class from which all widgets in FlareGUI come from.An end object that is derived directly from FGUIWidget is the last node in a tree and thus has no children. Some objects that are part of the SWS and are derived directly from FGUIWidget include FGUIButton, FGUIDraggableRegion, FGUIImage, FGUIProgressBar


FGUIScreen
----------

This is the main class that you use to derive your main project.  While it's possible to have multiple instances of FGUIScreen, it's best to start out keeping all of your GUI under one screen.  FGUIScreen is also derived from FGUIParent, and essentially acts as the root parent for all the objects in the GUI tree.


