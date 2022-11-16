#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols
#include <iostream>
#include <sstream>
#include <time.h>
#include <thread>
#include <fstream>


using namespace std;
using namespace sf;




//funzioni
void selectTypeMove( View& view, Event event, float dt);
void mouseUpdate(RenderWindow& window, View& view);



//global values
double WINX = 1920.f, WINY = 1080.f;

//delta time per movimento
float dt = 0.f;

//speed
float speed=220.f;

//font
Font font;


struct Tile {

    unsigned int idLv0 = 0;
    unsigned int idLv1 = 0;

    RectangleShape shapeLv0;
    //coordinate per texture
    int coordLv0[2];

    RectangleShape shapeLv1;
    int coordLv1[2];

    //per inizializzazione progressiva cosí da non sovraccaricare il buffer
    bool initCheck = false;

};

Tile prevTile;




//size of a tile
float gridSizeF = 100.f;
unsigned gridSize = static_cast<unsigned>(gridSizeF);

const int mapSize = 250;
Tile tileMap[mapSize][mapSize];


//mouse variables 
Vector2i mousePosScreen; //mouse pos relative to monitor
Vector2i mousePosWindow; //mouse pos relative to game Window
Vector2f mousePosView;  //mouse pos relative to game view
Vector2u mousePosGrid;  //mouse pos relative to grid

//costanti per il rendering
int fromX = 0, toX = 0, fromY = 0, toY = 0;

//input id when in the box
int inputId = 0;

int actualId = 1;
short int actualLv = 0;

//game status
bool isPress = false;
bool selectId = false;
bool dropper = false;

Texture tileTexture;
Texture objectTexture;
Texture saveTexture;
Texture dropperTetxure;
Texture exitTexture;


#include "mapGen.h"
#include "UI.h"
#include "file.h"
#include "select.h"




