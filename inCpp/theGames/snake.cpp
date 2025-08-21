
#include "../dataStructs/BDS.h"
#include <conio.h>
#include <math.h>


class snakeObj
{
    // ================ position struct
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
    bool ateFood; 
    
    public:
    // ================================================= snake movement 
    bool moveSnake(int row, int col, coolMat<char>& map)
    {  
        if(map.getPosData(row, col) == 'Q') //add node, don't remove tail
        {
            snakeBody.add_node(position(row, col)); 
            map.resetVal(row,col); 
            map.setVal(row, col, 'o'); 
            ateFood = true; 
            return false; 
        }
        else if(map.getPosData(row, col) == 'o') // don't add node, replace head with X
        {
            map.resetVal(snakeBody.getTailData().row, snakeBody.getTailData().col); 
            map.setVal(snakeBody.getTailData().row, snakeBody.getTailData().col, 'x');
            return true; 
        }
        else // normal movement
        {
            if(map.outOfBoundsCheck(row, col) == true) // out of bounds
            {
                map.resetVal(snakeBody.getTailData().row,snakeBody.getTailData().col);           
                map.setVal(snakeBody.getTailData().row, snakeBody.getTailData().col, 'x');
                return true; 
            }
            else // not out of bounds
            {
                map.setVal(row, col, 'o');
                snakeBody.add_node(position(row, col)); 
                
                // movement animation
                if(snakeBody.getSize() > 1)
                {
                    map.resetVal(snakeBody.getHeadData().row, snakeBody.getHeadData().col);
                    snakeBody.removeHead();                 
                }
                return false; 
            }
        } 
    }

    // ============================================================ player movement driver
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
        return moveSnake(row, col, map); 
    }

    bool snakeAteFood(){return ateFood; }
    void makeSnakeHungry(){ateFood = false; }
    //============================================ constructor
    snakeObj(int row, int col, coolMat<char>& map): snakeBody(false)
    {
        moveSnake(row, col, map);  
        ateFood = false; 
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
            
            case 107:
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

}
void playSnake()
{

    srand(time(0));
    coolMat<char> map = buildMap(7);
    snakeObj snake = initializeCharacter(map); 
    setFood(map); 
    runGame(map, snake); 

}


/*
[X] load environment : starting body, map, food gen
[X] snake movement 
[X] eat food, grow body (matrix cell = 1) | same size if not
[X] game over if eat own body (matrix cell = 2)
[X] game over if out of bounds 
[ ] implement AI 
*/