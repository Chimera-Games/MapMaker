#pragma once

void initTile(int id, int y, int x);
void updateRenderTiles(View& view, int nX, int nY);
void initTileLv0(int max);
void initTileLv1(int max);
void drawTileLv0(RenderWindow& window);
void drawTileLv1(RenderWindow& window);

void initTileLv0(int max) {
	for (int y = 0; y < max; y++) {
		for (int x = 0; x < max; x++) {
			if (tileMap[y][x].initCheck == false) {
				tileMap[y][x].shapeLv0.setSize(Vector2f(gridSizeF, gridSizeF));
				tileMap[y][x].shapeLv0.setPosition(Vector2f(x * gridSizeF, y * gridSizeF));
				tileMap[y][x].initCheck = true;
			}
		}
	}
}

void initTile(int id, int y, int x) {

	switch (id)
	{
		//blocco transparente
	case 0:
		tileMap[y][x].shapeLv0.setFillColor(Color::Blue);
		tileMap[y][x].shapeLv0.setOutlineThickness(1);
		tileMap[y][x].shapeLv0.setOutlineColor(Color::Cyan);

		//tileMap[y][x].description = "Blocco Trasparente";
		break;
		//blocco erba
	case 1:
		tileMap[y][x].coordLv0[0] = 0;
		tileMap[y][x].coordLv0[1] = 0;
		//tileMap[y][x].description = "Erba, probabilmente pietro ne aveva bisogno";
		break;
		//blocco erba arida
	case 2:
		tileMap[y][x].coordLv0[0] = 1;
		tileMap[y][x].coordLv0[1] = 0;
		// tileMap[y][x].description = "Erba arida ";
		break;

	case 3: //erba con fiori
		tileMap[y][x].coordLv0[0] = 2;
		tileMap[y][x].coordLv0[1] = 0;
		// tileMap[y][x].description = "Erba, stranamente, con fiori";
		break;

		//albero senza foglie
	case 500:
		tileMap[y][x].coordLv1[0] = 1;
		tileMap[y][x].coordLv1[1] = 0;
		break;

		//albero con foglie
	case 501:
		tileMap[y][x].coordLv1[0] = 0;
		tileMap[y][x].coordLv1[1] = 0;
		break;

		//fiume
	case 502:
		tileMap[y][x].coordLv1[0] = 2;
		tileMap[y][x].coordLv1[1] = 0;
		break;

	case 503:
		tileMap[y][x].coordLv1[0] = 3;
		tileMap[y][x].coordLv1[1] = 0;
		break;

	default:
		break;
	}

}

void updateRenderTiles(View& view, int nX, int nY) {


	//reneder Game elements
	fromX = view.getCenter().x / gridSizeF - static_cast<float>(nX) / 2 - 1;
	toX = view.getCenter().x / gridSizeF + static_cast<float>(nX) / 2 + 2;

	fromY = view.getCenter().y / gridSizeF - static_cast<float>(nY) / 2 - 1;
	toY = view.getCenter().y / gridSizeF + static_cast<float>(nY) / 2 + 2;



	//X
	if (fromX <= 0) {
		fromX = 0;
	}
	else if (fromX >= mapSize) {
		fromX = mapSize - 1;
	}

	if (toX <= 0) {
		toX = 0;
	}
	else if (toX >= mapSize) {
		toX = mapSize - 1;
	}

	//Y
	if (fromY <= 0) {
		fromY = 0;
	}
	else if (fromY >= mapSize) {
		fromY = mapSize - 1;
	}

	if (toY <= 0) {
		toY = 0;
	}
	else if (toY >= mapSize) {
		toY = mapSize - 1;
	}


}

void drawTileLv0(RenderWindow& window) {

	Vector2u textureSize;
	textureSize.x = gridSizeF;
	textureSize.y = gridSizeF;

	textureSize.x /= 4;
	textureSize.y /= 4;

	//draw TileMap
	for (int y = fromY; y < toY; y++) {
		for (int x = fromX; x < toX; x++) {
			if (tileMap[y][x].idLv0 != 0) {
				/*
				tileMap[y][x].idLv0 = 0;
				initTile(tileMap[y][x].idLv0, y, x);
				*/
				tileMap[y][x].shapeLv0.setFillColor(Color::White);
				tileMap[y][x].shapeLv0.setOutlineThickness(0);
				tileMap[y][x].shapeLv0.setTexture(&tileTexture);
				tileMap[y][x].shapeLv0.setTextureRect(IntRect(64 * tileMap[y][x].coordLv0[0] * 5, 64 * tileMap[y][x].coordLv0[1], 64 * 5, 64 * 5));
			}

             window.draw(tileMap[y][x].shapeLv0);
		}
	}

}

void drawTileLv1(RenderWindow& window) {

	Vector2u textureSize;
	textureSize.x = gridSizeF;
	textureSize.y = gridSizeF;

	textureSize.x /= 4;
	textureSize.y /= 4;

	//draw TileMap
	for (int y = fromY; y < toY; y++) {
		for (int x = fromX; x < toX; x++) {
			if (tileMap[y][x].idLv1 != 0) {
				tileMap[y][x].shapeLv1.setFillColor(Color::White);
				tileMap[y][x].shapeLv1.setOutlineThickness(0);
				tileMap[y][x].shapeLv1.setTexture(&objectTexture);
				tileMap[y][x].shapeLv1.setTextureRect(IntRect(64 * tileMap[y][x].coordLv1[0] * 5, 64 * tileMap[y][x].coordLv1[1], 64 * 5, 64 * 5));
				window.draw(tileMap[y][x].shapeLv1);
			}

		}
	}
}

void initTileLv1(int max) {

	for (int y = 0; y < mapSize; y++) {
		for (int x = 0; x < mapSize; x++) {
			tileMap[y][x].shapeLv1.setSize(Vector2f(gridSizeF, gridSizeF));
			tileMap[y][x].shapeLv1.setPosition(Vector2f(x * gridSizeF, y * gridSizeF));
			/*
			tileMap[y][x].idLv1 = 0;
			initTile(tileMap[y][x].idLv1, y, x);
			*/
		}
	}
}
