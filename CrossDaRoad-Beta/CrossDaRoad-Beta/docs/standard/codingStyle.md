# Coding Style

---
---
---
---
---

## Project Styles

---

### General Rule

#### **Line Length:** `120 characters per line`

> Allows a broad view of expressive code.

#### **Editor Character:** `ASCII Only`

> Do not use Unicode, considering using `wstring, wchar_t, L".."` with UTF-8 Formatting instead.

#### **Brackets Style:** `One True Brace Style`

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
```

#### **Variable Declaration:**  `Omit Redundant Spaces`

```cpp
// These are fine, space preceding.
char *c;
const std::string &str;
int *GetPointer();
std::vector<char *>

// These are fine, space following (or elided).
char* c;
const std::string& str;
int* GetPointer();
std::vector<char*>  // Note no space between '*' and '>'

int x, y;    // Acceptable - Helpful for readability
int x, *y;   // Bad - no & or * in multiple declaration
int* x, *y;  // Bad - no & or * in multiple declaration; inconsistent spacing
char * c;    // Bad - spaces on both sides of *
const std::string & str;  // Bad - spaces on both sides of &
```

#### **Variable Initialization:** `Always Init`

> Always init variables with default values, either in compile time or in runtime. Internal property initialization should have prefix `this->` for avoiding typo.

```cpp
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

### Code Formatting

#### **Brackets Spacing:** `Omit Redundant Spaces Only`

> Only redundant spaces needed to be removed. `First Param Swapping` isnt considered as redundatn spaces but rather code formatting.

```cpp
if(condition) {}                   // Bad - space missing after `if`.
else if ( condition ) {}           // Bad - space between the parentheses and the condition.
else if (condition){}              // Bad - space missing before `{`.
else if(condition){}               // Bad - multiple spaces missing.
for (int a = f();a == 10) {}       // Bad - space missing after the semicolon.
```

#### **Indentation:** `4 spaces per indent`

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

#### **Maximum nested scope:** `3 nested per function`

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

#### **Padding:** `Control Flow Padding Only`

> Insert space padding between a control flow (e.g. 'if', 'for', 'while'...) and the following paren.

#### **Function Default Value:** `Declaration only`

```cpp
/// Good - declaration with default value
class Player : public PlayerBase {
 public:
  void MoveHorizontal(double Range, double Speed = 1, bool isLeft = false) override;
};
```

#### **Floating Point Format:** `Literal value`

```cpp
/// Bad, do not use
float f1 = 1.f;
float f2 = 1;
long double ld = -.5L;
double d = 1248e6;

/// Recomended
float f1 = 1.0f;
float f2 = 1f;
long double ld = -0.5L;
double d = 1248.0e6;
```

- **Function Max Line Limit:**
  - Simple functions: `3 lines`
  - Calculation functions: `8 lines`
  - Core module functions: `13 lines`

---

### Function Styles

#### **Function Tag:** `Before Function Name`

> Attributes, and macros that expand to attributes, appear at the very beginning of the function declaration or definition, before the return type:

```cpp
[[noreturn]] void DoNothing();
[[nodiscard]] bool IsOk();
ABSL_ATTRIBUTE_NOINLINE void ExpensiveFunction();
```

#### **Function Definition:** `No omomission`

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

##### **Function Declaration:** `Single Indent Wrapping`

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

#### **Function Call:** `First Param Wrapping`

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

#### **Function Return:** `First Condition Wrapping With Prefix`

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

#### **Lambda Expressions:**

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

### Frequently Asked Questions

#### `FAQ#1:` Why dont we use tabs identation instead of spaces ?

> - While tabs are a valid choice, they can lead to inconsistencies in how code appears.
> - Tab are viewed differently in editors with different tab width settings.
> - Might confuse project collaborators and reduce team work performance.

#### `FAQ#2:` Why do we use identation of 2 spaces or 8 spaces ?
>
> - Enhance code readability, while balancing with the compactness.
> - 8 spaces might be good but most of the codes are simple and small.

#### `FAQ#3:` Why do we use limited code limit ?
>
> - Excessive nesting can lead to complex and convoluted logic that is hard to understand.
> - Reduce the testing and maintain code, improve bug tracking time.

#### `FAQ#4:` What if a code exceeds the nested limit ?
>
> - You might considering refactor the code for providing better context:
>   - Early Returns.
>   - Guard Clauses.
>   - Ternary Operators.
>   - Defining extra variables.
>   - Switch statements
>   - Inverted if.

#### `FAQ#5:` Why use such a high character limit?
>
> - Facilitates readable variables, fostering expressiveness.
> - Averts deeply nested structures with longer lines.
> - Minimizes vertical scrolling, enhancing code visibility.

#### `FAQ#6:` Why not use unlimited character limit?
>
> - Restricts to 120 to avoid eye strain from smaller text or excessively wide code.

- **Variable Naming Max Limit: `18`** - Enhances readability with contextual variables.

#### `FAQ#7:` Why use such a high nested limit?
>
> - Enables variables to provide meaningful context.
> - Reduces abbreviations and misuse of variables.
> - Allows functions or code structures to be self-explanatory.

#### `FAQ#8:` Why not use a higher nested limit?
>
> - Eases code review and collaboration by reducing time spent on variable names.
> - While readability is desirable, it shouldn't be overly verbose to improve conciseness.
> - Typing might be an issue as longer names increase development cost.

#### `FAQ#9:` Why use such a small line limit?
>
> - Promotes modularity and single responsibility.
> - Shorter lines of code enhance readability.

#### `FAQ#10:` Why to have different line limits?
>
> - Avoids overly fragmented code by not using functions that are too small.
> - Prevents an increase in maintenance costs from numerous functions with simple lines.
