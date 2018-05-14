// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "common/shader.hpp"
#include "common/texture.hpp"
#include "common/controls.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "common/objloader.hpp"

glm::mat4 getMVPMatrix() {
	glm::mat4 Projection = glm::perspective(
		glm::radians(30.0f), // The vertical Field of View, usually between 90°(extra wide) and 30°(quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the sizeof your window.
		0.1f, // Near clipping plane. Keep as big aspossible, or you'll get precision issues.
		100.0f // Far clipping plane. Keep as littleas possible.
	);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 5, 4), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0.7, 1), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside - down)
		);
	glm::mat4 Model = glm::mat4(1.0f); // keep an identity matrix so the geometry stays where it was placed originally
										// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
	return mvp;
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1080, 720, "The Race against time!", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1080 / 2, 720 / 2);

	// Moccasin background
	glClearColor(1.0f, 0.894f, 0.710f, 0.0f);	

	// Buffers to help to describe data in a 3D scene
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//game floor
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("GameFloor.obj", vertices, uvs, normals);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//ball
	std::vector<glm::vec3> vertices1;
	std::vector<glm::vec2> uvs1; // Won't be used at the moment.
	std::vector<glm::vec3> normals1; // Won't be used at the moment.
	bool res1 = loadOBJ("Ball.obj", vertices1, uvs1, normals1);

	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

	//Spike1
	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec2> uvs2; // Won't be used at the moment.
	std::vector<glm::vec3> normals2; // Won't be used at the moment.
	bool res2 = loadOBJ("Spike1.obj", vertices2, uvs2, normals2);

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	//Spike2
	std::vector<glm::vec3> vertices3;
	std::vector<glm::vec2> uvs3; // Won't be used at the moment.
	std::vector<glm::vec3> normals3; // Won't be used at the moment.
	bool res3 = loadOBJ("Spike2.obj", vertices3, uvs3, normals3);

	GLuint vertexbuffer3;
	glGenBuffers(1, &vertexbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);

	//Spike3
	std::vector<glm::vec3> vertices4;
	std::vector<glm::vec2> uvs4; // Won't be used at the moment.
	std::vector<glm::vec3> normals4; // Won't be used at the moment.
	bool res4 = loadOBJ("Spike3.obj", vertices4, uvs4, normals4);

	GLuint vertexbuffer4;
	glGenBuffers(1, &vertexbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(glm::vec3), &vertices4[0], GL_STATIC_DRAW);

	//Spike4
	std::vector<glm::vec3> vertices5;
	std::vector<glm::vec2> uvs5; // Won't be used at the moment.
	std::vector<glm::vec3> normals5; // Won't be used at the moment.
	bool res5 = loadOBJ("Spike4.obj", vertices5, uvs5, normals5);

	GLuint vertexbuffer5;
	glGenBuffers(1, &vertexbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices5.size() * sizeof(glm::vec3), &vertices5[0], GL_STATIC_DRAW);

	//Spike5
	std::vector<glm::vec3> vertices6;
	std::vector<glm::vec2> uvs6; // Won't be used at the moment.
	std::vector<glm::vec3> normals6; // Won't be used at the moment.
	bool res6 = loadOBJ("Spike5.obj", vertices6, uvs6, normals6);

	GLuint vertexbuffer6;
	glGenBuffers(1, &vertexbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices6.size() * sizeof(glm::vec3), &vertices6[0], GL_STATIC_DRAW);

	//Spike6
	std::vector<glm::vec3> vertices7;
	std::vector<glm::vec2> uvs7; // Won't be used at the moment.
	std::vector<glm::vec3> normals7; // Won't be used at the moment.
	bool res7 = loadOBJ("Spike6.obj", vertices7, uvs7, normals7);

	GLuint vertexbuffer7;
	glGenBuffers(1, &vertexbuffer7);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer7);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices7.size() * sizeof(glm::vec3), &vertices7[0], GL_STATIC_DRAW);

	//Spike7
	std::vector<glm::vec3> vertices8;
	std::vector<glm::vec2> uvs8; // Won't be used at the moment.
	std::vector<glm::vec3> normals8; // Won't be used at the moment.
	bool res8 = loadOBJ("Spike7.obj", vertices8, uvs8, normals8);

	GLuint vertexbuffer8;
	glGenBuffers(1, &vertexbuffer8);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer8);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices8.size() * sizeof(glm::vec3), &vertices8[0], GL_STATIC_DRAW);

	//Spike8
	std::vector<glm::vec3> vertices9;
	std::vector<glm::vec2> uvs9; // Won't be used at the moment.
	std::vector<glm::vec3> normals9; // Won't be used at the moment.
	bool res9 = loadOBJ("Spike8.obj", vertices9, uvs9, normals9);

	GLuint vertexbuffer9;
	glGenBuffers(1, &vertexbuffer9);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer9);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices9.size() * sizeof(glm::vec3), &vertices9[0], GL_STATIC_DRAW);

	//Spike9
	std::vector<glm::vec3> vertices10;
	std::vector<glm::vec2> uvs10; // Won't be used at the moment.
	std::vector<glm::vec3> normals10; // Won't be used at the moment.
	bool res10 = loadOBJ("Spike9.obj", vertices10, uvs10, normals10);

	GLuint vertexbuffer10;
	glGenBuffers(1, &vertexbuffer10);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer10);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices10.size() * sizeof(glm::vec3), &vertices10[0], GL_STATIC_DRAW);

	//Spike10
	std::vector<glm::vec3> vertices11;
	std::vector<glm::vec2> uvs11; // Won't be used at the moment.
	std::vector<glm::vec3> normals11; // Won't be used at the moment.
	bool res11 = loadOBJ("Spike10.obj", vertices11, uvs11, normals11);

	GLuint vertexbuffer11;
	glGenBuffers(1, &vertexbuffer11);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer11);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices11.size() * sizeof(glm::vec3), &vertices11[0], GL_STATIC_DRAW);

	//Spike11
	std::vector<glm::vec3> vertices12;
	std::vector<glm::vec2> uvs12; // Won't be used at the moment.
	std::vector<glm::vec3> normals12; // Won't be used at the moment.
	bool res12 = loadOBJ("Spike11.obj", vertices12, uvs12, normals12);

	GLuint vertexbuffer12;
	glGenBuffers(1, &vertexbuffer12);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer12);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices12.size() * sizeof(glm::vec3), &vertices12[0], GL_STATIC_DRAW);

	//Coin1
	std::vector<glm::vec3> vertices13;
	std::vector<glm::vec2> uvs13; // Won't be used at the moment.
	std::vector<glm::vec3> normals13; // Won't be used at the moment.
	bool res13 = loadOBJ("Coin1.obj", vertices13, uvs13, normals13);

	GLuint vertexbuffer13;
	glGenBuffers(1, &vertexbuffer13);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer13);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices13.size() * sizeof(glm::vec3), &vertices13[0], GL_STATIC_DRAW);

	//Coin2
	std::vector<glm::vec3> vertices14;
	std::vector<glm::vec2> uvs14; // Won't be used at the moment.
	std::vector<glm::vec3> normals14; // Won't be used at the moment.
	bool res14 = loadOBJ("Coin2.obj", vertices14, uvs14, normals14);

	GLuint vertexbuffer14;
	glGenBuffers(1, &vertexbuffer14);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer14);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices14.size() * sizeof(glm::vec3), &vertices14[0], GL_STATIC_DRAW);

	//Coin3
	std::vector<glm::vec3> vertices15;
	std::vector<glm::vec2> uvs15; // Won't be used at the moment.
	std::vector<glm::vec3> normals15; // Won't be used at the moment.
	bool res15 = loadOBJ("Coin3.obj", vertices15, uvs15, normals15);

	GLuint vertexbuffer15;
	glGenBuffers(1, &vertexbuffer15);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer15);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices15.size() * sizeof(glm::vec3), &vertices15[0], GL_STATIC_DRAW);

	//Coin4
	std::vector<glm::vec3> vertices16;
	std::vector<glm::vec2> uvs16; // Won't be used at the moment.
	std::vector<glm::vec3> normals16; // Won't be used at the moment.
	bool res16 = loadOBJ("Coin4.obj", vertices16, uvs16, normals16);

	GLuint vertexbuffer16;
	glGenBuffers(1, &vertexbuffer16);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer16);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices16.size() * sizeof(glm::vec3), &vertices16[0], GL_STATIC_DRAW);

	//Coin5
	std::vector<glm::vec3> vertices17;
	std::vector<glm::vec2> uvs17; // Won't be used at the moment.
	std::vector<glm::vec3> normals17; // Won't be used at the moment.
	bool res17 = loadOBJ("Coin5.obj", vertices17, uvs17, normals17);

	GLuint vertexbuffer17;
	glGenBuffers(1, &vertexbuffer17);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer17);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices17.size() * sizeof(glm::vec3), &vertices17[0], GL_STATIC_DRAW);

	//Coin6
	std::vector<glm::vec3> vertices18;
	std::vector<glm::vec2> uvs18; // Won't be used at the moment.
	std::vector<glm::vec3> normals18; // Won't be used at the moment.
	bool res18 = loadOBJ("Coin6.obj", vertices18, uvs18, normals18);

	GLuint vertexbuffer18;
	glGenBuffers(1, &vertexbuffer18);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer18);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices18.size() * sizeof(glm::vec3), &vertices18[0], GL_STATIC_DRAW);

	/*/static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end

		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// One color for each vertex. 
	static const GLfloat g_color_buffer_data[] = {
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,

		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
		0.0f,  0.0f,  5.0f,
	};

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);*/

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	GLuint MatrixID1 = glGetUniformLocation(programID, "MVP");

	do{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear( GL_COLOR_BUFFER_BIT );

		glm::mat4 mvp1 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1[0][0]);

		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(res));

		glm::mat4 mvp2 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp2[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles
		
		glDrawArrays(GL_TRIANGLES, 0, vertices1.size() * sizeof(res1));

		//New mvp
		glm::mat4 mvp3 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp3[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices2.size() * sizeof(res2));

		//New mvp
		glm::mat4 mvp4 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp4[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices3.size() * sizeof(res3));

		//New mvp
		glm::mat4 mvp5 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp5[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices4.size() * sizeof(res4));

		//New mvp
		glm::mat4 mvp6 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp6[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices5.size() * sizeof(res5));

		//New mvp
		glm::mat4 mvp7 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp7[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices6.size() * sizeof(res6));

		//New mvp
		glm::mat4 mvp8 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp8[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer7);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices7.size() * sizeof(res7));

		//New mvp
		glm::mat4 mvp9 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp9[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer8);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices8.size() * sizeof(res8));

		//New mvp
		glm::mat4 mvp10 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp10[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer9);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices9.size() * sizeof(res9));

		//New mvp
		glm::mat4 mvp11 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp11[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer10);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices10.size() * sizeof(res10));

		//New mvp
		glm::mat4 mvp12 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp12[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer11);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices11.size() * sizeof(res11));

		//New mvp
		glm::mat4 mvp13 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp13[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer12);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices12.size() * sizeof(res12));

		//New mvp
		glm::mat4 mvp14 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp14[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer13);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices13.size() * sizeof(res13));

		//New mvp
		glm::mat4 mvp15 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp15[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer14);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices14.size() * sizeof(res14));

		//New mvp
		glm::mat4 mvp16 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp16[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer15);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices15.size() * sizeof(res15));

		//New mvp
		glm::mat4 mvp17 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp17[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer16);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices16.size() * sizeof(res16));

		//New mvp
		glm::mat4 mvp18 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp18[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer17);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices17.size() * sizeof(res17));

		//New mvp
		glm::mat4 mvp19 = getMVPMatrix();
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp19[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer18);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles

		glDrawArrays(GL_TRIANGLES, 0, vertices18.size() * sizeof(res18));

		glDisableVertexAttribArray(0);

		/* 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// The following code draws a triangle using the function void glDrawArrays(     GLenum mode,      GLint first,      GLsizei count);
		glDrawArrays(GL_TRIANGLES, 0, 36); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3

		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);*/
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &vertexbuffer1);
	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteBuffers(1, &vertexbuffer3);
	glDeleteBuffers(1, &vertexbuffer4);
	glDeleteBuffers(1, &vertexbuffer5);
	glDeleteBuffers(1, &vertexbuffer6);
	glDeleteBuffers(1, &vertexbuffer7);
	glDeleteBuffers(1, &vertexbuffer8);
	glDeleteBuffers(1, &vertexbuffer9);
	glDeleteBuffers(1, &vertexbuffer10);
	glDeleteBuffers(1, &vertexbuffer11);
	glDeleteBuffers(1, &vertexbuffer12);
	glDeleteBuffers(1, &vertexbuffer13);
	glDeleteBuffers(1, &vertexbuffer14);
	glDeleteBuffers(1, &vertexbuffer15);
	glDeleteBuffers(1, &vertexbuffer16);
	glDeleteBuffers(1, &vertexbuffer17);
	glDeleteBuffers(1, &vertexbuffer18);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	/* Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	/* Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);*/
}

