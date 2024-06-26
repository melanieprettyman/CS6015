
# Scripting Language

MSD-Script is a custom scripting language designed to explore and experiment with language design and parser implementation. It features expression parsing, variable management, and supports essential programming constructs such as conditionals, functions, and arithmetic operations.





## Features 
**Expression Evaluation:** Directly interpret expressions input through the console.

**Variable Binding:** Utilize **_let** expressions to bind values to variables.

**Function Definitions and Calls:** Define and use functions with the **_fun** keyword.

**Control Structures:** Implement conditional logic with **_if**, **_then**, and **_else**.









## Setup and Installation

Clone the repository and compile project with make file. 
Run the shell:
`./msd-script`

## Usage
You can pass different commands to the program to control its behavior:
- **`--test`:** Run all predefined tests.
- **`--interp`:** Evaluate expressions directly.
- **`--print`:** Print the parsed expressions.
- **`--pretty-print`:** Pretty print the expressions for easier reading.

For example, to interpret an expression, you can use:
```
_let factrl = _fun (factrl)
                _fun (x)
                  _if x == 1
                  _then 1
                  _else x * factrl(factrl)(x + -1)
_in factrl(factrl)(10)
```
returns `3628800`


