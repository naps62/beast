/*
 * async_window.h
 *
 *  Created on: Feb 10, 2013
 *      Author: naps62
 */

#ifndef _BEAST_GL_ASYNC_WINDOW_HPP_
#define _BEAST_GL_ASYNC_WINDOW_HPP_

#include <beast/common.hpp>

#include <boost/thread.hpp>
#include <string>
using std::string;

namespace beast { namespace gl {

	class async_window {

		// opengl calls need to be static. A handle to the current async_gl instance is required
		// currently assumes only one instance is used at a time
		static async_window* current_handle;


	public:
		async_window(const string _name, const uint _w, const uint _h);

		void start();				// starts the window using a separate boost::thread
		void stop();				// triggers kill of the window thread
		void join();				// joins the current window thread
		void run();					// method run by the window thread

		// opengl public (overridable) callbacks
		virtual void keyboard(uchar, int, int);
		virtual void mouse(int, int, int, int);
		virtual void special(int, int, int);
		virtual void idle();
		virtual void render();

	private:
		boost::thread thread;
		const string name;
		const int w, h;

		void gl_init();			// initializes opengl stuff

		// opengl private callbacks
		static void _keyboard(unsigned char, int, int);
		static void _mouse(int, int, int, int);
		static void _special(int, int, int);
		static void _idle();
		static void _render();
	};

} }


#endif /* _BEAST_GL_ASYNC_WINDOW_HPP_ */
