#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<time.h>
#include<string>
#include<random>
#include<iomanip>
#include<vector>
#include<fstream>
#include<Windows.h>
#include"Menu.h"
#include<math.h>
#include<SFML/Window/Event.hpp>


using namespace std;
using namespace sf;

/*
**************************************************************
*      page number        *       fun                        *
**************************************************************
*       1000              *         mainmenu                 *
*        -1               *         close=Exit               *
*         0               *         Game_Play                *
*         1               *         instruction              *
*         2               *         Designers                *
*         3               *         Name player              *
**************************************************************
*      options            *          menu play               *
*         -1              *           Exit                   *
*          1              *          Restart                 *
*          2              *          Continue                *
*                         *                                  *
**************************************************************
*/

//workout  rounds
const int maxhealth = 6;
const int soundSize = 14;
const int soundsmallSize = 4;
struct Spells {
    int speed;
    int moveto;
    Sprite spellSprite;
    int spelleffect = 0;
    bool collideCheck = false;

};

struct players {

    float timershield;


    float Vx = 200, Vy = -14, IndexMultiplier = 1, accY = 5.3;
    int healthCharacter = 6;

    Sprite sprite1;

    bool isGrounded = true;

    int XOffset = 0;
    int numberplayer = -1;

    vector<Spells> spellsInst;
    int effect = -1;
    int index = -1;
    int directionspell;
    int spelltype = -1;
    float addspeed = 0.0;

    bool anotherspell = true;
    Clock spelltake;


    //sound for jump
    SoundBuffer jumpp;
    Sound jump;
    // sound 

    Spells sh;
    bool checktshield = false;
    bool shield_spell = false;
    int tshield = 0;
    //freeze declration
    int tfreeze = 0;
    //shield declration
    Clock tspell;


    //Constructor
    players() {

        //Define player 1

        player1.sprite1.setTextureRect(IntRect(0, 0, 32, 32));
        player1.sprite1.setScale(3, 3);
        player1.sprite1.setPosition(20, 950);

        //sound jump

        jumpp.loadFromFile("jump.wav");
        jump.setBuffer(jumpp);




        player2.sprite1.setTextureRect(IntRect(0, 0, 32, 32));
        player2.sprite1.setScale(3, 3);
        player2.sprite1.setPosition(1800, 950);

        //sound 
        jumpp.loadFromFile("jump.wav");
        jump.setBuffer(jumpp);

    };

    void movement(Time DeltaTime, bool& isGrounded) {

        //Player1 Horizontal movement
        if (Keyboard::isKeyPressed(Keyboard::D) && player1.sprite1.getPosition().x < 1840)
        {

            XOffset = ((int)IndexMultiplier % 3) * (32);
            player1.sprite1.setTextureRect(sf::IntRect(XOffset, 64, 30, 32));
            player1.sprite1.move(player1.Vx * DeltaTime.asSeconds(), 0);
            IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
            player1.directionspell = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A) && player1.sprite1.getPosition().x > -5)
        {
            XOffset = ((int)IndexMultiplier % 3) * (32);
            player1.sprite1.setTextureRect(sf::IntRect(XOffset, 32, 30, 32));
            player1.sprite1.move(-player1.Vx * DeltaTime.asSeconds(), 0);
            IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
            player1.directionspell = -1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player1.sprite1.setTextureRect(sf::IntRect(32, 0, 32, 32));
        }
        //Player 2 Horizontal movement
        if (Keyboard::isKeyPressed(Keyboard::Right) && player2.sprite1.getPosition().x < 1840)
        {
            XOffset = ((int)IndexMultiplier % 3) * (32);
            player2.sprite1.setTextureRect(sf::IntRect(XOffset, 64, 30, 32));
            player2.sprite1.move(player2.Vx * DeltaTime.asSeconds(), 0);
            IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
            player2.directionspell = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) && player2.sprite1.getPosition().x > -5)
        {
            XOffset = ((int)IndexMultiplier % 3) * (32);
            player2.sprite1.setTextureRect(sf::IntRect(XOffset, 32, 30, 32));
            player2.sprite1.move(-player2.Vx * DeltaTime.asSeconds(), 0);
            IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
            player2.directionspell = -1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player2.sprite1.setTextureRect(sf::IntRect(32, 0, 32, 32));
        }

        //Vertical movement of both players
        if (Keyboard::isKeyPressed(Keyboard::W) && player1.isGrounded) {
            player1.isGrounded = false;
            player1.sprite1.move(0, player1.Vy);
        }

        if (!player1.isGrounded) {
            player1.Vy += player1.accY * DeltaTime.asSeconds() * 4;
            player1.sprite1.move(0, player1.Vy);
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && player2.isGrounded) {
            player2.isGrounded = false;
            player2.sprite1.move(0, player2.Vy);
        }

        if (!player2.isGrounded) {
            player2.Vy += player2.accY * DeltaTime.asSeconds() * 4;
            player2.sprite1.move(0, player2.Vy);
        }
    }
    //Draw players
    void draw(RenderWindow& window) {
        window.draw(player1.sprite1);
        window.draw(player2.sprite1);
    }
}player1, player2;

struct Ground {
    Texture GroundTexture;
    Sprite GroundSprite;
    Ground() {
        ground.GroundTexture.loadFromFile("ground2.png");
        ground.GroundSprite.setTexture(ground.GroundTexture);
        ground.GroundSprite.setPosition(0, 1030);
        ground.GroundSprite.setColor(Color(0, 0, 0, 0));
        ground.GroundSprite.setScale(100, 2);
    }
    void Draw(RenderWindow& window) {
        window.draw(ground.GroundSprite);
    }
    bool operator==(const Ground& other) const
    {
        return false;
    }
}ground;

Clock timer;
int t1 = 0, t2 = 0, t3, t4, td = 0, ts = 0;
int r;
const int NBlocks = 11;
struct maps {
    Sprite background_sprite;
    Texture background_texture;

    Sprite ground_sprite;
    Sprite ground2;
    Texture ground_texture;


    Sprite gates_sprite[7];
    Texture gates_texture;

    Sprite blocks_sprite[NBlocks];
    Texture blocks_texture;
    Texture blocks2_texture;
    Texture blocks3_texture;
    Texture rocket_texture;

    Texture meteorTexture;

    Sprite branches[4];
    Texture branches_texture[3];


}mapp[6];

struct Enemy
{
    Sprite enemy_sprite;
    int speed;
    float animation = 0;
}enemy[6];

struct helpspells {
    Sprite dropspells;
    Sprite targetspells;
    int type;
    Clock clock1, clock2;

};

vector<helpspells>spellbag;
//Sprite spellbullet[6];
//Texture spellbullettex[6];
struct dragons
{
    int  vi;
    Sprite dragon_sprite;
    Texture dragon_tex;
    float animation = 0;
}Dragon[2];

Sprite spells[4];
Texture spellstex[20];
Texture enemy_tex;
//-------------------------------------------------------------maps functions---------------------------------------------------------//
void draw(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, int nblocks, Sprite blocks[]);
void gateslogic1(RenderWindow& w, Sprite gate[]);
void gateslogic2(RenderWindow& w, Sprite gate[]);
void gateslogic3(RenderWindow& w, Sprite gate[]);
void setBlockPositions1(Sprite blocks[]);
void setBlockPositions2(Sprite blocks[]);
void setBlockPositions3(Sprite blocks[]);
void preDrawing1(RenderWindow& w);
void preDrawing2(RenderWindow& w);
void preDrawing3(RenderWindow& w);
void preDrawing4(RenderWindow& w); //REham 
void dragonlogic(RenderWindow& w);// Reham 
void moveAndSwapBlocks(RenderWindow& w);
void preDrawing6(RenderWindow& w);
void enemy_things(RenderWindow& w, Sprite enemy_sprite);
void enemy_things2(RenderWindow& w, Sprite enemy_sprite);
void spellslogic6(RenderWindow& w);
void setBlockPositions6(Sprite blocks_sprite[]);
void draw3(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, Sprite blocks[], Sprite enemy_sprite);
void draw2(RenderWindow& w, Sprite back, Sprite ground, Sprite ground2, Sprite dragon1, Sprite dragon2, Sprite blocks[], int n);
//----------------------------------------
void setBlockPositions5(Sprite blocks[]);
void preDrawing5(RenderWindow& w);
void moveRocket(Vector2f targetPosition[], float speed, Time stopTime[], int& countrocket, int& randomrocket);
void updateMeteor(Vector2f startPos[], Vector2f endPos[], float& speed, float& rotationSpeed, float deltaTime[], float totalTime[], int randomMeteor[], int count, Clock& MeteorRepeatingTime);
void Meteordamage(RenderWindow& window, Vector2f endPos[], bool& shackdamage1, bool& shackdamage2, bool grounddamage[]);
void startNewMeteor(Vector2f startPos[], Vector2f endPos[], int randomMeteor[], int x);
void clocktime(RenderWindow& w, Clock& time1, int t[], Text time[], int& countr);
//----------------------------

void block_intersect2(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision);
void block_intersect(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision);
//-------------------------------------------------------------maps functions--------------------------------------------------------//


struct SoundManager {
    /*Music smain;  sound[0]
      Music map1;   sound[1]
      Music map2;   sound[2]
      Music map3;   sound[3]
      Music yousab; sound[4]
      Music assma;  sound[5]
      Music assma effect sound[6]
      music winner sound[7]
      music will typing sound[8]

      sound
      Music spell;  sound[10]
      Music spelll; sound[11]

      */

      /* SoundBuffer CLICK;
       SoundBuffer typingg;
       SoundBuffer randomm;*/


       //Sound click; sound_smal[0]
       //Sound typing;sound_smal[1]
       //Sound random;soundsmall[2]

    Music sound[soundSize];
    Sound sound_small[soundsmallSize];
    SoundBuffer soundbuffer[soundsmallSize];

    Texture unmutedTexture;
    Texture mutedTexture;
    Texture mutedTexture1;
    Texture mutedTexture2;
    Sprite unmuteSprite;
    Sprite muteSprite;
    Sprite muteSprite1;
    Sprite muteSprite2;
    int mutenumber = 0;
    int sound_value = 50;

    bool initialize() {
        if (!soundbuffer[2].loadFromFile("random.wav")) {
            cout << "ERROR: Can't load random menu.wav\n";
            return false;
        }
        sound_small[2].setBuffer(soundbuffer[2]);
        if (!soundbuffer[0].loadFromFile("clik.wav")) {
            cout << "ERROR: Can't load clik.wav\n";
            return false;
        }
        sound_small[0].setBuffer(soundbuffer[0]);
        if (!soundbuffer[1].loadFromFile("clik.wav"))
        {
            cout << "ERROR: Can't load typing.wav\n";
            return false;
        }
        sound_small[1].setBuffer(soundbuffer[1]);

        if (!sound[0].openFromFile("sound menu.wav")) {
            cout << "ERROR: Can't load sound menu.wav\n";
            return false;
        }
        if (!unmutedTexture.loadFromFile("unmute.png")) {
            cout << "ERROR: Can't load unmute.png\n";
            return false;
        }
        unmuteSprite.setTexture(unmutedTexture);
        unmuteSprite.setPosition(5, 20);
        unmuteSprite.scale(1.5, 1.5);
        if (!mutedTexture1.loadFromFile("mute2.png")) {
            cout << "ERROR: Can't load unmute.png\n";
            return false;
        }
        muteSprite1.setTexture(mutedTexture1);
        muteSprite1.setPosition(5, 20);
        muteSprite1.scale(1.5, 1.5);
        if (!mutedTexture2.loadFromFile("mute1.png"))
        {
            cout << "ERROR: Can't load unmute.png\n";
            return false;
        }
        muteSprite2.setTexture(mutedTexture2);
        muteSprite2.setPosition(5, 20);
        muteSprite2.scale(1.5, 1.5);

        if (!mutedTexture.loadFromFile("mute.png"))
        {
            cout << "ERROR: Can't load mute.png\n";
            return false;
        }
        muteSprite.setTexture(mutedTexture);
        muteSprite.setPosition(5, 20);
        muteSprite.scale(1.5, 1.5);
        if (!sound[1].openFromFile("egy map sound .wav"))
        {
            cout << "ERROR: Can't load egy map sound .wav\n";
            return false;
        }

        if (!sound[2].openFromFile("snow map spell.wav")) {
            cout << "ERROR: Can't load snow map spell.wav\n";
            return false;
        }

        if (!sound[3].openFromFile("lib sound map.wav")) {
            cout << "ERROR: Can't load lib sound map.wav\n";
            return false;
        }

        if (!sound[10].openFromFile("freeze.wav")) {
            cout << "ERROR: Can't load freeze.wav\n";
            return false;
        }
        if (!sound[11].openFromFile("damage spell.wav")) {
            cout << "ERROR: Can't load damage spell.wav\n";
            return false;
        }  if (!sound[4].openFromFile("Meteor map.wav"))
        {
            cout << "ERROR: Can't load egy map sound .wav\n";
            return false;
        }
        if (!sound[5].openFromFile("forest map.wav")) {
            cout << "ERROR: Can't load forest map.wav\n";
            return false;
        }
        if (!sound[6].openFromFile("Bats map.wav")) {
            cout << "ERROR: Can't load Bats map.wav\n";
            return false;
        }
        if (!sound[7].openFromFile("wimmers.wav")) {
            cout << "ERROR: Can't load wimmers.wav\n";
            return false;
        }
        if (!sound[8].openFromFile("while typing.wav")) {
            cout << "ERROR: Can't load while typing.wav\n";
            return false;
        }
        if (!sound[9].openFromFile("burn map.wav"))
        {
            cout << "ERROR: Can't load burn map .wav\n";
            return false;
        }
        if (!sound[12].openFromFile("Dragon map.wav"))
        {
            cout << "ERROR: Can't load Dragon map.wav\n";
            return false;
        }
        if (!sound[13].openFromFile("reh map.wav"))
        {
            cout << "ERROR: Can't load reh map.wav\n";
            return false;
        }

        return true;
    }


    void drawMuteIcon(RenderWindow& window)
    {
        if (sound_value == 0)
        {
            window.draw(muteSprite);
        }
        else if (sound_value > 0 && sound_value <= 30)
        {
            window.draw(muteSprite1);
        }
        else if (sound_value > 30 && sound_value <= 70)
        {
            window.draw(muteSprite2);
        }
        else
        {
            window.draw(unmuteSprite);
        }
    }
    void value()
    {
        for (int i = 0; i < soundSize; i++)
        {
            sound[i].setVolume(sound_value);
        }
        for (int i = 0; i < soundsmallSize; i++)
        {
            sound_small[i].setVolume(sound_value);
        }

    }
};
void handleEvents(RenderWindow& window, SoundManager& soundManager, Menu& menu, int& pagenum) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            break;
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) {
                menu.MoveUp();
                soundManager.sound_small[0].play();
            }
            if (event.key.code == Keyboard::Down) {
                menu.MoveDown();
                soundManager.sound_small[0].play();
            }
            if (event.key.code == Keyboard::Return) {
                if (menu.pressed() == 0) {
                    soundManager.sound[0].stop();
                    pagenum = 0;
                }
                if (menu.pressed() == 1) {
                    if (soundManager.mutenumber == 1) {
                        soundManager.sound[0].stop();
                    }
                    pagenum = 1;
                }
                if (menu.pressed() == 2) {
                    if (soundManager.mutenumber == 1) {
                        soundManager.sound[0].stop();
                    }
                    pagenum = 2;
                }
                if (menu.pressed() == 3) {
                    pagenum = -1;
                }
            }
        }

        if (event.type == Event::MouseMoved) {
            menu.checkMouseHover(window);
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left)
            {
                int selectedItemIndex = menu.getHoveredIndex(window);
                if (selectedItemIndex != -1 && selectedItemIndex == menu.pressed()) {
                    if (menu.pressed() == 0) {
                        soundManager.sound[0].stop();
                        pagenum = 0;
                    }
                    if (menu.pressed() == 1) {
                        if (soundManager.mutenumber == 1) {
                            soundManager.sound[0].stop();
                        }
                        pagenum = 1;
                    }
                    if (menu.pressed() == 2) {
                        if (soundManager.mutenumber == 1) {
                            soundManager.sound[0].stop();
                        }
                        pagenum = 2;
                    }
                    if (menu.pressed() == 3) {
                        pagenum = -1;
                    }
                }
            }
        }
    }
}
void drawMenu(RenderWindow& window, Menu& menu, SoundManager& soundManager, Sprite& bg)
{
    window.clear();
    window.draw(bg);
    menu.draw(window);
    soundManager.drawMuteIcon(window);
    window.display();
}


void effct1(RenderWindow& w);
void effct2(RenderWindow& w);
//--------------------------------------------------------
int Design(RenderWindow& window);
void numphoto_checkMouseHover(RenderWindow& window, RectangleShape Photo[], int& selectedOption);
int Game_Play(RenderWindow& window, int& mutenumber, SoundManager& soundManagerr);
int instruction(RenderWindow& window, SoundManager& soundManagerr);
void numplayer_checkMouseHover(RenderWindow& window, Sprite numplay[], int& selectedOption);
void sheckround_checkMouseHover(RenderWindow& window, Sprite round[], int& selectedOption);
void Name_player(RenderWindow& window, string& Pname1, string& Pname2, SoundManager& soundManagerr, int& maxround, int& level);
int playmenu(RenderWindow& window, int& mutenumber, SoundManager& soundManagerr);
void playmenu_checkMouseHover(RenderWindow& window, Text options[], int& selectedOption);
void Round(RenderWindow& window, int& Character1, int& Character2, int& rounds, int& maxround, bool& finish, string Pname1, string Pname2, SoundManager& soundManagerr);
//---------------------------------------------------------

void CheckCollision(bool&);

void spellentersect();
void checkspellplayer1();
void checkspellplayer2();
void restspeed1();
void restspeed2();

void drawHealth1(RenderWindow& window, Texture& healthTexture);
void drawHealth2(RenderWindow& window, Texture& healthTexture);
void choosespells(Sprite blocks, int = 1, int n = 80);
void choosespells_rocket(Sprite block);
void spellspeed();
void movespellbullet1();
void movespellbullet2();
void spelldefine();
void damagespell1();
void damagespell2();

void shieldspell(Vector2f endPos[], Sprite enemy_sprite);
void freezespell();

void lava(Sprite blocks[], Clock& clocklava, Clock& timelava, Clock& timelava2, int& lavarand);

//void FireBall(vector<Spells>& vectorSpells, RenderWindow& window);


RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);