int main()
{
    //game element
    Text text;
    Text tileStats;
    //Init Window
    unsigned short int frame = 144;
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned>(WINX), static_cast<unsigned>(WINY)), "MapMaker");
    window.setFramerateLimit(frame);
	//
	View view;
    view.setSize(WINX, WINY);
    //imposto la vista esattamente al centro
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    view.move(0, 0);

    if(!tileTexture.loadFromFile("./assets/tileTable.png")){
        cout << "Not loaded" << endl;
    }

	if (!objectTexture.loadFromFile("./assets/objectTable.png")) {
		cout << "Not loaded" << endl;
	}

    if (!saveTexture.loadFromFile("./assets/saveIcon.png")) {
        cout << "Not loaded" << endl;
    }

    if (!dropperTetxure.loadFromFile("./assets/dropperIcon.png")) {
        cout << "Not loaded" << endl;
    }

    if (!exitTexture.loadFromFile("./assets/exitIcon.png")) {
        cout << "Not loaded" << endl;
    }

    loadFromFile(mapSize);

    initTileLv0(mapSize);
    initTileLv1(mapSize);

	//clock di gioco per movimento
	Clock dtClock;


    Event event;


    font.loadFromFile("./assets/Dosis-Light.ttf");

	RectangleShape tileSelector(Vector2f(gridSizeF, gridSizeF));
	tileSelector.setFillColor(Color(255,0,0,125));



    while (window.isOpen()) {


		
        //Update game
        //Update dt
        dt = dtClock.restart().asSeconds();

        //Update game elements
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        //Update UI
		mouseUpdate(window, view);
        stringstream mouseTxt;
        mouseTxt << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
            << "ID LV 0: " << tileMap[mousePosGrid.y][mousePosGrid.x].idLv0 << "\n"
            << "ID LV 1: " << tileMap[mousePosGrid.y][mousePosGrid.x].idLv1 << "\n";

        stringstream tileTxt;
        tileTxt << "Actual id: " << actualId << "\n"
            << "Actual Lv: " << actualLv << "\n";

        tileStats.setString(tileTxt.str());
        tileStats.setFont(font);
        tileStats.setPosition(Vector2f(text.getPosition().x + 300, 0));

        text.setString(mouseTxt.str());
        text.setFont(font);

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (Event::KeyPressed && isPress == false) {
                
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    if (selectId) {
                        selectId = false;
                        if (inputId == 0) {
                            inputId = 1;
                        }
                        actualId = inputId;
                        inputId = 0;
                    }

                    else {
                        selectId = true;
                    }

                }

                isPress = true;

            }

            else if(Event::KeyReleased && isPress == true){
                isPress = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {

                if (selectId == false) {
                    actualId++;
                    if (actualId > 999) {
                        actualId = 999;
                    }
                    else if (actualId >= 500) {
                        actualLv = 1;
                    }
                    else {
                        actualLv = 0;
                    }
                }

                else {
                    inputId++;
                    if (inputId > 999) {
                        inputId = 999;
                    }
                }

            }

            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (selectId == false) {
                    actualId--;
                    if (actualId < 1) {
                        actualId = 1;
                    }
                    else if (actualId >= 500) {
                        actualLv = 1;
                    }
                    else {
                        actualLv = 0;
                    }
                }
                else {
                    inputId--;
                    if (inputId < 1) {
                        inputId = 1;
                    }
                }
            }

            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                inputId = 0;
                dropper = false;
                selectId = false;
            }
            
            if (selectId == true) {
                changeNum(event.key.code, actualLv);
            }

            else {

                if (Mouse::isButtonPressed && mousePosWindow.x <= WINX - 150) {
                    if (Mouse::isButtonPressed(Mouse::Right)) {
                        tileMap[mousePosGrid.y][mousePosGrid.x].idLv1 = 0;
                        initTile(tileMap[mousePosGrid.y][mousePosGrid.x].idLv1, mousePosGrid.y, mousePosGrid.x);
                    }

                    else if (Mouse::isButtonPressed(Mouse::Left)) {


                        if (dropper == true) {
                            if (tileMap[mousePosGrid.y][mousePosGrid.x].idLv1 != 0) {
                                actualId = tileMap[mousePosGrid.y][mousePosGrid.x].idLv1;
                                actualLv = 1;
                            }
                            else {
                                actualId = tileMap[mousePosGrid.y][mousePosGrid.x].idLv0;
                                actualLv = 0;
                            }
                            dropper = false;
                        }

                        else {
                            if (actualLv == 0) {
                                tileMap[mousePosGrid.y][mousePosGrid.x].idLv0 = actualId;
                                initTile(tileMap[mousePosGrid.y][mousePosGrid.x].idLv0, mousePosGrid.y, mousePosGrid.x);
                            }

                            else {
                                tileMap[mousePosGrid.y][mousePosGrid.x].idLv1 = actualId;
                                initTile(tileMap[mousePosGrid.y][mousePosGrid.x].idLv1, mousePosGrid.y, mousePosGrid.x);
                            }
                        }

                    }

                }

                //tools
                else if(Mouse::isButtonPressed){
                    if (Mouse::isButtonPressed(Mouse::Left)) {

                        if (mousePosScreen.x >= saveicon.getPosition().x && mousePosScreen.x <= saveicon.getPosition().x + 100 && mousePosScreen.y >= saveicon.getPosition().y && mousePosScreen.y <= saveicon.getPosition().y + 100 + 50) {
                            saveFile(mapSize);
                        }

                        else if (mousePosScreen.x >= droppericon.getPosition().x && mousePosScreen.x <= droppericon.getPosition().x + 100 && mousePosScreen.y >= droppericon.getPosition().y && mousePosScreen.y <= droppericon.getPosition().y + 100 + 50) {
                            dropper = true;
                        }

                        else if (mousePosScreen.x >= exiticon.getPosition().x && mousePosScreen.x <= exiticon.getPosition().x + 100 && mousePosScreen.y >= exiticon.getPosition().y && mousePosScreen.y <= exiticon.getPosition().y + 100 + 25) {
                            window.close();
                        }
                    }
                }

            }
        }

        if (selectId == false) {
            if (Keyboard::isKeyPressed(Keyboard::LShift)) {
                speed = 1800.f;
            }
            else {
                speed = 220.f;
            }

            if (Keyboard::isKeyPressed(Keyboard::LControl)) {
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    cout << "Salvato" << endl;
                    saveFile(mapSize);
                }
            }

            else {
                selectTypeMove(view, event, dt);
            }
        }


		updateRenderTiles(view, WINX / gridSizeF, WINY / gridSizeF);

        //cout << tileMap[mousePosGrid.x][mousePosGrid.y].idLv1 << endl;

		tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        window.clear();

		window.setView(view);

		//Debugging info
        //Update Mouse
        drawTileLv0(window);
        drawTileLv1(window);
		window.draw(tileSelector);



		window.setView(window.getDefaultView());
		
        window.draw(text);
        window.draw(tileStats);
        strumentalBar(window);

        if (selectId) {
            renderBox(window);
        }
        


        window.display();
    }


    return 0;
}


void selectTypeMove(View& view, Event event, float dt) {

    if (Keyboard::isKeyPressed(Keyboard::A)) {//Sinistra
        view.move(-speed * dt, 0.f);

    }

    else if (Keyboard::isKeyPressed(Keyboard::D)) {//Destra
        view.move(speed * dt, 0.f);

    }

    else if (Keyboard::isKeyPressed(Keyboard::W)) {//Sopra
        view.move(0.f, -speed * dt);

    }

    else if (Keyboard::isKeyPressed(Keyboard::S)) {//Sotto
        view.move(0.f, speed * dt);

    }

}

void mouseUpdate(RenderWindow& window, View& view) {

    //Update mouse position
    mousePosScreen = Mouse::getPosition();
    mousePosWindow = Mouse::getPosition(window);
    window.setView(view);
    mousePosView = window.mapPixelToCoords(mousePosWindow);
    if (mousePosView.x >= 0.f) {
        mousePosGrid.x = mousePosView.x / static_cast<unsigned>(gridSizeF);
    }
    if (mousePosView.y >= 0.f) {
        mousePosGrid.y = mousePosView.y / static_cast<unsigned>(gridSizeF);
    }
    window.setView(window.getDefaultView());

}
