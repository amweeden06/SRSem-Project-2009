/*
 *  Room.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/2/09.
 *
 */
/*#include "Room.hpp"

namespace Sewers
{
	// Constructor
	Room::Room(int gate_quad, int num_inverters, int num_ands, int num_ors, int num_panels, int num_switches, int door_pos)
	{
		_gate_quadrant = gate_quad;
		_num_inverters = num_inverters;
		_inverter = new Inverter[num_inverters];
		_num_ands = num_ands;
		_and = new AND[num_ands];
		_num_ors = num_ors;
		_or = new OR[num_ors];
		_num_panels = num_panels;
		_panel = new Panel[num_panels];
		_num_switches = num_switches;
		_switch = new Switch[num_switches];
	}
	
	// Destructor
	Room::~Room()
	{
		delete [] _panel;
		delete [] _switch;
	}
	
	// Remap the player with bottom-left corner (left, bottom)
	void Room::setup_player(GLint left, GLint bottom)
	{
		_player.reMap(IntRect(left, bottom, left+15, bottom+30));
	}
	
	// Remap the index-th panel with bottom-left corner (left, bottom)
	void Room::setup_panel(int index, GLint left, GLint bottom)
	{
		_panel[index].reMap(IntRect(left, bottom, left+20, bottom+20));
	}
	
	// Remap the index-th switch with bottom-left corner (left, bottom)
	void Room::setup_switch(int index, bool val, GLint left, GLint bottom)
	{
		_switch[index].set(val);
		_switch[index].reMap(IntRect(left, bottom, left+20, bottom+20));
	}
	
	// Remap the door with bottom-left corner (left, bottom)
	void Room::setup_door(GLint left, GLint bottom)
	{
		if(_door_position == 3)
			_door.reMap(IntRect(left, bottom, left+20, bottom+60));
	}
	
	void Room::re_display(void)
	{
		// Initialize
		glClear(GL_COLOR_BUFFER_BIT);
		initDraw();
				
		// Draw walls
		for(int i = 0; i < 5; ++i)
			_wall[i].re_display();
		// Draw switches
		for(int i = 0; i < _num_switches; ++i)
			_switch[i].re_display();
		// Draw panels
		for(int i = 0; i < _num_panels; ++i)
			_panel[i].re_display();
		// Draw inverters
		// Draw AND gates
		// Draw OR gates
		// Draw player
		_player.re_display();
		// Draw door
		_door.re_display(); // Door has to be drawn on top of player to give illusion of walking through the door.
				
		// Flush the display
		glFlush();
	}
}*/