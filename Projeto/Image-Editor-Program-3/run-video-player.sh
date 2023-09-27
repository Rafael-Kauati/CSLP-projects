#!/bin/bash
clear
cmake . && make && ./main $#
