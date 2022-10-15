#include <iostream>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to 
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/** 
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 * 
 */
int checkForWinner(char grid[], int dim);


/** 
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 * 
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current 
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);
 

/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
  /* Convert r,c to 1D index here */
  return grid[((dim*r) + c)];
}

int idxToRow(int idx, int dim)
{
  /* Add Expression here to convert idx to appropriate row */
  return ((idx / dim)+1);
}

int idxToCol(int idx, int dim)
{
  /* Add Expression here to convert idx to appropriate column */
  return (idx%dim);
}

void printTTT(char grid[], int dim)
{
  // i loop for setting the row. ex) if it is 5 x 5, i will go from
  // 0,1,2,3,4, resulting in looping through the whole array.
  for(int i = 0 ; i < dim; i++){
    // k loop for going through each of the variable in the row.
    // ex) if it is 3 x 3, it will go the the ith row, kth value, and
    // print out the value and the "|" sign.(if it is the last value 
    // in the row it will not print out the "|" sign.)
    for (int k = 0; k < dim; k++){
      if(k == (dim-1)){
        cout << " " << grid[(i*dim) + k] << " ";
      } else if (k != (dim-1)){
        cout << " " << grid[(i*dim) + k] << " " << "|"; 
      }
    }
    // return once one row is fully typed
    cout << endl;
    // in between each row, type neccesary amount of dashes ("-") 
    // except for the last line
    if(i == (dim-1)){
      continue;
    } else {
      for (int j = 0; j < (dim*4)-1; j++){
          cout << "-";
      }
    }
    cout << endl;
  }
}

int checkForWinner(char grid[], int dim)
{
  // this boolean variable "thereiswinner" will be true
  // if any wincombo(horizontal, vertical, diagonal matches) is/are there.
  bool thereiswinner = false;
  // once there is a wincombo(horizontal, vertical, diagonal matches)
  // this will increase in number and at the end, it results in 
  // determining if there is a winner
  int wincombo = 0;

  // checking if each row has all same symbols(X or O). that is not "?"
  for(int i = 0 ; i < dim; i++){
    int rowcheck = 0;
    for (int k = 0; k < (dim-1); k++){
      if((getEntryAtRC(grid, dim, i, k))=='?' || (grid[(i*dim) + k + 1])=='?'){
        break;
      }
      if((getEntryAtRC(grid, dim, i, k)) != (grid[(i*dim) + k + 1])){
        break;
      } 
      rowcheck += 1;
    }
    if(rowcheck == (dim-1)){
      wincombo += 1;
    } 
  }
  
  // checking through each colomns and checking if there are any colomn with 
  // all same symbols(X or O)
  for(int i = 0 ; i < dim; i++){
    int columncheck = 0;
    for (int k=0; k < (dim - 1); k++){
      if ((grid[(k*dim) + i]) =='?' || (grid[((k+1)*dim) + i]) =='?'){
        break;
      }
      if ((grid[(k*dim) + i]) != (grid[((k+1)*dim) + i])){
        break;
      }
      columncheck += 1;            
    }
    if(columncheck == (dim-1)){
      wincombo += 1;
    }
  }

  // checking if Left to Right Diagonal has any matches
  int LtoRDiagonal = 0;
  for(int i = 0; i < dim - 1; i++){
    if(grid[(i*dim) + i]=='?' || grid[((i+1)*dim + (i+1))]=='?'){
      break;
    }
    if(grid[(i*dim) + i] != grid[((i+1)*dim + (i+1))]){
      break;
    }
    LtoRDiagonal += 1;
    if(LtoRDiagonal == dim-1){
      wincombo += 1;
    }
  }

  // checking if Right to Left Diagonal has any matches
  int RtoLDiagonal = 0;
  for(int i = 1; i < dim; i++){
    if (grid[(i*dim) - i]=='?' || grid[((i+1)*dim) - (i+1)]=='?'){
      break;
    }
    if (grid[(i*dim) - i] != grid[((i+1)*dim) - (i+1)]){
      break;
    }
    RtoLDiagonal += 1;
    if(RtoLDiagonal == dim-1){
      wincombo += 1;
    }
  }

  // checking if there are any rows, columns, diagonals that has all 
  // same symbol, and changing the returning variable(either true or false)
  if (wincombo >= 1){
    thereiswinner = true;
  }
  return thereiswinner;
}


