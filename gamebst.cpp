//Bruce, Samantha                                                                                                                                                                                           
//gamebst.cpp                                                                                                                                                                                               
//October 21, 2020                                                                                                                                                                                          

//Description: Method Implementation file where functions                                                                                                                                                   
//are written and implemented.                                                                                                                                                                              

//Assumptions: Correct input type for parameters                                                                                                                                                            

//Sources: N/A                                                                                                                                                                                              

#include <iostream>
#include <string>
#include "gamebst.h"
using namespace std;

//Constructor: Creates an empty bst                                                                                                                                                                         
//Post: Creates a VALID empty bst                                                                                                                                                                           
GameBST::GameBST()
{
  root = NULL;
}

//Copy Constructor: Initializes he new bst to be equivalent                                                                                                                                                 
//to the old bst                                                                                                                                                                                            
//Pre: Old bst is a valid bst                                                                                                                                                                               
//Post: Creates a deep copy of old bst                                                                                                                                                                      
GameBST::GameBST(const GameBST &rhs)
{
  root = nullptr;
  root = clone(rhs.root);
}

//Copy Assignment: sets object parameter to be equivalent                                                                                                                                                   
//to old bst and returns a reference to "this" object                                                                                                                                                       
//Pre: Old Tree is a valid BST                                                                                                                                                                              
//Post: Creates a deep copy of the originial bst                                                                                                                                                            
GameBST& GameBST::operator=(const GameBST &rhs)
{
  makeEmpty(root);
  root = clone(rhs.root);
  return *this;
}

//Clone Helper Function: creates identical data members of                                                                                                                                                  
//those in orginal bst which is called in copy const/assign                                                                                                                                                 
//Pre: bst called is valid                                                                                                                                                                                  
//Post: returns the newly created data members                                                                                                                                                              
TreeNode* GameBST::clone(TreeNode *t) const
{
  if(t == nullptr)
    return nullptr;
  TreeNode *temp = new TreeNode();

  temp->key = t->key;
  temp->playtime = t->playtime;
  temp->maxPlayers = t->maxPlayers;

  temp->left = clone(t->left);
  temp->right = clone(t->right);
  return temp;
}

//Insert Function: Inserts new data into bst                                                                                                                                                                
//Pre: inserted data matches parameters string and integer                                                                                                                                                  
//Post: Data inserted from least to greatest (left to right in bst)                                                                                                                                         
void GameBST::insert(string game, int players, int time)
{
  //Create new node if node/tree is empty                                                                                                                                                                   
  TreeNode *tree = new TreeNode;
  TreeNode *parent;
  TreeNode *current;

  tree->key = game;
  tree->maxPlayers = players;
  tree->playtime = time;

  tree->left = nullptr;
  tree->right = nullptr;

  if (root == nullptr)
    root = tree;
  else {
    current = root;

    while (current)
    {
      parent = current;

      if (tree->key > current->key)
        current = current->right;

      else
        current = current->left;
    }
    if(tree->key < parent -> key)
      parent->left = tree;
    else
      parent->right = tree;
  }
}

//Get Height Function: Returns # of nodes                                                                                                                                                                   
//from top to bottom - 1                                                                                                                                                                                    
//Pre:                                                                                                                                                                                                      
//Post: Returns integer                                                                                                                                                                                     
int GameBST::getHeight()
{
  int Height = findHeight(root);
  return Height-1;
}

//Helper function for getHeight(): counts the                                                                                                                                                               
//number of nodes from top to bottom INCLUDING                                                                                                                                                              
// the root                                                                                                                                                                                                 
//Pre: Must take in a valid bst; could be empty                                                                                                                                                             
//Post: Returns the bigger integer (compares the left and right)                                                                                                                                            
int GameBST::findHeight(TreeNode* p)
{
  if(p == nullptr)
    return 0;
  else{
    int heightL = findHeight(p->left);
    int heightR = findHeight(p->right);

    if(heightL > heightR)
      return(heightL+1);
    else
      return(heightR+1);
  }
}

//Remove Function: called when wanting to remove a node in bst                                                                                                                                              
//Pre: Takes in a valid string                                                                                                                                                                              
//Post: Returns False if game is not found and True if found                                                                                                                                                
bool GameBST::remove(string gName)
{
  return removeGame(root, gName);
}

