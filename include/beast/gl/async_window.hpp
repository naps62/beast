/*
 * async_window.h
 *
 *  Created on: Feb 10, 2013
 *      Author: naps62
 */

#ifndef _BEAST_GL_ASYNC_WINDOW_HPP_
#define _BEAST_GL_ASYNC_WINDOW_HPP_

#include <boost/thread.hpp>

namespace beast { namespace gl {

	class async_window {

		// opengl calls need to be static. A handle to the current async_gl instance is required
		// currently assumes only one instance is used at a time
		static async_window* current_handle;


	public:
		async_window();

		void start();				// starts the window using a separate boost::thread
		void stop();				// triggers kill of the window thread
		void join();				// joins the current window thread
		void run();					// method run by the window thread

		// opengl public (overridable) callbacks
		void keyboard(unsigned char, int, int);
		void mouse(int, int, int, int);
		void special(int, int, int);
		void idle();
		void render();

	private:
		boost::thread thread;

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
