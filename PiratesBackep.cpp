#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;
HANDLE acolor = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

void frontPage();
void keys();
int menu();
void characters();
void clearScreen();
void instruction();
char printMaze[36][103]; // array to print the maze
void loadMaze();         // ftn to load the maze from file

void printMainCharacter(); // ftn to print main character
void eraseMainCharacter(); // ftn to erase main character
char mainCharacter1[4][4] = {{'(', '0', '0', ')'},
                             {'<', ' ', ' ', '>'},
                             {' ', '(', ')', ' '},
                             {' ', char(192), char(192), ' '}}; // Array to print the main character

int mainX = 5; // X coordinate of main character
int mainY = 6; // Y coordinate of main character

void moveMainCharDown();  // ftn to move main character down
void moveMainCharUp();    // ftn to move main character up
void moveMainCharRight(); // ftn to move main character right
void moveMainCharLeft();  // ftn to move main character left

void moveBullet();                     // ftn to move bullet of main character
void generateBullet();                 // ftn to generate bullet of main character
void removeBulletFromArray(int index); // ftn to remove bullet of main character from main
void printBullet(int x, int y);        // ftn to print bullet of main character
void eraseBullet(int x, int y);        // ftn to erase bullet of main character

int bulletX[100];         // X coordinates of bullet of main character
int bulletY[100];         // Y coordinates of bullet of main character
bool isBulletActive[100]; // ftn to make bullet active of main character
int bulletCount = 0;      // bullet counter for main character

// details of first enemy
void printEnemy1(); // array to print first enemy
void eraseEnemy1();
int boxx = 223;
char Enemy1[2][5] = {{'<', '=', char(boxx), char(boxx), char(boxx)},
                     {' ', ' ', '0', ' ', '0'}}; // array to print 1st enemy

int enemy1X = 40; // x coordinates of enemy 1
int enemy1Y = 23; // y coordinate of enemy 1

string enemyDirection = "right"; // a variable to declare the direction
string dir = "up";               // a variable to declare the direction
void moveEnemy1();               // ftn to move enemy 1
void moveEnemyDown();            // ftn to move 1st enemy down
void moveEnemyUp();              // ftn to move 1st enemy up

int bulletXenemy[100];    // X coordinates of bullet of 1st enemy
int bulletYenemy[100];    // Y coordinates of bullet of 1st enemy
int bulletCountenemy = 0; // bullet counter for 1st enemy

void generateBulletenemy();                 // ftn to generate bullet of 1st enemy
void printBulletenemy(int x, int y);        // ftn to print bullet of 1st enemy
void eraseBulletenemy(int x, int y);        // ftn to erase bullet of 1st enemy
void removeBulletFromArrayenemy(int index); // ftn to remove bullet of 1st enemy
void moveBulletEnemy();                     // ftn to move bullet of 1st enemy

// enemy2 detail
void printEnemy2(int x, int y); // ftn to print enemy 2
char Enemy2[3][3] = {{' ', 'o', ' '},
                     {'/', '^', '>'},
                     {'/', ' ', '\\'}}; // array to print enemy 2
int enemy2X = 70;                       // x coordinates of enemy 2
int enemy2Y = 31;                       // y coordinates of enemy 2
void eraseEnemy2();                     // ftn to erase enemy 2
void chaseEnemy2();                     // ftn to chase enemy 2

string destination = "up"; // a variable to declare the direction
void printEnemy3();        // ftn to print enemy 3
void eraseEnemy3();        // ftn to erase enemy 3
int p = 244;
int questionMark = 168;
char Enemy3[2][5] = {{'<', char(boxx), char(p), char(boxx), '>'},
                     {' ', char(questionMark), ' ', char(questionMark), ' '}}; // array to print enemy 3

int enemy3X = 90; // x coordinates of enemy 3
int enemy3Y = 5;  // y coordinates of enemy 3

void moveMainEnemyLeft();  // ftn to move main enemy down
void moveMainEnemyRight(); // ftn to move main enemy up
void moveMainEnemyUp();    // ftn to move main enemy left
void moveMainEnemyDown();  // ftn to move main enemy right
void moveEnemy3();         // ftn to move enemy 3

int timer = 0; // timer to move all the three enemies
// int time = 0;
int score = 0;    // variable to add the score
int health = 100; // a variable for health

void addScore(); // ftn to add the score
// void healthh();
// void bulletCollisionWithEnemy1();

void printScore(); // ftn to print score of main character
void start();
void topHeader();
bool gameRunning = true;

int escapeKeyX = 65;
int escapeKeyY = 15;
void Exit();
char escapeKey1[1][1] = {{char(176)}};
void storeData();

