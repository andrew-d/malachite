# Ideas

## Overview

- VM written in ANSI C
  - Pluggable memory allocator, for portability
  - Core library should only use standard ANSI C
- Can split into:
  - core  : basic VM, compile/run code, no external libraries (not even fopen/etc.)
            should be able to e.g. run in the windows kernel, embedded, anywhere
  - std   : standard library, written in ANSI C / Malachite, mostly for basic stuff like
            file I/O, networking, OS services, etc (should only use POSIX)
  - extra : platform-specific stuff, can include bindings to libuv (for example)

- Should be more functional - like Ruby - but have Python's nice(er) object model
- Operator overloading, e.g. "def +(one, two)", or the reverse version (a la \_\_radd\_\_), "def \\+(one, two)"
  - Not sold on the reverse syntax
  - Allow any function that takes two arguments to be called infix like Haskell?
- (probably) implicit "self"
  - how to specify static methods?
- Easy packaging
  - Package manager
  - Ability to distribute entire application as single-file
    - Have a pluggable 'require()' or 'import' feature, so we can package all dependencies
      up in, e.g. a ZIP archive, or concatenated together, etc., and then have the
      custom loader just run from there
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
    - Slice (this is useful to prevent copying)
- C API necessary
  - FFI too - use libffi (maybe as part of std?)
- Having something like Python's generators or Lua's coroutines would be nice
- Blocks / non-crippled lambdas a necessity
  - Syntactic sugar for last argument being a block/lambda, like Ruby/Rust?
- Classes
  - Interfaces or traits - possibly sugar for duck-typing?
  - First-class interfaces?
