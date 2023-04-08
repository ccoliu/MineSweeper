#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <sstream>
using namespace std;

int col = 0, row = 0;
int bombNum = 0;
int flagNum = 0;
int openedNum = 0;
int remainNum = 0;
char** devBoard;
char** board;
char** gameBoard;
ifstream inFile;
ofstream outFile;
ifstream in;



void CountItem()
{
    flagNum = 0;
    openedNum = 0;
    remainNum = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (gameBoard[i][j] == '#' && board[i][j] != 'X')
            {
                remainNum++;
            }
            if (gameBoard[i][j] == 'F')
            {
                flagNum++;
            }
            if (isdigit(gameBoard[i][j]))
            {
                openedNum++;
            }
        }
    }
}

void ClearBoard()
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            gameBoard[i][j] = '#';
        }
    }
}

void expandBoard(int y, int x)
{
    gameBoard[y][x] = board[y][x];
    if (gameBoard[y][x] != '0') return;
    if (x - 1 >= 0 && y - 1 >= 0 && gameBoard[y - 1][x - 1] == '#' && board[y - 1][x - 1] != 'X')
    {
        expandBoard(y - 1, x - 1);
    }
    if (x + 1 < row && y - 1 >= 0 && gameBoard[y - 1][x + 1] == '#' && board[y - 1][x + 1] != 'X')
    {
        expandBoard(y - 1, x + 1);
    }
    if (x - 1 >= 0 && y + 1 < col && gameBoard[y + 1][x - 1] == '#' && board[y + 1][x - 1] != 'X')
    {
        expandBoard(y + 1, x - 1);
    }
    if (x + 1 < row && y + 1 < col && gameBoard[y + 1][x + 1] == '#' && board[y + 1][x + 1] != 'X')
    {
        expandBoard(y + 1, x + 1);
    }
    if (y - 1 >= 0 && gameBoard[y - 1][x] == '#' && board[y - 1][x] != 'X')
    {
        expandBoard(y - 1, x);
    }
    if (y + 1 < col && gameBoard[y + 1][x] == '#' && board[y + 1][x] != 'X')
    {
        expandBoard(y + 1, x);
    }
    if (x - 1 >= 0 && gameBoard[y][x - 1] == '#' && board[y][x - 1] != 'X')
    {
        expandBoard(y, x - 1);
    }
    if (x + 1 < row && gameBoard[y][x + 1] == '#' && board[y][x + 1] != 'X')
    {
        expandBoard(y, x + 1);
    }
    return;
}

void NoteBoard(int y, int x)
{
    if (gameBoard[y][x] == '#')
    {
        gameBoard[y][x] = 'F';
    }
    else if (gameBoard[y][x] == 'F')
    {
        gameBoard[y][x] = '?';
    }
    else gameBoard[y][x] = '#';
}

void ClickBoard(int y, int x)
{
    gameBoard[y][x] = board[y][x];
    if (gameBoard[y][x] == 'X')
    {
        return;
    }
    else if (gameBoard[y][x] == '0')
    {
        expandBoard(y, x);
    }
}

char checkSurroundMines(char** board, int y, int x)
{
    int mines = 0;
    if (board[y][x] == 'X') return 'X';
    for (int i = y - 1; i <= y + 1; i++)
    {
        if (i < 0 || i >= col) continue;
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (j < 0 || j >= row) continue;
            if (board[i][j] == 'X') mines++;
        }
    }
    return mines + '0';
}

void printBoard(char** board)
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            outFile << board[i][j] << " ";
        }
        outFile << endl;
    }
}

void printCinBoard(char** board)
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void makeBoardRandom(int r, int c, string attr, int count, double rate)
{
    srand(time(NULL));
    row = r;
    col = c;
    board = new char* [col];
    gameBoard = new char* [col];
    devBoard = new char* [col];
    for (int i = 0; i < col; i++)
    {
        board[i] = new char[row];
        gameBoard[i] = new char[row];
        devBoard[i] = new char[row];
    }
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            devBoard[i][j] = 'O';
        }
    }
    if (attr == "count")
    {
        int y, x;
        for (int i = 0; i < count; i++)
        {
            y = rand() % col;
            x = rand() % row;
            if (devBoard[y][x] == 'X')
            {
                i--;
                continue;
            }
            devBoard[y][x] = 'X';
        }
    }
    if (attr == "rate")
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
            {
                int n = rand() % 100;
                if (n < rate * 100) devBoard[i][j] = 'X';
            }
        }
    }
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            board[i][j] = checkSurroundMines(devBoard, i, j);
            gameBoard[i][j] = '#';
        }
    }
}

