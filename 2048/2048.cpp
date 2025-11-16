#include <iostream>
#include <iomanip>
#include <string> // для работы с std::string
#include <time.h>
#include "Win10.h"

using namespace std;
#define RND(min, max)  (rand()%((max)-(min)+1)+(min))

//Прототипы функции
void Draw(); // игровое поле
void StartGame(); // Старт игры
void ShowBoard(int StartRow, int StartCol, int board[4][4]);  // прорисовка цифр

void About(); // об авторе
void GameInfo(); // инструкция по игре
void DecorMainMenu(); // декор. для меню

bool RandNum2(int board[4][4]); // два рандомных чисел для начала игры
bool RandNum(int board[4][4]); // рандомное число после каждого ход
string Space(int board);
bool GameWin(bool IsGameOver, int board[4][4]);

bool MoveUp(int board[4][4], int& Score); // сдвиг вверх
bool MoveDown(int board[4][4], int& Score); // сдвиг вниз
bool MoveLeft(int board[4][4], int& Score); // сдвиг влево
bool MoveRight(int board[4][4], int& Score); // сдвиг вправо
void CopyBoardStep(int CopyBoard[4][4], int board[4][4]);
void ShowCopyBoard(int CopyBoard[4][4], int board[4][4]);

bool GameLose(bool gameover, int board[4][4], int Score);

//глобальные переменные

int MenuRow = 4, MenuCol = 6;
int Select = 0;
int Record = 0;

int StartRow = 4;
int StartCol = 9;

//Размер массива
int BoardRow = 4;
int BoardCol = 4;

//Шаг между ячейками
int StepOnRow = 4;
int StepOnCol = 10;

//Цвета для меню
int colSelFon = COLOR::light_blue; // цвет фона
int colSelSym = COLOR::light_yellow; // цвет символа
// неактивного
int colUnSelFon = COLOR::white; // цвет фона
int colUnSelSym = COLOR::black; // цвет символа

// цвет по умолчанию (0,7)
int colDefFon = COLOR::black; // черный фон
int colDefSym = COLOR::white; // белые буквы

