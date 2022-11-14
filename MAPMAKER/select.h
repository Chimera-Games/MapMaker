#pragma once

void renderBox(RenderWindow& window);
void changeNum(Keyboard::Key key, short int& lv);

void renderBox(RenderWindow& window) {

	int sX = 600, sY = 300;

	RectangleShape backRect(Vector2f(sX, sY));
	backRect.setPosition(Vector2f(WINX / 2 - sX / 2, WINY / 2 - sY / 2));
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