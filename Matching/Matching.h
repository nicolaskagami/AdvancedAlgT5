

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#ifndef MIN
#define MIN 0
#endif

class Matching
{
    public:
        unsigned num_nodes;
        int * weights;

        unsigned * matches;
        bool * marked;

        unsigned int * prev;
        int * Avalue;
        int * Bvalue;
        bool * Bvisited;
        bool * Bmatched;

        Matching(std::istream& in);
        ~Matching();
        void print();
        void printPrevs();

        void BellmanFordMatch();

        //Benchmarking
        unsigned long long nodes_visited;
};
