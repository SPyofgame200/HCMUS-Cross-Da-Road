# Directory Structure

> Explain the organization of project directories and their purposes

## Table of Contents

- [Directory Structure](#directory-structure)
  - [Table of Contents](#table-of-contents)
  - [Project Structure](#project-structure)
  - [src Structure](#src-structure)
    - [Object Class Files (`cFileName.cpp`)](#object-class-files-cfilenamecpp)
    - [Handler Class Files (`hFileName.cpp`)](#handler-class-files-gfilenamecpp)
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

### Handler Class Files (`hFileName.cpp`)

- These files should contain handler classes for object classes, do not use them as objects.
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

## Editor

- **Indentation:** `4 spaces`

- **Character Limit: `120`** - Allows a broad view of expressive code.

> **FAQ:** Why use such a high limit?
>
> - Facilitates readable variables, fostering expressiveness.
> - Averts deeply nested structures with longer lines.
> - Minimizes vertical scrolling, enhancing code visibility.

> **FAQ:** Why not use an unlimited character limit?
>
> - Restricts to 120 to avoid eye strain from smaller text or excessively wide code.

- **Variable Naming Max Limit: `18`** - Enhances readability with contextual variables.

> **FAQ:** Why use such a high limit?
>
> - Enables variables to provide meaningful context.
> - Reduces abbreviations and misuse of variables.
> - Allows functions or code structures to be self-explanatory.

> **FAQ:** Why not use a higher limit?
>
> - Eases code review and collaboration by reducing time spent on variable names.
> - While readability is desirable, it shouldn't be overly verbose to improve conciseness.
> - Typing might be an issue as longer names increase development cost.

- **Function Max Line Limit:**
  - Simple functions: `3 lines`
  - Calculation functions: `8 lines`
  - Core module functions: `13 lines`

> **FAQ:** Why use such a small limit?
>
> - Promotes modularity and single responsibility.
> - Shorter lines of code enhance readability.

> **FAQ:** Why to have different line limits?
>
> - Avoids overly fragmented code by not using functions that are too small.
> - Prevents an increase in maintenance costs from numerous functions with simple lines.
