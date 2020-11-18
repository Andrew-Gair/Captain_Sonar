/*
// Author:Andrew Gair
// Date: October 2020
// Purpose: Header file for CaptainSonar class.
*/

#ifndef CAPTAIN_SONAR_H
#define CAPTAIN_SONAR_H

#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<cmath> // For absulute value abs() and pow().

enum InputCode {
  north, east, south, west,
  sonar, radar, silent, torpedo, mine, revert,
  noVal, quit
};

class CaptainSonar
{
  public:
    std::vector<std::vector<char>> Map;     // Contains what is actually shown to user/used in calculations.
    std::vector<std::vector<char>> PrevMap; // Used for 'revert' functionality.
    std::vector<char> MovementLog;          // Tracks submarine movements for use in 'radar' functionality.
    
    char Alphabet[16] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o', '\0' }; // Where \0 is null-terminator. 

  // Map modification methods
  void FindSubmarine(std::vector<std::vector<char>> &Map, enum InputCode Direction);
  std::vector<std::vector<char>> RemoveClosedSpaces(std::vector<std::vector<char>> Map, enum InputCode Direction);
  std::vector<std::vector<char>> AddClosedSpaces(std::vector<std::vector<char>> Map, enum InputCode Direction);
  
  // Movement methods
  std::vector<std::vector<char>> SilentRunning(std::vector<std::vector<char>> Map);
  
  // Weapons methods
  std::vector<std::vector<char>> EnemyTorpedo(std::vector<std::vector<char>> Map);
  std::vector<std::vector<char>> FriendlyTorpedo(std::vector<std::vector<char>> Map);
  std::vector<std::vector<char>> FriendlyMine(std::vector<std::vector<char>> Map);
  
  // Radar methods
  std::vector<std::vector<char>> Radar(std::vector<std::vector<char>> Map);
  std::vector<std::vector<char>> ModifyTargetSector(std::vector<std::vector<char>> Map, int TargetSector);
  std::vector<std::vector<char>> ModifyOtherSectors(std::vector<std::vector<char>> Map, int TargetSector);
  
  // Sonar methods
  std::vector<std::vector<char>> Sonar(std::vector<std::vector<char>> Map, std::vector<char> MovementLog);
  
  // Assorted methods
  void DisplayMap(std::vector<std::vector<char>> &Map, char* Alphabet);
  void DisplaySetup();
  enum InputCode GetCommand();
  void RunCommand(std::vector<std::vector<char>> &Map, std::vector<std::vector<char>> PrevMap, enum InputCode UserCommand, char* Alphabet);
  int AlphabetToInteger(char* Alphabet, char UserValue);
  
  char MyGetChar(std::string DisplayText);
  int MyGetInt(std::string DisplayText);
  std::string MyGetString(std::string DisplayText);
};

#endif
