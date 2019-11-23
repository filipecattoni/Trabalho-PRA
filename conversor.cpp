#include<bits/stdc++.h>
#include <cstring>

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

void printGame(Game g){

    // cout << "Game ----------------------------" << endl;
    cout << g.id << endl;
    // cout << g.name << endl;
    // cout << g.subtitle << endl;
    // cout << g.avgRate << endl;
    // cout << g.countRate << endl;
    // cout << g.price << endl;
    // cout << g.purchases << endl;
    // cout << g.description << endl;
    // cout << g.developer << endl;
    // cout << g.age << endl;
    // cout << g.languages << endl;
    // cout << g.size << endl;
    // cout << g.primaryGenre << endl;
    // cout << g.genres << endl;
    // cout << g.originalRelease << endl;
    // cout << g.lastRelease << endl;
    // cout << g.rank << endl;
    // cout << "Endgame -------------------------" << endl;

}

bool is_numeric(const char *s)
{
    int sizeOfString = strlen(s);
    int iteration = 0;
    bool isNumeric = true;

    while(iteration < sizeOfString)
    {
        if(!isdigit(s[iteration]))
        {
            isNumeric = false;
            break;
        }

        iteration++;

    }

    return isNumeric;
}

void convert_data()
{

    int i = 1;
    // File pointer
    fstream fin;

    // Open an existing file
    fin.open("dados.csv", ios::in);

    // reseting file
    FILE *f = fopen("games.bin", "w");
    fclose(f);

    f = fopen("games.bin", "a");

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;

    // tirar o cabecalho
    getline(fin, line);
    i++;

    while (getline(fin, line)) {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        // getline(fin, line);
        // cout << line <<  endl << endl;
        // cout << temp <<  endl;

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ';')) {


            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        Game aux;

        // cout << row[0] <<  endl;
        // if(!is_numeric(row[0].c_str()))
        //     cout << "erro0: '" << row[0] << "', linha: " << i << endl;
        aux.id = stoul(row[0]);
        strcpy(aux.name, row[1].c_str());
        strcpy(aux.subtitle, row[2].c_str());
        // cout << row[3] <<  endl;
        aux.avgRate = stof(row[3]);
        // if(!is_numeric(row[4].c_str()))
        //     cout << "erro4: '" << row[4] << "', linha: " << i << endl;
        aux.countRate = stoul(row[4]);
        // cout << row[5] <<  endl;
        aux.price = stof(row[5]);
        strcpy(aux.purchases, row[6].c_str());
        strcpy(aux.description, row[7].c_str());
        strcpy(aux.developer, row[8].c_str());
        strcpy(aux.age, row[9].c_str());
        strcpy(aux.languages, row[10].c_str());
        // if(!is_numeric(row[11].c_str()))
        //     cout << "erro11: '" << row[11] << "', linha: " << i << endl;
        aux.size = stoul(row[11]);
        strcpy(aux.primaryGenre, row[12].c_str());
        strcpy(aux.genres, row[13].c_str());
        strcpy(aux.originalRelease, row[14].c_str());
        strcpy(aux.lastRelease, row[15].c_str());
        // if(!is_numeric(row[16].c_str()))
        //     cout << "erro16: '" << row[16] << "', linha: " << i << endl;
        aux.rank = stoul(row[16]);

        // printGame(aux);
        i++;

        if (fwrite(&aux,sizeof(Game),1,f) != 1) {
            printf("Erro na escrita do arquivo\n");
        }

    }

    fin.close();

    fclose(f);
}

void dumpFile(){

    FILE *f = fopen("games.bin","r");

    Game aux;

    while(fread(&aux, sizeof(game), 1,f) == 1){

        printGame(aux);
        break;

    }

    fclose(f);

}

int main(int argc, char const *argv[])
{
    setbuf(stdin, NULL);

    //convert_data();

    dumpFile();

    return 0;
}
