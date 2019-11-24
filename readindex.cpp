#include "index.h"
using namespace std;

int main() {

    ID_Page temp;
    FILE *fp = fopen("index-id.bin", "rb");
    int i=0;

    while (true) {
        fread(&temp, sizeof(ID_Page), 1, fp);
        if (feof(fp)) break;
        cout << "Página " << i << ": " << endl;
        cout << "Pai: " << temp.parent << endl;
        cout << "Elementos: " << temp.size << endl;
        for (int j=0; j<temp.size; j++) {
            cout << temp.elements[j].id << ", índice " << temp.elements[j].i << endl;
        }
        if (!temp.is_leaf) {
            cout << "Filhos: " << endl;
            for (int j=0; j<temp.size+1; j++) {
                cout << temp.children[j] << endl;
            }
        }
        cout << endl;
        i++;
    }

}