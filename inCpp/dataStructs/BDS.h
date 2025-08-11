#ifndef BASIC_DATA_STRUCTURES_HEADER
#define BASIC_DATA_STRUCTURES_HEADER

#include <iostream>

// ====================== linked list class
template <class T>
class LL
{
    // ================= node struct
    struct node
    {
        T data; 
        node * nextNode; 
        node * prevNode;

        // tail <-> new node <-> head
        node(T data)
        {
            this->data = data; 
            prevNode = nullptr; 
            nextNode = nullptr; 
        }
    };
    // ===================
    // <- head <-> tail ->

    node * head; 
    node * tail; 
    int nodeCount;
    bool list_circularity; 

    // ================ helper methods

    void deleteLastNode()
    {
        if(head){
            delete head;
            head = nullptr;
            tail = nullptr;  
        }

    }
public: 

    // ================================= basic node stuff
    void add_node(T data)
    {
        node * newAdd = new node(data); 

        // append new node to end of list
        if(nodeCount == 0) 
        {
            head = tail = newAdd;
        }
        else 
        {
            tail -> nextNode = newAdd; 
            newAdd -> prevNode = tail; 
            tail = newAdd; 
           
        }

        // make new node the tail and connect to head
        if(list_circularity == true)
        {
            head -> prevNode = tail; 
            tail -> nextNode = head; 
        }
        nodeCount ++; 
    }

    T getHeadData(){ return head->data; }
    T getTailData(){ return tail->data; }
    int getSize(){return nodeCount; }
    void set_circularity(bool isCircular)
    {
        if(isCircular == false)
        {
            head -> prevNode = nullptr; 
            tail -> nextNode = nullptr;
        }
        else 
        {
            head -> prevNode = tail; 
            tail -> nextNode = head; 
        }
    }

    // =========================== node removal 
    
    void removeTail()
    {
       
        if(nodeCount == 1) // delete only node
        {
            deleteLastNode(); 
        }
        else if(tail != nullptr && nodeCount > 1) // delete tail and reconnect
        {
            node * newTail = tail ->prevNode; 
            delete tail; 
            tail = newTail;

            if (list_circularity == true)
            {
                tail ->nextNode = head; 
                head-> prevNode = tail;
            }
            newTail = nullptr;  
        }
        else // there are not any nodes to delete
        {
            return;
        }
        nodeCount--; 
    }

    void removeHead()
    {
        if(nodeCount == 1) // remove last node
        {
            deleteLastNode(); 
        }
        else if(head != nullptr && nodeCount > 1) // remove and reconnect head
        {
            node* newHead = head -> nextNode; 
            delete head; 
            head = newHead; 

            if(list_circularity == true)
            {
                tail -> nextNode = head; 
                head->prevNode = tail; 
            }
            newHead = nullptr; 
        }
        else
        {
            return; 
        }
        nodeCount--; 
    }

    // ============= constructor / destructor
    
    LL(bool isCircular)
    {
        nodeCount = 0; 
        head = nullptr; 
        tail = nullptr;
        list_circularity = isCircular; 
    }
    ~LL()
    {        
        if (head == nullptr){return;}
        // un-circularify the LL and initialize trash
        
        if(list_circularity == true)
        {
            set_circularity(false); 
        }

        node * trash = head;
          
        // make trav = next node; delete current node; move trav
        while (trash != nullptr)
        {
            node * trav = trash->nextNode; 
            delete trash; 
            trash = trav; 
            nodeCount--; 
        }

    }
};

// ========================== stack class
template <class T>
class stack
{
    
    LL<T>* baseList = nullptr; 

    public: 

    void push(T data)
    {
        baseList->addNode(data);
    }
    void pop()
    {   
        if(!isEmpty())
        {
            baseList->removeTail();
        }
    }
    T top()
    {
        if(!isEmpty())
        {
            return baseList->getTailData();
        }
        return;  
    }
    bool isEmpty()
    {
        if(baseList->getSize() == 0){return true;}
        else{return false;}
    }
    int size()
    {
        return baseList->getSize(); 
    }
    stack()
    {
        baseList = new LL<T>(false); 
    }
    ~stack()
    {
        delete baseList;
    }
};

// ========================= queue class
template<class T>
class queue 
{
    LL<T>* baseList = nullptr; 

    public:

