/*
// Author: Andrew Gair
// Date: October 2020
// Purpose: Captain Sonar is a board game where two teams secretly
//          maneuver submarines around on a board. Whichever team
//          can find their opponent's submarine first generally wins.
//          This program is intended to be an aid to find the
//          opponent's submarine quickly and accuratly.
*/

#include<cstdio>
#include<iostream>
#include<fstream>  // For reading from files.
#include<vector>
#include<string>
#include<cmath> // For absulute value abs() and pow().
#include<ctype.h> // For isalpha()

#include "CaptainSonar.h"




int main()
{
  CaptainSonar PlayerBoard; // PlayerBoard is a class
  
  PlayerBoard.DisplaySetup();
  
  int UserSelection;        // Tracks user input
  std::string MapSelection; // Actual name of the map chosen
  
  std::cin >> UserSelection;
  
  if(std::cin.fail()){
    std::cout << "Invalid selection, program terminating" << std::endl;
    return 0;
  }
  
  switch(UserSelection)
  {
    case 1: MapSelection = "..//Resources//Alpha";
      break;
    case 2: MapSelection = "..//Resources//Bravo";
      break;
    case 3: MapSelection = "..//Resources//Charlie";
      break;
    case 4: MapSelection = "..//Resources//Delta";
      break;
    case 5: MapSelection = "..//Resources//Echo";
      break;
    case 6: MapSelection = "..//Resources//Golf";
      break;
    case 7: MapSelection = "..//Resources//Hotel";
      break;
    case 8: MapSelection = "..//Resources//India";
      break;
    case 9: MapSelection = "..//Resources//Juliet";
      break;
    case 0: MapSelection = "..//Resources//Kilo";
      break;
    default: MapSelection = "Error";
      break;
  }

  std::ifstream MapFile; // Open file for [i]nput, as opposed to ofstream for [o]utput.
  MapFile.open(MapSelection);
  
  char Alphabet[16] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o', '\0' }; // Where \0 is null-terminator. 
  
  if(MapFile.is_open()){
    char ch;
    int rows = 0;
    int cols = 0;
    std::vector<char> tmp; // Temperary storage for map rows.
    
    while(MapFile.get(ch))
    {
      if(ch == '\n'){
        cols = 0;
        rows++;
        PlayerBoard.Map.push_back(tmp);
        tmp.clear();
      }
      else{
        tmp.push_back(ch);
        cols++;
      }
    }
    
    PlayerBoard.DisplayMap(PlayerBoard.Map, Alphabet);
    MapFile.close();
  }
  else{
    std::cout << "Couldn't open that file, exiting program." << std::endl;
    return 0;
  }
  
  std::cout << "Press 'q' or type 'quit' to exit, please enter direction..." << std::endl;
  
  //-------------------------------//
  //---- The Main program loop ----//
  //-------------------------------//
  InputCode UserCommand = noVal;
  PlayerBoard.PrevMap = PlayerBoard.Map; // Initialize PrevMap to prevent errors if user 'reverts' before entering any other commands.
  while(UserCommand != quit)
  {
    std::cout << "Enter a direction: [n]orth, [e]ast, [s]outh, [w]est." << std::endl;
    std::cout << "Or a special ability: [sonar], [silent] running, [radar], [torpedo], [mine], [revert] (to go back one step)" << std::endl;
    UserCommand = PlayerBoard.GetCommand();
    if(UserCommand != revert){
      PlayerBoard.PrevMap = PlayerBoard.Map;
    }
    PlayerBoard.RunCommand(PlayerBoard.Map, PlayerBoard.PrevMap, UserCommand, Alphabet);
    PlayerBoard.DisplayMap(PlayerBoard.Map, Alphabet);
  }
  return 0;
}
