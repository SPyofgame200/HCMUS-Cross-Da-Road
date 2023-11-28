# Function Standard

## General Cases

- All functions must named under `PascalCase()`
- Functions might have their prefix, based on their group tags.
- Functions might have their suffix, based on the returned type.
- Here are all possibles tags, each tag indicate a group of function share similarities.
  - `[Constructors]` initialize object's variables upon creation.
  - `[Destructors]` cleaning and release resources upon destruction.
  - `[Initializers]` boolean functions that being used in the `constructors`.
  - `[Clean-up]` boolean functions that being used in the `destructors`.
  - `[Release]` helper functions for the clean-up for releasing pointer resources
  - `[Validators]` boolean functions that validates certain actions.
  - `[Checkers]` boolean functions to check certain conditions.
  - `[Constant Getters]`
  - `[Property Getters]`
  - `[Utility Getters]`
  - `[Setters]`
  - `[File Managements]`
  - `[Input - Output]`

## `[Constructors]`

Constructors are special member functions responsible for initializing the object when it is created.

They have the same name as the class and do not have a return type.

Requirement:

- Non-static non-pointer variables inside a class **MUST** being initialized, in the constructor.
- You might use functions inside the constructor to do it, those should return boolean.
- We recommended you use `[Initializers]` for constructions.

Notice:

- Pointer Variables: You should init them as `nullptr` using member initializer list. Then you can use another functions to provide details. Why you might ask, since certain classes might be called by another thread, which is unsafe it isnt initialized as nullptr upon creation.
- Static Variables: You should init them in the source file (not the header file).

Message:

- By using `[Initializers]`, if the member variables isnt being constructed successfully, you should log a Warning or Error messages for better bug tracing.

### Foo.h

```cpp
#ifndef FOO_H
#define FOO_H

class Foo
{
public:
    Foo();  // Constructor declaration
};

#endif // FOO_H
```

### Foo.cpp

```cpp
#include "Foo.h"

Foo::Foo()
{
    // Constructor definition
    // Initialization code goes here
}
```

### Bar.h

```cpp
#ifndef BAR_H
#define BAR_H

#include <iostream>

class Bar
{
public:
    // Constructor declaration
    Bar(int initialValue);

    // Function to demonstrate initialization with boolean return
    bool initializeWithFunction();

    // Function to provide details for pointer variables
    void provideDetailsForPointer();

    // Static variable for demonstration
    static int staticVariable;

private:
    // Non-static non-pointer variable
    int nonStaticVariable;

    // Pointer variable
    int* pointerVariable;

    // Function to demonstrate logging a warning or error message
    void logMessage(const std::string& message);
};

#endif // BAR_H
```

### Bar.cpp

```cpp
#include "Bar.h"

// Static variable initialization in the source file
int Bar::staticVariable = 0;

Bar::Bar(int initialValue) : nonStaticVariable(initialValue), pointerVariable(nullptr)
{
    // Constructor definition
    // Initialization code goes here
    bool initializationResult = initializeWithFunction();

    if (!initializationResult) {
        logMessage("Initialization failed. Consider checking the parameters.");
    }

    provideDetailsForPointer();
}

bool Bar::initializeWithFunction()
{
    // Function for initialization logic
    // Return true if initialization is successful, false otherwise
    return true; // Example: Always return true for simplicity
}

void Bar::provideDetailsForPointer()
{
    // Function to provide details for pointer variable
    if (pointerVariable == nullptr) {
        pointerVariable = new int(42); // Example: Initializing the pointer variable
    }
}

void Bar::logMessage(const std::string& message)
{
    // Function to log a warning or error message
    std::cerr << "Warning/Error: " << message << std::endl;
}
```

## Category: [Destructors]

Destructors handle the cleanup of resources when an object is about to be destroyed.

You should output to the console indicating the destruction of classes if they are handled successfully.

**Note:** If a class is destructed excessively, the messages (`std::cerr`) should be rate-limited.

**Foo.h:**

```cpp
#ifndef FOO_H
#define FOO_H

class Foo
{
public:
    ~Foo();  // Destructor declaration
};

#endif // FOO_H
```

**Foo.cpp:**

```cpp
#include "Foo.h"

Foo::~Foo()
{
    // Destructor definition
    std::cerr <<  "Foo::~Foo(): is being destructed" << std::endl;
}
```

## Category: Initializer

Initializers are functions responsible for initializing the object's state.

**Foo.cpp:**

```cpp
void Foo::Create()
{
    // Initialization code goes here
}

Foo::Foo()
{
    Create();  // Call the initializer in the constructor
}
```

## Category: Cleaner

Cleaners handle the cleanup of resources before an object is destroyed.

**Foo.cpp:**

```cpp
void Foo::Destroy()
{
    // Cleanup code goes here
}

Foo::~Foo()
{
    Destroy();  // Call the cleaner in the destructor
}
```

## Category: Validators

Validators are functions used to check the validity of certain conditions. Function names should use a prefix like "Can-*" or "Validate-*", and they should use `const` if they don't modify the object's state.

**Foo.cpp:**

```cpp
bool Foo::CanMoveUp() const
{
    return player.PositionY() + 1 <= TOP_BORDER;
}
```

## Category: Checkers

Checkers are functions used to check specific conditions, and they should use `const` if they don't modify the object's state. Function names should use a prefix like "Is-*".

**Foo.cpp:**

```cpp
bool Foo::IsOdd(int x) const
{
    return (x % 2 != 0);
}
```

## Category: Getters

### Category: Constant Getters

Constant getters return values without modifying the object's state. They should use `const` and can use `constexpr`.

**Foo.h:**

```cpp
class Foo
{
public:
    int GetX() const;  // Constant getter declaration
};
```

**Foo.cpp:**

```cpp
int Foo::GetX() const
{
    return X;
}
```

### Category: Properties Getters

Properties getters return values related to the object's properties. They should use `const` but not `constexpr`.

**Foo.h:**

```cpp
class Foo
{
public:
    int GetPosition() const;  // Property getter declaration
};
```

**Foo.cpp:**

```cpp
int Foo::GetPosition() const
{
    return position;
}
```

### Category: Utilities Getters

Utilities getters are used for calculations and should use `const`. Function names should use prefixes like "Get-*" or "Calculate-*".

**Foo.cpp:**

```cpp
int Foo::CalculateArea() const
{
    // Calculation code goes here
}
```
