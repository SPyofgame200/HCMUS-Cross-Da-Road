# Directory Structure

> Explain the organization of project directories and their purposes

## Table of Contents

- [Directory Structure](#directory-structure)
  - [Table of Contents](#table-of-contents)
  - [Project Structure](#project-structure)
  - [src Structure](#src-structure)
    - [Object Class Files (`cFileName.cpp`)](#object-class-files-cfilenamecpp)
    - [Core Game Class Files (`gFileName.cpp`)](#core-game-class-files-gfilenamecpp)
    - [Utilities Function Files (`uFileName.cpp`)](#utilities-function-files-ufilenamecpp)
    - [Header Files](#header-files)
  - [data/maps Structure](#datamaps-structure)
  
## Project Structure

- **/docs**: Includes project documentation.
- **/data/assets**: Stores project assets.
- **/data/icons**: Store game icons.
- **/data/maps**: Store game maps.
- **/data/music**: Store game music.
- **/data/save**: Store game save files.
- **/src**: Contains source code for the game.
  
## src Structure

### Object Class Files (`cFileName.cpp`)

- These files should contain object classes.
- Avoid using the global namespace in these files unless it's for debugging purposes.

### Core Game Class Files (`gFileName.cpp`)

- These files should contain core game classes.
- Use namespaces when defining classes in these files.

### Utilities Function Files (`uFileName.cpp`)

- These files should contain utility functions, and constants, not classes.
- Use namespaces when defining functions in these files.

### Header Files

- Each `.cpp` file should have its corresponding `.h` header file, except for `main.cpp`.

## data/maps Structure

Refer to [Map Standard](mapStandard.md) for more information.
