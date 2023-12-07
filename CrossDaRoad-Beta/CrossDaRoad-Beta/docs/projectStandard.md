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

When there are clear coding standards, developers don't waste time arguing about how to write code – they can focus on getting work done efficiently. These standards also make the codebase better in the long run because it's easier to maintain. As a game project grows, these rules help the code adapt and scale properly, making it quick and easy for developers to understand the project.

---
---
---
---
---

## B. The goals of the project standard

The project standard has specific goals to provide a clear framework and guidelines for developers, ensuring a standardized and efficient approach to coding practices. These goals serve as a foundation for creating rules that are easy to remember, promoting a shared understanding of coding conventions among developers without restricting the usage of features. It's important to note that this guide is not a tutorial for using C++ effectively, but rather a team guideline for better project development, assuming readers already have a basic understanding of the C++ language.

---

### B.1 - Coherence Memorizing

One of the project standard goals is to create rules that are essential and easy for everyone to remember. This ensures that developers can recall and apply the rules effortlessly, promoting a shared understanding of coding practices. While certain code styles might goes out of sync (read Project Vision), it should be noted that periodic reviews and updates to the coding standards are encouraged.

---

### B.2 - Reader-Friendly

It's a good idea to make your code easy to read so people don't have to spend a lot of time trying to understand it. This involves keeping the style of your code the same across the whole project, making it simpler for others to read and understand. However, it's important not to stick to an old style just for the sake of consistency; you should also consider the benefits of newer styles and how the code might naturally move towards them over time.

---

### B.3 - Community Consistency

The project standard encourages alignment with the broader C++ community, emphasizing consistency with community practices. It advises using common sense, following community rules, and seeking help when needed. This approach fosters a collaborative coding environment, contributing to a shared knowledge culture and continuous improvement.

---

### B.4 - Module Reliability

To maintain code quality, the standard warns against using surprising or dangerous code and advises steering clear of tricky or hard-to-understand parts. This ensures that the codebase remains safe, comprehensible, and conducive to long-term development. When something surprising or unusual is happening in a snippet of code (pointers, or rarely used features), leaving contextual hints and references for the readers.

---

### B.5 - Project Vision

The guide empowers developers to adopt a forward-thinking and adaptive approach to coding practices by emphasizing the importance of considering the big picture of the project's production and encouraging improvements as needed. Performance optimizations can sometimes be necessary and appropriate, even when they conflict with the other principles of this document. Certain simple functions might require effective error handling and a comprehensive logging mechanism to ensure robustness, even if they necessitate trade-offs with performance and code modularity.

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
