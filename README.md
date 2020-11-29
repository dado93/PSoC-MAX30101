# PSoC DS2438 Library
This repository contains the code required to interface a PSoC 5 LP microcontroller to a MAX30101 sensor. 

### Documentation Status
[![Docs Status](https://travis-ci.com/dado93/PSoC-MAX30101.svg?branch=main)](https://travis-ci.com/dado93/PSoC-MAX30101.svg?branch=main)

Documentation can be found at [https://dado93.github.io/PSoC-MAX30101/](https://dado93.github.io/PSoC-MAX30101/)

## Setup
My current setup for testing purposes is based on a breakout board by SparkFun which mounts the MAX30101: [MAX30101-Photodetector Breakout](https://www.sparkfun.com/products/16474). For the PSoC 5LP, I'm using the [CY8CKIT-059](https://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and) PSoC 5LP prototyping kit.

### Hardware connections
To interface the MAX30101 breakout board to the PSoC 5LP, I'm using a level shifter to shift logical values from 3.3 V to 5V. Pull-up resistors are of 2.2kOhm on the 3.3V side, and of 10kOhm on the 5V side.

## TODO
- The current implementation works with only one DS2438 device on the 1-Wire interface, as the SKIP_ROM commands are issued with read/write transactions. An update is required to make this library work with multiple DS2438 devices connected to the same 1-Wire interface.

## References
[MAX30101 Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX30101.pdf)
[MAX30101 Application Note](https://pdfserv.maximintegrated.com/en/an/AN6409.pdf)