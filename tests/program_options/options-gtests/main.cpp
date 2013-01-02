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

	beast::program_options::options ops;
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

	beast::program_options::options ops;
	ops.flag("flag", flag, "description");
	ops.parse(argc, argv);

    EXPECT_TRUE(flag);
}

// flag should be false by default
TEST(SimpleFlag, SimpleFlagFalse) {
    char  arg0[] = "program_name";
    char* argv[] = { &arg0[0], NULL };
    int   argc = INIT_ARGC;

    bool flag = true;

	beast::program_options::options ops;
	ops.flag("flag", flag, "description");
	ops.parse(argc, argv);

    EXPECT_FALSE(flag);
}

// int variable value should have default value if not set
TEST(SimpleValue, DefaultValue) {
	char  arg0[] = "program_name";
	char* argv[] = { &arg0[0], NULL };
	int argc = INIT_ARGC;

	int val;

	beast::program_options::options ops;
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

	beast::program_options::options ops;
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

	beast::program_options::options ops;
	ops.value("val", val, 0.0f);
	ops.parse(argc, argv);

	EXPECT_EQ(62.62f, val);
}

// config file should load properly
TEST(ConfigFile, ConfigLoad) {
	char  arg0[] = "program_name";
	char  arg1[] = "--options-file";
	char  arg2[] = "../sample_options.cfg";
	char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };
	int argc = INIT_ARGC;

	bool flag = false;
	int val;

	beast::program_options::options ops;
	ops.flag("flag",   flag);
	ops.value("value", val);
	ops.parse(argc, argv);

	EXPECT_TRUE(flag);
	EXPECT_EQ(62, val);
}

// command line options should take precedence over config file
// also, @filename short version should work like the --options-file
TEST(ConfigFile, ConfigPrecedence) {
	char  arg0[] = "program_name";
	char  arg1[] = "@../sample_options.cfg";
	char  arg2[] = "--value";
	char  arg3[] = "1";
	char* argv[] = { &arg0[0], &arg1[0], &arg2[0], &arg3[0], NULL };
	int argc = INIT_ARGC;

	bool flag = false;
	int val;

	beast::program_options::options ops;
	ops.flag("flag",   flag);
	ops.value("value", val);
	ops.parse(argc, argv);

	EXPECT_TRUE(flag);
	EXPECT_EQ(1, val); // this should be the value from the cmd line, not the file
}


int main (int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