//Функция для старта игры
void StartGame() {
    system("cls");

    int board[4][4] = { 0 };  //Массив 4х4
    int CopyBoard[4][4] = { 0 };
    bool IsGameOver = false;
    int key = 0;
    system("chcp 1251 > nul");
    RandNum2(board);
    int Step = 0;
    int Score = 0;
    while (!IsGameOver)  // Цикл пока идет игра
    {
        ShowBoard(StartRow, StartCol, board);  //постоянная прорисовка
        Draw(); //игровое поле
        SetPos(3, 49);

        cout << "Score: " << Score;  //очки набранные игроком
        key = _getch();
        switch (key) {
        case _KEY::UP:
            system("cls"); //ход вверх
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveUp(board, Score);
            RandNum(board);
            break;
        case _KEY::DOWN:
            system("cls");  //ход вниз
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveDown(board, Score);
            RandNum(board);
            break;
        case _KEY::LEFT:
            system("cls");  // ход влево
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveLeft(board, Score);
            RandNum(board);
            break;
        case _KEY::RIGHT:
            system("cls");  //ход вправо
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveRight(board, Score);
            RandNum(board);
            break;
        case 'w': case 'W':
            system("cls");
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveUp(board, Score);
            RandNum(board);
            break;
        case 's':case'S':
            system("cls");
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveDown(board, Score);
            RandNum(board);
            break;
        case'a':case'A':
            system("cls");
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveLeft(board, Score);
            RandNum(board);
            break;
        case 'd':case'D':
            system("cls");
            Step++;
            CopyBoardStep(CopyBoard, board);
            MoveRight(board, Score);
            RandNum(board);
            break;
        case _KEY::ESC:
            SetPos(20, 8);
            cout << "Вы действительно хоите выйти? y/n: ";
            //cin >> sym;
            char sym;
            cin >> sym;
            if (sym == 'y' || sym == 'Y') {
                IsGameOver = true;
            }
            else if (sym == 'n' || sym == 'N') {
                system("cls");
            }
            else {
                CursorHide(TRUE, 100);
                SetPos(23, 8);
                cout << "Не правильно введена буква. Для повторного ввода нажмите на кнопку ESC: " << endl;
            }
            break;
        case _KEY::F1:
            system("chcp 1251 > nul");
            system("cls");
            cout << "1. In each round, a tile with a value of ‘2’ (with a probability of 91%) or ‘4’ (with a probability of 9%) appears." << endl;
            cout << endl;
            cout << "2. By pressing the arrow, the player can drop all the tiles on the playing field in one of four directions. If, when dropping, two tiles of the same denomination ‘fly’ into each other, they stick together into one tile, the denomination of which is equal to the sum of the joined tiles. After each move, a new tile with a value of ‘2’ or ‘4’ appears on a free section of the field. If pressing the button does not change the location or value of the tiles, then the move is not made." << endl;
            cout << endl;
            cout << "3. If there are more than two tiles of the same value in a row or column, they will stick together on the side they were facing when they are cleared. For example, tiles (4, 4, 4) in the same row will turn into (8, 4) after a move to the left, and into (4, 8) after a move to the right. This handling of ambiguity allows for a more precise game strategy." << endl;
            cout << endl;
            cout << "4. For each connection, the game points increase by the value of the resulting tile." << endl;
            cout << endl;
            cout << "5. The game ends in defeat if it is impossible to perform an action after the next move." << endl;
            cout << endl;
            cout << "To continue the game, press any key..." << endl;
            cout << endl;
            cout << "Author: Student SDP-212.2 group, Nurgazy Talgat. " << endl;
            system("pause>nul");
            system("cls");
            break;
        case _KEY::SPACE:
            SetColor(COLOR::black, RND(1, 15));
            break;
        case _KEY::BACKSPACE:
            if (Step > 0) {
                ShowCopyBoard(CopyBoard, board);   // Функция копирования массива (отмена хода)
            }
            ShowBoard(StartRow, StartCol, board);
            break;

        }
        for (int i = 0; i < BoardRow; i++)
        {
            for (int j = 0; j < BoardCol; j++)
            {
                if (board[i][j] == 2048) {
                    IsGameOver = true;

                }
            }
        }

    }
    GameLose(IsGameOver, board, Score);
    if (IsGameOver == true)
    {
        CursorHide(FALSE);
        SetPos(22, 8);
        cout << "Game Over!";
        SetPos(24, 8);
        cout << "Спасибо за игру! :)" << endl;
        SetPos(25, 8);
        cout << "Thanks for playing! :)";
        SetPos(26, 8);
        cout << "Your Score: " << Score;
        system("pause > nul");
        system("cls");
    }

}


bool GameLose(bool gameover, int board[4][4], int Score)
{
    if (MoveUp(board, Score) == false && MoveDown(board, Score) == false && MoveRight(board, Score) == false && MoveLeft(board, Score) == false)
    {
        gameover = true;
    }
    return gameover;

}

void ShowCopyBoard(int CopyBoard[4][4], int board[4][4])
{
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            board[i][j] = CopyBoard[i][j];
        }
    }
}


void CopyBoardStep(int CopyBoard[4][4], int board[4][4])
{
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            CopyBoard[i][j] = board[i][j];
        }
    }
}

int RandomNum() {
    int Ran = RND(0, 100);
    if (Ran > 10) {
        return 2;
    }
    else if (Ran < 10) {
        return 4;
    }
    return 0;
}

