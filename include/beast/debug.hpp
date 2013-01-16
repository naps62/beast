/*
 * debug.hpp
 *
 *  Created on: Jan 15, 2013
 *      Author: naps62
 */

#ifndef _BEAST_DEBUG_HPP_
#define _BEAST_DEBUG_HPP_

#ifdef _Debug
	#define _debug true
	#define _if_dbg(x) x
#else
	#define _debug false
	#define _if_dbg(x)
#endif // _Debug






#endif // _BEAST_DEBUG_HPP_
