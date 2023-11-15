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

## Category: Cleaner

## Category: Validators 

## Category: Checkers

## Category: Getters

## Category: Setters

## Category: Updaters

## Category: Loaders

## Category: Savers

## Category: Custom