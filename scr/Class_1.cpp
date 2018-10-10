#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//申明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//设置参数
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    //初始化窗体
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//调用核心

    //创建窗体
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);//实例化窗体对象（宽，高，窗体名称）
    //异常捕获
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//创建窗体
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//窗体大小更新函数

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // 循环体
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 键盘输入检测
        // -----
        processInput(window);

        
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwPollEvents();//窗体事件捕获
    }

  
    // ------------------------------------------------------------------
    glfwTerminate();//关闭窗体后释放资源
    return 0;
}

//检测用户键盘输入Esc键后关闭窗体
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//调用glViewport函数来设置窗口的维度
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。 
    glViewport(0, 0, width, height);
}
