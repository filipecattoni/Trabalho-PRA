#include "index.h"
using namespace std;

int main () {

    // FILE *fp = fopen("games.bin", "rb");
    // Game temp;
    // int i=0;

    // while (true) {
    //     fread(&temp, sizeof(Game), 1, fp);
    //     if (feof(fp)) break;
    //     cout << i << ": " << temp.name << endl;
    //     i++;
    // }

    // fclose(fp);

    FILE *fp = fopen("index-name.bin", "rb");
    char name[100];
    string line;

    getline(cin, line);
    strcpy(name, line.c_str());

    cout << str_get_index(name, 0, fp) << endl;

    fclose(fp);

}