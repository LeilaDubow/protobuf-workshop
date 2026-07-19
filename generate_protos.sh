#! /bin/bash
rm -r src/protos
mkdir src/protos
cd src/protos
../../lib/nanopb/generator/nanopb_generator -I ../../lib/protos message.proto
