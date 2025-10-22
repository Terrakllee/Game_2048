#include <iostream>

using namespace std;

class Game_2048
{
    public:
    class Tile
    {
        public:
        short value, row, col;
        bool isUpEdge = false;
        bool isDownEdge = false;
        bool isLeftEdge = false;
        bool isRightEdge = false;
        bool isStuck = false;
        bool moved = false;

        public:

        short GetValue()
        {
            return value;
        }

        Tile() : value(0), row(0), col(0) {}

        Tile(short value, short row, short col) 
        : value(value), row(row), col(col) {}

        void PrintTile()
        {
            cout << "T(" << row << ", " << col << ") = " << value << " *" << isStuck << "\t\t"; // Debug
            // cout << " [" << value << "] " << "\t";

        }
    };

    Game_2048()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = Tile(0, i, j);

                if (i == 0)
                {
                    grid[i][j].isUpEdge = true;

                }
                if (i == 3)
                {
                    grid[i][j].isDownEdge = true;
                }
                if (j == 0)
                {
                    grid[i][j].isLeftEdge = true;

                }
                if (j == 3)
                {
                    grid[i][j].isRightEdge = true;
                }
            }
            
        }
        
    }

    void PrintGrid()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                grid[i][j].PrintTile();
            }
            cout << "\n\n";
        }
        cout << "\n";
    }

    void RandomTile()
    {
        do
        {
            rowRand = rand() % rows;
            colRand = rand() % cols;
        } while (grid[rowRand][colRand].value != 0);

        valueRandChance = rand() % (tileValue2SpawnChance+1);

        if (valueRandChance == tileValue2SpawnChance)
        {
            valueRandom = value4;
        }
        else
        {
            valueRandom = value2;
        }
    
        grid[rowRand][colRand].value = valueRandom;
    }

    void StartingTiles()
    {
        for (short i = 0; i < startingTiles; i++)
        {
            RandomTile();
        }
        
    }

    void CountTiles()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j].value != 0)
                {
                    ++tilesCounter;
                }
                if (grid[i][j].isStuck == true)
                {
                    ++stuckTilesCounter;
                }
                if (grid[i][j].value > biggestTile)
                {
                    biggestTile = grid[i][j].value;
                }
                if (grid[i][j].value == 0)
                {
                    grid[i][j].isStuck = false;
                }
                
                
                
                
            }
        }
    }

    short GetBiggestTile()
    {
        return biggestTile;
    }

    short GetStuckTilesCounter()
    {
        return stuckTilesCounter;
    }

    void UserInput()
    {
        cout << "WASD: ";
        cin >> user;
        cout << "\n";


        switch (user)
        {
        case 'w':
            do
            {
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        tilesCounter = 0;
                        stuckTilesCounter = 0;
                        CountTiles();
                        tilesCounter = 0;
                        stuckTilesCounter = 0;

                        if (grid[i][j].row != 0 && grid[i][j].value != 0 && grid[i-1][j].value == 0)
                        {
                            grid[i-1][j].value = grid[i][j].value;
                            grid[i][j].value = 0;
                            grid[i][j].isStuck = false;
                            grid[i-1][j].isStuck = false;
                        }
                        else if (grid[i][j].row != 0 && grid[i][j].value != 0 && grid[i-1][j].value != 0)
                        {
                            if (grid[i-1][j].value == grid[i][j].value)
                            {
                                grid[i-1][j].value *= 2;
                                grid[i][j].value = 0;
                                grid[i][j].isStuck = false;
                                grid[i-1][j].isStuck = false;
                                grid[i-1][j].moved = true;
                            }
                            else if (grid[i-1][j].value != grid[i][j].value)
                            {
                                grid[i][j].isStuck = true;
                            }
                            
                        }
                        if (grid[i][j].isUpEdge == true && grid[i][j].value != 0)
                        {
                            grid[i][j].isStuck = true;
                        }
                        

                        // if (grid[i][j].isStuck && grid[i-1][j].value == grid[i][j].value)
                        // {
                        //     grid[i][j].isStuck = false;
                        // }

                        // if (grid[i-1][j].isStuck && grid[i-1][j].value == grid[i][j].value)
                        // {
                        //     grid[i][j].isStuck = false;
                        // }
                        
                        tilesCounter = 0;
                        stuckTilesCounter = 0;
                        CountTiles();
                        if (tilesCounter == stuckTilesCounter && tilesCounter != 0 && stuckTilesCounter != 0)
                        {
                            break;
                        }

                        if (stuckTilesCounter == rows * cols)
                        {
                            break;
                        }
                        
                        
                        tilesCounter = 0;
                        stuckTilesCounter = 0;
                    }
                    if (stuckTilesCounter == rows * cols)
                    {
                        break;
                    }
                }
                
                if (stuckTilesCounter == rows * cols)
                {
                    break;
                }

            } while (!(tilesCounter == stuckTilesCounter && tilesCounter != 0 && stuckTilesCounter != 0));

            break;
        
        default:
            break;
        }
    }

    public:
    static const short rows = 4;
    static const short cols = 4;
    static const short startingTiles = 2;
    static const short tileValue2SpawnChance = 9; // 90% Chance of getting tile with value 2
    static const short value2 = 2;
    static const short value4 = 4;

    private:
    short valueRandom;
    short valueRandChance;
    short rowRand, colRand;
    char user;
    short tilesCounter = 0;
    short stuckTilesCounter = 0;
    short biggestTile = 0;

    Tile grid[rows][cols];


};

int main()
{
    Game_2048 A1;

    A1.PrintGrid();
        
    A1.StartingTiles();

    A1.PrintGrid();

    do
    {
        cout << "\nStuck: " << A1.GetStuckTilesCounter() << "\n";

        A1.UserInput();

        cout << "\nStuck: " << A1.GetStuckTilesCounter() << "\n";

        A1.PrintGrid();

        if (A1.GetStuckTilesCounter() == A1.rows * A1.cols)
        {
            break;
        }
        
        A1.RandomTile();

        cout << "_____________________________vvv After Random Tile vvv_________________________________\n\n";

        A1.PrintGrid();

        

    } while (A1.GetBiggestTile() != 2048 || A1.GetStuckTilesCounter() != A1.rows * A1.cols);
    
    
    
 


    
}