#define GLEW_STATIC

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

#include "ShaderFactory.h"
int main()
{
	// SFML creates window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Make it Rain",sf::Style::Close);
	sf::Clock clock = sf::Clock();
	// init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// create the vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create the vertex buffer object and copy vertex data
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
     -1.0f,-1.0f, // Vertex 1 (X, Y)
     -1.0f, 1.0f, // Vertex 2 (X, Y)
      1.0f, 1.0f,  // Vertex 3 (X, Y)
      1.0f, 1.0f, // Vertex 1 (X, Y)
      1.0f,-1.0f, // Vertex 2 (X, Y)
     -1.0f,-1.0f  // Vertex 3 (X, Y)
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// create and compile vertex and fragment shader using ShaderFactory
	ShaderFactory::GetInstance()->LoadShaderFromFile("Shaders/shader.vert", "Shaders/shader.frag");
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));

	GLint posAttrib = glGetAttribLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0), "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	GLint timeuni = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0), "time");

	while(window.isOpen())
	{
#pragma region //closes the window
		
		glUniform1f(timeuni, clock.getElapsedTime().asSeconds());
		std::cout<<"Time: " << clock.getElapsedTime().asSeconds() << std::endl;
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			switch(windowEvent.type)
			{
				//Stop the program from running after the window is closed
				case sf::Event::Closed:
					window.close();
					break;

				// Allows the escape key to close window
				case sf::Event::KeyPressed:
					if(windowEvent.key.code == sf::Keyboard::Escape)
						window.close();
					break;
			}
		}
#pragma endregion
		// clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.display();
	}

	// clean up after myself.
	glDeleteProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

	return 0;
}
