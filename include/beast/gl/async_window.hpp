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

	/*
	 * OpenGL window manager running asynchronously on a dedicated thread
	 * assumes there is only one OpenGL instance running
	 */
	class async_window {

		// opengl calls need to be static. A handle to the current async_gl instance is required
		// currently assumes only one instance is used at a time
		static async_window* current_handle;


	public:
		// constructor
		async_window(
				const string _name,		// window name
				const uint _width,		// window width
				const uint _height);	// window height

		// destructor
		virtual ~async_window();

		void start();	// starts the window using a dedicated thread
		void stop();	// triggers kill of the window thread
		void join();	// joins the current window thread
		void run();		// method run by the window thread

		/*
		 * opengl public (overridable) callbacks
		 * override these methods to add functionality to each event
		 */
		virtual void keyboard(uchar, int, int);
		virtual void mouse(int, int, int, int);
		virtual void special(int, int, int);
		virtual void idle();
		virtual void render();

	private:
		boost::thread thread;	// window thread
		const string name;		// window name
		const int width;		// window width
		const int height;		// window height

		// initializes opengl stuff
		void gl_init();

		/*
		 * opengl private callbacks
		 */
		static void _keyboard(unsigned char, int, int);	// keyboard events
		static void _mouse(int, int, int, int);			// mouse events
		static void _special(int, int, int);			// keyboard special functions
		static void _idle();							// idle
		static void _render();							// render
	};

} }


#endif // _BEAST_GL_ASYNC_WINDOW_HPP_