bool checkForDraw(char grid[], int dim)
{
  // boolean "isdraw" is what the whole function will return at the end
  // once the all rows, columns, and diagonals have one X and one O,
  // "isdraw" will become true
  bool isdraw = false;
  // bool condition1 is for checking if every row has at least one X and O.
  bool condition1 = false;
  // bool condition2 is for checking if every colomn has at least one X and O.
  bool condition2 = false;
  // bool condition3 is for checking if every left to right diagonal
  // has at least one X and O.
  bool condition3 = false;
  // bool condition4 is for checking if every right to left diagonal
  // has at least one X and O.
  bool condition4 = false;

  // going through all rows to check if all rows have at least one X and O
  int rowsatisfy = 0;
  for(int i = 0 ; i < dim; i++){
    bool XinRow = false;
    bool OinRow = false;
    for (int k = 0; k < dim; k++){
      if((grid[(i*dim) + k])=='X'){
        XinRow = true;
      } else if((grid[(i*dim) + k])=='O'){
        OinRow = true;
      }
      if(XinRow == true && OinRow == true){
        rowsatisfy += 1;
        break;
      }
    }
  }
  // if all row has at least one X and O, bool "condition1" will be true
  if(rowsatisfy == dim){
    condition1 = true;
  }

  // going through all colomns to check if all columns have at least one X and O
  int colsatisfy = 0;
  for(int i = 0 ; i < dim; i++){
    bool XinCol = false;
    bool OinCol = false;
    for (int k=0; k < dim; k++){
      if ((grid[(k*dim) + i]) =='X'){
        XinCol = true;
      } else if((grid[(k*dim) + i]) =='O'){
        OinCol = true;
      }
      if(XinCol == true && OinCol == true){
        colsatisfy += 1;
        break;
      }         
    }
  }
  // if all column has at least one X and O, bool "condition2" will be true
  if(colsatisfy == dim){
    condition2 = true;
  }

  // going through Left to Right Diagonal and checking if there is at least 
  // one X and O.
  bool XinLtoRDiagonal = false;
  bool OinLtoRDiagonal = false;    
  for(int i = 0; i < dim; i++){
    if(grid[(i*dim) + i]=='X'){
      XinLtoRDiagonal = true;
    } else if(grid[(i*dim) + i]=='O'){
      OinLtoRDiagonal = true;
    }
    // if theres one X and O in Left to Right Diagonal, bool "condition3" will be true.
    if(XinLtoRDiagonal == true && OinLtoRDiagonal == true){
      condition3 = true;
      break;
    } 
  }

  // going through Right to left Diagonal and checking if there is at least 
  // one X and O.
  bool XinRtoLDiagonal = false;
  bool OinRtoLDiagonal = false;
  for(int i = 1; i < dim+1; i++){
    if (grid[(i*dim) - i]=='X'){
      XinRtoLDiagonal = true;
    } else if (grid[(i*dim) - i]=='O'){
      OinRtoLDiagonal = true;
    }
    // if theres one X and O in Left to Right Diagonal, bool "condition4" will be true.
    if(XinRtoLDiagonal == true && OinRtoLDiagonal == true){
      condition4 = true;
      break;
    } 
  }

  // if all conditions(all row, column, and diagonal have at least one X and O) matches, the function will return true
  if(condition1==true && condition2==true && condition3==true && condition4==true){
    isdraw = true;
  }
  return isdraw;
}



/**********************************************************
 *  Complete the indicated parts of main(), below. 
 **********************************************************/
