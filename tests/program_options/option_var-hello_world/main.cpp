/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/program_options.hpp>
using namespace std;
using namespace beast::program_options;

int main(int argc, char **argv) {


	option_var<bool> flag_1("flag_1,f", true, "A flag");
	option_var<bool> flag_2("flag_2",   true);
	option_var<int>  val_a("val_a,a", 0, "The value");
	option_var<int>  val_b("val_b,b", 2, "Another value");

	parse_option_vars(argc, argv);

	cout << "flag_1:" << flag_1() << endl;
	cout << "flag_2:" << flag_2() << endl;
	cout << "val_a: " << val_a()  << endl;
	cout << "val_b: " << val_b()  << endl;

	// fetching via the ops.get methods will always give the original value accross the entire program

}
