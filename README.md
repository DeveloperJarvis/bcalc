# bcalc - A Simple Command-Line Calculator

`bcalc` is a basic command-line calculator written in C that supports basic arithmetic operations: addition, subtraction, multiplication, and division. It uses recursive descent parsing to evaluate mathematical expressions, handling operator precedence and parentheses.

## Features

- **Supports Basic Arithmetic**: Addition, subtraction, multiplication, and division.
- **Parentheses**: Supports grouping of expressions using parentheses `()` to control operator precedence.
- **Interactive Mode**: Continuously evaluates expressions entered by the user until the program is exited.
- **Command-Line Options**:

  - `-h` or `--help`: Display help information.
  - `-v` or `--version`: Display the version of the calculator.
  - `-q` or `--quiet`: Suppress the initial banner and version output.
  - `-l` or `--mathlib`: (Currently a placeholder) Intended for enabling math library routines.

## Installation

To compile and run `bcalc`, follow these steps:

1. **Clone the repository**:

   ```bash
   git clone https://github.com/DeveloperJarvis/bcalc.git
   cd bcalc
   ```

2. **Compile the program**:
   You can compile `bcalc` using `gcc` (or any C compiler):

   ```bash
   gcc -o bcalc bcalc.c
   ```

3. **Run the calculator**:
   After compilation, run the `bcalc` program:

   ```bash
   ./bcalc
   ```

4. **Use command-line options**:

   - To get help:

     ```bash
     ./bcalc -h
     ```

   - To see the version:

     ```bash
     ./bcalc -v
     ```

   - To run in quiet mode (no banner):

     ```bash
     ./bcalc -q
     ```

   - To enable math library (future functionality):

     ```bash
     ./bcalc -l
     ```

## Usage

Once the program is running, you can enter mathematical expressions directly into the terminal. The program will evaluate and print the result.

### Example 1: Basic Arithmetic

```bash
$ ./bcalc
3 + 5 * (2 - 8)
-13
```

### Example 2: Division

```bash
$ ./bcalc
10 / 2
5
```

### Example 3: Parentheses

```bash
$ ./bcalc
(3 + 2) * (4 - 1)
15
```

## How It Works

1. **Tokenizer**: The program first tokenizes the input string. This process breaks the input down into smaller components (tokens) like numbers, operators, and parentheses.
2. **Parser**: Using recursive descent parsing, the program processes the tokens based on their precedence (multiplication/division before addition/subtraction).
3. **Evaluation**: Once the tokens are parsed into an expression tree, the result is calculated and displayed.

## Error Handling

The program includes basic error handling:

- **Mismatched parentheses** will result in an error message and exit.
- **Division by zero** will trigger an error message and terminate the program.
- **Invalid tokens** will lead to an error message indicating the unexpected character or token.

## Planned Features

- **Math Library**: The `-l` (or `--mathlib`) option is currently a placeholder. In the future, it could be used to enable advanced mathematical functions like square roots, trigonometry, etc.
- **Improved Error Handling**: The program could provide more detailed error messages to help users debug input issues.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
