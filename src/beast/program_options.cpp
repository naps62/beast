/*
 * program_options.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: naps62
 */

#include <beast/program_options.hpp>
#include <iostream>

namespace beast {

	program_options::program_options()
	: options(BEAST_PROGRAM_OPTIONS_DESC)
	{
		init();
	}

	program_options::program_options(const char* desc)
	: options(desc)
	{
		init();
	}

	program_options& program_options::add(const char* name, const char* desc) {
		this->options.add_options() (name, desc);
		return *this;
	}

	program_options& program_options::add(const char *name, const po::value_semantic* semantic, const char *desc) {
		this->options.add_options() (name, semantic, desc);
		return *this;
	}

	void program_options::parse(int argc, char **argv) {
		po::store(po::parse_command_line(argc, argv, this->options), this->vm);
		po::notify(vm);
		if (this->has(BEAST_PROGRAM_OPTIONS_HELP_OP_LONG)) {
			std::cout << this->help();
			exit(0);
		}
	}

	int program_options::count(const char* name) {
		return this->vm.count(name);
	}

	bool program_options::has(const char* name) {
		return this->count(name) > 0;
	}

	po::options_description program_options::help() const {
		return this->options;
	}

	void program_options::init() {
		this->add(BEAST_PROGRAM_OPTIONS_HELP_OP, BEAST_PROGRAM_OPTIONS_HELP_DESC);
	}

}
