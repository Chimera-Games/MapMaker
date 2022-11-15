#pragma once

RectangleShape saveicon;
void saveDraw(RenderWindow& window);
void strumentalBar(RenderWindow& window);

void strumentalBar(RenderWindow& window) {

	int s = 150;

	RectangleShape bar(Vector2f(s, WINY));
	bar.setPosition(Vector2f(WINX - s, 0));
	bar.setFillColor(Color::Black);

	window.draw(bar);
	saveDraw(window);

}

void saveDraw(RenderWindow& window) {

	int s = 100;
	int margin = 25;
	saveicon.setSize(Vector2f(s, s));
	saveicon.setPosition(Vector2f(WINX - s - margin, margin));
	saveicon.setTexture(&saveTexture);

	if (mousePosScreen.x >= saveicon.getPosition().x && mousePosScreen.x <= saveicon.getPosition().x + s) {

		if (mousePosScreen.y >= saveicon.getPosition().y && mousePosScreen.y <= saveicon.getPosition().y + s + margin) {
			saveicon.setOutlineThickness(3);
			saveicon.setOutlineColor(Color::Yellow);
		}

	}

	else {
		saveicon.setOutlineThickness(0);
	}
	window.draw(saveicon);

	//actualid
	RectangleShape blockContainer(Vector2f(s, s));
	blockContainer.setPosition(Vector2f(WINX - s - margin, WINY - s * 2 - margin));
	blockContainer.setFillColor(Color::Black);
	blockContainer.setOutlineColor(Color::Yellow);
	blockContainer.setOutlineThickness(3);
	window.draw(blockContainer);

	int marginPrev = 40;
	RectangleShape blockPreview(Vector2f(s - marginPrev, s - marginPrev));
	blockPreview.setPosition(Vector2f(blockContainer.getPosition().x + marginPrev / 2, blockContainer.getPosition().y + marginPrev / 2));

	initTile(actualId, 0, 0, true);
	if (actualId >= 500) {
		blockPreview.setTexture(&objectTexture);
	}

	else {
		blockPreview.setTexture(&tileTexture);
	}
	blockPreview.setTextureRect(IntRect(64 * prevTile.coordLv0[0] * 5, 64 * prevTile.coordLv0[1] * 5, 64 * 5, 64 * 5));

	window.draw(blockPreview);

}