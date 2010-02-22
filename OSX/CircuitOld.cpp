/*
 *  Circuit.cpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  A circuit object, which contains objects and the wires that connect them
 *
 */
/*#include "CircuitOld.hpp"

namespace SewersOld
{
	Circuit::Circuit()
	{
	}
	
	// Changes the charge of the circuit's switch
	void Circuit::set_switch_charge(int charge)
	{
		update(0,charge);
	}
	
	// 1's inverse is 0, and vice versa
	int Circuit::invert_charge(int charge)
	{
		bool output_charge = -1;
		if(charge == 0)
			output_charge = 1;
		else if(charge == 1)
			output_charge = 0;
		return output_charge;
	}
	
	int Circuit::andify_charge(int charge)
	{
		return charge;
	}
	
	void Circuit::draw()
	{
		for(size_t i = 0; i < _objects.size(); ++i)
			_objects[i].draw();
	}
	
	// Add wires to connect object 1 to object 2
	void Circuit::connect(SewersObject obj1, SewersObject obj2)
	{
		if(obj1.top() == obj2.top())
		{
			_objects.push_back(SewersObject("WIRE",obj1.right(),
										  obj2.left(),
										  obj1.bottom() + obj1.height()/2,
										  obj1.bottom() + obj1.height()/2, obj1.int1(), false));
		}
		else
		{
			_objects.push_back(SewersObject("WIRE",obj1.right(),
											(obj1.right() + obj2.left())/2,
											obj1.bottom() + obj1.height()/2,
											obj1.bottom() + obj1.height()/2, obj1.int1(), false));
			_objects.push_back(SewersObject("WIRE",(obj1.right() + obj2.left())/2,
											(obj1.right() + obj2.left())/2,
											obj2.bottom() + obj2.height()/2,
											obj1.bottom() + obj1.height()/2, obj1.int1(), false));
			_objects.push_back(SewersObject("WIRE",(obj1.right() + obj2.left())/2,
											obj2.left(),
											obj2.bottom() + obj2.height()/2,
											obj2.bottom() + obj2.height()/2, obj1.int1(), false));
		}		
	}
	
	// If the object is a door, adds the switch to the circuit
	//  otherwise, adds the object with a wire connecting the last object
	//  in the circuit
	void Circuit::add_object(SewersObject obj)
	{
		if(obj.id() != "DOOR")
		{
			if(obj.id() == "NOT")
			{
				obj.set_int(invert_charge(last_obj().int1()));
			}
			else if(obj.id() == "DOOR")
			{
				if(last_obj().int1() == 1)
					obj.set_bool(OPEN);
				else
					obj.set_bool(CLOSED);
			}
			connect(last_obj(),obj);
		}
		_objects.push_back(obj);
	}
	
	// Change the value of the object at pos to charge, and update the rest
	//  of the circuit appropriately
	void Circuit::update(size_t pos, int charge)
	{
		_objects[pos].set_int(charge);
		for(size_t i = pos+1; i < _objects.size(); ++i)
		{
			if(_objects[i].id() == "WIRE")
			{
				_objects[i].set_int(charge);
			}
			else if(_objects[i].id() == "NOT")
			{
				charge = invert_charge(charge);
			}
			else if(_objects[i].id() == "AND")
			{
				charge = andify_charge(charge);
			}
			else if(_objects[i].id() == "DOOR")
			{
				if(charge == 1)
				{
					_objects[i].set_bool(OPEN);
				}
				else
					_objects[i].set_bool(CLOSED);
			}
		}
	}
}*/