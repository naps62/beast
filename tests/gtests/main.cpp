/*
 * main.cpp
 *
 *  Created on: Dec 28, 2012
 *      Author: naps62
 */

#include <gtest/gtest.h>

#include "tests/po_options.h"
#include "tests/time_timer.h"
#include "tests/time_multi_timer.h"

int main (int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

