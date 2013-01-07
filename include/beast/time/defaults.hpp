/*
 * defaults.hpp
 *
 *  Created on: Jan 6, 2013
 *      Author: naps62
 */

#ifndef __BEAST_TIME_DEFAULTS_HPP_
#define __BEAST_TIME_DEFAULTS_HPP_

#define BEAST_TIMER_NAME "beast_timer"

#include <ctime>
#if defined(CLOCK_MONOTONIC_HR)
#define BEAST_TIMER_CLOCK_TYPE CLOCK_MONOTONIC_HR
#elif defined(CLOCK_MONOTONIC_RAW)
#define BEAST_TIMER_CLOCK_TYPE CLOCK_MONOTONIC_RAW
#else
#define BEAST_TIMER_CLOCK_TYPE CLOCK_MONOTONIC
#endif


#endif /* __BEAST_TIME_DEFAULTS_HPP_ */
