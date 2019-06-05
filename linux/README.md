# ldd3-examples
Linux Device Driver examples updated and based upon https://lwn.net/Kernel/LDD3/

## YCM & Other Completion Tools

Since YCM and some other tools rely on the clang `compile_commands.json` that usually is fed by CMake, and we don't care about protablility or CMake since this is for the Linux kernel, we can generate the JSON file to aid in development of kernel code (e.g. parse kernel headers and have proper flags) by using [Bear](https://github.com/rizsotto/Bear): install `bear` and then run `$ bear make` to generate a `compile_commands.json` from the make process.