main()
{
    storeData();
    system("cls");
    topHeader();
    frontPage();
    getch();
    system("cls");
    int option = 0;

    while (option != 5)
    {
        system("cls");
        topHeader();
        clearScreen();
        option = menu();

        if (option == 1)
        {
            clearScreen();
            // topHeader();
            system("cls");
            // loadMaze();
            start();
        }
        else if (option == 2)
        {
            clearScreen();
            // topHeader();
            keys();
        }
        else if (option == 3)
        {
            clearScreen();
            // topHeader();
            instruction();
        }
        else if (option == 4)
        {
            clearScreen();
            // topHeader();
            characters();
        }
    }
}
void start()
{
    system("cls");
    SetConsoleTextAttribute(acolor , 3);
    loadMaze();
    
    printMainCharacter();
    SetConsoleTextAttribute(acolor , 4);
    printEnemy1();
    // SetConsoleTextAttribute(acolor , 4);
    printEnemy2(enemy2X, enemy2Y);
    // SetConsoleTextAttribute(acolor , 4);
    printEnemy3();
    gotoxy(escapeKeyX, escapeKeyY);
    cout << char(176);

    while (gameRunning)
    {

        generateBulletenemy();

        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveMainCharLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveMainCharRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveMainCharUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveMainCharDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }

        if (mainX == escapeKeyX || (mainY == escapeKeyY || mainY + 1 == escapeKeyY || mainY + 2 == escapeKeyY || mainY + 3 == escapeKeyY))
        {
            for (int idx = 0; idx < 3; idx++)
            {
                gotoxy(96, 32 + idx);
                for (int idx = 0; idx < 3; idx++)
                {
                    cout << char(178);
                }
            }
        }
        if (timer == 2)
        {
            moveEnemy1();
            chaseEnemy2();
            moveEnemy3();
            timer = 0;
        }
        moveBullet();
        moveBulletEnemy();

        gotoxy(107, 9);
        cout << "Health : " << health << " ";
        if (health == 0)
        {
            system("cls");
            gotoxy(10, 10);
            cout << "********************************" << endl;
            Sleep(100);
            gotoxy(10, 11);
            cout << "*                              *" << endl;
            Sleep(100);
            gotoxy(10, 12);
            cout << "*      WOOPS! YOU ARE DEAD!    *" << endl;
            Sleep(100);
            gotoxy(10, 13);
            cout << "*      SEE YOU AGAIN!          *" << endl;
            Sleep(100);
            gotoxy(10, 14);
            cout << "*             :(               *" << endl;
            Sleep(100);
            gotoxy(10, 15);
            cout << "*                              *" << endl;
            Sleep(100);
            gotoxy(10, 16);
            cout << "********************************" << endl;
            storeData();
            gameRunning = false;
            Sleep(5000);
            // break;
        }
        timer++;
        Sleep(30);
    }
}

