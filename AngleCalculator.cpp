#define _USE_MATH_DEFINES // M_PI

#include "AngleCalculator.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

using namespace std;


map<string, OutputFormat> AngleCalculator::m_AllowableOutputFormats;
map<string, ClockType> AngleCalculator::m_AllowableClockTypes;


AngleCalculator::AngleCalculator() {
	m_Hours = 0;
	m_Minutes = 0;
	m_OutputFormat = DEG;
	m_ClockType = MECH;
	if( m_AllowableOutputFormats.size() == 0 ) {
		m_AllowableOutputFormats["rad"] = RAD;
		m_AllowableOutputFormats["deg"] = DEG;
		m_AllowableOutputFormats["dms"] = DMS;
		m_AllowableClockTypes["mech"] = MECH;
		m_AllowableClockTypes["quar"] = QUAR;
	}
}


void AngleCalculator::setTime( string time ) {

	toLowerCase( &time );

	if ( !boost::regex_match( time, boost::regex( "\\d{1,2}:\\d{2}\\s*(am|pm)?" ) ) ) {
		throw WRONG_TIME_FORMAT;
	}

	bool h12 = boost::regex_search( time, boost::regex( "am|pm" ) );
	int hours = atoi( time.substr( 0, time.find( ":" ) ).c_str() );
	int minutes = atoi( time.substr( time.find( ":" ) + 1, 2 ).c_str() );

	if( 23 < hours || 59 < minutes || ( 11 < hours && h12 ) ) {
		throw OUT_OF_TIME_BOUNDARY;
	}

	m_Hours = hours;
	m_Minutes = minutes;
}


void AngleCalculator::setOutputFormat( string fmt ) {

	OutputFormat oFmt = m_AllowableOutputFormats[ toLowerCase( &fmt ) ];

	if( oFmt == UNKNOWN_O_F ) throw WRONG_OUTPUT_FORMAT;

	m_OutputFormat = oFmt;
}


void AngleCalculator::setClockType( string type ) {

	ClockType cType = m_AllowableClockTypes[ toLowerCase( &type ) ];

	if( cType == UNKNOWN_C_T ) throw WRONG_CLOCK_TYPE;

	m_ClockType = cType;
}


float AngleCalculator::m_GetAngle() const {

	float hoursAngle = ( float )( ( m_Hours * 30 ) % 360 );

	if( m_ClockType == MECH ) {
		hoursAngle += m_Minutes * 0.5f;
	}

	float minutesAngle = ( float )( m_Minutes * 6 );
	float angleBtwArrows = abs( hoursAngle - minutesAngle );

	if( 180 < angleBtwArrows ) {
		angleBtwArrows = 360 - angleBtwArrows;
	}

	return angleBtwArrows;
}


string AngleCalculator::getFormattedAngle() const {

	float degAngle = m_GetAngle();											// 123.456 deg
	char formatBuffer[ 11 ];
	string formattedAngle;

	switch( m_OutputFormat ) {
		case DEG: {
			formattedAngle = boost::lexical_cast<string>( degAngle );
			break;
		}
		case RAD: {
			float radAngle = ( float )( degAngle * M_PI / 180 );			// 2.1547136813421 rad
			// radAngle = floor( radAngle * 10000 + 0.5f ) / 10000;			// 2.1547000000001 rad ;(
			float integralRad;												// 2.0 rad
			float fractionalRad = modf( radAngle, &integralRad );			// 0.1547136813421 rad
			fractionalRad = floor( fractionalRad * 10000 + 0.5f );			// (0.)1547 rad

			sprintf( formatBuffer, "%.0f.%.0f", integralRad, fractionalRad );
			formattedAngle = formatBuffer;
			break;
		}
		case DMS: {
			float integralDeg;												// 123.0 deg
			float fractionalDeg = modf( degAngle, &integralDeg );			// 0.456 deg
			float arcminAngle = fractionalDeg * 60;							// 27.36 arcmin
			float integralArcmin;											// 27.0  arcmin
			float fractionalArcmin = modf( arcminAngle, &integralArcmin );	// 0.36  arcmin
			float integralArcsec = floor( fractionalArcmin * 60 );			// 21.0  arcsec

			sprintf( formatBuffer, "%.0f.%02.f'%02.f\"", integralDeg, integralArcmin, integralArcsec );
			formattedAngle = formatBuffer;
			break;
		}
		default: {
			throw REQUIRE_OUTPUT_FORMAT;
		}

	}

	return formattedAngle;
}


string toLowerCase( string* str ) {
	boost::to_lower( *str );
	return *str;
}
