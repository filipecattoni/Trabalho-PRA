#include "index.h"
using namespace std;

int main () {

    FILE *fp = fopen("index-id.bin", "rb");
    unsigned int id;

    cin >> id;

    cout << id_get_index(id, 0, fp) << endl;

    fclose(fp);

}