int main()
{
  // This array holds the actual board/grid of X and Os. It is sized 
  // for the biggest possible case (11x11), but you should only 
  // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
  char tttdata[121];

  // setting all the variable in the array 0 to avoid any random errors
  for(int i=0; i < 121; i++){
    tttdata[i] = '0';
  }

  // dim stands for dimension and is the side length of the 
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5). 
  int dim;

  // Get the dimension from the user
  cin >> dim;
    
  int dim_sq = dim*dim;

  for(int i=0; i < dim_sq; i++){
    tttdata[i] = '?';
  }

  // Print one of these messages when the game is over
  // and before you quit
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] =  "Draw...game over!";

  bool done = false;
  char player = 'X';

  // Show the initial starting board
  printTTT(tttdata, dim);

  while(!done){

    //**********************************************************
    // Get the current player's input (i.e. the location they want to
    // choose to place their mark [X or O]) and update the tttdata array.
    // Be sure to follow the requirements defined in the guide/writeup
    // for quitting immediately if the user input is out-of-bounds 
    // (i.e. not in the range 0 to dim_sq-1) as well as continuing to 
    // prompt for an input if the user chooses locations that have already
    // been chosen (already marked with an X or O).
    //**********************************************************

    // Add your code here for getting input

    // getting input and either quiting the program if input is out of range
    // or if it is a taken spot, it will ask for another input.
    cout << "Player " << player <<" enter your square choice [0-8]: " << endl;
    int userinput;
    cin >> userinput;
    bool goodinput = false;
    bool outofrange = false;

    // if out of range, then quit the progra
    if(userinput > ((dim*dim)-1) || userinput < 0){
      break;
    } 
    // if in range and not taken, take the input
    if(userinput <= ((dim*dim)-1) && tttdata[userinput] == '?'){
      goodinput = true;
    }
    // if the input did not qualify on the first try, this while loop will 
    // check if the next(or even more) input is out of range, taken, or qualified.
    while(!goodinput){
      cout << "Player " << player <<" enter your square choice [0-8]: " << endl;
      cin >> userinput;
      // if out of range, then quit the program
      if(userinput > ((dim*dim)-1) || userinput < 0){
        outofrange = true;
        break;
      // if in range and not taken, take it as the input
      } else if(userinput <= ((dim*dim)-1) && tttdata[userinput] == '?'){
        goodinput = true;
      }
    }
    if(outofrange == true){
      break;
    }

    // change the array variable to X or O depending on who the player is
    tttdata[userinput] = player;
    
    // Show the updated board if the user eventually chose a valid location
    // (i.e. you should have quit the loop and program by now without any 
    //  other output message if the user chosen an out-of-bounds input).

    printTTT(tttdata, dim);
    
    //**********************************************************
    // Complete the body of the while loop to process the input that was just
    //  received to check for a winner or draw and update other status, as 
    //  needed. 
    // 
    // To match our automated checkers' expected output, you must output 
    // one of the messages defined above using *one* of the cout commands 
    // (under the appropriate condition) below:
    //   cout << xwins_msg << endl;  OR
    //   cout << owins_msg << endl;  OR
    //   cout << draw_msg << endl;
    //
    // Note: Our automated checkers will examine a specific number of lines
    //  at the end of the program's output and expect to see the updated board
    //  and game status message.  You may certainly add some debug print  
    //  statements during development but they will need to be removed to 
    //  pass the automated checks.
    //**********************************************************
    
    // check for winner, and if someone won, print the winner statement(pre-created)
    // according to who the player is. And then quit the program.
    if(checkForWinner(tttdata, dim) == 1){
      if (player == 'X'){
        cout << xwins_msg << endl;
      } else if (player == 'O'){
        cout << owins_msg << endl;
      }
      break; 
    }

    // check if the game is draw, and if it is, print out the pre-created message
    // and quit the program
    if(checkForDraw(tttdata, dim) == 1){
      cout << draw_msg << endl;
      break;
    }

    // after each input and checking for winner and draw, change the player (X to O or O to X)
    if(player == 'X'){
      player = 'O';
    } else if(player == 'O'){
      player = 'X';
    }
  } // end while
  return 0;
}