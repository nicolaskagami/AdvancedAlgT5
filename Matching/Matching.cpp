

#include "Matching.h"

Matching::Matching(std::istream & in)
{
    nodes_visited = 0;
    num_nodes = 0;
    std::string line="", dummy;
    getline(in,line);

    std::stringstream linestr;
    linestr.str(line);
    linestr >> num_nodes;

    matches = new unsigned int[num_nodes];
    weights = new int[num_nodes*num_nodes];
    marked = new bool[num_nodes];

    Avalue = new int[num_nodes];
    Bvalue = new int[num_nodes];
    Bvisited = new bool[num_nodes];
    Bmatched = new bool[num_nodes];
    prev = new unsigned int [num_nodes];

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
            if(MIN)
                weights[i*num_nodes+j] *= -1;
        }
    }

}
Matching::~Matching()
{
    delete []matches;
    delete []weights;    
    delete []marked;

    delete []prev;
    delete []Bvisited;
    delete []Bmatched;
    delete []Avalue;
    delete []Bvalue;
}
void Matching::print()
{
    /*
    printf("Num Nodes: %u\n",num_nodes);
    for(unsigned i=0;i<num_nodes;i++)
    {
        for(unsigned j=0;j<num_nodes;j++)
        {
            if(matches[i]==j)
                printf("[%i] ",weights[i*num_nodes+j]);
            else
                printf("%i ",weights[i*num_nodes+j]);
        }
        printf("\n");
    }*/
    int sum = 0;
    for(unsigned i=0;i<num_nodes;i++)
    {
        if(matches[i]!=-1)
            sum+=weights[i*num_nodes+matches[i]] ;
    }
    if(MIN)
        sum*=-1;
    std::cout << sum << std::endl; 
    std::cerr << num_nodes  << " " << nodes_visited << std::endl;
}
void Matching::printPrevs()
{
    printf("A\t\t\t\tB\n");
    for(unsigned i=0;i<num_nodes;i++)
    {
        printf("[%i] ",matches[i]);
        printf(" %d",Avalue[i]);
        printf("\t\t%i ",prev[i]);
        printf(" %d",Bvalue[i]);
        printf("\n");
    }
    printf("\n");
}
void Matching::BellmanFordMatch()
{
    for(unsigned i=0;i<num_nodes;i++)
    {
        matches[i] = -1;
        marked[i] = false;

        prev[i]=i; 
        Bvisited[i]=false; 
        Bmatched[i]=false; 
        Avalue[i]=0;
        Bvalue[i]=0;
    }
    bool foundAugPath;
    do
    {
        foundAugPath = false;
        //Search Augmenting Path
        for(unsigned i=0;i<num_nodes;i++)
        {
            if(matches[i]==-1)
                marked[i] = true;
            else
                marked[i] = false;

            Bvisited[i]=false; 
            prev[i]=3; 
            Avalue[i]=0;
            Bvalue[i]=0;
        }
        for(unsigned k=0;k<num_nodes;k++)
        {
            //From now on, complexity = O(E)
            for(unsigned i=0;i<num_nodes;i++)
            {
                if((matches[i] != -1)&&(Bvisited[matches[i]]))
                {
                    marked[i] = true;
                    Avalue[i] = Bvalue[matches[i]] + weights[i*num_nodes + matches[i]];
                }
                if(marked[i])
                    for(unsigned j=0;j<num_nodes;j++)
                    {
                        if(j!=matches[i]) 
                        {
                            nodes_visited++;
                            //If there is a value to propagate and (this is a new node || this is a better value)
                            if(!Bvisited[j] || (Bvalue[j] > Avalue[i] - weights[i*num_nodes+j]))
                            {
                                Bvalue[j] = Avalue[i] - weights[i*num_nodes+j];
                                prev[j] = i;
                                Bvisited[j] = true;
                            }
                        }
                    }
            }
        }
        //Determine best path
        int bestValue = 0;
        unsigned bestNode;
        for(unsigned i =0;i<num_nodes;i++)
        {
            if((!Bmatched[i])&&((!foundAugPath)||(bestValue>Bvalue[i])))
            {
                foundAugPath = true;
                bestValue = Bvalue[i];
                bestNode = i;
            }
        }

        if(foundAugPath)
        {
            unsigned node = bestNode;
            while(matches[prev[node]]!=-1)
            {
                //printf("BNode: %u\n",node);
                //printf("ANode: %u\n",prev[node]);
                unsigned next_node = matches[prev[node]];
                matches[prev[node]] = node;
                Bmatched[node]=true; 
                node = next_node;
            }
            matches[prev[node]] = node;
            Bmatched[node]=true; 
        }//Apply Augmenting Path
    }while(foundAugPath);//There is augmenting path
      
}

int main(int argc, char ** argv)
{
    Matching h(std::cin);
    h.BellmanFordMatch();
    h.print();
}
