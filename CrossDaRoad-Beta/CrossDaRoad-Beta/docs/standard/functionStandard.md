# Class Organization

---
---
---
---
---

## ∅. General

---

### ∅.I. General

- All functions must be named using `PascalCase()`.
- Functions may have prefixes based on their group tags.
- Functions may have suffixes based on the returned type.

---

### ∅.II. Class Tags

- Tags are utilized to indicate groups of functions that share similarities.
- Organizing functions with tags enhances clarity and facilitates easier searches.
- Non-special tag naming must be singular noun.
- You can add messages after the tag

- Here is a list of possible tags, arranged in the order of declaration in the class:
  - I. Component Group:
    - `[Static Property]`: - - -
    - `[Data Component]`: Manages the main information of the class.
    - `[Handler Component]`: Deals with the handlers of the class.
    - `[Instance]`: Manages instance-related operations.
  - II. Core Group:
    - `[Friend Property]`: - - -
    - `[Member Property]`: - - -
    - `[Constructor]`: Initializes object variables upon creation.
    - `[Destructor]`: Manages cleaning and releases resources upon destruction.
  - III. Lifecycle Group:
    - `[Initializer]`: Boolean functions used in constructors.
    - `[Clean-up]`: Boolean functions used in destructors.
    - `[Reseter]`: Helper function for resetting certain properties to default states.
    - `[Core]`: Manipulation and control lifecycle core actions.
  - IV. Verification Group:
    - `[Evaluation]`: Calculation function that doesnt mutate the data.
    - `[Validator]`: Boolean functions that validate certain actions.
    - `[Checker]`: Boolean functions to check specific conditions.
    - `[Getter]`: Retrieves data or properties.
  - V. Action Group:
    - `[Loader]`: Boolean functions used to load and extract data.
    - `[Setter]`: Sets data or properties.
    - `[Handler]`: Handler functions of the events
    - `[Event]`: Events functions
  - VI. Data Group:
    - `[File]`: Manages file-related operations.
    - `[Input]`: Handles input-related functionality only.
    - `[Output]`: Manages output-related functionality only.
    - `[Debug]`: Special functions for debugging

- Functions without those common patterns should use special tags
  - `[Unused]`:
    - Unused functions or variables.
    - Serve design purposes, allow extensibilities.
  - `[TODO]`:
    - Functions that are intended to be implemented.
    - Do not spam the tag unless needed.
  - `[Utility]`:
    - Helper functions, should be private, otherwise include a utilities file.
    - Better to be defined belowest everything
  - `[Deprecated]`:
    - Functions that are no longer being used or supported.
    - Functions that have limited usecase, or contains side-effects

- If the tags are small, you should merge them using `&` in the between the tags

```cpp
private: /// [Constructor] & [Destructor]
    cFrameManager();
    ~cFrameManager();
```

- Tag close relation:
  - `[Data Component]` and `[Handler Component]`
  - `[Constructor]` and `[Destructor]`
  - `[Constructor]` and `[Initializer]`
  - `[Destructor]` and `[Clean-up]`
  - `[Validator]` and `[Checkers]`
  - `[Reseter]` and `[Setter]`
  - `[Getter]` and `[Setter]`
  - `[Input]` and `[Output]`

---

### ∅.III. Table of contents

---
---
---
---
---

## I. Class Components

---

### I.A. `[Static Property]`

---

### I.B. `[Data Component]`

---

### I.C. `[Handler Component]`

---

### I.D. `[Instance]`

---
---
---
---
---

## II. Class Cores

---

### II.A. `[Friend Property]`

---

### II.B. `[Member Property]`

---

### II.C. `[Constructor]`

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

### II.D. `[Destructor]`

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

---
---
---
---
---

## III. Class Lifecycles

---

### III.A. `[Initializer]`

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

---

### III.B. `[Clean-up]`

**Purpose:**

- Handle the destruction.

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

---

### III.C. `[Reseter]`

---

### III.D. `[Core]`

---
---
---
---
---

## IV. Class Verifications

---

### IV.A. `[Validator]`

---

### IV.B. `[Checker]`

---

### IV.C. `[Getter]`

---
---
---
---
---

## V. Class Action

---

### V.A. `[Loader]`

---

### V.B. `[Setter]`

---

### V.C. `[Handler]`

---

### V.D. `[Event]`

---
---
---
---
---

## VI. Class Data

---

### VI.A. `[File]`

---

### VI.B. `[Input]`

---

### VI.C. `[Output]`

---

### VI.D. `[Debug]`

---

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

.

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
