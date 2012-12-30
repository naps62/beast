/*
 * main.cpp
 *
 *  Created on: Dec 28, 2012
 *      Author: naps62
 */

#include <beast/program_options.hpp>
#include <gtest/gtest.h>

#define INIT_ARGC ((int)(sizeof(argv) / sizeof(argv[0])) - 1)

TEST(ProgramOptions, NoArguments) {
    char  arg0[] = "program_name";
    char* argv[] = { &arg0[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.parse(argc, argv);

	EXPECT_EQ(0, ops.has("random_name"));
}

// --flag shoud make flag true
TEST(SimpleFlag, SimpleFlagTrue) {
    char  arg0[] = "program_name";
    char  arg1[] = "--flag";
    char* argv[] = { &arg0[0], &arg1[0], NULL };
    int   argc = INIT_ARGC;

    bool flag = false;

	beast::program_options ops;
	ops.flag("flag", flag, "description");
	ops.parse(argc, argv);

    EXPECT_EQ(true, flag);
}

// flag should be false by default
TEST(SimpleFlag, SimpleFlagFalse) {
    char  arg0[] = "program_name";
    char* argv[] = { &arg0[0], NULL };
    int   argc = INIT_ARGC;

    bool flag = true;

	beast::program_options ops;
	ops.flag("flag", flag, "description");
	ops.parse(argc, argv);

    EXPECT_EQ(false, flag);
}

// int variable value should have default value if not set
TEST(SimpleValue, DefaultValue) {
	char  arg0[] = "program_name";
	char* argv[] = { &arg0[0], NULL };
	int argc = INIT_ARGC;

	int val;

	beast::program_options ops;
	ops.value("val", val, 62);
	ops.parse(argc, argv);

	EXPECT_EQ(62, val);
}

// int variable value should have the given value
TEST(SimpleValue, GivenValue) {
	char  arg0[] = "program_name";
	char  arg1[] = "--val";
	char  arg2[] = "62";
	char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };
	int argc = INIT_ARGC;

	int val;

	beast::program_options ops;
	ops.value("val", val, 0);
	ops.parse(argc, argv);

	EXPECT_EQ(62, val);
}

// float variable should also work
TEST(SimpleValue, GivenFloatValue) {
	char  arg0[] = "program_name";
	char  arg1[] = "--val";
	char  arg2[] = "62.62";
	char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };
	int argc = INIT_ARGC;

	float val;

	beast::program_options ops;
	ops.value("val", val, 0.0f);
	ops.parse(argc, argv);

	EXPECT_EQ(62.62f, val);
}


int main (int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
