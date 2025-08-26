#include "snakeClasses.h"
#include <conio.h>
#include <math.h>

namespace BASE_SNAKE {
    

void setFood(coolMat<char>& map)
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

bool moveLogic(int rowOffset, int colOffset, coolMat<char>& map, snakeObj& snake)
{
    bool gameOver = snake.makeMove(rowOffset, colOffset, map);

        system("cls");
        map.showMatrix(); 
   
    return gameOver; 
}
// ================= build the game
coolMat<char> buildMap(int width_and_height)
{
    coolMat<char> map(width_and_height,width_and_height, '*', false, false); 
    return map; 
}
snakeObj initializeCharacter(coolMat<char>& map)
{

    int row = (map.getHeight() - 1) / 2; 
    int col = (map.getHeight() - 1 )/ 2; 
    
    snakeObj snake(row, col, map);

    return snake; 
}
// =================== run the game
void runGame (coolMat<char>& map, snakeObj& snake)
{

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
            setFood(map); 
            snake.makeSnakeHungry(); 
        }
    } 
    
    std::cout << "\n\nGame Over" << std::endl; 
    system("pause"); 
    system("cls");
}

} // namespace BASE_SNAKE

void playSnake(int mapSize)
{

    system("cls");
    srand(time(0));
    coolMat<char> map = BASE_SNAKE::buildMap(mapSize);
    snakeObj snake = BASE_SNAKE::initializeCharacter(map); 
    BASE_SNAKE::setFood(map); 
    BASE_SNAKE::runGame(map, snake); 

}


/*
[X] load environment : starting body, map, food gen
[X] snake movement 
[X] eat food, grow body (matrix cell = 1) | same size if not
[X] game over if eat own body (matrix cell = 2)
[X] game over if out of bounds 
[ ] implement AI 
*/