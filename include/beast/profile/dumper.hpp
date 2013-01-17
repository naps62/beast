/*
 * profiler.hpp
 *
 *  Created on: Jan 12, 2013
 *      Author: naps62
 */

#ifndef _BEAST_PROF_DUMPER_HPP_
#define _BEAST_PROF_DUMPER_HPP_

#include <beast/profile.hpp>

#include <beast/time/timer.hpp>
using beast::time::timer;

#include <vector>
#include <map>
#include <string>
#include <sstream>

using std::vector;
using std::map;
using std::string;
using std::stringstream;

namespace beast { namespace profile {

	class dumper {

		// key-value pair containing counter name and value
		map<const string, const string> data;

	public:

		template<class T>
		void add(const T& obj);

		void dump() const;
	};

	template<class T>
	void dumper::add(const T& obj) {
		#ifdef _Profile
			const stringstream name(obj.name());
			const stringstream value(obj.value());
			data.insert(make_pair(name.str(), value.str()));
		#endif
	}

} }

#endif /* _BEAST_PROF_DUMPER_HPP_ */
