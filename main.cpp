#include <iostream>
#include <fstream>
#include <cstring>
#include "Btn.h"
#include "AvlTree.h"

using namespace std;

int main()
{
    ifstream f("commands.txt");
    if(!f)
    {
        cout<<"Commands.txt did not open."<<endl;
        return 0;
    }

    string s;
    int a, b;
    AvlTree *tree = new AvlTree();

    while(!f.eof())
    {
        f>>s;
        if(s == "READ_DATA")
        {
            //cout<<"Reading data."<<endl;
            ifstream f2("input.txt");
            if(!f2)
            {
                cout<<"Input.txt did not open."<<endl;
                return 0;
            }

            while(!f2.eof())
            {
                f2>>a>>b;
                //cout<<a<<" "<<b<<endl;
                tree->addNeighbor(a,b);
                //add function here
            }
        }
        else if(s == "INSERT_LINK")
        {
            f>>a>>b;
            //cout<<"Inserting link : "<<a<<" "<<b<<endl;
            tree->addNeighbor(a,b);
            //add function here
        }
        else if(s == "DELETE_LINK")
        {
            f>>a>>b;
            //cout<<"Deleting link : "<<a<<" "<<b<<endl;
            tree->delNeighbor(a,b);
            //add function here
        }
        else if(s == "WRITE_INDEX")
        {
            ofstream f2("output.txt");
            if(!f2)
            {
                cout<<"Output.txt did not open."<<endl;
                return 0;
            }
            tree->output();
            //add function here
        }
    }

    return 0;
}
