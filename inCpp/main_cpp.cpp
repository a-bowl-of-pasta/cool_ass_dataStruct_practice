#include <iostream>
#include "theGames/snake.cpp"
int main()
{
    std::cout << "this is a menue to test out the various data structures and some of their algorithms" <<std::endl; 
    std::cout << "1.) snake\n2.) AI sliding puzzle solver\n3.) AI map directions\n4.) interactive grid world"<<std::endl; 
    
    int choice; 

    std::cin>>choice; 
    system("cls"); 

    if(choice == 1)
    {
        playSnake(); 
    }
    else if(choice == 2)
    {

    }
    else if(choice == 3)
    {

    }
    else if(choice == 4)
    {

    }
    


}