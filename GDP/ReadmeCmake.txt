Get the latest stable version of CMake. Version 3.5.1 works for me.7

FIRST!!!
New environment variable for QT
QT_DEV_PATH = C:\Qt\5.6
This should contain a folder like msvc2015_64. Cmake depends on this to find all the correct include and library paths.
Qt has first-class support for CMake as thats what QtCreator is using behind the scenes, this is absolutely the best way to use Qt.

BEWARE CMAKE SYNTAX IS HORRIFIC, MESSAGES ARE THE ONLY DEBUG TOOL, ITS AMAZING WITH SUCH A BAD LANGUAGE THEY BECAME SO POPULAR....

Next!!!
Open cmake-gui

I'll refer to the root gdp folder (where top-level CMakeLists.txt lives) as {GDPROOT} from now on

Source code folder: {GDPROOT}
Binaries: {GDPROOT}/BuildCMake << this can be whatever you want (DON'T  call it Build). Do not add this to version control!!

Hit Configure, choose your compiler (MSVC 14 x64)
Hit Generate

There will now be an sln in the Binaries folder. Whip it open, hit build, hoepfully everything should be fine, and the binaries will be placed in {GDPROOT}/Build/Windows/{Debug\Release}

~~~~~~~~~~~~~~~~~~~~~~~~
Few points for a better quality of life!

	- The solution should be treated as transient, you shoud be able to delete the BuildCmake folder whenever you want without crying (except for debugger settings, granted its a pain if you depend on these), don't go adding compiler defs/linker flags etc.. in the solution. Update the cmake scripts and re-generate.

		- Cmake has no way of informing the visual studio solution generator it should use a certain path for the debug working directory :(, defaults to the mad folder structure cmake generates, once you set it it is saved in a user prefs file so cmake doesn't trash this. i.e. once its set its set forever (applies to all debugger settings i.e command line args).

	- Be careful when adding a file using visual studio, the default folder it points at is the buildCmake location of the vcxproj. Once changed it remembers it for the session.

	- Qt has a quirk for its magic auto-genned files when used in tandem with CMake. When you add a new header/cpp combo that uses the Q_OBJECT macro you need to regen the solution with cmake. This is so it knows to run MOC on it for the auto-generated moc_ files (otherwise you'll end up with moc_dirkadirka.cpp not found)

	- The Cmake scripts are setup to recursively search the folders where the code is expected to live for each project, so you need not worry about updating any scripts to add new files (apparently this is not great cmake practise, but in my work experience I am yet to find a problem with it...)

	- If you need to add more Qt library dependency look at cmake/macros.cmake for Setup_qt to modify. Then go to the cmakelists.txt for the project you want the dependency adding for and add it in the link settings. Self-ish explanator: WARNING: online documentation of half of this is terrible at best.

	- When in doubt delete the cmake cache through the gui.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LOTS OF WORDS FOR SOMETHING THATS MEANT TO BE SIMPLE :) trust me it is a great workflow!
