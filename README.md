# PurpleMesa
A VHDL parser based on flex and bison

## Goals
The reason PurpleMesa got started is to fill the need for a VHDL parser written in C++ that provides access to the underlying AST structure. This in itself may not seem as exciting as a simulation or synthesis tool, but it allows for various transformations, analyses and exports to be carried out that enable various exciting applications such as:
* Formal verification
* Equivalence testing
* VHDL analysis
* Code linting
* Editor code highlighting
* VHDL to verilog translation
The initial goal is to make a standalone parser that is independent of any particular application. This is meant to make sure that PurpleMesa can serve as an independent parser. The first application will be **formal verification**, more details are provided below.

## Contact and current status
If you have comments or questions, feel free to reach out to me at PurpleMesaProject@gmail.com. As of now, the basic structure of PurpleMesa is being worked on, so the parser is **not** functional. A description of current challenges can be found below.
