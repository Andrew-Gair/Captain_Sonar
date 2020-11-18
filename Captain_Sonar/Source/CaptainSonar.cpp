
#include "CaptainSonar.h"


//------------------------------------- Find-Submarine Algorithm
//  *All map-edges and islands are marked with a special 'e' or 'i' character.
//    These characters are known as 'Closed-Spaces'.
//  *User enters a movement direction:
//    For each square:
//      1st) remove Closed-Space if Open-Space in opposite direction
//      2nd) add Closed-Space if Closed-Space in opposite direction
void CaptainSonar::FindSubmarine(std::vector<std::vector<char>> &Map, enum InputCode Direction)
{
  Map = CaptainSonar::RemoveClosedSpaces(Map, Direction);
  Map = CaptainSonar::AddClosedSpaces(Map, Direction);
}

std::vector<std::vector<char>> CaptainSonar::RemoveClosedSpaces(std::vector<std::vector<char>> Map, enum InputCode Direction)
{
  std::vector<std::vector<char>> NewMap = Map;
  for(int row = 0; row < 17; row++){
    for(int col = 0; col < 17; col++){
      if(Map[row][col] == 'x'){
        switch(Direction){
          case north: // Check if the south is an Open-Space
            if(Map[row+1][col] == '-'){
              NewMap[row][col] = '-';
            }
            break;
          case east: // Check if the west is an Open-Space
            if(Map[row][col-1] == '-'){
              NewMap[row][col] = '-';
            }
            break;
          case south: // Check if the north is an Open-Space
            if(Map[row-1][col] == '-'){
              NewMap[row][col] = '-';
            }
            break;
          case west: // Check if the east is an Open-Space
            if(Map[row][col+1] == '-'){
              NewMap[row][col] = '-';
            }
            break;
        }
      }
    }
  }
  return NewMap;
}

std::vector<std::vector<char>> CaptainSonar::AddClosedSpaces(std::vector<std::vector<char>> Map, enum InputCode Direction)
{
  std::vector<std::vector<char>> NewMap = Map;
  for(int row = 0; row < 17; row++){
    for(int col = 0; col < 17; col++){
      if(Map[row][col] == '-'){
        switch(Direction){
          case north: // Check if the south is a Closed-Space
            if(Map[row+1][col] == 'x' || Map[row+1][col] == 'e' || Map[row+1][col] == 'I'){
              NewMap[row][col] = 'x';
            }
            break;
          case east: // Check if the west is a Closed-Space
            if(Map[row][col-1] == 'x' || Map[row][col-1] == 'e' || Map[row][col-1] == 'I'){
              NewMap[row][col] = 'x';
            }
            break;
          case south: // Check if the north is a Closed-Space
            if(Map[row-1][col] == 'x' || Map[row-1][col] == 'e' || Map[row-1][col] == 'I'){
              NewMap[row][col] = 'x';
            }
            break;
          case west: // Check if the east is a Closed-Space
            if(Map[row][col+1] == 'x' || Map[row][col+1] == 'e' || Map[row][col+1] == 'I'){
              NewMap[row][col] = 'x';
            }
            break;
        }
      }
    }
  }
  return NewMap;
}


//------------------------------------- Silent Running
// Use: allows opponent's submarine to secretly move in one direction up to 4 squares (or none at all).
// 
// This function removes all Closed-Spaces that have an Open-Space within 4 squares distance.
std::vector<std::vector<char>> CaptainSonar::SilentRunning(std::vector<std::vector<char>> Map)
{
  std::vector<std::vector<char>> NewMap = Map;
  bool StopCheck = false;
  for(int row = 0; row < 17; row++){
    for(int col = 0; col < 17; col++){
      if(Map[row][col] == '-'){
      
        StopCheck = false; // Check to the north.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row-k][col] == 'x'){
            NewMap[row-k][col] = '-';
          }
          else if(Map[row-k][col] == 'I' || Map[row-k][col] == 'e'){
            StopCheck = true;
          }
        }

        StopCheck = false;  // Check to the east.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row][col+k] == 'x'){
            NewMap[row][col+k] = '-';
          }
          else if(Map[row][col+k] == 'I' || Map[row][col+k] == 'e'){
            StopCheck = true;
          }
        }
        
        StopCheck = false; // Check to the south.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row+k][col] == 'x'){
            NewMap[row+k][col] = '-';
          }
          else if(Map[row+k][col] == 'I' || Map[row+k][col] == 'e'){
            StopCheck = true;
          }
        }
        
        StopCheck = false; // Check to the west.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row][col-k] == 'x'){
            NewMap[row][col-k] = '-';
          }
          else if(Map[row][col-k] == 'I' || Map[row][col-k] == 'e'){
            StopCheck = true;
          }
        }
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row][col+k] == 'x'){
            NewMap[row][col+k] = '-';
          }
          else if(Map[row][col+k] == 'I' || Map[row][col+k] == 'e'){
            StopCheck = true;
          }
        }
        
        StopCheck = false; // Check to the south.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row+k][col] == 'x'){
            NewMap[row+k][col] = '-';
          }
          else if(Map[row+k][col] == 'I' || Map[row+k][col] == 'e'){
            StopCheck = true;
          }
        }
        
        StopCheck = false; // Check to the west.
        for(int k = 1; k <= 4 && !StopCheck; k++){
          if(Map[row][col-k] == 'x'){
            NewMap[row][col-k] = '-';
          }
          else if(Map[row][col-k] == 'I' || Map[row][col-k] == 'e'){
            StopCheck = true;
          }
        }
      }
    }
  }
  return NewMap;
}

