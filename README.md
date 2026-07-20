The following is tested on Ubuntu 24.04 LTS.

# Quickstart:
Clone the repository and navigate to it:
``` 
    git clone https://github.com/LeilaDubow/protobuf-workshop
    cd protobuf-workshop
```
## Prerequisites: protobuf
An easy way is to install via pip (Python package manager).

You will need pip installed:
```
	sudo apt update
	sudo apt install python3-pip python3.12-venv
```

First create a virtual environment:
```
	python3 -m venv .venv
```
To activate it:
```
	source .venv/bin/activate
```

Then download the required packages:
```
	pip3 install protobuf grpcio-tools 
    sudo apt install protobuf-compiler
```

## Prerequisites: build tools
```
    sudo apt install cmake gcc-arm-none-eabi
```

## How to run example

Initialise the submodules:
```
    git submodule update --init --recursive
```
In order to generate the protobuf code & headers, make sure the virtual environment is activated.
Then, make the script executable (if not already) and run it:
```
	chmod +x generate_protos.sh
	./generate_protos.sh
```
The protobuf code only needs to be rebuild when the protobuf definitions are changed.

To build:
```
    mkdir build
    cd build
    cmake ..
    make
```

Then, connect the RP2040 to your computer. 
Hold the boot and reset buttons both for around one second, release the reset button, and approximately one second later release the boot button.
This should mount the device (it should be visible in your file system).

You can then drag the Protobuf.uf2 found in the build directory there.

The device should no longer be mounted.

```
    sudo cat /dev/ttyACMx
```
or 
``` 
    sudo screen /dev/ttyACMx
```
(this will typically be /dev/ttyACM0).

> Note: if you are using WSL, a virtual machine, docker etc. to access Linux, you probably won't be able to access this file without extra configuration. A simple workaround for this example is to just read the outputs using your host machine, e.g. with PuTTY on Windows, and copy in the data that we want to use later.
> However, there are typically ways to give Linux access to this device. For example:
>* If you are using docker, you can add the --device=/dev/ttyACMx flag.
>* If you are using a virtual machine, look up device passthrough.


The output should show the encoded message written in hexadecimal.

```
9 bytes written: 0801 1500 00b0 4018 36
```

The output can be redirected into a file as follows:
```
    sudo cat /dev/ttyACMx > output.txt
```

# CLI encoding and decoding with proto-c
Make sure xxd is installed:
```
    sudo apt install xxd
```
and that you are in the protobuf-workshop directory. 
e.g.
```
	cd ..
```
or 
```
	cd /path/to/protobuf-workshop
```

## Decoding example
We can verify whether the output is correct by decoding it again to recover the initial message:
```
	echo "0801 1500 00b0 4018 36" > encoded_hexdump 
	xxd -r -p encoded_hexdump > encoded_bin
	protoc < encoded_bin --decode=Message lib/protos/message.proto

```
should output 
```
	val1: 1
	val2: 5.5
	val3: 54
```
which was our original message.

## Encoding example
We can also check how we expect our messages to be encoded:

```
	echo "val1 : 1, val2 : 5.5, val3 : 54" > cli_message
	protoc --encode=Message lib/protos/message.proto < cli_message > encoded.bin
	xxd encoded.bin
```
should output the original hexadecimal.

