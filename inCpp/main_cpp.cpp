#include <iostream>
#include "theGames/snake.cpp"
#include "theGames/eightPuzzleSolver.cpp"
#include "theGames/gridWorld.cpp"

int main()
{
    std::cout << "this is a menue to test out the various data structures and some of their algorithms" <<std::endl; 
    std::cout << "0.) endGame \n1.) snake\n2.) AI sliding puzzle solver\n3.) AI map directions\n4.) interactive grid world"<<std::endl; 
    
    int choice; 

    std::cin>>choice; 
    system("cls"); 

    if(choice == 0)
    {
        return 0; 
    }
    else if(choice == 1)
    {
        playSnake(); 
    }
    else if(choice == 2)
    {
        play_eight_puzzle(); 
    }
    else if(choice == 3)
    {

    }
    else if(choice == 4)
    {

    }
    

    return 0; 
}