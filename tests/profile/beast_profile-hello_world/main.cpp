/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/time/timer.hpp>
using namespace std;
using beast::time::timer;

#include <beast/profile.hpp>

int main(int argc, char **argv) {

	_if_prof(
		timer t("my_timer");
		t.start();
		t.stop();
	)

	sleep(1);

	_if_prof(
		beast::profile::dumper dumper;
		dumper.add(t);
		dumper.dump();
	)


}
