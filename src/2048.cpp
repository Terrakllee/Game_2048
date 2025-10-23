#include <iostream>

using namespace std;

//Global Const Variables
static const short MULT = 2;
static const short WINING_TILE = 2048;
static const short ROWS = 4;
static const short COLS = 4;
static const short ALL_TILES_COUNT = ROWS * COLS;
static const short RAND_CHANCE_OF_SPAWN_VAL_4 = 10;
static const short VALUE2 = 2;
static const short VALUE4 = 4;

class Game_2048
{
    public:
    class Tile
    {
        //Variables
        private:
        short value;
        bool isMoved;
        bool isStuckU; //Up
        bool isStuckD; //Down
        bool isStuckL; //Left
        bool isStuckR; //Right

        public:

        //Getters
        short GetValue() {return value;}
        bool GetIsMoved() {return isMoved;}
        bool GetIsStuckU() {return isStuckU;}
        bool GetIsStuckD() {return isStuckD;}
        bool GetIsStuckL() {return isStuckL;}
        bool GetIsStuckR() {return isStuckR;}

        //Setters
        void SetValue(short value) {this->value = value;}
        void SetIsMoved(bool isMoved) {this->isMoved = isMoved;}
        void SetIsStuckU(bool isStuckU) {this->isStuckU = isStuckU;}
        void SetIsStuckD(bool isStuckD) {this->isStuckD = isStuckD;}
        void SetIsStuckL(bool isStuckL) {this->isStuckL = isStuckL;}
        void SetIsStuckR(bool isStuckR) {this->isStuckR = isStuckR;}

        //Constructors
        Tile() : value(0), isMoved(false), isStuckU(false), isStuckD(false), isStuckL(false), isStuckR(false) {};

        Tile(int value, bool isMoved, bool isStuckU, bool isStuckD, bool isStuckL, bool isStuckR) :
        value(value), isMoved(isMoved), isStuckU(isStuckU), isStuckD(isStuckD), isStuckL(isStuckL), isStuckR(isStuckR) {};

    };

    //Methods
    void MsgGreetings()
    {
        cout << "Game 2048\n";
        cout << "Made by Terrakllee\n";
    }

    void Play()
    {
        SpawnStartingTiles();
        PrintGrid();

        do
        {
            do
            {
                UserTurn();
            } while (badMove);
            CheckIfYouWin();
            if (youWin == true)
            {
                PrintGrid();
                cout << "\nYou Win!\n";
                cout << "Your score is " << score << "\n";
                break;
            }
            CheckIfGameOver();
            if (gameOver == true)
            {
                PrintGrid();
                cout << "\nGame Over!\n";
                cout << "Your score is " << score << "\n";
                break;
            }
            ClearMovementInfo();
            if (!disableRandomTiles)
                SpawnRandomTile();
            PrintGrid();
        } while (true);
    }

