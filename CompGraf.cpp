#define GLHW_DDL
#define GLEW_DDL

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
float point[] = { 0.0f, 0.5f, 0.0f ,
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f };

int index[] = { 0 ,1 ,2 };

int main()
{
	std::cout << "Hello triangle!\n";

	glfwInit();

	if (!glfwInit()) {
		fprintf(stderr, "ERROR GLFW3:\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* MyWindow = glfwCreateWindow(512, 512, "My window", NULL, NULL);

	if (!MyWindow) {
		glfwTerminate();
		return 1;
	}

	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(MyWindow);

	GLenum ret = glewInit();
	if (GLEW_OK != ret) {
		fprintf(stderr, "ERROR: %s \n", glewGetErrorString(ret));
		return 1;
	}

	GLuint vAo, vBo, Ebo;
	glGenVertexArrays(1, &vAo);
	glGenBuffers(1, &vBo);
	glGenBuffers(1, &Ebo);

	glBindVertexArray(vAo);

	glBindBuffer(GL_ARRAY_BUFFER, vBo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	const char* vert_shader =
		"#version 460 \n"
		"layout (location=0) in vec3 vp;"
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		"}";

	const char* frag_shader =
		"#version 460 \n"
		"uniform vec4 ourColour;"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = ourColour;"
		"}";

	GLuint vesrts = glCreateShader(GL_VERTEX_SHADER);
	GLuint frags = glCreateShader(GL_FRAGMENT_SHADER);
	GLint success;
	GLchar infoLog[1024];

	glShaderSource(vesrts, 1, &vert_shader, NULL);
	glShaderSource(frags, 1, &frag_shader, NULL);

	glCompileShader(vesrts);
	glGetShaderiv(vesrts, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vesrts, sizeof(infoLog), 0, infoLog);
	fprintf(stderr, "ERROR: %s \n", infoLog);
	glCompileShader(frags);
	glGetShaderiv(vesrts, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(frags, sizeof(infoLog), 0, infoLog);
	fprintf(stderr, "ERROR: %s \n", infoLog);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vesrts);
	glAttachShader(shader_program, frags);
	glLinkProgram(shader_program);



	while (!glfwWindowShouldClose(MyWindow)) {

		glfwPollEvents();

		glClearColor(1, 1, 1, 1);

		glClear(GL_COLOR_BUFFER_BIT);


		//glBegin(GL_TRIANGLES);
		//glColor3f(1,0,0);
		//glVertex3f(0, 0.5, 0);
		//glColor3f(0,1,0);
		//glVertex3f(-0.5, -0.5, 0);
		//glColor3f(0,0,1);
		//glVertex3f(0.5, -0.5, 0);
		//glEnd();

		glUseProgram(shader_program);
		float vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
		glUniform4f(vertexColorLocation, 0, 1, 0, 1);
		glBindVertexArray(vAo);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(MyWindow);
	}
}