//------------------------------------- Torpedo/Mine
// Use: The max range of a torpedo is 4 squares, when the opponent fires a torpedo you know
//      that their submarine must be within range of the torpedo detonation.
// This function will add Closed-Spaces to all Open-Spaces not within 4 squares of detonation.
// This is done by the following equation:
//   Given two sets of points: (v1, v2) and (u1, u2)
//   The two sets are within a distance of 4 if: |v1 - v2| + |v2 - u2| <= 4
std::vector<std::vector<char>> CaptainSonar::EnemyTorpedo(std::vector<std::vector<char>> Map)
{
  int TargetRow = 0;
  char CharTargetCol = ' ';
  int TargetCol;
  
  while((TargetRow < 1) || (TargetRow > 9)){
    TargetRow = MyGetInt("Please enter the target row: {integer} ");
  }
  bool EntryFailure = true;
  while(EntryFailure){
    CharTargetCol = MyGetChar("Please enter the target column: {character} ");
    for(int i = 0; i < 15; i++){ // Check entered char against array of acceptable chars.
      if(CharTargetCol == Alphabet[i]){
        EntryFailure = false;
        TargetCol = AlphabetToInteger(Alphabet, CharTargetCol);
        break;
      }
      else{
        EntryFailure = true;
      }
    }
  }
  for(int row = 0; row < 17; row++){
    for(int col = 0; col < 17; col++){
      if(Map[row][col] == '-' && abs(row-TargetRow) + abs(col-TargetCol) > 4){
        Map[row][col] = 'x';
      }
    }
  }
  return Map;
}

std::vector<std::vector<char>> CaptainSonar::FriendlyTorpedo(std::vector<std::vector<char>> Map)
{
  std::string TorpedoResults = " ";
  int TargetRow = 0;
  char CharTargetCol = ' ';
  int TargetCol;
  
  while((TargetRow < 1) || (TargetRow > 9)){
    TargetRow = MyGetInt("Please enter the target row: {integer} ");
  }
  bool EntryFailure = true;
  while(EntryFailure){
    CharTargetCol = MyGetChar("Please enter the target column: {character} ");
    for(int i = 0; i < 15; i++){ // Check entered char against array of acceptable chars.
      if(CharTargetCol == Alphabet[i]){
        EntryFailure = false;
        TargetCol = AlphabetToInteger(Alphabet, CharTargetCol);
        break;
      }
      else{
        EntryFailure = true;
      }
    }
  }
 
  while(TorpedoResults != "indirect" && TorpedoResults != "direct" && TorpedoResults != "miss"){
    TorpedoResults = MyGetString("Did torpedo [indirect] hit, [direct] hit, or [miss]? {string} ");
  }
  if(TorpedoResults == "direct"){ // Block out all open spots on map except torpedo location
    for(int row = 1; row < 16; row++){
      for(int col = 1; col < 16; col++){
        if(Map[row][col] == '-' && !(row == TargetRow && col == TargetCol)){
          Map[row][col] = 'x';
        }
      }
    }
  }
  else if(TorpedoResults == "indirect"){ // Block out the center spot, leave circle around target location open.
    for(int row = 1; row < 16; row++){
      for(int col = 1; col < 16; col++){
        if(Map[row][col] == '-' && !(pow(row-TargetRow,2) + pow(col-TargetCol,2) <= 2)){ // The "Mitchell-Cab method".
          Map[row][col] = 'x';
        }
      }
    }
    Map[TargetRow][TargetCol] = 'x';
  }
  else{ // Block out the 9 grids around torpedo location.
    for(int row = TargetRow-1; row <= TargetRow+1; row++){
      for(int col = TargetCol-1; col <= TargetCol+1; col++){
        if(Map[row][col] == '-'){
          Map[row][col] = 'x';
        }
      }
    }
  }
  
  return Map;
}

