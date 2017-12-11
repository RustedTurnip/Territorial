# Compiling Territorial using Visual Studio

### Download SFML
You can download the SFML library from [here](http://www.sfml-dev.org/download.php).
Once you have navigated to the page linked above, you will need to:
- Select the link labelled "Latest stable verison"
- Download the __Visual C++ 14 (2015) - 32-bit__ library
- Save it locally on the computer you wish to compile the game on

### Open source code as Visual Studio Project 
For ease of linking SFML (to allow you to compile the game), I recommend you create a __Visual Studio Console Application__ project, and paste the source code within this projects directories.

### Link SFML to the Visual Studio Compiler
The next step is to link the SFML library that you now have downloaded to the project to allow compilation.

- Navigate to __Project > *Project* Properties

This will display a window to allow you to configure the project.

- Navigate to __C/C++__ located within the treeview on the left hand side of the configuration window
- Paste the location of the __include__ directory contained within the downloaded SFML library into the *Additional Include Directories* entry (i.e. `C:/SFML/include`)
- Now navigate to __Linker__ also located in the treeview (like __C/C++__)
- Paste the location of the __lib__ directory contained within the downloaded SFML library into the *Additional Library Directories* entry (i.e. `C:/SFML/lib`)
- Lastly, you need to navigate to __input__ located within __Linker__ in the treeview
- Now you need to paste the following text - `sfml-audio-s.lib; sfml-network-s.lib; sfml-graphics-d.lib; sfml-window-d.lib; sfml-system-d.lib;` __*at the beginning of the text*__ contained within the *Additional Dependencies* entry

### Important
Now you have linked the SFML library to the Visual Studio project you will need to attempt to run the code (using the *Local Windows Debugger*), however __compilation will fail__ when you do this.

To resolve this issue, 
- Copy the contents of the bin folder included within the SFML library (i.e. `SFML/bin/`)
- And paste into the Visual Studio project directories `Debug` folder - i.e. Assuming the project's name is Territorial
    - `Territorial/Debug`
    - __NOT__  `Territorial/Territorial/Debug`