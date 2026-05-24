# TinyC
TinyC Compiler

A modular compiler pipeline for a subset of the C programming language (tinyC) built using Flex, Bison, and C++ as part of the Compilers Laboratory (CS39003) at Indian Institute of Technology Kharagpur.

This project implements the core phases of a compiler including:

Lexical Analysis
Syntax Parsing
Semantic Analysis
Symbol Table Management
Three Address Code (3AC) Generation

The compiler translates tinyC programs into a machine-independent intermediate representation using quad-based three-address code.

Features
Lexical Analysis
Tokenization of tinyC source programs using Flex
Recognition of:
Keywords
Identifiers
Constants
String literals
Operators and punctuators
Comments
Symbol table generation for lexical tokens
Syntax Parsing
Parsing based on a subset of the ISO/IEC 9899:1999 C specification
Implemented using Bison
Handles:
Expressions
Declarations
Statements
Function definitions
Arrays and pointers
Semantic Analysis
Type checking and compatibility validation
Implicit type conversion routines
Temporary variable generation
Nested symbol table handling for functions and scopes
Intermediate Code Generation
Quad Array based Three Address Code (3AC) generation
Support for:
Arithmetic operations
Relational and logical expressions
Conditional and unconditional jumps
Pointer and array operations
Function calls and returns
Backpatching for control flow handling
Tech Stack
Flex — Lexical Analyzer Generator
Bison — Parser Generator
C++ — Semantic analysis and intermediate code generation
Makefile — Build automation
Project Structure
TinyC3/
│
├── Test_Inputs/              # Sample tinyC test programs
├── TinyC3.l                  # Flex lexer specification
├── TinyC3.y                  # Bison parser specification
├── TinyC3_translator.h       # Data structures and declarations
├── TinyC3_translator.cxx     # Semantic actions and code generation
├── Makefile                  # Build instructions
└── README.md
Compiler Pipeline
tinyC Source Program
        ↓
Lexical Analysis (Flex)
        ↓
Syntax Parsing (Bison)
        ↓
Semantic Analysis
        ↓
Symbol Table Construction
        ↓
Three Address Code Generation
        ↓
Quad Array Representation
Symbol Table Design

The compiler maintains hierarchical symbol tables for:

Global scope
Function scope
Nested block scopes

Each symbol table entry stores:

Name
Type
Initial Value
Size
Offset
Nested Table Pointer
Intermediate Representation

The compiler generates machine-independent Three Address Code (3AC) in quad format.

Example:

a = b + c;

Generated Quad:

t1 = b + c
a = t1

Control flow statements are translated using:

Labels
Conditional jumps
Backpatching
Supported Language Features
Expressions
Arithmetic expressions
Relational expressions
Logical expressions
Unary operations
Assignment expressions
Data Types
int
char
float
void
pointers
arrays
Statements
if-else
while
do-while
for loops
return statements
compound statements
Functions
Function declarations
Function definitions
Parameter handling
Building the Project
Prerequisites

Install:

Flex
Bison
g++
Ubuntu/Debian
sudo apt install flex bison g++
Compile
make
Run
./a.out < Test_Inputs/test1.c
Sample Output

The compiler generates:

Symbol Tables
Quad Array based Intermediate Code

Example output:

L100: t1 = i - 1
L101: i = t1
L102: t2 = i * 4
L103: t3 = a[t2]
L104: if (t3 < v) goto L100
Key Compiler Concepts Implemented
Lexical tokenization
Context-free grammar parsing
Syntax-directed translation
Semantic actions
Type checking
Intermediate code generation
Backpatching
Temporary variable management
Nested symbol tables
