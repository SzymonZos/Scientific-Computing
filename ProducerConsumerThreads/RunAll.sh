#!/bin/bash

find $1 -name $2 -executable -type f -exec {} \;
