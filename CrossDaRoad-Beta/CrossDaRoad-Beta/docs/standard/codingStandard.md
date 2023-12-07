# Project Code Standards

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Basic Code Standards](#basic-code-standards)
  - [Coding Style](#coding-style)
  - [Naming Conventions](#naming-conventions)
    - [File Name](#file-name)
    - [Variable Name](#variable-name)
    - [Constant Name](#constant-name)
    - [Scope Name](#scope-name)
    - [Function Name](#function-name)
  - [Comment Style](#comment-style)
  
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
