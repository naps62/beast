/*
 * profile.hpp
 *
 *  Created on: Jan 12, 2013
 *      Author: naps62
 */

#ifndef _BEAST_PROF_HPP_
#define _BEAST_PROF_HPP_

#ifdef _Profile
	#define _profile true
	#define _if_prof(x) x
#else
	#define _profile false
	#define _if_prof(x)
#endif // _Profile





#include <beast/profile/defaults.hpp>
#include <beast/profile/dumper.hpp>

#endif // _BEAST_PROF_HPP_
