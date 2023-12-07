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

---
---
---
---
---

## A. The meaning of the project standard

C++ serves as a primary programming language for numerous open-source projects, including our pixel game **Cross Da Road**. However, known for its extensive features, C++ introduces extensive features that require a good understanding of various concepts. Without careful consideration, features can be misused by developers, potentially turning beneficial aspects into bug-prone, making it harder to maintain.

---

### A.1 - Why coding standards matter ?

Coding standards are rules for writing code that help developers work together better. These rules make sure everyone uses the same style when writing code, which makes it easier for everyone to read and understand. Those challengs should be outlined in the dos and don'ts of writing C++ code, helping manage complexity and enhance productivity.

---

### A.2 - Benefits of coding standards ?

When there are clear coding standards, developers don't waste time arguing about how to write code – they can focus on getting work done efficiently. These standards also make the codebase better in the long run because it's easier to maintain. As a game project grows, these rules help the code adapt and scale properly. They're also like a guide for new developers, making it quick and easy for them to understand the project.

---
---
---
---
---

## B. The goals of the project standard

The project standard has specific goals to provide a clear framework and guidelines for developers, ensuring a standardized and efficient approach to coding practices. These goals serve as a foundation for creating rules that are easy to remember, promoting a shared understanding among developers. It focuses on coding conventions, formatting styles without restricting the usage of features.

It's important to note that this guide is not a tutorial for using C++ effectively, but rather a team guideline for better project development, assuming readers already have a basic understanding of the C++ language.

---

### B.1 - Clarity and Memorability

One of the project standard goals is to create rules that are essential and easy for everyone to remember. This ensures that developers can recall and apply the rules effortlessly, promoting a shared understanding of coding practices. While certain code styles might goes out of sync, it should be better.

---

### B.2 - Reader-Friendly

It is a recommendation that the code should be reader-friendly, so less time will be spent on understanding and questioning about it. This means maintaining consistency in the code's style throughout the project, making it easier for others to read and understand, fostering a collaborative and efficient coding environment.

---

### B.3 - Community Consistency

The project standard promotes consistency with the larger C++ community when applicable, aligning with community practices. Encouraging the use of common sense, it suggests following community rules and seeking help when things are unclear. By doing so, developers contribute to a broader coding culture and leverage widely accepted conventions. This promotes a pragmatic and collaborative coding environment, fostering a culture of shared knowledge and continuous improvement.

---

### B.4 - Module Reliability

To maintain code quality, the standard warns against using surprising or dangerous code and advises steering clear of tricky or hard-to-understand parts. This ensures that the codebase remains safe, comprehensible, and conducive to long-term development. When something surprising or unusual is happening in a snippet of code (pointers, or rarely used features), leaving contextual hints and references for the readers.

---

### B.5 - Big-Picture Perspective

The guide emphasizes the importance of considering the big picture of the project's production. It empowers developers to improve aspects of the project when needed, promoting a forward-thinking and adaptive approach to coding practices.

---
---
---
---
---

## Project Guidance

- **IMPORTANT:** All code must follow `./docs/standard/*.md`
- Do not use nested ternary operators, considering `if` statements and `switch case` instead.
- Specialized numbers that are related should be converted into Descripted Enum Values.
- Store magic numbers in `gConst.h` (for core framework) and `uAppConst.h` (for application).
- Try to use `const` and `constexpr` variables if possible, except for customization.
- Using const functions whenever it is possible, excepts for **Setters**

> Warning: Pointers might change the data but can use keyword `const`.
