/*
 *  Sandbox.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 3/14/10.
 *  Copyright 2010 Earlham College. All rights reserved.
 *
 */
#include "Door.hpp"
#include "Avatar.hpp"
#include "HudButtons.hpp"

using namespace Sewers;

Avatar bitty("BITTY");
DrawingObject stats_button;
DrawingObject save_button;
DrawingObject load_button;
HudButtons hud_buttons;
DrawingObject hud_gate;
DrawingObject truth_table;

void move_bitty(string direction)
{
	bitty.set_direction(direction);
	bitty.set_animation_frame(!bitty.animation_frame());
		if(direction == "LEFT")
		{
			if(bitty.left() - MOVE_FACTOR >= 20)
			   bitty.set_left(bitty.left() - MOVE_FACTOR);
		}
		else if(direction == "RIGHT")
		{
			if(bitty.right() + MOVE_FACTOR <= 280)
				bitty.set_left(bitty.left() + MOVE_FACTOR);
		}
		else if(direction == "UP")
		{
			if(bitty.top() + MOVE_FACTOR <= 300)
				bitty.set_bottom(bitty.bottom() + MOVE_FACTOR);
		}
		else
		{
			if(bitty.bottom() - MOVE_FACTOR >= 20)
				bitty.set_bottom(bitty.bottom() - MOVE_FACTOR);
		}
}

void wrap_display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	bitty.draw();
	stats_button.draw();
	save_button.draw();
	load_button.draw();
	hud_gate.draw();
	hud_buttons.draw();
	truth_table.draw();
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
	y = WINDOW_HEIGHT - y - WINDOW_HEIGHT/2;
		
	if(inside(hud_buttons.quit_button(),x,y) && (state == GLUT_DOWN))
	   exit(0);
}

int main(int argc, char** argv)
{
	const GLint BUTTON_WIDTH = 30;
	const GLint BUTTON_HEIGHT = 30;
	const GLint GATE_WIDTH = 20;
	const GLint GATE_HEIGHT = 20;
	const GLint BIT_WIDTH = 10;
	const GLint BIT_HEIGHT = 10;
	const GLint MAX_NUM_GATE_INPUTS = 2;
	const GLint MAX_NUM_COLUMNS = MAX_NUM_GATE_INPUTS + 1;
	const GLint MAX_NUM_ROWS = pow(2.0,MAX_NUM_GATE_INPUTS);
	const GLint COLUMN_WIDTH = 2 * BIT_WIDTH;
	const GLint ROW_HEIGHT = 2 * BIT_HEIGHT;
	const GLint TRUTH_TABLE_WIDTH = MAX_NUM_COLUMNS * COLUMN_WIDTH;
	const GLint TRUTH_TABLE_HEIGHT = (MAX_NUM_ROWS + 1) * ROW_HEIGHT;
	const GLint NUM_BUTTONS = 4;
	const GLint HUD_BUTTONS_WIDTH = NUM_BUTTONS * BUTTON_WIDTH * 2;
	const GLint HUD_PUZZLE_WIDTH = 2 * GATE_WIDTH + 2 * TRUTH_TABLE_WIDTH;
	const GLint HUD_BUTTONS_HEIGHT = BUTTON_HEIGHT * 2;
	const GLint HUD_PUZZLE_HEIGHT = GATE_HEIGHT > TRUTH_TABLE_HEIGHT 
									 ? GATE_HEIGHT * 2
									 : TRUTH_TABLE_HEIGHT * 1.5;
	const GLint HUD_WIDTH = HUD_BUTTONS_WIDTH + HUD_PUZZLE_WIDTH;
	const GLint HUD_HEIGHT = HUD_PUZZLE_HEIGHT > HUD_BUTTONS_HEIGHT 
							  ? HUD_PUZZLE_HEIGHT
							  : HUD_BUTTONS_HEIGHT;
	const GLint WINDOW_WIDTH = HUD_WIDTH;
	const GLint WINDOW_HEIGHT = HUD_HEIGHT;
	
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Computer City:  Sewers");
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	bitty.set_left(20);
	bitty.set_width(15);
	bitty.set_bottom(20);
	bitty.set_height(30);
	
	stats_button.set_left(BUTTON_WIDTH/2);
	stats_button.set_bottom(BUTTON_HEIGHT/2);
	stats_button.set_width(BUTTON_WIDTH);
	stats_button.set_height(BUTTON_HEIGHT);
	
	save_button.set_left(stats_button.right() + BUTTON_WIDTH);
	save_button.set_bottom(BUTTON_HEIGHT/2);
	save_button.set_width(BUTTON_WIDTH);
	save_button.set_height(BUTTON_HEIGHT);

	load_button.set_left(save_button.right() + BUTTON_WIDTH);
	load_button.set_bottom(BUTTON_HEIGHT/2);
	load_button.set_width(BUTTON_WIDTH);
	load_button.set_height(BUTTON_HEIGHT);	
	
	DrawingObject quit_button;
	quit_button.set_left(load_button.right() + BUTTON_WIDTH);
	quit_button.set_bottom(BUTTON_HEIGHT/2);
	quit_button.set_width(BUTTON_WIDTH);
	quit_button.set_height(BUTTON_HEIGHT);
	
	hud_buttons.set_button(quit_button);
	
	hud_gate.set_left(HUD_BUTTONS_WIDTH + GATE_WIDTH);
	hud_gate.set_bottom(HUD_HEIGHT/2 - GATE_HEIGHT/2);
	hud_gate.set_width(GATE_WIDTH);
	hud_gate.set_height(GATE_HEIGHT);
		
	truth_table.set_left(hud_gate.right() + BUTTON_WIDTH/2 + TRUTH_TABLE_WIDTH/2);
	truth_table.set_bottom(TRUTH_TABLE_HEIGHT/4);
	truth_table.set_width(TRUTH_TABLE_WIDTH);
	truth_table.set_height(TRUTH_TABLE_HEIGHT);	
	
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	glutMouseFunc(wrap_mouse);
	glutMainLoop();
}