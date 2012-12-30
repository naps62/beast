/*
 * program_options.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: naps62
 */

#include <beast/program_options.hpp>
#include <iostream>

namespace beast {

	/**
	 * Constructors
	 */
	program_options::program_options()
	: options(BEAST_PROGRAM_OPTIONS_DESC)
	{
		_init();
	}

	program_options::program_options(const char* desc)
	: options(desc)
	{
		_init();
	}

	/**
	 * Add methods
	 */
	program_options& program_options::flag(const char* name, bool& var, const char* desc) {
		this->options.add_options() (name, po::bool_switch(&var), desc);
		return *this;
	}

	/**
	 *
	 */
	void program_options::parse(int argc, char **argv) {
		po::store(po::parse_command_line(argc, argv, this->options), this->vm);
		po::notify(vm);
		if (this->count("help")) {
			std::cout << this->help();
			exit(0);
		}
	}

	/**
	 * Getters
	 */
	bool program_options::get_flag(const char* name) const {
		return this->get<bool>(name);
	}

	int program_options::count(const char* name) const {
		return this->vm.count(name);
	}

	bool program_options::has(const char* name) const {
		return this->count(name) > 0;
	}

	po::options_description program_options::help() const {
		return this->options;
	}

	void program_options::_init() {
		this->options.add_options() (BEAST_PROGRAM_OPTIONS_HELP_OP, BEAST_PROGRAM_OPTIONS_HELP_DESC);
	}

}
