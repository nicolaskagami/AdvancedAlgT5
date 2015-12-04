
#include<stdlib.h>
#include<iostream>
#include<time.h>

int main(int argc, char ** argv)
{
    if(argc!=2)
    {
        std::cerr << "Usage: " << argv[0] << " NumNodes\n";
        exit(1); 
    }
    unsigned num_nodes = atoi(argv[1]);
    srand(time(NULL));
    unsigned max = num_nodes*num_nodes;
    std::cout << num_nodes << std::endl;
    for(unsigned i = 0;i<num_nodes;i++)
    {
        for(unsigned j = 0;j<num_nodes;j++)
        {
            std::cout << rand()%max << " ";
        }
        std::cout << std::endl;
    }

}
