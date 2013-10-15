# Ideas

## Overview

- VM written in ANSI C
  - Pluggable memory allocator, for portability
  - Core library should only use standard ANSI C
  - "Extra" library can include platform-specific stuff
  - Need a sane threading model
  - If willing to sacrifice portability, can make like Julia and use LLVM

- Should be more functional - like Ruby - but have Python's nice(er) object model
- Operator overloading, e.g. "def +(one, two)", or the reverse version (a la \_\_radd\_\_), "def \\+(one, two)"
  - Not sold on the reverse syntax
  - Allow any function that takes two arguments to be called infix like Haskell?
- (probably) implicit "self"
- Easy packaging
  - Package manager
  - Distribute entire application as single-file?
  - Compile to C, like Luac?
- Types:
  - Integer
  - Floating-point
  - String
    - Immutable or mutable?
    - Internal representation undefined
    - Consist of Unicode codepoints
    - Indexing probably not O(1), can amortize with a skiplist
    - Need to encode to binary before doing byte-level operations
  - Binary data
  - Data structures:
    - List
    - Hash / dict
    - Set
    - Maybe array (not linked list)
  - Enum (a.k.a. symbol?)
  - Maybe:
    - Range
    - Slice
- FFI necessary - use libffi
  - C API too
- Having something like Python's generators or Lua's coroutines would be nice
- Blocks / non-crippled lambdas a necessity
  - Syntactic sugar for last argument being a block/lambda, like Ruby/Rust?
- Classes
  - Interfaces or traits - possibly sugar for duck-typing?
- First-class interfaces
