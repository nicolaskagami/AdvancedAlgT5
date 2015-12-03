

#include "Matching.h"

Matching::Matching(std::istream & in)
{
    num_nodes = 0;
    std::string line="", dummy;
    getline(in,line);

    std::stringstream linestr;
    linestr.str(line);
    linestr >> num_nodes;

    matches = new unsigned int[num_nodes];
    matched = new bool[num_nodes];
    weights = new int[num_nodes*num_nodes];

    //getline(in,line);
    for(unsigned i=0;i<num_nodes;i++)
    {
        if(!std::getline(in, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        std::stringstream arc(line);
        for(unsigned j=0;j<num_nodes;j++)
        {
            arc >> weights[i*num_nodes+j];
        }
    }


}
Matching::~Matching()
{
    delete matches;
    delete weights;    
}
void Matching::print()
{
    printf("Num Nodes: %u\n",num_nodes);
    for(unsigned i=0;i<num_nodes;i++)
    {
        for(unsigned j=0;j<num_nodes;j++)
        {
            printf("%i ",weights[i*num_nodes+j]);
        }
        printf("\n");
    }
    unsigned sum = 0;
    for(unsigned i=0;i<num_nodes;i++)
    {
        sum+=weights[i*num_nodes+matches[i]] ;
    }
    printf("Sum: %u\n",sum);
}
void Matching::BellmanFordMatch()
{
    unsigned * prev;
    bool * visited;
    unsigned * src;
    int * value;
    value = new int[num_nodes];
    visited = new bool[num_nodes];
    prev = new unsigned[num_nodes];
    src = new unsigned[num_nodes];
    for(unsigned i=0;i<num_nodes;i++)
    {
        matches[i] = i;
        visited[i]=false; 
        prev[i]=i; 
        value[i]=0;
    }

    bool foundAugPath;
    do
    {
        foundAugPath = false;
        //Search Augmenting Path
        for(unsigned i=0;i<num_nodes;i++)
        {
            for(unsigned j=0;j<num_nodes;j++)
            {
                if(j!=matches[i]) 
                {
                           
                }
            }
        }
        if(foundAugPath)
            ;//Apply Augmenting Path
     
    }while(foundAugPath);//There is augmenting path
      
    delete prev;
    delete visited;
    delete value;
    delete src;
}


int main(int argc, char ** argv)
{
    Matching h(std::cin);
    h.BellmanFordMatch();
    h.print();
}
