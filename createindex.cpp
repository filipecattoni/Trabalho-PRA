#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include "index.h"
using namespace std;

int main() {

    vector<ID_Page> btree;
    Game temp;
    ID_Index in;

    FILE *fp = fopen("games.bin", "rb");
    int count = 0;

    ID_Page root;
    root.is_leaf = true;
    root.size = 0;
    root.parent = -1;
    btree.push_back(root);

    while (!feof(fp)) {
        // if (count == 25) break;
        fread(&temp, sizeof(Game), 1, fp);
        in.i = count;
        in.id = temp.id;
        // cout << in.id << ", index " << in.i << endl;
        btree_insert_id(in, btree);
        // cout << btree.size() << endl;
        count++;
    }

    // exit(0);

    fclose(fp);
    fp = fopen("index-id.bin", "wb");

    for (auto page:btree) {
        fwrite(&page, sizeof(ID_Page), 1, fp);
    }

    fclose(fp);

}