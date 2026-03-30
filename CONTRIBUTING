While I will likely only be working on this myself, it is still good to follow these rules.<br>
Also, if you are reading this and you are not me;
1. I am so sorry that you have to work with my code
2. I will try my best to follow these rules, and I expect you to do the same (though slight slip up are inevitable)

# Git Rules
## Branch Naming
To keep things organized, use prefix followed by a short description of the branch's purpose. Use hyphens to separate words.
|**Prefix**|**Purpose**|**Example**|
|----------|-----------|-----------|
|`feat/`|A new feature or addition|`feature/item-function`|
|`fix/`|A buf fix|`fix/error-fixed`|
|`docs/`|Documentation changes|`docs/update-readme`|
|`refactor/`|Code changes that neither fix a bug, not add a feature|`refactor/api-logic`|

## Commit Messages
To quickly be ablt to see what a commit has done, commit messages should be short and concise.<br>
Messages should also contain a prefix telling you what type of changes were made.

**The Format**<br>
`type: description`
- **Type**: Use the prefix from the [branch naming section](#Branch-Naming).
- **Description**: Start with a lowercase letter, and use the imperative mood (e.g., "add" instead of "added"), and do not end with a period.

**Examples**<br>
- `feat: add display print`
- `fix: resolve dangling pointer`
- `docs: clarify installation steps`
- `refactor: simplify database connection string`


## Basic Workflow
1. **Main should not be touched**: NEVER commit directly to the `main` branch.
2. **Tiny commits**: Commits should be small. If you can't figure out how to write a commit message the is short and concise your commit is too long.
3. **Sync often**: Pull the latest changes before starting a new branch to avoid merge conflicts


# Code Conventions
## Naming Conventions
|**Entity**|**Case**|**Example**|
|----------|--------|-----------|
|**Classes/Structs**|`PascalCase`|`class DisplayMargins`|
|**Methods/Functions**|`camelCase`|`void getItems()`|
|**Local Variables**|`camelCase`|`int foo`|
|**Private Members**|`m` prefix|`int mSpeed`|
|**Constants/Macros**|`UPPERCASE`|`#define SCREEN_WIDTH`|
|**Namespaces**|`lowercase`|`namespace display`|
|**Files**|`snake_case`|`display_margins.cpp`|


## Code structure
### Functions
- **Function size**: Functions should not exceed 60 lines. If it's longer it will become a pain to refactor. You should instead split up the function into multiple smaller functions and one "main" function where all these functions come together.
- **Early returns**: If possible, exit functions early. This will prevent `if-else` nesting. Keep the "happy path" as much to the left as possible.

### Modern C++ Safety
- **Prefer `nullptr`**: Never use `NULL` or `0` for pointers, as this may cause crashes later down the road.
- **Use of `auto`**: Use `auto` only when the type is obvious (e.g., iterators or `new` allocations) to keep the code clean, but don't overdo it, as this will lower the readability.
- **Brace initialization**: Use `{}` for initialization so that the compiler know exactly which type to expect, and narrows convertions.
- **Header guards**: Every header file must have `#ifndef FILE_NAME_H`. This code is written for hardware interfacing, and `#pragma once` may not always be recognized by the compiler.
- **Devining ints**: Since this is for hardware, you should specify how long they should be, as not all hardware uses the same size for integers. Instead, you should prefer types like `uint8_t`, `uint16_t` and `uint32_t`.

### Comments
When writing code, it should almost not need comments. This is done by for example; not using magic numbers, and exiting a function early. If you do have to write comments, please follow these conventions.

- Use `//` for single-line logic explanations or inline comments
- Use `/* ... */` for multi-line comments for a more detailed explanation.
- Use `/** ... */` for Doxygen comments. These are comments explaining in detail what a function does, so that when I want to use a function my IDE/text editor tells me what they do.

Here are some Doxygen tags that should be used when writing a class/function description:
|**Tag Name**|**Format**|**Description**|
|------------|----------|---------------|
|`@brief`|n/a|A one-sentance summary|
|`@param`|`@param <name> <description>`|Describes an input|
|`@return`|`@return <description>`|Describes what the function returns|
|`@note`|n/a|Adds a highlighted note|
|`@tparam`|`@tparam <type> <description>`|Used for template parameters|