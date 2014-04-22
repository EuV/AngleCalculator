#include "AngleCalculator.h"
#include <iostream>

using namespace std;

int main( int argc, char* argv[] ) {
	try {
		if ( argc < 3 ) throw REQUIRE_ARGUMENTS;

		AngleCalculator aCalc;
		aCalc.setTime( argv[ TIME ] );
		aCalc.setOutputFormat( argv[ OUTPUT_FORMAT ] );
		if ( 4 <= argc ) aCalc.setClockType( argv[ CLOCK_TYPE ] );

		cout << aCalc.getFormattedAngle() << endl;

	} catch ( Exception ex ) {
		switch( ex ) {
			case REQUIRE_ARGUMENTS:
				cout << "Usage: AngleCalculator <time> <format> [<type>]" << endl;
				break;
			case WRONG_TIME_FORMAT:
				cout << "Required time format: 'HH:MM' (24 h.) or 'HH:MM AM/PM' (12 h.)" << endl;
				break;
			case OUT_OF_TIME_BOUNDARY:
				cout << "Required boundaries for hours: 0-23 (0-11 if AM/PM is set); minutes: 0-59" << endl;
				break;
			case WRONG_OUTPUT_FORMAT:
				cout << "Required output format: 'rad', 'deg' or 'dms'" << endl;
				break;
			case WRONG_CLOCK_TYPE:
				cout << "Allowable clock types: 'mech', 'quar' ('mech' by default)" << endl;
				break;
			case REQUIRE_OUTPUT_FORMAT:
				cout << "Specify an output format before invoking getFormattedAngle()" << endl;
				break;
			default:
				cout << "An unknown exception has occurred" << endl;
				break;
		}
	}
	return 0;
}