//Helper function of remove(string): Looks for the node based                                                                                                                                               
//on the given name                                                                                                                                                                                         
//Pre: Takes in valid BST and valid string                                                                                                                                                                  
//Post: Returns the node                                                                                                                                                                                    
bool GameBST::removeGame(TreeNode *&p, string gName)
{
  if(p == nullptr)
    return false;
  else if(gName < p->key)
    return removeGame(p->left, gName);
  else if(gName > p->key)
    return removeGame(p->right, gName);
  else if (p->left != nullptr && p->right != nullptr)
    {
      p->key = findMin(p->right)->key;
      removeGame(p->right, p->key);
      return true;
    }
  else {
    TreeNode *oldNode = p;
    p = (p->left !=nullptr) ? p->left : p->right;
    delete oldNode;
    return true;
  }
}

//find min helper function: finds the minimum value of bst                                                                                                                                                  
//Pre: Takes in valid tree                                                                                                                                                                                  
//Post: returns node of min value                                                                                                                                                                           
TreeNode* GameBST::findMin(TreeNode* p)
{
  if(p!=nullptr)
    while(p->left != nullptr)
      p = p->left;
  return p;
}

//helper function for print(): displays the game name in order                                                                                                                                              
//Pre: takes in valid tree                                                                                                                                                                                  
//Post: Displays the names                                                                                                                                                                                  
void GameBST::helpPrint(TreeNode *p)
{
  if(p!=NULL){
    helpPrint(p->left);
    cout<<p->key<<endl;
    helpPrint(p->right);
  }
}

//Print Function: Prints the tree inorder traversal by                                                                                                                                                      
//calling helper function                                                                                                                                                                                   
//Pre: valid helper function                                                                                                                                                                                
//Post: Displays key of tree in order                                                                                                                                                                       
void GameBST::print()
{
  helpPrint(root);
}

//Search Helper: finds if game is in tree                                                                                                                                                                   
//Pre: Valid tree and valid string                                                                                                                                                                          
//Post: Returns true or false                                                                                                                                                                               
bool GameBST::searchTree(TreeNode* root, string gName)
{
  if (root == nullptr)
    return false;
  else if(gName == root->key)
    return true;
  else if(gName > root->key)
    return searchTree(root->right, gName);
  else
    return searchTree(root->left, gName);
}

//Helper function for printGame(string): finds the information                                                                                                                                              
//assigned to node where "name" is located                                                                                                                                                                  
//Pre: Takes in Valid bst and valid name                                                                                                                                                                    
//Post: displays relevant data members in node                                                                                                                                                              
void GameBST::searchKey(TreeNode *p, string name)
{
    if(p!=NULL){
      if(p->key == name){
        cout<<"Game: "<<p->key<<endl;
        cout<<"Maximum # of Players: "<<p->maxPlayers<<endl;
        cout<<"Minimum playtime: "<<p->playtime<<endl;
      }
      else if(p->key < name)
        searchKey(p->right, name);
      else
        searchKey(p->left, name);
    }
}

//Helper function for printPlayable(int): finds the nodes the contain                                                                                                                                       
//playtime less than the "Time" given                                                                                                                                                                       
//Pre: Takes in valid bst and valid integer                                                                                                                                                                 
//Post: Displays the list of games (key)                                                                                                                                                                    
void GameBST::searchPlayable(TreeNode *p, int Time)
{
  if(p!=NULL){
    searchPlayable(p->left, Time);
    searchPlayable(p->right, Time);
    if(p->playtime <= Time) {
      cout<<p->key<<endl;
    }
  }
}

//Print Game Function: finds game and prints                                                                                                                                                                
//all the information about the game                                                                                                                                                                        
//Pre: Takes in valid string                                                                                                                                                                                
//Post: Displays relevant data members in node                                                                                                                                                              
void GameBST::printGame(string name)
{
  searchKey(root, name);
}

//Print Playable Function: finds and prints all the games with playtime                                                                                                                                     
//that is equal to or smaller than timeLeft using post-order traversal                                                                                                                                      
//Pre: Takes in valid integer                                                                                                                                                                               
//Post: Displays a list of the games that satisfy conditions in helper                                                                                                                                      
void GameBST::printPlayable(int timeLeft)
{
  searchPlayable(root, timeLeft);
}

//Delete Helper Function: deletes all nodes in bst                                                                                                                                                          
//Pre: Takes in valid bst                                                                                                                                                                                   
//Post: returns empty/nullptr                                                                                                                                                                               
TreeNode* GameBST::makeEmpty(TreeNode* t)
{
  if(t == nullptr)
    return nullptr;
  else {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  return nullptr;
}

//Destructor: Deallocates memory used to store data in bst                                                                                                                                                  
//Post: bst will be empty                                                                                                                                                                                   
GameBST::~GameBST(){
  root = makeEmpty(root);
}
