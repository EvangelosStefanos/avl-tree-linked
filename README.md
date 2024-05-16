# avl-tree-linked
  A C++ implementation of the AVL tree data structure used as a search index for linked integers.

## Details
  A node in the AVL tree stores an integer and a separate AVL tree that includes integers linked to the node's integer. Links between integers are specified as input.

## Sample Files

For convenience a total of three sample files are provided. Two of them are input files and the third is the output of the program.

### Input
  [commands.txt](input/commands.txt) :  Each line contains a command the program can process. When using the READ_DATA command you must use a correct relative file path based on your current working directory.
  
  [input.txt](input/input.txt) :  Each line contains a pair of integers used to define that the second integer is linked to the first.

### Output
  [output.txt](output/ouput.txt) Each line contains an integer, the number of integers linked to that integer and the linked integers themselves.

## Usage
  An executable will be provided with each release. The directory of the executable must also contain a directory `input` with the `commands.txt` and `input.txt` files and a directory `output` where the output text file will be saved. To use the executable, open a terminal in the directory it is located and enter `.\AvlTree_Final.exe` to run the program. Otherwise, you will have to compile the code and then run it on your own.
  