#include <iostream>

using namespace std;

//Bug when going down or right

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
        cout << "Игра 2048\n";

        PrintGrid();
        SpawnStartingTiles();
        PrintGrid();

        do
        {
            UserTurn();
            // MoveUp(); //Debug
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
                // cout << "[" << Grid[i][j].GetValue() << "]" << "\t\t";
                cout << "(" << i << ";" << j << ") " << Grid[i][j].GetValue(); //Debug
                cout << " m" << Grid[i][j].GetIsMoved() << " u" << Grid[i][j].GetIsStuckU(); //Debug
                cout << " d" << Grid[i][j].GetIsStuckD() << " l" << Grid[i][j].GetIsStuckL() << " r" << Grid[i][j].GetIsStuckR() << "\t\t\t"; //Debug
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

    bool IsUpEdge(short i, short j)
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

    bool IsDownEdge(short i, short j)
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

    bool IsLeftEdge(short i, short j)
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

    bool IsRightEdge(short i, short j)
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

    // void DebugMoveUp()
    // {
    //     short user;
    //     cout << "\nВведите количество шагов вверх\n";
    //     cout << "Ввод: ";
    //     cin >> user;
    //     for (short i = 0; i < user; i++)
    //     {
    //         MoveUp();
    //     }
        
    // }

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

    void MoveUpStep()
    {
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                CountTiles();
                CheckIfAllUpIsStuck();
                if (!IsUpEdge(i, j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i-1][j].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i-1][j].SetValue(Grid[i-1][j].GetValue() * mult);
                        Grid[i-1][j].SetIsMoved(true);
                        if (IsUpEdge(i-1, j))
                        {
                            Grid[i-1][j].SetIsStuckU(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsUpEdge(i, j) && TileIsEmpty(i-1, j))
                    {
                        Grid[i-1][j].SetValue(Grid[i][j].GetValue());
                        if (IsUpEdge(i-1, j))
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
                else if (IsUpEdge(i, j) && Grid[i][j].GetValue() != 0)
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
                if (!IsDownEdge(i, j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i+1][j].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i+1][j].SetValue(Grid[i+1][j].GetValue() * mult);
                        Grid[i+1][j].SetIsMoved(true);
                        if (IsDownEdge(i+1, j))
                        {
                            Grid[i+1][j].SetIsStuckD(true);
                        }
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsDownEdge(i, j) && TileIsEmpty(i+1, j))
                    {
                        Grid[i+1][j].SetValue(Grid[i][j].GetValue());
                        if (IsDownEdge(i+1, j))
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
                else if (IsDownEdge(i, j) && Grid[i][j].GetValue() != 0)
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
                if (!IsLeftEdge(i, j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j-1].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i][j-1].SetValue(Grid[i][j-1].GetValue() * mult);
                        Grid[i][j-1].SetIsMoved(true);
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsLeftEdge(i, j) && TileIsEmpty(i, j-1))
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
                else if (IsLeftEdge(i, j) && Grid[i][j].GetValue() != 0)
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
                if (!IsRightEdge(i, j) && !TileIsEmpty(i, j))
                {
                    if (Grid[i][j+1].GetValue() == Grid[i][j].GetValue() && Grid[i][j].GetIsMoved() == false)
                    {
                        Grid[i][j+1].SetValue(Grid[i][j+1].GetValue() * mult);
                        Grid[i][j+1].SetIsMoved(true);
                        ClearTile(i, j);
                        PrintGrid(); //Debug
                    }
                    else if (!IsRightEdge(i, j) && TileIsEmpty(i, j+1))
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
                else if (IsRightEdge(i, j) && Grid[i][j].GetValue() != 0)
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
        cout << "\nВведите направление\n";
        cout << "Ввод: ";
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

    return 0;
}