void topHeader()
{

    cout << "TTTTTTTTTTTTTTTTTTTTTTThhhhhhh                                      PPPPPPPPPPPPPPPPP     iiii                                             tttt                                               " << endl;
    cout << "T:::::::::::::::::::::Th:::::h                                      P::::::::::::::::P   i::::i                                         ttt:::t                                               " << endl;
    cout << "T:::::::::::::::::::::Th:::::h                                      P::::::PPPPPP:::::P   iiii                                          t:::::t                                               " << endl;
    cout << "T:::::TT:::::::TT:::::Th:::::h                                      PP:::::P     P:::::P                                                t:::::t                                               " << endl;
    cout << "TTTTTT  T:::::T  TTTTTT h::::h hhhhh           eeeeeeeeeeee           P::::P     P:::::Piiiiiiirrrrr   rrrrrrrrr   aaaaaaaaaaaaa  ttttttt:::::ttttttt        eeeeeeeeeeee        ssssssssss   " << endl;
    cout << "        T:::::T         h::::hh:::::hhh      ee::::::::::::ee         P::::P     P:::::Pi:::::ir::::rrr:::::::::r  a::::::::::::a t:::::::::::::::::t      ee::::::::::::ee    ss::::::::::s  " << endl;
    cout << "        T:::::T         h::::::::::::::hh   e::::::eeeee:::::ee       P::::PPPPPP:::::P  i::::ir:::::::::::::::::r aaaaaaaaa:::::at:::::::::::::::::t     e::::::eeeee:::::eess:::::::::::::s " << endl;
    cout << "        T:::::T         h:::::::hhh::::::h e::::::e     e:::::e       P:::::::::::::PP   i::::irr::::::rrrrr::::::r         a::::atttttt:::::::tttttt    e::::::e     e:::::es::::::ssss:::::s" << endl;
    cout << "        T:::::T         h::::::h   h::::::he:::::::eeeee::::::e       P::::PPPPPPPPP     i::::i r:::::r     r:::::r  aaaaaaa:::::a      t:::::t          e:::::::eeeee::::::e s:::::s  ssssss " << endl;
    cout << "        T:::::T         h:::::h     h:::::he:::::::::::::::::e        P::::P             i::::i r:::::r     rrrrrrraa::::::::::::a      t:::::t          e:::::::::::::::::e    s::::::s      " << endl;
    cout << "        T:::::T         h:::::h     h:::::he::::::eeeeeeeeeee         P::::P             i::::i r:::::r           a::::aaaa::::::a      t:::::t          e::::::eeeeeeeeeee        s::::::s   " << endl;
    cout << "        T:::::T         h:::::h     h:::::he:::::::e                  P::::P             i::::i r:::::r          a::::a    a:::::a      t:::::t    tttttte:::::::e           ssssss   s:::::s " << endl;
    cout << "      TT:::::::TT       h:::::h     h:::::he::::::::e               PP::::::PP          i::::::ir:::::r          a::::a    a:::::a      t::::::tttt:::::te::::::::e          s:::::ssss::::::s" << endl;
    cout << "      T:::::::::T       h:::::h     h:::::h e::::::::eeeeeeee       P::::::::P          i::::::ir:::::r          a:::::aaaa::::::a      tt::::::::::::::t e::::::::eeeeeeee  s::::::::::::::s " << endl;
    cout << "      T:::::::::T       h:::::h     h:::::h  ee:::::::::::::e       P::::::::P          i::::::ir:::::r           a::::::::::aa:::a       tt:::::::::::tt  ee:::::::::::::e   s:::::::::::ss  " << endl;
    cout << "      TTTTTTTTTTT       hhhhhhh     hhhhhhh    eeeeeeeeeeeeee       PPPPPPPPPP          iiiiiiiirrrrrrr            aaaaaaaaaa  aaaa         ttttttttttt      eeeeeeeeeeeeee    sssssssssss    " << endl;
}
void frontPage()
{
    SetConsoleTextAttribute(acolor , 2);
    cout << "                                 .:-=+**##**+=:                                                     " << endl;
    cout << "                             .=*###%%%%%%%%%%%#*-                                                   " << endl;
    cout << "                          :-**#%%###%%%%%%%%%%#%%#-                                                 " << endl;
    cout << "                         +############%%%%%%%%%%%%%*                                                " << endl;
    cout << "                        =#######%######%###%%%%%%%%%#                                               " << endl;
    cout << "                        .=****#*#%%#####%#####%#%%%%%%=                                             " << endl;
    cout << "                    :-===++===+*######%#%%###%##%%%%%%.                                             " << endl;
    cout << "                        --=**##+-:-####*+==+###%%%#**#%:                                            " << endl;
    cout << "                        =###%= -=+.+#######*++-=+=::::+                                             " << endl;
    cout << "                      .:-=+#%-.+%%-*#######%%%%#+.=-:--                                             " << endl;
    cout << "                    ::.....:=#+==+#%%%%%%%%%%%%%=:::::-                                             " << endl;
    cout << "                   -......::::-=+*******+=-===-=::..:-:   ......                                    " << endl;
    cout << "                   -....:::::====---===----==--======-:-------::---::.                              " << endl;
    cout << "                   .:----=====----===--------=======------------------=-:.                          " << endl;
    cout << "                         ======----=-----=======---------------------------::                       " << endl;
    cout << "                          .:  .:=+#=---======---------------------------------:                     " << endl;
    cout << "                            =%#====---====-------======-------------------------:                   " << endl;
    cout << "                            ====-=--====---=============--------------------------.                 " << endl;
    cout << "                            .==--::.:--=======-:::-:-===---------------------------:                " << endl;
    cout << "                           :-::......=+===--:      .  -+===------------------------=:               " << endl;
    cout << "                          ::-:.......:::- .=-::.    : .#++===-----------------------=               " << endl;
    cout << "                         .-====:......::+%#%%%%%%*=::=%%%#++====----------------------              " << endl;
    cout << "                     :----======-:::.::.*#***#%%%%%%##%%#=:-=+====-------------------=              " << endl;
    cout << "                     .=-=+=--=+=----:  :#+      :+#%%%*-   +%+=======---------------=+              " << endl;
    cout << "                       -=---===--::  :+%%%*#*+=:   --    =#%%%*==--=====------------==              " << endl;
    cout << "                        :=====: .:=+#%%%%#..#%%%%+::.:=*%%%%%%+-==-----------------==-              " << endl;
    cout << "                           ..     =%@%%+-  -%#%%%%%#%%%%%%#+- ..-====------------====.              " << endl;
    cout << "                ..               :  =-.   =%%%.-%@+---::.     :+#+==================:               " << endl;
    cout << "-***=:       :::..::. ...-##%*   #%#=.:.-*%%%+  :*     .:-=+#%%%@%=================:                " << endl;
    cout << "*###+-++++===.:===--:::  -%%%+   #%%%: -#%%%+  .:#%%%%%%%%%%%%%#*================-                  " << endl;
    cout << "####*=######=-+##%=+:.:  -%%%*   +%%%%:::.==::::=**#####**+=-.  :-+===========-:                    " << endl;
    cout << "###%*++++-:-:=:-:=+*---..:@@@@-..-%%%#-.  :%#=-.           :-=+#%@#.::----::.                       " << endl;
    cout << ":---:     ..:--=-=--.  ...----:...        .*#%%%%##***##%%%%%%%@%#-                                 " << endl;
    cout << "                                           .:..:-=============-::.                                  " << endl;
    cout << "                                          :--===========----=+++*                                   " << endl;
    cout << "                                       .:--========+++===++***#**.                                  " << endl;
    cout << "                                     .--=======++++====+*****#*++=                                  " << endl;
    cout << "                                    --======+++=======+**#***===+*                                  " << endl;
    cout << "                                   =-====+++=====+++=-:=-===++==+*.                                 " << endl;
    cout << "                                  ::====++=+++++=:.    ::====+==++=                                 " << endl;
    cout << "                                  .--====+==+*:         --===+==++*                                 " << endl;
    cout << "                                   --====++==++.        .-===+==+++===---::..                       " << endl;
    cout << "                                    -:====++==++.        :===++================-:.                  " << endl;
    cout << "                                     -:====++==++         -====++++==============---::.             " << endl;
    cout << "                                      =:====++==+=         -+======++++++++++======+%%@@@@          " << endl;
    cout << "                                       -:====+==+*:          :--=+++++=======++++++%@@@@@@          " << endl;
    cout << "                                       :--====*==++:               .:-=+++=======+%%%%@@@%          " << endl;
    cout << "                                        =:====*===++=                   .-=++++++%%%@@@@@#          " << endl;
    cout << "                                        -:====++===+++:                     .-+#%%%%@@@+..          " << endl;
    cout << "                                 =*##+=:=-====++===++=.                 .=*#%%%%%%%%%@@=            " << endl;
    cout << "                               :#%%%%%%%%###**####%%#                  :#%%%%%%%%%%@@@%.            " << endl;
    cout << "                               %@%%%%%%%%%%%%%@@@%@@@:                 +%%%%%%%%%%@@@%:             " << endl;
    cout << "                               -#@@@@@@@@@@@@@@@@@@@@*                 *@@@@@@@@@@@*-               " << endl;
}

