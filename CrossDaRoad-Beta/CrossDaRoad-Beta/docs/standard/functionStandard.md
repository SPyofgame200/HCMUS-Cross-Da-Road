# Comment Standard

## Category: Constructors

```
class Foo()
{
    Foo();
}

Foo::Foo()
{
}
```

## Category: Destructor

with "uMessage.h", any destructed class that is being destructed too much will be rate limited and logging into a file instead.

```
#include "uMessage.h"
class Foo()
{
    ~Foo();
}

Foo::~Foo()
{

    message::error("~Foo", "is being destructed");
}
```

## Category: Initializer

```
Foo::Foo()
{
    Create();
}

Foo::Create()
{
    ...
}
```

## Category: Cleaner

```
Foo::~Foo()
{
    Destroy();
}

Foo::Destroy()
{
    ...
}
```

## Category: Validators 

Functions should use const
Prefixes: Can-\*, Validate-\*
Naming: Verb

```
Foo::CanMoveUp()
{
    return player.PositionY() + 1 <= TOP_BORDER;
}
```

## Category: Checkers

Functions needed to use const
Prefix: Is-*
Naming: Verb

```
Foo::IsOdd(int x) const
{
    return (x % 2 != 0);
}
```

## Category: Getters

### Category: Constant Getters

Function MUST use const, can use constexpr
Prefix: Dont have any prefix
Naming: Properties' noun or self-explainary constexpr values

### Category: Properties Getters

Functions MUST use consts, shouldnt use constexpr
Prefix Get-*
Naming: Get-Noun

```
Foo::GetX() const
{
    return X;
}
```

### Category: Utilities Getters

Mostly for calculations, should use const
Prefix: Get-\*, Calculate-\*
Naming: Verb-Noun

```
Foo::CalculateArea()
{
}
```

## Category: Setters

## Category: Updaters

## Category: Loaders

## Category: Savers

## Category: Custom