#include<glad/glad.h>  
#include<GLFW/glfw3.h>


#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//GLSL着色器语言，来写两个着色器
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//编译顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//把着色器源码附加到顶点着色器上
	glCompileShader(vertexShader);//编译顶点着色器

	//编译片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建片段着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//把着色器源码附加到顶点着色器上
	glCompileShader(fragmentShader);//编译片段着色器

	//创建着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();//实例化着色器程序对象
	glAttachShader(shaderProgram, vertexShader);//链接顶点着色器
	glAttachShader(shaderProgram, fragmentShader);//链接片段着色器
	glLinkProgram(shaderProgram);//链接所有着色器

	//删除两个着色器程序释放资源
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//定义顶点数组
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	
	unsigned int VBO, VAO;//定义缓冲对象和缓冲数组
	glGenVertexArrays(1, &VAO);//创建缓冲数组
	glGenBuffers(1, &VBO);//创建缓冲对象
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);//绑定缓冲数组

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲类型
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置缓冲数据
	//缓冲类型,缓冲数据大小,顶点输出,绘画方式

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//链接顶点属性
	//顶点属性的位置值(Location)，顶点属性的大小，顶点数据类型，是否希望数据被标准化，步长
	glEnableVertexAttribArray(0);//启用顶点属性

	glBindBuffer(GL_ARRAY_BUFFER, 0);//
	glBindVertexArray(0);//

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
