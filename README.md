# same5x-dev
Firmware development template for ATSAME5x microcontrollers from Atmel

### Supported Devices
- ATSAME5x
- ATSAMD5x (untested)

### Instructions

clone the repo (recomended you fork the repo to your account first)
```
git clone https://github.com/pepetech/same5x-dev
```

open code on the software directory

```
cd code same5x-dev/software

```

The binaries will be located at `bin/APP_NAME.bin` and `bin/APP_NAME.elf`.

if you're taking advantage of code you can use these shortcuts:
```
Ctrl + Shift + B (Build task)
```
```
F5 (Start Debugging)
```

Otherwise you can
```
make (Build)
```
```
make clean (Clean)
```

### Dependencies

This project requires libopencm3 to be installed system-wide. I will only be able
to provide techincal support for Archlinux.

  - editor: [code](https://www.archlinux.org/packages/community/x86_64/code/)
  - Compiler: [arm-none-eabi-gcc](https://www.archlinux.org/packages/community/x86_64/arm-none-eabi-gcc/)
  - armmem: [armmem](https://github.com/vankxr/armmem)

#### Extensions

These extension help with development.

  - C/C++ IntelliSesnse 
  - Cortex-Debug

## Authors

* **Rafael Silva** - :portugal: - *initial work*- [gimbas](https://github.com/gimbas)

See also the list of [contributors](https://github.com/gimbas/nixie_clock/graphs/contributors) who participated in this project.

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
This software is licensed under MIT.