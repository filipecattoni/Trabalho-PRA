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

            } else {
                cout << "Opção inválida. " << endl << endl;
            }

        } else if (menu == 2) {



        } else {
            cout << "Opção inválida. " << endl << endl;
        }

    }

}