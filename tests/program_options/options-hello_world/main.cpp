/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/program_options.hpp>
using namespace std;

struct Config : public beast::program_options::options {
	int val_a, val_b;
	bool flag_1, flag_2;

	Config(const char *desc, int argc, char **argv) : beast::program_options::options(desc) {
		// flags can be set like this:
		flag("flag_1,f", flag_1, "optional description");
		flag("flag_2",   flag_2);

		// or when values are also passed as arguments:
		value("val_a,a", val_a, 0, "The value");
		value("val_b,b", val_b);

		// now parse the arguments
		parse(argc, argv);
	}
};

int main(int argc, char **argv) {
	// add the options to the description
	Config ops("description", argc, argv);

	// flags can be fetched in these 2 ways:
	cout << "flag_1:" << ops.get_flag("flag_1") << endl;
	cout << "flag_2:" << ops.flag_2             << endl;
	// and values like this:
	cout << "val_a: " << ops.get<int>("val_a")  << endl;
	cout << "val_b: " << ops.val_b              << endl;

	// fetching via the ops.get methods will always give the original value accross the entire program

}
