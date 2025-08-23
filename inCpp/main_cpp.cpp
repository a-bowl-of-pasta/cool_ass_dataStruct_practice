#include <iostream>
#include "theGames/snake.cpp"
#include "theGames/eightPuzzleSolver.cpp"
#include "theGames/gridWorld.cpp"

int main()
{
    int choice = 0 ; 
    do 
    {
        std::cout << "\nHello, I wanted to see if i could\nwrite data structures and\nalgorithms by hand." <<std::endl;
        std::cout << "so here is a collection\nof games using AI - all \nhand written : data structs, games, and algs." << std::endl<<std::endl;  
        std::cout << "1.) snake\n2.) sliding 8 puzzle\n3.) interactive grid world\n0.) End Game"<<std::endl; 
        std::cout << "enter choice :: "; 
        std::cin>>choice; 

        system("cls"); 

        if(choice == 1)
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
  
    } while(choice != 0);  

    std::cout << "hope you enjoyed at least\none of those games\n:)\n\t-the_tonester"<<std::endl<<std::endl;

    return 0; 
}