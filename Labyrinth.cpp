/*
Design the set of classes for the computer game Labyrinth.  The maze has an entrance,
an exit and is composed of a number of squares (locations), which represent rooms, walls and possibly
 doors that can be opened.  Inside the maze, in addition to the player, there are other elements:
 opponents (enemies) that can catch the player (or decrease his powers), one or more
 treasures (of different values) that the player or opponents can take, as well as a certain number
 of friends who can help the player (increase his strength, allow him to open the doors of the maze,
 etc.).  A game begins with the player entering the maze and ends when he leaves the maze,
 when he is blocked by enemies, or when he has no power left.  The score of the game is given by the sum
 the values ​​of the accumulated treasures.

 The maze is a two-dimensional painting that contains squares, each square representing a room,
 a wall or a door and is configurable at the beginning of the game.  The labyrinth (as an instance of a class
 Labyrinth) knows the elements inside them, but not their position.  Maze coordination
 it is decentralized, so that when it is drawn, it lets each component location be drawn,
 and the location, knowing what elements it contains inside, can draw them.
 Communication between the different elements of the game (maze, locations, game elements) is done through
 messages.  For example, a game item has no information about the maze, it only knows the location
 current where it is.  To do this, it will keep a pointer to the current location.  To perform
 of a move, it will query the current location (which in turn knows only its four neighbors)
 whether the movement is valid or not.

 Allowed orders are as follows:

 - east, north, south, west - specifies the player's movement in one of the four directions;
 - show_location - displays the contents of the location;
 - fight - hits the opponent if he is in an adjacent location
 - get_item (get_treasure) the player takes a friend (or treasure) who is in the same location;
 - drop_item - the player leaves a friend;
 - quit - the game ends forcibly;
 - save - the game is saved (classes must contain a Save method);
 - load - a previously saved game is loaded;
 - help - displays game controls.

 After each move of the player, the opponents move according to a certain specified strategy
 for each enemy.

 The application must contain (among other classes) a hierarchy of classes (with an abstract base class)
 associated with elements in the labyrinth, which use polymorphism.
 To scroll through the locations of the maze, the Iterator design template will be used, and for

 the design of the other classes will use the templates: AbstractFactory, Composite and Singleton.
*/

#include <vector>
#include <list>
#include <iostream>
 
 class Element;
 enum class BoxType { ROOM, WALL, DOOR };
 class MaizeBox {
  BoxType m_type;
  Element* m_ocupier;
  public:
  MaizeBox():m_type(ROOM),m_ocupier(0){}
  MaizeBox(const MaizeBox& ) = delete;
  MaizeBox& operator=(const MaizeBox& ) = delete;
  void set(BoxType type) {m_type=type};
  getOccupier() const {return m_ocupier;}
  setOccupier(Element* o) {m_ocupier=o;}
  print() { std::cout << "BoxType" << m_type ; m_ocupier->print(); }
 };

 class Maize{
	std::vector<std::vector<MaizeBox>> m_matrix;
 public:
	Maize() = delete;
    print() { 
	  for(auto& r : m_matrix){
		for(auto& e : r){
		   e.print();
	    }  
	  }
	}
	Maize(BoxType[][] config, int rows, int cols){
	    m_matrix.resize(rows); 
	    for(int i=0;i<rows;i++){
			std::vector<MaizeBox> mrows;
			m_matrix[i].resize(cols);
			for(int j=0;j<cols;j++){
			   m_matrix[i][j].set(config[[i][j]);
			}
		}
	}
}; 


enum class TEAM { A, B };

class Element{
int m_pos_row;
int m_pos_col;
 public:
 Element(int row, int col)m_pos_row(row),m_pos_col(col)
 void moveN(){--m_pos_col;}
 void moveS(){++m_pos_col;}
 void moveE(){++m_pos_row;}
 void moveW(){--m_pos_row;}
 int currentRow() {return m_pos_row;}  
 int currentCol() {return m_pos_row;}  
 virtual print(){ std::cout << "Row:" << m_pos_row << " Col:" << m_pos_col << ::std::endl;}
};

class Player: public Element{
TEAM m_team;
int m_id;
public:
Player(TEAM team, int id, int row, int col):Element(row, col),m_team(team),m_id(id){}
virtual print() override { std::cout << "Player:" << m_team << " ID:" << m_id << " ";  Element::print();}
int getPlayerID() {return m_id;}
};

class Treasure: public Element{
int m_value;
public:
Treasure(int value, int row, int col):Element(row, col),m_value(value){}
virtual print() override { std::cout << "Treasure:" << m_value ;  Element::print();}
};

class Friend: public Element{
int m_value;
public:
Friend(int value, int row, int col):Element(row, col),m_value(value){}
virtual print() override { std::cout << "Friend:" << m_value ;  Element::print();}
};

class Enemy: public Element{
int m_value;
public:
Enemy(int value, int row, int col):Element(row, col),m_value(value){}
virtual print() override { std::cout << "Enemy:" << m_value ;  Element::print();}
};

class Labyrinth {
	Maize m_Maize;
	std::map<int,Element> m_Players;
	std::map<int,Element> m_Players;
	Public:
	Labyrinth(int rows, int cols):m_Maize(rows, cols)
	// specifies the player's movement in one of the four directions;
    MoveEast(id int);
	MoveNorth(id int);
	MoveSouth(id int);
	MoveWest(id int) ; 
    show_location() {
	    m_Maize.print();
	} //- displays the contents of the location;
    fight(){ if } // - hits the opponent if he is in an adjacent location
    get_item(){} //(get_treasure) the player takes a friend (or treasure) who is in the same location;
    drop_item(){} //- the player leaves a friend;
    quit(){} // - the game ends forcibly;
    save(){} // - the game is saved (classes must contain a Save method);
    load(){} // - a previously saved game is loaded;
    help(){} //- displays game controls.
};
