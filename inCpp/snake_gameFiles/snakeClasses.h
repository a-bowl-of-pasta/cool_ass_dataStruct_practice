#ifndef HELPER_SNAKE_CLASSES
#define HELPER_SNAKE_CLASSES

#include "../dataStructs/BDS.h"
struct metaData
{
    /*
        stored_in_cell - the thing the cell stores :: 
        0 = empty space
        1 = snake head
        2 = snake body 
        3 = food
    */
    int row; 
    int col; 
    int stored_in_cell;
    bool known; 

    metaData(int y, int x, bool isKnown, int inCell)
    {
        row = y; 
        col = x; 
        known = isKnown; 
        stored_in_cell = inCell;
    } 
    metaData()
    {
        row = 0; 
        col = 0; 
        known = false; 
        stored_in_cell = 0;     
    }
};
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
        
        if(map.outOfBoundsCheck(row, col) == true) // if out of bounds
        { 
            map.resetVal(snakeBody.getTailData().row,snakeBody.getTailData().col);           
            map.setVal(snakeBody.getTailData().row, snakeBody.getTailData().col, 'x');
            return true; 
        }
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
        else // normal movement, not out of bounds
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



#endif