void makeBoard(ifstream &in)
{
    in >> col >> row;
    board = new char* [col];
    gameBoard = new char* [col];
    devBoard = new char* [col];
    for (int i = 0; i < col; i++)
    {
        board[i] = new char[row];
        gameBoard[i] = new char[row];
        devBoard[i] = new char[row];
    }
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            char s;
            in >> s;
            if (s == 'X') bombNum++;
            devBoard[i][j] = s;
        }
    }
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            board[i][j] = checkSurroundMines(devBoard, i, j);
            gameBoard[i][j] = '#';
        }
    }
}

void ConditionCinOutput(string seq, int flag, string additional)
{
    if (flag == 1)
    {
        cout << "< " << seq << " > " << ": Success" << endl;
    }

    else if (flag == 0)
    {
        cout << "< " << seq << " > " << ": Failed " << additional << endl;
    }
    else
    {
        cout << "< " << seq << " > : " << additional << endl;
    }
}

void ConditionOutput(string seq, int flag, string additional)
{
    if (flag == 1)
    {
        outFile << "< " << seq << " > " << ": Success" << endl;
    }
    else if (flag == 0)
    {
        outFile << "< " << seq << " > " << ": Failed " << additional << endl;
    }
    else
    {
        outFile << "< " << seq << " > : " << additional << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1 || argc == 2)
    {
        string method;
        string cOutput;
        string status = "Standby";
        bool hasLoaded = false;

        while (cin >> method)
        {
            cOutput = method;

            if (method != "Load" && method != "StartGame" && method != "Print" && method != "LeftClick" && method != "RightClick" && method != "Replay" && method != "Quit")
            {
                ConditionCinOutput(cOutput, 0, ": No such method.");
                continue;
            }

            if (method == "Load")
            {
                string type;
                cin >> type;
                cOutput += " " + type;
                if (type == "BoardFile")
                {
                    string filename;
                    cin >> filename;
                    if (status != "Standby")
                    {
                        ConditionCinOutput(cOutput + " " + filename, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ifstream in(filename);
                    if (in.is_open())
                    {
                        hasLoaded = true;
                        ConditionCinOutput(cOutput + " " + filename, 1, "");
                        makeBoard(in);
                    }
                    else
                    {
                        ConditionCinOutput(cOutput + " " + filename, 0, ": File can't find!");
                    }
                }
                if (type == "RandomCount")
                {
                    int m, n, mines;
                    cin >> m >> n >> mines;
                    cOutput += " " + to_string(m) + " " + to_string(n) + " " + to_string(mines);
                    if (status != "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 1, " ");
                    makeBoardRandom(m, n, "count", mines, 0);
                }
                if (type == "RandomRate")
                {
                    int m, n;
                    double rate;
                    cin >> m >> n >> rate;
                    string s = to_string(rate);
                    string str = "";
                    if (rate < 1 && rate > 0)
                    {
                        for (int i = 0; i < s.length(); i++)
                        {
                            if (i > 1 && s[i] == '0') break;
                            str += s[i];
                        }
                    }
                    else str = s[0];
                    cOutput += " " + to_string(m) + " " + to_string(n) + " " + str;
                    if (status != "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 1, " ");
                    makeBoardRandom(m, n, "rate", 0, rate);
                }
            }
            if (method == "Print")
            {
                string type;
                cin >> type;
                cOutput += " " + type;
                if (type == "GameBoard")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, "");
                    printCinBoard(gameBoard);
                }
                if (type == "GameState")
                {
                    ConditionCinOutput(cOutput, 2, status);
                }
                if (type == "GameAnswer")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, "");
                    printCinBoard(board);
                }
                if (type == "BombCount")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, to_string(bombNum));
                }
                if (type == "FlagCount")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, to_string(flagNum));
                }
                if (type == "OpenBlankCount")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, to_string(openedNum));
                }
                if (type == "RemainBlankCount")
                {
                    if (status == "Standby")
                    {
                        ConditionCinOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionCinOutput(cOutput, 2, to_string(remainNum));
                }
            }
            if (method == "StartGame")
            {
                if (status != "Standby")
                {
                    ConditionCinOutput(cOutput, 0, ": Game has already started/ended!");
                    continue;
                }
                if (hasLoaded == false)
                {
                    ConditionCinOutput(cOutput, 0, ": No board to play!");
                    continue;
                }
                ConditionCinOutput(cOutput, 1, "");
                status = "Playing";
            }
            if (method == "LeftClick")
            {
                int y, x;
                cin >> x >> y;
                cOutput += " " + to_string(x) + " " + to_string(y);
                if (status != "Playing")
                {
                    ConditionCinOutput(cOutput, 0, ": Not in playing state!");
                    continue;
                }
                if (y < 0 || x < 0 || x >= row || y >= col)
                {
                    ConditionCinOutput(cOutput, 0, ": Out of range!");
                    continue;
                }
                if (gameBoard[y][x] == 'F')
                {
                    ConditionCinOutput(cOutput, 0, ": This coordinate has been flaged, unflag it to click on it.");
                    continue;
                }
                if (isdigit(gameBoard[y][x]))
                {
                    ConditionCinOutput(cOutput, 0, ": This coordinate has already been opened!");
                    continue;
                }
                ConditionCinOutput(cOutput, 1, "");
                ClickBoard(y, x);
                CountItem();
                if (gameBoard[y][x] == 'X')
                {
                    cout << "Stepped on mine! Game end." << endl;
                    status = "GameOver";
                }
                if (status != "GameOver" && remainNum == 0)
                {
                    cout << "There is no spare blocks left, you win!" << endl;
                    status = "GameOver";
                }
            }
            if (method == "RightClick")
            {
                int y, x;
                cin >> x >> y;
                cOutput += " " + to_string(x) + " " + to_string(y);
                if (status != "Playing")
                {
                    ConditionCinOutput(cOutput, 0, ": Not in playing state!");
                    continue;
                }
                if (y < 0 || x < 0 || x >= row || y >= col)
                {
                    ConditionCinOutput(cOutput, 0, ": Out of range!");
                    continue;
                }
                if (isdigit(gameBoard[y][x]))
                {
                    ConditionCinOutput(cOutput, 0, ": This coordinate has already been opened!");
                    continue;
                }
                ConditionCinOutput(cOutput, 1, "");
                NoteBoard(y, x);
                CountItem();
            }
            if (method == "Replay")
            {
                if (status != "GameOver")
                {
                    ConditionCinOutput(cOutput, 0, ": Game is not over/Game has not started!");
                    continue;
                }
                ConditionCinOutput(cOutput, 1, "");
                status = "Standby";
                ClearBoard();
            }
            if (method == "Quit")
            {
                if (status != "GameOver")
                {
                    ConditionCinOutput(cOutput, 0, ": Game is not over/Game has not started!");
                    continue;
                }
                ConditionCinOutput(cOutput, 1, "");
                break;
            }
        }
    }
    else if (argc == 4)
    {
        string method;
        string cOutput;
        string status = "Standby";
        bool hasLoaded = false;

        while (inFile >> method)
        {
            cOutput = method;

            if (method != "Load" && method != "StartGame" && method != "Print" && method != "LeftClick" && method != "RightClick" && method != "Replay" && method != "Quit")
            {
                ConditionOutput(cOutput, 0, ": No such method.");
                continue;
            }

            if (method == "Load")
            {
                string type;
                inFile >> type;
                cOutput += " " + type;
                if (type == "BoardFile")
                {
                    string filename;
                    inFile >> filename;
                    if (status != "Standby")
                    {
                        ConditionOutput(cOutput + " " + filename, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ifstream in(filename);
                    if (in.is_open())
                    {
                        hasLoaded = true;
                        ConditionOutput(cOutput + " " + filename, 1, "");
                        makeBoard(in);
                    }
                    else
                    {
                        ConditionOutput(cOutput + " " + filename, 0, ": File can't find!");
                    }
                }
                if (type == "RandomCount")
                {
                    int m, n, mines;
                    inFile >> m >> n >> mines;
                    cOutput += " " + to_string(m) + " " + to_string(n) + " " + to_string(mines);
                    if (status != "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ConditionOutput(cOutput, 1, " ");
                    makeBoardRandom(m, n, "count", mines, 0);
                }
                if (type == "RandomRate")
                {
                    int m, n;
                    double rate;
                    inFile >> m >> n >> rate;
                    string s = to_string(rate);
                    string str = "";
                    if (rate < 1 && rate > 0)
                    {
                        for (int i = 0; i < s.length(); i++)
                        {
                            if (i > 1 && s[i] == '0') break;
                            str += s[i];
                        }
                    }
                    else str = s[0];
                    cOutput += " " + to_string(m) + " " + to_string(n) + " " + str;
                    if (status != "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has already started/ended!");
                        continue;
                    }
                    ConditionOutput(cOutput, 1, " ");
                    makeBoardRandom(m, n, "rate", 0, rate);
                }
            }
            if (method == "Print")
            {
                string type;
                inFile >> type;
                cOutput += " " + type;
                if (type == "GameBoard")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, "");
                    printBoard(gameBoard);
                }
                if (type == "GameState")
                {
                    ConditionOutput(cOutput, 2, status);
                }
                if (type == "GameAnswer")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, "");
                    printBoard(board);
                }
                if (type == "BombCount")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, to_string(bombNum));
                }
                if (type == "FlagCount")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, to_string(flagNum));
                }
                if (type == "OpenBlankCount")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, to_string(openedNum));
                }
                if (type == "RemainBlankCount")
                {
                    if (status == "Standby")
                    {
                        ConditionOutput(cOutput, 0, ": Game has not started!");
                        continue;
                    }
                    ConditionOutput(cOutput, 2, to_string(remainNum));
                }
            }
            if (method == "StartGame")
            {
                if (status != "Standby")
                {
                    ConditionOutput(cOutput, 0, ": Game has already started/ended!");
                    continue;
                }
                if (hasLoaded == false)
                {
                    ConditionOutput(cOutput, 0, ": No board to play!");
                    continue;
                }
                ConditionOutput(cOutput, 1, "");
                status = "Playing";
            }
            if (method == "LeftClick")
            {
                int y, x;
                inFile >> x >> y;
                cOutput += " " + to_string(x) + " " + to_string(y);
                if (status != "Playing")
                {
                    ConditionOutput(cOutput, 0, ": Not in playing state!");
                    continue;
                }
                if (y < 0 || x < 0 || x >= row || y >= col)
                {
                    ConditionOutput(cOutput, 0, ": Out of range!");
                    continue;
                }
                if (gameBoard[y][x] == 'F')
                {
                    ConditionOutput(cOutput, 0, ": This coordinate has been flaged, unflag it to click on it.");
                    continue;
                }
                if (isdigit(gameBoard[y][x]))
                {
                    ConditionOutput(cOutput, 0, ": This coordinate has already been opened!");
                    continue;
                }
                ConditionOutput(cOutput, 1, "");
                ClickBoard(y, x);
                CountItem();
                if (gameBoard[y][x] == 'X')
                {
                    outFile << "Stepped on mine! Game end." << endl;
                    status = "GameOver";
                }
                if (status != "GameOver" && remainNum == 0)
                {
                    outFile << "There is no spare blocks left, you win!" << endl;
                    status = "GameOver";
                }
            }
            if (method == "RightClick")
            {
                int y, x;
                inFile >> x >> y;
                cOutput += " " + to_string(x) + " " + to_string(y);
                if (status != "Playing")
                {
                    ConditionOutput(cOutput, 0, ": Not in playing state!");
                    continue;
                }
                if (y < 0 || x < 0 || x >= row || y >= col)
                {
                    ConditionOutput(cOutput, 0, ": Out of range!");
                    continue;
                }
                if (isdigit(gameBoard[y][x]))
                {
                    ConditionOutput(cOutput, 0, ": This coordinate has already been opened!");
                    continue;
                }
                ConditionOutput(cOutput, 1, "");
                NoteBoard(y, x);
                CountItem();
            }
            if (method == "Replay")
            {
                if (status != "GameOver")
                {
                    ConditionOutput(cOutput, 0, ": Game is not over/Game has not started!");
                    continue;
                }
                ConditionOutput(cOutput, 1, "");
                status = "Standby";
                ClearBoard();
            }
            if (method == "Quit")
            {
                if (status != "GameOver")
                {
                    ConditionOutput(cOutput, 0, ": Game is not over/Game has not started!");
                    continue;
                }
                ConditionOutput(cOutput, 1, "");
                break;
            }
        }
        inFile.close();
        outFile.close();
    }
    else
    {
        cout << argc << " Error" << endl;
    }
}
