/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/program_options.hpp>
using namespace std;

int main(int argc, const char **argv) {
	// this program receives two unsigned args
	unsigned one_val, other_val;

	// add the options to the description
	beast::program_options ops;
	// flags can be set like this:
	ops.add("flag,f", "Boolean value");
	// or when values are also passed as arguments:
	ops.add("one_val,a", po::value<unsigned>(&one_val)->default_value(0), "The value");
	// or for a simpler syntax:
	ops.add<unsigned>("other_val,b", other_val, 0, "The other value");

	// now parse the arguments
	ops.parse(argc, argv);

	// values can be fetched like this:
	cout << "flag:      " << ops.has("flag") << endl;
	cout << "one_val:   " << ops.get<unsigned>("one_val") << endl;
	// or they can be accessed directly, if a variable was provided
	cout << "other_val: " << other_val << endl;

}