std::vector<std::vector<char>> CaptainSonar::FriendlyMine(std::vector<std::vector<char>> Map)
{
  std::string MineResults = " ";
  int TargetRow = 0;
  char CharTargetCol = ' ';
  int TargetCol;
  
  while((TargetRow < 1) || (TargetRow > 9)){
    TargetRow = MyGetInt("Please enter the target row: {integer} ");
  }
  bool EntryFailure = true;
  while(EntryFailure){
    CharTargetCol = MyGetChar("Please enter the target column: {character} ");
    for(int i = 0; i < 15; i++){ // Check entered char against array of acceptable chars.
      if(CharTargetCol == Alphabet[i]){
        EntryFailure = false;
        TargetCol = AlphabetToInteger(Alphabet, CharTargetCol);
        break;
      }
      else{
        EntryFailure = true;
      }
    }
  }
  while(MineResults != "indirect" && MineResults != "direct" && MineResults != "miss"){
    MineResults = MyGetString("Did mine [indirect] hit, [direct] hit, or [miss]? {string} ");
    std::cin.clear();
    std::cin.ignore(INT8_MAX, '\n');
  }
  
  if(MineResults == "direct"){ // Block out all open spots on map except torpedo location
    for(int row = 1; row < 16; row++){
      for(int col = 1; col < 16; col++){
        if(Map[row][col] == '-' && !(row == TargetRow && col == TargetCol)){
          Map[row][col] = 'x';
        }
      }
    }
  }
  else if(MineResults == "indirect"){ // Block out the center spot, leave circle around target location open.
    for(int row = 1; row < 16; row++){
      for(int col = 1; col < 16; col++){
        if(Map[row][col] == '-' && !(pow(row-TargetRow,2) + pow(col-TargetCol,2) <= 2)){ // The "Mitchell-Cab method".
          Map[row][col] = 'x';
        }
      }
    }
    Map[TargetRow][TargetCol] = 'x';
  }
  else{ // Block out the 9 grids around torpedo location.
    for(int row = TargetRow-1; row <= TargetRow+1; row++){
      for(int col = TargetCol-1; col <= TargetCol+1; col++){
        if(Map[row][col] == '-'){
          Map[row][col] = 'x';
        }
      }
    }
  }
  
  return Map;
}


//------------------------------------- Radar
std::vector<std::vector<char>> CaptainSonar::Radar(std::vector<std::vector<char>> Map)
{
  int TargetSector = 0;
  char InSector = ' ';
  while((TargetSector < 1) || (TargetSector > 9)){
    TargetSector = MyGetInt("Please enter target sector: {integer} ");
    std::cin.clear();
    std::cin.ignore(INT8_MAX, '\n');
  }
  while(InSector != 'y' && InSector != 'n'){
    InSector = MyGetChar("Is opponent's submarine located in targeted sector? y/n {character} ");
    std::cin.clear();
    std::cin.ignore(INT8_MAX, '\n');
  }
  if(InSector == 'n'){
    return ModifyTargetSector(Map, TargetSector);
  }
  else{
    return ModifyOtherSectors(Map, TargetSector);
  }
}