//Игровое поле
void Draw() {
    system("chcp 866 > nul");
    srand(time(0));
    for (int i = 0; i < 16; i++) {
        SetPos(3 + i, 8);                  // левая линия
        cout << char(186) << endl;
    }
    SetPos(6, 8);
    cout << char(204);

    SetPos(6, 17);
    cout << char(206);

    SetPos(2, 8);
    cout << char(201);
    for (int i = 0; i < 8; i++) {
        SetPos(2, i + 9);                      //верхняя линия
        cout << char(205);
    }

    for (int i = 0; i < 8; i++) {
        SetPos(2, i + 27);
        cout << char(205);
    }
    cout << char(203);

    for (int i = 0; i < 8; i++) {
        SetPos(2, i + 36);
        cout << char(205);
    }

    SetPos(2, 17);
    cout << char(203);

    for (int i = 0; i < 8; i++) {
        SetPos(2, i + 18);
        cout << char(205);
    }
    SetPos(2, 26);
    cout << char(203);

    SetPos(2, 44);
    cout << char(187);
    for (int i = 0; i < 16; i++) {
        SetPos(3 + i, 44);             //правая линия
        cout << char(186) << endl;
    }
    SetPos(18, 8);
    cout << char(200);
    for (int i = 0; i < 8; i++) {
        SetPos(18, i + 9);
        cout << char(205);
    }
    SetPos(18, 17);              // нижняя линия
    cout << char(202);

    for (int i = 0; i < 8; i++) {
        SetPos(18, i + 18);
        cout << char(205);
    }
    cout << char(202);

    for (int i = 0; i < 8; i++) {
        SetPos(18, i + 27);
        cout << char(205);
    }
    cout << char(202);
    for (int i = 0; i < 8; i++) {
        SetPos(18, i + 36);
        cout << char(205);
    }
    SetPos(18, 44);
    cout << char(188);

    //Центральные линии

    for (int i = 0; i < 3; i++) {  //первая центральная линия слева
        SetPos(3 + i, 17);
        cout << char(186) << endl;
    }

    //SetPos(19, 50);
    for (int i = 0; i < 3; i++) {
        SetPos(3 + i, 26);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 3; i++) {
        SetPos(3 + i, 35);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 8; i++) {
        SetPos(6, i + 9);
        cout << char(205);
    }
    for (int i = 0; i < 8; i++) {
        SetPos(6, i + 18);
        cout << char(205);
    }
    cout << char(206);
    for (int i = 0; i < 8; i++) {
        SetPos(6, i + 27);
        cout << char(205);
    }
    cout << char(206);
    for (int i = 0; i < 8; i++) {
        SetPos(6, i + 36);
        cout << char(205);
    }
    cout << char(185);
    SetPos(10, 8);
    cout << char(204);
    SetPos(14, 8);
    cout << char(204);
    SetPos(14, 44);
    cout << char(185);
    for (int i = 0; i < 8; i++) {
        SetPos(10, i + 9);
        cout << char(205);
    }
    for (int i = 0; i < 8; i++) {
        SetPos(10, i + 18);
        cout << char(205);
    }
    cout << char(206);
    for (int i = 0; i < 8; i++) {
        SetPos(10, i + 27);
        cout << char(205);
    }
    cout << char(206);
    for (int i = 0; i < 8; i++) {
        SetPos(10, i + 36);
        cout << char(205);
    }
    cout << char(185);

    for (int i = 0; i < 3; i++) {  //первая центральная линия слева
        SetPos(7 + i, 17);
        cout << char(186) << endl;
    }
    SetPos(10, 17);
    cout << char(206);

    for (int i = 0; i < 3; i++) {
        SetPos(7 + i, 26);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 3; i++) {
        SetPos(7 + i, 35);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 3; i++) {
        SetPos(11 + i, 17);
        cout << char(186) << endl;
    }

    //SetPos(19, 50);
    for (int i = 0; i < 3; i++) {
        SetPos(11 + i, 26);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 3; i++) {
        SetPos(11 + i, 35);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 35; i++) {
        SetPos(14, i + 9);
        cout << char(205);
    }

    for (int i = 0; i < 8; i++) {
        SetPos(14, i + 9);
        cout << char(205);
    }

    for (int i = 0; i < 8; i++) {
        SetPos(14, i + 26);
        cout << char(205);
    }

    for (int i = 0; i < 4; i++) {
        SetPos(14 + i, 17);
        cout << char(186) << endl;
    }
    //SetPos(19, 50);
    for (int i = 0; i < 4; i++) {
        SetPos(14 + i, 26);
        cout << char(186) << endl;
    }

    for (int i = 0; i < 4; i++) {
        SetPos(14 + i, 35);
        cout << char(186) << endl;
    }

    SetPos(14, 17);
    cout << char(206);
    SetPos(14, 26);
    cout << char(206);
    SetPos(14, 35);
    cout << char(206);

    //system("chcp 1251 > nul");

    SetPos(7, 49);
    cout << "W" << " => " << "Up";
    SetPos(8, 49);
    cout << "S" << " => " << "Down";
    SetPos(10, 49);
    cout << "A" << " => " << "Left";
    SetPos(11, 49);
    cout << "D" << " => " << "Right";

    SetPos(13, 49);
    cout << "ESC - Exit";
    SetPos(14, 49);
    cout << "F1 - Information";
    SetPos(15, 49);
    cout << "BACKSPACE - Cancel last step";
    SetPos(17, 49);
    cout << "SPACE - Customize color";

    system("chcp 1251 > nul");
}

