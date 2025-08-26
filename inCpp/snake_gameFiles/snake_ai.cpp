#include "snakeClasses.h"
#include <conio.h>
#include <math.h>

namespace SNAKE_AI {
    
int mapDimensions = 0; 

// ================= init game
void set_data_matrix(coolMat<metaData>& dataMap)
{
    // !!!!!!!!!!!!!!!!!!!!!!!!! write this function 
}
//
//
//
coolMat<char> buildMap()
{
    coolMat<char> map(mapDimensions, '*', false, false); 
    return map; 
}
//
//
//
coolMat<metaData> parallelData()
{
    coolMat<metaData> metDat(mapDimensions, mapDimensions, metaData(), false, false); 
    
    // !!!!!!!!!!!!!!!!!!!!!! check to see it works
    set_data_matrix(metDat); 
    // !!!!!!!!!!!!!!!!!!!!!!!
    
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

    // !!!!!!!!!!!!!!!!!!!!!! make sure this is right
    dataMap.setVal(row, col, metaData(row, col, true, 1));
    // !!!!!!!!!!!!!!!!!!!!! 

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
    
    // !!!!!!!!!!!!!!!!!!!!!!! make sure this is right
    mapData.setVal(row, col, metaData(row, col, false, 2)); 
    // !!!!!!!!!!!!!!!!!!!!!!!
    
    map.setVal(row, col, 'Q'); 

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

    // !!!!!!!!!!!!!!! double check that this is correct
    // !!!!!!!!!!!!!!! it's just running the game, so it
    // !!!!!!!!!!!!!!! likely just needs some tweaks

    bool gameOver = false; 
    map.showMatrix(); 
    while(gameOver == false)
    {
        int key_press = 0;
        
        switch((key_press=getch()))
        {
            case 72: // up key
            gameOver = moveLogic(-1,0,map, snake); 
            break;
            
            case 80: // down key
            gameOver = moveLogic(1,0,map, snake);
            break;
            
            case 75: // left key
            gameOver = moveLogic(0,-1,map, snake); 
            break;
            
            case 77: // right key
            gameOver = moveLogic(0,1,map, snake); 
            break;
            
            case 107: // k = kill game
            gameOver = true; 
            break; 

            default:
            break; 
        }
        // snake ate food, so reset food and snake's hunger
        if(snake.snakeAteFood() == true) 
        { 
            // !!!!!!!!!!!!!!!! make sure this works
            setFood(map, md); 
            // !!!!!!!!!!!!!!!!

            snake.makeSnakeHungry(); 
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

    // !!!!!!!!!!! make sure this whole cluster works as intended
    system("cls");
    SNAKE_AI::mapDimensions = mapSize; 
    srand(time(0));

    coolMat<char> map = SNAKE_AI::buildMap();
    coolMat<metaData> mapData = SNAKE_AI::parallelData(); 
    snakeObj snake = SNAKE_AI::initializeCharacter(map, mapData); 
    // !!!!!!!!!!!!!


    
    // ----------------- !!!!!!!!!!!!!!!!!!!!!!!!! make sure all this shows the right output 

    // !!!!!!!!!!!!!!!!!! write a 'print' function for metaData
    mapData.showMatrix(); 
    // !!!!!!!!!!!!!!!!!!

    std::cout << std::endl<< std::endl; 

    map.showMatrix(); 
    // ------------------ !!!!!!!!!!!!!!!!!!!!!!!     
    
    //setFood(map, mapData); 
    //runGame(map, mapData, snake); 
}

/*
Base Game :: 

[X] load environment : starting body, map, food gen
[X] snake movement 
[X] eat food, grow body (matrix cell = 1) | same size if not
[X] game over if eat own body (matrix cell = 2)
[X] game over if out of bounds 

implement AI :: 

[] build parallel metaData matrix
[] write a metaData reset - used when initializing map & when food is eaten
[] update metaData when food is placed
[] update metaData when food is eaten
[] update metaData when snake moves - old tail slot = empty when snake moves
[] give the snake vision - snake can see an 8 x 8 square, with its head being the center
[] write heuristic
[] write A* search
[] explore until food is found then path with A*
*/

/*
v = snake's vision 
o = snake body 
* = empty spaces
Q = food

* * * * * * * * * * * * * *  
* * * * * * * * v v v v v v
* * * * * * o o o v v v v v 
* * * * * * o * v v v v Q v 
* * * * o o o * * * * * * * 
* * * * o * * * * * * * * * 
* * * * o * * * * * * * * * 
* * * * o * * * * * * * * * 
* * * * * * * * * * * * * * 

the food is within the snake's line
of sight, so the food is known.
since the food is known, we can make
a path to it with A* 

*/