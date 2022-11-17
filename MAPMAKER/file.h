#pragma once

void saveFile(int max);


void loadFromFile(int max);

void loadFromFile(int max) {

	string line;
	string idStr;

	ifstream file;
	file.open("./assets/mapLv0.txt");

	int index = 0;
	int n = 0;
	int x = 0;
	int y = 0;

	while (getline(file, line)) {
		while (line[index] != 59) {
			if (line[index] == 32) {

				if (index - n + 1 == 1) {
					idStr = line.substr(0, n);
				}
				else {
					idStr = line.substr(index - n + 1, n);
				}
				n = 0;
				if (idStr != ";") {
					tileMap[y][x].idLv0 = stoi(idStr);
					initTile(tileMap[y][x].idLv0, y, x);
				}
				x++;
			}
			n++;
			index++;
		}
		x = 0;
		index = 0;
		y++;
	}
	y = 0;

	file.close();

	file.open("./assets/mapLv1.txt");
	while (getline(file, line)) {
		while (line[index] != 59) {
			if (line[index] == 32) {
				if (index - n + 1 < 0) {
					n = 0;
				}
				idStr = line.substr(index - n + 1, n);
				n = 0;
				if (idStr != ";") {
					tileMap[y][x].idLv1 = stoi(idStr);
					initTile(tileMap[y][x].idLv1, y, x);
				}
				x++;
			}
			n++;
			index++;
		}
		x = 0;
		index = 0;
		y++;
	}
	y = 0;

	file.close();



}

void saveFile(int max) {

	ofstream file;
	file.open("./assets/mapLv0.txt");
	for (int y = 0; y < max; y++) {
		for (int x = 0; x < max; x++) {
			file << tileMap[y][x].idLv0 << " ";
		}
		file << ";" << endl;
	}
	file.close();

	file.open("./assets/mapLv1.txt");
	for (int y = 0; y < max; y++) {
		for (int x = 0; x < max; x++) {
			file << tileMap[y][x].idLv1 << " ";
		}
		file <<";"<< endl;
	}
	file.close();

}

