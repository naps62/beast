/*
 * options_description.hpp
 *
 *  Created on: Jan 1, 2013
 *      Author: naps62
 */

#ifndef __BEAST_PO_OPTIONS_HPP_
#define __BEAST_PO_OPTIONS_HPP_

#include <beast/common.hpp>

#include <string>
#include <utility> // pair<T>

#include <boost/program_options.hpp>
namespace bpo = boost::program_options;
using bpo::value;

namespace beast { namespace program_options {

	class options {

		bpo::options_description _options; ///< holds details of all options allowed by the program
		bpo::variables_map vm;            ///< value map of all the values parsed


	public:
		// Constructors
		options();
		options(const char* desc);

		/////////////////////////////
		// Adding options
		/////////////////////////////

		// Adds a flag
		// name should be a string like "level" or "level,l"
		// meaning that --help and -h will be used to identify this option
		options& flag(const char *name, bool& var, const char *desc = "");

		// Adds an options with the type being given by the template parameter
		//   options.add<int>("name", my_int, 2, "description")
		//
		// note that instead of an address, my_int is passed as a C++ reference
		template<class T> options& value(const char* name, T& addr, T default_value = T(), const char *desc = "");

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
		bpo::options_description help() const;

	private:
		// Initialization method
		// Adds the "help,h" option by default
		void _init();

		// Internal helper method to add a value option
		template<class T> options& _value(const char* name, bpo::value_semantic* semantic, const char *desc = NULL);

		// looks for a @filename option in the arguments
		static std::pair<std::string, std::string> file_option_parser(const std::string& s);

		// load an options file
		void load_options_file(const std::string& filename);
	};





	//
	// Template definitions
	//

	template<class T>
	T options::get(const char* name) const {
		return this->vm[name].as<T>();
	}


	template<class T>
	options& options::value(const char* name, T& addr, T default_value, const char *desc) {
		return this->_value<T>(name, bpo::value<T>(&addr)->default_value(default_value), desc);
	}

	template<class T>
	options& options::_value(const char* name, bpo::value_semantic* semantic, const char *desc) {
		this->_options.add_options() (name, semantic, desc);
		return *this;
	}
} }


#endif /* __BEAST_PO_OPTIONS_HPP_ */
