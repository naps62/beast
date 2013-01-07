/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/time/timer.hpp>
using namespace std;
using beast::time::timer;

int main(int argc, char **argv) {

	timer t("my_timer");
	t.start();
	t.stop();
	cout << t.name << ": " << t.ns() << "ns ";
}
