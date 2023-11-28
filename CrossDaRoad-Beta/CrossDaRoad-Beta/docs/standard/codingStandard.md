# Project Code Standards

## Table of Contents

- [Project Code Standards](#project-code-standards)
  - [Table of Contents](#table-of-contents)
  - [Why Code Standards?](#why-code-standards)
  - [Basic Code Standards](#basic-code-standards)
    - [Coding Style](#coding-style)
    - [Naming Conventions](#naming-conventions)
      - [File Name](#file-name)
        - [Object Class Files (cFileName.cpp)](#object-class-files-cfilenamecpp)
        - [Core Game Class Files (gFileName.cpp)](#core-game-class-files-gfilenamecpp)
        - [Utilities Function Files (uFileName.cpp)](#utilities-function-files-ufilenamecpp)
      - [Variable Name](#variable-name)
      - [Constant Name](#constant-name)
      - [Scope Name](#scope-name)
      - [Function Name](#function-name)
    - [Comment Style](#comment-style)
  
## Why Code Standards?

Code standards are important for the following reasons:

- **Readability**: Code standards make code easier to read and understand.
- **Maintainability**: Code standards make code easier to maintain.
- **Consistency**: Code standards make code more consistent.
- **Collaboration**: Code standards make collaboration easier.
- **Learning**: Code standards make learning easier.
- **Efficiency**: Code standards make coding more efficient.
- **Quality**: Code standards make code higher quality.
- **Professionalism**: Code standards make code more professional.
- **Pride**: Code standards make code something to be proud of.

## Basic Code Standards

### Coding Style

- **Indentation**: Use 4 spaces for indentation.
- **Braces**:
  - Use the [Allman style](https://en.wikipedia.org/wiki/Indentation_style#Allman_style) for scope braces such as: `class`, `struct`, `namespace`, `enum`, etc. For example:

    ```cpp
    namespace example_name_space
    {
        class ExampleClass
        {
        public:
            ExampleClass();
            ~ExampleClass();
            void exampleFunction();
        private:
            int exampleVariable;
        }; // class ExampleClass

        struct ExampleStruct
        {
            int exampleVariable;
        }; // struct ExampleStruct

        enum ExampleEnum
        {
            EXAMPLE_ENUM_VALUE_1,
            EXAMPLE_ENUM_VALUE_2,
            EXAMPLE_ENUM_VALUE_3
        }; // enum ExampleEnum
    } // namespace example_name_space
    ```

    - Use the [K&R style](https://en.wikipedia.org/wiki/Indentation_style#K&R_style) for all other braces. For example:

    ```cpp
    void exampleFunction()
    {   
        // If-else statements
        if (exampleVariable == 0) {
            exampleVariable = 1;
        } else {
            exampleVariable = 0;
        }
        // For loops
        for (int i = 0; i < 10; ++i) {
            exampleVariable += i;
        }
        // While loops
        while (exampleVariable < 10) {
            exampleVariable++;
        }
        // Switch statements
        switch (exampleVariable) {
            case 0:
                exampleVariable = 1;
                break;
            case 1:
                exampleVariable = 0;
                break;
            default:
                exampleVariable = 0;
                break;
        }
    }
    ```

- **Line Length**: Use a maximum line length of 80 characters.

### Naming Conventions

#### File Name

##### Object Class Files (cFileName.cpp)

- Object class names should follow lower camel case naming conventions with the prefix "c."
- For example: `cMyClass`

##### Core Game Class Files (gFileName.cpp)

- Core game class names should follow Pascal case naming conventions for convenience.
- For example: `gGameEngine`

##### Utilities Function Files (uFileName.cpp)

- These files should contain only functions, not classes.
- For example: `uStringUtils`

#### Variable Name

- Variable names should follow the lower camel case naming convention.
- Use prefixes to denote the variable type:
  - `b-*` for boolean variables.
  - `n-*` for signed integer variables.
  - `u-*` for unsigned integer variables.
  - `f-*` for float variables.
  - `s-*` for string variables.
  - `e-*` for enum variables.
  - `p-*` for variables of type `Pixel`.
  - `ptr-*` for variables of pointet type `type*`.
  - `vec-*` for variables of type `std::vector<>`.
  - `arr-*` for variables of type `std::array<>`.
  - `map-*` for variables of type `std::map<>`.
  - `set-*` for variables of type `std::set<>`.
- Use suffixes to denote the variable properties:
  - `*-s` for array or any container (plural countable noun)

#### Constant Name

- Constant names should follow the upper snake case naming convention.
- Example: `const int MY_CONSTANT = 0;`

#### Scope Name

- `namespace` names should follow lower snake case naming conventions. Example: `app_const`
- `class` names should follow Pascal case naming conventions with the prefix "c." Example: `cMyClass`
- `struct` names should follow Pascal case naming conventions with the prefix "s." Example: `sMyStruct`
- `enum` names should follow Pascal case naming conventions with the prefix "e." Example: `eMyEnum`

#### Function Name

- Function names should follow Pascal case naming conventions.
- Use prefixes to denote the function's purpose:
- Functions that retrieve properties (e.g., "size()" and "length()") should be named using nouns.
  - Functions that return boolean values should have prefixes like "OnFunction()" or "IsFunction()" or use adjectives.
  - Other function names should have prefixes like "GetFunction()" or "SetFunction()" or use verbs.
- Example:

    ```cpp
    
    class ExampleClass 
    {
    public:
        /// @brief Get the size of the object.
        /// @return The size of the object.
        int GetSize() const 
        {
            return size;
        }

        /// @brief Check if the object is active.
        /// @return True if the object is active, false otherwise.
        bool IsActive() const {
            return active;
        }

        /// @brief Set the name of the object.
        /// @param newName The new name of the object.
        void setName(const std::string& newName) {
            name = newName;
        }

    private:
        int size; ///< Size of the object
        bool active; ///< Whether the object is active
        std::string name; ///< Name of the object
    };

    ```

### Comment Style

Use Doxygen style comments for all comments.

- Use `//` for inline comments. For example:

  ```cpp
  double division(int a, int b) {
      if (b == 0) { // Cannot divide an integer by zero
          cerr << "Division by zero";
          exit(-1);
      }
      return static_cast<double>(a) / b;
  }
  ```

- Use `///` for function comments. For example:

    ```cpp
    /// @brief Right-pad a string with a character to a certain length
    /// @param input String to be padded
    /// @param paddingChar Character to be padded
    /// @param length Length of the padded string
    /// @return Padding string
    /// @example rpad("spyofgame", '*', 5)
    ///          returns "spyofgame*****"
    std::string rpad(const std::string& input, const char paddingChar, const size_t length)
    {
        if (input.length() >= length)
        return input;
        return input + std::string(length - input.length(), paddingChar);
    }
    ```

- Use `/** **/` for file comments. For example:

    ```cpp
    /**
     * @file example_file.cpp
     * @brief Example file
     * 
     * This is an example file.
    **/
    ```

- Use `///<` for variable in scope comments or enum value comments. For example:

    ```cpp
    class ViewportState
    {
    private:
        int32_t nWidth;  ///< Viewport width in pixels
        int32_t nHeight; ///< Viewport height in pixels
        int32_t nPosX;   ///< Viewport X position in pixels
        int32_t nPosY;   ///< Viewport Y position in pixels
    };

    /// @brief Enumeration of codes in the game engine (for error handling)
    enum Code
    {
        // Successful codes
        SUCCESS = 0,         ///< The program executed successfully without errors
        SUCCESS_WARNING = 1, ///< The program succeeded, but ignore non-fatal warnings
        SUCCESS_DANGER = 2,  ///< The program is partially succeeded, with fatal warnings and potential bugs
        SUCCESS_RISK = 3,    ///< The program is partially succeeded, produce minor or even major issues

        // General error codes
        FAILURE = -1,         ///< Generic failure code, indicating an unspecified error
        ACCESS_DENIED = -2,   ///< The user doesn't have permission for the requested operation
        INCOMPATIBILITY = -3, ///< Default settings are incompatible with custom settings
    };
    ```

- Use `///...///` for comment blocks. For example:

    ```cpp
    ...
    //////////////////////////////////////////////////////////////
    /////////////            SETTERS                 /////////////
    //////////////////////////////////////////////////////////////
    ...
    //////////////////////////////////////////////////////////////
    /////////////            GETTERS                 /////////////
    //////////////////////////////////////////////////////////////
    ...
    ```
