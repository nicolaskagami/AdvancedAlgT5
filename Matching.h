

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>

class Matching
{
    public:
        int * weights;
        unsigned * matches;
        bool * matched;
        unsigned num_nodes;

        Matching(std::istream& in);
        ~Matching();
        void print();

        void BellmanFordMatch();

};
