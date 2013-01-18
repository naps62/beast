/*
 * profile.hpp
 *
 *  Created on: Jan 12, 2013
 *      Author: naps62
 */

#ifndef _BEAST_PROF_HPP_
#define _BEAST_PROF_HPP_

#include <unistd.h>
#include <iostream>
#include <fstream>

#ifdef _Profile
	#define _profile        true
	#define _if_prof(x)     x
	#define _if_not_prof(x)
#else
	#define _profile        false
	#define _if_prof(x)
	#define _if_not_prof(x) x
#endif // _Profile

namespace beast { namespace profile {
	extern int __out_fd;
	extern int __null_fd;

	struct __out_class : public std::ofstream {
			template<class T>
			__out_class& operator << (const T& obj) {
				dup2(profile::__out_fd,  fileno(stdout)); // re-enable stdout
				std::cout << obj;
				std::cout.flush();
				dup2(profile::__null_fd, fileno(stdout));  // disable stdout again
				return *this;
			}
		};

	extern __out_class out;
} }

#include <beast/profile/defaults.hpp>
#include <beast/profile/dumper.hpp>

#endif // _BEAST_PROF_HPP_
