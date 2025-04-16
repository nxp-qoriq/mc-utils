# Management Complex Utils

The Management Complex (MC) is a key component of DPAA2 (Data Path
Acceleration Architecture, second version).  
MC runs an NXP-supplied firmware image that abstracts and simplifies the
allocation and configuration of the other hardware elements using DPAA2
“objects”.  
These objects provide familiar services such as the core of network
interfaces, switching services, access to accelerators, etc.

## Management Complex API

In the *api* folder one can find the MC APIs for specific releases of
the Management Complex.  
Apart from the API functions provided in the
header files *fsl_.h*, this repository also containes the library that
implements the serialization and deserialization of the command
structure to be passed to the MC.

## Management Complex Configuration

The *config* folder holds the source files for the 2 configuration files
needed by the MC:
 * DPC: Data Path Control (DPC) file, a dtb format file.
 * DPL: Data Path Layout (DPL) file, a dtb format file.

In order to compile the source files into the *dtb* format, one will need
the *device-tree-compiler (dtc)* installed on their system. Afterwards,
the following command can be run:

```bash
[~/mc-utils] $ make -C config/
```

## Build Options

The `Makefile` supports two customizations:

- `DTC`: Specify the path to the Device Tree Compiler (DTC).
- `SOURCES`: Provide an external set of Device Tree Source (DTS) files,
  which should be space-separated.

For instance, to build with a specific DTC path and external DTS files, you can run:

```bash
[~/mc-utils] $ make DTC=/dev/br_build/host/bin/dtc SOURCES="path1/file1.dts path2/file2.dts" -C config/
```

In this example, the `make` command is used to specify the path to the DTC and include
additional DTS files from the specified paths.
