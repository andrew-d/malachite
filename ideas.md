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
  - Can be like python - everything is an object, callables are things with `__call_`
  - Ruby is more like: everything's an object, can send 'messages' to objects
- Elixir does something cool where all the control flow operators are like this:
    if condition do
      true
    else
      false
    end
  And this desugars to:
    if(condition, do={block}, else={block})
  So, you can define arbitrary control-flow structures in the same way.
  - See for more info about homoiconicity:
    - http://craftsmanship.sv.cmu.edu/posts/lispy-elixir
    - http://blog.pluralsight.com/elixir-is-for-programmers ("multi-block control flow")
      - and linked: https://github.com/elixir-lang/elixir/blob/c572cb80fced4111ea98ed4a0e27550e09816f66/lib/elixir/lib/kernel.ex#L2526
    - http://www.erlang.org/doc/apps/erts/absform.html
- Operator overloading, e.g. "def +(one, two)", or the reverse version (a la \_\_radd\_\_), "def \\+(one, two)"
  - Not sold on the reverse syntax
  - Can have it such that for 'a + b', will first try `a.+(b)`, and then b.+(a)
  - Allow any function that takes two arguments to be called infix like Haskell (with backticks)?
- (probably) implicit "self"
  - how to specify static methods?
  - static / non-static can be done with macros?
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
  - Lua's coroutines are kind of cool:
    - function calls track stack without the C stack
    - when doing a coroutine.resume(), recursively call the interpreter with the
      new coroutine
    - when doing a coroutine.yield(), return from the (recursive) interpreter call,
      which will then resume the previous coroutine
    - remaining question: how does this save the state of the (now-yielded) coroutine?
    - LuaJIT has a fully resumable VM which means that it can support yielding across C calls, too
  - Need to think about interoperability between coroutines and exceptions (they're
    technically two sides of the same coin, but having a try/finally block with a yield
    in the middle could result in funky things)
- Blocks / non-crippled lambdas a necessity
  - Syntactic sugar for last argument being a block/lambda, like Ruby/Rust?
- Classes
  - Interfaces or traits - possibly sugar for duck-typing?
  - First-class interfaces?
- Concurrency thoughts:
  - VM uses no globals
    - Pass state around, can borrow from mitsuhiko's Arana and have special defines
      that expand to the required state variables, e.g.:
          void do_something(MCH_STATE, int other, char arg, void* here) {
              /* ... */
              other_function(MCH_STATE_FWD, ...)
          }
  - Single execution context not thread safe
  - TODO:
    - Multiple execution contexts in a single VM?
      - If the execution context is a single object, a single host program could run
        multiple execution contexts...
    - Cooperative multithreading?
    - Language-level support for sending values between VMs?
    - More?

- See mitsuhiko's `arana` for more info on this kind of thing:
  https://bitbucket.org/mitsuhiko/arana-main/src/

- For macros / homoiconicity:
  - Language can be a collection of 'everything involves message sending', and thus all
    expressions can be in the form [:message, target, [args]]
    For example:
        foo.bar(1, 2, 3, 'baz')
    Means:
        1) Send message '.' with args (:bar) to foo
        2) Send message 'call' to the result of (1) with args [1, 2, 3, 'baz']
    Can be decomposed as:
        [ :call,
          [:., :foo, [:bar]],
          [[1, 2, 3, 'baz'], []]
        ]

    Others:
      if 1 == 2 do
        3
      else
        4
      end

      [:call,
       :if,
       [
        [[:==, Kernel, [1, 2]]],
        [[:do, 3], [:else, 4]]
       ]
      ]

  Note that this implies a couple things:
    - Lots of lists
    - Calls must take two arguments, a list of positional, and a list of keyword args
    - Parsing / codegen will probably be slow, due to the ridiculous depth of the parse tree
    - Need a "Kernel" module for basic stuff like operators (since, if we want operators to
      be functional from both sides, we need can't just send :== to a.  e.g.: a == b should
      call :== on a and b...)
    - Everything is an expression, can have a "block" type?
    - Could add a "tuple" type (like Python) which is immutable, to speed up the AST
      - Arena allocator for an entire tree, too?
- GC
  - Pluggable would be nice
  - If so, need at least the following:
      gc_init(...)
      gc_run()
      gc_read_barrier(object)
      gc_write_barrier(object)
      gc_alloc(size)
  - Plus some methods for finding roots, and traversing an object.
  - To find roots, one of:
    - `gc_run` calls something like `find_roots` to get all roots
    - Host code is responsible for maintaining set of root objects and calling
      `gc_add_root` and `gc_remove_root` for each root
    - Host code can maintain contiguous array of roots, pass to GC when necessary
  - To traverse, one of:
    - Callback in object header
    - GC has one callback to host, pass object and 2nd callback for adding new object
    - Provide GC with map between object type and traversal function
      - I like this one the best, since it shouldn't be necessary to define a new
        object type at runtime
      - Can be done pre-include with a macro, too
  - Lots of info on GCs here:
    - http://rubini.us/2013/06/22/concurrent-garbage-collection/



# Explicit Goals
- Reasonably simple VM (somewhere in the range of 20 - 30k lines of C would be nice)
  - Should be able to conditionally compile out parts of it
    - e.g. building a VM with no lexer/parser/compiler
- Embeddable, with a simple and usable C API
  - Also implies portability - only written in ANSI C
  - Should not use even certain POSIX APIs in the core VM (e.g. for Windows kernel stuff)
  - Implies needing a pluggable memory allocator
  - Implies needing a pluggable require() implementation
  - Should be the same as Lua, where the C API doesn't leak the state of the VM - this
    prevents a whole class of bugs like Python/Ruby have, e.g. with reference counting,
    and allows further optimizations of the garbage collector
  - Should be able to turn off floating point numbers?
- More expressive than Lua
  - Lists, dicts distinct
  - Integer/floating point and string/byte distinction
  - Ruby-esque symbols (aka. atoms)
  - Classes should be present in language (might be a library thing, though)
  - Blocks (can be syntactic sugar for calling a function with a function as the
    last argument)
- Garbage collected

# Other Goals
- Better object model than Lua
  - "Everything is an object" like Python?
- Modern:
  - More functional than Python - closer to Ruby
  - 0-based indexing
  - Support for metaprogramming, if possible
  - Much as I'm not a fan: optimize to some degree for DSLs, e.g. allowing calling
    a function with a single argument with no brackets, etc.
    NOTE: could combine this with the block syntactic sugar to allow calling a function
          with one argument + a block argument with no parens too...
- Good support for concurrency
  - VM code should be thread-safe - i.e. no use of globals
  - A single VM does not need to be thread-safe (i.e. it will not be possible to run
    multiple threads in a single VM at a time)
