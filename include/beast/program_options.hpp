/*
 * program_options.hpp
 *
 *  Created on: Dec 22, 2012
 *      Author: naps62
 *
 *  A class to allow easier usage of boost/program_options library
 */

#ifndef ARGS_HPP_
#define ARGS_HPP_

#include <beast/common.hpp>

#include <string>
#include <utility> // pair<>

#include <boost/program_options.hpp>
namespace po = boost::program_options;
using po::value;

namespace beast {

	class program_options {

		po::options_description options; ///< holds details of all options allowed by the program
		po::variables_map vm;            ///< value map of all the values parsed


	public:
		// Constructors
		program_options();
		program_options(const char* desc);

		/////////////////////////////
		// Adding options
		/////////////////////////////

		// Adds a flag
		// name should be a string like "level" or "level,l"
		// meaning that --help and -h will be used to identify this option
		program_options& flag(const char *name, bool& var, const char *desc = "");

		// Adds an options with the type being given by the template parameter
		//   options.add<int>("name", my_int, 2, "description")
		//
		// note that instead of an address, my_int is passed as a C++ reference
		template<class T> program_options& value(const char* name, T& addr, T default_value = T(), const char *desc = "");

		// This method should be called prior to reading any value
		void parse(int argc, char **argv);

		// Returns the amount of ocurrences for a given key
		int count(const char* name) const;

		// Indicates if a given key is present
		bool has(const char *name) const;


		// Gets the value of a flag
		bool get_flag(const char* name) const;

		// Gets the value of a given key
		template<class T> T get(const char* name) const;

		// Returns the help message (assumes option "help,h" exists)
		po::options_description help() const;

	private:
		// Initialization method
		// Adds the "help,h" option by default
		void _init();

		// Internal helper method to add a value option
		template<class T> program_options& _value(const char* name, po::value_semantic* semantic, const char *desc = NULL);

		// looks for a @filename option in the arguments
		static std::pair<std::string, std::string> file_option_parser(const std::string& s);

		// load an options file
		void load_options_file(const std::string& filename);
	};





	//
	// Template definitions
	//

	template<class T>
	T program_options::get(const char* name) const {
		return this->vm[name].as<T>();
	}


	template<class T>
	program_options& program_options::value(const char* name, T& addr, T default_value, const char *desc) {
		return this->_value<T>(name, po::value<T>(&addr)->default_value(default_value), desc);
	}

	template<class T>
	program_options& program_options::_value(const char* name, po::value_semantic* semantic, const char *desc) {
		this->options.add_options() (name, semantic, desc);
		return *this;
	}
}

#endif /* ARGS_HPP_ */
