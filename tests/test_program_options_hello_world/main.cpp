/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/program_options.hpp>
using namespace std;

int main(int argc, char **argv) {
	int val_a, val_b;
	bool flag_1 = true, flag_2 = false;

	// add the options to the description
	beast::program_options ops;
	// the --help / -h flag is added by default

	// flags can be set like this:
	ops.flag("flag_1,f", flag_1, "optional description");
	ops.flag("flag_2",   flag_2);

	// or when values are also passed as arguments:
	ops.value("val_a,a", val_a, 0, "The value");
	ops.value("val_b,b", val_b);

	// now parse the arguments
	ops.parse(argc, argv);

	// flags can be fetched in these 2 ways:
	cout << "flag_1:" << ops.get_flag("flag_1") << endl;
	cout << "flag_2:" << flag_2                 << endl;
	// and values like this:
	cout << "val_a: " << ops.get<int>("val_a")  << endl;
	cout << "val_b: " << val_b                  << endl;

}
