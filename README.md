# PICOSHELL EXPLANATION
## By Hugo Parada (htrindad)

The exam subject will give you a ``main.c`` for you to test with your application. **you should watchout for any potential cases of infinite loop which will be explained**.

For those of you who didn't do ``pipex`` there is lots of ways to mess this up, usually it will cause the program to cause an infinite loop. You might have to study pipes.

Every command token will be seggregated by pipes, nothing else.

### My own messes

I was one of those folks who didn't do pipex, so I was very clumsy at the beggining at handling pipes inside a program, and working with processes. TBF I am still learning to handle these specific computer functions, usually this would cause for me to run a program such as "grep" and there wouldn't be an output for it to read, so **the grep would be running for infinity**. I will compile my own mistakes in this README file.

### What I had learned

- You cannot fork a program twice or more.
- You need to be precise with the way you close the pipe fds.
- All the pipes are writing to the ``STDIN_FILENO``, and it's just a question of dupping everything

### Why doesn’t close(fd[0]) in the child break it?

file descriptors **are not universal**. So 2 processes can have a an fd id number 3. Which is why it is important to close the respective fds in their respective processes.

This is why the code:

```c
		in_fd = fd[0]; // this sets to fd[0] but said fd is closed.
```

seems to work.

### you don't need to dup2 fd[0] until the last program, unless you're piping between programs

technically you could add the outputs of ``ls``, ``whoami``, and ``git`` then piping them all into ``grep`` with some argument and it would work

### credits

[Lastftw's picoshell](https://github.com/Lastftw/42-Exam-rank-4/blob/main/LVL%201/picoshell.c)
