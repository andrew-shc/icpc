#!/bin/bash


# CF: GNU G++17 7.3.0
# Sys: GNU G++17 11.4.0
# (Release? Unlikely to be used) `g++ -std=c++17 -O2 A.cpp -o A`
# (Debug) `g++ -std=c++17 -Wall -Wextra -fdiagnostics-color=always -Wshadow -ggdb3 -DDEBUG -fsanitize=address,undefined A.cpp`



# Usage: ./run.sh [folder] problemname 
# Example: ./run.sh div2_1078_virt A
# Example: ./run.sh . B  (uses current directory)

if [ $# -eq 0 ]; then
    echo "Usage: $0 [folder] <problem_name>"
    echo "Example: $0 div2_1078_virt A"
    echo "Example: $0 . B  (uses current folder)"
    exit 1
fi

if [ $# -eq 1 ]; then
    # Only one argument, assume current directory
    FOLDER="."
    PROBLEM=$1
else
    # Two arguments, folder first
    FOLDER=$1
    PROBLEM=$2
fi

# Set file paths
CPP_FILE="${FOLDER}/${PROBLEM}.cpp"
OUTPUT_FILE="${FOLDER}/${PROBLEM}"

# Check if source file exists
if [ ! -f "$CPP_FILE" ]; then
    echo "❌ Error: $CPP_FILE does not exist"
    exit 1
fi

# Compilation flags (Debug with sanitizers)
FLAGS="-std=c++17 -Wall -Wextra -O2 -fdiagnostics-color=always -Wshadow -Wno-sign-compare -ggdb3 -DDEBUG -fsanitize=address,undefined -pedantic -fno-sanitize-recover"

# Add include path for shared headers (script directory and current folder)
SCRIPT_DIR=$(dirname "$0")
INCLUDE_PATH="-I${SCRIPT_DIR} -I${FOLDER}"

# Compile silently
g++ $FLAGS $INCLUDE_PATH "$CPP_FILE" -o "$OUTPUT_FILE"

# Check if compilation was successful and run
if [ $? -eq 0 ]; then
    echo "✅ Compilation succeeded"
    "$OUTPUT_FILE"
else
    echo "❌ Compilation failed" >&2
    exit 1
fi

