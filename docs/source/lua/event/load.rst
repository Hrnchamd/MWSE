
load
========================================================

The **load** event fires when the game is about to load. This event allows scripts to block loading.

.. note:: See the `Event Guide`_ for more information on event data, return values, and filters.


Event Data
--------------------------------------------------------

fileName
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
`String`_. The filename of the save we want to load, not including file extension.

quickLoad
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
`Boolean`_. Read-only. True if this load was caused by pressing the quickload key. 

newGame
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
`Boolean`_. Read-only. True if we're starting a new game.


Filter
--------------------------------------------------------
This event may be filtered by `fileName`.


.. _`Event Guide`: ../guide/events.html
.. _`String`: ../type/lua/string.html
.. _`Boolean`: ../type/lua/boolean.html
