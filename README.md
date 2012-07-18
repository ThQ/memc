**Memc** is a compiler for Mem (a programming language).


# Mem

* Compiled
* Imperative
* Static typing
* Low level (in a C++ sense)

# Examples
## *Hello, World !*

    use io
    
    main ()
        io.print("Hello, World !")

## Factorial
    fact (n :int) -> int
        if n == 0i
            return 1i
        else
            return n * fact(n - 1i)
    
    main (argc :int) -> int
        return fact(10)


# Dependencies

* Lex (tokenizer)
* Yacc (parser)
* LLVM (used to compile to native code)
* Python (for some utils)

## Optional
* Automake
