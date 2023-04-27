A shell is an interface present between a kernel and the user. 
A kernel is a the core of an Operating system. A shell has 4 functions:
	> prints a prompt.
	> Reads a line
	> Parse (builds a tree representation)
	> Execute


To use a shell use system calls. A system call is a function that a user program uses to ask the particular OS for a particular service, sort of like communicating with the OS.
Examples of system calls:
	-fork
	-exec
	-exit
	-wait
   (these are used in process control)

	-open
	-close
	-read
	-write
 (these are used in Input/Output)

	-pipe
	-dup
 (these are used to pipe)

	-chdir
 (used to change directory)


* In our project, we are creating a simple shell that mimics the bash shell.
* It should be able to read commands from a file or a standard I/O and executes them.