void ShowBoard(int StartRow, int StartCol, int board[4][4])
{

    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            SetPos(StartRow + i * StepOnRow, StartCol + j * StepOnCol);
            if (board[i][j] != 0)
            {
                cout << Space(board[i][j]) << board[i][j];
            }
            else { cout << "    "; }
        }
    }
}

bool RandNum2(int board[4][4])
{
    bool AddNewNum = false;
    int RandRow = 0;
    int RandCol = 0;

    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            if (board[i][j] == 0) {
                AddNewNum = true;
            }
        }
    }
    bool Add = false;
    while (AddNewNum && !Add)
    {
        RandRow = RND(0, 3);
        RandCol = RND(0, 3);
        if (board[RandRow][RandCol] == 0)
        {
            board[RND(0, 3)][RND(0, 3)] = RandomNum();
            board[RND(0, 3)][RND(0, 3)] = RandomNum();
            Add = true;
        }
    }
    return Add;
}

bool RandNum(int board[4][4])
{
    bool AddNewNum = false;
    int RandRow = 0;
    int RandCol = 0;
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            if (board[i][j] == 0) {
                AddNewNum = true;
            }
        }
    }
    bool Add = false;
    while (AddNewNum && !Add)
    {
        RandRow = RND(0, 3);
        RandCol = RND(0, 3);
        if (board[RandRow][RandCol] == 0) {
            board[RandRow][RandCol] = RandomNum();
            Add = true;
        }
    }
    return Add;
}

void GameInfo()
{
    system("cls");
    cout << "1. In each round, a tile with a value of ‘2’ (with a probability of 90.9090909%) or ‘4’ (with a probability of 9.09090909%) appears." << endl;
    cout << endl;
    cout << "2. By pressing the arrow, the player can drop all the tiles on the playing field in one of four directions. If, when dropping, two tiles of the same denomination ‘fly’ into each other, they stick together into one tile, the denomination of which is equal to the sum of the joined tiles. After each move, a new tile with a value of ‘2’ or ‘4’ appears on a free section of the field. If pressing the button does not change the location or value of the tiles, then the move is not made." << endl;
    cout << endl;
    cout << "3. If there are more than two tiles of the same value in a row or column, they will stick together on the side they were facing when they are discarded. For example, tiles (4, 4, 4) in the same row will turn into (8, 4) after a move to the left, and into (4, 8) after a move to the right. This handling of ambiguity allows for a more precise game strategy." << endl;
    cout << endl;
    cout << "4. For each connection, the game points increase by the value of the resulting tile." << endl;
    cout << endl;
    cout << "5. The game ends in defeat if it is impossible to perform an action after the next move." << endl;

    SetPos(7, 0);
    cout << "The playing field is 4x4. By pressing the SPACE key, you can customise the colour of the field to your liking." << endl;
    cout << endl;
    cout << "By pressing the keys: Up, Down, Left, Right, w, s, a, d, W, S, A, D, you can move the numbers around the field according to the rules of the game." << endl;
    cout << endl;

    cout << "Up    -  to up" << endl;
    cout << "Down  -  to down" << endl;
    cout << "Left  -  to left" << endl;
    cout << "Right -  to right" << endl;
    SetPos(15, 0);
    cout << "To continue, press any key..." << endl;

    SetPos(9, 30);
    cout << "w - Up" << endl;
    SetPos(10, 30);
    cout << "s - Down" << endl;
    SetPos(11, 30);
    cout << "a - Left" << endl;
    SetPos(12, 30);
    cout << "d - Right" << endl;
    SetPos(13, 30);
    cout << "The same applies to capital letters." << endl;

    system("pause > nul");
    system("cls");
}

void About()
{
    system("cls");
    SetPos(5, 25);
    cout << "The game was developed by a student";
    SetPos(7, 25);
    cout << "SDP-212.2 groups";
    SetPos(9, 25);
    cout << "Nurgazy Talgat";
    system("pause > nul");
    system("cls");
}

