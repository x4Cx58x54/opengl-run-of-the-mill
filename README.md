# OpenGL-Run-of-the-Mill

Some OpenGL commonplace procedures are piled here, only for the purpose of submitting assignments for a course in computer graphics. I wouldn't recommend anyone to attempt vainly to make any "innovative" use of them as the name already implied: it's a run-of-the-mill.

*About the coursework per se*: Each project is runnable, as long as the environment is set up as follows. The screenshots are ommitted here and will be sent in another way.

## Setup and Dependency

Here I will use GLFW and GLAD as the libraries to create graphics. Setup the environment following the steps in [https://learnopengl.com/Getting-started/Creating-a-window](https://learnopengl.com/Getting-started/Creating-a-window).

I chose [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) as the image loader, and the mathematics library is [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm).

## Compile and Run

In each separate folder under this directory, the programs are independent and runnable. Add the folder to the above-mentioned OpenGL environment, and compile the source by

```
g++ $fileName -g -I../include -L../lib -o ../$executableName -lglad -lglfw3dll
```

These commands may need some modification according to the actual directory structure.

## License

[GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)

Please star this repo if it is helpful to you!
