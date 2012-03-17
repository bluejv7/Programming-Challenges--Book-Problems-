#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Increment the cell's value (if possible)
void IncrementCell(vector<string> &field, int current_row, int current_column)
{
  //If empty, increase to 1
  if (field[current_row][current_column] == '.')
    field[current_row][current_column] = '1';
  //If not a mine, increment by 1
  else if (field[current_row][current_column] != '*')
    field[current_row][current_column]++;
}

//Increment the surrounding cells (if possible)
void IncrementSurroundingCells(vector<string> &field, int current_row, int current_column, int max_row, int max_column)
{
  //Is top row?
  if (current_row == 0)
  {
    //Is left most column?
    if (current_column == 0)
    {
      //Is bottom row?
      if (current_row + 1 == max_row)
      {
        //If not right most column, increment right
        if (current_column + 1 < max_column)
          IncrementCell(field, current_row, current_column + 1);
      }
      //Else not bottom row
      else if (current_row + 1 < max_row)
      {
        //Increment bottom
        IncrementCell(field, current_row + 1, current_column);
        
        //If not right most column, increment right and bottom
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row, current_column + 1);
          IncrementCell(field, current_row + 1, current_column + 1);
        }
      }
    }
    //Is not left most column
    else if (current_column > 0)
    {
      //Increment left
      IncrementCell(field, current_row, current_column - 1);

      //Is bottom row?
      if (current_row + 1 == max_row)
      {
        //If not right most column, increment right
        if (current_column + 1 < max_column)
          IncrementCell(field, current_row, current_column + 1);
      }
      //Else not bottom row
      else if (current_row + 1 < max_row)
      {
        //Increment bottom-left
        IncrementCell(field, current_row + 1, current_column - 1);
        //Increment bottom
        IncrementCell(field, current_row + 1, current_column);
        
        //If not right most column, increment right and bottom
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row, current_column + 1);
          IncrementCell(field, current_row + 1, current_column + 1);
        }
      }
    }
  }
  //Is not top row
  else if (current_row > 0)
  {
    //Increment the top cell
    IncrementCell(field, current_row - 1, current_column);

    //Is left most column?
    if (current_column == 0)
    {
      //Is bottom row?
      if (current_row + 1 == max_row)
      {
        //If not right most column, increment top-right, right
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row - 1, current_column + 1);
          IncrementCell(field, current_row, current_column + 1);
        }
      }
      //Else not bottom row
      else if (current_row + 1 < max_row)
      {
        //Increment bottom
        IncrementCell(field, current_row + 1, current_column);
        
        //If not right most column, increment bottom-right, right, and bottom
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row - 1, current_column + 1);
          IncrementCell(field, current_row, current_column + 1);
          IncrementCell(field, current_row + 1, current_column + 1);
        }
      }
    }
    //Is not left most column
    else if (current_column > 0)
    {
      //Increment top-left
      IncrementCell(field, current_row - 1, current_column - 1);
      //Increment left
      IncrementCell(field, current_row, current_column - 1);

      //Is bottom row?
      if (current_row + 1 == max_row)
      {
        //If not right most column, increment top-right and right
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row - 1, current_column + 1);
          IncrementCell(field, current_row, current_column + 1);
        }
      }
      //Else not bottom row
      else if (current_row + 1 < max_row)
      {
        //Increment bottom-left
        IncrementCell(field, current_row + 1, current_column - 1);
        //Increment bottom
        IncrementCell(field, current_row + 1, current_column);
        
        //If not right most column, increment top-right, right, and bottom-right
        if (current_column + 1 < max_column)
        {
          IncrementCell(field, current_row - 1, current_column + 1);
          IncrementCell(field, current_row, current_column + 1);
          IncrementCell(field, current_row + 1, current_column + 1);
        }
      }
    }
  }
}

int main()
{
  // initialize variables
  int row, column, field_num = 0;

  // While we can read in grid dimensions
  while (cin >> row >> column)
  {
    //Exit on this condition
    if (row == 0 && column == 0)
      return 0;

    //New line in beginning?
    if (field_num > 0)
      cout << endl;

    field_num++;

    vector<string> field;
    string input;
    // Read each row of input and populate the field
    for (int i = 0; i < row; i++)
    {
      cin >> input;
      field.push_back(input);
    }

    //For each mine found, increase surrounding cells by 1
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < column; j++)
      {
        //If mine found
        if (field[i][j] == '*')
        {
          //Increment numbers around cells
          IncrementSurroundingCells(field,i,j,row,column);
        }
        else if (field[i][j] == '.')
          field[i][j] = '0';
      }
    }

    //Output the field
    cout << "Field #" << field_num << ":" << endl;
    for (int i = 0; i < row; i++)
      cout << field[i] << endl;
  }

  return 0;
}