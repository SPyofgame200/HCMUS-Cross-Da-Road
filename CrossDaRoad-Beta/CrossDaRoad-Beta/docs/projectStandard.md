# Project Standard

---
---
---
---
---

## Table of Contents

- [Project Standard](#project-standard)
  - [Table of Contents](#table-of-contents)
  - [The meaning of the project standard](#the-meaning-of-the-project-standard)
  - [The goals of the project standard](#the-goals-of-the-project-standard)
    - [Rule Clarity and Memorability](#rule-clarity-and-memorability)
    - [Reader-Friendly Code](#reader-friendly-code)
    - [Community Consistency](#community-consistency)
    - [Safe and Understandable Code](#safe-and-understandable-code)
    - [Big-Picture Perspective](#big-picture-perspective)
    - [Common-Sense Application](#common-sense-application)
  - [Project Guidance](#project-guidance)

## The meaning of the project standard

Coding standards are rules for writing code that help developers work together better. These rules make sure everyone uses the same style when writing code, which makes it easier for everyone to read and understand.

When there are clear coding standards, developers don't waste time arguing about how to write code – they can focus on getting work done efficiently. These standards also make the codebase better in the long run because it's easier to maintain. As a game project grows, these rules help the code adapt and scale properly. They're also like a guide for new developers, making it quick and easy for them to understand the project.

---
---
---
---
---

## The goals of the project standard

The project standard has specific goals to provide a clear framework and guidelines for developers, ensuring a standardized and efficient approach to coding practices. These goals serve as a foundation for creating rules that are easy to remember, promoting a shared understanding among developers.

---

### Rule Clarity and Memorability

One of the project standard goals is to create rules that are essential and easy for everyone to remember. This ensures that developers can recall and apply the rules effortlessly, promoting a shared understanding of coding practices.

---

### Reader-Friendly Code

Another goal emphasizes writing code that is reader-friendly. This means maintaining consistency in the code's style throughout the project. Consistent code style makes it easier for others to read and understand, fostering a collaborative and efficient coding environment.

---

### Community Consistency

The project standard encourages consistency with the larger C++ community when it makes sense. By aligning with community practices, developers contribute to a broader coding culture and leverage widely accepted conventions.

---

### Safe and Understandable Code

To maintain code quality, the standard warns against using surprising or dangerous code and advises steering clear of tricky or hard-to-understand parts. This ensures that the codebase remains safe, comprehensible, and conducive to long-term development.

---

### Big-Picture Perspective

The guide emphasizes the importance of considering the big picture of the project's production. It empowers developers to improve aspects of the project when needed, promoting a forward-thinking and adaptive approach to coding practices.

---

### Common-Sense Application

Encouraging the use of common sense, the project standard suggests following community rules and seeking help when things are unclear. This promotes a pragmatic and collaborative coding environment, fostering a culture of shared knowledge and continuous improvement.

## Project Guidance

- **IMPORTANT:** All code must follow `./docs/standard/*.md`
- Do not use nested ternary operators, considering `if` statements and `switch case` instead.
- Specialized numbers that are related should be converted into Descripted Enum Values.
- Store magic numbers in `gConst.h` (for core framework) and `uAppConst.h` (for application).
- Try to use `const` and `constexpr` variables if possible, except for customization.
- Using const functions whenever it is possible, excepts for **Setters**

> Warning: Pointers might change the data but can use keyword `const`.
