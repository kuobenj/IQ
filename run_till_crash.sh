#!/bin/bash
for (( i = 0; i < 1179648; i++ )); do
	./devmem_test $i
done