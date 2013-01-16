/*
 * time_multi_timer.h
 *
 *  Created on: Jan 16, 2013
 *      Author: naps62
 */

#include <beast/time/multi_timer.hpp>
using beast::time::multi_timer;

#include <unistd.h>

TEST(Count, DefaultToZero) {
	multi_timer t;
	ASSERT_EQ(0, t.count());
}

TEST(Count, CorrectValue) {
	multi_timer t;
	t.start();
	t.stop();
	t.start();
	t.stop();
	ASSERT_EQ(2, t.count());
}
