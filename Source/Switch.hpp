/*  Switch.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{		
	class Switch : public DrawingObject
	{
	public:
		static const int MAX_NUM_OUTPUTS = MAX_NUM_BLUEPRINT_CONNECTIONS;
		/* CONSTRUCTOR */
		Switch();
		/* ACCESSORS */
		int num_outputs() const;
		DrawingObject* outputs(int index) const;
		/* FUNCTIONS */
		int add_output(DrawingObject*);
        int draw() const;
	private:
		DrawingObject* _outputs[MAX_NUM_OUTPUTS];
    };
	
	/* A TESTING FUNCTION FOR THE SWITCH CLASS */
	static void SwitchTest()
	{
		Switch s;
		DrawingObject d;
		int i;

		for(i = 0; i < s.MAX_NUM_OUTPUTS; ++i)
		{
			if(s.num_outputs() != i)
			{
				cerr << "ERROR:  Switch should have had " << i << " outputs but instead had ";
				cerr << s.num_outputs() << "." << endl;
				exit(EXIT_FAILURE);
			}
		
			if(s.add_output(&d) == FULL_ARRAY)
			{
				cerr << "ERROR: Switch has " << s.num_outputs() << " outputs but it claims to have ";
				cerr << "a full array, but a full array is " << s.MAX_NUM_OUTPUTS << "." << endl;
				exit(EXIT_FAILURE);
			}
		}
		
		if(s.add_output(&d) != FULL_ARRAY)
		{
			cerr << "ERROR: Switch has " << s.num_outputs() << " outputs but it claims to have ";
			cerr << "a non-full array, but a full array is " << s.MAX_NUM_OUTPUTS << "." << endl;
			exit(EXIT_FAILURE);			
		}
	}
}