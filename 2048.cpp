#include <iostream>

using namespace std;

//Bug when going down or right

static const bool DEBUG = false;

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

    void Play()
    {
        cout << "Game 2048\n";
        cout << "Made by Terrakllee\n";

        PrintGrid();
        SpawnStartingTiles();
        PrintGrid();

        do
        {
            UserTurn();
            CheckIfYouWin();
            if (youWin == true)
            {
                cout << "\nYou Win!\n";
                break;
            }
            CheckIfGameOver();
            PrintGrid();
            if (gameOver == true)
            {
                cout << "\nGame Over!\n";
                break;
            }
            ClearMovementInfo();
            SpawnRandomTile();
            PrintGrid();

        } while (!gameOver);
    }

    void PrintGrid()
    {
        cout << "\n";
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (!DEBUG)
                {
                    cout << "[" << Grid[i][j].GetValue() << "]" << "\t\t";
                }
                else
                {
                    cout << "(" << i << ";" << j << ") " << Grid[i][j].GetValue(); //Debug
                    cout << " m" << Grid[i][j].GetIsMoved() << " u" << Grid[i][j].GetIsStuckU(); //Debug
                    cout << " d" << Grid[i][j].GetIsStuckD() << " l" << Grid[i][j].GetIsStuckL() << " r" << Grid[i][j].GetIsStuckR() << "\t\t\t"; //Debug
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
            randomTileRow = rand() % rows;
            randomTileCol = rand() % cols;
        } while (Grid[randomTileRow][randomTileCol].GetValue() != 0);

        randomTileChance = rand() % randomChanceOfSpawn_4;

        if (randomTileChance < randomChanceOfSpawn_4 - 1) 
        {
            randomTileValue = value2;
        }
        else
        {
            randomTileValue = value4;
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
        if (i == rows-1)
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
        if (j == cols-1)
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
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
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

    void DebugCaseLose()
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

    void DebugCaseWin()
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

    void DebugCaseH2222()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    void DebugCaseV2222()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }

    //Debug Left
    void DebugCaseLeft1()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(4);
        Grid[0][3].SetValue(0);
    }

    void DebugCaseLeft2()
    {
        Grid[0][0].SetValue(2);
        Grid[0][1].SetValue(2);
        Grid[0][2].SetValue(0);
        Grid[0][3].SetValue(4);
    }

    //Debug Right
    void DebugCaseRight1()
    {
        Grid[0][0].SetValue(0);
        Grid[0][1].SetValue(4);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    void DebugCaseRight2()
    {
        Grid[0][0].SetValue(4);
        Grid[0][1].SetValue(0);
        Grid[0][2].SetValue(2);
        Grid[0][3].SetValue(2);
    }

    //Debug Up
    void DebugCaseUp1()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(4);
        Grid[3][0].SetValue(0);
    }
    void DebugCaseUp2()
    {
        Grid[0][0].SetValue(2);
        Grid[1][0].SetValue(2);
        Grid[2][0].SetValue(0);
        Grid[3][0].SetValue(4);
    }

    //Debug Down
    void DebugCaseDown1()
    {
        Grid[0][0].SetValue(0);
        Grid[1][0].SetValue(4);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }
    void DebugCaseDown2()
    {
        Grid[0][0].SetValue(4);
        Grid[1][0].SetValue(0);
        Grid[2][0].SetValue(2);
        Grid[3][0].SetValue(2);
    }

    void LoadDebugCases()
    {
        int loadCase;
        cout << "Debug case loader\n";
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
        cout << "\nEnter: ";
        cin >> loadCase;

        switch (loadCase)
        {
        case 0:
            DebugCaseLose();
            break;
        case 1:
            DebugCaseWin();
            break;
        case 2:
            DebugCaseH2222();
            break;
        case 3:
            DebugCaseV2222();
            break;
        case 4:
            DebugCaseLeft1();
            break;
        case 5:
            DebugCaseLeft2();
            break;
        case 6:
            DebugCaseRight1();
            break;
        case 7:
            DebugCaseRight2();
            break;
        case 8:
            DebugCaseUp1();
            break;
        case 9:
            DebugCaseUp2();
            break;
        case 10:
            DebugCaseDown1();
            break;
        case 11:
            DebugCaseDown2();
            break;
        default:
            break;
        }
        cout << "\n";
    }

    void DebugMenu()
    {
        bool debugExit = false;
        char debugMenuChoice;
        do
        {
            cout << "Debug Menu\n";
            cout << "Exit - 'e'\n";
            cout << "Set value at specific index - 'i'\n";
            cout << "Set values in first row - 'f'\n";
            cout << "Set all tile values - 'a'\n";
            cout << "Load debug cases - 'g'\n";
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
                DebugCaseCreatorIndex();
                break;
            case 'f':
                DebugCaseCreatorRow();
                break;
            case 'a':
                DebugCaseCreatorAll();
                break;
            case 'g':
                LoadDebugCases();
                break;
            case 'p':
                PrintGrid();
                break;
            case 'c':
                ClearGrid();
                break;
            default:
                break;
            }
        } while (!debugExit);
    }

    void DebugCaseCreatorAll()
    {
        cout << "DebugCaseCreatorAll()\n";
        int debugValues;
        cout << "If you want to skip this row enter - 9 or -1 to skip all rows\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << "[" << i << "][" << j << "] val = ";
                do
                {
                    cin >> debugValues;
                    if (debugValues == 9)
                    {
                        if (i+1 < rows)
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

    void DebugCaseCreatorRow()
    {
        cout << "DebugCaseCreatorRow()\n";
        int debugValues;
        cout << "Enter first row values\n";
        for (int i = 0; i < rows; i++)
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

    void DebugCaseCreatorIndex()
    {
        cout << "DebugCaseCreatorIndex()\n";
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
        } while (dI > rows && dJ > cols && dI < 0 && dJ < 0);

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
        cout << "ClearGrid()\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ClearTile(i,j);
            }
        }
    }

    void MoveUpStep()
    {
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                CountTiles();
                CheckIfAllUpIsStuck();
                if (!IsUpEdge(i) && !TileIsEmpty(i, j))
                {
                    if (Grid[i-1][j].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i-1][j].SetValue(Grid[i-1][j].GetValue() * mult);
                        Grid[i-1][j].SetIsMoved(true);
                        if (IsUpEdge(i-1))
                        {
                            Grid[i-1][j].SetIsStuckU(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsUpEdge(i) && TileIsEmpty(i-1, j))
                    {
                        Grid[i-1][j].SetValue(Grid[i][j].GetValue());
                        if (IsUpEdge(i-1))
                        {
                            Grid[i-1][j].SetIsStuckU(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
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
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                CountTiles();
                CheckIfAllDownIsStuck();
                if (!IsDownEdge(i) && !TileIsEmpty(i, j))
                {
                    if (Grid[i+1][j].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i+1][j].SetValue(Grid[i+1][j].GetValue() * mult);
                        Grid[i+1][j].SetIsMoved(true);
                        if (IsDownEdge(i+1))
                        {
                            Grid[i+1][j].SetIsStuckD(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsDownEdge(i) && TileIsEmpty(i+1, j))
                    {
                        Grid[i+1][j].SetValue(Grid[i][j].GetValue());
                        if (IsDownEdge(i+1))
                        {
                            Grid[i+1][j].SetIsStuckD(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
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
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                CountTiles();
                CheckIfAllLeftIsStuck();
                if (!IsLeftEdge(j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j-1].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i][j-1].SetValue(Grid[i][j-1].GetValue() * mult);
                        Grid[i][j-1].SetIsMoved(true);
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsLeftEdge(j) && TileIsEmpty(i, j-1))
                    {
                        Grid[i][j-1].SetValue(Grid[i][j].GetValue());
                        ClearTile(i, j);
                        PrintGrid(); //Debug
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
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                CountTiles();
                CheckIfAllRightIsStuck();
                if (!IsRightEdge(j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j+1].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i][j+1].SetValue(Grid[i][j+1].GetValue() * mult);
                        Grid[i][j+1].SetIsMoved(true);
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsRightEdge(j) && TileIsEmpty(i, j+1))
                    {
                        Grid[i][j+1].SetValue(Grid[i][j].GetValue());
                        ClearTile(i, j);
                        PrintGrid(); //Debug
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
        char user;
        cout << "\nEnter the direction\n";
        cout << "Enter: ";
        cin >> user;

        switch (user)
        {
        case 'w':
            MoveUp();
            break;
        case 'a':
            MoveLeft();
            break;
        case 's':
            MoveDown();
            break;
        case 'd':
            MoveRight();
            break;
        case '~':
            ClearGrid();
            break;
        case '@':
            DebugMenu();
            break;
        case '#':
            LoadDebugCases();
            break;
        case '0':
            gameOver = true;
            break;
        default:
            break;
        }
    }

    void CheckIfAllUpIsStuck()
    {
        tilesStuckUpCount = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (Grid[i][j].GetIsStuckU())
                {
                    tilesStuckUpCount++;
                }
                
            }
            
        }
    }

    void CheckIfAllDownIsStuck()
    {
        tilesStuckDownCount = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (Grid[i][j].GetIsStuckD())
                {
                    tilesStuckDownCount++;
                }
                
            }
            
        }
    }

    void CheckIfAllLeftIsStuck()
    {
        tilesStuckLeftCount = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (Grid[i][j].GetIsStuckL())
                {
                    tilesStuckLeftCount++;
                }
                
            }
            
        }
    }

    void CheckIfAllRightIsStuck()
    {
        tilesStuckRightCount = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (Grid[i][j].GetIsStuckR())
                {
                    tilesStuckRightCount++;
                }
                
            }
            
        }
    }

    void CountTiles()
    {
        tilesCount = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
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
        if (tilesStuckUpCount == allTilesCount)
        {
            gameOver = true;
        }
        else if (tilesStuckDownCount == allTilesCount)
        {
            gameOver = true;
        }
        else if (tilesStuckLeftCount == allTilesCount)
        {
            gameOver = true;
        }
        else if (tilesStuckRightCount == allTilesCount)
        {
            gameOver = true;
        }
    }

    void CheckIfYouWin()
    {
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                if (Grid[i][j].GetValue() == wininigTile)
                {
                    youWin = true;
                }
            }
            
        }
        
    }

    Game_2048()
    {
        Grid = new Tile*[rows];
        for (short i = 0; i < rows; i++)
        {
            Grid[i] = new Tile[cols];
        }
    }

    ~Game_2048()
    {
        for (short i = 0; i < rows; i++)
        {
            delete[] Grid[i];
        }
        delete[] Grid;
        Grid = nullptr;
    }



    private:
    static const short rows = 4;
    static const short cols = 4;
    static const short allTilesCount = 16;
    Tile **Grid;
    static const short randomChanceOfSpawn_4 = 10;
    static const short value2 = 2;
    static const short value4 = 4;
    short tilesCount;
    short tilesStuckUpCount;
    short tilesStuckDownCount;
    short tilesStuckLeftCount;
    short tilesStuckRightCount;
    bool gameOver = false;
    bool youWin = false;
    static const short mult = 2;
    static const short wininigTile = 2048;


};




int main()
{
    Game_2048 A1;
    A1.Play();

    system("pause");
    return 0;
}