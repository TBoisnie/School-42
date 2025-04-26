#ifndef TIME_HPP
#define TIME_HPP

#include <sys/time.h> // gettimeofday

namespace tester
{

class Time
{
	// Type --------------------------------------------------------------------
public:
	typedef timeval             value_type;
	typedef unsigned long long  ms_type;
	typedef unsigned long long  us_type;

	// Attribute ---------------------------------------------------------------
private:
	value_type m_Time;

	// Constructor -------------------------------------------------------------
public:
	Time(
		value_type const & time
	)
		: m_Time( time )
	{
	}

	Time(
		Time const & other
	)
		: m_Time( other.m_Time )
	{
	}

	// Method ------------------------------------------------------------------
public:
	// Static --------------------------
	static Time
	Now()
	{
		timeval now;
		gettimeofday( &now, 0 );
		return Time(now);
	}

	// Arithmetic ----------------------
	static Time
	Difference(
		Time const & from,
		Time const & to
	)
	{
		return Time(to).Sub(from);
	}

	Time &
	Sub(
		Time const & timer
	)
	{
		timeval diff;
		timersub( &m_Time, &timer.m_Time, &diff );

		m_Time = diff;

		return *this;
	}

	// Convertion ----------------------
	us_type
	ToMicroSecond()
	{
		return ( m_Time.tv_sec * 1000000 + m_Time.tv_usec );
	}

}; // class Time

} // namespace tester

#endif