    void push(T data)
    {
        baseList->addNode(data);
    }
    void pop()
    {   
        baseList->removeHead();
    }
    T top()
    {
        if(!isEmpty())
        {
            return baseList->getHeadData();
        }
            return; 
    }
    bool isEmpty()
    {
        if(baseList->getSize() == 0){return true;}
        else{return false;}
    }
    int size()
    {
        return baseList->getSize(); 
    }
    queue()
    {
        baseList = new LL<T>(false); 
    }
    ~queue()
    {
        delete baseList; 
    }
};

// ===================== matrix class
template <class T>
class coolMat{
/*
        3 x 3 coolMat 
        0 0 0 
        0 0 0 
        0 0 0 
*/
    T ** matrix;  
    T defaultValue; 
    int height; 
    int width; 
    bool boundWrapping;
    bool safetyBorder; 

// ======================= helper

public: 

    bool setVal(int row, int col, T val)
    {

        /*
            reference matrix
            with coordinates 

            [0,0]  [0,1]  [0,2]
            [1,0]  [1,1]  [1,2]
            [2,0]  [2,1]  [2,2] 
        */
        bool outOfBounds = false; 
        if (safetyBorder == false && safetyBorder == false) // no border and no wrapping 
        {
           /*
                user has no safety
                out of bounds returns true
            */
            if(row > height -1 || col > width -1)
            {
                outOfBounds = true; 
            }
            else
            {
                matrix[row][col] = val; 
            }   

        }
        else if(safetyBorder == true) // safety border is on -> inherently no wrapping 
        {
             /*
                does not allow out of bounds
                val will be set at closes
                perimeter instead of going out
                of bounds

                [3,1] becomes [2,1] | [1,3] becomes [1,2]
            */
            
            // ------- out of bounds in + direction
            if(row > height-1) row = height - 1; 
            if (col > width-1) col = width -1; 

            // -------- out of bounds in - direction
            if(row < 0) row = 0;    
            if(col < 0) col = 0;
            
            // --------- correctly setting
            matrix[row][col] = val; 
        }
        else // there is bound wrapping but not border safety 
        {
            /*
                user wraps around when out of bounds

                [3, 1] becomes [0,1]
                [0,3] becomes [0,0]
                [-1,2] becomes [2,2]
                [1,-1] becomes [1,2] 
            */
            
            // wrap in + direction
            if(row > height-1) row = 0; 
            if (col > width -1) col = 0;

            // wrap in - direction
            if(row < 0) row = height -1; 
            if(col < 0) col = width -1; 

            matrix [row][col] = val; 
        }
        return outOfBounds; 
    }

    void resetVal(int row, int col)
    {
        bool validRow = false; 
        bool validCol = false; 

        if(row >= 0 && row < height) validRow = true; 
        if(col >= 0 && col < width) validCol = true; 

        if( validRow == true && validCol == true)
        {
            matrix[row][col] = defaultValue; 
        }
    }

    void showMatrix()
    {
        for(int row = 0 ; row < height; row ++)
        {
            for(int col = 0; col < width ; col++)
            {
                std::cout<< matrix[row][col] << " ";        
            }
            std::cout << std::endl; 
        }
    }

    int getHeight(){ return height; }
    int getWidth(){ return width; }
    bool isBoundWrapping(){ return boundWrapping; }
    bool isSafetyBorder(){ return safetyBorder; }
    void setBoundWrapping(bool valSetter) { boundWrapping = valSetter; }
    void setSafetyBorder(bool valSetter) { safetyBorder = valSetter; }

    coolMat(int height, int width, bool boundWrapping, bool safetyBorder)
    {
        defaultValue = T{}; 
        matrix = new T*[height];
        for(int i =0; i < height; i++)
        {
            matrix [i] = new T[width](); 
        }
        this->boundWrapping = boundWrapping; 
        this->safetyBorder = safetyBorder; 
        this-> height = height; 
        this-> width = width; 
    }
       coolMat(int height, int width, T defaultValue , bool boundWrapping, bool safetyBorder)
    {
        this->defaultValue = defaultValue;
        matrix = new T*[height];
        for(int i =0; i < height; i++)
        {
            matrix [i] = new T[width](); 
            
            for (int j = 0; j < width; j++)
            {
                matrix[i][j] = defaultValue;
            }
        }
        this->boundWrapping = boundWrapping; 
        this->safetyBorder = safetyBorder; 
        this-> height = height; 
        this-> width = width; 
    }

    ~coolMat()
    {
        for(int i = 0; i < height; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix; 
    }

};

#endif 