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

    vector<NUM_Page> btree_id, btree_rank;
    vector<STR_Page> btree_name;
    Game temp;
    NUM_Index in;
    STR_Index in_str;

    FILE *fp = fopen("games.bin", "rb");
    int count = 0;

    NUM_Page root;
    root.is_leaf = true;
    root.size = 0;
    root.parent = -1;
    btree_id.push_back(root);
    btree_rank.push_back(root);

    STR_Page root_str;
    root_str.is_leaf = true;
    root_str.size = 0;
    root_str.parent = -1;
    btree_name.push_back(root_str);

    while (!feof(fp)) {
        // if (count == 927) break;
        fread(&temp, sizeof(Game), 1, fp);
        in.i = count;
        in.num = temp.id;
        // cout << in.id << ", index " << in.i << endl;
        btree_insert_num(in, btree_id);
        in.num = temp.rank;
        btree_insert_num(in, btree_rank);
        strcpy(in_str.str, temp.name);
        in_str.i = count;
        // cout << count << " " << in_str.str << endl;
        btree_insert_str(in_str, btree_name);
        count++;
    }

    // exit(0);

    fclose(fp);
    fp = fopen("index-id.bin", "wb");

    for (auto page:btree_id) {
        fwrite(&page, sizeof(NUM_Page), 1, fp);
    }

    fclose(fp);

    fp = fopen("index-rank.bin", "wb");

    for (auto page:btree_rank) {
        fwrite(&page, sizeof(NUM_Page), 1, fp);
    }

    fclose(fp);

    fp = fopen("index-name.bin", "wb");

    for (auto page:btree_name) {
        fwrite(&page, sizeof(STR_Page), 1, fp);
    }

    fclose(fp);

}