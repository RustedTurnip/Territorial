# Changelog
---
#### v0.7.0 - [DD-MM-2018]
###### Features:
- Introduce interactive map (with overlays being displayed for each Territory when the mouse is over it)
###### Patches:
- Fix thread scope issues that would cause threads to terminate prematurely causing undefined behaviour
- Add thread synchronisation to the LoadingScreen class to prevent the potential for race conditions


---
#### v0.6.0 - [24-01-2018]
###### Features:
- Loading screen, with implementation between `MenuView` and `GameView`
- Add Splash screen with implementation (using placeholder canalside_splash.png)
###### Patches:
- Update fixed master loop rate to 1/60 of a second


---
#### v0.5.1 - [03-01-2018]
###### Patches:
- Renamed territorial.h and territorial.cpp to Territorial.h and Territorial.cpp respectively
- Removed arbitrary test print statements from Reader.cpp


---
#### v0.5.0 - [03-01-2018]
###### Features:
- Introduce Map class
- Add map image to act as background for game
- Integrate Map class with game
###### Patches:
- N/A


---
#### v0.4.0 - [28-12-2017]
###### Features:
- Added Reader to read in Map Data
- Added map data to resource folder
- Added a Territory class to be used to represent territories within the code
###### Patches:
- Pressing the left system key (windows key) minimises the window
- Remove unused `stdafx.h` header called in some source files


---
#### v0.3.0 - [27-12-2017]
###### Features:
- Added Frame Rate regulation (in the form of a limit) within execution loop
- Introduced a ViewManager system for controlling screen changes
- Added redirection from the main menu to a blank GameView upon clicking any Menu button
###### Patches:
- N/A


---
#### v0.2.0 - [16-12-2017]
###### Features:
- Made game's window fullscreen (using `esc` to close window)
- Added changelog to documentation
- Add UI Elements Tbutton and TanimatedButton for Menu
- Add res/ directory including Territorial title logo and cinzel font
- Add Identifiers.h header (with some pre-emptive data)
- Add Territorial main menu
###### Patches:
- Remove unused `stdafx.h` header called in some source files


---
#### v0.1.0 - [11-12-2017]
###### Features:
- Created 'master' loop in which the game will run, providing a platform on which the game will be developed
- Created an arbitrarily sized window that the game will render to
- Configure a top-level class to safely store global data (i.e. version number)
###### Patches:
- N/A


