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

typedef struct btree{
    int root;
    int order = TREE_ORD;
    vector<ID_Page> nodes;
}Btree;

Btree bt;

void addIndexInPage( int i_page, ID_Index new_index ){

    int ii = 0; // ii = insertion index

    while (true) {
        //cout << bt.nodes[i_page].elements[ii].id << " > " << new_index.id << endl;
        if (ii > bt.nodes[i_page].size-1) break;
        if (bt.nodes[i_page].elements[ii].id > new_index.id) break;
        ii++;
    }
    cout << bt.nodes[i_page].size-1 << " >= " << ii << endl;
    for (int i=bt.nodes[i_page].size; i>=ii; i--) {
        bt.nodes[i_page].elements[i] = bt.nodes[i_page].elements[i-1];
        cout << ii << " " << i << endl;
    }
    bt.nodes[i_page].elements[ii] = new_index;
    bt.nodes[i_page].size++;
}

void btree_insert_id(ID_Index in) {

    int ic = bt.root, ip = -1; // ic = index of current, ip = index of parent. -1 = não existe parent (raiz nó)
    cout << in.i << " " << in.id << endl;

    while (!bt.nodes[ic].is_leaf) { // percorre bt.nodes até chegar em folha

        ip = ic;
        int it = 0;
        cout << ic << " " << bt.nodes[ic].size-1 << " " << it << endl;
        cout << bt.nodes[ic].elements[it].id << " > " << in.id << endl;

        while (true) {
            if (it > bt.nodes[ic].size-1) break;
            printf("1\n");
            if (bt.nodes[ic].elements[it].id > in.id) break;
            printf("2\n");
            it++;
            cout << "o";
        }
        printf("3\n");
        ic = bt.nodes[ic].children[it];
        printf("4 %i\n", ic);
    }
    printf("1\n");
    if (bt.nodes[ic].size < TREE_ORD-1) { // folha não está cheia, inserir normalmente

        cout << "d";
        addIndexInPage( ic, in );
        for (int j=0; j<bt.nodes[ic].size; j++) {
            cout << bt.nodes[ic].elements[j].id << ", índice " << bt.nodes[ic].elements[j].i << endl;
        }
        cout << endl;
        
    }else{
        cout << "c";

        int i_split = (TREE_ORD-1)/2;
        int i;

        // separando nó atual
        // nó da direita
        ID_Page rightNode;
        rightNode.is_leaf = bt.nodes[ic].is_leaf;
        rightNode.size = bt.nodes[ic].size/2;
        for (i=0; i<bt.nodes[ic].size/2; i++) {
            rightNode.elements[i] = bt.nodes[ic].elements[i+bt.nodes[ic].size/2+1];
            rightNode.children[i] = bt.nodes[ic].children[bt.nodes[ic].size/2+i+1];
        }
        rightNode.children[i] = bt.nodes[ic].children[bt.nodes[ic].size/2+i+1];

        // nó da esquerda
        bt.nodes[ic].size /= 2;

        // adicionando novo nó à bt.nodes
        bt.nodes.push_back(rightNode);

        // adicionando in em uma das duas páginas criadas
        if(in.id > bt.nodes[ic].elements[i_split].id){
            addIndexInPage( bt.nodes.size()-1, in );
        }else{
            addIndexInPage( ic, in );
        }

        if(ip == -1){
            cout << "b";

            // criando novo nó raiz
            ID_Page newRoot;
            newRoot.is_leaf = false;
            newRoot.size = 1;
            newRoot.elements[0] = bt.nodes[ic].elements[i_split];
            newRoot.children[0] = ic;
            newRoot.children[1] = bt.nodes.size() - 1;
            bt.nodes.push_back(newRoot);
            bt.root = bt.nodes.size() - 1;

        }else{
            cout << "a";

            // adicionado elemento no nó pai 
            addIndexInPage( ip, bt.nodes[ic].elements[i_split] );

        }

    }

}

int main() {

    setbuf(stdin, NULL);
    Game temp;
    ID_Index in;

    FILE *fp = fopen("games.bin", "rb");
    int count = 0;

    ID_Page root;
    root.is_leaf = true;
    root.size = 0;
    bt.nodes.push_back(root);
    bt.root = 0;

    while (!feof(fp)) {
        // if (count == 10) exit(0);
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

    for (auto page:bt.nodes) {
        fwrite(&page, sizeof(ID_Page), 1, fp);
    }
    cout << sizeof(ID_Page) << endl;

    fclose(fp);

}