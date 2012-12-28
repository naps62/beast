/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/program_options.hpp>
using namespace std;

int main(int argc, char **argv) {
	int val_a, val_b;

	// add the options to the description
	beast::program_options ops;
	// flags can be set like this:
	ops.add("flag,f", "optional description");
	ops.add("other_flag");
	// or when values are also passed as arguments:
	ops.add("val_a,a", po::value<int>(&val_a)->default_value(0), "The value");
	// or for a simpler syntax:
	ops.add<int>("val_b,b", val_b, 0);

	// now parse the arguments
	ops.parse(argc, argv);

	// flags can be fetched like this:
	cout << "flag:  " << ops.has("flag") << endl;
	// and values like this:
	cout << "val_a: " << ops.get<int>("val_a") << endl;
	// or they can be accessed directly, if a variable was provided
	cout << "val_b: " << val_b << endl;

}
