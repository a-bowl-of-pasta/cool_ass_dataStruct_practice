#include "../dataStructs/BDS.h"
#include <conio.h>
#include <math.h>
/*
    1 2 3
    4 5 6
    7 8 0

*/
struct zeroCord
{
    int col; 
    int row; 
    zeroCord(): col(0), row(0){}
    zeroCord(int x, int y): col(y), row(x){} 
};

//======================= game functions
bool isUnique (int num, int* container, int sizeSoFar)
{

    for(int i =0; i < sizeSoFar; i++ )
    {
        if(num == container[i]) {return false; }
    }
    return true; 

}

void moveLogic(coolMat<int>& map, int rowOffset, int colOffset, zeroCord& pos)
{
    int newRow = pos.row + rowOffset; 
    int newCol = pos.col + colOffset;
   
    // if valid new pos, then switch
    if(map.outOfBoundsCheck(newRow, newCol) == false)
    { 
        map.setVal(pos.row, pos.col, map.getPosData(newRow, newCol));
        map.resetVal(newRow, newCol); 
        pos.row = newRow; 
        pos.col = newCol;
    }

    system("pause");
    system("cls");
    map.showMatrix(); 
}
bool winCheck(coolMat<int>& map)
{
    bool isCorrect = false; 
    int checker[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };

    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            if(map.getPosData(row, col) != checker[row][col]){return false; }
        }
    }

    return true;   
}

//====================== main functions

coolMat<int> createMap()
{
    srand(time(0)); 
    coolMat<int> puzzleBoard(3, 3, 0, false, true); 

    // puzzle randomly places nums 1-8 in all slots excluding last one [2,2]
    // last slot [2,2] will have a 0, that is the starting position 
    int curindx = 0; 
    int container[9] = {0}; 

    while(curindx < 8) 
    {  
        int addNum = rand() % 9; 
        
        if(addNum != 0)
        {
            if(isUnique(addNum, container, curindx) == true)
            {
                container[curindx] = addNum; 
                curindx++; 
            }
        }
    }
    container[8] = 0; 
    
    // populate the matrix
    curindx = 0;
    for(int row = 0; row < 3; row++)
    {
        for(int col =0; col < 3; col++)
        {
            puzzleBoard.setVal(row, col, container[curindx]);
            curindx++;  
        }
    }

    puzzleBoard.setVal(2,2,0); 
    return puzzleBoard; 
}

void runGame(coolMat<int>& pb)
{
    
    bool gameOver = false; 
    zeroCord pos(2,2);
    pb.showMatrix(); 
    while(gameOver == false)
    {
        int key_press = 0;
        
        switch((key_press=getch()))
        {
            case 72: // up key
            moveLogic(pb, -1, 0, pos);
            gameOver = winCheck(pb);
            break;
            
            case 80: // down key
            moveLogic(pb, 1, 0, pos);
            gameOver = winCheck(pb);
            break;
            
            case 75: // left key
            moveLogic(pb, 0, -1, pos);
            gameOver = winCheck(pb);
            break;
            
            case 77: // right key
            moveLogic(pb, 0, 1, pos);
            gameOver = winCheck(pb);
            break;
            
            case 107: // k = kill game
            gameOver = true; 
            break; 

            default:
            break; 
        }
     
    } 
    
    std::cout << "\n\nGame Over" << std::endl; 
}

void play_eight_puzzle()
{
    coolMat<int> puzzleBoard = createMap(); 
    runGame(puzzleBoard);     
}