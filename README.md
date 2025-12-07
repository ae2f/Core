# ae2f::Core
```
             ____   __     ____               
   __ _  ___|___ \ / _| _ / ___|___  _ __ ___ 
  / _` |/ _ \ __) | |(_|_) |   / _ \| '__/ _ \
 | (_| |  __// __/|  _| _| |__| (_) | | |  __/
  \__,_|\___|_____|_|(_|_)\____\___/|_|  \___|

```

- Rel-v6.25.19

> This project has been migrated to [codeberg.org](https://codeberg.org/ae2f/Core).  
> You will still be able to access to upstream with github page.

> CMake-generated-headerset which guarantees the same method to work on C/C++, regardless of versions.  
> Works under standard C/C++

# Dependency
[![ae2f-workflow](https://github.com/ae2f/Core/actions/workflows/test-default.yml/badge.svg?branch=main)](https://github.com/ae2f/Core/actions/workflows/test-default.yml)
- cmake     >= 3.10
- C         >= 90
- C++       >= 98

# CMake Ctl Variables
- ae2f_Core_N_RELOAD_ALWAYS
    > always auto-regenerate the header on configure step when set to `OFF`

- ae2f_float
    > the custom type for floating type for this.
