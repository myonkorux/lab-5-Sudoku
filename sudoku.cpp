/*Tim Chang
  sudoku.cpp
  This is where we will play sudoku. 
  A sudoku file will be read in and displayed, and the user will enter 
  a number as well as an index to modify the board. The game will
  be over when the board is filled and all the rules are followed
*/
#include<iostream>
#include"Puzzle.h"
using namespace std;

int main(){
  int done=0,row=0,piece=0, choice=0;
  char col;

  Puzzle<int> p("sudoku.txt");

  cout << "Welcome to Sudoku.\n"; 
  while(!done){
    cout << p;
    cout << "Press 1 to enter a number. Press -1 to quit.\n";    
    cin >> choice;

    switch(choice){
    case 1:
      cout << "which number would you like to enter? ";
      cin >> piece;
      cout << "choose a row [1-9]: ";
      cin >> row;
      if(row>=9){  //If row is not a digit, or it is out of bounds, return error.
	cout << "Invalid row. Please try again.\n";
	break;
      }
      cout << "choose a column [a-i]: ";
      cin >> col;
      if(!isalpha(col) || (col-97)>=9){  //if the column is not a letter or if the index is out of bounds
	cout << "Invalid col. Please try again.\n";
	break;
      }
      p.place(row,col,piece);
      break;
    case -1:
      cout <<"Thanks for playing!\n";
      done=1;
      break;
    default:
      cout<< "Sorry, please try again.\n";
    }

    if(p.complete()){
      if(p.win()){
	cout << "you win!\n";
	done =1;
      }
      else
	cout<<"keep trying!\n";
    }
  }
}
