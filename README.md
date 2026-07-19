# Prerequisites:
## Installing protobuf

An easy way is to install via pip (Python package manager)

First create a virtual environment:
```
	python3 -m venv .venv
```
To activate it:
```
	source ./.venv/bin/activate
```

Then download the required packages
```
	pip3 install protobuf grpcio-tools 
```
# Generating the protobuf code & headers
Make sure the virtual environment is activated.
Make the script executable
```
	chmod +x generate_protos.sh
``` 
Then to run it:
```
	./generate_protos.sh
```

# CLI encoding and decoding with proto-c
## Encoding example

```
	echo "val1 : 1, val2 : 5.5, val3 : 54" > cli_message
	protoc --encode=Message lib/protos/message.proto < cli_message > encoded.bin
	xxd encoded.bin
```
## Decoding example
```
	echo "0801 1500 00b0 4018 36" > encoded_hexdump 
	xxd -r -p encoded_hex_dump > encoded_bin
	protoc < encoded_bin --decode=Message lib/protos/message.proto

```

