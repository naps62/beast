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

// --help should exist by default
TEST(ProgramOptions, HelpFlag) {
    char  arg0[] = "program_name";
    char  arg1[] = "--help";
    char* argv[] = { &arg0[0], &arg1[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.parse(argc, argv);

    EXPECT_EQ(1, ops.has("help"));
}

// -h should be the same as --help
TEST(ProgramOptions, ShortHelpFlag) {
    char  arg0[] = "program_name";
    char  arg1[] = "-h";
    char* argv[] = { &arg0[0], &arg1[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.parse(argc, argv);

    EXPECT_EQ(1, ops.has("help"));
}

// --flag shoud make has("flag") true
TEST(SimpleFlag, SimpleFlagTrue) {
    char  arg0[] = "program_name";
    char  arg1[] = "--flag";
    char* argv[] = { &arg0[0], &arg1[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.add("flag", "description");
	ops.parse(argc, argv);

    EXPECT_EQ(1, ops.has("flag"));
}

// has("flag") should be false by default
TEST(SimpleFlag, SimpleFlagFalse) {
    char  arg0[] = "program_name";
    char* argv[] = { &arg0[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.add("flag", "description");
	ops.parse(argc, argv);

    EXPECT_EQ(0, ops.has("flag"));
}

// has("flag") should be true by default if specified
TEST(SimpleFlag, SimpleFlagTrueByeDefault) {
    char  arg0[] = "program_name";
    char* argv[] = { &arg0[0], NULL };
    int   argc = INIT_ARGC;

	beast::program_options ops;
	ops.add<int>("flag", 1, "description");
	ops.parse(argc, argv);

    EXPECT_EQ(1, ops.get<int>("flag"));
}


int main (int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
