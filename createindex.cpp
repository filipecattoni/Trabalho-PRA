#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define TREE_ORD 10
using namespace std;

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
    int children[TREE_ORD];
    ID_Index elements[TREE_ORD-1];
    int size;
    bool is_leaf;
} ID_Page;

vector<ID_Page> btree;

void btree_insert_id(ID_Index in) {

    int ic = 0, ip = -1; // ic = index of current, ip = index of parent. -1 = não existe parent (raiz nó)
    cout << in.i << " " << in.id << endl;

    while (!btree[ic].is_leaf) { // percorre btree até chegar em folha

        ip = ic;
        int it = 0;

        while (true) {
            if (it >= TREE_ORD-1) break;
            if (btree[ic].elements[it].id > in.id) break;
            it++;
        }

        ic = btree[ic].children[it];

    }

    if (btree[ic].size < TREE_ORD-1) { // folha não está cheia, inserir normalmente
        int ii = 0; // ii = insertion index
        while (true) {
            cout << btree[ic].elements[ii].id << " > " << in.id << endl;
            if (ii >= btree[ic].size-1) break;
            if (btree[ic].elements[ii].id > in.id) break;
            ii++;
        }
        cout << btree[ic].size-1 << " >= " << ii << endl;
        for (int i=btree[ic].size; i>=ii; i--) {
            btree[ic].elements[i] = btree[ic].elements[i-1];
        }
        btree[ic].elements[ii] = in;
        btree[ic].size++;
        for (int j=0; j<btree[ic].size; j++) {
            cout << btree[ic].elements[j].id << ", índice " << btree[ic].elements[j].i << endl;
        }
        cout << endl;
    }

}

int main() {

    Game temp;
    ID_Index in;

    FILE *fp = fopen("games.bin", "rb");
    int count = 0;

    ID_Page root;
    root.is_leaf = true;
    root.size = 0;
    btree.push_back(root);

    while (!feof(fp)) {
        if (count == 10) exit(0);
        fread(&temp, sizeof(Game), 1, fp);
        in.i = count;
        in.id = temp.id;
        // cout << in.id << ", index " << in.i << endl;
        btree_insert_id(in);
        count++;
    }

    exit(0);

    fclose(fp);
    fp = fopen("index-id.bin", "wb");

    for (auto page:btree) {
        fwrite(&page, sizeof(ID_Page), 1, fp);
    }
    cout << sizeof(ID_Page) << endl;

    fclose(fp);

}