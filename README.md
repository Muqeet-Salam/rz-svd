# Rizin SVD Parser (rz-svd)

The System View Description (SVD) files are XML-based configuration files used primarily in microcontroller development. They provide a standardized, machine-readable description of a microcontroller's peripheral registers, bit fields, and memory map, defined by the chip manufacturer.

This repository implements a generic parser to structures which Rizin uses to enrich the disassembly output.

The SVD files are stored under the `svd/` folder.

The repository holds a copy of `yxml`, owned by `Yoran Heling` under `MIT` license.
