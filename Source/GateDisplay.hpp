/*
 *  GateDisplay.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *
 */
#include "component.h"
#include "Inverter.hpp"
#include "AND.hpp"
#include "OR.hpp"

using namespace GLTYPES;

namespace Sewers
{
	class GateDisplay : public Component
		{
		public:
			// Mutators
			void hide_inverter() { _inverter.hide(); }
			void show_inverter() { _inverter.show(); }
			void hide_AND()      { _AND.hide(); }
			void show_AND()		 { _AND.show(); }
			void hide_OR()		 { _OR.hide(); }
			void show_OR()		 { _OR.show(); }
			// Accessors
			Inverter inverter() const { return _inverter; }
			AND And() const { return _AND; }
			OR Or() const { return _OR; }
			// Functions for GLUT
			void re_display(void);
		private:
			Inverter _inverter;
			AND _AND;
			OR _OR;
		};
}


