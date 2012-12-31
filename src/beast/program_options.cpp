/*
 * program_options.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: naps62
 */

#include <beast/program_options.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::pair;
using std::make_pair;
using std::ifstream;
using std::vector;

#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>

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
		po::store(
				po::command_line_parser(argc, argv)                   // command line options
				   .options(this->options)                            // option definitions
				   .extra_parser(program_options::file_option_parser) // look for @filename argument
				   .run()
				, this->vm);

		po::notify(this->vm);

		// check for options-file
		if (vm.count(BEAST_PROGRAM_OPTIONS_OP_FILE)) {
			this->load_options_file(vm[BEAST_PROGRAM_OPTIONS_OP_FILE].as<string>());
		}

		// deal with help options
		if (this->count("help")) {
			cout << this->help();
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
		this->options.add_options()
			(BEAST_PROGRAM_OPTIONS_HELP_OP, BEAST_PROGRAM_OPTIONS_HELP_DESC)
			(BEAST_PROGRAM_OPTIONS_OP_FILE, po::value<string>(), BEAST_PROGRAM_OPTIONS_OP_FILE_DESC);
	}

	pair<string, string> program_options::file_option_parser(const string& s) {
		if (s[0] == '@')
			return make_pair(string(BEAST_PROGRAM_OPTIONS_OP_FILE), s.substr(1));
		else
			return pair<string, string>();
	}

	void program_options::load_options_file(const string& filename) {
		// Load the file and tokenize it
		ifstream ifs(filename.c_str());
		if (!ifs) {
			cerr << filename << ": " << BEAST_PROGRAM_OPTIONS_ERROR_OP_FILE << endl;
			exit(1);
		}
		po::store(po::parse_config_file(ifs, this->options), this->vm);
		ifs.close();
		po::notify(this->vm);
	}

}
