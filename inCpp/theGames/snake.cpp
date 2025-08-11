
#include "../dataStructs/BDS.h"
#include <conio.h>

struct snakeObj
{
    struct position
    {
        int row; 
        int col; 
        position(){row = 0; col = 0;}
        position(int r, int c)
        {
            row = r; 
            col = c; 
        }
    };
    LL<position> snakeBody;  

    void makeMove(int rowOffset, int colOffset)
    {
        
    }
    void addToSnake(int row, int col, coolMat<char>& map)
    {
        // new head position
        snakeBody.add_node(position(row, col));
        // mark on map
        bool isOutOfBounds = map.setVal(row, col, 'o');
        // remove tail 
        map.resetVal());
        // game over if out of bounds
        if(isOutOfBounds == true)
        {
            system("cls"); 
            std::cout << "GAME OVER" << std::endl; 
        }
    }

    snakeObj(int row, int col, coolMat<char>& map): snakeBody(false)
    {
        position firstPos(row, col); 
        snakeBody.add_node(firstPos);
        addToSnake(snakeBody.getHeadData().row, snakeBody.getHeadData().col, map); 

    }

};


/*
7 x 7  map

* = movable space

o = snake body
X = snake hit itself 

Q = food 

0 0 0 0 0 0 0
0 Q 0 0 0 0 0 
0 0 0 0 0 0 0
0 0 0 o 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
*/
// ================= game logic


void moveUp()
{

}
void moveDown()
{

}
void moveLeft()
{

}
void moveRight()
{

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
    map.showMatrix(); 

    return snake; 
}
// =================== run the game
void runGame ()
{

    bool gameOver = false; 
    while(gameOver == false)
    {
        int key_press = 0;
        
        switch((key_press=getch()))
        {
            case 72: // up key
            moveRight(); 
            std::cout << "move up" << std::endl; 
            break;
            
            case 80: // down key
            moveDown();
            std::cout << "move down" << std::endl; 
            break;
            
            case 75: // left key
            moveLeft(); 
            std::cout<< "move left" << std::endl; 
            break;
            
            case 77: // right key
            moveRight(); 
            std::cout << "move right" << std::endl; 
            break;
            
            case 107:
            gameOver = true; 
            std::cout << "Game Over" << std::endl; 
            break; 

            default:
            break; 
        }



    }

}
void playSnake()
{

    coolMat<char> map = buildMap(7);
    snakeObj snake = initializeCharacter(map); 
    runGame(); 

}


/*

[ ] load environment : starting body, map, food gen
[ ] snake movement 
[ ] eat food, grow body (matrix cell = 1) | same size if not
[ ] game over if eat own body (matrix cell = 2)
[ ] game over if out of bounds 
[ ] 

*/