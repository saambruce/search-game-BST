//Bruce, Samantha                                                                                                                                                                                           
//gamebst.h                                                                                                                                                                                                 
//October 21, 2020                                                                                                                                                                                          

//Description: Class and functions are declared                                                                                                                                                             

//Assumptions: N/A                                                                                                                                                                                          

//Source: N/A                                                                                                                                                                                               

#include <iostream>
#include <string>
using namespace std;

struct TreeNode{
    string key;
    int maxPlayers;
    int playtime;
    TreeNode* left;
    TreeNode* right;
};

class GameBST
{
private:
  TreeNode* root;

  //helper function                                                                                                                                                                                         
  void helpPrint(TreeNode*);
  void searchKey(TreeNode*, string);
  void searchPlayable(TreeNode*, int);
  int findHeight(TreeNode*);
  bool removeGame(TreeNode *&, string);
  TreeNode* findMin(TreeNode*);
  TreeNode* makeEmpty(TreeNode*);
  TreeNode* clone(TreeNode*) const;
  bool searchTree(TreeNode*, string);

public:
  GameBST();
  GameBST(const GameBST &);
  GameBST& operator=(const GameBST&);
  ~GameBST();

  void insert(string, int, int);
  bool remove(string);
  int getHeight();
  void print();
  void printGame(string);
  void printPlayable(int);
  bool search(string);
};
