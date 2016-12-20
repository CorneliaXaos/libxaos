# libxaos
A Game Engine built as part of the EAE Engineers track at the University of Utah.
(Obviously flavored by personal preference. :P )

## Notes on Stability and Development
This engine is being designed as part of the Entertainment Arts and Engineering "Engineer" track coursework.  As such, its in a constant state of flux and shouldn't be relied on to be "stable".  :P  That being said, it will have "pseudo-releases" that will likely match up with the ends of semesters.

## Objectives
There are namely two objectives in this engine:  performance and desktop portability.  As such, for code to be merged into master it must compile on Linux, Windows, and OSX.  (OSX testing is currently pending and so I shall be a little lax about that, for the moment.  Also.. this restriction is kinda just to reinforce myself as I'm unlikely to merge anything in while I'm still working on this as part of class. :P )

## Modules
libxaos is divided into many modules and is / shall be designed to be extended by other modules.  That being said, there are (currently) four "base" modules:

- libxaos-core   : Memory management, custom containers, etc.
- libxaos-game   : The "meat" of the game engine.  (i.e. GameEntity, etc.)
- libxaos-maths  : Linear Algebra and Physics
- libxaos-render : A crossplatform rendering wrapper.

Each module shall be explained within a README within the appropriate project directory.  Additionally, there is a "pseudo-module" named 'libxaos-tests' which performs unittesting for the four base modules.

## Future Considerations
Each module is currently configured to compile as static libraries.  Pending the creation of another module which wraps shared library loading for all platforms in a convenient manner, the modules can be reconfigured to compile as shared objects.  This can allow for ease of swapping release variants.. if this little project ever gets that far. :P

## Folder Hierarchy
The headers and source files within each project are organized in a manner to allow for easy includes.  There are two primary directories: 'interface' and 'implementation'.  The 'interface' directory should only contain PUBLIC API.  If it's in there, expect users to touch it.  The 'implementation' directory contains implementation, obviously, as well as any private headers.

## Coding Style
The project doesn't really follow any public coding styles, but using common sense and follow good practices (such as Forward Declaration) should be obvious.  Specific formatting is..  based on my own preferences.  As such it is likely that any code merged into the project will be re-formated.  (Sorry. :P )

## FAQ
- Can I help?
    - Sure.. but your modifications, as mentioned above, might not be merged in until the Summer of 2018 when my program culminates. :P
- STL?
    - STL.
