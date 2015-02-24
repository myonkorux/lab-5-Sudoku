/*Tim Chang
  Puzzle.h
  This is the interface and implementation of the puzzle class
  The puzzle will take in a text file formatted as a valid sudoku puzzle.
  This puzzle will be stored in a 2d vector named board.
  An output operator is provided.

 */
#ifndef PUZZLE_H
#define PUZZLE_H
#include<vector>
#include<iostream>
#include<string>
#include<cstring>  //for file open
#include<fstream>
#include<ctype.h>  //for isnum
//#include<stdlib.h> //for atoi
using std::ostream;
using namespace std;

template<typename T>
class Puzzle;

template<typename T>
ostream &operator<<(ostream &, const Puzzle<T> &);

template<typename T>
class Puzzle{
 public:
  friend ostream &operator<< <T>(ostream &, const Puzzle<T> &); //overloaded output
  Puzzle(string = "  ");
  T getBoard(int,int) const;
  int getSize() const;
  void place(int,char,T);  //places element T in index (int,char)
  int checkRow(int,T); //checks for existing numbers in row
  int checkCol(int,T); //checks for existing numbers in column
  int checkBox(int,int,T); //checks for exisint numbers in boxes 
  int itBox(int,int,T);  //iterates through the small boxes
  int win();  //complete, and all rules followed
  int complete(); //all spaces filled out;
 private:
  vector<vector <T> > board;  //2d vector
};

template<typename T>
Puzzle<T>::Puzzle(string name){ //constructor will input file and initialize vec
  string fname;
  ifstream infile; //input file
  vector<T> temp;  //a temp vector used to read in file
  T var;

  if(name.compare("  ")!=1){
    cout << "please input a file name: "; //if file is unspecified, take one in from the user
    cin >> fname;  //name of the file
  }else
    fname = name;

  infile.open(fname.c_str()); //opening the file
  while(!infile.eof()){ //while the file is not over
    for(int i=0;i<9;i++){
      infile >> var;  
      temp.push_back(var);  //fill a vec with a row of ints
    }
    board.push_back(temp); //add that row to a vec of vecs
    temp.clear();  //clear temp vec
  }
  //cout << "successful\n";
}

template<typename T>
T Puzzle<T>::getBoard(int i, int j) const{  //a get function to return an element of board
  return board[i][j];
}

template<typename T>
int Puzzle<T>::getSize() const{
  return board.size();
}

template<typename T>
ostream &operator<<(ostream & out, const Puzzle<T> & puzzle){ //overloading output
  out <<"*|abc|def|ghi\n";
  for(int i=0;i< 9;i++){  //This is assuming standard size of sudoku puzzle
    out << i+1;
    for(int j=0;j<9;j++){  
      if((j)%3==0)
	out << '|';
      if(puzzle.getBoard(i,j)==0 || puzzle.getBoard(i,j)=='0') //output space if 0
	out << '.';
      else
	out << puzzle.getBoard(i,j); //output board
    }
    out << '|';
    out << endl;
  }
}

template<typename T>
void Puzzle<T>::place(int row, char col, T piece){  //the place function. 
  int r=row-1,c=col-97;

  if(board[r][c]!=0){  //If we try to modify an already existing location
    cout << "Invalid placement. Element already exists.\n";
    return;
  }

  if(checkRow(r,piece)){
    cout << "Invalid placement. Element Exists in the row.\n";
    return;
  }

  if(checkCol(c,piece)){
    cout << "Invalid placement. Element Exists in the column.\n";
    return;
  }

  if(checkBox(r,c,piece)){
    cout << "Invalid placement. Element Exists in the box.\n";
    return;
  }
  board[r][c]= piece;
}

template<typename T>
int Puzzle<T>::checkRow(int i,T piece){ //checks to see if piece already exists in the user specified row. Returns 0 if no errors encountered.
  int result=0;

  for(int j=0;j<9;j++){
    if(board[i][j]==piece)
      return 1;
  }

  return 0;
}

template<typename T>
int Puzzle<T>::checkCol(int j,T piece){ //checks for exisitng piece in user specified column. Returns 0 if no errors encountered
  for(int i=0;i<9;i++){
    if(board[i][j]==piece)
      return 1;
  }

  return 0;
}

template<typename T>
int Puzzle<T>::checkBox(int row, int col, T piece){ //checks for existing piece in 3x3 square. Returns 0 if no errors encountered
  //This was not fun to write. But it probably doesn't affect efficiency

  if(row==0||row==1||row==2){  //are we in the first three rows?
    if(col==0||col==1||col==2){  //top left box?
      if(itBox(0,0,piece))
	return 1;
    }else if(col==3||col==4||col==5){ //top middle box?
      if(itBox(0,3,piece))
	return 1;
    }else if(col==6||col==7||col==8){ //top right box?
      if(itBox(0,6,piece))
	return 1;
    }
  }else if(row==3||row==4||row==5){ //are we in the second three rows?
    if(col==0||col==1||col==2){  //middle left box?
      if(itBox(3,0,piece))
	return 1;
    }else if(col==3||col==4||col==5){  //center box?
      if(itBox(3,3,piece))
	return 1;
    }else if(col==6||col==7||col==8){   //middle right box?
      if(itBox(3,6,piece))
	return 1;
    }
  }else if(row==6||row==7||row==8){//are we in the last three rows?
    if(col==0||col==1||col==2){   //bottom left box?
      if(itBox(6,0,piece))
	return 1;
    }else if(col==3||col==4||col==5){  //bottom middle box?
      if(itBox(6,3,piece))
	return 1;
    }else if(col==6||col==7||col==8){  //bottom right box?
      if(itBox(6,6,piece))
	return 1;
    }
  }

  return 0;
}

template<typename T>
int Puzzle<T>::itBox(int row,int col, T piece){ //iterates through small boxes and looks for exisitng pieces. Returns 1 if error found
  for(int i=row;i<(row+3);i++){ //small boxes are 3x3. so, we iterate a 3x3 box
    for(int j=col;j<(col+3);j++){
      if(board[i][j]==piece)
	return 1;
    }
  }
  return 0;
}

template<typename T>
int Puzzle<T>::complete(){  //iterates through board to see if complete. Returns 1 if complete. Apologies for inconsistency.
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(board[i][j]==0)
	return 0;
    }
  }

  return 1;
}

template<typename T>
int Puzzle<T>::win(){ //iterates through board to see if all rules are followed. This is pretty intensive and should only be run once. Returns 1 if all rules are followed. Apologies for inconsistency.
  for(int row=0;row<9;row++){  //runs checkRow on each row for every possible value
    for(int piece=1;piece<10;piece++){
      if(!checkRow(row,piece))
	 return 0;
    }
  }

  for(int col=0;col<9;col++){ //runs checkCol on each row for every possible value
    for(int piece=1;piece<10;piece++){
      if(!checkCol(col,piece))
	 return 0;
    }
  }

  for(int row=0;row<9;row+=3){  //runs itBox on every box.
    for(int col=0;col<9;col+=3){
      for(int piece=1;piece<10;piece++){
	if(!itBox(row,col,piece))
	  return 0;
      }
    }
  }
  cout<<"boxes good\n";
  return 1;
}

#endif
