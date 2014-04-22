#include <string>
#include <map>

enum CommandLineArg {
	TIME = 1,
	OUTPUT_FORMAT = 2,
	CLOCK_TYPE = 3
};

enum OutputFormat {
	UNKNOWN_O_F = 0,
	RAD,
	DEG,
	DMS
};

enum ClockType {
	UNKNOWN_C_T = 0,
	MECH,
	QUAR
};

enum Exception {
	REQUIRE_ARGUMENTS,
	WRONG_TIME_FORMAT,
	OUT_OF_TIME_BOUNDARY,
	WRONG_OUTPUT_FORMAT,
	WRONG_CLOCK_TYPE,
	REQUIRE_OUTPUT_FORMAT
};

std::string toLowerCase( std::string* );

class AngleCalculator {
	int m_Hours;
	int m_Minutes;
	OutputFormat m_OutputFormat;
	ClockType m_ClockType;
	float m_GetAngle() const;
public:
	AngleCalculator();
	void setTime( std::string );
	void setOutputFormat( std::string );
	void setClockType( std::string );
	std::string getFormattedAngle() const;
private:
	static std::map<std::string, OutputFormat> m_AllowableOutputFormats;
	static std::map<std::string, ClockType> m_AllowableClockTypes;
};
