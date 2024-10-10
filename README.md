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

[output.txt](output/output.txt) Each line contains an integer, the number of integers linked to that integer and the linked integers themselves.

## For Users

### Usage

To execute run:
```
docker compose up
```
Once execution has ended, the container will exit automatically. The program writes output to `/apps/output` inside the container. To get the output directory to your system run:
```
docker cp avl-tree-linked-avl-tree-linked-1:/app/output ./
```
The `output` directory will contain only one file, `output.txt`, which contains the result of the execution.

## For Developers
>New in v1.4: Rewritten as a header-only library so the only file neccessary is [AVLtree.h](src/AVLtree.h).

### Includes

```
#include "AVLtree.h"
```

### Create an empty tree

```
AVLtree<int> * tree = new AVLtree<int>();
```

### Insert value

```
int value = 5;
Node<int> * node = tree->insertElement(value);
if(node)
{
  std::cout << "Inserted";
}
```  

### Delete value

```
int value = 5;
bool deleted = tree->deleteElement(value);
if(deleted)
{
  std::cout << "Deleted";
}
```    

### Search value

```
int value = 5;
Node<int> * node = tree->search(value);
if(node)
{
  std::cout << "Found";
}

```

### Insert link

```
int value = 5;
int neighbor = 6;
Node<int> * node = tree->search(value);
if(node)
{
  Node<int> * neighborNode = node->insertNeighbor(neighbor);
  if(neighborNode)
  {
    std::cout << "Link inserted";
  }
}
```

### Delete link

```
int value = 5;
int neighbor = 6;
Node<int> * node = tree->search(value);
if(node)
{
  bool deleted = node->deleteNeighbor(neighbor);
  if(deleted)
  {
    std::cout << "Link deleted";
  }
}
```
