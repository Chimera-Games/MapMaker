#pragma once

RectangleShape saveicon;
RectangleShape droppericon;
RectangleShape exiticon;

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

	if (mousePosScreen.x >= saveicon.getPosition().x && mousePosScreen.x <= saveicon.getPosition().x + s && mousePosScreen.y >= saveicon.getPosition().y && mousePosScreen.y <= saveicon.getPosition().y + s + margin) {
		saveicon.setOutlineThickness(3);
		saveicon.setOutlineColor(Color::Yellow);

	}

	else {
		saveicon.setOutlineThickness(0);
	}
	window.draw(saveicon);

	droppericon.setSize(saveicon.getSize());
	droppericon.setPosition(Vector2f(saveicon.getPosition().x , saveicon.getPosition().y + saveicon.getSize().y + margin * 2));
	droppericon.setTexture(&dropperTetxure);

	if (mousePosScreen.x >= droppericon.getPosition().x && mousePosScreen.x <= droppericon.getPosition().x + s && mousePosScreen.y >= droppericon.getPosition().y && mousePosScreen.y <= droppericon.getPosition().y + s + margin || dropper == true) {
		droppericon.setOutlineThickness(3);
		droppericon.setOutlineColor(Color::Yellow);
	}

	else {
		droppericon.setOutlineThickness(0);
	}


	window.draw(droppericon);


	//actualid
	RectangleShape blockContainer(Vector2f(s, s));
	blockContainer.setPosition(Vector2f(WINX - s - margin, WINY - (s + margin)*2));
	blockContainer.setFillColor(Color::Black);
	blockContainer.setOutlineColor(Color::Yellow);
	blockContainer.setOutlineThickness(3);
	window.draw(blockContainer);

	int marginPrev = 20;
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

	//exit
	exiticon.setSize(saveicon.getSize());
	exiticon.setPosition(Vector2f(blockContainer.getPosition().x, WINY - (s + margin)));
	exiticon.setTexture(&exitTexture);

	if (mousePosScreen.x >= exiticon.getPosition().x && mousePosScreen.x <= exiticon.getPosition().x + s && mousePosScreen.y >= exiticon.getPosition().y && mousePosScreen.y <= exiticon.getPosition().y + s + margin) {
		exiticon.setOutlineThickness(3);
		exiticon.setOutlineColor(Color::Yellow);
	}

	else {
		exiticon.setOutlineThickness(0);
	}



	window.draw(exiticon);

}