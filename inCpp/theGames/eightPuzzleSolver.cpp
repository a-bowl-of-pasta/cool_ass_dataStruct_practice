#include "../dataStructs/BDS.h"
#include <conio.h>
#include <math.h>



/*
    1 2 3
    4 5 6
    7 8 0

*/

void runGame(coolMat<int>& pb)
{

}
coolMat<int> createMap()
{
    srand(time(0)); 
    coolMat<int> puzzleBoard(3, 3, 0, false, true); 

    // puzzle randomly places nums 1-8 in all slots excluding last one [2,2]
    // last slot [2,2] will have a 0, that is the starting position 
    for(int row = 0; row < 3; row ++)
    {
        for(int col = 0; col < 3; col++ )
        {
        
            // puzzleBoard.setVal(row, col, );
        }
    }

    puzzleBoard.setVal(2,2,0); 
    return puzzleBoard; 
}


void play_eight_puzzle()
{
    coolMat<int> puzzleBoard = createMap(); 
    runGame(puzzleBoard);     
}