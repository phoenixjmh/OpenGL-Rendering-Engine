#include <iostream>
#include <stdio.h>
#include "Application.h"




int main()
{
    Application app;

    while (!glfwWindowShouldClose(app.GetWindow())) {
        app.Run();
        // frame logic
           }
    app.Close();

      return 0;
}


// #endif
