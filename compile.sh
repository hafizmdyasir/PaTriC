#!/bin/bash

clear
echo " ####        #######                 #### "
echo "#    #          #                   #    #"
echo "#    #          #                   #     "
echo "#####   ###     #     ###   #####   #     "
echo "#      #   #    #    #   #    #     #     "
echo "#      #####    #    ####     #     #    #"
echo "#      #   #    #    #   #  #####    #### "

echo ""
echo "=========================================="
echo ""


compilers=("g++" "clang" "icc")

echo "Select a C++ compiler from the list below, or type a custom compiler name:"
echo "Compilation will be done using the command <compiler-name> <files>."
for i in "${!compilers[@]}"; do
    echo "    $((i + 1)). ${compilers[$i]}"
done

echo ""
read -p "Awaiting input... : " user_input

# Determine the selected compiler
if [[ "$user_input" =~ ^[0-9]+$ ]] && ((user_input >= 1 && user_input <= ${#compilers[@]})); then
    selected_compiler=${compilers[$((user_input - 1))]}
else
    selected_compiler=$user_input
fi

echo "Selected compiler: $selected_compiler"
echo ""

# Compile all headers.
echo "Compiling headers..."
$selected_compiler source/headers/*.h

# Compile and link the main program.
echo "Compiling and linking main program..."
$selected_compiler source/*.cpp -o runtime/patric

if [[ $? -eq 0 ]]; then
    echo "Compilation successful! "
fi