#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include "index.h"
using namespace std;

void id_fix_parents(vector<ID_Page> &btree) {

    stack<int> s;
    s.push(0);

    while (!s.empty()) {

        int c = s.top();
        s.pop();

        if (!btree[c].is_leaf) {
            for (int i=0; i<btree[c].size+1; i++) {
                btree[btree[c].children[i]].parent = c;
                s.push(btree[c].children[i]);
            }
        }

    }

}

void id_insert_index(int ic, ID_Index in, vector<ID_Page> &btree) {

    int ii = 0; // ii = insertion index
    while (true) {
        // cout << btree[ic].elements[ii].id << " > " << in.id << endl;
        if (ii > btree[ic].size-1) break;
        if (btree[ic].elements[ii].id > in.id) break;
        ii++;
    }
    // cout << btree[ic].size-1 << " >= " << ii << endl;
    for (int i=btree[ic].size; i>=ii; i--) {
        btree[ic].elements[i] = btree[ic].elements[i-1];
    }
    btree[ic].elements[ii] = in;
    btree[ic].size++;

}

void id_split_root(vector<ID_Page> &btree) {

    int ic = 0, mid = (TREE_ORD-1)/2;

    ID_Page left, right;
    int ileft = btree.size(), iright = btree.size()+1;

    for (int i=0; i<mid; i++) {
        left.elements[i] = btree[ic].elements[i];
    }
    left.size = mid;
    left.parent = ic;

    for (int i=0; i<mid; i++) {
        right.elements[i] = btree[ic].elements[mid+1+i];
    }
    right.size = mid;
    right.parent = ic;

    if (!btree[ic].is_leaf) {
        for (int i=0; i<mid+1; i++) {
            left.children[i] = btree[ic].children[i];
            right.children[i] = btree[ic].children[mid+i+1];
        }
        left.is_leaf = false;
        right.is_leaf = false;
    } else {
        left.is_leaf = true;
        right.is_leaf = true;
    }

    btree.push_back(left);
    btree.push_back(right);

    btree[ic].is_leaf = false;
    btree[ic].elements[0] = btree[ic].elements[mid];
    btree[ic].size = 1;
    btree[ic].children[0] = ileft;
    btree[ic].children[1] = iright;

}

void id_move_up(int ic, ID_Index in, int c1, int c2, vector<ID_Page> &btree) {

    // cout << "Inserindo " << in.id << " com filhos " << c1 << ", " << c2 << endl;
    // for (int i=0; i<btree[ic].size; i++) {
    //     cout << btree[ic].elements[i].id << endl;
    // }
    // cout << "Filhos: " << endl;
    // for (int i=0; i<btree[ic].size+1; i++) {
    //     cout << btree[ic].children[i] << endl;
    // }

    int ii = 0; 
    while (true) {
        if (ii > btree[ic].size-1) break;
        if (btree[ic].elements[ii].id > in.id) break;
        ii++;
    }
    for (int i=btree[ic].size; i>=ii; i--) {
        btree[ic].elements[i] = btree[ic].elements[i-1];
    }
    for (int i=btree[ic].size+1; i>=ii; i--) {
        btree[ic].children[i] = btree[ic].children[i-1];
    }
    btree[ic].elements[ii] = in;
    btree[ic].children[ii] = c1;
    btree[ic].children[ii+1] = c2;
    btree[ic].size++;

    // for (int i=0; i<btree[ic].size; i++) {
    //     cout << btree[ic].elements[i].id << endl;
    // }
    // cout << "Filhos: " << endl;
    // for (int i=0; i<btree[ic].size+1; i++) {
    //     cout << btree[ic].children[i] << endl;
    // }
    // cout << "------------------" << endl << endl;

}

void id_split_node(int ic, vector<ID_Page> &btree) {

    id_fix_parents(btree);

    if (ic == 0) {
        id_split_root(btree);
    } else {

        int mid = (TREE_ORD-1)/2;
        ID_Index temp = btree[ic].elements[mid];

        ID_Page newpage;
        newpage.size = mid;
        newpage.is_leaf = btree[ic].is_leaf;
        newpage.parent = btree[ic].parent;
        int inewpage = btree.size();

        for (int i=0; i<mid; i++) {
            newpage.elements[i] = btree[ic].elements[mid+1+i];
        }
        if (!btree[ic].is_leaf) {
            for (int i=0; i<mid+1; i++) {
                newpage.children[i] = btree[ic].children[mid+1+i];
            }
        }

        btree[ic].size = mid;
        btree.push_back(newpage);
        id_move_up(btree[ic].parent, temp, ic, inewpage, btree);

        if (btree[btree[ic].parent].size == TREE_ORD) {
            id_split_node(btree[ic].parent, btree);
        }

    }

}

void btree_insert_id(ID_Index in, vector<ID_Page> &btree) {

    int ic = 0; // ic = index of current
    // cout << in.i << " " << in.id << endl;

    while (!btree[ic].is_leaf) { // percorre btree até chegar em folha

        int it = 0;

        while (true) {
            if (it > btree[ic].size) {
                it--;
                break;
            }
            if (btree[ic].elements[it].id > in.id) break;
            it++;
        }

        ic = btree[ic].children[it];

    }

    id_insert_index(ic, in, btree);
    if (btree[ic].size == TREE_ORD) {
        id_split_node(ic, btree);
    }

}

int id_get_index(unsigned int id, int ic, FILE * fp) {

	fseek(fp, sizeof(ID_Page)*ic, SEEK_SET);
	ID_Page temp;
	fread(&temp, sizeof(ID_Page), 1, fp);

	int ii=0;
	for (int i=0; i<TREE_ORD-1; i++) {
		if (temp.elements[i].id == id) return temp.elements[i].i;
		if (temp.elements[i].id > id) break;
		ii++;
	}

	if (temp.is_leaf) return -1;
	return id_get_index(id, temp.children[ii], fp);

}