void DecorMainMenu()
{
    system("chcp 866 > nul");

    SetColor(COLOR::black, yellow);
    for (int i = 0; i < 119; i++)
    {
        cout << char(220);
    }
    for (int i = 0; i < 25; i++)
    {
        cout << char(220) << endl;
    }
    for (int i = 0; i < 120; i++)
    {
        cout << char(220);
    }
    for (int i = 0; i < 25; i++)
    {
        SetPos(0 + i, 119);
        cout << char(220) << endl;
    }
    SetPos(9, 44);
    cout << char(16);
    SetPos(9, 63);
    cout << char(17);

    SetPos(11, 46);
    cout << char(16);
    SetPos(11, 61);
    cout << char(17);

    SetPos(13, 47);
    cout << char(16);
    SetPos(13, 60);
    cout << char(17);

    SetPos(15, 50);
    cout << char(16);
    SetPos(15, 57);
    cout << char(17);
}

string Space(int board)
{
    if (board == 2 || board == 8 || board == 4)
    {
        return "   "; // количество пробелов 3
    }
    if (board == 16 || board == 64 || board == 32)
    {

        return "  "; // количество пробелов 2
    }
    if (board == 128 || board == 256 || board == 512)
    {

        return " "; // количество пробелов 1
    }
    if (board == 2048)
    {
        return ""; // количество пробелов 0
    }
}

int main()
{
    DecorMainMenu();
    system("chcp 1251 > nul");
    srand(time(0));

    bool isExit = false;

    while (!isExit) // for(;;)
    {
        system("chcp 1251 > nul");
        CursorHide();//скрыть курсор
        // 1) печать, вывод пунктов меню (Начать игру, Информация, Об авторах, и т.д.);
        SetPos(MenuRow + 5, MenuCol + 40);
        if (Select == 0) { SetColor(colSelFon, colSelSym); }
        else { SetColor(colUnSelFon, colUnSelSym); }
        cout << "Start Game 2048";
            
        SetPos(MenuRow + 7, MenuCol + 40);
        if (Select == 1) { SetColor(colSelFon, colSelSym); }
        else { SetColor(colUnSelFon, colUnSelSym); }
        cout << "Rules";

        SetPos(MenuRow + 9, MenuCol + 40);
        if (Select == 2) { SetColor(colSelFon, colSelSym); }
        else { SetColor(colUnSelFon, colUnSelSym); }
        cout << "Author";

        SetPos(MenuRow + 11, MenuCol + 40);
        if (Select == 3) { SetColor(colSelFon, colSelSym); }
        else { SetColor(colUnSelFon, colUnSelSym); }
        cout << "Exit";

        // восстановление цвета вывода по умолчанию
        SetColor(colDefFon, colDefSym);

        // 2) обработка нажатия клавиш:
        //if(_kbhit())  // if (_kbhit() != 0)
        {
            int key = _getch(); // _getche();
            // если пользователь нажал на кнопку - узнать
            // на какую кнопку нажал пользователь
            // среагировать на нажатие кнопок ESC,
            // ENTER, UP/DOWN/LEFT/RIGHT
            switch (key)
            {
            case _KEY::UP: // вверх
                if (Select > 0) { Select--; }
                break;
            case _KEY::DOWN: // вниз
                if (Select < 3) { Select++; }
                break;
            case _KEY::ENTER: // выбор пункта меню

                // обработка пунктов меню
                switch (Select) { // вложенный оператор switch
                case 0: // Начать новую игру-2048
                    StartGame(); // вызов функции StartGameXO() для запуска игры
                    break;
                case 1: //Информация о игре
                    GameInfo();
                    break;
                case 2: // Об авторе
                    About();
                    break;
                case 3: // Exit
                    isExit = true; // Cигнал о завершении игры
                    system("cls");
                    break;
                }
                break;
            case _KEY::ESC: // нажата ESC - выход из меню
                // return 0;
                system("cls");
                isExit = true; // сигнал о завершении работы программы
                break;
            } // switch();
            /*if (isExit == true) {
             break; // выход из цикла while(true) - обрыв цикла
            }*/
        } // if(_kbhit())
    } // while(true)
    // удаление старой надписи
    SetPos(MenuRow + 6, MenuCol - 2);
    cout << "                                ";
    // вывод новой надписи
    SetPos(MenuRow + 6, MenuCol - 2);
    cout << "Goob bye...";

    //cin.get(); cin.get(); // блокирующие консоль ф-ции
} // main()    

