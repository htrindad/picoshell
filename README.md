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

### Why doesn’t close(fd[0]) in the child break it?

Because the child doesn’t need it. The parent needs ``fd[0]``, and it still has its own reference. When the parent sets ``in_fd = fd[0]``, that’s a live descriptor, not closed in the parent.

### credits

[Lastftw's picoshell](https://github.com/Lastftw/42-Exam-rank-4/blob/main/LVL%201/picoshell.c)
