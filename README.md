# OpenGL-Run-of-the-Mill

Some OpenGL commonplace procedures are piled here, only for the purpose of submitting assignments for a course in computer graphics. I wouldn't recommend anyone to make any "innovative" use of them in a vain attempt as its name already implied: it's a run-of-the-mill.

*About the coursework per se*: Each project is runnable, as long as the environment is set up as follows. The screenshots are ommitted here and will be sent in another way.

## Setup

Here I will use GLFW and GLAD as the libraries to create graphics. Setup the environment following the steps in [https://learnopengl.com/Getting-started/Creating-a-window](https://learnopengl.com/Getting-started/Creating-a-window).

## Compile and Run

In each separate folder under this directory, the programs are independent and runnable. Add the folder to the above-mentioned OpenGL environment, and compile by

```powershell
g++ $fileName -g -I../include -L../lib -o ../$executableName -lglad -lglfw3dll
```

These commands may need some modification according to the actual directory structure.

## License

[GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)

*Special admonition*: Copying the source codes to gloss over any assignments/coursework is considered as plagiarism and piracy, and such behavior is not permitted. This restriction is applied to the contents in this whole repository, along with the GNU GPLv3, as an additional term, and is not stated specially in each file.
