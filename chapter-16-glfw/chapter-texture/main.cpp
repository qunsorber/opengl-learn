#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../public/shader.h"
#include "../public/texture.h"

#include <iostream>
#include <memory>

void framebuffer_size_callback(GLFWwindow* window,int width, int height);
void processInput(GLFWwindow* window);

int main()
{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

		GLFWwindow *window = glfwCreateWindow(640,480,"learn opengl",NULL,NULL);
		if(window == NULL)
		{
				std::cout<<"failed create window"<<std::endl;
				glfwTerminate();
				return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
				std::cout<<"glfw load gl loader failed."<<std::endl;
				return -1;
		}

		GLuint vao;
		GLuint vbo;
		luwu::Shader sd("./texture.vert","./texture.frag");

		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);

		glGenBuffers(1,&vbo);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);

		float vertices[]=
		{
			-0.5,0.5,-1,0,1,
			0.5,0.5,-1,1,1,
			0.5,-0.5,-1,1,0,

			0.5,-0.5,-1,1,0,
			-0.5,-0.5,-1,0,0,
			-0.5,0.5,-1,0,1
		};

		glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT) * 5,(GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*5,(GLvoid*)(sizeof(GL_FLOAT)*3));
		glEnableVertexAttribArray(1);

		std::unique_ptr<luwu::Texture2D> tex = std::make_unique<luwu::Texture2D>("./3.png");
		std::unique_ptr<luwu::Texture2D> tex2 = std::make_unique<luwu::Texture2D>("./yu.png");
		while(!glfwWindowShouldClose(window))
		{
				processInput(window);
				glClearColor(0.2,0.3,0.3,1.0);
				glClear(GL_COLOR_BUFFER_BIT);

				//triangle
				sd.Use();
				glBindTexture(GL_TEXTURE_2D,tex->Get());
				glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES,0,6);

				glfwSwapBuffers(window);
				glfwPollEvents();

		}

		glDeleteVertexArrays(1,&vao);
		glDeleteBuffers(1,&vbo);

		glfwTerminate();
		return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
		glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
		if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
				glfwSetWindowShouldClose(window,GL_TRUE);
		}
}
