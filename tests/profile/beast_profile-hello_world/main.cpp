/**
 * This is a basic example usage of beast/program_options
 */

#include <iostream>
#include <beast/init.hpp>
#include <beast/time/timer.hpp>
using beast::time::timer;

#include <beast/profile.hpp>
#include <unistd.h>
#include <cstdio>

int main(int argc, char **argv) {
	beast::init();

	_if_prof(	timer t("my_timer");
				t.start();
				t.stop();
	)

	std::cout << "This does nothing in Profile mode\n" << std::endl;

	_if_prof(
		beast::profile::out << "asd" << "asd";
	)

	sleep(1);

	_if_prof(	beast::profile::dumper dumper;
				dumper.add(t);
				dumper.dump();)


}
