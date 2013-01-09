/*
 * timer.hpp
 *
 *  Created on: Jan 6, 2013
 *      Author: naps62
 */

#ifndef _BEAST_TIMER_HPP_
#define _BEAST_TIMER_HPP_

#include <beast/common.hpp>
#include <beast/time/defaults.hpp>
#include <beast/time/time_val.hpp>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <numeric>
using std::accumulate;

#include <algorithm>
using std::nth_element;

#include <iostream>
using namespace std;

namespace beast { namespace time {

	class timer {

		const string _name;
		bool running;
		time_val _start;
		time_val _end;
		time_val _elapsed;
		vector<double> _history;


	public:

		timer()
		: _name(BEAST_TIMER_NAME), running(false)
		{
		}

		timer(const string& name)
		: _name(name), running(false)
		{
		}

		timer(const char* name)
		: _name(name), running(false)
		{
		}

		__beast_force_inline__
		void start() {
			running = true;
			gettime(_start);
		}

		__beast_force_inline__
		void stop() {
			if (running) {
				elapsed();
				running = false;
				_history.push_back(_elapsed.ns());
			}
		}

		__beast_force_inline__
		time_val elapsed() {
			if (running) {
				gettime(_end);
				_elapsed = _end - _start;
			}
			return _elapsed;
		}

		double average() {
			return accumulate(_history.begin(), _history.end(), 0.0) / _history.size();
		}

		double median() {
			int middle = _history.size() / 2;
			nth_element(_history.begin(), _history.begin()+middle, _history.end());
			return _history[middle];
		}

		__beast_force_inline__ string name() const { return _name; }
		__beast_force_inline__ double ns() const { return _elapsed.ns(); }
		__beast_force_inline__ double us() const { return _elapsed.us(); }
		__beast_force_inline__ double ms() const { return _elapsed.ms(); }
		__beast_force_inline__ double s () const { return _elapsed.s(); }

	private:

		__beast_force_inline__
		void gettime(timespec& t) {
			clock_gettime(BEAST_TIMER_CLOCK_TYPE, &t);
		}

	};

} }


#endif /* _BEAST_TIMER_HPP_ */
