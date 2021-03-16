#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"Vertex.h"

int main() {
    ALGraph g;
    CreateGraph(g);
    PrintDGraph(&g);
    DFSTraverse(&g);
    return 0;
}
