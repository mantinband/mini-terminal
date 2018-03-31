amichai mantinband 305663106

added features:
read, write, touch, copy, remove, move, cat, wc, ln,
mkdir, rmdir, ls and pwd:
command <file name> without path refers to current folder.
(e.x 'mkdir hello', instead of 'mkdir V/hello')
when in folder other than root, no need to specify entire path.
(e.x when in 'V/hello', typing touch 'hi.txt'
will create file, instead of touch 'V/hello/hi.txt')


ls:
ls . (dot) prints current folders content
(e.x 'ls .' instead of ls 'V/hello/')

--help:
prints commands.

lproot:
lproot prints time stamp as well, updated every "touch", or edit.


enjoy!
