#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sstream>
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

typedef struct num_index
{
    int i;
    unsigned int num;
} NUM_Index;

typedef struct num_page
{
    int parent;
    int children[TREE_ORD+1];
    NUM_Index elements[TREE_ORD];
    int size;
    bool is_leaf;
} NUM_Page;

typedef struct str_index
{
    int i;
    char str[100];
} STR_Index;

typedef struct str_page
{
    int parent;
    int children[TREE_ORD+1];
    STR_Index elements[TREE_ORD];
    int size;
    bool is_leaf;
} STR_Page;

void num_fix_parents(std::vector<NUM_Page> &btree);
void num_insert_index(int ic, NUM_Index in, std::vector<NUM_Page> &btree);
void num_split_root(std::vector<NUM_Page> &btree);
void num_move_up(int ic, NUM_Index in, int c1, int c2, std::vector<NUM_Page> &btree);
void num_split_node(int ic, std::vector<NUM_Page> &btree);
void btree_insert_num(NUM_Index in, std::vector<NUM_Page> &btree);
int num_get_index(unsigned int num, int ic, FILE * fp);

void str_fix_parents(std::vector<STR_Page> &btree);
void str_insert_index(int ic, STR_Index in, std::vector<STR_Page> &btree);
void str_split_root(std::vector<STR_Page> &btree);
void str_move_up(int ic, STR_Index in, int c1, int c2, std::vector<STR_Page> &btree);
void str_split_node(int ic, std::vector<STR_Page> &btree);
void btree_insert_str(STR_Index in, std::vector<STR_Page> &btree);
int str_get_index(char *str, int ic, FILE * fp);