//Mark Boady
//Drexel University 2021

//Tic-Tac-Toe Board

#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>

class board{
	private:
		char* spaces;
		int size = 9;
	public:
		//Constructor
		board();
		//Destructor
		~board();
		//Place Piece true is success, false if not allowed
		bool place(int loc, char sym);
		//Check Game Over
		bool gameOver() const;
		//Determine Winner
		char winner() const;
		//Get a location
		char get(int pos) const;
		//Get size
		int getSize() const;
};

//Overload the print command
std::ostream& operator<<(std::ostream& os, const board& b);

#endif