std::vector<std::vector<char>> CaptainSonar::ModifyTargetSector(std::vector<std::vector<char>> Map, int TargetSector)
{
  switch(TargetSector){
    case 1: for(int row = 1; row <= 5; row++){
              for(int col = 1; col <= 5; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 2: for(int row = 1; row <= 5; row++){
              for(int col = 6; col <= 10; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 3: for(int row = 1; row <= 5; row++){
              for(int col = 11; col <= 15; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 4: for(int row = 6; row <= 10; row++){
              for(int col = 1; col <= 5; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 5: for(int row = 6; row <= 10; row++){
              for(int col = 6; col <= 10; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 6: for(int row = 6; row <= 10; row++){
              for(int col = 11; col <= 15; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 7: for(int row = 11; row <= 15; row++){
              for(int col = 1; col <= 5; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 8: for(int row = 11; row <= 15; row++){
              for(int col = 6; col <= 10; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 9: for(int row = 11; row <= 15; row++){
              for(int col = 11; col <= 15; col++){
                if(Map[row][col] == '-'){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
  }
  return Map;
}

std::vector<std::vector<char>> CaptainSonar::ModifyOtherSectors(std::vector<std::vector<char>> Map, int TargetSector)
{
  switch(TargetSector){
    case 1: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=1 && row<=5) && (col>=1 && col<=5))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 2: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=1 && row<=5) && (col>=6 && col<=10))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 3: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=1 && row<=5) && (col>=11 && col<=15))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 4: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=6 && row<=10) && (col>=1 && col<=5))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 5: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=6 && row<=10) && (col>=6 && col<=10))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 6: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=6 && row<=10) && (col>=11 && col<=15))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 7: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=11 && row<=15) && (col>=1 && col<=5))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 8: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=11 && row<=15) && (col>=6 && col<=10))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
    case 9: for(int row = 1; row <= 15; row++){
              for(int col = 1; col <= 15; col++){
                if(Map[row][col] == '-' && !((row>=11 && row<=15) && (col>=11 && col<=15))){
                  Map [row][col] = 'x';
                }
              }
            }
            break;
  }
  return Map;
}

//------------------------------------- Sonar
//Algorithm: keep track of all submarine movements in a vector
// When the opponent says their truth+lie, trace all possible routes using movement vector.
// If opponent used silent running, delete the movement vector and start over.
std::vector<std::vector<char>> CaptainSonar::Sonar(std::vector<std::vector<char>> Map, std::vector<char> MovementLog){

  // Get info1
    
  // Get info2
    
  for(int row = 1; row <= 16; row++){
    for(int col = 1; col <= 16; col++){
      if(Map[row][col] == '-'){
        for(unsigned int iterator = 0; iterator < MovementLog.size(); iterator++){
          
        }
      }
    }
  }
  return Map;
}


//------------------------------------- Assorted
void CaptainSonar::DisplaySetup()
{
  std::cout << "Please select a map by pressing the corresponding number:" << std::endl;
  std::cout << "  1) Alpha" << std::endl;
  std::cout << "  2) Bravo" << std::endl;
  std::cout << "  3) Charlie" << std::endl;
  std::cout << "  4) Delta" << std::endl;
  std::cout << "  5) Echo" << std::endl;
  std::cout << "  6) Golf" << std::endl;
  std::cout << "  7) Hotel" << std::endl;
  std::cout << "  8) India" << std::endl;
  std::cout << "  9) Juliet" << std::endl;
  std::cout << "  0) Kilo" << std::endl;
}

void CaptainSonar::DisplayMap(std::vector<std::vector<char>> &Map, char* Alphabet)
{
  for(int row = 0; row < 17; row++){
    for(int col = 0; col < 17; col++){

      if(row == 0 || row == 16){ // For first and last rows.
	      if(col == 1){
          std::cout << "    " << Alphabet[0]; // Print column ID (alphabetical) with extra space initialized.
	      }
	      if(col != 0 && col != 1 && col < 16){ // Print column ID with less spaces between IDs.
          std::cout << "   " << Alphabet[col-1];
	      }
      }

      else if(col == 0 || col == 16){ // For first and last columns.
	      if(row != 0 && row < 10){
          std::cout << row << "   "; // Print row ID with 3 spaces, row ID is only a single character.         
        }
	      else if(row > 9 && row < 16){
          std::cout << row << "  "; // Print row ID with 2 spaces, row ID is now 2 characters long.
	      }
      }
      
      else{ // Print the map contents as normal.
        std::cout << Map[row][col] << "   ";
      }
    }
    std::cout << std::endl;
  }
}

// GetDirection() uses a long 'if' chain as c++ switch statements
// cannot handle string comparisons.
// The function returns an enum-value declared in InputCode.
enum InputCode CaptainSonar::GetCommand()
{
  std::string userVal;
  std::cin >> userVal;
  if(userVal == "north" || userVal == "n"){
    MovementLog.push_back('n');
    return north;
  }
  else if(userVal == "east" || userVal == "e"){
    MovementLog.push_back('e');
    return east;
  }
  else if(userVal == "south" || userVal == "s"){
    MovementLog.push_back('s');
    return south;
  }
  else if(userVal == "west" || userVal == "w"){
    MovementLog.push_back('w');
    return west;
  }
  else if(userVal == "quit" || userVal == "q"){
    return quit;
  }
  else if(userVal == "sonar"){
    return sonar;
  }
  else if(userVal == "radar"){
    return radar;
  }
  else if(userVal == "silent"){
    MovementLog.clear();
    return silent;
  }
  else if(userVal == "torpedo"){
    return torpedo;
  }
  else if(userVal == "mine"){
    return mine;
  }
  else if(userVal == "revert"){
    return revert;
  }
  else{
    return noVal;
  }
}

void CaptainSonar::RunCommand(std::vector<std::vector<char>> &Map, std::vector<std::vector<char>> PrevMap, enum InputCode UserCommand, char* Alphabet)
{
  bool EntryFailure;
  
  if(UserCommand == sonar){
    Map = Sonar(Map, MovementLog);
  }
  
  else if(UserCommand == radar){
    Map = Radar(Map);
  }
  
  else if(UserCommand == silent){
    std::cout << "Opponent used Silent Running" << std::endl;
    Map = SilentRunning(Map);
  }
  
  else if(UserCommand == torpedo){
    std::string TorpedoType = " ";
    
    while(TorpedoType != "friendly" && TorpedoType != "enemy"){
      TorpedoType = MyGetString("Is this a [friendly] or [enemy] torpedo? {string} ");
    }

    if(TorpedoType == "enemy"){
      Map = EnemyTorpedo(Map);
    }
    else{
      Map = FriendlyTorpedo(Map);
    }
  }
  
  else if(UserCommand == mine){
    Map = FriendlyMine(Map);
  }
  
  else if(UserCommand == noVal){
    std::cout << "Command not accepted, try again" << std::endl;
  }
  
  else if(UserCommand == revert){
    Map = PrevMap;
    std::cout << "Undoing previous move" << std::endl;
  }
  
  else{ // Move submarine
    FindSubmarine(Map, UserCommand);
  }
}

int CaptainSonar::AlphabetToInteger(char* Alphabet, char UserValue)
{
  int ColNum = 0;
  switch(UserValue)
  {
    case 'a':
    case 'A': ColNum = 1;
              break;
    case 'b':
    case 'B': ColNum = 2;
              break;
    case 'c':
    case 'C': ColNum = 3;
              break;
    case 'd':
    case 'D': ColNum = 4;
              break;
    case 'e':
    case 'E': ColNum = 5;
              break;
    case 'f':
    case 'F': ColNum = 6;
              break;
    case 'g':
    case 'G': ColNum = 7;
              break;
    case 'h':
    case 'H': ColNum = 8;
              break;
    case 'i':
    case 'I': ColNum = 9;
              break;
    case 'j':
    case 'J': ColNum = 10;
              break;
    case 'k':
    case 'K': ColNum = 11;
              break;
    case 'l':
    case 'L': ColNum = 12;
              break;
    case 'm':
    case 'M': ColNum = 13;
              break;
    case 'n':
    case 'N': ColNum = 14;
              break;
    case 'o':
    case 'O': ColNum = 15;
              break;
    default: ColNum = 0;
             break;
  } 
}

char CaptainSonar::MyGetChar(std::string DisplayText)
{
  char TargetValue;
  bool EntryFailure = true;
  while(EntryFailure){
    EntryFailure = false;
    std::cout << DisplayText << " ";
    std::cin >> TargetValue;
    if(std::cin.fail()){
      EntryFailure = true;
      std::cin.clear();
      std::cin.ignore(INT8_MAX, '\n');
	    std::cout << "Bad value, please try again" << std::endl;    
    }
  }
  return TargetValue;
}

int CaptainSonar::MyGetInt(std::string DisplayText)
{
  int TargetValue;
  bool EntryFailure = true;
  while(EntryFailure){
    EntryFailure = false;
    std::cout << DisplayText << " ";
    std::cin >> TargetValue;
    if(std::cin.fail()){
      EntryFailure = true;
      std::cin.clear();
      std::cin.ignore(INT8_MAX, '\n');
	    std::cout << "Bad value, please try again" << std::endl;    
    }
  }
  return TargetValue;
}

std::string CaptainSonar::MyGetString(std::string DisplayText)
{
  std::string TargetValue;
  bool EntryFailure = true;
  while(EntryFailure){
    EntryFailure = false;
    std::cout << DisplayText << " ";
    std::cin >> TargetValue;
    if(std::cin.fail()){
      EntryFailure = true;
      std::cin.clear();
      std::cin.ignore(INT8_MAX, '\n');
	    std::cout << "Bad value, please try again" << std::endl;    
    }
  }
  return TargetValue;
}
