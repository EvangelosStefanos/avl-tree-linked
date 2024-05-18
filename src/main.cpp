#include <iostream>
#include <fstream>
#include "Node.h"
#include "Node.cpp"
#include "AVLtree.h"
#include "AVLtree.cpp"

int main()
{
  std::string commands_path = "input/commands.txt";
  std::ifstream commands_stream(commands_path);
  if (!commands_stream)
  {
    std::cout << commands_path << " did not open." << std::endl;
    return 0;
  }

  std::string command_read = "READ_DATA";
  std::string command_insert = "INSERT_LINK";
  std::string command_delete = "DELETE_LINK";
  std::string command_write = "WRITE_INDEX";

  std::string command;
  int first;
  int second;
  AVLtree<int> *tree = new AVLtree<int>();

  while (commands_stream >> command)
  {
    if (command == command_read)
    {
      // cout<<"Reading data."<<endl;
      std::string input_path;
      commands_stream >> input_path;
      std::ifstream input_stream(input_path);
      if (!input_stream)
      {
        std::cout << input_path << " did not open." << std::endl;
        return 0;
      }

      while (input_stream >> first >> second)
      {
        Node<int> *node = tree->search(first);
        if(!node)
        {
          node = tree->insertElement(first);
        }
        if(!node->hasNeighbor(second))
        {
          node->insertNeighbor(second);
        }
      }
    }
    else if (command == command_insert)
    {
      commands_stream >> first >> second;
      Node<int> *node = tree->search(first);
      if (!node)
      {
        node = tree->insertElement(first);
      }
      if (!node->hasNeighbor(second))
      {
        node->insertNeighbor(second);
      }
    }
    else if (command == command_delete)
    {
      commands_stream >> first >> second;
      Node<int> *node = tree->search(first);
      if (!node)
      {
        std::cout << "INFO: No link deleted for " << first << " and " << second << ". " << first << " was not found." << std::endl;
      }
      else
      {
        if(!node->hasNeighbor(second))
        {
          std::cout << "INFO: No link deleted for " << first << " and " << second << ". Link does not exist." << std::endl;
        }
        else
        {
          node->deleteNeighbor(second);
        }
      }
    }
    else if (command == command_write)
    {
      std::string output_path;
      commands_stream >> output_path;
      tree->output(output_path);
    }
  }
  return 0;
}
