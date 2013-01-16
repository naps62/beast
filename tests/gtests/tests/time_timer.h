/*
 * time_timer.h
 *
 *  Created on: Jan 16, 2013
 *      Author: naps62
 */

#ifndef GTEST_TIME_TIMER_H_
#define GTEST_TIME_TIMER_H_

#include <beast/time/timer.hpp>
using beast::time::timer;

#include <unistd.h>


TEST(TimerName, DefaultName) {
	timer t;
	ASSERT_STREQ(t.name().c_str(), BEAST_TIMER_NAME);
}


TEST(TimerName, CustomName) {
	const string str("custom_name");
	timer t(str);
	ASSERT_STREQ(t.name().c_str(), str.c_str());
}


TEST(ElapsedTime, ZeroBeforeStart) {
	timer t("asd");
	ASSERT_EQ(0.0L, t.elapsed().ns());
}

TEST(ElapsedTime, NotZeroAfterStart) {
	timer t;
	t.start();
	ASSERT_GT(t.elapsed().ns(), 0.0L);
}

TEST(ElapsedTime, NotZeroAfterStop) {
	timer t;
	t.start();
	t.stop();
	ASSERT_GT(t.elapsed().ns(), 0.0L);
}

TEST(ElapsedTime, ConsecutiveElapsedBeforeStop) {
	timer t;
	t.start();
	double ns1 = t.elapsed().ns();
	usleep(100);
	double ns2 = t.elapsed().ns();
	ASSERT_GT(ns2, ns1);
}

TEST(ElapsedTime, ElapsedBeforeAndAfterStop) {
	timer t;
	t.start();
	double ns1 = t.elapsed().ns();
	t.stop();
	double ns2 = t.elapsed().ns();
	ASSERT_GT(ns2, ns1);
}

TEST(ElapsedTime, ConsecutiveElapsedAfterStop) {
	timer t;
	t.start();
	t.stop();
	double ns1 = t.elapsed().ns();
	double ns2 = t.elapsed().ns();
	ASSERT_EQ(ns2, ns1);
}


#endif // GTEST_TIME_TIMER_H_
