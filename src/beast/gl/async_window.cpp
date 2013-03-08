#include <beast/gl/async_window.hpp>
#include <boost/date_time.hpp>
using namespace std;

#include<GL/freeglut.h>

namespace beast { namespace gl {

	// handle for current opengl thread
	async_window* async_window::current_handle;

	// constructor
	async_window :: async_window() {
	}

	// start the display thread
	void async_window :: start() {
		thread = boost::thread(&async_window::run, this);
	}

	// terminate the display thread
	void async_window :: stop() {
		glutLeaveMainLoop();
	}

	// wait for it to end
	void async_window :: join() {
		thread.join();
	}

	// display thread main function
	void async_window :: run() {
		async_window::current_handle = this;
		gl_init();
		glutMainLoop();
	}


	// initializes opengl
	void async_window :: gl_init() {
		char  arg0[] = "program_name";
		char* argv[] = { &arg0[0], NULL };
		int argc = 1;

		// glut main inits
		glutInit(&argc, argv);
		glutInitWindowSize(800, 600);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutCreateWindow("async_window");

		// default viewport setup
		glMatrixMode(GL_PROJECTION);
		glViewport(0, 0, 800, 600);
		glLoadIdentity();
		glOrtho(0.f, 800 - 1.f, 0.f, 600 -1.f, -1.f, -1.f);

		// callbacks
		glutMouseFunc(async_window::_mouse);
		glutKeyboardFunc(async_window::_keyboard);
		glutSpecialFunc(async_window::_special);
		glutDisplayFunc(async_window::_render);
		glutIdleFunc(async_window::_idle);
	}

	//
	// Callbacks
	//
	void async_window::render() { }
	void async_window::keyboard(unsigned char key, int mousex, int mousey) { }
	void async_window::mouse(int btn, int state, int x, int y) { }
	void async_window::special(int key, int mousex, int mousey) { }
	void async_window::idle() { }


	void async_window::_render() {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		async_window::current_handle->render();
		glutSwapBuffers();
	}

	void async_window::_keyboard(unsigned char key, int mousex, int mousey) {
		switch (key) {
		case 27: // ESC
			async_window::current_handle->stop();
			break;
		}
		// delegate
		async_window::current_handle->keyboard(key, mousex, mousey);
	}

	void async_window::_mouse(int btn, int state, int x, int y) {
		// delegate
		async_window::current_handle->mouse(btn, state, x, y);
	}

	void async_window::_special(int key, int mousex, int mousey) {
		// delegate
		async_window::current_handle->special(key, mousex, mousey);
	}

	void async_window::_idle() {
		// delegate
		async_window::current_handle->idle();
	}

} }
