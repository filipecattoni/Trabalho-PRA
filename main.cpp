#include "index.h"
using namespace std;

void print_game(Game g) {
    cout << "ID: " << g.id << endl;
    cout << "Nome: " << g.name << endl;
    cout << "Subtitulo: " << g.subtitle << endl;
    cout << "Avaliação média: " << g.avgRate << endl;
    cout << "Número de avaliações: " << g.countRate << endl;
    cout << "Preço: " << g.price << endl;
    cout << "Compras: " << g.purchases << endl;
    cout << "Descrição: " << g.description << endl;
    cout << "Desenvolvedor: " << g.developer << endl;
    cout << "Idade: " << g.age << endl;
    cout << "Línguas: " << g.languages << endl;
    cout << "Tamanho: " << g.size << endl;
    cout << "Gênero principal: " << g.primaryGenre << endl;
    cout << "Gêneros: " << g.genres << endl;
    cout << "Data de lançamento: " << g.originalRelease << endl;
    cout << "Data de atualização: " << g.lastRelease << endl;
    cout << "Ranqueamento: " << g.rank << endl;
    cout << "-------------------------------" << endl;
}

Game read_game() {
    Game g;
    cout << "Digite o ID: " << endl;
    cin >> g.id;
    cout << "Digite o Nome: " << endl;
    cin >> g.name;
    cout << "Digite o Subtitulo: " << endl;
    cin >> g.subtitle;
    cout << "Digite a Avaliação média: " << endl;
    cin >> g.avgRate;
    cout << "Digite o Número de avaliações: " << endl;
    cin >> g.countRate;
    cout << "Digite o Preço: " << endl;
    cin >> g.price;
    cout << "Digite as Compras: " << endl;
    cin >> g.purchases;
    cout << "Digite a Descrição: " << endl;
    cin >> g.description;
    cout << "Digite o Desenvolvedor: " << endl;
    cin >> g.developer;
    cout << "Digite a Idade: " << endl;
    cin >> g.age;
    cout << "Digite as Línguas: " << endl;
    cin >> g.languages;
    cout << "Digite o Tamanho: " << endl;
    cin >> g.size;
    cout << "Digite o Gênero principal: " << endl;
    cin >> g.primaryGenre;
    cout << "Digite os Gêneros: " << endl;
    cin >> g.genres;
    cout << "Digite a Data de lançamento: " << endl;
    cin >> g.originalRelease;
    cout << "Digite a Data de atualização: " << endl;
    cin >> g.lastRelease;
    cout << "Digite o Ranqueamento: " << endl;
    cin >> g.rank;
    return g;
}

int main () {

    FILE *fp, *fi;
    char name[100];
    Game temp;
    string line;
    int menu, submenu, i;

    while (true) {

        cout << "1 - Consulta\n2 - Inserção\n0 - Sair " << endl;
        cin >> menu;
        if (menu == 0) break;
        if (menu == 1) {

            cout << "1 - Consulta por ID\n2- Consulta por rank\n3 - Consulta por nome" << endl;
            cin >> submenu;

            if (submenu == 1) {

                int id;
                cout << "Digite o ID: " << endl;
                cin >> id;
                fi = fopen("index-id.bin", "rb");
                i = num_get_index(id, 0, fi);
                fclose(fi);

                if (i == -1) {
                    cout << "ID não encontrado. " << endl;
                } else {

                    fp = fopen("games.bin", "rb");
                    fseek(fp, sizeof(Game)*i, SEEK_SET);
                    fread(&temp, sizeof(Game), 1, fp);
                    print_game(temp);
                    fclose(fp);

                }


            } else if (submenu == 2) {

                int rank;
                cout << "Digite o rank: " << endl;
                cin >> rank;
                fi = fopen("index-rank.bin", "rb");
                i = num_get_index(rank, 0, fi);
                fclose(fi);

                if (i == -1) {
                    cout << "Rank não encontrado. " << endl;
                } else {

                    fp = fopen("games.bin", "rb");
                    fseek(fp, sizeof(Game)*i, SEEK_SET);
                    fread(&temp, sizeof(Game), 1, fp);
                    print_game(temp);
                    fclose(fp);

                }

            } else if (submenu == 3) {

                cout << "Digite o nome: " << endl;
                getline(cin, line);
                while (line.length()==0) { getline(cin, line); }
                strcpy(name, line.c_str());
                fi = fopen("index-name.bin", "rb");
                i = str_get_index(name, 0, fi);
                fclose(fi);

                if (i == -1) {
                    cout << "Nome não encontrado. " << endl;
                } else {

                    fp = fopen("games.bin", "rb");
                    fseek(fp, sizeof(Game)*i, SEEK_SET);
                    fread(&temp, sizeof(Game), 1, fp);
                    print_game(temp);
                    fclose(fp);

                }

            } else {
                cout << "Opção inválida. " << endl << endl;
            }

        } else if (menu == 2) {

            // temp = read_game();
            // int ii;
            // fp = fopen("games.bin", "rb");
            // fseek(fp, 0, SEEK_END);
            // ii = ftell(fp) / sizeof(Game);
            // fclose(fp);

            // fp = fopen("games.bin", "wb");
            // fwrite(&temp, sizeof(Game), 1, fp);
            // fclose(fp);

            // NUM_Index ni; STR_Index si;
            // ni.i = ii;

        } else {
            cout << "Opção inválida. " << endl << endl;
        }

    }

}