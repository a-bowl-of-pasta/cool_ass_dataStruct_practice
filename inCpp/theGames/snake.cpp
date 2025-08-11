
#include "../dataStructs/BDS.h"
#include <conio.h>

/*
7 x 7  map

* = movable space

o = snake body
X = snake hit itself 

Q = food 

0 0 0 0 0 0 0
0 2 0 0 0 0 0 
0 0 0 0 0 0 0
0 0 0 x 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
*/
// ================= helpful functions

void addToSnake(int row, int col, coolMat<char>& map)
{
   bool isOutOfBounds = map.setVal(row, col, 'o');
   if(isOutOfBounds == true)
   {
        std::cout << "GAME OVER" << std::endl; 
   }
}
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
void initializeCharacter(coolMat<char>& map)
{

    int row = (map.getHeight() - 1) / 2; 
    int col = (map.getHeight() - 1 )/ 2; 
    addToSnake(row, col, map);
    map.showMatrix(); 


}
// ===================== game logic





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
            break;
            
            case 75: // left key
            break;
            
            case 80: // down key
            break;
            
            case 77: // right key
            break;
            
            default:
            break; 
        }



    }

}
void playSnake()
{

    coolMat<char> map = buildMap(7);
    initializeCharacter(map); 
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