void loadMaze()
{
    SetConsoleTextAttribute(acolor , 9);
    fstream yourfile;
    string line;
    int rows = 0;
    yourfile.open("print.txt", ios::in);
    while (getline(yourfile, line))
    {
        for (int cols = 0; cols < 102; cols++)
        {
            printMaze[rows][cols] = line[cols];
        }
        rows++;
    }
    yourfile.close();
    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < 102; j++)
        {
            cout << printMaze[i][j];
        }
        cout << endl;
    }
}
void instruction()
{
    
    cout << "\t"
            "                  ------------------------------- "
         << endl;
    cout << "\t"
            "                 |                               |"
         << endl;
    cout << "\t"
            "                 |          HOW TO PLAY          |"
         << endl;
    cout << "\t"
            "                  ------------------------------- "
         << endl;
    cout << endl
         << endl
         << endl;
    cout << "\t"
            "    1.THE PIRATES  is a game in which there is only one Player named as Thomas.            "
         << endl
         << endl;
    cout << "\t"
            "    2. In this game there are 3 enemies. "
         << endl
         << endl;
    cout << "\t"
            "    3. Press the Space bar to release fire of Thomas.                                      "
         << endl
         << endl;
    cout << "\t"
            "    4. When the bullet hits the Enemy , the score will add by '1' per bullet.    "
         << endl
         << endl;
    cout << "\t"
            "    5. Thomas has to reach the main gate in order to escape after getting the key.    "
         << endl
         << endl;
    cout << "\t"
            "    6. The goal of the game is to reach the top lower  corner of th maze.   "
         << endl
         << endl;
    cout << "\t"
            "    7. Highway poliece fires on left .                                             "
         << endl
         << endl;

    cout << endl;
    cout << "\t"
            "  Press Any Key to Continue .. !"
         << endl;

    getch();
}

