# Function Standard

## Category: [Constructors]

Constructors are special member functions responsible for initializing the object when it is created. They have the same name as the class and do not have a return type. Here's an example of a simple constructor for a class `Foo`:

**Foo.h:**
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

**Foo.cpp:**
```cpp
#include "Foo.h"

Foo::Foo()
{
    // Constructor definition
    // Initialization code goes here
}
```

## Category: [Destructors]

Destructors handle the cleanup of resources when an object is about to be destroyed. In this example, the destructor of class `Foo` is logging a message using an external logging mechanism provided by the "uMessage.h" header. If a class is destructed excessively, it will be rate-limited, and messages will be logged into a file.

**Foo.h:**
```cpp
#ifndef FOO_H
#define FOO_H

#include "uMessage.h"

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
    message::error("~Foo", "is being destructed");
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