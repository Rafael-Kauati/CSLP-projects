#!/bin/bash

# Prompt the user to input the directory path (accept "." for current directory)
read -p "Enter the directory path (use '.' for current directory): " directory_to_search

# Remove CMakeFiles, CMakeCache.txt, cmake_install.cmake, and Makefile in the specified directory and its subdirectories
find "$directory_to_search" -type d -name "CMakeFiles" -exec rm -rf {} +
find "$directory_to_search" -type f -name "CMakeCache.txt" -delete
find "$directory_to_search" -type f -name "cmake_install.cmake" -delete
find "$directory_to_search" -type f -name "Makefile" -delete

echo "CMake-related files and directories removed successfully in the specified directory and its subdirectories."
#!/bin/bash

rm -r CMakeFiles CMakeCache.txt cmake_install.cmake Makefile