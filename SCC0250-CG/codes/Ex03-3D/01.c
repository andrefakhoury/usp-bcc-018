/**
 * =========================================
 * + Atividade 4.1 - Computação Gráfica    +
 * + André Luís Mendes Fakhoury - 4482145  +
 * + Professor Ricardo Marcacini           +
 * + ICMC - USP - São Carlos - 2021        +
 * =========================================
*/

#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct {
	float x, y, z;
} Point3D;

// global variables
float angle = 0;

// callback to key actions
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
	printf("Pressing key %d\n", key);

	if(key == GLFW_KEY_RIGHT) angle -= 0.05;
	if(key == GLFW_KEY_LEFT)  angle += 0.05;

	if (key == GLFW_KEY_ENTER) {
		angle = 0;
	}
}

// multiplies matrices a and b, c = a * b
void matrix_mult(float* a, float* b, float* c, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i * n + j] = 0;
			for (int k = 0; k < n; k++) {
				c[i * n + j] += a[i * n + k] * b[k * n + j];
			}
		}
	}
}

/** Compile given shader and check and print any errors */
void compileAndCheckShader(GLuint shader) {
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE){ // Compilation error
		int infoLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

		char *info = malloc(infoLength * sizeof(char));
		glGetShaderInfoLog(shader, infoLength, NULL, info);

		fprintf(stderr, "Shader compilation error: %s\n", info);
	}
}

int main() {
	/* =================================== Initialize windows =================================== */
	glfwInit(); // init windows system
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // set window invisible

	// creating new window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);

	// set default window
	glfwMakeContextCurrent(window);

	// initialize GLEW
	GLint GlewInitResult = glewInit();
	printf("[GlewStatus] %s\n", glewGetErrorString(GlewInitResult));

	/* ======================================== Shaders ======================================== */
	const GLchar* vertex_code = // Vertex Shader GLSL
		"attribute vec3 position;\n"
		"uniform mat4 mat_transformation;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = mat_transformation * vec4(position, 1.0);\n"
		"}\n";

	const GLchar* fragment_code = // Fragment Shader GLSL
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = color;\n"
		"}\n";

	// GPU slot requisition
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// associating GLSL codes to slots
	glShaderSource(vertex, 1, &vertex_code, NULL);
	glShaderSource(fragment, 1, &fragment_code, NULL);

	// compile shader and check for errors
	compileAndCheckShader(vertex);
	compileAndCheckShader(fragment);

	// attaching shader to main program
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	// link program and use as default
	glLinkProgram(program);
	glUseProgram(program);

	// Prepare vertices
	Point3D vertices[16] = {
		{-0.2, +0.0, +0.2},
		{+0.2, +0.0, +0.2},
		{+0.0, +0.5, +0.0},

		{+0.2, +0.0, +0.2},
		{+0.2, +0.0, -0.2},
		{+0.0, +0.5, +0.0},

		{+0.2, +0.0, -0.2},
		{-0.2, +0.0, -0.2},
		{+0.0, +0.5, +0.0},

		{-0.2, +0.0, +0.2},
		{-0.2, +0.0, -0.2},
		{+0.0, +0.5, +0.0},
		
		// base
		{-0.2, +0.0, -0.2},
		{+0.2, +0.0, -0.2},         
		{-0.2, +0.0, +0.2},
		{+0.2, +0.0, +0.2},        
	};

	// Buffer data
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// send buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// associate variables from GLSL with data
	GLint loc = glGetAttribLocation(program, "position");
	GLint loc_transf = glGetUniformLocation(program, "mat_transformation");
	GLint loc_color = glGetUniformLocation(program, "color");
	
	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), NULL);

	// attach window to keyboard events
	glfwSetKeyCallback(window, key_event);


	/* =================================== Show windows =================================== */
	glfwShowWindow(window);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);

		float c = cos(angle);
		float s = sin(angle);
		
		float mat_rotation_z[16] = {
			c   , -s  , 0.0f, 0.0f,
			s   ,  c  , 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		float mat_rotation_x[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  c  ,  -s , 0.0f,
			0.0f,  s  ,   c , 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		float mat_rotation_y[16] = {
			c   , 0.0f,   s , 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-s  , 0.0f,   c , 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		float mat_aux[16], mat_transf[16];

		matrix_mult(mat_rotation_z, mat_rotation_x, mat_aux, 4);
		matrix_mult(mat_rotation_y, mat_aux, mat_transf, 4);
		
		loc_transf = glGetUniformLocation(program, "mat_transformation");
		glUniformMatrix4fv(loc_transf, 1, GL_TRUE, mat_transf);
		
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
		
		glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 3, 3);
		
		glUniform4f(loc_color, 0.0, 1.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 6, 3);
		
		glUniform4f(loc_color, 1.0, 1.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 9, 3);
		
		glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
