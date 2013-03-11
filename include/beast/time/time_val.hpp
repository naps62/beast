/*
 * time.hpp
 *
 *  Created on: Jan 6, 2013
 *      Author: naps62
 */

#ifndef _BEAST_TIME_VAL_HPP_
#define _BEAST_TIME_VAL_HPP_

#include <beast/common.hpp>

#include <ctime>

namespace beast { namespace time {

	struct time_val : public timespec {

		/*
		 * constructors
		 */

		// default constructor. sets value to 0
		time_val() {
			zero();
		}

		// constructor with initial time value (by pointer)
		time_val(const time_val* const t) {
			this->tv_sec  = t->tv_sec;
			this->tv_nsec = t->tv_nsec;
		}

		// constructor with initial time value (by reference)
		time_val(const time_val& t) {
			this->tv_sec  = t.tv_sec;
			this->tv_nsec = t.tv_nsec;
		}

		// resets the value to 0
		void zero() {
			tv_sec = tv_nsec = 0;
		}

		/*
		 * getters
		 */
		__beast_force_inline__ double ns() const { return tv_sec * 1e9 + tv_nsec; }
		__beast_force_inline__ double us() const { return ns() * 1e-3; }
		__beast_force_inline__ double ms() const { return ns() * 1e-6; }
		__beast_force_inline__ double s () const { return ns() * 1e-9; }

		/*
		 * operators
		 */
		const time_val& operator-= (const time_val& t) {
			if (t.tv_sec > tv_sec || (t.tv_sec == tv_sec && t.tv_nsec > tv_nsec)) {
				zero();
			} else {
				tv_sec -= t.tv_sec;
				tv_nsec -= t.tv_nsec;
				if (tv_nsec < 0) {
					--tv_nsec;
					tv_nsec += 1e9;
				}
			}
			return *this;
		}

		time_val operator- (const time_val& t) const {
			time_val result(*this);
			result -= t;
			return result;
		}

		const time_val& operator+= (const time_val& t) {
			tv_sec  += t.tv_sec;
			tv_nsec += t.tv_nsec;
			if (tv_nsec > 1e9) {
				++tv_sec;
				tv_nsec -= 1e9;
			}
			return *this;
		}

		const time_val operator+ (const time_val& t) {
			time_val result(*this);
			result += t;
			return result;
		}
	};

} }


#endif // _BEAST_TIME_VAL_HPP_
