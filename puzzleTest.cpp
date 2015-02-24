/*Tim Chang
  puzzleTest.cpp

  This is a simple main file that instantiates two sudoku puzzles. One int and one char 
 */
#include<iostream>
#include<string>
#include"Puzzle.h"
using namespace std;

int main(){
  Puzzle<int> p("sudoku.txt"); //initializing one int puzzle
  Puzzle<char> w("wordoku.txt");

  cout << p;
  cout << w;
}
