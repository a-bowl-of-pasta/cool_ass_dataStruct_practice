#include "snakeClasses.h"
#include <conio.h>
#include <math.h>

namespace SNAKE_AI {
    
int mapDimensions = 0; 

// ================= init game
void set_data_matrix(coolMat<metaData>& dataMap, coolMat<char>& map)
{
    // this sets the matrix to the default state
    for(int row =0; row < mapDimensions; row++)
    {
        for(int col = 0; col < mapDimensions; col ++ )
        {
            if(map.getPosData(row, col) == 'o')
            {
                dataMap.setVal(row, col, metaData(row, col, true, 1)); 
            }
            else
            {
                dataMap.setVal(row, col, metaData(row, col, false, 0));
            }
        }
    }
}
//
//
//
coolMat<char> buildMap()
{
    coolMat<char> map(mapDimensions,mapDimensions,  '*', false, false); 
    return map; 
}
//
//
//
coolMat<metaData> parallelData()
{
    coolMat<metaData> metDat(mapDimensions, mapDimensions, metaData(), false, false); 
    return metDat; 
}
//
//
//
snakeObj initializeCharacter(coolMat<char>& map, coolMat<metaData>& dataMap)
{

    int row = (map.getHeight() - 1) / 2; 
    int col = (map.getHeight() - 1 )/ 2; 

    snakeObj snake(row, col, map);
    dataMap.setVal(row, col, metaData(row, col, true, 1));
    return snake; 
}
// ================= game logic

void setFood(coolMat<char>& map, coolMat<metaData>& mapData)
{

    int height = map.getHeight(); 
    int width = map.getWidth(); 

    int row;
    int col; 
    do{
        row = rand() % height;
        col = rand() % width;
    }while(map.getPosData(row, col) != '*');
    
    map.setVal(row, col, 'Q'); 

}
//
//
//
void visualize_dataMatrix(coolMat<metaData>& md)
{
    for(int row =0; row < mapDimensions; row++)
    {
        for(int col =0; col < mapDimensions; col ++)
        {
            metaData var = md.getPosData(row, col) ;
            if(var.stored_in_cell == 0)
            {
                if(var.known == true) { std::cout << "~ "; }
                else { std::cout << "X ";}
            }
            else if(var.stored_in_cell == 1)
            {
                std::cout << "o "; 
            }
            else if(var.stored_in_cell == 2)
            {
                std::cout << "Q "; 
            }
        }
        std::cout << std::endl; 
    }
}
//
//
//
void printDataMatrix(coolMat<metaData>& md)
{
    for(int row = 0; row < mapDimensions; row++)
    {
        for(int col =0; col < mapDimensions; col++)
        {
            md.getPosData(row, col).dataDisplay();      
               std::cout << std::endl; 

        }
    }
}
//
//
//
void snakeVis(snakeObj& snakeRef, coolMat<metaData>& md, coolMat<char>& map)
{
    
    int headRow = snakeRef.getSnakeHead().row; 
    int headCol = snakeRef.getSnakeHead().col; 
    
    bool complete = false; 

    int rowPos =0; 
    int colPos =0;
    while(!complete)
    {
        // look at row
        if(colPos < mapDimensions)
        {
            // mark when food or snake body is found
            if(map.getPosData(headRow, colPos) == 'Q' )
            {
               md.setVal(headRow, colPos, metaData(headRow, colPos, true, 2)); 
            }
            else if(map.getPosData(headRow, colPos) == 'o')
            {
                md.setVal(headRow, colPos, metaData(headRow, colPos, true, 1)); 

            }
            else
            {
               md.setVal(headRow, colPos, metaData(headRow, colPos, true, 0)); 
            }
        }       
        // look at col
        if(rowPos < mapDimensions)
        {
            // mark when food or snake body is found
            if(map.getPosData(rowPos, headCol) == 'Q' )
            {
               md.setVal(rowPos, headCol, metaData(rowPos, headCol, true, 2)); 

            }
            else if(map.getPosData(rowPos, headCol) == 'o')
            {
               md.setVal(rowPos, headCol, metaData(rowPos, headCol, true, 1)); 

            }
            else
            {
                md.setVal(rowPos, headCol, metaData(rowPos, headCol, true, 0)); 
               
            }
        }
        colPos++; 
        rowPos++; 
        
        if(rowPos >= mapDimensions && colPos >= mapDimensions){complete = true;}
    }
    visualize_dataMatrix(md);
}
//
//
//
bool moveLogic(int rowOffset, int colOffset, coolMat<char>& map, snakeObj& snake)
{


    // !!!!!!!!!!!! make sure that you rewrite the  
    // !!!!!!!!!!!! AI's movement logic, should differ
    // !!!!!!!!!!!! from the player movement logic


    bool gameOver = snake.makeMove(rowOffset, colOffset, map);

        system("cls");
        map.showMatrix(); 
   
    return gameOver; 
}
// =================== run the game
void runGame (coolMat<char>& map, coolMat<metaData>& md, snakeObj& snake)
{

    bool gameOver = false; 

    // initial board display
    map.showMatrix(); 
    std::cout<<std::endl; 
    snakeVis(snake, md, map); 

    while(gameOver == false)
    {
        int key_press = 0;
        
        switch((key_press=getch()))
        {
            case 72: // up key
            gameOver = moveLogic(-1,0,map, snake); // move snake
            std::cout<<std::endl; 
            snakeVis(snake, md, map); // update meta data
            break;
            
            case 80: // down key
            gameOver = moveLogic(1,0,map, snake);
            std::cout<<std::endl; 
            snakeVis(snake, md, map); 
            break;
            
            case 75: // left key
            gameOver = moveLogic(0,-1,map, snake); 
            std::cout<<std::endl; 
            snakeVis(snake, md, map); 
            break;
            
            case 77: // right key
            gameOver = moveLogic(0,1,map, snake); 
            std::cout<<std::endl; 
            snakeVis(snake, md, map); 
            break;
            
            case 107: // k = kill game
            gameOver = true; 
            break; 

            default:
            break; 
        }
        // if food found : 
        // food is reset
        // snake's boolean 'has eaten' value is reset to false 
        // meta_data array is reset | new food location is unknown 
        if(snake.snakeAteFood() == true) 
        { 
            setFood(map, md); 
            snake.makeSnakeHungry(); 
            set_data_matrix(md, map); 
        }
    } 
    
    std::cout << "\n\nGame Over" << std::endl; 
    system("pause"); 
    system("cls");
}
//
//
//
} // namespace SNAKE_AI

