# Project Structure

- **/docs**: Includes project documentation.
- **/data/assets**: Stores project assets.
- **/data/icons**: Store game icons.
- **/data/maps**: Store game maps.
- **/data/music**: Store game music.
- **/data/save**: Store game save files.
- **/src**: Contains source code for the game.

## Project source codes

### Header Files

- Each `.cpp` file should have its corresponding `.h` header file, except for `main.cpp`.

#### Object Class Files (`cFileName.cpp`)

- These files should contain object classes.
- Avoid using the global namespace in these files unless it's for debugging purposes.

#### Handler Class Files (`hFileName.cpp`)

- These files should contain handler classes for object classes, do not use them as objects.
- Avoid using the global namespace in these files unless it's for debugging purposes.

#### Core Game Class Files (`gFileName.cpp`)

- These files should contain core game classes.
- Use namespaces when defining classes in these files.

#### Utilities Function Files (`uFileName.cpp`)

- These files should contain utility functions, and constants, not classes.
- Use namespaces when defining functions in these files.
