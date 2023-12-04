# Class Organization

---
---
---
---
---

## Table of Contents

- [Class Organization](#class-organization)
  - [Table of Contents](#table-of-contents)
  - [∅. General Guidelines](#-general-guidelines)
    - [∅.I. General Functions Naming](#i-general-functions-naming)
    - [∅.II. Class Tags](#ii-class-tags)
    - [∅.III. Table of contents](#iii-table-of-contents)
  - [I. Class Components](#i-class-components)
    - [I-A. `[Static Property]`](#i-a-static-property)
    - [I-B. `[Data Component]`](#i-b-data-component)
    - [I-C. `[Handler Component]`](#i-c-handler-component)
    - [I-D. `[Instance]`](#i-d-instance)
  - [II. Class Cores](#ii-class-cores)
    - [II-A. `[Friend Property]`](#ii-a-friend-property)
    - [II-B. `[Member Property]`](#ii-b-member-property)
    - [II-C. `[Constructor]`](#ii-c-constructor)
    - [II-D. `[Destructor]`](#ii-d-destructor)
  - [III. Class Lifecycles](#iii-class-lifecycles)
    - [III-A. `[Initializer]`](#iii-a-initializer)
    - [III-B. `[Disposer]`](#iii-b-disposer)
    - [III-C. `[Reseter]`](#iii-c-reseter)
    - [III-D. `[Core]`](#iii-d-core)
  - [IV. Class Verifications](#iv-class-verifications)
    - [IV-A. `[Evaluation]`](#iv-a-evaluation)
    - [IV-B. `[Validator]`](#iv-b-validator)
    - [IV-C. `[Checker]`](#iv-c-checker)
    - [IV-D. `[Getter]`](#iv-d-getter)
  - [V. Class Action](#v-class-action)
    - [V-A. `[Loader]`](#v-a-loader)
    - [V-B. `[Setter]`](#v-b-setter)
    - [V-C. `[Handler]`](#v-c-handler)
    - [V-D. `[Event]`](#v-d-event)
  - [VI. Class Data](#vi-class-data)
    - [VI-A. `[File]`](#vi-a-file)
    - [VI-B. `[Input]`](#vi-b-input)
    - [VI-C. `[Output]`](#vi-c-output)
    - [VI-D. `[Debug]`](#vi-d-debug)
  - [Category: Validators](#category-validators)
  - [Category: Checkers](#category-checkers)
  - [Category: Getters](#category-getters)
    - [Category: Constant Getters](#category-constant-getters)
    - [Category: Properties Getters](#category-properties-getters)
    - [Category: Utilities Getters](#category-utilities-getters)

## ∅. General Guidelines

---

### ∅.I. General Functions Naming

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
  - I. Core Group:
    - `[Property]`: - - -
    - `[Component]`: Manages the main information of the class.
    - `[Accessor]`: Get the current object or its components.
  - III. Lifecycle Group:
    - `[Constructor]`: Initializes object variables upon creation.
    - `[Destructor]`: Manages cleaning and releases resources upon destruction.
    - `[Initializer]`: Boolean functions used in constructors.
    - `[Disposer]`: Boolean functions used in destructors.
  - IV. Evaluation Group:
    - `[Calculator]`: Calculation function that doesnt mutate the data.
    - `[Validator]`: Boolean functions that validate certain actions.
    - `[Checker]`: Boolean functions to check specific conditions.
    - `[Getter]`: Retrieves class data and properties.
  - V. Action Group:
    - `[Reseter]`: Helper function for resetting certain properties to default states.
    - `[Setter]`: Sets data or properties.
  - VI. Events Group:
    - `[Core]`: Core events controller.
    - `[Event]`: Events functions.
    - `[Handler]`: Handler functions of the events.
  - VII. Data Group:
    - `[File]`: Manages file-related operations.
    - `[Input]`: Handles class data input functionality.
    - `[Output]`: Manages class data output functionality.
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
  - `[Destructor]` and `[Disposer]`
  - `[Validator]` and `[Checkers]`
  - `[Reseter]` and `[Setter]`
  - `[Getter]` and `[Setter]`
  - `[Input]` and `[Output]`

---

### ∅.III. Table of contents

## G. Class

### G.1 - Class Tag

### G.2 - Class Properties: `[Property]`

> Declare properties in order:
>
> - Static Properties.
> - Friend Properties.
> - Member Properties.
> - Unused Properties.

### G.3 - Class Components: `[Component]`

> Declare components in order:
>
> - Data Component
> - Handler Component

### G.4 - Class Instance

---
---
---
---
---

## I. Class Components

---

### I-A. `[Property]`

Static properties are attributes or variables that belong to the class itself rather than instances of the class. Those properties are shared among all instances of the class.

#### Pros

- It will be memory efficient if all instances of an object need to share such variables.

#### Cons

- What is the consequences if there are too many class static properties ?

#### Keyword

- `static` must use it to define a static property.

#### Declaration

- `static type var;`

#### Definition

- `type class::var = defaultValue;`

#### Requirement

- If a variable is a dependency pointer for a component, it should also be static. (for example: passing `this` into handler components)
- Singleton design.
- What is required to use this static property and not friend nor a member property ?

---

### I-B. `[Data Component]`

A Data Component is employed when a class becomes sufficiently complex, featuring a multitude of private member variables that share a close relationship.  In such cases, it is beneficial to segregate the responsibilities and improve the structure by utilizing a separate class to encapsulate and manage this related data.

#### Pros

- Better storage handling capabilities and accessiblities, prevent unauthorized access.
- Components can be reused, reduce the redundancy, improve integrity and readability.
- Reduce handler dependencies by injecting the pointer to the data instead of the main class.

#### Cons

- Make the class more complex
- Increase the code amount.

---

### I-C. `[Handler Component]`

When a class is big enough with a bunches of public classes, that have close relation to each other. We might want to separate the concenrs of data handling, by using a class that have a pointer to `this` or `this->dataComponents`. Handler components manage specific functionalities and behaviors.

#### Pros

- Avoid the God Classes.
- They promote modularity and avoid unintentionally misusing the functions.

#### Cons

- Most of the handler components can not be reused, but sticking to their main class.

---

### I-D. `[Instance]`

---
---
---
---
---

## II. Class Cores

---

### II-A. `[Friend Property]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### II-B. `[Member Property]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### II-C. `[Constructor]`

Constructors are special member functions responsible for initializing the object when it is created.
They have the same name as the class and do not have a return type.

#### Keyword

- `private` if singletons.
- `public` if objects.

#### Declaration

- `Class()`
- `Class(tDefault = tDefaultValue)`
- Note: `t-*` prefix indicating variable type.

#### Definition

- `Class::Class() : tMemberVar(defaultValue) {}`
- `Class::Class() : ptrMemberPointer(nullptr) {}` - pointers should be init as nullptr
- `Class::Class(tDefault) : tMemberVar(tDefault) {}`
- Note: `t-*` prefix indicating variable type.

#### Requirement

- Non-static non-pointer variables inside a class **MUST** being initialized, in the constructor.
- You might use functions inside the constructor to do it, those should return boolean.
- Please use member initializer list whenever it is possible
- Use `[Initializer]` if the variables can be re-initialized multiple times.

#### Notice

- Pointer Variables: You should init them as `nullptr` using member initializer list. Then you can use another functions to provide details. Why you might ask, since certain classes might be called by another thread, which is unsafe it isnt initialized as nullptr upon creation.
- Static Variables: You should init them in the source file (not the header file).

#### Message

- Log Level: `FATAL` - construction failure.
- By using `[Initializers]`, if the returned value is false, you should log a Warning or Error messages for bug tracking.

#### Example

##### `Foo.h`

```cpp
#ifndef FOO_H
#define FOO_H

class Foo
{
public: // [Constructor]
    Foo();
};

#endif // FOO_H
```

##### `Foo.cpp`

```cpp
#include "Foo.h"

Foo::Foo()
{
    // Constructor definition
    // Initialization code goes here
}
```

---

### II-D. `[Destructor]`

Destructors handle the cleanup of resources when an object is about to be destroyed.

#### Keyword

- `private` if singletons.
- `public` if objects.
- `virtual` if you use inheritance.
- `final` if it is the final produced class (so that the parent can be destructed).

#### Declaration

- `~Class()`

#### Definition

- `Class::~Class() {}`

#### Requirement

- No parameter allowed.
- Do not clean-up on itself, please use `[]`.

#### Notice

- Do not always delete pointers. sometimes certain dependencies pointers needed to be assign to `nullptr` and other function will destruct pointers later.
- If a class is destructed excessively, the messages (`std::cerr`) should be rate-limited.

#### Message

- Log Level: `FATAL` - destruction failure.
- You can output certain useful information like the container size before its data is released.

#### Example

##### `Foo.h`

```cpp
#ifndef FOO_H
#define FOO_H

class Foo
{
public: // [Destructor]
    ~Foo(); 
};

#endif // FOO_H
```

##### `Foo.cpp`

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

### III-A. `[Initializer]`

Initializers are functions responsible for initializing the object's state.

#### Keyword

- `private` if singletons.
- `public` if objects.

#### Declaration

- `bool Create-*()` Preparing data for the use of lifecycle functions
- `bool Init-*()` Initialize certain components of the class
- Note: `*-` indicating prefix noun and `-*` indicating suffix noun

#### Definition

- `bool Class::Create-*()`
- `bool Class::Init-*()`
- Note: `*-` indicating prefix noun and `-*` indicating suffix noun

#### Requirement

- Always have boolean return type, return true indicating success initialization
- Should be called from the constructor, but should always used on their own without side-effects

#### Notice

- All member variables using `Init()` must be reinitializable, otherwise use `Create()` instead.

#### Message

- Log Level: `FATAL` - creation failure.
- Log Level: `ERROR` - init failure.

#### Example

##### `Foo.h`

```cpp
#ifndef FOO_H
#define FOO_H

class Foo
{
private: // [Member Property]
    int *x;

public: // [Constructor] & [Destructor]
    Foo();
    ~Foo();

public: // [Initializer]
    bool Init();
    bool Create();

public: // [Getter]
    int GetX() const; // Constant getter declaration
};

#endif // FOO_H

```

##### `Foo.cpp`

```cpp
#include "Foo.h"
#include <iostream> // Include any necessary headers

Foo::Foo() : x(nullptr) // Initialize the pointer to nullptr in the constructor
{
    if (!Create()) // if the component creation fails
    {
        // logging warning or error messages
        std::cerr << "Foo::Foo(): Creation failed!" << std::endl;
    }
}

Foo::~Foo()
{
    delete x; // Release memory in the destructor
    // Destructor definition
    std::cerr << "Foo::~Foo(): is being destructed" << std::endl;
    // Additional cleanup code goes here
}

bool Foo::Create()
{
    x = new int;
    return true; // indicating successful creation
}

bool Foo::Init()
{
    if (x)
    {
        *x = 0;
        return true; // indicating successful initialization
    }
    else
    {
        // Handle the case where the pointer is not properly created
        std::cerr << "Foo::Init(): x is not properly created!" << std::endl;
        return false;
    }
}

int Foo::GetX() const
{
    if (x)
    {
        return *x;
    }
    else
    {
        // Handle the case where the pointer is null
        std::cerr << "Foo::GetX(): x is null!" << std::endl;
        return 0; // or return some default value
    }
}

```

#### `main.cpp`

```cpp
int main()
{
    Foo myFoo;
    if (myFoo.Create())
    {
        // Code to execute after successful creation
        std::cout << "Foo created successfully!" << std::endl;
        myFoo.Init();
        std::cout << "X value: " << myFoo.GetX() << std::endl;
    }
    else
    {
        // Code to handle creation failure
        std::cerr << "Error creating Foo!" << std::endl;
    }
    return 0;
}
```

---

### III-B. `[Disposer]`

Clean-up are functions responsible for clean-up and release the object's state.

#### Keyword

- `private` if singletons.
- `public` if objects.
- `virtual` if you use inheritance (so that the parrent can be cleaned-up)

#### Declaration

- `bool Destroy-*()` Preparing data for the use of lifecycle functions
- `bool Exit-*()` Initialize certain components of the class
- `bool Release-*(&ptr)` Helper function for releasing a pointer.
- `bool Clean-*(&ptr)` Helper function for cleaning up trash values from a pointer.
- Note: `*-` indicating prefix noun and `-*` indicating suffix noun

#### Definition

- `bool Class::Destroy-*()`
- `bool Class::Exit-*()`
- `bool Class::Release-*(&ptr)`
- `bool Class::Clean-*(&ptr)`
- Note: `*-` indicating prefix noun and `-*` indicating suffix noun

#### Requirement

- Always have boolean return type, return true indicating success cleaning up and release resources.
- Should be called from the destructor, but should always used on their own without side-effects

#### Notice

- All member variables using `Init()` must be reinitializable, otherwise use `Create()` instead.

#### Message

- Log Level: `FATAL` - destruction failure.
- Log Level: `ERROR` - exit failure.
- Log Level: `WARNING` - release or clean-up failure.

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### III-C. `[Reseter]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### III-D. `[Core]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---
---
---
---
---

## IV. Class Verifications

---

### IV-A. `[Evaluation]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### IV-B. `[Validator]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### IV-C. `[Checker]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### IV-D. `[Getter]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---
---
---
---
---

## V. Class Action

---

### V-A. `[Loader]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### V-B. `[Setter]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### V-C. `[Handler]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### V-D. `[Event]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---
---
---
---
---

## VI. Class Data

---

### VI-A. `[File]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### VI-B. `[Input]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### VI-C. `[Output]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

---

### VI-D. `[Debug]`

#### Keyword

#### Declaration

#### Definition

#### Requirement

#### Notice

#### Message

#### Example

##### `Foo.h`

##### `Foo.cpp`

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