int main() {
    SoundManager soundManagerr;
    if (!soundManagerr.initialize()) {
        system("pause");
        return -1;
    }

    int pagenum = 1000; // Index for choosing
    Menu menu(1920, 1080);
    Texture mainmenubg;
    if (!mainmenubg.loadFromFile("menu main.jpg")) {
        cout << "ERROR: Can't load menu main.jpg\n";
        system("pause");
        return -1;
    }
    Sprite bg;
    bg.setTexture(mainmenubg);


    soundManagerr.sound[0].play();
    while (true) {

        if (pagenum == 1000) {
            while (window.isOpen()) {
                handleEvents(window, soundManagerr, menu, pagenum);
                if (pagenum != 1000) {
                    break;
                }
                drawMenu(window, menu, soundManagerr, bg);
                soundManagerr.value();
            }
            if (pagenum == 0) {

                pagenum = Game_Play(window, soundManagerr.mutenumber, soundManagerr);
            }
            if (pagenum == -1) {
                window.close();
                break;
            }
            if (pagenum == 2) {
                pagenum = Design(window);
            }
            if (pagenum == 1) {
                pagenum = instruction(window, soundManagerr);
            }
            if (soundManagerr.mutenumber == 0 && pagenum == 1000) {
                soundManagerr.sound[0].play();
            }
            for (int i = 1; i < soundSize; i++)
            {
                soundManagerr.sound[i].stop();
            }
        }
    }

    return 0;
}

void numphoto_checkMouseHover(RenderWindow& window, RectangleShape numplay[], int& selectedOption)
{
    bool check = 0;
    for (int i = 0; i < 6; i++)
    {
        if (numplay[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
        {
            selectedOption = i;
            check = 1;
        }
    }
    if (check == 0)
    {
        selectedOption = -1;
    }

}

int Design(RenderWindow& window)
{
    Texture background;
    background.loadFromFile("Designers.jpg");  //background
    Sprite bg;
    bg.setTexture(background);
    Font font;
    font.loadFromFile("IZONERY Trial.otf");   //font
    Text t[8];
    for (int i = 0; i < 8; i++)
    {
        t[i].setFont(font);                           //language
        t[i].setCharacterSize(70);             //font size 
        t[i].setFillColor(Color::White);
        t[i].setPosition(620, (920));      //( X , Y)
    }
    t[0].setString("Taha Mustafa Abdel Fattah");
    t[1].setString("\t  Reham Maher Roshdy");
    t[2].setString("  Yousab Ashraf Makram");
    t[3].setString("Mohamed Sameh El-Sayed");
    t[4].setString("Asmaa Walid Sayed Moawad");
    t[5].setString("\tYoussef Khaled Hussein");
    t[6].setString("\tRana Mohamad Fattouh ");
    t[7].setString("It was developed by them");


    RectangleShape Photo[6];

    Photo[0].setPosition(70, 210.f);
    Photo[1].setPosition(380.f, 210.f);
    Photo[2].setPosition(690.f, 210.f);
    Photo[3].setPosition(1000.f, 210.f);
    Photo[4].setPosition(1310, 210.f);
    Photo[5].setPosition(1630.f, 210.f);
    for (int i = 0; i < 6; i++)
    {
        Photo[i].setSize(Vector2f(230, 660));
        Photo[i].setFillColor(Color::Green);
    }


    int numphoto = -1;
    int selectedOption = -1;
    int checkphoto = -1;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                return 1000; // ÇáÚæÏÉ Åáì ÇáÞÇÆãÉ
            }
        }
        if (event.type == Event::MouseMoved)
        {
            numphoto_checkMouseHover(window, Photo, selectedOption);
        }
        if (event.type == Event::MouseMoved)
        {
            for (int i = 0; i < 6; i++)
            {
                if (Photo[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    checkphoto = i;
                    break;
                }
            }
        }
        if (checkphoto == selectedOption)
        {
            numphoto = checkphoto;
        }
        else
        {
            numphoto = -1;
        }


        window.clear();
        window.draw(bg);   //background
        if (numphoto == -1)
        {
            window.draw(t[7]);
        }
        else
        {
            window.draw(t[numphoto]);
        }

        window.display();
    }
}


int instruction(RenderWindow& window, SoundManager& soundManagerr)
{
    Texture background;
    background.loadFromFile("instructions.png");  //background
    Sprite bg;
    Sprite KEY[9];
    Texture key[9];


    key[0].loadFromFile("W.png");
    key[1].loadFromFile("A.png");
    key[2].loadFromFile("D.png");
    key[3].loadFromFile("ctrl.png");
    key[4].loadFromFile("UP.png");
    key[5].loadFromFile("L.png");
    key[6].loadFromFile("R.png");
    key[7].loadFromFile("space.png");
    key[8].loadFromFile("sad.png");

    for (int i = 0; i < 4; i++)
    {
        KEY[i].setPosition(540, 240 + i * 100);

    }
    for (int i = 0; i < 3; i++)
    {
        KEY[i + 4].setPosition(1750, 250 + i * 100);

    }
    KEY[7].setPosition(1650, 420);
    KEY[8].setPosition(1780, 850);
    KEY[8].setScale(1.3, 1.3);

    for (int i = 0; i < 9; i++)
    {
        KEY[i].setTexture(key[i]);
    }
    bg.setTexture(background);
    Font font;
    font.loadFromFile("IZONERY Trial.otf");   //font
    Text t[12];
    for (int i = 3; i < 12; i++)
    {
        t[i].setFont(font);
        t[i].setCharacterSize(70);
        t[i].setFillColor(Color::White);
    }
    t[11].setCharacterSize(40);
    for (int i = 0; i < 3; i++)
    {
        t[i].setFont(font);
        t[i].setCharacterSize(70);
        t[i].setFillColor(Color::White);
    }
    for (int i = 1; i < 5; i++)
    {
        t[i + 2].setPosition(40, 150 + i * 100);
    }
    for (int i = 1; i < 5; i++)
    {
        t[i + 6].setPosition(1250, 150 + i * 100);
    }
    t[11].setPosition(1050, 800);

    t[0].setString("Instruction");
    t[1].setString("The First Player");
    t[2].setString("The Second Player");

    t[3].setString("MOVE UP");
    t[4].setString("MOVE LEFT");
    t[5].setString("MOVE RIGTH");
    t[6].setString("USE THE SPELL");

    t[7].setString("MOVE UP");
    t[8].setString("Move LEFT");
    t[9].setString("MOVE RIGTH");
    t[10].setString("USE THE SPELL");

    t[11].setString("When you obtain this, a random spell will be\n available to you that will either increase your\n power or deal damage to the other player.\n Each spell has a unique impact and differs\n from the others.");

    t[0].setPosition(770, 10);
    t[1].setPosition(60, 70);
    t[2].setPosition(1350, 70);

    Font fontnumbers;
    fontnumbers.loadFromFile("font numbers.ttf");
    std::vector<sf::CircleShape> points(101);
    float startX = 300.0f;
    float startY = 910.0f;
    float spacing = 3.0f;

    for (int i = 0; i < 101; ++i) {
        points[i] = CircleShape(10.0f);
        points[i].setFillColor(Color::White);
        points[i].setPosition(startX + i * spacing, startY);
    }
    CircleShape indicator(20.0f);
    indicator.setFillColor(Color::Green);
    indicator.setPosition(points[soundManagerr.sound_value].getPosition().x, points[soundManagerr.sound_value].getPosition().y - 10);
    int currentRound = -1;
    static int positionround = 50;
    bool isDragging = false;
    bool checkmuics = false;
    Text youssef;
    youssef.setFont(fontnumbers);
    youssef.setCharacterSize(70);
    youssef.setFillColor(Color::White);
    youssef.setPosition(700, 880);
    ostringstream s;

    Texture unmutedTexture;
    Texture mutedTexture;
    Texture mutedTexture1;
    Texture mutedTexture2;
    Sprite unmuteSprite;
    Sprite muteSprite;
    Sprite muteSprite1;
    Sprite muteSprite2;

    if (!unmutedTexture.loadFromFile("unmute.png")) {
        cout << "ERROR: Can't load unmute.png\n";
        return false;
    }
    unmuteSprite.setTexture(unmutedTexture);
    unmuteSprite.setPosition(50, 850);
    unmuteSprite.scale(1.5, 1.5);

    if (!mutedTexture1.loadFromFile("mute2.png")) {
        cout << "ERROR: Can't load unmute.png\n";
        return false;
    }
    muteSprite1.setTexture(mutedTexture1);
    muteSprite1.setPosition(50, 850);
    muteSprite1.scale(1.5, 1.5);

    if (!mutedTexture.loadFromFile("mute.png")) {
        cout << "ERROR: Can't load mute.png\n";
        return false;
    }
    muteSprite.setTexture(mutedTexture);
    muteSprite.setPosition(50, 850);
    muteSprite.scale(1.5, 1.5);

    if (!mutedTexture2.loadFromFile("mute1.png")) {
        cout << "ERROR: Can't load mute.png\n";
        return false;
    }
    muteSprite2.setTexture(mutedTexture2);
    muteSprite2.setPosition(50, 850);
    muteSprite2.scale(1.5, 1.5);



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return 1000;   //Return to menu
            }


        }
        if (event.type == Event::MouseButtonPressed) {
            if (indicator.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
            }
        }

        if (event.type == Event::MouseButtonReleased) {
            isDragging = false;
        }
        if (isDragging) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f worldPos = window.mapPixelToCoords(mousePos);

            if (worldPos.x >= startX && worldPos.x <= startX + 100 * spacing) {
                indicator.setPosition(worldPos.x, startY - 10);
            }
        }

        float minDistance = numeric_limits<float>::max();
        for (int i = 0; i <= 100; ++i) {
            float distance = abs(indicator.getPosition().x - points[i].getPosition().x);
            if (distance < minDistance)
            {
                minDistance = distance;
                positionround = i;
                soundManagerr.sound_value = positionround;
                soundManagerr.value();
                s.str("");
                s.clear();
                s << positionround;
                youssef.setString(s.str());
            }
        }
        window.clear();
        window.draw(bg);
        for (int i = 0; i < 9; i++)
        {
            window.draw(KEY[i]);
        }
        for (int i = 0; i < 12; i++)
        {
            window.draw(t[i]);
        }
        for (int i = 0; i < 101; i++)
        {
            window.draw(points[i]);
        }
        if (soundManagerr.sound_value == 0)
        {
            window.draw(muteSprite);
        }
        else if (soundManagerr.sound_value > 0 && soundManagerr.sound_value < 30)
        {
            window.draw(muteSprite1);
        }
        else if (soundManagerr.sound_value > 30 && soundManagerr.sound_value < 70)
        {
            window.draw(muteSprite2);
        }
        else
        {
            window.draw(unmuteSprite);
        }
        window.draw(youssef);
        window.draw(indicator);
        window.display();
    }
}

