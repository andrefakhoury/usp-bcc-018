/**
 * =========================================
 * + Atividade 1 - Computação Gráfica      +
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
	double x, y;
} Point2D;

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
		"attribute vec2 position;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(position, 0.0, 1.0);\n"
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

	/* =================================== Fill vertices =================================== */

	// prepare data to send to GPU
	const int NCIRCLE = 50;
	const int NSQUARE = 36;
	const int NRANDOM = 20;

	Point2D vertices[NCIRCLE + NSQUARE + NRANDOM];

	// set fixed random seed
	int seed = 1619099895; // time(NULL);
	srand(seed);
	printf("Seed: %d\n", seed);

	// == Square points ==
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			double x_square = (col + 1) * 0.1 + col * 0.6 - 1.0;
			double y_square = (row + 1) * 0.1 + row * 0.6 - 1.0;
			double sq_radius = 0.6;

			int cur_id = (3 * row + col) * 4; // each square has 4 points
			for (int i = 0; i <= 1; i++) { // 00, 01, 11, 10
				for (int j = i, cnt = 0; cnt < 2; cnt++, j ^= 1) {
					vertices[cur_id].x = x_square + i * sq_radius;
					vertices[cur_id].y = y_square + j * sq_radius;
					cur_id++;
				}
			}
		}
	}

	// == Circle points ==
	double x_circle = (rand() % 200 - 100) / 100.0;
	double y_circle = (rand() % 200 - 100) / 100.0;
	double radius = 0.5;
	for (int i = 0; i < NCIRCLE; i++) {
		double alpha = 2 * i * M_PI / NCIRCLE;
		vertices[i + NSQUARE].x = cos(alpha) * radius + x_circle;
		vertices[i + NSQUARE].y = sin(alpha) * radius + y_circle;
	}

	// == Random points ==
	for (int i = 0; i < NRANDOM; i++) {
		vertices[i + NSQUARE + NCIRCLE].x = (rand() % 200 - 100) / 100.0;
		vertices[i + NSQUARE + NCIRCLE].y = (rand() % 200 - 100) / 100.0;
	}

	// Buffer data
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// send buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// associate variables from GLSL with data
	GLint loc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_DOUBLE, GL_FALSE, sizeof(vertices[0]), NULL); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

	// associate color variable
	GLint loc_color = glGetUniformLocation(program, "color");

	/* =================================== Show windows =================================== */
	glfwShowWindow(window);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);

		int cur_id = 0;

		// Square
		glUniform4f(loc_color, 0, 0, 0, 1.0);
		for (int square = 0; square < 9; square++) {
			glDrawArrays(GL_LINE_LOOP, cur_id, 4);
			cur_id += 4;
		}

		// Circle
		glUniform4f(loc_color, 1.0, 0.5, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, cur_id, NCIRCLE);
		cur_id += NCIRCLE;

		// triangles
		glUniform4f(loc_color, 0.4, 0.9, 0.4, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, cur_id, 3);
		cur_id += 3;

		glUniform4f(loc_color, 0.2, 0.7, 0.8, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, cur_id, 3);
		cur_id += 3;

		// Points
		glUniform4f(loc_color, 1, 1, 1, 1.0);
		glDrawArrays(GL_POINTS, NCIRCLE + NSQUARE, NRANDOM);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
