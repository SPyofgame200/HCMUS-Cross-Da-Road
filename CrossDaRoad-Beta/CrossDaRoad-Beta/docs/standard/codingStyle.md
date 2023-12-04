# Coding Style

---
---
---
---
---

## ∅. The need of coding style

Coding style is essentially a set of guidelines and conventions that dictate how code should be written and formatted within a project or organization. While it may seem like a matter of personal preference, having a consistent coding style is crucial for several reasons, as indicated in the provided context:

- Readability and Maintainability
- Collaboration and Code Reviews
- Enforce Best Practices and Avoid Common Bugs
- Tool Integration and Editor Extension
- Code Quality and Professionalism

In this coding style, we provide to you common fields that require styling and formatting:

- A. [Style Preferences](#a-style-preferences)
- B. [Naming Rule](#b-naming-rule)
- C. [Comment Style](#c-comment-style)
- D. [Identation Style](#d-identation-style)
- E. [Variable Formatting](#e-variable-formatting)
- F. [Function Formatting](#f-function-formatting)

For more question you might ask, see this [Frequently Asked Questions](#z-frequently-asked-questions)

### Table Of Contents

A. [Style Preferences](#a-style-preferences)

- A.1. [Editor Character: `ASCII Only`](#a1-editor-character-ascii-only)
- A.2. [Line Length: `120 characters per line`](#a2-line-length-120-characters-per-line)
- A.3. [Maximum Nested Scope: `3 nested per function`](#a3-maximum-nested-scope-3-nested-per-function)
- A.4. [Use of Preprocessor Macros: `Limited`](#a4-the-use-of-preprocessor-macros-limited)
  - A.4.1. [Templated Class Instantiation](#a4-1-templated-class-instantiation)
  - A.4.2. [Message Logging Generator](#a4-2-message-logging-generator)
  - A.4.3. [File Guard](#a4-3-file-guard)

B. [Naming Rule](#b-naming-rule)

- B.1. [File Name: `Mixed Cases`](#b1-file-name-mixed-cases)
- B.2. [Class Name: `prefixedLowerCamelCase`](#b2-class-name-prefixedlowercamelcase)
- B.3. [Struct Name: `PascalCase`](#b3-struct-name-pascalcase)
- B.4. [Enumerator Name: `PascalCase`](#b4-enumerator-name-pascalcase)
- B.5. [Type Name: `lower_snake_case_with_suffix`](#b5-type-name-lower_snake_case_with_suffix)
- B.6. [Scope Name](#b6-scope-name)
- B.7. [Variable Name](#b7-variable-name)
- B.8. [Macro Name](#b8-macro-name)
- B.9. [Function Name](#b9-function-name)

C. [Comment Style](#c-comment-style)

- C.1. [Inline Comment: `// simple comment`](#c1-inline-comment-simple-comment)
- C.2. [Function Comment: `/// @doxygen comments`](#c2-function-comment-doxygen-comments)
- C.3. [File Comment: `/** @doxygen multiple line comments **/`](#c-3-file-comment-doxygen-multiple-line-comments-)
- C.4. [Property Comment `///< simple comment`](#c4-property-comment-simple-comment)
- C.5. [Block Comment: `/// COMMENT ///`](#c5-block-comment-comment-)
- C.6. [Scope Comment: `/* Scope */`](#c-6-scope-comment-scope-)

D. [Identation Style](#d-identation-style)

- D.1. [Indentation Gap: `4 spaces per indent`](#d1-indentation-gap-4-spaces-per-indent)
- D.2. [Brackets Style: `One True Brace Style`](#d2-brackets-style-one-true-brace-style)
- D.3. [Brackets Spacing: `Omit Redundant Spaces Only`](#d3-brackets-spacing-omit-redundant-spaces-only)
- D.4. [Space Padding: `Control Flow Padding Only`](#d4-space-padding-control-flow-padding-only)

E. [Variable Formatting](#e-variable-formatting)

- E.1. [Variable Declaration: `Omit Redundant Spaces`](#e1-variable-declaration--omit-redundant-spaces)
  - E.1.1. [Good Cases](#e1-1-good-cases)
  - E.1.2. [Bad Cases](#e1-2-bad-cases)
- E.2. [Variable Initialization: `Always Init`](#e2-variable-initialization-always-init)
  - E.2.1. [Preferable Cases](#e2-1-preferable-cases)
  - E.2.2. [Acceptable Cases](#e2-2-acceptable-cases)
  - E.2.3. [Bad Cases](#e2-3-bad-cases)
  - E.2.4. [Internal Property Initialization](#e2-4-internal-property-initialization)
- E.3. [Floating Point Format: `Literal value`](#e3-floating-point-format-literal-value)
- E.4. [Boolean Expression Format: `First Variable Wrapping With Prefix`](#e4-boolean-expression-format-first-variable-wrapping-with-prefix)

F. [Function Formatting](#f-function-formatting)

- F.1. [Function Default Value: `Declaration only`](#f1-function-default-value-declaration-only)
- F.2. [Function Tag: `Before Function Name`](#f2-function-tag-before-function-name)
- F.3. [Function Definition: `No omomission`](#f3-function-definition-no-omomission)
- F.4. [Function Declaration: `Single Indent Wrapping`](#f4-function-declaration-single-indent-wrapping)
- F.5. [Function Call: `First Param Wrapping`](#f5-function-call-first-param-wrapping)
- F.6. [Function Return: `First Condition Wrapping With Prefix`](#f6-function-return-first-condition-wrapping-with-prefix)
- F.7. [Lambda Expressions](#f8-lambda-expressions)
- F.8. [Function Max Line Limit `21 lines`](#f8-function-max-line-limit-21-lines)

Z. [Frequently Asked Questions](#z-frequently-asked-questions)

- Z.1. [FAQ#1: Why dont we use tabs identation instead of spaces ?](#faq1-why-dont-we-use-tabs-identation-instead-of-spaces-)
- Z.2. [FAQ#2: Why do we use identation of 2 spaces or 8 spaces ?](#faq2-why-do-we-use-identation-of-2-spaces-or-8-spaces-)
- Z.3. [FAQ#3: Why do we use limited code limit ?](#faq3-why-do-we-use-limited-code-limit-)
- Z.4. [FAQ#4: What if a code exceeds the nested limit ?](#faq4-what-if-a-code-exceeds-the-nested-limit-)
- Z.5. [FAQ#5: Why use such a high character limit?](#faq5-why-use-such-a-high-character-limit)
- Z.6. [FAQ#6: Why not use unlimited character limit?](#faq6-why-not-use-unlimited-character-limit)
- Z.7. [FAQ#7: Why use such a high nested limit?](#faq7-why-use-such-a-high-nested-limit)
- Z.8. [FAQ#8: Why not use a higher nested limit?](#faq8-why-not-use-a-higher-nested-limit)
- Z.9. [FAQ#9: Why use such a small line limit?](#faq9-why-use-such-a-small-line-limit)
- Z.10. [FAQ#10: Why to have different line limits?](#faq10-why-to-have-different-line-limits)

---
---
---
---
---

## A. Style Preferences

---

### A.1 - Editor Character: `ASCII Only`

> Do not use Unicode, considering using `wstring, wchar_t, L".."` with UTF-8 Formatting instead.

---

### A.2 - Line Length: `120 characters per line`

> Allows a broad view of expressive code.

---

### A.3 - Maximum nested scope: `3 nested per function`

> To maintain code clarity, a maximum of 3 nested scopes per function is recommended.

```cpp
std::string Foo(int nFirstNested, int nSecondNested, int nThirdNested)
{
    if (nFirstNested == 1) {
        if (nSecondNested == 2) {
            if (nThirdNested == 3) {
                return "3 nested";
            }
            else {
                return "3 nested";
            }
            return "2 nested";
        }
        return "1 nested";
    }
    return "0 nested";
}
```

---

### A.4 - The use of preprocessor macros: `Limited`

> Avoiding macro at all cost, unless necessary. Do not use macro to replace functions or constants. Do not use macro inside header file (unless you remember to `#undef` them). Do not `#undef` existing macro in another header file. All macros must have brackets for all parameters, and an outermost brackets for avoiding typo.
>
> These are the only exceptions where you could use macro:
>
> - Templated class instantiations: Must be used in templated classes.
> - Message Logging Generators: Should be used in most of the source files.
> - File Guard: Must be used in all header files.

#### A.4-1) Templated Class Instantiation

```cpp
#define DECLARE_MY_TEMPLATE_INSTANTIATION(T) \
    template class MyClass<T>;

DECLARE_MY_TEMPLATE_INSTANTIATION(int);
DECLARE_MY_TEMPLATE_INSTANTIATION(double);

#undef DECLARE_MY_TEMPLATE_INSTANTIATION // note: dont forgot to #undef
```

#### A.4-2) Message Logging Generator

```cpp
#ifdef ENABLE_LOGGING
#define LOG_MESSAGE(message) \
    do { \
        logFunction(__FILE__, __LINE__, __func__, message) \
    } while (0)
#else
#define LOG_MESSAGE(message) \
    do { ... } while(0)
#endif
```

#### A.4-3) File Guard

```cpp
#ifndef FOO_H
#define FOO_H
#pragma once // you can use #pragma once with file guard in rare cases

class Foo
{
    Foo();
};

#endif // FOO_H
```

---
---
---
---
---

## B. Naming Rule

---

### B.1 - File Name: `Mixed Cases`

> Source Filenames should be `lowerCamelCase` with single prefixed character indicating their functionality. If there is no consistent local pattern to follow, prefer "_".
> Prefixes of functionalities:
>
> - `./src/cFileName.*`: Class Objects, contains the application functionalities.
> - `./src/hFileName.*`: Class Handlers, contains the class handler.
> - `./src/gFileName.*`: Core Classs, contains main frameworks of the application.
> - `./src/uFileName.*`: Utilities, contains only helper functions or namespaces.

> Documentation Filenames, should be either `lowerCamelCase` or `lower_snake_case`.
>
> - `./docs/report/*`: Project Reports, lower snake case.
> - `./docs/standard/fileName.md`: Project Standards, lower camel case.
> - `./docs/documentation/fileName.md`: Project Documentations, unused just for now.

> Data Filenames should be lower snake case, might have unsigned integer suffix as animation ID
>
> - `./data/assets/*.png`: Asset Files, including: characters, entities, backgrounds, frontground, underlay, projectiles, ...
> - `./data/icons/*<id>.png`: Branding Files, including: icon, favicon, logo, avatars, banners, splash screen, thumbnails, infographics, ...
> - `./data/maps/map*.txt`: Map Files, contains the map data of each level.
> - `./data/report/log*.txt`: Log Files, for debugging purposes.
> - `./data/musics/ncs*.wav`: Sound Files, we use ncs to avoid copyright.
> - `./data/save/*.txt`: Saved Data Files, for loading and saving player data.

---

### B.2 Class Name: `prefixedLowerCamelCase`

> Due to the complexity of the projects, only Class (not Enum Class) need its prefixed character indicating its functionality:
>
> - `o-*` Object Class - contain functionalities as an object.
> - `c-*` Component Class - contain data and manage it with getters, setters, ...
> - `h-*` Handler Component - static class contain only dependencies pointers.
>
> Notice that struct is only used as a passive object that only carry data. See below

```cpp
struct Struct { ... }
enum Enum { ... }
enum class EnumClass { ...}
Struct sStruct;
Enum eEnum;
EnumClass eEnumClass;
```

---

### B.3 Struct Name: `PascalCase`

> Struct should only be used as a passive object that only carry data. If there are more functions or itself become complex, consider using class instead.

```cpp
class oEntityObject {
    cEntityComponent cComponent;
    static hEntityHandler hHandler;
}
oEntityObject oEntitys[100]; // note suffix s indicating array
```

---

### B.4 Enumerator Name: `PascalCase`

> Enum, Enum Class

```cpp
/// Good Example

// Enumerator in PascalCase
enum Color {
    Red,
    Green,
    Blue
};

/// Bad Example

// Enumerator in camelCase
enum color {
    Red,
    Green,
    Blue
};

// Enumerator in snake_case
enum color_table {
    Red,
    Green,
    Blue
};
```

---

### B.5 Type Name: `lower_snake_case_with_suffix`

```cpp
using data_t = int;
```

---

### B.6 Scope Name

- Compound Statements should have comments indicating their scope.
- Compound Statements and namespace should have `lower_snake_case` naming.

```cpp
/// Namespace Example
namespace app_const
{
    constexpr int APP_HEIGHT = 1200;
    constexpr int APP_WIDTH = 1800;
}

/// Compound Statements Example
void Foo()
{
    /* load_data */
    {
        FooLoad();
    }
    /* update_game */
    {
        FooUpdate();
    }
    /* render_game */
    {
        FooRender();
    }
}

```

---

### B.7 - Variable Name

> - Non-constant variable names should follow the lower camel case naming convention.
> - Use prefixes to denote the variable type:
>   - `b-*` for boolean variables.
>   - `n-*` for signed integer variables.
>   - `u-*` for unsigned integer variables.
>   - `f-*` for float variables.
>   - `s-*` for string variables.
>   - `e-*` for enum variables.
>   - `c-*` for class and struct variables.
>   - `o-*` for object variables.
>   - `c-*` for component variables.
>   - `h-*` for handler variables.
>   - `t-*` for variables of type `template<>`.
>   - `p-*` for variables of type `std::unique_pointer<>` or `std::shared_pointer<>`.
>   - `ptr-*` for variables of type `type*`.
>   - `vec-*` for variables of type `std::vector<>` or `std::array<>`
>   - `map-*` for variables of type `std::map<>` or `std::unordered_map<>`.
>   - `set-*` for variables of type `std::set<>` or `std::unordered_set<>`.
>   - `stack-*` for variables of type `std::stack<>`.
>   - `queue-*` for variables of type `std::queue<>`.
>   - `deque-*` for variables of type `std::deque<>`.
> - Use suffixes to denote the variable properties:
>   - `*-s` for array or any container (plural countable noun)
>   - `*-<index>` for indexed variables (ex: animation frames).
> - Constant names should follow the `UPPER_SNAKE_CASE` naming convention.
> - Compiled Time Constants and Static Variables must be inside a namespace or classes.

> Choose descriptive names for objects that clearly convey their purpose or intent. Prioritize clarity over saving horizontal space.
> Avoid excessive use of abbreviations, especially those unfamiliar to readers outside the project. Refrain from deleting letters within words when abbreviating. Use abbreviations listed in Wikipedia when appropriate.
> Tailor the descriptiveness of a name to its scope of visibility; for instance, use more specific names in broader scopes like classes. Avoid overly vague names like 'n,' especially in larger contexts.
> Exception are: iteration (`i`, `id`, `idx`), template type (`T`, `type`)

```cpp
// Use prefixes to denote the variable type:
bool bIsActive;
int nItemCount;
unsigned int uIndex;
float fTemperature;
std::string sName;
enum Color { Red, Green, Blue };
Color eCurrentColor;
Pixel pCurrentPixel;
int* ptrData;
std::vector<int> vecNumbers;
std::array<char, 5> vecChars;
std::map<std::string, int> mapScores;
std::set<int> setValues;

// Use suffixes to denote the variable properties:
std::vector<int> numbersArr; // 'Arr' suffix indicates it's an array or container

// Constant names should follow the upper snake case naming convention.
const int MAX_LIMIT = 100;

// Static Variables inside a class.
class ExampleClass {
public:
    static constexpr double PI_VALUE = 3.141592653589793;
    static int sInstanceCount;
};
int ExampleClass::sInstanceCount = 0;

// Static Variables inside a namespace.
namespace configuration 
{
    static const int TIMEOUT_DURATION = 5000;
    static int sGlobalCounter = 0;
}
// Compiled Time Constants inside a namespace.
namespace app_const
{
    constexpr int APP_HEIGHT = 1200;
    constexpr int APP_WIDTH = 1800;
}

/// Good Example
class MyClass {
public:
    int CountFooErrors(const std::vector<Foo>& foos) {
        int n = 0;  // Clear meaning given limited scope and context
        for (const auto& foo : foos) {
           ...
           ++n;
        }
        return n;
    }
    void DoSomethingImportant() {
        std::string fqdn = ...;  // Well-known abbreviation for Fully Qualified Domain Name
    }
private:
    const int kMaxAllowedConnections = ...;  // Clear meaning within context
};

/// Bad Example
class MyClass {
public:
    int CountFooErrors(const std::vector<Foo>& foos) {
        int total_number_of_foo_errors = 0;  // Overly verbose given limited scope and context
        for (int foo_index = 0; foo_index < foos.size(); ++foo_index) {  // Use idiomatic `i`
            ...
            ++total_number_of_foo_errors;
        }
        return total_number_of_foo_errors;
    }
    void DoSomethingImportant() {
        int cstmr_id = ...;  // Deletes internal letters
    }
private:
    const int kNum = ...;  // Unclear meaning within broad scope
};

```

---

### B.8 - Macro Name

> Macro must be named with `UPPER_SNAKE_CASE`
>
> The preprocessor directives (`#define`, `#undef`, `#ifdef`, `#ifndef`, `#elif`, `#endif`, ...) must be put in the beginning of the line.

```cpp
// Example of using a macro for include guard
#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

// Header file contents go here

#endif // MY_HEADER_FILE_H

// Example of using a macro for message logging
#ifdef ENABLE_LOGGING
#define LOG_MESSAGE(message) \
    logFunction(message)
#else
#define LOG_MESSAGE(message) \
    do { ... } while(0)
#endif

// Usage example
LOG_MESSAGE("This is a log message");

// Bad - indented directives
if (lopsided_score) {
    #if DISASTER_PENDING  // Wrong!  The "#if" should be at beginning of line
    DropEverything();
    #endif                // Wrong!  Do not indent "#endif"
    BackToNormal();
}
```

---

### B.9 - Function Name

- Function names should follow Pascal case naming conventions.
- For functions in classes, please read `./docs/classStandard.md`

```cpp
/// Good Examples

// Regular function
void CalculateTotalAmount() {
    // Function implementation
}

// Member function within a class
class ShoppingCart {
public:
    void AddItemToCart() {
        // Function implementation
    }

    double CalculateCartTotal() const {
        // Function implementation
        return 0.0;
    }
};

/// Bad Examples

// Regular function
void calculate_total_amount() {
    // Non-Pascal case naming
}

// Member function within a class
class ShoppingCart {
public:
    void add_item_to_cart() {
        // Non-Pascal case naming
    }

    double calculateCartTotal() const {
        // Camel case instead of Pascal case
        return 0.0;
    }
};
```

---
---
---
---
---

## C - Comment Style

> Use Doxygen style comments for all comments.

### C.1 - Inline Comment: `// simple comment`

```cpp
double division(int a, int b) {
    if (b == 0) { // Cannot divide an integer by zero
        cerr << "Division by zero";
        exit(-1);
    }
    return static_cast<double>(a) / b;
}
```

### C.2 - Function Comment: `/// @doxygen comments`

```cpp
/// @brief Right-pad a string with a character to a certain length
/// @param input String to be padded
/// @param paddingChar Character to be padded
/// @param length Length of the padded string
/// @return Padding string
/// @example rpad("spyofgame", '*', 5)
///       returns "spyofgame*****"
std::string rpad(const std::string& input, const char paddingChar, const size_t length)
{
    if (input.length() >= length)
    return input;
    return input + std::string(length - input.length(), paddingChar);
}
```

### C-3 - File Comment: `/** @doxygen multiple line comments **/`

```cpp
/**
    * @file example_file.cpp
    * @brief Example file
    * 
    * This is an example file.
**/
```

### C-4 - Property Comment `///< simple comment`

```cpp
class ViewportState
{
private:
    int32_t nWidth;  ///< Viewport width in pixels
    int32_t nHeight; ///< Viewport height in pixels
    int32_t nPosX;   ///< Viewport X position in pixels
    int32_t nPosY;   ///< Viewport Y position in pixels
};

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

### C.5 - Block Comment: `/// COMMENT ///`

```cpp
...
/////////////////////////////////////////////////////////////
////////////////////////// SETTERS //////////////////////////
/////////////////////////////////////////////////////////////
...
/////////////////////////////////////////////////////////////
////////////////////////// GETTERS //////////////////////////
/////////////////////////////////////////////////////////////
...
```

### C-6 - Scope Comment: `/* Scope */`

> Recommemded to use compound statements with commented scope instead of `if (true) {}`

```cpp
/// Compound Statements Example
void Foo()
{
    /* load_data */
    {
        FooLoad();
        BarLoad();
    }
    /* update_game */
    {
        FooUpdate();
        BarUpdate();
    }
    /* render_game */
    {
        FooRender();
        BarRender();
    }
}
```

---
---
---
---
---

## D. Identation Style

---

### D.1 - Indentation Gap: `4 spaces per indent`

> Do not use tabs, you should set your editor to emit spaces when you hit the tab key.

```cpp
std::string Foo(int nFirstIdent, int nSecondIdent, int nThirdIdent)
{
    if (nFirstIdent == 1) {
        if (nSecondIdent == 2) {
            if (nThirdIdent == 3) {
                return "16 spaces";
            }
            else {
                return "16 spaces";
            }
            return "12 spaces";
        }
        return "8 spaces";
    }
    return "4 spaces";
}
```

---

### D.2 - Brackets Style: `One True Brace Style`

> Opening brackets are broken from namespaces, classes, and function definitions. Brackets are attached to everything else including statements within a function, arrays, structs, and enums.

```cpp
/// Example Function
bool Foo(bool isBar)
{
    if (isBar) {
        Bar();
        return true;
    } else {
        return false;
    }
}

/// Example Conditional
if (condition) {                     // Good - no spaces inside parentheses, space before brace.
    DoOneThing();                    // Good - two-space indent.
    DoAnotherThing();
} else if (int a = f(); a != 3) {    // Good - closing brace on new line, else on same line.
    DoAThirdThing(a);
} else {
    DoNothing();
}

/// Example looping
while (condition) {
    RepeatAThing();
}
do {
    RepeatAThing();
} while (condition);
for (int i = 0; i < 10; ++i) {
    RepeatAThing();
}

/// Bad - `if ... else` statement does not have braces everywhere.
if (condition)
    foo;
else {
    bar;
}

/// Bad - `if` statement too long to omit braces.
if (condition)
    // Comment
    DoSomething();

/// Bad -`if` statement too long to omit braces.
if (condition1 &&
    condition2)
    DoSomething();

/// Bad - `if ... else` statement is missing braces.
if (x) DoThis();                   
else DoThat();

/// Bad - `do ... while` statement is missing braces.
do DoThis();                       
while (x);

while (condition);  // Bad - looks like part of `do-while` loop.

/// Example swtich case
switch (var) {
    case 0: { // Case with Braces
        Foo(); 
        type newVar = var;
        Bar(newVar);
        break;
    }
    case 1: Foo1();         // Case without Braces
    case 2: Foo2(Bar(var)); // Case without Braces
    default: {
        FooDefault();
    }
}

/// Example with pointers
x = *p;
p = &x;
x = r.y;
x = r->y;


/// Example with single line blocks (only if the blocks are simple enough)
if (condition) DoSomething();
for (int i = 0; i < 10; ++i) DoSomething(); 
while (x > 0) DoSomething();
```

---

### D.3 - Brackets Spacing: `Omit Redundant Spaces Only`

> Only redundant spaces needed to be removed. `First Param Swapping` isnt considered as redundatn spaces but rather code formatting.

```cpp
if(condition) {}                   // Bad - space missing after `if`.
else if ( condition ) {}           // Bad - space between the parentheses and the condition.
else if (condition){}              // Bad - space missing before `{`.
else if(condition){}               // Bad - multiple spaces missing.
for (int a = f();a == 10) {}       // Bad - space missing after the semicolon.
```

---

### D.4 - Space Padding: `Control Flow Padding Only`

> Insert space padding between a control flow (e.g. 'if', 'for', 'while'...) and the following paren.

```cpp
if (condition) {                    // Good - space after 'if'
    DoSomething();
}

for (int i = 0; i < 10; ++i) {       // Good - space after 'for'
    DoSomething();
}

while (x > 0) {                      // Good - space after 'while'
    DoSomething();
}

do {                                 // Good - space after 'do'
    DoSomething();
} while (condition);

switch (value) {                     // Good - space after 'switch'
    case 1: 
        DoSomething();
        break;
    default: 
        DoDefault();
}

/// Not recommended, unless the blocks are simple enough
if (condition) DoSomething();               // Good - no space padding needed in single-line blocks.
for (int i = 0; i < 10; ++i) DoSomething(); // Good - no space padding needed in single-line blocks.
while (x > 0) DoSomething();                // Good - no space padding needed in single-line blocks.

```

---
---
---
---
---

## E. Variable Formatting

---

### E.1 - Variable Declaration:  `Omit Redundant Spaces`

> Aiming to improve code consistency, readability, and maintainability we need to omit the redundant spaces as inconsistent spacing can lead to confusion and make the code harder to understand, especially when declare a pointer.

#### E.1-1) Good Cases

```cpp
// Good - Helpful for readability
int x, y;   

// Good - These are fine, space preceding.
char *c;
char *d, *e; // both are char* type
const std::string &str;
int *GetPointer();
std::vector<char *>

// Good - Consistent use of pointer notation
int *a, *b; // Both 'a' and 'b' are int pointers

// Good - Clear declaration of a reference and a pointer
float *f;
const auto& g = someFunction(); // Using 'auto' for clarity

// Good - Consistent pointer declaration and spacing
int *x, *y, *z; // All are int pointers

// Good - Clear use of pointers for all variables
char *p, *q, *r; // All are char pointers

// Good - Clearly differentiate between array of pointers and array of ints
int* arr1[5]; // Array of int pointers
int arr2[5];  // Array of ints

// Good - Clearly specify pointer in function parameters
void someFunction(int* a, int* b); // Both 'a' and 'b' are pointers

// Good - Use pointers consistently for strings
char* str1 = "Hello";
const char* str2 = "World"; // Use 'const' for string literals

// Good - Clearly declare a pointer and a reference
int* pInt;
const auto& refInt = someFunction(); // Using 'auto' for clarity
```

#### E.1-2) Bad Cases

```cpp
// Bad - Do not use C style declaration, as it can cause confusion
char* c;
char* d, e;  /// e is char type but not char*
const std::string& str;
int* GetPointer();
std::vector<char*>  // Note no space between '*' and '>'

// Bad - Confusing mix of pointer and non-pointer types
int* a, b; // 'a' is int*, but 'b' is just int, not int*

// Bad - Mixing pointer and reference in a declaration
float* f, &g = someFunction(); // 'f' is float*, but 'g' is a reference

// Bad - Inconsistent spacing and confusion between pointer and multiplication
int* x, y, z; // 'x' is int*, but 'y' and 'z' are just int, not int*

// Bad - Lack of clarity when combining multiple types
char *p, q, *r; // 'p' is char*, 'q' is char, 'r' is char*

// Bad - Confusing use of pointer with arrays
int* arr1[5], arr2[5]; // 'arr1' is an array of int pointers, 'arr2' is an array of ints

// Bad - Misleading use of pointers in function parameters
void someFunction(int* a, int b); // 'a' is a pointer, 'b' is not

// Bad - Ambiguous declaration with pointer and array
char* str1, str2[] = "Hello"; // 'str1' is a pointer, 'str2' is an array

// Bad - Ambiguity when mixing pointers and references
int* pInt, &refInt = someFunction(); // 'pInt' is a pointer, 'refInt' is a reference
 
// Bad - no & or * in multiple declaration
int x, *y;   

// Bad - no & or * in multiple declaration; inconsistent spacing
int* x, *y;  

// Bad - spaces on both sides of *
char * c;    
const std::string & str;  // Bad - spaces on both sides of &
```

---

### E.2 - Variable Initialization: `Always Init`

> Always init variables with default values, either in compile time or in runtime. Internal property initialization should have prefix `this->` for avoiding typo. Do not use initializer list unless needed.

#### E.2-1) Preferable Cases

```cpp
int x = 3;                         
std::string nameX = "Some Name";     
std::vector<int> v = {0, 0, 0};  // vector have 3 initial values are all zeros
int pi = static_cast<int>(3.14f);
```

#### E.2-2) Acceptable Cases

```cpp
int y(3);                          
std::string nameY("Some Name");     
std::vector<int> v(3, 0);        // vector have size of 3, default value is 0
int pi(3.14);                    // pi init as 3.
```

#### E.2-3) Bad Cases

```cpp
int z{3};                          
std::string nameZ{"Some Name"};  // {} cause confusing with () braces
std::vector<int> v{3, 0};        // vector have two variables 3 and 0
int pi{3.14};                    // Compile Error - narrowing conversion.
```

#### E.2-4) Internal Property Initialization

```
class Foo 
{
    int x;
    Foo(int x = 0); // parameter name is acceptable
};

/// Note: Using this->property in order to avoid typo.
Foo::Foo(int x)
{
    this->x = x;
}
```

---

### E.3 - Floating Point Format: `Literal value`

> Readability is improved if all floating-point literals take this familiar form, as this helps ensure that they are not mistaken for integer literals, and that the E/e of the exponential notation is not mistaken for a hexadecimal digit. It is fine to initialize a floating-point variable with an integer literal (assuming the variable type can exactly represent that integer), but note that a number in exponential notation is never an integer literal.
>
> By using literal for floating point, you will also avoid the unwanted typo and precision issues.

```cpp
/// Bad, do not use
float f1 = 1.f;
float f2 = 1; // acceptable but should indicate better
long double ld = -.5L;
double d = 1248e6;

/// Recomended
float f1 = 1.0f;
float f2 = 1f;
long double ld = -0.5L;
double d = 1248.0e6;
```

---

### E.4 - Boolean Expression Format: `First Variable Wrapping With Prefix`

> Wrap the boolean expression on the first variable, logical operators (`||`, `&&`, ...) shall be as prefixes of the following expressions. It is recommended to use a variable to capture the result of the calculation before returning it to the function.

```cpp
/// Good - All conditions must have braces, and wrapped with prefix
bool result = (condition_1)
           && (long_condition_2)
           && (very_long_condition_3);
```

---
---
---
---
---

## F. Function Formatting

---

### F.1 - Function Default Value: `Declaration only`

```cpp
/// Good - declaration with default value
class Player : public PlayerBase {
 public:
  void MoveHorizontal(double Range, double Speed = 1, bool isLeft = false) override;
};
```

---

### F.2 - Function Tag: `Before Function Name`

> Attributes, and macros that expand to attributes, appear at the very beginning of the function declaration or definition, before the return type:

```cpp
[[noreturn]] void DoNothing();
[[nodiscard]] bool IsOk();
ABSL_ATTRIBUTE_NOINLINE void ExpensiveFunction();
```

---

### F.3 - Function Definition: `No omomission`

> Do not omit any parameter names. Consider good self-explainary param names.

```cpp
/// Good - self-explainary parameter name
class Foo {
 public:
  Foo(const Foo& self) = delete;
  Foo& operator=(const Foo& self) = delete;
};

/// Good - self-explainary parameter name
class Shape {
 public:
  virtual void SetSpeed(float fNewSpeed) = 0;
};

/// Good - declaration with descriptive parameter name
class Circle : public Shape {
 public:
  void Rotate(double radians, bool isClockwise = false) override;
};

/// Good - declaration with comments
void Circle::Rotate(double /*radians*/) {}


// Bad - if someone wants to implement later, it's not clear what the
// variable means.
void Circle::Rotate(double) {}
```

---

### F.4 - Function Declaration: `Single Indent Wrapping`

```cpp
bool ClassName::Foo(Type par1, Type par2) {
  DoSomething();
  ...
}

bool LongClassName::ExtremelyProfoundlyExtendedSuperVeryLongFunction(
    Type par_name1,
    Type par_name2,
    Type par_name3) {
    DoSomething();  // 2 space indent
    ...
}
```

---

### F.5 - Function Call: `First Param Wrapping`

> Write the call all on a single line, wrap the arguments at the parenthesis. You might create a variable that capture a calculation with descripted name or using comment.

```cpp
/// Long argument name example
bool result = DoSomething(argument1, argument2, argument3);
bool answer = DoSomething(extremelyProfoundlyExtendedSuperVeryLongArgument1,
                          extremelyProfoundlyExtendedSuperVeryLongArgument2,
                          extremelyProfoundlyExtendedSuperVeryLongArgument3);

/// Long calculation example
int nUpperValue = alphaVeryLong[x] + betaVeryLong[y] + deltaVeryLong[z];
bool result1 = DoSomething(my_heuristic, x, y, z);
bool result2 = DoSomething(alphaVeryLong[x] + betaVeryLong[y] + deltaVeryLong[z], // Upper Value.
                           x, y, z);

/// Meaningful wrapping example
vector3D.Transform(x1, y1, z1,
                   x2, y2, z2,
                   x3, y3, z3);

/// Lambda formatting example
std::vector<int> to_remove = {2, 7, 2};
std::vector<int> digits = {2, 7, 0, 2, 2, 0, 0, 4};
digits.erase(std::remove_if(digits.begin(), digits.end(), [&to_remove](int i) {
               return count(to_remove.begin(), to_remove.end(), i) > 0;
             }),
             digits.end());
```

---

### F.6 - Function Return: `First Condition Wrapping With Prefix`

> Do not needlessly surround the return expression with parentheses. Use parentheses in `return expr;` only where you would use them in `x = expr;`

```cpp
return result;                 // Good - Non condition shouldnt have braces
return (value);                // Bad - You wouldn't write var = (value);
return(result);                // Bad - Return is not a function!
return var = value;            // Bad - Reduce readability

/// Good - All conditions must have braces, and wrapped with prefix
return (condition_1)
    && (long_condition_2)
    && (very_long_condition_3);
```

---

### F.8 - Lambda Expressions

> For by-reference captures, do not leave a space between the ampersand (&) and the variable name. Short lambdas may be written inline as function arguments.

```cpp
int x = 0;
auto x_plus = [&x](int value) -> int { return x + value; }

std::vector<int> to_remove = {2, 7, 2};
std::vector<int> digits = {2, 7, 0, 2, 2, 0, 0, 4};
digits.erase(std::remove_if(digits.begin(), digits.end(), [&to_remove](int i) {
               return count(to_remove.begin(), to_remove.end(), i) > 0;
             }),
             digits.end());
```

---

### F.8 - Function Max Line Limit `21 lines`

> The strict limit is `21 lines`. Adding more might reduce the modularity of the code and make the functions having multiple reponsibilities. Even though there are cases where needed, it is not recommended to do so, try refactoring the code or representing the function in another way.
>
> These are the recommended limits for common cases:
>
> - Simple functions: `3 lines` - Like `GetFunction()`, `IsFunction()`, `CanFunction()`, ...
> - Calculation functions: `8 lines`
> - Module functions: `13 lines`

## Z. Frequently Asked Questions

### `FAQ#1:` Why dont we use tabs identation instead of spaces ?

> - While tabs are a valid choice, they can lead to inconsistencies in how code appears.
> - Tab are viewed differently in editors with different tab width settings.
> - Might confuse project collaborators and reduce team work performance.

### `FAQ#2:` Why do we use identation of 2 spaces or 8 spaces ?
>
> - Enhance code readability, while balancing with the compactness.
> - 8 spaces might be good but most of the codes are simple and small.

### `FAQ#3:` Why do we use limited code limit ?
>
> - Excessive nesting can lead to complex and convoluted logic that is hard to understand.
> - Reduce the testing and maintain code, improve bug tracking time.

### `FAQ#4:` What if a code exceeds the nested limit ?
>
> - You might considering refactor the code for providing better context:
>   - Early Returns.
>   - Guard Clauses.
>   - Ternary Operators.
>   - Defining extra variables.
>   - Switch statements
>   - Inverted if.

### `FAQ#5:` Why use such a high character limit?
>
> - Facilitates readable variables, fostering expressiveness.
> - Averts deeply nested structures with longer lines.
> - Minimizes vertical scrolling, enhancing code visibility.

### `FAQ#6:` Why not use unlimited character limit?
>
> - Restricts to 120 to avoid eye strain from smaller text or excessively wide code.

### `FAQ#7:` Why use such a high nested limit?
>
> - Enables variables to provide meaningful context.
> - Reduces abbreviations and misuse of variables.
> - Allows functions or code structures to be self-explanatory.

### `FAQ#8:` Why not use a higher nested limit?
>
> - Eases code review and collaboration by reducing time spent on variable names.
> - While readability is desirable, it shouldn't be overly verbose to improve conciseness.
> - Typing might be an issue as longer names increase development cost.

### `FAQ#9:` Why use such a small line limit?
>
> - Promotes modularity and single responsibility.
> - Shorter lines of code enhance readability.

### `FAQ#10:` Why to have different line limits?
>
> - Avoids overly fragmented code by not using functions that are too small.
> - Prevents an increase in maintenance costs from numerous functions with simple lines.
