


all: EPM EPPM Gen
EPM: Matching/Matching.cpp
	g++ -O3 -DMIN=0 Matching/Matching.cpp -o EPM
EPPM: Matching/Matching.cpp
	g++ -O3 -DMIN=1 Matching/Matching.cpp -o EPPM
Gen: Generation/RandomBipartiteGraph.cpp
	g++ Generation/RandomBipartiteGraph.cpp -o Gen
	
clean:
	rm -f EPM EPPM Gen