    void PrintGrid()
    {
        cout << "\n";
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (!debug)
                {
                    cout << "[" << Grid[i][j].GetValue() << "]" << "\t\t";
                }
                else
                {
                    cout << "[" << i << ";" << j << "] " << Grid[i][j].GetValue(); //debug
                    cout << " m" << Grid[i][j].GetIsMoved() << " l" << Grid[i][j].GetIsStuckL(); //debug
                    cout << "u" << Grid[i][j].GetIsStuckU() << "d" << Grid[i][j].GetIsStuckD() << "r" << Grid[i][j].GetIsStuckR() << "\t\t"; //debug
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void SpawnStartingTiles()
    {
        SpawnRandomTile();
        SpawnRandomTile();
    }

    void SpawnRandomTile()
    {
        short randomTileRow;
        short randomTileCol;
        short randomTileChance;
        short randomTileValue;

        do
        {
            randomTileRow = rand() % ROWS;
            randomTileCol = rand() % COLS;
        } while (Grid[randomTileRow][randomTileCol].GetValue() != 0);

        randomTileChance = rand() % RAND_CHANCE_OF_SPAWN_VAL_4;

        if (randomTileChance < RAND_CHANCE_OF_SPAWN_VAL_4 - 1) 
        {
            randomTileValue = VALUE2;
        }
        else
        {
            randomTileValue = VALUE4;
        }

        Grid[randomTileRow][randomTileCol].SetValue(randomTileValue);
    }

    bool IsUpEdge(short i)
    {
        if (i == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool IsDownEdge(short i)
    {
        if (i == ROWS-1)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool IsLeftEdge(short j)
    {
        if (j == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool IsRightEdge(short j)
    {
        if (j == COLS-1)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    void ClearMovementInfo()
    {
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetIsMoved() == true)
                {
                    Grid[i][j].SetIsMoved(false);
                }
            }
        }
    }

    void ClearTile(short i, short j)
    {
        Grid[i][j].SetValue(0);
        Grid[i][j].SetIsMoved(false);
        Grid[i][j].SetIsStuckU(false);
        Grid[i][j].SetIsStuckD(false);
        Grid[i][j].SetIsStuckL(false);
        Grid[i][j].SetIsStuckR(false);
    }

    bool TileIsEmpty(short i, short j)
    {
        if (Grid[i][j].GetValue() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void debugCaseLose()
    {
        Grid[0][0].SetValue(128);
        Grid[0][1].SetValue(16);
        Grid[0][2].SetValue(32);
        Grid[0][3].SetValue(64);

        Grid[1][0].SetValue(64);
        Grid[1][1].SetValue(32);
        Grid[1][2].SetValue(16);
        Grid[1][3].SetValue(128);

        Grid[2][0].SetValue(128);
        Grid[2][1].SetValue(16);
        Grid[2][2].SetValue(32);
        Grid[2][3].SetValue(64);
    }

    void debugCaseWin()
    {
        Grid[0][0].SetValue(1024);
        Grid[0][1].SetValue(512);
        Grid[0][2].SetValue(256);
        Grid[0][3].SetValue(128);

        Grid[1][0].SetValue(8);
        Grid[1][1].SetValue(16);
        Grid[1][2].SetValue(32);
        Grid[1][3].SetValue(64);

        Grid[2][0].SetValue(4);
        Grid[2][1].SetValue(2);
        Grid[2][2].SetValue(0);
        Grid[2][3].SetValue(0);
    }

    void debugCaseH2222()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    void debugCaseV2222()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }

    //debug Left
    void debugCaseLeft1()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(4);
        Grid[0][3].SetValue(0);
    }

    void debugCaseLeft2()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(0);
        Grid[0][3].SetValue(4);
    }

    void debugCaseLeft3()
    {
        Grid[0][0].SetValue(8);
        Grid[0][1].SetValue(4);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    //debug Right
    void debugCaseRight1()
    {
        Grid[0][0].SetValue(0);
        Grid[0][1].SetValue(4);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    void debugCaseRight2()
    {
        Grid[0][0].SetValue(4);
        Grid[0][1].SetValue(0);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    //debug Up
    void debugCaseUp1()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(4);
        Grid[3][0].SetValue(0);
    }
    void debugCaseUp2()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(0);
        Grid[3][0].SetValue(4);
    }

    //debug Down
    void debugCaseDown1()
    {
        Grid[0][0].SetValue(0);
        Grid[1][0].SetValue(4);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }
    void debugCaseDown2()
    {
        Grid[0][0].SetValue(4);
        Grid[1][0].SetValue(0);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }

    //Random
    void debugCaseRandom1()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(0);

        Grid[1][0].SetValue(2);
        Grid[1][1].SetValue(0);
        Grid[1][2].SetValue(0);
        Grid[1][3].SetValue(0);

        Grid[2][0].SetValue(16);
        Grid[2][1].SetValue(0);
        Grid[2][2].SetValue(0);
        Grid[2][3].SetValue(0);

        Grid[3][0].SetValue(4);
        Grid[3][1].SetValue(0);
        Grid[3][2].SetValue(2);
        Grid[3][3].SetValue(0);
    }

    void debugCaseRandom2()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(0);
        Grid[0][3].SetValue(0);

        Grid[1][0].SetValue(4);
        Grid[1][1].SetValue(32);
        Grid[1][2].SetValue(2);
        Grid[1][3].SetValue(0);

        Grid[2][0].SetValue(4);
        Grid[2][1].SetValue(16);
        Grid[2][2].SetValue(8);
        Grid[2][3].SetValue(0);

        Grid[3][0].SetValue(4);
        Grid[3][1].SetValue(8);
        Grid[3][2].SetValue(2);
        Grid[3][3].SetValue(4);
    }

    void LoadDebugCases()
    {
        int loadCase;
        cout << "debug case loader\n";
        cout << "Lose - 0\t";
        cout << "Win - 1\t";
        cout << "Horisontal 2222 - 2\t";
        cout << "Vertical 2222 - 3\n";
        cout << "Left1 - 4\t";
        cout << "Left2 - 5\t";
        cout << "Right1 - 6\t";
        cout << "Right2 - 7\n";
        cout << "Up1 - 8\t";
        cout << "Up2 - 9\t";
        cout << "Down2 - 10\t";
        cout << "Down2 - 11\t";
        cout << "Random1 - 12\n";
        cout << "Random2 - 13\t";
        cout << "Left3 - 14\t";
        cout << "\nEnter: ";
        cin >> loadCase;

        switch (loadCase)
        {
        case 0:
            debugCaseLose();
            break;
        case 1:
            debugCaseWin();
            break;
        case 2:
            debugCaseH2222();
            break;
        case 3:
            debugCaseV2222();
            break;
        case 4:
            debugCaseLeft1();
            break;
        case 5:
            debugCaseLeft2();
            break;
        case 6:
            debugCaseRight1();
            break;
        case 7:
            debugCaseRight2();
            break;
        case 8:
            debugCaseUp1();
            break;
        case 9:
            debugCaseUp2();
            break;
        case 10:
            debugCaseDown1();
            break;
        case 11:
            debugCaseDown2();
            break;
        case 12:
            debugCaseRandom1();
            break;
        case 13:
            debugCaseRandom2(); // a w
            break;
        case 14:
            debugCaseLeft3(); // a w
            break;
        default:
            break;
        }
        cout << "\n";
    }

    void debugMenu()
    {
        bool debugExit = false;
        char debugMenuChoice;
        do
        {
            cout << "debug Menu\n";
            cout << "Exit - 'e'\n";
            cout << "Set value at specific index - 'i'\n";
            cout << "Set values in first row - 'f'\n";
            cout << "Set all tile values - 'a'\n";
            cout << "Load debug cases - 'g'\n";
            cout << "Disable tile spawn - 'n'\n";
            cout << "Print grid - 'p'\n";
            cout << "Clear grid - 'c'\n";
            cout << "Enter: ";
            cin >> debugMenuChoice;

            switch (debugMenuChoice)
            {
            case 'e':
                debugExit = true;
                break;
            case 'i':
                debugCaseCreatorIndex();
                break;
            case 'f':
                debugCaseCreatorRow();
                break;
            case 'a':
                debugCaseCreatorAll();
                break;
            case 'g':
                LoadDebugCases();
                break;
            case 'n':
                disableRandomTiles == false ? disableRandomTiles = true : disableRandomTiles = false;
                break;
            case 'p':
                PrintGrid();
                break;
            case 'c':
                ClearGrid();
                break;
            default:
                cout << "No such option!\n";
                break;
            }
        } while (!debugExit);
    }

    void debugCaseCreatorAll()
    {
        cout << "debugCaseCreatorAll()\n";
        int debugValues;
        cout << "If you want to skip this row enter - 9 or -1 to skip all ROWS\n";
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                cout << "[" << i << "][" << j << "] val = ";
                do
                {
                    cin >> debugValues;
                    if (debugValues == 9)
                    {
                        if (i+1 < ROWS)
                        {
                            i++;
                            j = -1;
                            break;
                        }
                        else
                        {
                            i = 3;
                            j = 3;
                            break;
                        }
                        
                    }
                    else if (debugValues == -1)
                    {
                        i = 3;
                        j = 3;
                        break;
                    }
                } while (debugValues >= 0 && debugValues % 2 != 0);

                if (debugValues != 9 && debugValues != -1)
                {
                    Grid[i][j].SetValue(debugValues);
                    cout << "Value " << debugValues << " at [" << i << "][" << j << "] is set successfuly!\n";
                }
            }
        }
    }

    void debugCaseCreatorRow()
    {
        cout << "debugCaseCreatorRow()\n";
        int debugValues;
        cout << "Enter first row values\n";
        for (int i = 0; i < ROWS; i++)
        {
            cout << "col " << i << ": ";
            do
            {
                cin >> debugValues;
            } while (debugValues >= 0 && debugValues % 2 != 0);
            Grid[0][i].SetValue(debugValues);
            cout << "Value " << debugValues << " at [" << 0 << "][" << i << "] is set successfuly!\n";
        }
    }

    void debugCaseCreatorIndex()
    {
        cout << "debugCaseCreatorIndex()\n";
        int debugValues;
        int debugIndex;
        int dI, dJ;
        cout << "Enter indexes to edit tile value (12 = [1][2], 01 = [0][1])\n";
        cout << "Enter: ";

        do
        {
            cin >> debugIndex;
            dI = (debugIndex / 10);
            dJ = (debugIndex % 10);
        } while (dI > ROWS && dJ > COLS && dI < 0 && dJ < 0);

        cout << "Enter Value: ";
        do
        {
            cin >> debugValues;
        } while (debugValues >= 0 && debugValues % 2 != 0);

        Grid[dI][dJ].SetValue(debugValues);

        cout << "Value " << debugValues << " at [" << dI << "][" << dJ << "] is set successfuly!\n";
    }

    void ClearGrid()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                ClearTile(i,j);
            }
        }
    }

    void MoveUpStep()
    {
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                CountTiles();
                CheckIfAllUpIsStuck();
                if (!IsUpEdge(i) && !TileIsEmpty(i, j))
                {
                    if (Grid[i-1][j].GetValue() == Grid[i][j].GetValue() && Grid[i-1][j].GetIsMoved() == false && Grid[i][j].GetIsMoved() == false)
                    {
                        score += Grid[i-1][j].GetValue() * MULT;
                        Grid[i-1][j].SetValue(Grid[i-1][j].GetValue() * MULT);
                        Grid[i-1][j].SetIsMoved(true);
                        if (IsUpEdge(i-1))
                        {
                            Grid[i-1][j].SetIsStuckU(true);
                        }
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else if (!IsUpEdge(i) && TileIsEmpty(i-1, j))
                    {
                        Grid[i-1][j].SetValue(Grid[i][j].GetValue());
                        if (IsUpEdge(i-1))
                        {
                            Grid[i-1][j].SetIsStuckU(true);
                        }
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else
                    {
                        Grid[i][j].SetIsStuckU(true);
                    }
                }
                else if (IsUpEdge(i) && Grid[i][j].GetValue() != 0)
                {
                    Grid[i][j].SetIsStuckU(true);
                }
            }
        }
    }

    void MoveDownStep()
    {
        for (short i = ROWS-1; i >= 0; i--)
        {
            for (short j = 0; j < COLS; j++)
            {
                CountTiles();
                CheckIfAllDownIsStuck();
                if (!IsDownEdge(i) && !TileIsEmpty(i, j))
                {
                    if (Grid[i+1][j].GetValue() == Grid[i][j].GetValue() && Grid[i+1][j].GetIsMoved() == false && Grid[i][j].GetIsMoved() == false)
                    {
                        score += Grid[i+1][j].GetValue() * MULT;
                        Grid[i+1][j].SetValue(Grid[i+1][j].GetValue() * MULT);
                        Grid[i+1][j].SetIsMoved(true);
                        if (IsDownEdge(i+1))
                        {
                            Grid[i+1][j].SetIsStuckD(true);
                        }
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else if (!IsDownEdge(i) && TileIsEmpty(i+1, j))
                    {
                        Grid[i+1][j].SetValue(Grid[i][j].GetValue());
                        if (IsDownEdge(i+1))
                        {
                            Grid[i+1][j].SetIsStuckD(true);
                        }
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else
                    {
                        Grid[i][j].SetIsStuckD(true);
                    }
                }
                else if (IsDownEdge(i) && Grid[i][j].GetValue() != 0)
                {
                    Grid[i][j].SetIsStuckD(true);
                }
            }
        }
    }

    void MoveLeftStep()
    {
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                CountTiles();
                CheckIfAllLeftIsStuck();
                if (!IsLeftEdge(j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j-1].GetValue() == Grid[i][j].GetValue() && Grid[i][j-1].GetIsMoved() == false && Grid[i][j].GetIsMoved() == false)
                    {
                        score += Grid[i][j-1].GetValue() * MULT;
                        Grid[i][j-1].SetValue(Grid[i][j-1].GetValue() * MULT);
                        Grid[i][j-1].SetIsMoved(true);
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else if (!IsLeftEdge(j) && TileIsEmpty(i, j-1))
                    {
                        Grid[i][j-1].SetValue(Grid[i][j].GetValue());
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else
                    {
                        Grid[i][j].SetIsStuckL(true);
                    }
                }
                else if (IsLeftEdge(j) && Grid[i][j].GetValue() != 0)
                {
                    Grid[i][j].SetIsStuckL(true);
                }
            }
        }
    }

    void MoveRightStep()
    {
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = COLS-1; j >= 0; j--)
            {
                CountTiles();
                CheckIfAllRightIsStuck();
                if (!IsRightEdge(j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j+1].GetValue() == Grid[i][j].GetValue() && Grid[i][j+1].GetIsMoved() == false && Grid[i][j].GetIsMoved() == false)
                    {
                        score += Grid[i][j+1].GetValue() * MULT;
                        Grid[i][j+1].SetValue(Grid[i][j+1].GetValue() * MULT);
                        Grid[i][j+1].SetIsMoved(true);
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else if (!IsRightEdge(j) && TileIsEmpty(i, j+1))
                    {
                        Grid[i][j+1].SetValue(Grid[i][j].GetValue());
                        ClearTile(i, j);
                        if (debug)
                            PrintGrid(); //debug
                    }
                    else
                    {
                        Grid[i][j].SetIsStuckR(true);
                    }
                }
                else if (IsRightEdge(j) && Grid[i][j].GetValue() != 0)
                {
                    Grid[i][j].SetIsStuckR(true);
                }
            }
        }
    }

    void MoveUp()
    {
        do
        {
            MoveUpStep();
        } while (tilesCount != tilesStuckUpCount);
    }

    void MoveDown()
    {
        do
        {
            MoveDownStep();
        } while (tilesCount != tilesStuckDownCount);
    }

    void MoveLeft()
    {
        do
        {
            MoveLeftStep();
        } while (tilesCount != tilesStuckLeftCount);
    }

    void MoveRight()
    {
        do
        {
            MoveRightStep();
        } while (tilesCount != tilesStuckRightCount);
    }

    void UserTurn()
    {
        CountTiles();
        char user;
        cout << "Your current score is " << score << "\n";
        cout << "Enter the direction\n";
        cout << "Enter: ";
        cin >> user;

        switch (user)
        {
        case 'w':
            CountTiles();
            CheckIfAllUpIsStuck();
            if (tilesStuckUpCount == tilesCount && tilesCount > 0)
            {
                badMove = true;
            }
            else
            {
                MoveUp();
                badMove = false;
            }
            break;
        case 'a':
            CountTiles();
            CheckIfAllLeftIsStuck();
            if (tilesStuckLeftCount == tilesCount && tilesCount > 0)
            {
                badMove = true;
            }
            else
            {
                MoveLeft();
                badMove = false;
            }
            break;
        case 's':
            CountTiles();
            CheckIfAllDownIsStuck();
            if (tilesStuckDownCount == tilesCount && tilesCount > 0)
            {
                badMove = true;
            }
            else
            {
                MoveDown();
                badMove = false;
            }
            break;
        case 'd':
            CountTiles();
            CheckIfAllRightIsStuck();
            if (tilesStuckRightCount == tilesCount && tilesCount > 0)
            {
                badMove = true;
            }
            else
            {
                MoveRight();
                badMove = false;
            }
            break;
        case '~':
            ClearGrid();
            badMove = true;
            break;
        case '@':
            if (debug)
                debugMenu();
            badMove = true;
            break;
        case '#':
            if (debug)
                LoadDebugCases();
            badMove = true;
            break;
        case '%':
            if (!debug)
            {
                debug = true;
                cout << "debug mode enabled!\n";
            }
            else
            {
                debug = false;
                cout << "debug mode disabled!\n";
            }
            badMove = true;
            break;
        case '0':
            gameOver = true;
            break;
        default:
            cout << "No such move! (use wasd)\n";
            badMove = true;
            break;
        }
    }

    void CheckIfAllUpIsStuck()
    {
        tilesStuckUpCount = 0;
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() != 0 && (IsUpEdge(i) || (!TileIsEmpty(i-1, j) && Grid[i-1][j].GetValue() != Grid[i][j].GetValue()) || Grid[i-1][j].GetIsMoved() || Grid[i][j].GetIsMoved()))
                {
                    Grid[i][j].SetIsStuckU(true);
                    tilesStuckUpCount++;
                }
                else
                {
                    Grid[i][j].SetIsStuckU(false);
                }
            }
        }
    }

    void CheckIfAllDownIsStuck()
    {
        tilesStuckDownCount = 0;
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() != 0 && (IsDownEdge(i) || (!TileIsEmpty(i+1, j) && Grid[i+1][j].GetValue() != Grid[i][j].GetValue()) || Grid[i+1][j].GetIsMoved() || Grid[i][j].GetIsMoved()))
                {
                    Grid[i][j].SetIsStuckD(true);
                    tilesStuckDownCount++;
                }
                else
                {
                    Grid[i][j].SetIsStuckD(false);
                }
            }
        }
    }

    void CheckIfAllLeftIsStuck()
    {
        tilesStuckLeftCount = 0;
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() != 0 && (IsLeftEdge(j) || (!TileIsEmpty(i, j-1) && Grid[i][j-1].GetValue() != Grid[i][j].GetValue()) || Grid[i][j-1].GetIsMoved() || Grid[i][j].GetIsMoved()))
                {
                    Grid[i][j].SetIsStuckL(true);
                    tilesStuckLeftCount++;
                }
                else
                {
                    Grid[i][j].SetIsStuckL(false);
                }
            }
        }
    }

    void CheckIfAllRightIsStuck()
    {
        tilesStuckRightCount = 0;
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() != 0 && (IsRightEdge(j) || (!TileIsEmpty(i, j+1) && Grid[i][j+1].GetValue() != Grid[i][j].GetValue()) || Grid[i][j+1].GetIsMoved() || Grid[i][j].GetIsMoved()))
                {
                    Grid[i][j].SetIsStuckR(true);
                    tilesStuckRightCount++;
                }
                else
                {
                    Grid[i][j].SetIsStuckR(false);
                }
            }
        }
    }

    void CountTiles()
    {
        tilesCount = 0;
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() != 0)
                {
                    tilesCount++;
                }
            }
        }  
    }

    void CheckIfGameOver()
    {
        if (tilesStuckUpCount == ALL_TILES_COUNT)
        {
            gameOver = true;
        }
        else if (tilesStuckDownCount == ALL_TILES_COUNT)
        {
            gameOver = true;
        }
        else if (tilesStuckLeftCount == ALL_TILES_COUNT)
        {
            gameOver = true;
        }
        else if (tilesStuckRightCount == ALL_TILES_COUNT)
        {
            gameOver = true;
        }
    }

    void CheckIfYouWin()
    {
        for (short i = 0; i < ROWS; i++)
        {
            for (short j = 0; j < COLS; j++)
            {
                if (Grid[i][j].GetValue() == WINING_TILE)
                {
                    youWin = true;
                }
            }
            
        }
        
    }

    void ResetGame()
    {
        ClearGrid();

        debug = false;
        gameOver = false;
        youWin = false;
        badMove = false;
        disableRandomTiles = false;

        tilesCount = 0;
        tilesStuckUpCount = 0;
        tilesStuckDownCount = 0;
        tilesStuckLeftCount = 0;
        tilesStuckRightCount = 0;

        score = 0;
    }

    //Constructors
    Game_2048()
    {
        Grid = new Tile*[ROWS];
        for (short i = 0; i < ROWS; i++)
        {
            Grid[i] = new Tile[COLS];
        }
    }

    //Destructors
    ~Game_2048()
    {
        for (short i = 0; i < ROWS; i++)
        {
            delete[] Grid[i];
        }
        delete[] Grid;
        Grid = nullptr;
    }

    private:
    
    //Variables
    Tile **Grid;
    double score = 0;
    //Tiles Statuses
    short tilesCount;
    short tilesStuckUpCount;
    short tilesStuckDownCount;
    short tilesStuckLeftCount;
    short tilesStuckRightCount;
    //Flags
    bool debug = false;
    bool gameOver = false;
    bool youWin = false;
    bool badMove = false;
    bool disableRandomTiles = false;
};




int main()
{
    Game_2048 A1;
    A1.MsgGreetings();

    char exit;

    do
    {
        A1.Play();
        cout << "Do you want to play again?\n";
        cout << "Enter yes or no (y/n)\n";
        cout << "Enter: ";
        cin >> exit;
        A1.ResetGame();
    } while (exit != 'n');

    cout << "Exiting...\n";
    system("pause");
    return 0;
}