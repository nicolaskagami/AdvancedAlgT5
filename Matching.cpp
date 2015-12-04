

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
            if(matches[i]==j)
                printf("[%i] ",weights[i*num_nodes+j]);
            else
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
    unsigned * src;
    int * Avalue = new int[num_nodes];
    int * Bvalue = new int[num_nodes];
    bool * Avisited = new bool[num_nodes];
    bool * Bvisited = new bool[num_nodes];
    prev = new unsigned[num_nodes];
    src = new unsigned[num_nodes];
    for(unsigned i=0;i<num_nodes;i++)
    {
        matches[i] = i;
        Avisited[i]=false; 
        Bvisited[i]=false; 
        prev[i]=i; 
        Avalue[i]=0;
        Bvalue[i]=0;
    }
    unsigned cycler;
    bool foundAugPath;
    do
    {
        foundAugPath = false;
        //Search Augmenting Path
        for(unsigned potential_cycle=0;potential_cycle<num_nodes;potential_cycle++)
        {
            for(unsigned i=0;i<num_nodes;i++)
            {
                Avisited[i]=false; 
                Bvisited[i]=false; 
                prev[i]=3; 
                Avalue[i]=0;
                Bvalue[i]=0;
            }
            Avisited[potential_cycle]=true;
            for(unsigned k=0;k<num_nodes;k++)
            {
                //From now on, complexity = O(E)
                for(unsigned i=0;i<num_nodes;i++)
                {
                    for(unsigned j=0;j<num_nodes;j++)
                    {
                        if(j==matches[i]) 
                        {
                            //If there is a value to propagate and (this is a new node || this is a better value)
                            if((Bvisited[j])&&(!Avisited[i] || (Avalue[i] < Bvalue[j] - weights[i*num_nodes+j])))
                            {
                                Avalue[i] = Bvalue[j] - weights[i*num_nodes+j];
                                Avisited[i] = true;
                                if(i==potential_cycle)
                                {
                                    cycler = potential_cycle;
                                    printf("Value: %u\n",Avalue[i]);
                                    print();
                                    foundAugPath = true;break;
                                }
                            }
                        }
                        else
                        {
                            //If there is a value to propagate and (this is a new node || this is a better value)
                            if((Avisited[i])&&(!Bvisited[j] || (Bvalue[j] < Avalue[i] + weights[i*num_nodes+j])))
                            {
                                Bvalue[j] = Avalue[i] + weights[i*num_nodes+j];
                                prev[j] = i;
                                Bvisited[j] = true;
                            }
                        }
                    }
                    if(foundAugPath)
                        break;
                }
                if(foundAugPath)
                    break;
            }
            if(foundAugPath)
                break;
        }

        if(foundAugPath)
        {
            unsigned node = matches[cycler];
            printf("Cycler: %u\n",cycler);
            while(Bvisited[node]&&(prev[node]!=cycler))
            {
                printf("BNode: %u\n",node);
                printf("ANode: %u\n",prev[node]);
                unsigned next_node = matches[prev[node]];
                matches[prev[node]] = node;
                node = next_node;
            }
            matches[cycler] = node;
        }//Apply Augmenting Path
    }while(foundAugPath);//There is augmenting path
      
    delete prev;
    delete Avisited;
    delete Bvisited;
    delete Avalue;
    delete Bvalue;
    delete src;
}


int main(int argc, char ** argv)
{
    Matching h(std::cin);
    h.BellmanFordMatch();
    h.print();
}
