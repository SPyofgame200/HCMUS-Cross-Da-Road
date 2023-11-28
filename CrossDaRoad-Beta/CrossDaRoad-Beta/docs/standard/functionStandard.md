# Function Standard

---

## ∅. General Cases

- All functions must named under `PascalCase()`
- Functions might have their prefix, based on their group tags.
- Functions might have their suffix, based on the returned type.
- We use tags for indicating each group of functions that share similarities.
- Also, by using tags, we can organize the functions better and search function easier.

- Here are all possibles tags
  - `[Constructor]` initialize object's variables upon creation.
  - `[Destructor]` cleaning and release resources upon destruction.
  - `[Initializer]` boolean functions that being used in the `constructors`.
  - `[Loader]` boolean functions that are used to load and extract data.
  - `[Clean-up]` boolean functions that being used in the `destructors`.
  - `[Release]` helper functions for the clean-up for releasing pointer resources
  - `[Validator]` boolean functions that validates certain actions.
  - `[Checker]` boolean functions to check certain conditions.
  - `[Constant Getter]`
  - `[Property Getter]`
  - `[Utility Getter]`
  - `[Setters]`
  - `[File Management]`
  - `[Data Component]`
  - `[Handler Component]`
  - `[Input - Output]`
  - `[Instantce]`

- Functions without those same patterns should use these special tag:
  - `[Custom]` customized on their own, unless specified needed
  - `[Deprecated]` the function is no longer being used or supported
  - `[Prototype]` the function is just a sketch of design pattern
  - `[Todo]` the function that is intended to be implemented

---

## A. `[Constructor]`

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

---

## B. `[Destructor]`

Destructors handle the cleanup of resources when an object is about to be destroyed.

You should output to the console indicating the destruction of classes if they are handled successfully.

Requirement

- Always log the message for destruction, you might want to output certain useful information like the container size before its destruction

Notice:

- Do not always delete pointers. sometimes certain dependencies pointers needed to be assign to `nullptr` and other function will destruct pointers later.

- If a class is destructed excessively, the messages (`std::cerr`) should be rate-limited.

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

## C. `[Initializer]`

Initializers are functions responsible for initializing the object's state.

Function names:
- `[Create-*]`: Loading and preparing data for the use of other functions  
- `[*-Init]`: Initialize certain components of the class

Requirement:
- Always have boolean return type, return true indicating success initialization
- Return false should come with logigng warning or error messages
- Should be called from the constructor, but should always used on their own without side-effects

**Foo.cpp:**

```cpp
bool Foo::Init()
{
    // Initialization code goes here
    return true; // indicating success init
}

bool Foo::Create()
{
    // Construct the class in a special way
}

Foo::Foo()
{
    if (!Init()) { // if the component initialization is failed
        // logging warning or error messages
    }
}

int main()
{
    if (Foo.Create()) {
        ...
    }
    return 0;
}
```

## D. `[Clean-up]`

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