bool GameWin(bool IsGameOver, int board[4][4])
{
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            if (board[i][j] == 2048)
            {
                IsGameOver = true;
                return IsGameOver;
                break;
            }
        }
    }
}



bool MoveUp(int board[4][4], int& Score)
{
    bool MoveU = false;
    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = 0; i < BoardRow; i++)
        {
            if (board[i][j] == 0)  // Передвигать цифры если они не равны
            {
                for (int k = i + 1; k < BoardRow; k++)
                {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        MoveU = true;
                        break;
                    }
                }
            }
        }
    }

    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = BoardRow - 1; i > 0; i--)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == board[i - 1][j]) //Соеденить цифры если они одинаковы
                {
                    board[i - 1][j] *= 2;
                    Score += board[i - 1][j];
                    board[i][j] = 0;
                    MoveU = true;
                }
            }
        }
    }
    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = 0; i < BoardRow; i++)
        {
            if (board[i][j] == 0)  // Передвигать цифры если они не равны
            {
                for (int k = i + 1; k < BoardRow; k++)
                {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        MoveU = true;
                        break;
                    }
                }
            }
        }
    }
    return MoveU;
}


bool MoveDown(int board[4][4], int& Score) {
    bool MoveD = false;
    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = BoardRow - 1; i > 0; i--)
        {
            if (board[i][j] == 0)
            {
                for (int k = i - 1; k >= 0; k--)
                {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        MoveD = true;
                        break;
                    }
                }
            }
        }
    }

    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = 0; i < BoardRow; i++)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == board[i + 1][j])
                {
                    board[i + 1][j] *= 2;
                    Score += board[i + 1][j];
                    board[i][j] = 0;
                    MoveD = true;
                }
            }
        }
    }
    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = BoardRow - 1; i > 0; i--)
        {
            if (board[i][j] == 0)
            {
                for (int k = i - 1; k >= 0; k--)
                {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        MoveD = true;
                        break;
                    }
                }
            }
        }
    }
    return MoveD;
}

bool MoveRight(int board[4][4], int& Score)
{
    bool MoveR = false;
    for (int i = BoardRow - 1; i >= 0; i--)
    {
        for (int j = BoardCol - 1; j >= 0; j--)
        {
            if (board[i][j] == 0)
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        MoveR = true;
                        break;
                    }
                }
            }
        }
    }
    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = BoardRow - 1; i >= 0; i--)
        {
            if (board[j][i] != 0)
            {
                if (board[j][i] == board[j][i - 1])  // Соеденить одинаковые цифры 
                {
                    board[j][i] *= 2;
                    Score += board[j][i];
                    board[j][i - 1] = 0;
                    MoveR = true;
                }
            }
        }
    }
    for (int i = BoardRow - 1; i >= 0; i--)
    {
        for (int j = BoardCol - 1; j >= 0; j--)
        {
            if (board[i][j] == 0)
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        MoveR = true;
                        break;
                    }
                }
            }
        }
    }
    return MoveR;
}

bool MoveLeft(int board[4][4], int& Score)
{
    bool Move = false;
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            if (board[i][j] == 0)
            {
                for (int k = j + 1; k < BoardCol; k++)
                {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        Move = true;
                        break;
                    }
                }
            }
        }
    }

    for (int j = 0; j < BoardCol; j++)
    {
        for (int i = 0; i < BoardRow; i++)
        {
            if (board[j][i] != 0)
            {
                if (board[j][i] == board[j][i + 1])
                {
                    board[j][i] *= 2;
                    Score += board[i][j];
                    board[j][i + 1] = 0;
                    Move = true;

                }
            }
        }
    }
    for (int i = 0; i < BoardRow; i++)
    {
        for (int j = 0; j < BoardCol; j++)
        {
            if (board[i][j] == 0)
            {
                for (int k = j + 1; k < BoardCol; k++)
                {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        Move = true;
                        break;
                    }
                }
            }
        }
    }
    return Move;
}