# `llvm_c_2`

This is my own attempt to create a C frontend to match the C++ API of llvm as close as reasonable.

Currently targeting `llvm-13`

Some notable features include:

- Any functions taking in a string take a pointer and a length.
- Match the file structure of LLVM
- All types and functions begin with `llvm_`
- All all methods are formatted as `llvm_<TypeName>_<methodName>_<maybe override specifier>`
- All enum variants start with their name
  <br/>ie. This means if an enum is named `llvm_Foo` and has the variants `Bar` and `Baz`, they will be named `llvm_Foo_Bar` and `llvm_Foo_Baz` respectively.

## Building

Building requires [deno](https://deno.land) as I am using my own _incomplete_ 'meta' build system: `rnn`, written in typescript.

Once deno is installed, all you need to do is run:

```sh
./rnn.ts build
```

This will create a folder `build` where you will find the static library.

### Note

Building has only been tested on linux.

## Contributing

Not everything is currently exposed. I'm only exposing specific APIs as I need them. Please feel free to contribute to add more.

For a loose list of what is exposed look at the file structure. Of course, not every function/method is exposed for every type.

## License

The `llvm_c_2` is licensed under the MIT license.
