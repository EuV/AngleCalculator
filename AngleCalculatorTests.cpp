#define BOOST_TEST_MODULE AngleCalculatorTest
#include <boost/test/unit_test.hpp>
#include "AngleCalculator.h"

struct F {
	AngleCalculator aCalc;
};

BOOST_FIXTURE_TEST_SUITE( s, F )

bool is_WRONG_TIME_FORMAT( Exception const& ex ) { return ex == WRONG_TIME_FORMAT; }
bool is_OUT_OF_TIME_BOUNDARY( Exception const& ex ) { return ex == OUT_OF_TIME_BOUNDARY; }
bool is_WRONG_OUTPUT_FORMAT( Exception const& ex ) { return ex == WRONG_OUTPUT_FORMAT; }
bool is_WRONG_CLOCK_TYPE( Exception const& ex ) { return ex == WRONG_CLOCK_TYPE; }



BOOST_AUTO_TEST_CASE( testSetTime ) {
	BOOST_CHECK_NO_THROW( aCalc.setTime( "00:00" ) );
	BOOST_CHECK_NO_THROW( aCalc.setTime( "23:59" ) );
	BOOST_CHECK_NO_THROW( aCalc.setTime( "0:00pm" ) );
	BOOST_CHECK_NO_THROW( aCalc.setTime( "11:59 AM" ) );

	BOOST_CHECK_EXCEPTION( aCalc.setTime( "11.30" ), Exception, is_WRONG_TIME_FORMAT );
	BOOST_CHECK_EXCEPTION( aCalc.setTime( "22:123" ), Exception, is_WRONG_TIME_FORMAT );
	BOOST_CHECK_EXCEPTION( aCalc.setTime( "123:22" ), Exception, is_WRONG_TIME_FORMAT );

	BOOST_CHECK_EXCEPTION( aCalc.setTime( "24:00" ), Exception, is_OUT_OF_TIME_BOUNDARY );
	BOOST_CHECK_EXCEPTION( aCalc.setTime( "17:60" ), Exception, is_OUT_OF_TIME_BOUNDARY );
	BOOST_CHECK_EXCEPTION( aCalc.setTime( "12:00 AM" ), Exception, is_OUT_OF_TIME_BOUNDARY );
}



BOOST_AUTO_TEST_CASE( testSetOutputFormat ) {
	BOOST_CHECK_NO_THROW( aCalc.setOutputFormat( "rad" ) );
	BOOST_CHECK_NO_THROW( aCalc.setOutputFormat( "deg" ) );
	BOOST_CHECK_NO_THROW( aCalc.setOutputFormat( "dms" ) );

	BOOST_CHECK_EXCEPTION( aCalc.setOutputFormat( "" ), Exception, is_WRONG_OUTPUT_FORMAT );
	BOOST_CHECK_EXCEPTION( aCalc.setOutputFormat( "grad" ), Exception, is_WRONG_OUTPUT_FORMAT );
}



BOOST_AUTO_TEST_CASE( testSetClockType ) {
	BOOST_CHECK_NO_THROW( aCalc.setClockType( "mech" ) );
	BOOST_CHECK_NO_THROW( aCalc.setClockType( "quar" ) );

	BOOST_CHECK_EXCEPTION( aCalc.setClockType( "" ), Exception, is_WRONG_CLOCK_TYPE );
	BOOST_CHECK_EXCEPTION( aCalc.setClockType( "Zenith" ), Exception, is_WRONG_CLOCK_TYPE );
}



BOOST_AUTO_TEST_CASE( testGetFormattedAngle ) {

	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "0" );

	aCalc.setOutputFormat( "rad" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "0.0" );

	aCalc.setOutputFormat( "dms" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "0.00'00\"" );

	aCalc.setTime( "03:00" );
	aCalc.setOutputFormat( "deg" );
	aCalc.setClockType( "mech" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "90" );

	aCalc.setTime( "15:00" );
	aCalc.setOutputFormat( "rad" );
	aCalc.setClockType( "mech" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "1.5708" );

	aCalc.setTime( "09:00 PM" );
	aCalc.setOutputFormat( "dms" );
	aCalc.setClockType( "quar" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "90.00'00\"" );

	aCalc.setTime( "12:31" );

	aCalc.setOutputFormat( "deg" );
	aCalc.setClockType( "mech" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "170.5" );

	aCalc.setOutputFormat( "rad" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "2.9758" );

	aCalc.setOutputFormat( "dms" );
	BOOST_CHECK_EQUAL( aCalc.getFormattedAngle(), "170.30'00\"" );

	aCalc.setOutputFormat( "deg" );
	aCalc.setClockType( "quar" );
	std::string t1 = aCalc.getFormattedAngle();
	aCalc.setTime( "12:29" );
	std::string t2 = aCalc.getFormattedAngle();
	BOOST_CHECK_EQUAL( t1, t2 );
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_CASE( testToLowerCase ) {
	std::string str = "QWERTY";
	toLowerCase( &str );
	BOOST_CHECK_EQUAL( str, "qwerty" );

	str = "A b C d";
	BOOST_CHECK_EQUAL( toLowerCase( &str ), "a b c d" );
}
