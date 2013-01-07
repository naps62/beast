/*
 * option_var.hpp
 *
 *  Created on: Dec 31, 2012
 *      Author: naps62
 */

#ifndef _BEAST_PO_OPTION_VAR_HPP_
#define _BEAST_PO_OPTION_VAR_HPP_

#include <beast/program_options/defaults.hpp>
#include <beast/program_options/options.hpp>

namespace beast { namespace program_options {

extern options __beast_option_var_descriptions;

	template<class T>
	class option_var {

		const std::string name;
		T _var;

	public:

		option_var(const char* _name,      const char* desc = "");
		option_var(const char* _name, T t, const char* desc = "");

		T& operator() ();			// getter
		T& operator() (const T& val);	// setter

	private:

		void init(const char* desc);
	};

	void parse_option_vars(int argc, char **argv);


	template<class T>
	option_var<T>::option_var(const char* _name, const char* desc)
	: name(_name), _var() {
		init(desc);
	}


	template<class T>
	option_var<T>::option_var(const char* _name, T t, const char* desc)
	: name(_name), _var(t)
	{
		init(desc);
	}


	template<class T>
	T& option_var<T>::operator() () {
		return _var;
	}

	template<class T>
	T& option_var<T>::operator() (const T& val) {
		return _var;
	}

	template<class T>
	void option_var<T>::init(const char* desc) {
		__beast_option_var_descriptions.value<T>(this->name.c_str(), this->_var, this->_var, desc);
	}
} }

#endif /* _BEAST_PO_OPTION_VAR_HPP_ */
