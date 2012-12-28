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

#include <boost/program_options.hpp>
namespace po = boost::program_options;
using po::value;

namespace beast {

	class program_options {

		po::options_description options; ///< holds details of all options allowed by the program
		po::variables_map vm;            ///< value map of all the values parsed

	public:
		/**
		 * Constructors
		 */
		program_options();
		program_options(const char* desc);

		/////////////////////////////
		// Adding options
		/////////////////////////////

		/**
		 * Adds an option
		 * name should be a string like "help" or "help,h"
		 * meaning that --help and -h will be used to identify this option
		 */
		program_options& add(const char *name, const char *desc);

		/**
		 * Adds an option along with the semantic description of its value
		 * semantic can be po::value<> type holding the address where the parsed value should be saved
		 *   po::value<int>(&my_int)
		 *
		 * optionally a default value can be specified
		 *   po::value<int>(&my_int)->default_value(2)
		 *
		 * if no address is given, the value is still accessible via the get method
		 */
		program_options& add(const char *name, const po::value_semantic* semantic, const char *desc);

		/**
		 * Syntax sugar for the add method
		 * instead of:
		 *   options.add("name", po::value<int>(&my_int)->default_value(2), "description")
		 * this method can be used:
		 *   options.add<int>("name", my_int, 2, "description")
		 *
		 * note that instead of an address, my_int is passed as a C++ reference
		 */
		template<class T> program_options& add(const char* name, T& addr, T default_value, const char *desc);

		/**
		 * This method should be called prior to reading any value
		 */
		void parse(const int argc, const char **argv);

		/**
		 * Returns the amount of ocurrences for a given key
		 */
		int count(const char* name);

		/**
		 * Indicates if a given key is present
		 */
		bool has(const char *name);

		/**
		 * Gets the value of a given key
		 */
		template<class T> T get(const char* name);

		/**
		 * Returns the help message (assumes option "help,h" exists)
		 */
		po::options_description help() const;

	private:
		/**
		 * Initialization method
		 * Adds the "help,h" option by default
		 */
		void init();
	};

	template<class T>
	T program_options::get(const char* name) {
		return this->vm[name].as<T>();
	}

	template<class T>
	program_options& program_options::add(const char* name, T& addr, T default_value, const char *desc) {
		return this->add(name, po::value<T>(&addr)->default_value(default_value), desc);
	}
}




#endif /* ARGS_HPP_ */
