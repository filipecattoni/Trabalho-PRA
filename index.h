#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define TREE_ORD 9

typedef struct game
{
    unsigned int id;
    char name[100];
    char subtitle[100];
    float avgRate;
    unsigned int countRate;
    float price;
    char purchases[500];
    char description[10000];
    char developer[100];
    char age[10];
    char languages[300];
    unsigned long int size;
    char primaryGenre[100];
    char genres[300];
    char originalRelease[15];
    char lastRelease[15];
    unsigned int rank;
} Game;

typedef struct id_index
{
    int i;
    unsigned int id;
} ID_Index;

typedef struct id_page
{
    int parent;
    int children[TREE_ORD+1];
    ID_Index elements[TREE_ORD];
    int size;
    bool is_leaf;
} ID_Page;

void fix_parents(std::vector<ID_Page> &btree_id);
void id_insert_index(int ic, ID_Index in, std::vector<ID_Page> &btree_id);
void id_split_root(std::vector<ID_Page> &btree_id);
void id_move_up(int ic, ID_Index in, int c1, int c2, std::vector<ID_Page> &btree_id);
void id_split_node(int ic, std::vector<ID_Page> &btree_id);
void btree_insert_id(ID_Index in, std::vector<ID_Page> &btree_id);
int id_get_index(unsigned int id, int ic, FILE * fp);