# The Crank Framework

Crank is a very simple and primative runtime management framework. It allows you to create pages following a virtual base class template. Pages are then pushed to a stack structure that allows traversal to and from different states.

## Build

## Include in your own Project

## Usage

This framework is built upon a state stack. Developers built states from the `base_state` class that contains virtual member function prototypes such as `draw()` `update()` `handle_events()` etc.
States are like pages, each page gives a different functionality given by the developer depending on the purpose the page must serve.

eg. A menu page might just render text as menu options and doesn't constantly require a redraw while the main game state would have the screen rerendered every frame.

States can also have additional member functions added to them to provide additional funcionality.
