# Huge Real and Any Base Calculator (RealHex)

## Description

`RealHex` is a C++ class designed to represent and manipulate large real numbers in any base (including hexadecimal). This class supports various arithmetic operations, comparisons, and input/output functionalities, making it ideal for advanced mathematical computations and numerical representations in non-decimal bases.

## Features

- Representation of large real numbers in any specified base.
- Arithmetic operations: addition, subtraction, multiplication, division.
- Comparison operations: less than, greater than, equal to, etc.
- Input/Output operations for stream and file handling.
- Increment and decrement operators.
- Support for handling both integer and decimal parts of numbers.
- Capability to handle negative numbers.

## Class Members

### Private Members

- `int base`: The base of the number system.
- `int* Is`: Pointer to the array holding the integer part.
- `int* Ds`: Pointer to the array holding the decimal part.
- `int Size`: Size of the integer part.
- `int dSize`: Size of the decimal part.
- `bool isNeg`: Flag to indicate if the number is negative.
- Various private methods for internal operations.

### Public Members

- Constructors for different initializations.
- Overloaded operators for arithmetic and comparison operations.
- Methods for loading from a file and trimming.
- Friend functions for stream input/output.

## Detailed Documentation

### Constructors

- `RealHex()`: Default constructor.
- `RealHex(int _size, int)`: Parameterized constructor.
- `RealHex(const std::string& str, int)`: Constructor from a string representation.
- `RealHex(const char* str, int)`: Constructor from a C-string representation.
- `RealHex(const RealHex&)`: Copy constructor.
- `RealHex(std::ifstream& rdr, int _base)`: Constructor from an input file stream.

### Operator Overloads

- Arithmetic operators: `+`, `-`, `*`, `/`
- Comparison operators: `>`, `<`, `==`, `!=`, `<=`, `>=`
- Increment and decrement operators: `++`, `--`
- Compound assignment operators: `+=`, `-=`, `*=`, `/=`
- Stream operators: `<<`, `>>`

### Methods

- `Load(std::ifstream& rrd, int)`: Load from a file stream.
- `Trim()`: Trim unnecessary zeros.
- `ABS() const`: Get the absolute value.
- `SplitIntoIntDec(int NOD)`: Split the number into integer and decimal parts.

### Static Methods

- `static RealHex one(int)`: Returns a `RealHex` representing the number one.
- `static RealHex zero(int)`: Returns a `RealHex` representing the number zero.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C++ compiler (e.g., g++, clang++)
- C++ Standard Library

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/RealHex.git
    cd RealHex
    ```

2. Compile the source code:
    ```sh
    g++ -o RealHex main.cpp RealHex.cpp
    ```

### Usage

After compiling the project, you can run the executable:

```sh
./RealHex
