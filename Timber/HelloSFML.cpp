// HelloSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    //Seting the widow
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    //Instantiating the background texture
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    //Instantiating tree texture
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    //Instantiating bee texture
    Texture textureBee;
    textureBee.loadFromFile("graphics/insect.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    bool beeActive = false;

    //bee speed
    float beeSpeed = 0.0f;

    //Instantiating cloud = texture
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    
    //Cloud speed
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    //Control time
    Clock clock;

    //Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    //Track if the game is running
    bool paused = true;

    //Draw some test
    int score = 0;
    Text messageText;
    Text scoreText;

    //Load font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Set the font to a message
    messageText.setFont(font);
    scoreText.setFont(font);

    //assign actual message
    messageText.setString("Press enter to start!");
    scoreText.setString("Score = 0");

    //Size character
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    //Set color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Position Text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;

            //Reset the time and the score
            score = 0;
            timeRemaining = 6;
        }
        
        if (!paused) {
            //Measur time
            Time dt = clock.restart();

            //Substract from the of time remaining
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond *
                timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                //pause the game
                paused = true;

                //change the message shown to the player
                messageText.setString("Out of time!!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            //Set up bee
            if (!beeActive) {

                //Set speed bee movement
                srand((int)time(0) * 10);
                beeSpeed = (rand() % 200) + 200;

                //Set hieght bee
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else {

                //Move the bee
                spriteBee.setPosition(
                    spriteBee.getPosition().x -
                    (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y);

                //Looking if the bee reached the edge
                if (spriteBee.getPosition().x < -100)
                {
                    //Desactivate the existance bee when reached de edge
                    beeActive = false;

                }
            }

            //setup cloud
            if (!cloud1Active) {

                //Set speed cloud movement
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                //Set hieght cloud
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;

            }
            else {

                //Move the bee
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x +
                    (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y);

                //Looking if the bee reached the edge
                if (spriteCloud1.getPosition().x > 1920)
                {
                    //Desactivate the existance bee when reached de edge
                    cloud1Active = false;

                }
            }

            if (!cloud2Active) {

                //Set speed cloud movement
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                //Set hieght cloud
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;

            }
            else {

                //Move the bee
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x +
                    (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y);

                //Looking if the bee reached the edge
                if (spriteCloud2.getPosition().x > 1920)
                {
                    //Desactivate the existance bee when reached de edge
                    cloud2Active = false;

                }
            }

            if (!cloud3Active) {

                //Set speed cloud movement
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                //Set hieght cloud
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;

            }
            else {

                //Move the bee
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x +
                    (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y);

                //Looking if the bee reached the edge
                if (spriteCloud3.getPosition().x > 1920)
                {
                    //Desactivate the existance bee when reached de edge
                    cloud3Active = false;

                }
            }

            //Update Score text
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        window.clear();

        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);

        window.draw(spriteBee);

        window.draw(scoreText);

        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
