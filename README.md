# PurpleMesa
A VHDL parser based on flex and bison

## Goals
The reason PurpleMesa got started is to fill the need for a VHDL parser written in C++ that provides access to the underlying AST structure. This in itself may not seem as exciting as a simulation or synthesis tool, but it allows for various transformations, analyses and exports to be carried out that enable various exciting applications such as:
* Formal verification
* Equivalence testing
* VHDL to Verilog translation
* VHDL analysis
* Code linting
* Editor code highlighting

The initial goal is to make a standalone parser that is independent of any particular application. This is meant to make sure that PurpleMesa can serve as an independent parser. The first application will be **formal verification**, more details are provided below.

## Contact and current status
If you have comments or questions, feel free to reach out to me at PurpleMesaProject@gmail.com. As of now, the basic structure of PurpleMesa is being worked on, so the parser is **not** functional. A description of current challenges can be found below.

## How to contribute
As of now, the project is in a stage that makes code contributions difficult. The basic structure of PurpleMesa is not stable, so please stay tuned before making any pull requests.
Instead, I'd be very happy to get comments on how to best structure PurpleMesa. So please feel free to reach out if you have experience with parsers and/or VHDL and have comments or suggestions. An outline of what's currently being worked on is provided in the milestones section.

## Formal verification
As a first application, PurpleMesa will be used as independent front-end for Yosys, which is hosted [here](https://github.com/YosysHQ/yosys). Yosys along with [Symbiyosys](https://github.com/YosysHQ/SymbiYosys) enables formal verification under a permissive license. While there is a commercial version available that uses Verific as VHDL front-end, an open VHDL parser is not available. PurpleMesa will be able to fill this gap by parsing VHDL to an AST representation that can then be exported as RTIL which is the internal language format used by Yosys. In addition to formal verification, equivalence testing can also be done with Yosys. This, in turn can then be used to verify successful translation between VHDL and Verilog.

## Milestones
VHDL parsers are fairly complex, so this section tries to break the project down into smaller aspects. The current goal is to generate a parser that works with little emphasis on performance. My expectation is that most applications will be limited by downstream processing rather than the parsing / elaboration done in PurpleMesa. This list may not be complete - if you know of something that's missing please shoot me an email so I can add it here.
### PurpleMesa Kernel
* Design class to manage multiple design files
* Implement STD library
### Design management
* Manage multiple design libraries (STD, WORK + user libraries)
* Do a first parse pass when design files are added to analyze dependencies
* Generate a proper order of analysis for design files in the design
### Parser / AST
* Generate hierarchy table when design is parsed
* Populate a symbol table to tag specific type of identifiers
* Finalize AST structure - continue with visitor pattern to make adding new AST transformation easy or switch to a more generic node type as used in Yosys?
### Elaboration
* Memory extraction
### RTIL export
* Transform AST into RTIL objects
