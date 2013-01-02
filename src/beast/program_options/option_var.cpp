/*
 * option_var.cpp
 *
 *  Created on: Dec 31, 2012
 *      Author: naps62
 */

#include <beast/program_options/option_var.hpp>

namespace beast { namespace program_options {

	// global program_options description for the option_var types
	options __beast_option_var_descriptions;

	// template specialization for bool
	template<>
	option_var<bool>::option_var(const char* _name, bool t, const char* desc)
	: name(_name), _var(t)
	{
		__beast_option_var_descriptions.flag(this->name.c_str(), this->_var, desc);
	}

	// parse function
	void parse_option_vars(int argc, char **argv) {
		__beast_option_var_descriptions.parse(argc, argv);
	}

} }
