#include <iostream>
#include <string>

# include "Character.h"
# include "HumanPlayerStrategy.h"
# include "Map.h"

using std::cin;
using std::cout;
using std::endl;



void HumanPlayerStrategy::execute(Map& m, Character& c) {
  string temp;
  cout << "for now just enter something" << endl;
  getline(cin, temp);
}
//void Character::openChest(Map m) {
  ////If the character is beside a chest
  //if (m.isBeside(currentPosition[0], currentPosition[1], 'T') == 1) {
    //cout << "Opening chest... Surprise!" << endl;
  //} else {
    //cout << "There is no chest around you. Nothing to open." << endl;
  //}
//}

//void Character::moveUp(Map m) {
  //if (currentPosition[1] == 0) {
    //cout << "Cannot move further, please select a different direction." << endl;
  //} else {
    //if (
        //m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'W' ||
        //m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'T' ||
        //m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'O'
        //) {
      //cout << "You cannot move into a wall, treasure, or opponent; please pick a different direction." << endl;
    //} else {
      //m.clearCell(currentPosition[0], currentPosition[1]);
      //currentPosition[1]--;
      //if (m.getCell(currentPosition[0], currentPosition[1]) == 'E'){
        //this->wonGame();
      //}
      //m.setCharacter(currentPosition[0], currentPosition[1]);
    //}
  //}
//}

//void Character::moveDown(Map m) {
  //if (currentPosition[1] == (m.getMapWidth()-1)) {
    //cout << "Cannot move further, please select a different direction." << endl;
  //} else {
    //if (
        //m.getCell(currentPosition[0], currentPosition[1] + 1) == 'W' ||
        //m.getCell(currentPosition[0], currentPosition[1] + 1) == 'T' ||
        //m.getCell(currentPosition[0], currentPosition[1] + 1) == 'O'
        //) {
      //cout << "You cannot move into a wall, treasure, or opponent; please pick a different direction." << endl;
    //}else{
      //m.clearCell(currentPosition[0], currentPosition[1]);
      //currentPosition[1]++;
      //if (m.getCell(currentPosition[0], currentPosition[1]) == 'E'){
        //this->wonGame();
      //}
      //m.setCharacter(currentPosition[0], currentPosition[1]);
    //}
  //}
//}

//void Character::moveLeft(Map m) {
  //if (currentPosition[0] == 0) {
    //cout << "Cannot move further, please select a different direction." << endl;
  //} else {
    //if (
        //m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'W' ||
        //m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'T' ||
        //m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'O'
        //) {
      //cout << "Cannot move into a wall, please select a different direction." << endl;
    //} else {
      //m.clearCell(currentPosition[0], currentPosition[1]);
      //currentPosition[0]--;
      //if (m.getCell(currentPosition[0], currentPosition[1]) == 'E'){
        //this->wonGame();
      //}
      //m.setCharacter(currentPosition[0], currentPosition[1]);
    //}
  //}
//}

//void Character::moveRight(Map m) {
  //if (currentPosition[0] == (m.getMapLength()-1)) {
    //cout << "Cannot move further, please select a different direction." << endl;
  //} else {
    //if (
        //m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'W' ||
        //m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'T' ||
        //m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'O'
        //) {
      //cout << "Cannot move into a wall, please select a different direction." << endl;
    //} else {
      //m.clearCell(currentPosition[0], currentPosition[1]);
      //currentPosition[0]++;
      //if (m.getCell(currentPosition[0], currentPosition[1]) == 'E'){
        //this->wonGame();
      //}
      //m.setCharacter(currentPosition[0], currentPosition[1]);
    //}
  //}
//}

