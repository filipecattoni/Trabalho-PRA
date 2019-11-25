#include "index.h"
#include <ctime>
#include <iomanip>
using namespace std;

int main() {

	setprecision(10);

	unsigned int vals[4] = {529479190, 1449033203, 1097491735, 3213213};
	Game temp;
	clock_t tl, ti;
	int il, ii;
	for (int i=0; i<4; i++) {

		il = 0;
		cout << "Buscando ID " << vals[i] << endl;
		FILE *fp = fopen("games.bin", "rb");
		tl = clock();
		while (true) {
			fread(&temp, sizeof(Game), 1, fp);
			if (feof(fp)) {
				il = -1;
				break;
			}
			if (temp.id == vals[i]) break;
			il++;
		}
		fclose(fp);
		tl = clock() - tl;
		fp = fopen("index-id.bin", "rb");
		ti = clock();
		ii = num_get_index(vals[i], 0, fp);
		ti = clock() - ti;

		cout << "Busca sequencial: encontrou em índice " << il << endl;
		cout << fixed << "Tempo: " << ((double) tl) / CLOCKS_PER_SEC << " segundos" << endl;
		cout << "Busca com índice: encontrou em índice " << ii << endl;
		cout << fixed << "Tempo: " << ((double) ti) / CLOCKS_PER_SEC << " segundos" << endl;
		cout << "---------------------------" << endl << endl;

	}

}