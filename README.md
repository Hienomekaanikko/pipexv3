Usage example:

Just like in bash this kind of input behaves: < infile grep "abc" | wc -l > outfile

Pipex accomplishes the same result with ./pipex infile 'grep "abc"' "wc -l" outfile

Error situations give the correct exitcode and error message, and correctly clears the memory and file descriptors in parent/child processes. 

The "star" functions in this project were dup2(), execve() and wait() which all became very familiar during the total 8 times I had to recreate this nervecracking project.