void characters()
{
    system("cls");
    cout << "Thomas :)" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << mainCharacter1[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << "Local Police :)>" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << Enemy1[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << "Motor Police: :)>" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << Enemy2[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << "Highway Police: :)>" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << Enemy3[i][j];
        }
        cout << endl;

        cout << endl;
        getch();
    }
}
int menu()
{

    int option;
    cout << "\t"
            "     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> "
         << endl;
    cout << "\t"
            "     |                               |"
         << endl;
    cout << "\t"
            "     |           Menu                |"
         << endl;
    cout << "\t"
            "     |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|"
         << endl;
    cout << "\t"
            "                                      "
         << endl;
    cout << "\t"
            "      1.Start Game                    "
         << endl;
    cout << "\t"
            "      2.Keys                          "
         << endl;
    cout << "\t"
            "      3.Instructions                  "
         << endl;
    cout << "\t"
            "      4.Characters                    "
         << endl;
    cout << "\t"
            "      5.Exit                          "
         << endl;
    cout << endl;
    cout << "\t"
            " Select any option..";
    cin >> option;

    return option;
}

void keys()
{
    cout << "\t"
            "      _______________________________ "
         << endl;
    cout << "\t"
            "     |                               |"
         << endl;
    cout << "\t"
            "     |            Keys               |"
         << endl;
    cout << "\t"
            "     |_______________________________|"
         << endl;
    cout << endl;
    cout << "\t"
            "     1. Up                 Go up    "
         << endl;
    cout << "\t"
            "                  ^      "
         << endl;
    cout << "\t"
            "                  |      "
         << endl;
    cout << endl;
    cout << "\t"
            "     2. Down               Go Down  "
         << endl;
    cout << "\t"
            "                  |      "
         << endl;
    cout << "\t"
            "                  V      "
         << endl;
    cout << endl;
    cout << "\t"
            "     3. Left               Go Left  "
         << endl;
    cout << "\t"
            "                <----       "
         << endl;
    cout << endl;
    cout << "\t"
            "     4. Right              Go Right "
         << endl;
    cout << "\t"
            "                ----->     "
         << endl;
    cout << endl;
    cout << "\t"
            "     5. Space              Fire     "
         << endl;
    cout << endl
         << endl;
    cout << "\t"
            "     6. Esc                End Game "
         << endl;
    cout << endl;
    cout << "\t"
            " Press any key to continue ..!"
         << endl;

    getch();
}
void clearScreen()
{
    cout << " Press any Key to Continue ! " << endl;
    getch();
    system("cls");
}
void printMainCharacter()
{
    SetConsoleTextAttribute(acolor , 4);
    for (int i = 0; i < 4; i++)
    {
        gotoxy(mainX, mainY + i);
        for (int j = 0; j < 4; j++)
        {
            cout << mainCharacter1[i][j];
        }
        cout << endl;
    }
}

void eraseMainCharacter()
{
    for (int i = 0; i < 4; i++)
    {
        gotoxy(mainX, mainY + i);
        for (int j = 0; j < 4; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void moveMainCharLeft()
{
    char next = printMaze[mainY][mainX - 1];
    char next1 = printMaze[mainY + 1][mainX - 1];
    char next2 = printMaze[mainY + 2][mainX - 1];
    char next3 = printMaze[mainY + 3][mainX - 1];

    if (next == '*' || next1 == '*' || next2 == '*' || next3 == '*')
    {
        score += 5;
        if (next == '*')
            printMaze[mainY][mainX - 1] = ' ';
        if (next1 == '*')
            printMaze[mainY + 1][mainX - 1] = ' ';
        if (next2 == '*')
            printMaze[mainY + 2][mainX - 1] = ' ';
        if (next3 == '*')
            printMaze[mainY + 3][mainX - 1] = ' ';
    }
    if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0'))
    {
        eraseMainCharacter();
        mainX = mainX - 1;
        printMainCharacter();
    }
    else if ((next == '<' || next1 == '<' || next2 == '<' || next3 == '<') || (next == '>' || next1 == '>' || next2 == '>' || next3 == '>') || (next == '0' || next1 == '0' || next2 == '0' || next3 == '0') || (next == char(questionMark) || next1 == char(questionMark) || next2 == char(questionMark) || next3 == char(questionMark)) || (next == '.' || next1 == '.' || next2 == '.' || next3 == '.'))
    {
        health--;
    }
}

void moveMainCharRight()
{
    char next = printMaze[mainY][mainX + 4];
    char next1 = printMaze[mainY + 1][mainX + 4];
    char next2 = printMaze[mainY + 2][mainX + 4];
    char next3 = printMaze[mainY + 3][mainX + 4];

    if (next == '*' || next1 == '*' || next2 == '*' || next3 == '*')
    {
        score += 5;
        if (next == '*')
            printMaze[mainY][mainX - 1] = ' ';
        if (next1 == '*')
            printMaze[mainY + 1][mainX - 1] = ' ';
        if (next2 == '*')
            printMaze[mainY + 2][mainX - 1] = ' ';
        if (next3 == '*')
            printMaze[mainY + 3][mainX - 1] = ' ';
    }
    if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0'))
    {
        eraseMainCharacter();
        mainX = mainX + 1;
        printMainCharacter();
    }
    else if ((next == '<' || next1 == '<' || next2 == '<' || next3 == '<') || (next == '>' || next1 == '>' || next2 == '>' || next3 == '>') || (next == '0' || next1 == '0' || next2 == '0' || next3 == '0') || (next == char(questionMark) || next1 == char(questionMark) || next2 == char(questionMark) || next3 == char(questionMark)) || (next == '.' || next1 == '.' || next2 == '.' || next3 == '.'))
    {
        health--;
    }
    else if (next == char(176) || next1 == char(176) || next2 == char(176) || next3 == char(176))
    {
        for (int idx = 0; idx < 3; idx++)
        {
            gotoxy(50, 5 + idx);
            for (int idx = 0; idx < 3; idx++)
            {
                cout << char(178);
            }
            cout << endl;
        }
    }
}

void moveMainCharUp()
{
    char next = printMaze[mainY - 1][mainX];
    char next1 = printMaze[mainY - 1][mainX + 1];
    char next2 = printMaze[mainY - 1][mainX + 2];
    char next3 = printMaze[mainY - 1][mainX + 3];

    if (next == '*' || next1 == '*' || next2 == '*' || next3 == '*')
    {
        score += 5;
        if (next == '*')
            printMaze[mainY][mainX - 1] = ' ';
        if (next1 == '*')
            printMaze[mainY + 1][mainX - 1] = ' ';
        if (next2 == '*')
            printMaze[mainY + 2][mainX - 1] = ' ';
        if (next3 == '*')
            printMaze[mainY + 3][mainX - 1] = ' ';
    }
    if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0'))
    {
        eraseMainCharacter();
        mainY = mainY - 1;
        printMainCharacter();
    }
    else if ((next == '<' && next1 == '<' && next2 == '<' && next3 == '<') || (next == '>' && next1 == '>' && next2 == '>' && next3 == '>') || (next == '0' && next1 == '0' && next2 == '0' && next3 == '0') || (next == char(questionMark) && next1 == char(questionMark) && next2 == char(questionMark) && next3 == char(questionMark)) || (next == '.' && next1 == '.' && next2 == '.' && next3 == '.'))
    {
        health--;
    }
}

void moveMainCharDown()
{
    char next = printMaze[mainY + 4][mainX];
    char next1 = printMaze[mainY + 4][mainX + 1];
    char next2 = printMaze[mainY + 4][mainX + 2];
    char next3 = printMaze[mainY + 4][mainX + 3];

    if (next == '*' || next1 == '*' || next2 == '*' || next3 == '*')
    {
        score += 5;
        if (next == '*')
            printMaze[mainY][mainX - 1] = ' ';
        if (next1 == '*')
            printMaze[mainY + 1][mainX - 1] = ' ';
        if (next2 == '*')
            printMaze[mainY + 2][mainX - 1] = ' ';
        if (next3 == '*')
            printMaze[mainY + 3][mainX - 1] = ' ';
    }
    if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0'))
    {
        eraseMainCharacter();
        mainY = mainY + 1;
        printMainCharacter();
    }
    else if ((next == '<' && next1 == '<' && next2 == '<' && next3 == '<') || (next == '>' && next1 == '>' && next2 == '>' && next3 == '>') || (next == '0' && next1 == '0' && next2 == '0' && next3 == '0') || (next == char(questionMark) && next1 == char(questionMark) && next2 == char(questionMark) && next3 == char(questionMark)) || (next == '.' && next1 == '.' && next2 == '.' && next3 == '.'))
    {
        health--;
    }
}

void generateBullet()
{
    char next;
    bulletX[bulletCount] = mainX + 4;
    bulletY[bulletCount] = mainY;
    isBulletActive[bulletCount] = true;
    gotoxy(mainX + 4, mainY);
    cout << "-";
    bulletCount++;
}

void generateBulletenemy()
{
    char next;
    bulletXenemy[bulletCountenemy] = enemy1X - 1;
    bulletYenemy[bulletCountenemy] = enemy1Y;
    gotoxy(enemy1X - 1, enemy1Y);
    for (next = 0; next < 100; next++)
    {
        if (next == ' ')
        {
            cout << ".";
        }
    }
    bulletCountenemy++;
}

void removeBulletFromArray(int index)
{
    for (int x = index; x < bulletCount - 1; x++)
    {
        bulletX[x] = bulletX[x + 1];
        bulletY[x] = bulletY[x + 1];
    }
    bulletCount--;
}

void moveBullet()
{
    SetConsoleTextAttribute(acolor , 7);
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x] + 1);
            if (next != ' ')
            {
                eraseBullet(bulletX[x], bulletY[x]);
                removeBulletFromArray(x);
            }
            else
            {
                eraseBullet(bulletX[x], bulletY[x]);
                bulletX[x] = bulletX[x] + 1;
                printBullet(bulletX[x], bulletY[x]);
            }
        }
    }
}

