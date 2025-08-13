
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

    bool makeMove(int rowOffset, int colOffset, coolMat<char>& map)
    {
        /*
            hypothetical moving left 

             headData = [row = 1, col = 2]
             rowOffset = 0 | colOffset = -1

             new_head_pos = [row = 1, col = 1] --> move one to the left
        */

        int row = snakeBody.getTailData().row + rowOffset; 
        int col = snakeBody.getTailData().col + colOffset;
        return  addToSnake(row, col, map);
    }
    bool addToSnake(int row, int col, coolMat<char>& map)
    {  
        // mark on map
        bool isOutOfBounds = map.setVal(row, col, 'o');
        
        if(isOutOfBounds == false) // remove tail (character movement logic)
        {
            // new head position
            snakeBody.add_node(position(row, col));
            
            // remove head (character movement animation)
            if(snakeBody.getSize() > 1 )
            {
                map.resetVal(snakeBody.getHeadData().row, snakeBody.getHeadData().col);
                snakeBody.removeHead(); 
            }
        }
        else // if out of bounds replace current 'o' with 'x' 
        {
            map.resetVal(snakeBody.getTailData().row,snakeBody.getTailData().col);           
            map.setVal(snakeBody.getTailData().row, snakeBody.getTailData().col, 'x');
        }
        
        return isOutOfBounds; 
    }

    snakeObj(int row, int col, coolMat<char>& map): snakeBody(false)
    {
        addToSnake(row, col, map); 
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
    map.showMatrix(); 

    return snake; 
}
// =================== run the game
void runGame (coolMat<char>& map, snakeObj& snake)
{

    bool gameOver = false; 
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
            
            case 107:
            gameOver = true; 
            break; 

            default:
            break; 
        }

    } 
    
    std::cout << "\n\nGame Over" << std::endl; 

}
void playSnake()
{

    coolMat<char> map = buildMap(7);
    snakeObj snake = initializeCharacter(map); 
    runGame(map, snake); 

}


/*

[ ] load environment : starting body, map, food gen
[ ] snake movement 
[ ] eat food, grow body (matrix cell = 1) | same size if not
[ ] game over if eat own body (matrix cell = 2)
[ ] game over if out of bounds 
[ ] 

*/