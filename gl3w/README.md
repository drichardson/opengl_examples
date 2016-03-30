# gl3w loading library

[gl3w](https://github.com/skaslev/gl3w) is an OpenGL loading library that is generated
by running a python script. Rather than running the python script in a build file, which
could produce different source and header files depending on when it was run, the generated
files are checked into this directory.

To update the generated files, run `./update.sh`.