void playSnake_AI(int mapSize)
{
    //  game setup 
    system("cls");
    SNAKE_AI::mapDimensions = mapSize; 
    srand(time(0));

    //  map & metaData setup
    coolMat<char> map = SNAKE_AI::buildMap(); 
    coolMat<metaData> mapData = SNAKE_AI::parallelData(); 
    SNAKE_AI::set_data_matrix(mapData, map); 
    snakeObj snake = SNAKE_AI::initializeCharacter(map, mapData); 

    //  run game
    SNAKE_AI::setFood(map, mapData);
    SNAKE_AI::runGame(map, mapData, snake); 
}

/*
Base Game :: 

[X] load environment : starting body, map, food gen
[X] snake movement 
[X] eat food, grow body (matrix cell = 1) | same size if not
[X] game over if eat own body (matrix cell = 2)
[X] game over if out of bounds 

implement AI :: 

[X] build parallel metaData matrix
[X] write a metaData reset - used when initializing map & when food is eaten
[X] update metaData when food is placed
[X] update metaData when food is eaten
[X] give the snake vision - snake can see an 8 x 8 square, with its head being the center
[] write heuristic
[] write A* search
[] AI movement | no keyboards used anymore
*/

/*
v = snake's vision 
o = snake body 
* = empty spaces
Q = food

* * * * * * * * v * * * * *  
* * * * * * * * v * * * * * 
v v v v v v o o o v v v v v 
* * * * * * o * v * * * * *
* Q * * o o o * v * * * * * 
* * * * o * * * v * * * * * 
* * * * o * * * v * * * * * 
* * * * o * * * v * * * * * 
* * * * * * * * v * * * * * 

the food is within the snake's line
of sight, so the food is known.
since the food is known, we can make
a path to it with A* 

*/