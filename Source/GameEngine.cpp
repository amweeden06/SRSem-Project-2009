/*
 *  GameEngine.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 3/14/10.
 *  Copyright 2010 Earlham College. All rights reserved.
 *
 */
#include "Avatar.hpp"
#include "Hud.hpp"
#include "ManufacturersRoom.hpp"
#include "PuzzleRoom.hpp"
#include "Puzzle.hpp"

using namespace Sewers;

/* GLOBALS */
Room* Current_Room;
Avatar Bitty;
Hud HeadsUpDisplay;
ManufacturersRoom Manufacturers_Room;
PuzzleRoom Puzzle_Rooms[NUM_PUZZLES / PUZZLES_PER_ROOM];
Puzzle Current_Puzzle;

void move_bitty(string direction)
{
	Bitty.set_direction(direction);
	Bitty.set_animation_frame(!Bitty.animation_frame());
	Avatar _proposed_location = Bitty;
	
	if(direction == "LEFT")
	{
		_proposed_location.set_left(Bitty.left() - MOVE_FACTOR);
	}
	else if(direction == "RIGHT")
	{
		_proposed_location.set_left(Bitty.left() + MOVE_FACTOR);
	}
	else if(direction == "DOWN")
	{
		_proposed_location.set_bottom(Bitty.bottom() - MOVE_FACTOR);
	}
	else if(direction == "UP")
	{
		_proposed_location.set_bottom(Bitty.bottom() + MOVE_FACTOR);
	}
	
	GLint shoe_top_x_left = _proposed_location.left();
	GLint shoe_top_x_right = _proposed_location.right();
	GLint shoe_bottom_x_left = shoe_top_x_left;
	GLint shoe_bottom_x_right = shoe_top_x_right;
	GLint shoe_top_y = _proposed_location.bottom() + AVATAR_HEIGHT/6;
	GLint shoe_bottom_y = _proposed_location.bottom();
	
	if(((*Current_Room).left_neighbor() != NULL && 
		(*Current_Room).left_doorway().contains(shoe_top_x_left,shoe_top_y) &&
		(*Current_Room).left_doorway().contains(shoe_bottom_x_left,shoe_bottom_y )) ||
	   ((*Current_Room).right_neighbor() != NULL &&
		(*Current_Room).right_doorway().contains(shoe_top_x_right,shoe_top_y) &&
		(*Current_Room).right_doorway().contains(shoe_bottom_x_right,shoe_bottom_y)) ||
	   ((*Current_Room).bottom_neighbor() != NULL &&
		(*Current_Room).bottom_doorway().contains(_proposed_location.left(),_proposed_location.bottom()) &&
		(*Current_Room).bottom_doorway().contains(_proposed_location.right(),_proposed_location.bottom())) ||
	   ((*Current_Room).top_neighbor() != NULL &&
		(*Current_Room).top_doorway().contains(_proposed_location.left(),_proposed_location.top()) &&
		(*Current_Room).top_doorway().contains(_proposed_location.right(),_proposed_location.top())) ||
		((_proposed_location.left() > WALL_WIDTH) &&
		 (_proposed_location.right() < WINDOW_WIDTH - WALL_WIDTH) &&
		 (_proposed_location.bottom() > HUD_HEIGHT + WALL_HEIGHT) &&
		 (_proposed_location.top() < WINDOW_HEIGHT)))
		Bitty = _proposed_location;
}

void wrap_display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	HeadsUpDisplay.draw();
	(*Current_Room).draw();
	
	Bitty.draw(GLblue3);
	glFlush(); 
}

void wrap_key(unsigned char k, int x, int y) 
{
	y = WINDOW_HEIGHT - y*2;
	if(k == 'a')
		move_bitty("LEFT");
	else if(k == 'd')
		move_bitty("RIGHT");
	else if(k == 's')
		move_bitty("DOWN");
	else if(k == 'w')
		move_bitty("UP");
	
	if(Bitty.right() < 0)
	{
		Current_Room = (*Current_Room).left_neighbor();
		Bitty.set_left(WINDOW_WIDTH);
	}
	else if(Bitty.left() > WINDOW_WIDTH)
	{
		Current_Room = (*Current_Room).right_neighbor();
		Bitty.set_left(-AVATAR_WIDTH);
	}
	else if(Bitty.top() < HUD_HEIGHT)
	{
		Current_Room = (*Current_Room).bottom_neighbor();
		Bitty.set_bottom(WINDOW_HEIGHT);
	}
	else if(Bitty.bottom() > WINDOW_HEIGHT)
	{
		Current_Room = (*Current_Room).top_neighbor();
		Bitty.set_bottom(HUD_HEIGHT);
	}
	
	/*else if(k == 'f')
	 {
	 if(intersecting(bitty, lp.logician()))
	 {
	 cerr << lp.logician().dialogue() << endl;
	 }
	 else if(intersecting(bitty, lp.shapes(0)))
	 {
	 lp.flip_color(0);
	 }
	 else if(intersecting(bitty, lp.shapes(1)))
	 {
	 lp.flip_color(1);
	 }
	 else if(next_to(bitty, table) || next_to(bitty, table_logician))
	 {
	 bool table_correct = true;
	 int value;
	 // Print truth table
	 cerr << "TRUTH TABLE" << endl;
	 cerr << "A\tB\t(A)XOR(B)" << endl;
	 cerr << "0\t0\t";
	 cin.clear();
	 cin >> value;
	 if(value != 0)
	 table_correct = false;
	 cerr << "0\t1\t";
	 cin.clear();
	 cin >> value;
	 if(value != 1)
	 table_correct = false;
	 cerr << "1\t0\t";
	 cin.clear();
	 cin >> value;
	 if(value != 1)
	 table_correct = false;
	 cerr << "1\t1\t";
	 cin.clear();
	 cin >> value;
	 if(value != 0)
	 table_correct = false;
	 
	 if(table_correct)
	 cerr << "Table is correct!" << endl;
	 else
	 cerr << "Table incorrect." << endl;
	 }
	 }
	 
	 if((lp.shapes(0).color() == GLred3 || lp.shapes(1).color() == GLyellow3) &&
	 !(lp.shapes(0).color() == GLred3 && lp.shapes(1).color() == GLyellow3))
	 {
	 TF.set_type("T");
	 }
	 else
	 TF.set_type("F");
	 
	 lp.set_tf_letter(TF);*/
	wrap_display();
}

void wrap_mouse(int b, int state, int x, int y)
{
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Computer City:  Sewers");
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	
	Room first_room;
	Room puzzle_room_1;
	Room puzzle_room_2;
	
	Bitty.set_left(BLUEPRINT_SCREEN_WIDTH/2 - AVATAR_WIDTH/2);
	Bitty.set_bottom(HUD_HEIGHT + BLUEPRINT_SCREEN_WIDTH/2 - AVATAR_HEIGHT/2);
	Bitty.set_width(AVATAR_WIDTH);
	Bitty.set_height(AVATAR_HEIGHT);
	Bitty.set_direction("DOWN");
	
	Manufacturers_Room.set_bottom_neighbor(&first_room);
	
	first_room.set_right_neighbor(&puzzle_room_1);
	first_room.set_top_neighbor(&Manufacturers_Room);
	
	puzzle_room_1.set_left_neighbor(&first_room);
	puzzle_room_1.set_right_neighbor(&puzzle_room_2);
	
	puzzle_room_2.set_left_neighbor(&puzzle_room_1);
	
	Current_Room = &first_room;
		
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	glutMouseFunc(wrap_mouse);
	glutMainLoop();
}