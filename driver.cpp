//Name: Bruce, Samantha                                                                                                                                                                                     
//driver.cpp                                                                                                                                                                                                   
//October 21, 2020                                                                                                                                                                                          

//Description: Program reads a file that contains 3 variables: name of game,                                                                                                                                
//max players needed, and time need to play. The program reads the file and                                                                                                                                 
//inserts it into tree. The user can choose a game and the information will                                                                                                                                 
//be printed out. The user can choose to remove a game from the tree and                                                                                                                                    
//print out a list of games based on a certian time.                                                                                                                                                        

//Assumption: Assumes user puts in the correct type.                                                                                                                                                        
//All input is case-sensitive. Assumes user copies name correctly.                                                                                                                                          

//Source: N/A                                                                                                                                                                                               

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "gamebst.h"
using namespace std;

string filename = "boardgames.csv";

int main(){
  string input;
  ifstream nameFile(filename);
  int size = 1;

  string name;

  int players;
  string tempPlayers;

  int time;
  string tempTime;

  GameBST l;

  cout<<"Hello! Processing the "<<filename<<" file."<<endl;

  if(nameFile.is_open())
    {
      getline(nameFile, input);

      while(getline(nameFile, input)){
        for(int i = 0; i < size; i++){
          stringstream ss(input);
          getline(ss, name, ',');
          getline(ss, tempPlayers, ',');
          getline(ss, tempTime, ',');
          
          players = stof(tempPlayers.c_str());
          time = stof(tempTime.c_str());


          l.insert(name, players, time);
        }
      }
      //print tree height;                                                                                                                                                                                  
      int Height = l.getHeight();
      cout<<"Tree height is "<<Height<<endl<<endl;

      //print                                                                                                                                                                                               
      l.print();

      cout<<endl;

      string printKey;

      cout<<"Which game do you want to print? ";
      getline(cin, printKey);
      bool searchS = l.search(printKey);

      //Testing edge case: if value not found                                                                                                                                                               
      while (searchS != true) {
        cout<<"Game is not found. Cannot print. "<<endl;
        cout<<"Enter a new game to delete or 'exit' (case-sensitive): ";
        getline(cin, deleteG);

        if(deleteG == "exit"){
          deleteG = "Nothing";
          break;
        }
        Status = l.remove(deleteG);
      }

      cout<<endl;
      cout<<deleteG<<" has been removed. Printing updated tree: "<<endl;
      l.print();

      cout<<endl;

      //print playable                                                                                                                                                                                      
      int timeLeft;

      cout<<"How much time do you have (in mins)? ";
      cin>>timeLeft;

      //Testing edge case of NEGATIVE number                                                                                                                                                                
      while(timeLeft < 0){
        cout<<"Please enter a VALID time GREATER THAN 0 (in mins): ";
        cin>>timeLeft;
      }

      cout<<"Games you can play in "<<timeLeft<<" minutes are: "<<endl;
      l.printPlayable(timeLeft);

      if (timeLeft < 15)
        cout<<"None"<<endl;

      cout<<endl<<"================================="<<endl;
      cout<<"Testing Copy Constructor and Assignment"<<endl;
      GameBST l2(l);
      l2.insert("New Game", 4, 20);
      cout<<"Printing New Tree"<<endl;
      l2.print();

      cout<<endl;
      cout<<"Printing Old Tree"<<endl;
      l.print();
    }
  else
    cout<<"error";

  return 0;

}
