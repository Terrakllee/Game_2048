#include <iostream>
#include <cmath>

using namespace std;

const short startingTiles = 2;
const short rows = 4, cols = 4;
const short value2 = 2;
const short value4 = 4;
const short value2SpawnChance = 9; // 90% Spawn chance of tile with value 2

class Game_2048
{
    public:
    int grid[rows][cols];

    short rowsRand;
    short colsRand;
    short valueRandChance;
    short valueRandom;
    char user;

    public:

    class Tile
    {
        private:
        short value, row, col;

        Tile()
        {
            value = 0;
            row = 0;
            col = 0;
        }
    };

    void Init()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = 0;
            }
        }
    }

    void Print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << grid[i][j] << "\t";
            }
            cout << "\n\n";
        }
        cout << "\n";
    }

    void StartingTiles()
    {
        for (int i = 0; i < startingTiles; i++)
        {
            RandomTile();
        }
    }

    void RandomTile()
    {
        do
        {
            rowsRand = rand() % rows;
            colsRand = rand() % cols;
        } while (grid[rowsRand][colsRand] != 0);

        valueRandChance = rand() % (value2SpawnChance+1);

        if (valueRandChance == value2SpawnChance)
        {
            valueRandom = value4;
        }
        else
        {
            valueRandom = value2;
        }
    
        grid[rowsRand][colsRand] = valueRandom;

    }

    void UserInput()
    {
        cout << "WASD: ";
        cin >> user;
        switch (user)
        {
        case 'W':
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (grid[i][j] != 0)
                    {
                        for (int k = i; k < rows; k++)
                        {
                            if (grid[k-1][j] == 0)
                            { 
                                grid[i+1][j] = grid[i][j];

                                // if (i > 0)
                                // {
                                //     grid[i][j] = grid[i-1][j];
                                // }
                            }
                        }
                        
                    }
                    
                }
                
            }
            
            break;
        
        // default:
        //     break;
        }
    }

};

int main()
{
    setlocale(0, "");


    cout << "\n\n";

    // int **grid = new int*[rows];
    // for (int i = 0; i < rows; i++)
    // {
    //     grid[i] = new int[cols];
    // }

    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < cols; j++)
    //     {
    //         grid[i][j] = 0;
    //     }
    // }

    Game_2048 t1;

    t1.Init();

    t1.Print();

    t1.StartingTiles();

    t1.Print();

    t1.UserInput();

    t1.Print();




    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < cols; j++)
    //     {
    //         cout << grid[i][j] << "\t";
    //     }
    //     cout << "\n";
    // }

    // short rowsRand;
    // short colsRand;
    // short valueRandChance;
    // short valueRandom;

    
    // for (int i = 0; i < startingTiles; i++)
    // {
    //     do
    //     {
    //         rowsRand = rand() % rows;
    //         colsRand = rand() % cols;
    //     } while (grid[rowsRand][colsRand] != 0);

    //     valueRandChance = rand() % 10;

    //     if (valueRandChance == 9)
    //     {
    //         valueRandom = value4;
    //     }
    //     else
    //     {
    //         valueRandom = value2;
    //     }
        
    //     grid[rowsRand][colsRand] = valueRandom;

    // }
    





    // cout << "\n";

    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < cols; j++)
    //     {
    //         cout << grid[i][j] << "\t";
    //     }
    //     cout << "\n";
    // }

    


    // for (int i = 0; i < rows; i++)
    // {
    //     delete[] grid[i];
    //     grid[i] = nullptr;
    // }
    // delete[] grid;
    // grid = nullptr;

    
    

    
}