void printBullet(int x, int y)
{
    gotoxy(x, y);
    cout << "-";
}

void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void printEnemy1()
{
    for (int i = 0; i < 2; i++)
    {
        gotoxy(enemy1X, enemy1Y + i);
        for (int j = 0; j < 5; j++)
        {
            cout << Enemy1[i][j];
        }
        cout << endl;
    }
}

void eraseEnemy1()
{
    for (int i = 0; i < 2; i++)
    {
        gotoxy(enemy1X, enemy1Y + i);
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void moveEnemy1()
{
    {
        if (dir == "up")
        {
            moveEnemyUp();
        }
        else if (dir == "down")
        {
            moveEnemyDown();
        }
    }
}

void moveEnemyUp()
{
    char next = getCharAtxy(enemy1X , enemy1Y-1);
    char next1 = getCharAtxy(enemy1X + 1, enemy1Y -1);

    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    {
        eraseEnemy1();
        enemy1Y = enemy1Y - 1;
        printEnemy1();
    }
    else
    {
        dir = "down";
    }

    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
}

void moveEnemyDown()
{
    char next = getCharAtxy(enemy1X , enemy1Y+3);
    char next1 = getCharAtxy(enemy1X + 1, enemy1Y + 3);

    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    {
        eraseEnemy1();
        enemy1Y = enemy1Y + 1;
        printEnemy1();
    }
    if (next == '#' || next1 == '#')
    {
        dir = "up";
    }
}

void printBulletenemy(int x, int y)
{
    gotoxy(x, y);
    cout << ".";
}

void eraseBulletenemy(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void removeBulletFromArrayenemy(int index)
{
    for (int x = index; x < bulletCountenemy - 1; x++)
    {
        bulletXenemy[x] = bulletXenemy[x + 1];
        bulletYenemy[x] = bulletYenemy[x + 1];
    }
    bulletCountenemy--;
}

void moveBulletEnemy()
{

    for (int x = 0; x < bulletCountenemy; x++)
    {
        char next = getCharAtxy(bulletXenemy[x] - 1, bulletYenemy[x]);
        if (next != ' ')
        {
            eraseBulletenemy(bulletXenemy[x], bulletYenemy[x]);
            removeBulletFromArrayenemy(x);
        }
        else if (next == ' ')
        {
            eraseBulletenemy(bulletXenemy[x], bulletYenemy[x]);
            bulletXenemy[x] = bulletXenemy[x] - 1;
            printBulletenemy(bulletXenemy[x], bulletYenemy[x]);
        }
    if ((next == '0' ||next == '<' || next == '>'  || next == '(' || next == ')'))
    {
        health--;
    }
    }

    
}

void printEnemy2(int enemy2X, int enemy2Y)
{
    for (int i = 0; i < 3; i++)
    {
        gotoxy(enemy2X, enemy2Y + i);
        for (int j = 0; j < 3; j++)
        {
            cout << Enemy2[i][j];
        }
        cout << endl;
    }
}

void eraseEnemy2(int enemy2X, int enemy2Y)
{
    for (int i = 0; i < 3; i++)
    {
        gotoxy(enemy2X, enemy2Y + i);
        for (int j = 0; j < 3; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void chaseEnemy2()
{
    int chaseX = enemy2X - mainX; // difference for chase
    int chaseY = enemy2Y - mainY;

    if (chaseX > 0) // left
    {
        char nextlocation = getCharAtxy(enemy2X - 1, enemy2Y);
        char nextlocation1 = getCharAtxy(enemy2X - 1, enemy2Y + 1);
        char nextlocation2 = getCharAtxy(enemy2X - 1, enemy2Y + 2);
        if (nextlocation == '0' || nextlocation == '>' || nextlocation == '<' || nextlocation == '(' || nextlocation == ')' || nextlocation1 == '0' || nextlocation1 == '>' || nextlocation1 == '<' || nextlocation1 == '(' || nextlocation1 == ')' || nextlocation2 == '0' || nextlocation2 == '<' || nextlocation2 == '>' || nextlocation2 == '(' || nextlocation2 == ')')
        {
            health--;
        }
        if (nextlocation == ' ' && nextlocation1 == ' ' && nextlocation2 == ' ')
        {
            eraseEnemy2(enemy2X, enemy2Y);
            enemy2X = enemy2X - 1;
            printEnemy2(enemy2X, enemy2Y);
        }
    }
    if (chaseX < 0) // right
    {
        char nextlocation = getCharAtxy(enemy2X + 3, enemy2Y);
        char nextlocation1 = getCharAtxy(enemy2X + 3, enemy2Y + 1);
        char nextlocation2 = getCharAtxy(enemy2X + 3, enemy2Y + 2);
        if (nextlocation == '0' || nextlocation == '>' || nextlocation == '<' || nextlocation == '(' || nextlocation == ')' || nextlocation1 == '0' || nextlocation1 == '>' || nextlocation1 == '<' || nextlocation1 == '(' || nextlocation1 == ')' || nextlocation2 == '0' || nextlocation2 == '<' || nextlocation2 == '>' || nextlocation2 == '(' || nextlocation2 == ')')
        {
            health--;
        }
        if (nextlocation == ' ' && nextlocation1 == ' ' && nextlocation2 == ' ')
        {
            eraseEnemy2(enemy2X, enemy2Y);
            enemy2X = enemy2X + 1;
            printEnemy2(enemy2X, enemy2Y);
        }
    }
    if (chaseY < 0) // down
    {
        char nextlocation = getCharAtxy(enemy2X, enemy2Y + 3);
        char nextlocation1 = getCharAtxy(enemy2X + 1, enemy2Y + 3);
        char nextlocation2 = getCharAtxy(enemy2X + 2, enemy2Y + 3);
        if (nextlocation == '0' || nextlocation == '>' || nextlocation == '<' || nextlocation == '(' || nextlocation == ')' || nextlocation1 == '0' || nextlocation1 == '>' || nextlocation1 == '<' || nextlocation1 == '(' || nextlocation1 == ')' || nextlocation2 == '0' || nextlocation2 == '<' || nextlocation2 == '>' || nextlocation2 == '(' || nextlocation2 == ')')
        {
            health--;
        }
        if (nextlocation == ' ' && nextlocation1 == ' ' && nextlocation2 == ' ')
        {
            eraseEnemy2(enemy2X, enemy2Y);
            enemy2Y = enemy2Y + 1;
            printEnemy2(enemy2X, enemy2Y);
        }
    }

    if (chaseY > 0) // up
    {
        char nextlocation = getCharAtxy(enemy2X, enemy2Y - 1);
        char nextlocation1 = getCharAtxy(enemy2X + 1, enemy2Y - 1);
        char nextlocation2 = getCharAtxy(enemy2X + 2, enemy2Y - 1);
        if (nextlocation == '0' || nextlocation == '>' || nextlocation == '<' || nextlocation == '(' || nextlocation == ')' || nextlocation1 == '0' || nextlocation1 == '>' || nextlocation1 == '<' || nextlocation1 == '(' || nextlocation1 == ')' || nextlocation2 == '0' || nextlocation2 == '<' || nextlocation2 == '>' || nextlocation2 == '(' || nextlocation2 == ')')
        {
            health--;
        }
        if (nextlocation == ' ' && nextlocation1 == ' ' && nextlocation2 == ' ')
        {
            eraseEnemy2(enemy2X, enemy2Y);
            enemy2Y = enemy2Y - 1;
            printEnemy2(enemy2X, enemy2Y);
        }
    }
}

void printEnemy3()
{
    for (int i = 0; i < 2; i++)
    {
        gotoxy(enemy3X, enemy3Y + i);
        for (int j = 0; j < 5; j++)
        {
            cout << Enemy3[i][j];
        }
        cout << endl;
    }
}
void eraseEnemy3()
{
    for (int i = 0; i < 2; i++)
    {
        gotoxy(enemy3X, enemy3Y + i);
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void moveMainEnemyLeft()
{
    char next = getCharAtxy(enemy3X - 1, enemy3Y);
    char next1 = getCharAtxy(enemy3X - 1, enemy3Y + 1);
    // char next2 = printMaze[enemy3Y + 2][enemy3X - 1];
    // char next3 = printMaze[enemy3Y + 3][enemy3X - 1];
    // char next4 = printMaze[enemy3Y + 4][enemy3X - 1];

    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    // if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%' && next4 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#' && next4 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!'&& next4 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-'&& next4 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<'&& next4 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx) && next4 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0' && next4 != '0'))
    {
        eraseEnemy3();
        enemy3X = enemy3X - 1;
        printEnemy3();
    }
    else
    {
        destination = "down";
    }

    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
}

void moveMainEnemyRight()
{
    char next = getCharAtxy(enemy3X + 5, enemy3Y);
    char next1 = getCharAtxy(enemy3X + 5, enemy3Y + 1);
    // char next2= printMaze[enemy3Y + 2][enemy3X + 4];
    // char next3 = printMaze[enemy3Y+ 3][enemy3X + 4];
    // char next4 = printMaze[enemy3Y+ 4][enemy3X + 4];

    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    // if ((next != '%' && next1 != '%' && next2 != '%' && next3 != '%' && next4 != '%') && (next != '#' && next1 != '#' && next2 != '#' && next3 != '#' && next4 != '#') && (next != '!' && next1 != '!' && next2 != '!' && next3 != '!'&& next4 != '!') && (next != '-' && next1 != '-' && next2 != '-' && next3 != '-'&& next4 != '-') && (next != '<' && next1 != '<' && next2 != '<' && next3 != '<'&& next4 != '<') && (next != char(boxx) && next1 != char(boxx) && next2 != char(boxx) && next3 != char(boxx) && next4 != char(boxx)) && (next != '0' && next1 != '0' && next2 != '0' && next3 != '0' && next4 != '0'))
    {
        eraseEnemy3();
        enemy3X = enemy3X + 1;
        printEnemy3();
    }
    else if ((next == '#' && next1 == '#') || (next == '!' && next1 == '!') || (next == '%' && next1 == '%'))
    {
        destination = "up";
    }
    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
}

void moveMainEnemyUp()
{
    char next = getCharAtxy(enemy3X, enemy3Y - 1);
    char next1 = getCharAtxy(enemy3X + 1, enemy3Y - 1);
    // char next2 = printMaze[enemy3Y - 1][enemy3X + 2];
    // char next3 = printMaze[enemy3Y - 1][enemy3X + 3];
    // char next4 = printMaze[enemy3Y - 1][enemy3X + 4];

    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    {
        eraseEnemy3();
        enemy3Y = enemy3Y - 1;
        printEnemy3();
    }
    else if ((next == '#' && next1 == '#') || (next == '!' && next1 == '!'))
    {
        destination = "left";
    }

    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
}

void moveMainEnemyDown()
{
    char next = getCharAtxy(enemy3X, enemy3Y + 4);
    char next1 = getCharAtxy(enemy3X + 1, enemy3Y + 4);
    // char next2 = printMaze[enemy3Y + 4][enemy3X + 2];
    // char next3 = printMaze[enemy3Y + 4][enemy3X + 3];
    // char next4 = printMaze[enemy3Y + 4][enemy3X + 4];

    if ((next != '%' && next1 != '%') && (next != '#' && next1 != '#') && (next != '!' && next1 != '!') && (next != '-' && next1 != '-') && (next != '<' && next1 != '<') && (next != char(boxx) && next1 != char(boxx)) && (next != '0' && next1 != '0'))
    {
        eraseEnemy3();
        enemy3Y = enemy3Y + 1;
        printEnemy3();
    }
    else if ((next == '#' && next1 == '#') || (next == '!' && next1 == '!'))
    {
        destination = "right";
    }

    if (next == '0' || next == '>' || next == '<' || next == '(' || next == ')' || next1 == '0' || next1 == '>' || next1 == '<' || next1 == '(' || next1 == ')')
    {
        health--;
    }
}

void moveEnemy3()
{
    {
        if (destination == "up")
        {
            moveMainEnemyUp();
        }
        else if (destination == "down")
        {
            moveMainEnemyDown();
        }
        else if (destination == "left")
        {
            moveMainEnemyLeft();
        }
        else if (destination == "right")
        {
            moveMainEnemyRight();
        }
    }
}

void bulletCollisionWithEnemy1()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (bulletX[x] + 1 == enemy1X && (bulletY[x] == enemy1Y || bulletY[x] == enemy1Y + 1 || bulletY[x] == enemy1Y + 2 || bulletY[x] == enemy1Y + 3))
        {
            addScore();
            eraseBulletenemy(bulletX[x], bulletY[x]);
            removeBulletFromArrayenemy(x);
            health--;
        }
    }
}

void printScore()
{
    gotoxy(109, 8);
    cout << "Score: " << score << " ";
}

void addScore()
{
    score += 5;
}

// void Exit()
// {

// }

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}


void storeData()
{
    fstream yourfile;
    yourfile.open("data.txt", ios::out);
    yourfile << score << ",";
    yourfile << health << ",";
    yourfile << mainX << ",";
    yourfile << mainY << ",";
    yourfile << enemy1X << ",";
    yourfile << enemy1Y << ",";
    yourfile << enemy2X << ",";
    yourfile << enemy2Y << ",";
    yourfile << enemy3X << ",";
    yourfile << enemy3Y << ",";
    yourfile << escapeKeyX << ",";
    yourfile << escapeKeyY << ","<< endl;
    yourfile.close();
}