#!/bin/bash

if 1; then
  echo "don't run this script"
  exit
fi

dd if=/dev/zero of=fs count=256 bs=4K
mke2fs fs
dumpe2fs fs
od -tx1 -Ax fs