void sheckround_checkMouseHover(RenderWindow& window, Sprite round[], int& selectedOption)
{
    for (int i = 0; i < 4; i++)
    {
        if (round[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
        {
            selectedOption = i;
            round[i].setColor(Color::Green);
        }
        else
        {
            round[i].setColor(Color::White);
        }
    }
}
void numplayer_checkMouseHover(RenderWindow& window, Sprite numplay[], int& selectedOption)
{
    for (int i = 0; i < 4; i++)
    {
        if (numplay[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
        {
            selectedOption = i;
            numplay[i].setScale(4, 4);
        }
        else
        {
            numplay[i].setScale(3.5, 3.5);

        }
    }


}
void Name_player(RenderWindow& window, string& Pname1, string& Pname2, SoundManager& soundManagerr, int& maxround, int& level)
{
    level = 2;
    bool checkmusic = false;

    bool enter1 = true;
    bool enter2 = true;


    Texture background1, background2;
    background1.loadFromFile("VS.png");
    background2.loadFromFile("VS2.png");
    Sprite bg1, bg2;
    bg1.setTexture(background1);
    bg2.setTexture(background2);
    bg2.setPosition(390, -100);
    bg2.setScale(2, 2);

    Texture random;
    random.loadFromFile("random.png");
    Sprite ran[2];
    for (int i = 0; i < 2; i++)
    {
        ran[i].setTexture(random);
        ran[i].setPosition(600 + 1220 * i, 660);
        ran[i].setScale(0.3, 0.3);
    }



    Clock timerandom[2], endrandom[2];
    bool sheckrandom[2]{ 0,0 };
    int xrandom[2]{};

    Font font;
    font.loadFromFile("IZONERY Trial.otf");
    Text t[4];
    for (int i = 0; i < 4; i++)
    {
        t[i].setFont(font);
        t[i].setCharacterSize(70);
        t[i].setFillColor(Color::White);

    }
    t[0].setPosition(100, 400);
    t[1].setPosition(1330, 400);

    t[0].setString("Name First Player");
    t[1].setString("Name Second Player");

    Clock delay;

    Text cursor;
    cursor.setFont(font);
    cursor.setString("|");
    cursor.setCharacterSize(70);
    cursor.setFillColor(Color::White);

    Clock clock;
    bool showCursor = true;
    Time blinkTime = seconds(0.5f);



    Texture* numplayer1 = new Texture[4];
    Texture* numplayer2 = new Texture[4];
    Sprite* numplay1 = new Sprite[4];
    Sprite* numplay2 = new Sprite[4];


    int selectedOption1 = 0;
    int selectedOption2 = 0;
    player1.numberplayer = -1;
    player2.numberplayer = -1;

    numplayer1[0].loadFromFile("player1.png");
    numplayer1[1].loadFromFile("player2.png");
    numplayer1[2].loadFromFile("player3.png");
    numplayer1[3].loadFromFile("player4.png");
    numplayer2[0].loadFromFile("player1.png");
    numplayer2[1].loadFromFile("player2.png");
    numplayer2[2].loadFromFile("player3.png");
    numplayer2[3].loadFromFile("player4.png");

    for (int i = 0; i < 4; i++)
    {
        numplay1[i].setTexture(numplayer1[i]);
        numplay1[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
        numplay1[i].setScale(3.5, 3.5);
        numplay1[i].setPosition((i * 150) + 0, 650);

        numplay2[i].setTexture(numplayer2[i]);
        numplay2[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
        numplay2[i].setScale(3.5, 3.5);
        numplay2[i].setPosition((i * 150) + 1250, 650);
    }

    Font fontmaxround;
    fontmaxround.loadFromFile("font numbers.ttf");
    Text Maxround[3];
    Texture line;
    line.loadFromFile("line.png");
    Sprite Line;
    Line.setTexture(line);
    Line.setPosition(700, 903);
    Line.setScale(0.7, 0.7);


    int currentRound = -1;
    int positionround = 2;
    for (int i = 0; i < 3; i++)
    {

        Maxround[i].setFont(fontmaxround);
        Maxround[i].setCharacterSize(70);
        Maxround[i].setFillColor(Color::White);
        Maxround[i].setPosition(1000, 900);
    }
    Maxround[0].setString("Easy");
    Maxround[1].setString("medium");
    Maxround[2].setString("difficult");

    std::vector<sf::CircleShape> points(3);
    float startX = 700.0f;
    float startY = 910.0f;
    float spacing = 120.0f;

    for (int i = 0; i < 3; ++i) {
        points[i] = CircleShape(10.0f);
        points[i].setFillColor(Color::White);
        points[i].setPosition(startX + i * spacing, startY);
    }
    Texture Round[4];
    Round[0].loadFromFile("round1.png");
    Round[1].loadFromFile("round3.png");
    Round[2].loadFromFile("round5.png");
    Round[3].loadFromFile("infinity.png");
    Sprite round[4];
    for (int i = 0; i < 4; i++)
    {
        round[i].setTexture(Round[i]);
        round[i].setPosition(950 + i * 80, 800);
        round[i].setColor(Color::White);
        round[i].setScale(0.2, 0.2);
    }
    Text roundss;
    roundss.setFillColor(Color::White);
    roundss.setFont(fontmaxround);
    roundss.setCharacterSize(70);
    roundss.setPosition(700, 780);
    roundss.setString("Round:");
    int selectedOption3 = 0, numround = -1;
    bool sheckround = 1;
    CircleShape indicator(20.0f);
    indicator.setFillColor(Color::Green);
    indicator.setPosition(points[1].getPosition().x, points[1].getPosition().y - 10);

    bool isDragging = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                delete[] numplayer1;
                numplayer1 = NULL;
                delete[] numplay1;
                numplay1 = NULL;
                delete[] numplayer2;
                numplayer2 = NULL;
                delete[] numplay2;
                numplay2 = NULL;
                break;
            }
            if (event.type == Event::TextEntered)
            {

                if (enter1)
                {
                    if (Pname1.size() < 10)
                    {
                        soundManagerr.sound_small[1].play();
                        Pname1 += static_cast<char>(event.text.unicode);
                        ran[0].setPosition(600, 660);
                    }
                }
                else if (enter2 && delay.getElapsedTime().asSeconds() > 0.1)
                {
                    if (Pname2.size() < 10)
                    {
                        soundManagerr.sound_small[1].play();
                        Pname2 += static_cast<char>(event.text.unicode);
                        ran[1].setPosition(600 + 1220, 660);

                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                if (enter1 && Pname1.size() > 0)
                {
                    soundManagerr.sound_small[1].play();
                    Pname1.resize(Pname1.size() - 1);
                }
                else if (enter2 && Pname2.size() > 0)
                {
                    soundManagerr.sound_small[1].play();
                    Pname2.resize(Pname2.size() - 1);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && Pname1.size() > 1)
            {
                enter1 = false;
                delay.restart();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && Pname2.size() > 1)
            {
                enter2 = false;
            }
            if (!enter2 && !enter1 && player1.numberplayer != -1 && player2.numberplayer != -1 && maxround != 0)
            {
                return;
            }
            if (event.type == Event::MouseMoved && player1.numberplayer == -1 && !sheckrandom[0])
            {
                numplayer_checkMouseHover(window, numplay1, selectedOption1);
            }
            if (event.type == Event::MouseMoved && player2.numberplayer == -1 && !sheckrandom[1])
            {
                numplayer_checkMouseHover(window, numplay2, selectedOption2);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && player1.numberplayer == -1 && !sheckrandom[0])
            {
                for (int i = 0; i < 4; i++)
                {
                    if (numplay1[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        player1.numberplayer = i;
                        numplay1[i].setScale(3.5, 3.5);
                        break;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && player2.numberplayer == -1 && !sheckrandom[1])
            {
                for (int i = 0; i < 4; i++)
                {
                    if (numplay2[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        player2.numberplayer = i;
                        numplay2[i].setScale(3.5, 3.5);
                        break;
                    }
                }
            }
            if (player1.numberplayer == selectedOption1)
            {
                numplay1[player1.numberplayer].setTextureRect(IntRect(0, 0, 32, 32));
                player1.sprite1.setTexture(numplayer1[player1.numberplayer]);
                if (Pname1.size() < 1)
                {
                    ran[0].setPosition(500, 500);
                }


            }
            if (player2.numberplayer == selectedOption2)
            {
                numplay2[player2.numberplayer].setTextureRect(IntRect(0, 0, 32, 32));
                player2.sprite1.setTexture(numplayer2[player2.numberplayer]);
                if (Pname2.size() < 1)
                {
                    ran[1].setPosition(600 + 1100, 500);
                }
            }
            if (event.type == Event::MouseMoved && sheckround)
            {
                sheckround_checkMouseHover(window, round, selectedOption3);
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && sheckround)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (round[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        numround = i;
                        break;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !sheckround)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (round[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        round[i].setColor(Color::White);
                        sheckround = 1;
                        numround = -1;
                        maxround = 0;
                        break;
                    }
                }
            }
            if (numround == selectedOption3)
            {
                sheckround = 0;
                round[numround].setColor(Color::Green);
                if (numround == 0)
                {
                    maxround = 1;
                }
                else if (numround == 1)
                {
                    maxround = 3;
                }
                else if (numround == 2)
                {
                    maxround = 5;
                }
                else if (numround == 3)
                {
                    maxround = 100;
                }
            }
            if (enter1)
            {
                cursor.setPosition(280 - (Pname1.size() * 10) + (Pname1.size() * 35), 500);
            }
            else if (enter2)
            {
                cursor.setPosition(1580 - (Pname2.size() * 10) + (Pname2.size() * 35), 500);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (Maxround[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        positionround = i;
                        break;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (indicator.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    isDragging = true;
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                isDragging = false;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (ran[0].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && (player1.numberplayer != selectedOption1 || Pname1.size() < 1))
                {
                    ran[0].setColor(Color(255, 255, 255, 128));
                    timerandom[0].restart();
                    endrandom[0].restart();
                    sheckrandom[0] = 1;
                    checkmusic = 1;
                }
                if (ran[1].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && (player2.numberplayer != selectedOption2 || Pname2.size() < 1))
                {
                    ran[1].setColor(Color(255, 255, 255, 128));
                    timerandom[1].restart();
                    endrandom[1].restart();
                    sheckrandom[1] = 1;
                    checkmusic = 1;
                }
            }
        }
        t[2].setPosition(350 - (Pname1.size() * 20), 500);
        t[3].setPosition(1580 - (Pname2.size() * 20), 500);

        t[2].setString(Pname1);
        t[3].setString(Pname2);
        window.clear();
        window.draw(bg1);
        window.draw(bg2);
        for (int i = 0; i < 4; i++)
        {
            window.draw(t[i]);
        }
        if (player1.numberplayer == -1)
        {
            for (int i = 0; i < 4; i++)
            {
                window.draw(numplay1[i]);
            }
        }
        else
        {
            window.draw(numplay1[player1.numberplayer]);
            numplay1[player1.numberplayer].setPosition(280, 600);
        }
        if (player2.numberplayer == -1)
        {
            for (int i = 0; i < 4; i++)
            {
                window.draw(numplay2[i]);
            }
        }
        else
        {
            window.draw(numplay2[player2.numberplayer]);
            numplay2[player2.numberplayer].setPosition(1550, 600);
        }

        if (clock.getElapsedTime() >= blinkTime)
        {
            showCursor = !showCursor;
            clock.restart();
        }

        if (enter1 && showCursor)
        {
            cursor.setPosition(t[2].getPosition().x + t[2].getGlobalBounds().width + 5, t[2].getPosition().y);
            window.draw(cursor);
        }

        if (enter2 && showCursor && !enter1)
        {
            cursor.setPosition(t[3].getPosition().x + t[3].getGlobalBounds().width + 5, t[3].getPosition().y);
            window.draw(cursor);
        }

        if (isDragging) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f worldPos = window.mapPixelToCoords(mousePos);

            if (worldPos.x >= startX && worldPos.x <= startX + 2 * spacing) {
                indicator.setPosition(worldPos.x, startY - 10);
            }
        }

        float minDistance = numeric_limits<float>::max();
        for (int i = 0; i < 3; ++i) {
            float distance = abs(indicator.getPosition().x - points[i].getPosition().x);
            if (distance < minDistance) {
                minDistance = distance;
                positionround = i;
                if (positionround == 0)
                {
                    level = 1;
                }
                else if (positionround == 1)
                {
                    level = 2;
                }
                else if (positionround == 2)
                {
                    level = 3;
                }
            }
        }

        if (sheckrandom[0] && timerandom[0].getElapsedTime().asSeconds() > 0.1)
        {
            if (player1.numberplayer != selectedOption1)
            {
                enter1 = false;
                if (xrandom[0] > 0)
                {
                    numplay1[xrandom[0] - 1].setScale(3.5, 3.5);
                }
                if (xrandom[0] >= 4)
                {
                    xrandom[0] = 0;
                }
                if (checkmusic == 1)
                {
                    soundManagerr.sound_small[2].play();
                    checkmusic = 0;
                }
                numplay1[xrandom[0]].setScale(4, 4);
                xrandom[0]++;

                timerandom[0].restart();

                if (endrandom[0].getElapsedTime().asSeconds() > 5)
                {
                    sheckrandom[0] = 0;
                    enter1 = false;
                    selectedOption1 = rand() % 4;
                    player1.numberplayer = selectedOption1;
                    numplay1[player1.numberplayer].setTextureRect(IntRect(0, 0, 32, 32));
                    player1.sprite1.setTexture(numplayer1[player1.numberplayer]);
                    if (Pname1.size() < 1)
                    {
                        switch (selectedOption1)
                        {
                        case 0: Pname1 = "Harry"; break;
                        case 1: Pname1 = "Malfoy"; break;
                        case 2: Pname1 = "Hermione"; break;
                        default: Pname1 = "Snape"; break;
                        }
                    }
                }
            }
            else
            {
                enter1 = false;
                sheckrandom[0] = 0;
                if (Pname1.size() < 1)
                {
                    switch (selectedOption1)
                    {
                    case 0: Pname1 = "Harry"; break;
                    case 1: Pname1 = "Malfoy"; break;
                    case 2: Pname1 = "Hermione"; break;
                    default: Pname1 = "Snape"; break;
                    }
                }

            }
        }

        if (sheckrandom[1] && timerandom[1].getElapsedTime().asSeconds() > 0.1)
        {
            if (player2.numberplayer != selectedOption2)
            {
                enter2 = false;
                if (xrandom[1] > 0)
                {
                    numplay2[xrandom[1] - 1].setScale(3.5, 3.5);
                }
                if (xrandom[1] >= 4)
                {
                    xrandom[1] = 0;
                }
                if (checkmusic == 1)
                {
                    soundManagerr.sound_small[2].play();
                    checkmusic = 0;
                }
                numplay2[xrandom[1]].setScale(4, 4);
                xrandom[1]++;

                timerandom[1].restart();

                if (endrandom[1].getElapsedTime().asSeconds() > 5)
                {
                    sheckrandom[1] = 0;
                    enter2 = false;
                    selectedOption2 = rand() % 4;
                    player2.numberplayer = selectedOption2;
                    numplay2[player2.numberplayer].setTextureRect(IntRect(0, 0, 32, 32));
                    player2.sprite1.setTexture(numplayer2[player2.numberplayer]);

                    if (Pname2.size() < 1)
                    {
                        switch (selectedOption2)
                        {
                        case 0: Pname2 = "Harry"; break;
                        case 1: Pname2 = "Malfoy"; break;
                        case 2: Pname2 = "Hermione"; break;
                        default: Pname2 = "Snape"; break;
                        }
                    }
                }
            }
            else
            {
                enter2 = false;
                sheckrandom[1] = 0;
                if (Pname2.size() < 1)
                {
                    switch (selectedOption2)
                    {
                    case 0: Pname2 = "Harry"; break;
                    case 1: Pname2 = "Malfoy"; break;
                    case 2: Pname2 = "Hermione"; break;
                    default: Pname2 = "Snape"; break;
                    }
                }
            }
        }



        if ((player1.numberplayer == selectedOption1 && Pname1.size() > 0))
        {
            ran[0].setColor(Color(255, 255, 255, 128));
            ran[0].setPosition(600, 660);

        }
        else
        {
            ran[0].setColor(Color::White);
        }
        if ((player2.numberplayer == selectedOption2 && Pname2.size() > 0))
        {
            ran[1].setColor(Color(255, 255, 255, 128));
            ran[1].setPosition(600 + 1220, 660);
        }
        else
        {
            ran[1].setColor(Color::White);

        }
        window.draw(Line);
        window.draw(indicator);
        window.draw(ran[0]);
        window.draw(ran[1]);
        window.draw(Maxround[positionround]);
        for (int i = 0; i < 4; i++)
        {
            window.draw(round[i]);
        }
        window.draw(roundss);
        window.display();

    }


}

void playmenu_checkMouseHover(RenderWindow& window, Text options[], int& selectedOption)
{
    for (int i = 0; i < 4; i++)
    {
        if (options[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
        {
            selectedOption = i;
            options[selectedOption].setFillColor(Color::Green);
        }
        else
        {
            options[i].setFillColor(Color::White);
        }
    }
}
int playmenu(RenderWindow& window, int& mutenumber, SoundManager& soundManagerr)
{
    Texture background;
    background.loadFromFile("menu play.jpg");
    Sprite bg;
    bg.setTexture(background);
    bg.setColor(Color(255, 255, 255, 128));

    Font font;
    font.loadFromFile("IZONERY Trial.otf");

    Text options[4];

    int selectedOption = 0;

    options[0].setString("  Continue");
    options[1].setString("   Restart");
    options[2].setString("Instruction");
    options[3].setString("\t  Exit");

    for (int i = 0; i < 4; ++i)
    {
        options[i].setFont(font);
        options[i].setCharacterSize(120);
        options[i].setFillColor(Color::White);
        options[i].setPosition(750, 450 + (i * 140));
    }
    options[2].setCharacterSize(110);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    selectedOption = (selectedOption + 3) % 4;
                    soundManagerr.sound_small[0].play();
                }
                if (event.key.code == Keyboard::Down)
                {
                    selectedOption = (selectedOption + 1) % 4;
                    soundManagerr.sound_small[0].play();
                }
                if (mutenumber == 1)
                {
                    soundManagerr.sound_small[0].stop();
                }

                if (event.key.code == Keyboard::Enter)
                {
                    if (selectedOption == 0)
                    {
                        return 2;
                    }
                    if (selectedOption == 1)
                    {
                        return 1;
                    }
                    if (selectedOption == 2)
                    {
                        instruction(window, soundManagerr);
                    }
                    if (selectedOption == 3)
                    {
                        return -1;
                    }
                }

            }
            if (event.type == Event::MouseMoved)
            {
                playmenu_checkMouseHover(window, options, selectedOption);
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int hoveredOption = -1;
                for (int i = 0; i < 4; i++)
                {
                    if (options[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        hoveredOption = i;
                        break;
                    }
                }

                if (hoveredOption == selectedOption)
                {
                    if (selectedOption == 0)
                    {
                        return 2;
                    }
                    if (selectedOption == 1)
                    {
                        return 1;
                    }
                    if (selectedOption == 2)
                    {
                        instruction(window, soundManagerr);
                    }
                    if (selectedOption == 3)
                    {
                        return -1;
                    }
                }
            }
        }
        window.clear();
        window.draw(bg);
        for (int i = 0; i < 4; i++)
        {
            if (i == selectedOption)
            {
                options[i].setFillColor(Color::Green);
            }
            else
            {
                options[i].setFillColor(Color::White);
            }
            window.draw(options[i]);
        }
        window.display();
    }
}

void Round(RenderWindow& window, int& Character1, int& Character2, int& rounds, int& maxround, bool& finish, string Pname1, string Pname2, SoundManager& soundManagerr)
{


    Texture background;
    background.loadFromFile("Winnerr.jpg");
    Sprite bg;

    bg.setTexture(background);

    Font font;
    font.loadFromFile("IZONERY Trial.otf");   //font

    //name player



    Clock clock;

    Text t[2], winner;
    for (int i = 0; i < 2; i++)
    {
        t[i].setFont(font);
        t[i].setCharacterSize(150);
        t[i].setFillColor(Color::White);
    }

    t[0].setPosition(10, 1080 - 500);
    t[1].setPosition(1920 - 120 - Pname2.size() * 50, 1080 - 500);


    t[0].setString(Pname1);
    t[1].setString(Pname2);

    winner.setFont(font);
    winner.setCharacterSize(150);
    winner.setFillColor(Color::White);
    winner.setPosition(400, 300);


    int currentRound = rounds;
    int maxRounds = maxround;


    Font fontnumbers;
    fontnumbers.loadFromFile("font numbers.ttf");   //font

    Text roundText, score[2];
    roundText.setFont(fontnumbers);
    roundText.setCharacterSize(200);
    roundText.setFillColor(Color::White);
    roundText.setPosition(600, 300);

    for (int i = 0; i < 2; i++)
    {
        score[i].setFont(fontnumbers);
        score[i].setCharacterSize(200);
        score[i].setFillColor(Color::White);
    }

    score[0].setPosition(0 + (Pname1.size()) * 30, 800);
    score[1].setPosition(1800 - (Pname2.size()) * 30, 800);
    ostringstream ss2, ss3, ss1;
    ss2.str("");
    ss2.clear();
    ss2 << Character1;
    score[0].setString(ss2.str());
    ss3.str("");
    ss3.clear();
    ss3 << Character2;
    score[1].setString(ss3.str());




    ostringstream ss;
    ss << "Round " << currentRound;
    roundText.setString(ss.str());

    if (finish)
    {
        if (Character1 > Character2)
        {
            ss1 << "Winner is " << Pname1;
        }
        else if (Character1 < Character2)
        {
            ss1 << "Winner is " << Pname2;
        }
        else
        {
            ss1 << "They are equal in score";
            winner.setCharacterSize(120);
        }
        winner.setString(ss1.str());

        for (int i = 0; i < soundSize; i++)
        {
            soundManagerr.sound[i].stop();
        }
        soundManagerr.sound[7].play();

    }

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                window.close();
            }

            if ((event.key.code == Keyboard::Enter && clock.getElapsedTime().asSeconds() >= 0.1f && !finish))
            {
                clock.restart();
                return;
            }
            if ((event.key.code == Keyboard::Enter && clock.getElapsedTime().asSeconds() >= 0.1f && finish))
            {
                clock.restart();
                return;
            }
        }
        if (clock.getElapsedTime().asSeconds() >= 2.0f && !finish)
        {
            clock.restart();
            return;
        }
        if (clock.getElapsedTime().asSeconds() >= 5.0f && finish)
        {
            clock.restart();
            return;
        }
        window.clear();
        if (finish)
        {
            window.draw(bg);
            window.draw(t[0]);
            window.draw(t[1]);
            window.draw(score[0]);
            window.draw(score[1]);
            window.draw(winner);
        }
        else
        {
            window.draw(bg);
            window.draw(t[0]);
            window.draw(t[1]);
            window.draw(score[0]);
            window.draw(score[1]);
            window.draw(roundText);
        }


        window.display();
    }
}


int Game_Play(RenderWindow& window, int& mutenumber, SoundManager& soundManagerr)
{
    for (int i = 0; i < soundSize; i++)
    {
        soundManagerr.sound[0].stop();
    }
    soundManagerr.sound[8].play();
    //name player
    string Pname1;
    string Pname2;

    int maxround = 0;
    int level;
    Name_player(window, Pname1, Pname2, soundManagerr, maxround, level);
    soundManagerr.sound[0].stop();
    Font font;
    font.loadFromFile("IZONERY Trial.otf");
    Text nameplayer1, nameplayer2;
    nameplayer1.setFont(font);
    nameplayer1.setCharacterSize(60);
    nameplayer1.setFillColor(Color::White);
    nameplayer1.setPosition(150 - (Pname1.size()) * 14, 25);
    nameplayer1.setString(Pname1);
    nameplayer2.setFont(font);
    nameplayer2.setCharacterSize(60);
    nameplayer2.setFillColor(Color::White);
    nameplayer2.setPosition(1770 - (Pname1.size()) * 14, 25);
    nameplayer2.setString(Pname2);

    Font fontnumbers;
    fontnumbers.loadFromFile("font numbers.ttf");   //font

    Text score[2];
    ostringstream ss1, ss2;
    for (int i = 0; i < 2; i++)
    {
        score[i].setFont(fontnumbers);
        score[i].setCharacterSize(80);
        score[i].setFillColor(Color::White);
    }
    score[0].setPosition(300, 30);
    score[1].setPosition(1600, 30);


    //Clock yousab;
    Text timemapp[6];
    for (int i = 0; i < 6; i++)
    {
        timemapp[i].setFont(fontnumbers);
        timemapp[i].setCharacterSize(200);
        timemapp[i].setFillColor(Color::White);
    }
    timemapp[0].setPosition(1200, -50);
    timemapp[1].setPosition(1100, -50);
    timemapp[2].setPosition(950, -50);
    timemapp[3].setPosition(850, -50);
    timemapp[4].setPosition(700, -50);
    timemapp[5].setPosition(600, -50);



    //Gravity check
    bool isGrounded = false;
    int blockCollision1 = 0;
    int blockCollision2 = 0;

    //Time since last frame
    Clock deltaClock;
    Time deltaTime;


    //______________________________________
    for (int i = 0; i < soundSize - 4; i++)
    {
        soundManagerr.sound[i].setLoop(true);
        soundManagerr.sound[12].setLoop(true);
        soundManagerr.sound[13].setLoop(true);
    }
    //---------------------------------------

    //health
    Texture healthTexture;
    healthTexture.loadFromFile("health.png");
    int Character1 = 0;
    int Character2 = 0;

    /////lava//////
    Clock clocklava, timelava1, timelava2;
    int lavarand = 0;




    Vector2f targetPosition[2];
    float speed = 300.0f;
    float rotationSpeed = 90.0f;
    Time stopTime[2];
    stopTime[0] = seconds(1);
    stopTime[1] = seconds(1);
    int randrocket = -1;
    int countrocket = 0;
    Clock clockmeteor[5];
    int randompositionmeteor = 0;
    int randomMeteor[5] = { -2, -2, -2, -2, -2 };
    Vector2f startPos[5]{}, endPos[5]{};
    float totalTimemeteor[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    float speeds = 200; // Initial speed for each meteor
    float deltaTimeMeteor[5];
    Clock Meteorrepeatingtime;
    bool shackdamage1 = 0, shackdamage2 = 0;
    bool grounddamage[3] = { false };
    Clock time1;
    int secoundandminute[6] = {};
    Clock timeradd;

    //rounds
    int rounds = 0;
    bool finish = 0;
    int randommap = 0;
    int* random = new int[maxround];

    if (maxround <= 5)
    {
        if (level == 1)
        {
            random[0] = rand() % 3;

            if (maxround == 3)
            {
                if (random[0] < 3)
                {
                    random[1] = random[0] + 1;
                }
                else
                {
                    random[1] = 0;
                }
                random[2] = rand() % 3 + 3;
            }
            if (maxround == 5)
            {
                if (random[0] < 3)
                {
                    random[1] = random[0] + 1;
                }
                else
                {
                    random[1] = 0;
                }
                if (random[1] < 3)
                {
                    random[2] = random[1] + 1;
                }
                else
                {
                    random[2] = 0;
                }

                random[3] = rand() % 3 + 3;
                if (random[3] < 6)
                {
                    random[4] = random[3] + 1;
                }
                else
                {
                    random[4] = 3;
                }

            }
        }
        if (level == 2)
        {
            random[0] = rand() % 3;
            if (maxround == 3)
            {
                if (random[0] < 3)
                {
                    random[1] = random[0] + 1;
                }
                else
                {
                    random[1] = 0;
                }
                random[2] = rand() % 3 + 3;
                if (random[2] < 6)
                {
                    random[3] = random[2] + 1;
                }
                else
                {
                    random[3] = 3;
                }
            }
            if (maxround == 5)
            {
                if (random[0] < 3)
                {
                    random[1] = random[0] + 1;
                }
                else
                {
                    random[1] = 0;
                }
                random[2] = rand() % 3 + 3;
                if (random[2] < 6)
                {
                    random[3] = random[2] + 1;
                }
                else
                {
                    random[3] = 3;
                }
                if (random[3] < 6)
                {
                    random[4] = random[3] + 1;
                }
                else
                {
                    random[4] = 3;
                }

            }
        }
        if (level == 3)
        {
            random[0] = rand() % 3 + 3;
            for (int i = 1; i < maxround; i++)
            {
                if (random[i - 1] < 6)
                {
                    random[i] = random[i - 1] + 1;
                }
                else
                {
                    random[i] = 3;
                }
            }

        }
    }
    if (maxround > 10)
    {
        delete[]random;
        random = NULL;
    }

    Event event;
    window.setFramerateLimit(60);
    float angle1, angle2;
    angle1 = atan2f(player1.sprite1.getPosition().y, player1.sprite1.getPosition().x);
    window.setFramerateLimit(60);
    spelldefine();

    while (true)
    {
        int menuplay = 100;
        if (menuplay == 100)
        {
            while (window.isOpen())
            {
                deltaTime = deltaClock.restart();
                Event event;

                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed())
                    {
                        window.close();
                        delete[]random;
                        random = NULL;
                    }
                    if (event.key.code == Keyboard::Escape)
                    {
                        menuplay = playmenu(window, mutenumber, soundManagerr);
                        timeradd.restart();
                        deltaClock.restart();
                        clocklava.restart();
                        t1 = 0; t2 = 0; timer.restart();
                    }
                }
                /////////////

                /*if (yousab.getElapsedTime().asSeconds()>2)
                {
                    player1.healthCharacter--;
                    yousab.restart();
                }*/

                ///////////
                if (rounds == 0 || player1.healthCharacter <= 0 || player2.healthCharacter <= 0)
                {

                    if (maxround <= 5)
                    {
                        randommap = random[rounds];
                    }
                    else
                    {
                        if (level == 0)
                        {
                            randommap = rand() % 3;
                        }
                        else if (level == 1)
                        {
                            randommap = rand() % 6;
                        }
                        else
                        {
                            randommap = rand() % 3 + 3;
                        }
                    }
                 //  randommap = 3;
                    rounds++;
                    if (player1.healthCharacter <= 0)
                    {
                        Character2++;
                    }
                    if (player2.healthCharacter <= 0)
                    {
                        Character1++;
                    }
                    ss1.str("");
                    ss1.clear();
                    ss1 << Character1;
                    score[0].setString(ss1.str());

                    ss2.str("");
                    ss2.clear();
                    ss2 << Character2;
                    score[1].setString(ss2.str());

                    player1.healthCharacter = 6; player2.healthCharacter = 6;
                    if (randommap == 0)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[1].play();
                        preDrawing1(window);
                    }
                    if (randommap == 1)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[2].play();
                        preDrawing2(window);
                    }
                    if (randommap == 2)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[3].play();
                        preDrawing3(window);
                    }
                    if (randommap == 3)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[13].play();
                        soundManagerr.sound[9].play();
                        soundManagerr.sound[12].play();
                        preDrawing4(window);
                    }
                    if (randommap == 4)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[4].play();
                        preDrawing5(window);
                    }
                    if (randommap == 5)
                    {
                        for (int i = 1; i < soundSize - 3; i++)
                        {
                            soundManagerr.sound[i].stop();
                            soundManagerr.sound[12].stop();
                            soundManagerr.sound[13].stop();
                        }
                        soundManagerr.sound[5].play();
                        soundManagerr.sound[6].play();
                        preDrawing6(window);
                        enemy_things(window, enemy->enemy_sprite);
                    }


                    if (rounds <= maxround)
                    {

                        if (Character2 == maxround / 2 + 1 || Character1 == maxround / 2 + 1)
                        {
                            finish = 1;
                            rounds++;
                            Round(window, Character1, Character2, rounds, maxround, finish, Pname1, Pname2, soundManagerr);
                            return 1000;
                            delete[]random;
                            random = NULL;
                        }
                        else
                        {
                            player1.sprite1.setPosition(20, 850);
                            player1.sprite1.setTextureRect(IntRect(32, 0, 32, 32));
                            player2.sprite1.setPosition(1800, 850);
                            player2.sprite1.setTextureRect(IntRect(32, 0, 32, 32));
                            player1.addspeed = 0; player2.addspeed = 0;
                            player1.anotherspell = true; player2.anotherspell = true;
                            player1.checktshield = false; player2.checktshield = false; //shield spell
                            player1.shield_spell = false; player2.shield_spell = false; //shield spell
                            player1.index = -1; player2.index = -1; t1 = 0; t2 = 0; t3 = 0; t4 = 0;
                            lavarand = 0; rotationSpeed = 90; speeds = 200; Meteorrepeatingtime.getElapsedTime();
                            randrocket = -1; countrocket = 0;

                            shackdamage1 = false; shackdamage2 = false; grounddamage[0] = false; grounddamage[1] = false; grounddamage[2] = false;
                            for (int i = 0; i < 6; i++)
                            {
                                secoundandminute[i] = 0;
                                timemapp[i].setFillColor(Color::White);
                            }
                            for (int i = 0; i < 5; i++)
                            {
                                endPos[i] = Vector2f(-1000, -1000);
                                startPos[i] = Vector2f(-1000, -1000);
                            }
                            targetPosition[0] = Vector2f(-1000, 130);
                            targetPosition[1] = Vector2f(2200, 50);

                            for (int i = 0; i < player1.spellsInst.size(); i++)
                            {
                                player1.spellsInst.erase(player1.spellsInst.begin() + i);
                            }
                            for (int i = 0; i < player2.spellsInst.size(); i++)
                            {
                                player2.spellsInst.erase(player2.spellsInst.begin() + i);
                            }
                            while (true)
                            {
                                if (!spellbag.empty())
                                    spellbag.erase(spellbag.begin());
                                else
                                    break;
                            }

                            timeradd.restart();
                            deltaClock.restart();
                            t1 = 0; t2 = 0; timer.restart();
                            clocklava.restart();
                            Round(window, Character1, Character2, rounds, maxround, finish, Pname1, Pname2, soundManagerr);
                        }

                    }
                    else
                    {
                        finish = 1;
                        Round(window, Character1, Character2, rounds, maxround, finish, Pname1, Pname2, soundManagerr);
                        return 1000;
                        delete[]random;
                        random = NULL;
                    }
                }
                window.clear();

                if (randommap == 0)
                {
                    gateslogic1(window, mapp[0].gates_sprite);
                    block_intersect(mapp[0].blocks_sprite, mapp[0].ground_sprite, 10, 97, blockCollision1);
                    block_intersect2(mapp[0].blocks_sprite, mapp[0].ground_sprite, 10, 97, blockCollision2);
                    draw(window, mapp[0].background_sprite, mapp[0].ground_sprite, mapp[0].gates_sprite, 4, 10, mapp[0].blocks_sprite);
                }
                if (randommap == 1)
                {
                    gateslogic2(window, mapp[1].gates_sprite);
                    block_intersect(mapp[1].blocks_sprite, mapp[1].ground_sprite, 10, 97, blockCollision1);
                    block_intersect2(mapp[1].blocks_sprite, mapp[1].ground_sprite, 10, 97, blockCollision2);
                    draw(window, mapp[1].background_sprite, mapp[1].ground_sprite, mapp[1].gates_sprite, 4, 10, mapp[1].blocks_sprite);
                }
                if (randommap == 2)
                {
                    gateslogic3(window, mapp[2].gates_sprite);
                    block_intersect(mapp[2].blocks_sprite, mapp[2].ground_sprite, 10, 95, blockCollision1);
                    block_intersect2(mapp[2].blocks_sprite, mapp[2].ground_sprite, 10, 95, blockCollision2);
                    draw(window, mapp[2].background_sprite, mapp[2].ground_sprite, mapp[2].gates_sprite, 1, 10, mapp[2].blocks_sprite);
                }
                if (randommap == 3)
                {
                    int blockcollision = 0;
                    dragonlogic(window);
                    moveAndSwapBlocks(window);
                    block_intersect(mapp[3].blocks_sprite, mapp[3].ground2, 2, 97, blockcollision);
                    block_intersect2(mapp[3].blocks_sprite, mapp[3].ground_sprite, 2, 97, blockcollision);
                    if (!player1.isGrounded)
                    {
                        block_intersect(mapp[3].blocks_sprite, mapp[3].ground_sprite, 2, 97, blockcollision);
                    }
                    if (!player2.isGrounded)
                    {
                        block_intersect2(mapp[3].blocks_sprite, mapp[3].ground2, 2, 97, blockcollision);
                    }
                    draw2(window, mapp[3].background_sprite, mapp[3].ground_sprite, mapp[3].ground2, Dragon[0].dragon_sprite, Dragon[1].dragon_sprite, mapp[3].blocks_sprite, 3);
                }
                if (randommap == 4)
                {
                    if (randrocket == -1)
                    {
                        countrocket++;
                        randrocket = rand() % 2;
                    }
                    for (int i = 0; i < 5; i++) {
                        deltaTimeMeteor[i] = clockmeteor[i].restart().asSeconds();
                    }
                    block_intersect(mapp[4].blocks_sprite, mapp[4].ground_sprite, 10, 95, blockCollision1);
                    block_intersect2(mapp[4].blocks_sprite, mapp[4].ground_sprite, 10, 95, blockCollision2);
                    updateMeteor(startPos, endPos, speeds, rotationSpeed, deltaTimeMeteor, totalTimemeteor, randomMeteor, countrocket, Meteorrepeatingtime);
                    draw(window, mapp[4].background_sprite, mapp[4].ground_sprite, mapp[4].gates_sprite, 7, 11, mapp[4].blocks_sprite);
                    clocktime(window, time1, secoundandminute, timemapp, countrocket);
                    moveRocket(targetPosition, speed, stopTime, countrocket, randrocket);
                }
                if (randommap == 5)
                {
                    int blockcollision = 0;
                    enemy_things2(window, enemy->enemy_sprite);
                    block_intersect(mapp[5].blocks_sprite, mapp[5].ground_sprite, 10, 95, blockCollision1);
                    block_intersect2(mapp[5].blocks_sprite, mapp[5].ground_sprite, 10, 95, blockCollision2);
                    spellslogic6(window);

                    draw3(window, mapp[5].background_sprite, mapp[5].ground_sprite, mapp[5].gates_sprite, 1, mapp[5].blocks_sprite, enemy->enemy_sprite);

                }
                if (menuplay == -1)
                {
                    finish = 1;
                    Round(window, Character1, Character2, rounds, maxround, finish, Pname1, Pname2, soundManagerr);
                    return 1000;
                    delete[]random;
                    random = NULL;
                }
                if (menuplay == 1)
                {
                    Character1 = 0;
                    Character2 = 0;
                    rounds = 0;
                    break;
                }
                player1.draw(window);
                player2.draw(window);
                //CheckCollision(isGrounded);
                player1.movement(deltaTime, isGrounded);
                player2.movement(deltaTime, isGrounded);
                window.draw(nameplayer1);
                window.draw(nameplayer2);

                for (int i = 0; i < 2; i++)
                {
                    window.draw(score[i]);
                }


                movespellbullet1();
                movespellbullet2();
                spellspeed();


                if (player1.tspell.getElapsedTime().asSeconds() >= 1.0f) {
                    player1.tshield++;
                    player1.tfreeze++;
                    player1.tspell.restart();
                }
                if (player2.tspell.getElapsedTime().asSeconds() >= 1.0f) {
                    player2.tshield++;
                    player2.tfreeze++;
                    player2.tspell.restart();
                }

                if (player1.checktshield)
                {
                    player1.shield_spell = true;
                    shieldspell(endPos, enemy->enemy_sprite);
                    if (player1.tshield >= 20.0)
                    {
                        player1.tshield = 0;
                        player1.checktshield = false;
                        player1.shield_spell = false;
                        checkspellplayer1();
                    }
                }
                if (player2.checktshield)
                {
                    player2.shield_spell = true;
                    shieldspell(endPos, enemy->enemy_sprite);
                    if (player2.tshield >= 20.0)
                    {
                        player2.tshield = 0;
                        player2.checktshield = false;
                        player2.shield_spell = false;
                        checkspellplayer1();
                    }
                }



                drawHealth1(window, healthTexture);
                drawHealth2(window, healthTexture);

                spellentersect();
                //FireBall(spellsInst, window);

                restspeed1();
                restspeed2();

                if (Keyboard::isKeyPressed(Keyboard::LControl) && !player1.spellsInst.empty() && player1.index >= 0)
                {
                    soundManagerr.sound[10].play();
                    player1.spellsInst.back().spellSprite.setPosition(player1.sprite1.getPosition());
                    player1.spellsInst[player1.index].moveto = player1.directionspell;
                    player1.index--;
                    player1.anotherspell = true;
                    player1.spellsInst.back().collideCheck = true;
                    player1.spelltake.restart();
                    soundManagerr.sound[10].play();
                }
                if (Keyboard::isKeyPressed(Keyboard::Space) && !player2.spellsInst.empty() && player2.index >= 0)
                {
                    soundManagerr.sound[11].play();
                    player2.spellsInst.back().spellSprite.setPosition(player2.sprite1.getPosition());
                    player2.spellsInst.back().moveto = player2.directionspell;
                    player2.index--;
                    player2.spellsInst.back().collideCheck = true;
                    player2.anotherspell = true;
                    player2.spelltake.restart();
                    soundManagerr.sound[11].play();
                }
                checkspellplayer1();
                checkspellplayer2();
                effct1(window);
                effct2(window);
                damagespell2();
                damagespell1();
                if (randommap == 4)
                {
                    Meteordamage(window, endPos, shackdamage1, shackdamage2, grounddamage);
                }
                for (int i = 0; i < player1.spellsInst.size(); i++)
                {
                    window.draw(player1.spellsInst[i].spellSprite);
                }

                for (int i = 0; i < player2.spellsInst.size(); i++)
                {
                    window.draw(player2.spellsInst[i].spellSprite);
                }
                for (int i = 0; i < spellbag.size(); i++)
                {
                    window.draw(spellbag[i].dropspells);
                }




                //---------------------amendment----------------
                if (randommap != 4 && randommap != 3 && randommap != 5)
                {
                    lava(mapp[randommap].blocks_sprite, clocklava, timelava1, timelava2, lavarand);
                    if (lavarand == 0)
                    {
                        lavarand = rand() % NBlocks;
                    }
                }

                //---------------------amendment----------------
                ground.Draw(window);

                window.display();
            }
        }
    }
}


//setting the possetion of the blocks for  map1.
void setBlockPositions1(Sprite blocks[]) {
    for (int i = 0; i < 10; i++)
    {
        blocks[i].setScale(0.30, 0.50);
    }
    blocks[0].setPosition(320, 300);
    blocks[1].setPosition(620, 520);
    blocks[2].setPosition(250, 800);
    blocks[3].setPosition(1340, 800);
    blocks[4].setPosition(1000, 300);
    blocks[5].setPosition(950, 700);
    blocks[6].setPosition(1600, 300);
    blocks[7].setPosition(1600, 600);
    blocks[8].setPosition(10, 600);
    blocks[9].setPosition(650, 1080);
}
//setting the possetion of the blocks for  map2.
void setBlockPositions2(Sprite blocks_sprite[])
{

    blocks_sprite[2].setPosition(1016, 300);
    blocks_sprite[0].setPosition(300, 800);
    blocks_sprite[3].setPosition(1400, 800);

    blocks_sprite[6].setPosition(0, 630);
    blocks_sprite[1].setPosition(676, 630);
    blocks_sprite[4].setPosition(1660, 630);

    blocks_sprite[5].setPosition(430, 400);
    blocks_sprite[8].setPosition(1400, 400);


    blocks_sprite[7].setPosition(0, 200);
    blocks_sprite[9].setPosition(1660, 200);


}
//setting the possetion of the blocks for  map3.
void setBlockPositions3(Sprite blocks[]) {

    blocks[0].setPosition(830, 630);
    blocks[1].setPosition(10, 600);
    blocks[2].setPosition(1660, 600);
    blocks[3].setPosition(1300, 800);
    blocks[4].setPosition(430, 800);
    blocks[5].setPosition(1300, 400);
    blocks[6].setPosition(10, 200);
    blocks[7].setPosition(850, 210);
    blocks[8].setPosition(430, 400);
    blocks[9].setPosition(1660, 200);
    //blocks[10].setPosition(0, 1040);
}
//setting the possetion of the blocks for  map6.
void setBlockPositions5(Sprite blocks[]) {

    blocks[0].setPosition(10, 630);
    blocks[1].setPosition(830, 630);
    blocks[2].setPosition(1680, 630);
    blocks[3].setPosition(1300, 820);
    blocks[4].setPosition(350, 810);
    blocks[5].setPosition(1300, 450);
    blocks[6].setPosition(10, 250);
    blocks[7].setPosition(1000, 220);
    blocks[8].setPosition(380, 450);
    blocks[9].setPosition(1680, 250);
    blocks[10].setPosition(650, 220);

}




void moveAndSwapBlocks(RenderWindow& w) {



    //the long block
    static bool movingRight = true; // Track the direction of block movement
    static float speed = 2.0f; // Speed of the block movement
    static float leftBound = 400.0f; // Left boundary for the block
    static float rightBound = 1000.0f; // Right boundary for the block

    // Move the blocks
    if (movingRight) {
        mapp[3].blocks_sprite[1].move(speed, 0);
        if (mapp[3].blocks_sprite[1].getPosition().x >= rightBound) {
            movingRight = false;
        }
    }
    else {
        mapp[3].blocks_sprite[1].move(-speed, 0);
        if (mapp[3].blocks_sprite[1].getPosition().x <= leftBound) {
            movingRight = true;
        }
    }









}


//predrawing1 function that is a function set the texture to background, ground, gates and blocks for map1. "RAAAAAAAAAAna"
void preDrawing1(RenderWindow& w) {
    // background map1
    mapp[0].background_texture.loadFromFile(("Background finalllll.jpg"));
    mapp[0].background_sprite.setTexture(mapp[0].background_texture);

    // ground map1
    mapp[0].ground_texture.loadFromFile("groundffpng.png");
    mapp[0].ground_sprite.setTexture(mapp[0].ground_texture);
    mapp[0].ground_sprite.setPosition(-100, 1030);

    mapp[0].ground_sprite.setScale(3, .2);

    // gates
    mapp[0].gates_texture.loadFromFile("gatessprite.png");
    for (int i = 0; i < 4; ++i) {
        mapp[0].gates_sprite[i].setTexture(mapp[0].gates_texture);
        mapp[0].gates_sprite[i].setTextureRect(IntRect(0, 0, 144, 144));
        //mapp[0].gates_sprite[i].setPosition((i) * 565,-40);
        mapp[0].gates_sprite[i].setPosition(320 + (i * 340), -30);
        mapp[0].gates_sprite[i].setScale(1.5, 1.5);
    }

    // blocks
    mapp[0].blocks_texture.loadFromFile("blockk.png");
    for (int i = 0; i < 10; ++i) {
        mapp[0].blocks_sprite[i].setTexture(mapp[0].blocks_texture);
    }
    setBlockPositions1(mapp[0].blocks_sprite);


}
//predrawing2 function that is a function set the texture to background, ground, gates and blocks for map2  "Reham".
void preDrawing2(RenderWindow& w) {
    // background
    mapp[1].background_texture.loadFromFile("baaaa2.png");
    mapp[1].background_sprite.setTexture(mapp[1].background_texture);

    // ground
    mapp[1].ground_texture.loadFromFile("groundd.png");
    mapp[1].ground_sprite.setTexture(mapp[1].ground_texture);
    mapp[1].ground_sprite.setPosition(1, 1020);
    mapp[1].ground_sprite.setScale(3, 1);

    // gates
    mapp[1].gates_texture.loadFromFile("gatess2.png");
    for (int i = 0; i < 4; ++i) {
        mapp[1].gates_sprite[i].setTexture(mapp[1].gates_texture);
        mapp[1].gates_sprite[i].setTextureRect(IntRect(0, 0, 146, 96));
        mapp[1].gates_sprite[i].setPosition(300 + (i * 340), 0);
        mapp[1].gates_sprite[i].setScale(1.5, 1.5);
    }

    // blocks
    mapp[1].blocks_texture.loadFromFile("block2.png");
    for (int i = 0; i < 14; ++i) {
        mapp[1].blocks_sprite[i].setTexture(mapp[1].blocks_texture);

    }
    setBlockPositions2(mapp[1].blocks_sprite);
}
//predrawing3 function that is a function set the texture to background, ground, gates and blocks for map3.... made for ypu "Asmaa".
void preDrawing3(RenderWindow& w) {

    //ground_properties
    mapp[2].ground_texture.loadFromFile("group1.png");
    mapp[2].ground_sprite.setTexture(mapp[2].ground_texture);
    mapp[2].ground_sprite.setPosition(0, 1040);

    //back
    mapp[2].background_texture.loadFromFile("back (1).jpg");
    mapp[2].background_sprite.setTexture(mapp[2].background_texture);


    //gate
    mapp[2].gates_texture.loadFromFile("group 3.png");

    for (int i = 0; i < 1; i++) {
        mapp[2].gates_sprite[i].setTexture(mapp[2].gates_texture);
        mapp[2].gates_sprite[i].setPosition(0, 0);
    }


    //blocks

    mapp[2].blocks_texture.loadFromFile("Layergate2.png");
    for (int i = 0; i < 10; i++) {

        mapp[2].blocks_sprite[i].setTexture(mapp[2].blocks_texture);
        mapp[2].blocks_sprite[i].setScale(0.7, 0.7);

    }

    setBlockPositions3(mapp[2].blocks_sprite);

}
//predrawing3 function that is a function set the texture to background, ground, gates and blocks for map3.... made for ypu "Yousab".
void preDrawing4(RenderWindow& w)
{

    //mapp[3].background_texture.loadFromFile("backk4 (1).jpg");
    //mapp[3].background_texture.loadFromFile("_91eb4006-d27d-4081-b544-010c70ad261e (1).jpeg");

    // background
    mapp[3].background_texture.loadFromFile("_5047880d-598a-42aa-8040-7f363ddafbeb (1).jpeg");
    mapp[3].background_sprite.setTexture(mapp[3].background_texture);


    // ground
    mapp[3].ground_texture.loadFromFile("grounddd4 (1).PNG");
    mapp[3].ground_sprite.setTexture(mapp[3].ground_texture);
    mapp[3].ground2.setTexture(mapp[3].ground_texture);
    mapp[3].ground_sprite.setPosition(1, 833);
    mapp[3].ground2.setPosition(1381, 833);
    //	mapp[3].ground_sprite.setScale(1920, 500);




        // blocks 



    mapp[3].blocks_texture.loadFromFile("the black one (1).png");

    mapp[3].blocks2_texture.loadFromFile("the red one (1).png");

    mapp[3].blocks3_texture.loadFromFile("the black one (1) (1).png");



    mapp[3].blocks_sprite[0].setTexture(mapp[3].blocks_texture); //the first 2 blocks are black

    mapp[3].blocks_sprite[1].setTexture(mapp[3].blocks3_texture);

    mapp[3].blocks_sprite[2].setTexture(mapp[3].blocks2_texture); // the second 2 red





    mapp[3].blocks_sprite[2].setPosition(1, 400); //black
    mapp[3].blocks_sprite[0].setPosition(1413, 300);//red

    mapp[3].blocks_sprite[1].setPosition(350, 600);//blcak


    //mapp[3].blocks_sprite[1].setScale(1000,143);//blcak
    //cout << "the posetion of block [] :(  " << mapp[3].blocks_sprite[1].getPosition().x << ", " << mapp[3].blocks_sprite[1].getPosition().y << ")" << "\n";






    //dragons


    //setting tex and sprite for the dragon 
    for (int i = 0; i < 2; i++)
    {
        Dragon[i].dragon_tex.loadFromFile("dragon1.png");
        Dragon[i].dragon_sprite.setTexture(Dragon[i].dragon_tex);


    }

    //movement
    Dragon[0].vi = -3;
    Dragon[1].vi = 3;

    //0 right 1 left 
    Dragon[1].dragon_sprite.setPosition(-431, -70);    //(-280,-70)
    Dragon[0].dragon_sprite.setPosition(1930, -70);     //(1930,-70)
    Dragon[1].dragon_sprite.setTextureRect(IntRect(0, 0, 431, 318)); //left
    Dragon[0].dragon_sprite.setTextureRect(IntRect(431, 0, -431, 318)); //right

}

void preDrawing5(RenderWindow& w) {

    //ground_properties
    mapp[4].ground_texture.loadFromFile("block6.png");
    mapp[4].ground_sprite.setTexture(mapp[4].ground_texture);
    mapp[4].ground_sprite.setPosition(-150, 1040);
    mapp[4].ground_sprite.setScale(8, 1);

    //back
    mapp[4].background_texture.loadFromFile("map3.png");
    mapp[4].background_sprite.setTexture(mapp[4].background_texture);


    //gate
    mapp[4].gates_texture.loadFromFile("rocket1.png");
    mapp[4].rocket_texture.loadFromFile("rocket2.png");
    mapp[4].gates_sprite[0].setTexture(mapp[4].gates_texture);
    mapp[4].gates_sprite[1].setTexture(mapp[4].rocket_texture);
    mapp[4].gates_sprite[0].setPosition(2200, 50);
    mapp[4].gates_sprite[1].setPosition(-100, 150);
    for (int i = 0; i < 2; i++)
    {
        mapp[4].gates_sprite[i].setOrigin(mapp[4].gates_texture.getSize().x / 2, mapp[4].gates_texture.getSize().y / 2);
        mapp[4].gates_sprite[i].setRotation(-10 + 20 * i);
        mapp[4].gates_sprite[i].setScale(0.5, 0.5);
    }
    mapp[4].meteorTexture.loadFromFile("meteor.png");
    for (int i = 0; i < 5; i++)
    {
        mapp[4].gates_sprite[i + 2].setTexture(mapp[4].meteorTexture);
        mapp[4].gates_sprite[i].setOrigin(mapp[4].meteorTexture.getSize().x / 2, mapp[4].meteorTexture.getSize().y / 2);
        mapp[4].gates_sprite[i + 2].setPosition(-1000, -1000);
    }

    //blocks

    mapp[4].blocks_texture.loadFromFile("block6.png");
    for (int i = 0; i < 11; i++)
    {

        mapp[4].blocks_sprite[i].setTexture(mapp[4].blocks_texture);
        mapp[4].blocks_sprite[i].setScale(0.7, 0.7);

    }
    setBlockPositions5(mapp[4].blocks_sprite);
}

void preDrawing6(RenderWindow& w) {

    mapp[5].background_texture.loadFromFile(("back4.png"));
    mapp[5].background_sprite.setTexture(mapp[5].background_texture);



    mapp[5].ground_texture.loadFromFile("Group 1.png");
    mapp[5].ground_sprite.setTexture(mapp[5].ground_texture);
    mapp[5].ground_sprite.setPosition(0, 1050);


    mapp[5].blocks_sprite[4].setTexture(mapp[5].branches_texture[1]);
    mapp[5].blocks_sprite[5].setTexture(mapp[5].branches_texture[0]); //right
    mapp[5].branches_texture[2].loadFromFile("l up branch.png");
    mapp[5].blocks_sprite[6].setTexture(mapp[5].branches_texture[2]);

    mapp[5].blocks_texture.loadFromFile("Group 1b.png");
    for (int i = 0; i < 3; ++i) {
        mapp[5].blocks_sprite[i].setTexture(mapp[5].blocks_texture);
    }
    setBlockPositions6(mapp[5].blocks_sprite);


}
//moving blocks


void dragonlogic(RenderWindow& w) {

    static  bool check = 1;



    // Timer
    if ((int)timer.getElapsedTime().asSeconds() >= 1) {
        td++;
        check = 1;
        cout << "the timer now : " << td << endl;
        timer.restart();
    }


    // Dragon logic (unchanged)
    if (td >= 10) {
        for (int i = 0; i < 2; i++) {
            Dragon[i].animation += 0.1f;

            // 0 --> Right 
            if (i == 0) {
                // Movement
                Dragon[i].dragon_sprite.move(Dragon[i].vi, 0);

                // Animation
                Dragon[i].dragon_sprite.setTextureRect(IntRect(431 * int(Dragon[i].animation) + 431, 0, -431, 318));
                if (Dragon[i].animation > 2)
                    Dragon[i].animation = 0;
            }

            // 1 --> Left
            if (i == 1) {
                // Movement
                Dragon[i].dragon_sprite.move(Dragon[i].vi, 0);

                // Animation
                Dragon[i].dragon_sprite.setTextureRect(IntRect(431 * int(Dragon[i].animation), 0, 431, 318));
                if (Dragon[i].animation > 2)
                    Dragon[i].animation = 0;
            }
        }



        //if the player collid with the dragon helth--
 /*       if (player1.sprite1.getGlobalBounds().intersects(Dragon[0].dragon_sprite.getGlobalBounds()) || player1.sprite1.getGlobalBounds().intersects(Dragon[1].dragon_sprite.getGlobalBounds())) {

            player1.healthCharacter--;



        }

        if (player2.sprite1.getGlobalBounds().intersects(Dragon[0].dragon_sprite.getGlobalBounds()) || player2.sprite1.getGlobalBounds().intersects(Dragon[1].dragon_sprite.getGlobalBounds())) {

            player2.healthCharacter--;



        }

        */

 


        if (td == 12 && check == 1) {
            choosespells(mapp[3].blocks_sprite[0], 2, 1000);
            choosespells(mapp[3].blocks_sprite[2], 2, 1000);
            check = 0;
        }



        if (td == 20 && check == 1) {



            choosespells(mapp[3].ground_sprite, 2, 1000);
            choosespells(mapp[3].ground2, 2, 1000);
            check = 0;


        }


    }


    if (td == 23) {
        td = 0;
        Dragon[0].dragon_sprite.setPosition(1930, -70);
        Dragon[1].dragon_sprite.setPosition(-431, -70);
    }








}


//the logic of opening and closeing the gates of map1 for"RANA"
void gateslogic1(RenderWindow& w, Sprite gate[]) {


    r = rand() % 4;
    if ((int)timer.getElapsedTime().asSeconds() >= 1) {
        t1++;
        t2++;
        cout << "T1 : " << t1 << endl;
        timer.restart();
    }
    if (t1 >= 4)
    {
        for (int i = 0; i < 4; i++) {
            gate[r].setTextureRect(IntRect(0 * 144, i * 144, 144, 144));
        }
        if (r == 0) {
            choosespells(mapp[0].blocks_sprite[0]);
            cout << "Block 1" << endl;
        }
        if (r == 1) {
            choosespells(mapp[0].blocks_sprite[1]);
            cout << "Block 2 \n";
        }
        if (r == 2)
        {
            choosespells(mapp[0].blocks_sprite[5]);
            cout << "Block 3 \n";

        }

        if (r == 3)
        {
            choosespells(mapp[0].blocks_sprite[3]);
            cout << "Block 4\n";
        }
        t1 = 0;
        t2 = 0;
    }


    if (t2 >= 2) {
        gate[r].setTextureRect(IntRect(0 * 144, 0 * 144, 144, 144));

    }

}
//for the logic of gates 2 "Reham".
void gateslogic2(RenderWindow& w, Sprite gate[]) {


    int r = rand() % 4;
    if ((int)timer.getElapsedTime().asSeconds() >= 1)
    {
        t1++;
        t2++;

        cout << "the timer now : " << t1 << endl;

        timer.restart();
    }

    if (t1 >= 4) {

        for (int i = 0; i < 4; i++) {
            gate[r].setTextureRect(IntRect(0 * 144, i * 96, 144, 96));

        } // now there is a random gate open.

        if (r == 0) {
            choosespells(mapp[1].blocks_sprite[0]);
            cout << "Block 1" << endl;
        }
        if (r == 1) {
            choosespells(mapp[1].blocks_sprite[1]);
            cout << "Block 2 \n";
        }
        if (r == 2)
        {
            choosespells(mapp[1].blocks_sprite[2]);
            cout << "Block 3 \n";

        }

        if (r == 3)
        {
            choosespells(mapp[1].blocks_sprite[3]);
            cout << "Block 4\n";
        }
        t1 = 0;
        t2 = 0;
    }

    if (t2 >= 4) {
        // Close the gate after 4 seconds
        gate[r].setTextureRect(IntRect(0, 0, 144, 96)); // Assuming the closed gate texture is at index 0
        // Reset t2 to restart the cycle
    }
}
//the logic of opening and closeing the gates of map3...made for you "Asmaa".
void gateslogic3(RenderWindow& w, Sprite gate[]) {

    int r = rand() % 4;


    if (timer.getElapsedTime().asSeconds() >= 1) {
        t1++;
        t2++;
        timer.restart(); // to be sure the timer is between 0 & 1..so every second the t1 will increse 1.
    }  // to avoid time delaying


    if (t1 >= 4) {
        gate[0].setPosition(0, -20);
        //every 15 sec gate opens

        if (r == 0) {
            choosespells(mapp[2].blocks_sprite[0]);
            cout << "Block 1" << endl;
        }
        if (r == 1) {
            choosespells(mapp[2].blocks_sprite[1]);
            cout << "Block 2 \n";
        }
        if (r == 2)
        {
            choosespells(mapp[2].blocks_sprite[2]);
            cout << "Block 3 \n";

        }

        if (r == 3)
        {
            choosespells(mapp[2].blocks_sprite[3]);
            cout << "Block 4\n";
        }
        t1 = 0;
        t2 = 0;
    }

    if (t2 >= 4.0) {
        gate[0].setPosition(0, 0);
    }
}

//-------------------------------yousab----------mapp[4]-----------------------------//
void moveRocket(Vector2f targetPosition[], float speed, Time stopTime[], int& countrocket, int& randomrocket)
{
    static bool reachedTarget[2] = { true ,true };
    static bool stopped[2] = { true ,true };
    static Clock stopClock[2];
    static Clock clock[2];
    Time deltaTime[2] = { clock[0].restart(), clock[1].restart() };

    static Clock timer[2];
    if (countrocket > 7)
    {
        speed = 400;

        if (countrocket > 14)
        {
            speed = 500;
        }
        if (countrocket > 25)
        {
            speed = 700;
        }
    }
    if (static_cast<int>(timer[0].getElapsedTime().asSeconds()) >= 1)
    {
        if (randomrocket == 0 || countrocket > 5)
        {
            t1++;
        }
        else
        {
            t3++;
        }
        cout << "the timer1 now : " << t1 << endl;
        timer[0].restart();
    }
    if (static_cast<int>(timer[1].getElapsedTime().asSeconds()) >= 1 && countrocket > 7)
    {
        t3++;

        cout << "the timer2 now : " << t3 << endl;
        timer[1].restart();
    }
    if (randomrocket == 0 || countrocket > 5)
    {
        if (t1 >= 10 && mapp[4].gates_sprite[0].getPosition().x < 0)
        {
            mapp[4].gates_sprite[0].setPosition(2200, 50);
            t2 = rand() % 9;
            targetPosition[0] = Vector2f(mapp[4].blocks_sprite[t2].getPosition().x + 5, mapp[4].blocks_sprite[t2].getPosition().y - 40);
            reachedTarget[0] = false;
            stopped[0] = false;
            t1 = 0;
            randomrocket = -1;
        }
    }
    if (!reachedTarget[0])
    {
        sf::Vector2f direction = targetPosition[0] - mapp[4].gates_sprite[0].getPosition();
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > speed * deltaTime[0].asSeconds()) {
            direction /= distance; // ÇáÍÕæá Úáì ÇáæÍÏÉ ÇáÇÊÌÇåíÉ
            mapp[4].gates_sprite[0].move(direction * speed * deltaTime[0].asSeconds());
        }
        else {
            mapp[4].gates_sprite[0].setPosition(targetPosition[0]);
            reachedTarget[0] = true;
            stopClock[0].restart();
        }
    }
    else if (!stopped[0]) {
        if (stopClock[0].getElapsedTime() >= stopTime[0]) {
            stopped[0] = true;
            choosespells_rocket(mapp[4].blocks_sprite[t2]);
        }
    }
    else
    {
        if (t2 > 0) {
            mapp[4].gates_sprite[0].move(-speed * deltaTime[0].asSeconds(), -1);
        }
        else
            mapp[4].gates_sprite[0].move(-speed * deltaTime[0].asSeconds(), 0);
    }
    if (randomrocket == 1 || countrocket > 5)
    {
        if (t3 >= 10 && mapp[4].gates_sprite[1].getPosition().x > 2200)
        {
            mapp[4].gates_sprite[1].setPosition(-100, 50);
            t4 = rand() % 9;
            targetPosition[1] = Vector2f(mapp[4].blocks_sprite[t4].getPosition().x + 5, mapp[4].blocks_sprite[t4].getPosition().y - 75);
            reachedTarget[1] = false;
            stopped[1] = false;
            t3 = 0;
            randomrocket = -1;
        }
    }
    if (!reachedTarget[1])
    {
        Vector2f direction = targetPosition[1] - mapp[4].gates_sprite[1].getPosition();
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > speed * deltaTime[1].asSeconds()) {
            direction /= distance; // ÇáÍÕæá Úáì ÇáæÍÏÉ ÇáÇÊÌÇåíÉ
            mapp[4].gates_sprite[1].move(direction * speed * deltaTime[1].asSeconds());
        }
        else {
            mapp[4].gates_sprite[1].setPosition(targetPosition[1]);
            reachedTarget[1] = true;
            stopClock[1].restart();
        }
    }
    else if (!stopped[1]) {
        if (stopClock[1].getElapsedTime() >= stopTime[1])
        {
            stopped[1] = true;
            choosespells_rocket(mapp[4].blocks_sprite[t4]);
        }
    }
    else
    {
        if (t4 > 0)
        {
            mapp[4].gates_sprite[1].move(speed * deltaTime[1].asSeconds(), -1);
        }
        else
            mapp[4].gates_sprite[1].move(speed * deltaTime[1].asSeconds(), 0);
    }
}
void updateMeteor(Vector2f startPos[], Vector2f endPos[], float& speed, float& rotationSpeed, float deltaTime[], float totalTime[], int randomMeteor[], int count, Clock& MeteorRepeatingTime)
{
    // Increase the number of meteors and speed based on countrocket


    if (count < 7 && MeteorRepeatingTime.getElapsedTime().asSeconds() > 7.0f)
    {
        speed = 200;
        rotationSpeed = 100;
        int i = rand() % 5;
        startNewMeteor(startPos, endPos, randomMeteor, i);
        randomMeteor[i] = i;
        totalTime[i] = 0.0f;
        MeteorRepeatingTime.restart();
    }
    else if (count >= 7 && count <= 15 && MeteorRepeatingTime.getElapsedTime().asSeconds() > 8.0f)
    {
        speed = 250;
        rotationSpeed = 200;
        int x = rand() % 2;
        int i = rand() % 3 + 2;
        startNewMeteor(startPos, endPos, randomMeteor, x);
        startNewMeteor(startPos, endPos, randomMeteor, i);
        randomMeteor[x] = x; randomMeteor[i] = i;
        totalTime[x] = 0.0f; totalTime[i] = 0.0f;
        MeteorRepeatingTime.restart();
    }
    else if (count >= 15 && count <= 25 && MeteorRepeatingTime.getElapsedTime().asSeconds() > 9.0f)
    {
        rotationSpeed = 300;
        speed = 300;
        int i = rand() % 2;
        int j = 2;
        int k = rand() % 2 + 3;

        startNewMeteor(startPos, endPos, randomMeteor, i);
        randomMeteor[i] = i;
        totalTime[i] = 0.0f;
        startNewMeteor(startPos, endPos, randomMeteor, j);
        randomMeteor[j] = j;
        totalTime[j] = 0.0f;
        startNewMeteor(startPos, endPos, randomMeteor, k);
        randomMeteor[k] = k;
        totalTime[k] = 0.0f;
        MeteorRepeatingTime.restart();
    }
    if (count >= 25 && MeteorRepeatingTime.getElapsedTime().asSeconds() > 10.0f)
    {
        speed = 500;
        rotationSpeed = 400;
        for (int x = 0; x < 5; x++)
        {
            startNewMeteor(startPos, endPos, randomMeteor, x);
            randomMeteor[x] = x;
            totalTime[x] = 0.0f;
            MeteorRepeatingTime.restart();
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (randomMeteor[i] == i)
        {
            totalTime[i] += deltaTime[i];
            Vector2f currentPosition = startPos[i] + (endPos[i] - startPos[i]) * (totalTime[i] * speed / 800.0f);
            mapp[4].gates_sprite[i + 2].setPosition(currentPosition);
            mapp[4].gates_sprite[i + 2].rotate(rotationSpeed * deltaTime[i]);
        }
    }
}
void clocktime(RenderWindow& w, Clock& time1, int t[], Text time[], int& countr)
{
    static ostringstream s[6];
    static bool blink = false;
    static Color originalColor = Color::White;

    auto updateClock = [&]() {
        for (int i = 0; i < 6; i++) {
            s[i].str("");
            s[i].clear();
        }
        s[0] << t[0];
        s[1] << t[1];
        s[2] << t[2] << ":";
        s[3] << t[3];
        s[4] << t[4] << ":";
        s[5] << t[5];

        for (int i = 0; i < 6; i++) {
            time[i].setString(s[i].str());
        }
        };

    auto incrementTime = [&]() {
        t[0]++;
        if (t[0] >= 10) { t[0] = 0; t[1]++; }
        if (t[1] >= 6) { t[1] = 0; t[2]++; }
        if (t[2] >= 10) { t[2] = 0; t[3]++; }
        if (t[3] >= 6) { t[3] = 0; t[4]++; }
        if (t[4] >= 10) { t[4] = 0; t[5]++; }
        };

    if (countr == 7 || countr == 15 || countr == 25) {
        if (time1.getElapsedTime().asSeconds() > 0.1f) {
            blink = !blink;
            Color color = blink ? Color::Transparent : originalColor;
            for (int i = 0; i < 6; i++)
            {
                time[i].setFillColor(color);
            }
            time1.restart();
        }
    }
    else {
        float elapsedSeconds = time1.getElapsedTime().asSeconds();
        if ((elapsedSeconds > 0.6f && countr < 7) ||
            (elapsedSeconds > 0.2f && countr > 7 && countr < 15) ||
            (elapsedSeconds > 0.05f && countr < 25 && countr > 15) ||
            (elapsedSeconds > 0.005f && countr > 25))
        {

            if (countr > 15)
            {
                for (int i = 0; i < 6; i++)
                {
                    time[i].setFillColor(Color::Red);
                }
            }
            else {
                for (int i = 0; i < 6; i++) {
                    time[i].setFillColor(originalColor);
                }
            }

            incrementTime();
            updateClock();
            time1.restart();
        }
    }

    for (int i = 0; i < 6; i++) {
        w.draw(time[i]);
    }
}
void startNewMeteor(Vector2f startPos[], Vector2f endPos[], int randomMeteor[], int x)
{
    int randomPosition;
    switch (x)
    {
    case 0:
        randomPosition = rand() % 1000 + 800;
        startPos[x] = Vector2f(-50, -50); // From top
        endPos[x] = Vector2f(randomPosition, 1150); // To bottom
        break;
    case 1:
        randomPosition = rand() % 800;
        startPos[x] = Vector2f(2000, -50); // From top
        endPos[x] = Vector2f(randomPosition, 1150); // To bottom
        break;

    case 2:
        randomPosition = rand() % 1920;
        startPos[x] = Vector2f(randomPosition, -50); // From top
        endPos[x] = Vector2f(randomPosition, 1150); // To bottom
        break;
    case 3:
        randomPosition = rand() % 860;
        startPos[x] = Vector2f(-50, randomPosition); // From left
        endPos[x] = Vector2f(2000, randomPosition); // To right
        break;
    case 4:
        randomPosition = rand() % 860;
        startPos[x] = Vector2f(2000, randomPosition); // From right
        endPos[x] = Vector2f(-50, randomPosition); // To left
        break;
    default:
        break;
    }
}
void Meteordamage(RenderWindow& window, Vector2f endPos[], bool& shackdamage1, bool& shackdamage2, bool grounddamage[])
{
    static Texture meteordamage1, meteordamage2;
    static Sprite meteordamage[2], meteordamage3[3];

    static bool texturesLoaded = false;
    static int countdamage3[3] = { 1, 1, 1 };
    static Clock grounddamagetime1[3];
    static Clock damage1, damage2, damage3;
    static Clock Wdamage1, Wdamage2;
    static Clock damage2meteordamage, damage1meteordamage;
    static int countdamage1 = 0, countdamage2 = 0;
    if (!texturesLoaded)
    {
        if (!meteordamage1.loadFromFile("damage1.png")) {
            std::cerr << "Error loading damage1.png" << std::endl;
            system("pause");
            return;
        }
        if (!meteordamage2.loadFromFile("damage2.png")) {
            std::cerr << "Error loading damage2.png" << std::endl;
            return;
        }
        meteordamage[0].setTexture(meteordamage1);
        meteordamage[1].setTexture(meteordamage1);
        for (int i = 0; i < 3; i++)
        {
            meteordamage3[i].setTexture(meteordamage2);
            meteordamage3[i].setPosition(2000, 2000);
        }
        texturesLoaded = true;
    }

    for (int i = 0; i < 5; i++)
    {
        if (mapp[4].gates_sprite[i + 2].getGlobalBounds().intersects(player1.sprite1.getGlobalBounds()) && damage1.getElapsedTime().asSeconds() > 1.0f && !shackdamage1)
        {
            player1.healthCharacter--;
            endPos[i] = Vector2f(-2000, -2000);
            shackdamage1 = true;
            countdamage1 = 0;
            damage1.restart();
        }
        if (mapp[4].gates_sprite[i + 2].getGlobalBounds().intersects(player2.sprite1.getGlobalBounds()) && damage2.getElapsedTime().asSeconds() > 1.0f && !shackdamage2)
        {
            player2.healthCharacter--;
            endPos[i] = Vector2f(-2000, -2000);
            shackdamage2 = true;
            countdamage2 = 0;
            damage2.restart();
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (mapp[4].ground_sprite.getGlobalBounds().intersects(mapp[4].gates_sprite[i + 2].getGlobalBounds()))
        {
            grounddamage[i] = true;
            meteordamage3[i].setPosition(mapp[4].gates_sprite[i + 2].getPosition().x - 30, 920);
            endPos[i] = Vector2f(-2000, -2000);
        }
    }

    if (shackdamage1)
    {
        if (Wdamage1.getElapsedTime().asSeconds() > 0.5f)
        {
            if (countdamage1 == 0)
            {
                meteordamage[0].setTextureRect(IntRect(0, 0, 75, 118));
            }
            if (countdamage1 == 1)
            {
                meteordamage[0].setTextureRect(IntRect(179, 0, 93, 118));
            }
            if (countdamage1 == 2)
            {
                meteordamage[0].setTextureRect(IntRect(283, 0, 98, 118));
            }
            if (countdamage1 == 3)
            {
                meteordamage[0].setTextureRect(IntRect(283, 0, 112, 118));
            }
            if (countdamage1 == 4)
            {
                meteordamage[0].setTextureRect(IntRect(399, 0, 117, 118));
            }
            if (countdamage1 == 5)
            {
                meteordamage[0].setTextureRect(IntRect(530, 0, 122, 118));
            }
            countdamage1++;
            Wdamage1.restart();
            meteordamage[0].setPosition(player1.sprite1.getPosition().x, player1.sprite1.getPosition().y);
            window.draw(meteordamage[0]);
        }
        if (countdamage1 >= 6)
        {
            countdamage1 = 0;
            shackdamage1 = false;
        }
    }

    if (shackdamage2)
    {
        if (Wdamage2.getElapsedTime().asSeconds() > 0.5f)
        {
            if (countdamage2 == 0)
            {
                meteordamage[1].setTextureRect(IntRect(0, 0, 75, 118));
            }
            if (countdamage2 == 1)
            {
                meteordamage[1].setTextureRect(IntRect(179, 0, 93, 118));
            }
            if (countdamage2 == 2)
            {
                meteordamage[1].setTextureRect(IntRect(283, 0, 98, 118));
            }
            if (countdamage2 == 3)
            {
                meteordamage[1].setTextureRect(IntRect(283, 0, 112, 118));
            }
            if (countdamage2 == 4)
            {
                meteordamage[1].setTextureRect(IntRect(399, 0, 117, 118));
            }
            if (countdamage2 == 5)
            {
                meteordamage[1].setTextureRect(IntRect(530, 0, 122, 118));
            }
            countdamage2++;
            Wdamage2.restart();
            meteordamage[1].setPosition(player2.sprite1.getPosition().x, player2.sprite1.getPosition().y);
            window.draw(meteordamage[1]);
        }
        if (countdamage2 >= 6)
        {
            countdamage2 = 0;
            shackdamage2 = false;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (grounddamage[i])
        {
            if (grounddamagetime1[i].getElapsedTime().asSeconds() > 0.1f)
            {
                if (countdamage3[i] == 1)
                {
                    meteordamage3[i].setTextureRect(IntRect(523, 0, 64, 150));
                }
                if (countdamage3[i] == 2)
                {
                    meteordamage3[i].setTextureRect(IntRect(459, 0, 62, 150));
                }
                if (countdamage3[i] == 3)
                {
                    meteordamage3[i].setTextureRect(IntRect(394, 0, 62, 150));
                }
                else if (countdamage3[i] == 4)
                {
                    meteordamage3[i].setTextureRect(IntRect(335, 0, 54, 150));
                }
                else if (countdamage3[i] == 5)
                {
                    meteordamage3[i].setTextureRect(IntRect(285, 0, 48, 150));
                }
                else if (countdamage3[i] == 6)
                {
                    meteordamage3[i].setTextureRect(IntRect(238, 0, 44, 150));
                }
                else if (countdamage3[i] == 7)
                {
                    meteordamage3[i].setTextureRect(IntRect(187, 0, 48, 150));
                }
                else if (countdamage3[i] == 8)
                {
                    meteordamage3[i].setTextureRect(IntRect(138, 0, 46, 150));
                }
                else if (countdamage3[i] == 9)
                {
                    meteordamage3[i].setTextureRect(IntRect(97, 0, 38, 150));
                }
                else if (countdamage3[i] == 10)
                {
                    meteordamage3[i].setTextureRect(IntRect(62, 0, 30, 150));
                }
                else if (countdamage3[i] == 11)
                {
                    meteordamage3[i].setTextureRect(IntRect(29, 0, 29, 150));
                }
                countdamage3[i]++;
                grounddamagetime1[i].restart();
            }
            if (countdamage3[i] > 11)
            {
                countdamage3[i] = 1;
                grounddamage[i] = false;
                meteordamage3[i].setPosition(-1000, -1000);
            }
            window.draw(meteordamage3[i]);
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (player2.sprite1.getGlobalBounds().intersects(meteordamage3[j].getGlobalBounds()) && !shackdamage2)
        {
            player2.healthCharacter--;
            shackdamage2 = true;
            countdamage2 = 0;
            damage2meteordamage.restart();

        }
        if (player1.sprite1.getGlobalBounds().intersects(meteordamage3[j].getGlobalBounds()) && !shackdamage1)
        {
            player1.healthCharacter--;
            shackdamage1 = true;
            countdamage1 = 0;
            damage1meteordamage.restart();
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------//
//drawing the whole map function
void draw(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, int nblocks, Sprite blocks[]) {

    w.draw(back); //drawing background

    for (int i = 0; i < ngates; ++i) {
        w.draw(gates[i]); // Draw the gates
    }

    w.draw(ground); // drawing groud

    for (int i = 0; i < nblocks; ++i) {
        w.draw(blocks[i]); //drawing blocks
    }

}

void draw2(RenderWindow& w, Sprite back, Sprite ground, Sprite ground2, Sprite dragon1, Sprite dragon2, Sprite blocks[], int n) {

    w.draw(back); //drawing background

    w.draw(dragon1);
    w.draw(dragon2);


    w.draw(ground); // drawing groud
    w.draw(ground2); // drawing groud

    for (int i = 0; i < n; ++i) {
        w.draw(blocks[i]); //drawing blocks

    }





}

void enemy_things(RenderWindow& w, Sprite enemy_sprite) {
    if (!enemy_tex.loadFromFile("enemy.png")) {
        cerr << "Error loading enemy texture" << endl;
        return;
    }

    for (int i = 0; i < 6; i++) {
        enemy[i].enemy_sprite.setTexture(enemy_tex);
        enemy[i].speed = rand() % (10 - 8 + 1); // to make speed from 8 to 10
        int y = rand() % (1000 - 80 + 1);
        if (i < 3) {
            //setscale if they are too small
            enemy[i].enemy_sprite.setPosition(0, y);
            enemy[i].enemy_sprite.setTextureRect(IntRect(137, 0, -137, 97));
        }

        else {
            enemy[i].enemy_sprite.setPosition(1900, y);
            enemy[i].enemy_sprite.setTextureRect(IntRect(0, 0, 137, 97));
        }

    }



}

void enemy_things2(RenderWindow& w, Sprite enemy_sprite)
{
    for (int i = 0; i < 6; i++) {

        enemy[i].animation += 0.1;
        if (i < 3)
        {
            if (enemy[i].enemy_sprite.getPosition().x > 1920) {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(0, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (8 - 4 + 1) + 4;

            }
            enemy[i].enemy_sprite.move(enemy[i].speed, 0);
            if (player1.sprite1.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds())) {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(0, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (8 - 4 + 1) + 4;
                player1.healthCharacter--;
                //health --
            }
            if (player2.sprite1.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds())) {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(0, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (8 - 4 + 1) + 4;
                player2.healthCharacter--;
                //health --
            }

            enemy[i].enemy_sprite.setTextureRect(IntRect(144 * int(enemy[i].animation) + 137, 0, -144, 97));
            if (enemy[i].animation > 2)
            {
                enemy[i].animation = 0;
            }
            for (int j = 0; j < player1.spellsInst.size(); j++)
            {
                if (player1.spellsInst[j].spellSprite.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
                {
                    int y = rand() % (921) + 80;
                    enemy[i].enemy_sprite.setPosition(1900, y);
                    enemy[i].speed = rand() % (8 - 4 + 1) + 4;
                }
            }
            for (int j = 0; j < player2.spellsInst.size(); j++)
            {
                if (player2.spellsInst[j].spellSprite.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
                {
                    int y = rand() % (921) + 80;
                    enemy[i].enemy_sprite.setPosition(1900, y);
                    enemy[i].speed = rand() % (8 - 4 + 1) + 4;
                }
            }
        }
        else
        {
            if (enemy[i].enemy_sprite.getPosition().x < 0) {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(1900, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (15 - 8 + 1) + 8;

            }
            enemy[i].enemy_sprite.move(-enemy[i].speed, 0);
            if (player1.sprite1.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
            {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(1900, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                player1.healthCharacter--;
                //health --
            }
            if (player2.sprite1.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
            {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(1900, y); // these lines to return the enemy if out of limit
                enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                player2.healthCharacter--;
            }

            enemy[i].enemy_sprite.setTextureRect(IntRect(144 * int(enemy[i].animation), 0, 137, 97));
            if (enemy[i].animation > 2) {
                enemy[i].animation = 0;
            }
            for (int j = 0; j < player1.spellsInst.size(); j++)
            {
                if (player1.spellsInst[j].spellSprite.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
                {
                    int y = rand() % (921) + 80;
                    enemy[i].enemy_sprite.setPosition(0, y);
                    enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                }
            }
            for (int j = 0; j < player2.spellsInst.size(); j++)
            {
                if (player2.spellsInst[j].spellSprite.getGlobalBounds().intersects(enemy[i].enemy_sprite.getGlobalBounds()))
                {
                    int y = rand() % (921) + 80;
                    enemy[i].enemy_sprite.setPosition(0, y);
                    enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                }
            }
        }
    }//draw enemy sprite after clear
}

void spellslogic6(RenderWindow& w) {
    int r = rand() % 3;


    if (timer.getElapsedTime().asSeconds() >= 1) {
        ts++;
        cout << "ts== " << ts << "\n";
        timer.restart(); // to be sure the timer is between 0 & 1..so every second the t1 will increse 1.
    }  // to avoid time delaying


    if (ts >= 5) {


        if (r == 0) {
            choosespells(mapp[5].blocks_sprite[0], 0);
            cout << "Block 1" << endl;
        }
        if (r == 1) {
            choosespells(mapp[5].blocks_sprite[1], 0);
            cout << "Block 2 \n";
        }
        if (r == 2)
        {
            choosespells(mapp[5].blocks_sprite[2], 0);
            cout << "Block 3 \n";

        }


        ts = 0;

    }



}
void setBlockPositions6(Sprite blocks_sprite[]) {

    //blocks_sprite[0].setPosition(800, 269);
    blocks_sprite[0].setPosition(1300, 820);
    blocks_sprite[1].setPosition(300, 820);
    blocks_sprite[2].setPosition(820, 580);

    //int blocks 3
}
void draw3(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, Sprite blocks[], Sprite enemy_sprite) {

    w.draw(back); //drawing background

    //draw branches

    w.draw(ground); // drawing groud



    for (int i = 0; i < 3; ++i) {
        w.draw(blocks[i]); //drawing blocks

    }


    for (int i = 0; i < 6; i++) {
        w.draw(enemy[i].enemy_sprite);
    }


}


void drawHealth1(RenderWindow& window, Texture& healthTexture)
{

    Sprite healthbars[maxhealth];
    for (int i = 0; i < maxhealth; i++)
    {
        healthbars[i].setTexture(healthTexture);
        healthbars[i].setPosition(10 + i * 40, 100);
        healthbars[i].setScale(0.25, 0.2);

        if (i < player1.healthCharacter)
        {
            window.draw(healthbars[i]);
        }
    }
}
void drawHealth2(RenderWindow& window, Texture& healthTexture)
{
    Sprite healthbars[maxhealth];
    for (int i = 0; i < maxhealth; i++)
    {

        healthbars[i].setTexture(healthTexture);
        healthbars[i].setPosition(1840 - i * 40, 100);
        healthbars[i].setScale(0.25, 0.2);

        if (i < player2.healthCharacter)
        {
            window.draw(healthbars[i]);
        }
    }
}


void CheckCollision(bool& isGrounded){
    //Player 1 collision
    if (ground.GroundSprite.getGlobalBounds().intersects(player1.sprite1.getGlobalBounds())) {
        player1.isGrounded = true;
        player1.Vy = -14;
    }
    else {
        player1.isGrounded = false;
    }

    //Player 2 collision
    if (ground.GroundSprite.getGlobalBounds().intersects(player2.sprite1.getGlobalBounds())) {
        player2.isGrounded = true;
        player2.Vy = -14;
    }
    else {
        player2.isGrounded = false;
    }
}


void spelldefine()
{
    spellstex[0].loadFromFile("leaf.png");
    spellstex[1].loadFromFile("sad.png");
    spellstex[2].loadFromFile("egg.png");
    spellstex[3].loadFromFile("sad.png");
    spellstex[4].loadFromFile("lightning.png");
    spellstex[5].loadFromFile("Water.png");
    spellstex[6].loadFromFile("net.png");
    spellstex[7].loadFromFile("fair.png");
    spellstex[8].loadFromFile("shield 3.png");// for shield tex
    spellstex[9].loadFromFile("freeze sprite.png");  // freeze 


    for (int i = 0; i < 4; i++)
    {
        spells[i].setTexture(spellstex[i]);
        spells[i].setScale(0.8f, 0.8f);

        if (i == 2) {
            spells[i].setScale(0.2f, 0.2f);

        }
    }

}


void spellspeed()
{


    for (int i = 0; i < spellbag.size(); i++)
    {
        spellbag[i].dropspells.move(0, 3);
        if (spellbag[i].dropspells.getGlobalBounds().intersects(spellbag[i].targetspells.getGlobalBounds()))
        {
            spellbag[i].dropspells.move(0, -3);
        }

    }
}


void choosespells(Sprite block, int i, int m)
{


    int indexspells = rand() % 7;

    helpspells spell;
    spell.dropspells = spells[i]; //for the texture
    spell.targetspells = block;

    spell.dropspells.setPosition(spell.targetspells.getPosition().x + spell.dropspells.getScale().x * m, 80);

    spell.type = indexspells;

    spellbag.push_back(spell);
}
void choosespells_rocket(Sprite block) {


    int indexspells = rand() % 7;


    helpspells spell;
    spell.dropspells = spells[1];

    spell.targetspells = block;

    spell.dropspells.setPosition(spell.targetspells.getPosition().x + spell.dropspells.getScale().x * 80, spell.targetspells.getPosition().y - 80);

    spell.type = indexspells;

    spellbag.push_back(spell);
}


void restspeed1() {
    if (player1.addspeed <= 0)
    {
        player1.addspeed = 0;
        player1.Vx = 200;
        player1.sprite1.setColor(Color::White);
        player1.accY = 5.3;

    }
    else
    {
        player1.addspeed -= 0.01;
    }
}
void restspeed2() {
    if (player2.addspeed <= 0)
    {
        player2.addspeed = 0;
        player2.Vx = 200;
        player2.sprite1.setColor(Color::White);
        player2.accY = 5.3;
    }
    else
    {
        player2.addspeed -= 0.01;
    }
}

void checkspellplayer1()
{

    if (player1.spelltype == 0)
    {
        Spells lightning;
        lightning.spellSprite.setTexture(spellstex[4]);
        lightning.spellSprite.scale(0.5, 0.5);
        lightning.spellSprite.setPosition(50, 150);
        lightning.speed = 6;
        player1.spellsInst.push_back(lightning);
        player1.index++;
        player2.effect = 0;
    }
    else if (player1.spelltype == 1)
    {
        Spells FireBall;
        FireBall.spellSprite.setTexture(spellstex[7]);
        FireBall.speed = 6;
        FireBall.spellSprite.setPosition(50, 150);

        player1.spellsInst.push_back(FireBall);
        player1.index++;
        player2.effect = 1;
    }
    else if (player1.spelltype == 2)
    {
        Spells Water;
        Water.spellSprite.setTexture(spellstex[5]);
        Water.speed = 6;
        Water.spellSprite.setPosition(50, 150);

        player1.spellsInst.push_back(Water);
        player1.index++;
        player2.effect = 2;
    }
    else if (player1.spelltype == 3)
    {
        Spells freeze;
        freeze.spellSprite.setTexture(spellstex[9]);
        freeze.spellSprite.setScale(0.2, 0.2);
        freeze.speed = 6;
        freeze.spellSprite.setPosition(50, 150);
        freeze.spelleffect = 1;
        player1.spellsInst.push_back(freeze);


        player1.index++;
        player2.effect = 3;
    }
    else if (player1.spelltype == 4)
    {
        Spells Net;
        Net.spellSprite.setTexture(spellstex[6]);
        Net.speed = 6;
        Net.spellSprite.setPosition(50, 150);

        player1.spellsInst.push_back(Net);
        player1.index++;
        player2.effect = 4;
    }
    else if (player1.spelltype == 5) {
        player1.tshield = 0;
        player1.timershield = 8;
        player1.checktshield = true;
    }
    else if (player1.spelltype == 6)
    {
        player1.addspeed = 8;
        player1.Vx = 250;
        player1.sprite1.setColor(Color::White);
        player1.accY = 5.3;
    }
    player1.spelltype = -1;
}
void checkspellplayer2()
{

    if (player2.spelltype == 0)
    {
        Spells lightning;
        lightning.spellSprite.setTexture(spellstex[4]);
        lightning.spellSprite.scale(0.5, 0.5);
        lightning.spellSprite.setPosition(1800, 150);
        lightning.speed = 6;
        player2.spellsInst.push_back(lightning);
        player2.index++;
        player1.effect = 0;

    }
    else if (player2.spelltype == 1)
    {
        Spells FireBall;
        FireBall.spellSprite.setTexture(spellstex[7]);
        FireBall.speed = 6;
        FireBall.spellSprite.setPosition(1800, 150);
        player1.effect = 1;
        player2.spellsInst.push_back(FireBall);
        player2.index++;
    }
    else if (player2.spelltype == 2)
    {
        Spells Water;
        Water.spellSprite.setTexture(spellstex[5]);
        Water.speed = 6;
        Water.spellSprite.setPosition(1800, 150);
        player1.effect = 2;
        player2.spellsInst.push_back(Water);
        player2.index++;

    }
    else if (player2.spelltype == 3)
    {
        Spells freeze;
        freeze.spellSprite.setTexture(spellstex[9]);
        freeze.spellSprite.setScale(0.2, 0.2);
        freeze.speed = 6;
        freeze.spellSprite.setPosition(1800, 150);
        freeze.spelleffect = 1;
        player2.spellsInst.push_back(freeze);

        player1.effect = 3;
        player2.index++;

    }
    else if (player2.spelltype == 4)
    {
        Spells Net;
        Net.spellSprite.setTexture(spellstex[6]);
        Net.speed = 6;
        Net.spellSprite.setPosition(1800, 150);
        player1.effect = 4;
        player2.spellsInst.push_back(Net);
        player2.index++;
    }
    else if (player2.spelltype == 5)
    {
        player2.tshield = 0;
        player2.timershield = 8;
        player2.checktshield = true;
    }
    else if (player2.spelltype == 6)
    {
        player2.addspeed = 8;
        player2.Vx = 250;
        player2.sprite1.setColor(Color::White);
        player2.accY = 5.3;
    }
    player2.spelltype = -1;
}


void spellentersect()
{
    for (int i = 0; i < spellbag.size(); i++)
    {
        if (player1.sprite1.getGlobalBounds().intersects(spellbag[i].dropspells.getGlobalBounds()))
        {
            if (player1.anotherspell && player1.spelltake.getElapsedTime().asSeconds() >= 0.1f)
            {
                player1.spelltype = spellbag[i].type;
                spellbag.erase(spellbag.begin() + i);
                if (player1.spelltype != 6 && player1.spelltype != 5)
                {
                    player1.anotherspell = false;
                }
            }
        }

        else if (player2.sprite1.getGlobalBounds().intersects(spellbag[i].dropspells.getGlobalBounds()))
        {
            if (player2.anotherspell && player2.spelltake.getElapsedTime().asSeconds() >= 0.1f)
            {
                player2.spelltype = spellbag[i].type;
                spellbag.erase(spellbag.begin() + i);

                if (player2.spelltype != 6 && player2.spelltype != 5)
                {
                    player2.anotherspell = false;
                }
            }
        }
    }
}

void movespellbullet1() {

    for (int i = 0; i < player1.spellsInst.size(); i++)
    {

        if (player1.spellsInst[i].moveto == 1)
        {
            player1.spellsInst[i].spellSprite.move(3 * player1.spellsInst[i].speed, 0);
        }
        if (player1.spellsInst[i].moveto == -1)
        {
            player1.spellsInst[i].spellSprite.move(-3 * player1.spellsInst[i].speed, 0);
        }
        if (player1.spellsInst[i].spellSprite.getPosition().x > 2000 || player1.spellsInst[i].spellSprite.getPosition().x < -10)
        {
            player1.spellsInst.erase(player1.spellsInst.begin() + i);

        }

    }
}
void movespellbullet2() {

    for (int i = 0; i < player2.spellsInst.size(); i++)
    {

        if (player2.spellsInst[i].moveto == 1)
        {
            player2.spellsInst[i].spellSprite.move(3 * player2.spellsInst[i].speed, 0);
        }
        if (player2.spellsInst[i].moveto == -1)
        {
            player2.spellsInst[i].spellSprite.move(-3 * player2.spellsInst[i].speed, 0);
        }

        if (player2.spellsInst[i].spellSprite.getPosition().x > 2000 || player2.spellsInst[i].spellSprite.getPosition().x < -10)
        {
            player2.spellsInst.erase(player2.spellsInst.begin() + i);

        }

    }
}

void damagespell1() {
    for (int i = 0; i < player1.spellsInst.size(); i++)
    {
        if (player2.sprite1.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()) && player1.spellsInst[i].collideCheck)
        {
            player2.healthCharacter--;

            if (player1.spellsInst[i].spelleffect == 1)
                freezespell();


            player1.spellsInst.erase(player1.spellsInst.begin() + i);

        }






    }
}
void damagespell2() {
    for (int i = 0; i < player2.spellsInst.size(); i++)
    {
        if (player1.sprite1.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()) && player2.spellsInst[i].collideCheck)
        {
            player1.healthCharacter--;

            if (player2.spellsInst[i].spelleffect == 1) {
                freezespell();
            }


            player2.spellsInst.erase(player2.spellsInst.begin() + i);

        }


    }
}

void freezespell() {
    Color freezeffect(0, 0, 255, 128);


    for (int i = 0; i < player2.spellsInst.size(); i++)
    {
        if (player1.sprite1.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()) && player2.spellsInst[i].collideCheck)
        {

            player1.sprite1.setColor(freezeffect);
            //player2.spellsInst.erase(player2.spellsInst.begin() + i);
            player2.spellsInst[i].spelleffect = 0;
            player1.addspeed = 8;
            player1.Vx = 20;
            player1.accY = 12;
        }
    }


    for (int i = 0; i < player1.spellsInst.size(); i++)
    {
        if (player2.sprite1.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()) && player1.spellsInst[i].collideCheck)
        {

            player2.sprite1.setColor(freezeffect);
            player1.spellsInst[i].spelleffect = 0;
            player2.addspeed = 8;
            player2.Vx = 20;
            player2.accY = 12;
            //player1.spellsInst.erase(player1.spellsInst.begin() + i);
        }

    }


}
void shieldspell(Vector2f endPos[], Sprite enemy_sprite)
{
    if (player1.shield_spell)
    {
        player1.sh.spellSprite.setTexture(spellstex[8]);
        player1.sh.spellSprite.setTextureRect(IntRect(0, 0, 1200, 1200));
        player1.sh.spellSprite.setScale(0.2, 0.2);
        player1.sh.spellSprite.setPosition(player1.sprite1.getPosition().x - 70, player1.sprite1.getPosition().y - 60);
        window.draw(player1.sh.spellSprite);
        for (int i = 0; i < player2.spellsInst.size(); i++)
        {
            if (player1.sh.spellSprite.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()))
            {
                player2.spellsInst.erase(player2.spellsInst.begin() + i);

                player1.tshield = 0;
                player1.checktshield = false;
                player1.shield_spell = false;
                checkspellplayer1();
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (mapp[4].gates_sprite[i + 2].getGlobalBounds().intersects(player1.sh.spellSprite.getGlobalBounds()))
            {
                endPos[i] = Vector2f(-2000, -2000);
                player1.tshield = 0;
                player1.checktshield = false;
                player1.shield_spell = false;
            }
        }
        for (int i = 0; i < 6; i++)
        {
            if (enemy[i].enemy_sprite.getGlobalBounds().intersects(player1.sh.spellSprite.getGlobalBounds()))
            {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(1900, y);
                enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                player1.tshield = 0;
                player1.checktshield = false;
                player1.shield_spell = false;
            }
        }
    }
    if (player2.shield_spell)
    {
        player2.sh.spellSprite.setTexture(spellstex[8]);
        player2.sh.spellSprite.setTextureRect(IntRect(0, 0, 1200, 1200));
        player2.sh.spellSprite.setScale(0.2, 0.2);
        player2.sh.spellSprite.setPosition(player2.sprite1.getPosition().x - 70, player2.sprite1.getPosition().y - 60);
        window.draw(player2.sh.spellSprite);
        for (int i = 0; i < player1.spellsInst.size(); i++)
        {
            if (player2.sh.spellSprite.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()))
            {
                player1.spellsInst.erase(player1.spellsInst.begin() + i);
                player2.tshield = 0;
                player2.checktshield = false;
                player2.shield_spell = false;
                checkspellplayer1();
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (mapp[4].gates_sprite[i + 2].getGlobalBounds().intersects(player2.sh.spellSprite.getGlobalBounds()))
            {
                endPos[i] = Vector2f(-2000, -2000);
                player2.tshield = 0;
                player2.checktshield = false;
                player2.shield_spell = false;
            }
        }
        for (int i = 0; i < 6; i++)
        {
            if (enemy[i].enemy_sprite.getGlobalBounds().intersects(player2.sh.spellSprite.getGlobalBounds()))
            {
                int y = rand() % (921) + 80;
                enemy[i].enemy_sprite.setPosition(1900, y);
                enemy[i].speed = rand() % (15 - 8 + 1) + 8;
                player2.tshield = 0;
                player2.checktshield = false;
                player2.shield_spell = false;
            }
        }

    }
}


//struct for map1 and map2
void block_intersect(Sprite blocks[], Sprite ground, int accuracyBlocks, int accuarcyGround, int& blockCollision) {

    float const rightWall = 1850; // --> according to our screen size
    float const leftwall = 0;

    static bool check = false;
    static Clock clock;
    static Color originalColor = Color::White;
    static int blinkCount = 0; // Added to count the number of blinks

    //float const ceiling = 1;     
    FloatRect playerBounds = player1.sprite1.getGlobalBounds();
    FloatRect groundBounds = ground.getGlobalBounds();

    for (int i = 0; i < NBlocks && player1.isGrounded == false; i++) {

        FloatRect blockBounds = blocks[i].getGlobalBounds();

        if (playerBounds.intersects(blockBounds))
        {
            if (player1.sprite1.getGlobalBounds().left + player1.sprite1.getGlobalBounds().width > blocks[i].getPosition().x &&
                player1.sprite1.getGlobalBounds().left + player1.sprite1.getGlobalBounds().width < blocks[i].getPosition().x + accuracyBlocks)
            {
                player1.sprite1.setPosition(blocks[i].getPosition().x - player1.sprite1.getGlobalBounds().width, player1.sprite1.getPosition().y);
            }
            // Check from the right side of the block
            else if (player1.sprite1.getGlobalBounds().left < blocks[i].getPosition().x + blockBounds.width &&
                player1.sprite1.getGlobalBounds().left > blocks[i].getPosition().x + blockBounds.width - accuracyBlocks)
            {
                player1.sprite1.setPosition(blocks[i].getPosition().x + blockBounds.width, player1.sprite1.getPosition().y);
            }
            else
            {
                player1.isGrounded = true;
                player1.Vy = 0;
                if (player1.sprite1.getGlobalBounds().top > blocks[i].getPosition().y)
                {
                    player1.isGrounded = false;
                }
                else
                {
                    blockCollision = i;
                    playerBounds.top = blocks[i].getPosition().y;
                    player1.isGrounded = true;
                    player1.Vy = -14;
                }
            }
        }

    }

    if (playerBounds.intersects(groundBounds))
    {
        player1.sprite1.setPosition(player1.sprite1.getPosition().x, groundBounds.top - accuarcyGround); //90
        player1.isGrounded = true;
        player1.Vy = -14;
    }
    else if (player1.isGrounded)
    {
        if (!playerBounds.intersects(blocks[blockCollision].getGlobalBounds())) // if the player 
        {
            player1.isGrounded = false;
            player1.Vy = 0;
        }
    }
    if (player1.sprite1.getPosition().y > 2000)
    {
        player1.healthCharacter--;
        player1.sprite1.setPosition(20, groundBounds.top - accuarcyGround);
        check = true;
        blinkCount = 0; // Reset blink count
    }
    if (check)
    {
        if (clock.getElapsedTime().asSeconds() > 0.1) // Blink interval (0.5 seconds)
        {
            Color color = (blinkCount % 2 == 0) ? Color(255, 255, 255, 0) : originalColor;
            player1.sprite1.setColor(color);
            blinkCount++;

            if (blinkCount >= 12) // Blink 3 times (6 intervals)
            {
                check = false;
                player1.sprite1.setColor(originalColor); // Restore original color
            }

            clock.restart();
        }
    }
}
void block_intersect2(Sprite blocks[], Sprite ground, int accuracyBlocks, int accuarcyGround, int& blockCollision) {

    float const rightWall = 1850; // --> according to our screen size
    float const leftwall = 0;

    static bool check = false;
    static Clock clock;
    static Color originalColor = Color::White;
    static int blinkCount = 0; // Added to count the number of blinks

    //float const ceiling = 1;     //
    FloatRect playerBounds2 = player2.sprite1.getGlobalBounds();
    FloatRect groundBounds2 = ground.getGlobalBounds();

    for (int i = 0; i < NBlocks && player2.isGrounded == false; i++) {

        FloatRect blockBounds2 = blocks[i].getGlobalBounds();

        if (playerBounds2.intersects(blockBounds2))
        {
            if (player2.sprite1.getGlobalBounds().left + player2.sprite1.getGlobalBounds().width > blocks[i].getPosition().x &&
                player2.sprite1.getGlobalBounds().left + player2.sprite1.getGlobalBounds().width < blocks[i].getPosition().x + accuracyBlocks)
            {
                player2.sprite1.setPosition(blocks[i].getPosition().x - player2.sprite1.getGlobalBounds().width, player2.sprite1.getPosition().y);
            }
            // Check from the right side of the block
            else if (player2.sprite1.getGlobalBounds().left < blocks[i].getPosition().x + blockBounds2.width &&
                player2.sprite1.getGlobalBounds().left > blocks[i].getPosition().x + blockBounds2.width - accuracyBlocks)
            {
                player2.sprite1.setPosition(blocks[i].getPosition().x + blockBounds2.width, player2.sprite1.getPosition().y);
            }
            else
            {
                player2.isGrounded = true;
                player2.Vy = 0;
                if (player2.sprite1.getGlobalBounds().top > blocks[i].getPosition().y + 20)
                {
                    player2.isGrounded = false;
                }
                else
                {
                    blockCollision = i;
                    playerBounds2.top = blocks[i].getPosition().y - 80;
                    player2.isGrounded = true;
                    player2.Vy = -14;
                }
            }
        }

    }

    if (playerBounds2.intersects(groundBounds2)) {
        player2.sprite1.setPosition(player2.sprite1.getPosition().x, groundBounds2.top - accuarcyGround); //90
        player2.isGrounded = true;
        player2.Vy = -14;
    }

    else if (player2.isGrounded) {
        if (!playerBounds2.intersects(blocks[blockCollision].getGlobalBounds())) // if the player 
        {
            player2.isGrounded = false;
            player2.Vy = 0;
        }
    }
    if (player2.sprite1.getPosition().y > 2000)
    {
        player2.healthCharacter--;
        player2.sprite1.setPosition(1800, groundBounds2.top - accuarcyGround);
        check = true;
        blinkCount = 0; // Reset blink count
    }
    if (check)
    {
        if (clock.getElapsedTime().asSeconds() > 0.1) // Blink interval (0.5 seconds)
        {
            Color color = (blinkCount % 2 == 0) ? Color(255, 255, 255, 0) : originalColor;
            player2.sprite1.setColor(color);
            blinkCount++;

            if (blinkCount >= 12) // Blink 3 times (6 intervals)
            {
                check = false;
                player2.sprite1.setColor(originalColor); // Restore original color
            }

            clock.restart();
        }
    }
}


void lava(Sprite blocks[], Clock& clocklava, Clock& timelava1, Clock& timelava2, int& lavarand)
{
    if (clocklava.getElapsedTime().asSeconds() >= 10.0f)
    {

        blocks[lavarand].setColor(Color::Red);
        if (player2.sprite1.getGlobalBounds().intersects(blocks[lavarand].getGlobalBounds()) && timelava2.getElapsedTime().asSeconds() >= 1.0f)
        {
            player2.healthCharacter--;
            timelava2.restart();
        }
        if (player1.sprite1.getGlobalBounds().intersects(blocks[lavarand].getGlobalBounds()) && timelava1.getElapsedTime().asSeconds() >= 1.0f)
        {
            player1.healthCharacter--;
            timelava1.restart();
        }

    }
    if (clocklava.getElapsedTime().asSeconds() >= 15.0f)
    {
        blocks[lavarand].setColor(Color::White);
        lavarand = 0;
        clocklava.restart();
    }
    if (lavarand == 0)
    {
        for (int i = 0; i < NBlocks; i++)
        {
            blocks[i].setColor(Color::White);
        }
    }
}

void effct1(RenderWindow& w)
{
    static bool effctsplls[20] = { false };
    static Clock clocksplls[20];
    static int countr[20] = {};
    static Texture Drawsplls[20];
    static Sprite drawsplls[20];
    static bool texturesLoaded = 0;
    static Color originalColor = Color::White;
    static int blinkCount = 0;
    if (!texturesLoaded)
    {
        if (!Drawsplls[0].loadFromFile("effect lighting.png"))
        {
            cerr << "Error loading damage1.png" << endl;
        }
        drawsplls[0].scale(0.2, 0.2);

        if (!Drawsplls[1].loadFromFile("effect fire.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[1].scale(0.5, 0.5);

        if (!Drawsplls[2].loadFromFile("effect Water.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[2].scale(0.9, 0.9);
        if (!Drawsplls[3].loadFromFile("effect freeze.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[3].scale(1.4, 1.4);
        if (!Drawsplls[4].loadFromFile("effcet net.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[4].scale(0.3, 0.3);

        for (int i = 0; i < 10; i++)
        {
            drawsplls[i].setTexture(Drawsplls[i]);
        }
        texturesLoaded = true;
    }
    for (int i = 0; i < player2.spellsInst.size(); i++)
    {
        if (player1.sprite1.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()))
        {
            effctsplls[player1.effect] = true;
        }
    }

    if (effctsplls[0])
    {
        if (clocksplls[0].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[0] < 2)
            {
                drawsplls[0].setTextureRect(IntRect(600 * countr[0] * 600, 0, 600, 592.5));
            }
            else
            {
                drawsplls[0].setTextureRect(IntRect(0 + (countr[0] - 2) * 600, 592.5, 600, 592.5));
            }
            Color color = (blinkCount % 2 == 0) ? Color(255, 255, 255, 0) : originalColor;
            player1.sprite1.setColor(color);
            blinkCount++;
            countr[0]++;
            clocksplls[0].restart();
            drawsplls[0].setPosition(player1.sprite1.getPosition().x - 25, player1.sprite1.getPosition().y);
            player1.addspeed = 20;
            player1.Vx = 0;

        }
        if (countr[0] > 4)
        {
            player1.addspeed = 0;
            player1.Vx = 200;
            effctsplls[0] = 0;
            countr[0] = 0;
            player1.sprite1.setColor(originalColor); // Restore original color
        }
        w.draw(drawsplls[0]);
    }

    if (effctsplls[1])
    {
        if (clocksplls[1].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[1] == 0)
            {
                drawsplls[1].setTextureRect(IntRect(0, 0, 89, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition().x + 10, player1.sprite1.getPosition().y);

            }
            if (countr[1] == 1)
            {
                drawsplls[1].setTextureRect(IntRect(124, 0, 135, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition().x + 8, player1.sprite1.getPosition().y);
            }
            if (countr[1] == 2)
            {
                drawsplls[1].setTextureRect(IntRect(313, 0, 175, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition().x + 5, player1.sprite1.getPosition().y);

            }
            if (countr[1] == 3)
            {
                drawsplls[1].setTextureRect(IntRect(506, 0, 202, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition());
            }
            if (countr[1] == 4)
            {
                drawsplls[1].setTextureRect(IntRect(743, 0, 219, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition());
            }
            if (countr[1] == 5)
            {
                drawsplls[1].setTextureRect(IntRect(995, 0, 218, 320));
                drawsplls[1].setPosition(player1.sprite1.getPosition());
            }
            countr[1]++;
            clocksplls[1].restart();
        }
        if (countr[1] > 6)
        {
            effctsplls[1] = 0;
            countr[1] = 0;
        }
        w.draw(drawsplls[1]);
    }

    if (effctsplls[2])
    {
        if (clocksplls[2].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[2] == 0)
            {
                drawsplls[2].setTextureRect(IntRect(0, 0, 101, 105));
            }
            if (countr[2] == 1)
            {
                drawsplls[2].setTextureRect(IntRect(139, 0, 107, 105));
            }
            if (countr[2] == 2)
            {
                drawsplls[2].setTextureRect(IntRect(297, 0, 107, 105));
            }
            if (countr[2] == 3)
            {
                drawsplls[2].setTextureRect(IntRect(0, 147, 101, 105));
            }
            if (countr[2] == 4)
            {
                drawsplls[2].setTextureRect(IntRect(139, 147, 107, 105));
            }
            if (countr[2] == 5)
            {
                drawsplls[2].setTextureRect(IntRect(297, 147, 107, 105));
            }
            countr[2]++;
            clocksplls[2].restart();
            drawsplls[2].setPosition(player1.sprite1.getPosition());
        }
        if (countr[2] > 6)
        {
            effctsplls[2] = 0;
            countr[2] = 0;
            player1.sprite1.setColor(originalColor); // Restore original color
        }
        w.draw(drawsplls[2]);
    }

    if (effctsplls[3])
    {
        if (clocksplls[3].getElapsedTime().asSeconds() > 0.1f)
        {
            if (countr[3] < 5)
            {
                drawsplls[3].setTextureRect(IntRect(155.6 * countr[3], 0, 155.6, 160.5));
            }
            else
            {
                if (countr[3] == 5)
                {
                    drawsplls[3].setTextureRect(IntRect(0, 321, 155.6, 160.5));
                }
                else if (countr[3] == 6)
                {
                    drawsplls[3].setTextureRect(IntRect(155.6, 321, 155.6, 160.5));

                }
                else
                {
                    drawsplls[3].setTextureRect(IntRect(311.2, 321, 155.6, 160.5));

                }
            }
            countr[3]++;
            clocksplls[3].restart();
            drawsplls[3].setPosition(player1.sprite1.getPosition().x - 120 + countr[3] * 20, player1.sprite1.getPosition().y - 105);
        }
        if (countr[3] > 8)
        {
            effctsplls[3] = 0;
            countr[3] = 0;
        }
        w.draw(drawsplls[3]);
    }

    if (effctsplls[4])
    {
        if (clocksplls[4].getElapsedTime().asSeconds() > 2.0f)
        {
            countr[4]++;
            clocksplls[4].restart();
            drawsplls[4].setPosition(player1.sprite1.getPosition().x - 30, player1.sprite1.getPosition().y + 30);
            player1.Vx = 0;
            player1.addspeed = 20;
        }
        if (countr[4] > 2)
        {
            player1.addspeed = 0;
            player1.Vx = 200;
            effctsplls[4] = 0;
            countr[4] = 0;
            player1.sprite1.setColor(originalColor);
        }
        w.draw(drawsplls[4]);
    }

}
void effct2(RenderWindow& w)
{
    static bool effctsplls[20] = { false };
    static Clock clocksplls[20];
    static int countr[20] = {};
    static Texture Drawsplls[20];
    static Sprite drawsplls[20];
    static bool texturesLoaded = 0;
    static Color originalColor = Color::White;
    static int blinkCount = 0;
    if (!texturesLoaded)
    {
        if (!Drawsplls[0].loadFromFile("effect lighting.png"))
        {
            cerr << "Error loading damage1.png" << endl;
        }
        drawsplls[0].scale(0.2, 0.2);

        if (!Drawsplls[1].loadFromFile("effect fire.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[1].scale(0.5, 0.5);

        if (!Drawsplls[2].loadFromFile("effect Water.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[2].scale(0.9, 0.9);
        if (!Drawsplls[3].loadFromFile("effect freeze.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[3].scale(1.4, 1.4);
        if (!Drawsplls[4].loadFromFile("effcet net.png"))
        {
            cout << "Error loading damage1.png" << endl;
        }
        drawsplls[4].scale(0.3, 0.3);

        for (int i = 0; i < 10; i++)
        {
            drawsplls[i].setTexture(Drawsplls[i]);
        }
        texturesLoaded = true;
    }
    for (int i = 0; i < player1.spellsInst.size(); i++)
    {
        if (player2.sprite1.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()))
        {
            effctsplls[player2.effect] = true;
        }
    }

    if (effctsplls[0])
    {
        if (clocksplls[0].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[0] < 2)
            {
                drawsplls[0].setTextureRect(IntRect(600 * countr[0] * 600, 0, 600, 592.5));
            }
            else
            {
                drawsplls[0].setTextureRect(IntRect(0 + (countr[0] - 2) * 600, 592.5, 600, 592.5));
            }
            Color color = (blinkCount % 2 == 0) ? Color(255, 255, 255, 0) : originalColor;
            player2.sprite1.setColor(color);
            blinkCount++;
            countr[0]++;
            clocksplls[0].restart();
            drawsplls[0].setPosition(player2.sprite1.getPosition().x - 25, player2.sprite1.getPosition().y);
            player2.addspeed = 8;
            player2.Vx = 0;
        }
        if (countr[0] > 4)
        {
            player2.addspeed = 0;
            player2.Vx = 200;
            effctsplls[0] = 0;
            countr[0] = 0;
            player2.sprite1.setColor(originalColor); // Restore original color
        }
        w.draw(drawsplls[0]);
    }

    if (effctsplls[1])
    {
        if (clocksplls[1].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[1] == 0)
            {
                drawsplls[1].setTextureRect(IntRect(0, 0, 89, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition().x + 10, player2.sprite1.getPosition().y);

            }
            if (countr[1] == 1)
            {
                drawsplls[1].setTextureRect(IntRect(124, 0, 135, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition().x + 8, player2.sprite1.getPosition().y);
            }
            if (countr[1] == 2)
            {
                drawsplls[1].setTextureRect(IntRect(313, 0, 175, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition().x + 5, player2.sprite1.getPosition().y);

            }
            if (countr[1] == 3)
            {
                drawsplls[1].setTextureRect(IntRect(506, 0, 202, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition());
            }
            if (countr[1] == 4)
            {
                drawsplls[1].setTextureRect(IntRect(743, 0, 219, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition());
            }
            if (countr[1] == 5)
            {
                drawsplls[1].setTextureRect(IntRect(995, 0, 218, 320));
                drawsplls[1].setPosition(player2.sprite1.getPosition());
            }
            countr[1]++;
            clocksplls[1].restart();
        }
        if (countr[1] > 6)
        {
            effctsplls[1] = 0;
            countr[1] = 0;
        }
        w.draw(drawsplls[1]);
    }

    if (effctsplls[2])
    {
        if (clocksplls[2].getElapsedTime().asSeconds() > 0.1)
        {
            if (countr[2] == 0)
            {
                drawsplls[2].setTextureRect(IntRect(0, 0, 101, 105));
            }
            if (countr[2] == 1)
            {
                drawsplls[2].setTextureRect(IntRect(139, 0, 107, 105));
            }
            if (countr[2] == 2)
            {
                drawsplls[2].setTextureRect(IntRect(297, 0, 107, 105));
            }
            if (countr[2] == 3)
            {
                drawsplls[2].setTextureRect(IntRect(0, 147, 101, 105));
            }
            if (countr[2] == 4)
            {
                drawsplls[2].setTextureRect(IntRect(139, 147, 107, 105));
            }
            if (countr[2] == 5)
            {
                drawsplls[2].setTextureRect(IntRect(297, 147, 107, 105));
            }
            countr[2]++;
            clocksplls[2].restart();
            drawsplls[2].setPosition(player2.sprite1.getPosition());
        }
        if (countr[2] > 6)
        {
            effctsplls[2] = 0;
            countr[2] = 0;
            player2.sprite1.setColor(originalColor); // Restore original color
        }
        w.draw(drawsplls[2]);
    }

    if (effctsplls[3])
    {
        if (clocksplls[3].getElapsedTime().asSeconds() > 0.1f)
        {
            if (countr[3] < 5)
            {
                drawsplls[3].setTextureRect(IntRect(155.6 * countr[3], 0, 155.6, 160.5));
            }
            else
            {
                if (countr[3] == 5)
                {
                    drawsplls[3].setTextureRect(IntRect(0, 321, 155.6, 160.5));
                }
                else if (countr[3] == 6)
                {
                    drawsplls[3].setTextureRect(IntRect(155.6, 321, 155.6, 160.5));

                }
                else
                {
                    drawsplls[3].setTextureRect(IntRect(311.2, 321, 155.6, 160.5));

                }
            }
            countr[3]++;
            clocksplls[3].restart();
            drawsplls[3].setPosition(player2.sprite1.getPosition().x - 120 + countr[3] * 20, player2.sprite1.getPosition().y - 105);
        }
        if (countr[3] > 8)
        {
            effctsplls[3] = 0;
            countr[3] = 0;
        }
        w.draw(drawsplls[3]);
    }

    if (effctsplls[4])
    {
        if (clocksplls[4].getElapsedTime().asSeconds() > 2.0f)
        {
            countr[4]++;
            clocksplls[4].restart();
            drawsplls[4].setPosition(player2.sprite1.getPosition().x - 30, player2.sprite1.getPosition().y + 30);
            player2.Vx = 0;
            player2.addspeed = 8;
        }
        if (countr[4] > 2)
        {
            player2.addspeed = 0;
            player2.Vx = 200;
            effctsplls[4] = 0;
            countr[4] = 0;
            player2.sprite1.setColor(originalColor); // Restore original color
        }
        w.draw(drawsplls[4]);
    }

}
