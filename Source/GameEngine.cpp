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
}

void wrap_display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
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
	
	SwitchTest();
	BitTest();
	RowTest();
	TruthTableTest();
	
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	glutMouseFunc(wrap_mouse);
	glutMainLoop();
}