#pragma once

void renderBox(RenderWindow& window);
void changeNum(Keyboard::Key key, short int& lv);

void renderBox(RenderWindow& window) {

	int sX = 600, sY = 300;

	RectangleShape backRect(Vector2f(sX, sY));
	backRect.setPosition(Vector2f(WINX / 2 - sX, WINY / 2 - sY / 2));
	backRect.setFillColor(Color::Black);
	backRect.setOutlineColor(Color::Yellow);
	backRect.setOutlineThickness(5);

	window.draw(backRect);

	Text text;
	text.setFont(font);
	text.setString("Inserisci id:");
	text.setCharacterSize(32);
	text.setPosition(Vector2f(backRect.getPosition().x + 25, backRect.getPosition().y + 25));
	window.draw(text);

	RectangleShape inputBox(Vector2f(sX - 100, 100));
	inputBox.setFillColor(Color::White);
	inputBox.setOutlineColor(Color(120, 120, 120));
	inputBox.setOutlineThickness(3);
	inputBox.setPosition(Vector2f(backRect.getPosition().x + (backRect.getSize().x -  inputBox.getSize().x) / 2, backRect.getPosition().y + 100));
	window.draw(inputBox);

	text.setString(to_string(inputId));
	text.setFillColor(Color::Black);
	text.setCharacterSize(52);
	text.setPosition(Vector2f(inputBox.getPosition().x + 25, backRect.getPosition().y + 120));
	window.draw(text);

	//actualid
	RectangleShape blockContainer(Vector2f(sY, sY));
	blockContainer.setPosition(Vector2f(backRect.getPosition().x + backRect.getSize().x + 50, backRect.getPosition().y));
	blockContainer.setFillColor(Color::Black);
	blockContainer.setOutlineColor(Color::Yellow);
	blockContainer.setOutlineThickness(3);
	window.draw(blockContainer);

	int margin = 40;
	RectangleShape blockPreview(Vector2f(sY - margin, sY - margin));
	blockPreview.setPosition(Vector2f(blockContainer.getPosition().x + margin / 2, blockContainer.getPosition().y + margin / 2));

	initTile(inputId, 0, 0, true);

	if (inputId >= 500) {
		blockPreview.setTexture(&objectTexture);
	}

	else {
		blockPreview.setTexture(&tileTexture);
	}
	blockPreview.setTextureRect(IntRect(64 * prevTile.coordLv0[0] * 5, 64 * prevTile.coordLv0[1] * 5, 64 * 5, 64 * 5));
	
	window.draw(blockPreview);


}

void changeNum(Keyboard::Key key, short int &lv) {

	if (key >= 48 && key <= 57) {
		int n = key - 48;

		inputId = inputId * 10 + n;
	}

	else if (key == 8) {
		inputId /= 10;
	}

	if (inputId > 999) {
		inputId = 0;
	}

	else {
		if (inputId >= 500) {
			lv = 1;
		}
		else {
			lv = 0;
		}
	}



}