## Equation compiler
This repository aims to provide a small example for Compiler Construction

It may be an equation compiler
___
### Tools required
- lex/flex
- yacc/bison
- a C compiler
___
### The compiler is broken up into phases
- phase 1 uses lex/flex to translate a text stream into tokens
- phase 2 uses yacc/bison to process a token stream and build an AST
- phase 3 adds a symbol table to the AST-building step
- phase 4 walks the AST and outputs MIPS assembly

Each phase has a Makefile and is compiled using `make`
___
### Resources
- [regex101](https://regex101.com)
- [JFLAP](https://www.jflap.org)
- [Flex](https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html)
- [Bison](https://www.gnu.org/software/bison/manual)
- [dinosaur.compilertools.net mirror](https://chaseleif.tech/dinosaur.compilertools.net)

___
