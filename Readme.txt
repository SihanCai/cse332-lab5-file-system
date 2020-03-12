1. Bugs and warning:
- Cannot use MetadataVisitor to print a file information if it is open.

2. Tests:
-----ls -l command-----
- Normal files:
root $ ls -l
123.txt text     size: 4
abc.img image    size: 9
xyz     directory        size: 31

- Print file that is open:
root/xyz $ ls -l
xyzChild        directory        size: 0
xyzTxt.txt cannot be inspected!
xyzImg.img      image    size: 0

-----rm command-----
- Remove file without -r flag:
root $ ls
123.txt
abc.img
xyz

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ rm abc.img
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
123.txt
xyz

- Remove unempty directory without -r tag:
root $ ls
123.txt
xyz

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ rm xyz
Directory is not empty
command failed
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
123.txt
xyz

- Remove directory with no open file:
root $ ls -l
123.txt text     size: 4
abc.img image    size: 9
xyz     directory        size: 31
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ rm xyz -r
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
123.txt
abc.img

- Remove directory with one open file:
root $ ls -l
123.txt text     size: 4
abc.img image    size: 9
xyz     directory        size: 31
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ rm xyz -r
Directory is not empty
command failed
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls -l
123.txt text     size: 4
abc.img image    size: 9
xyz     directory        size: 11

-----ds command-----
- Without -u flag:
root $ ds abc.img
X X
 X
X X

- With -u flag:
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds abc.img -d
X X X X X

-----cat command-----
- Write to text file:
root $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cat 123.txt
abc
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
abc

- Append to text file:
root $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cat 123.txt -a
aaaa
abc
1213
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
aaaaabc
1213

- Write to image file: 
root $ ds abc.img
X X
 X
X X

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cat abc.img
X  X2
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds abc.img
 X
X

- Write to image file (wrong format):
root $ ds abc.img
X X
 X
X X

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cat abc.img
QWE
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds abc.img

5.Copy - showing copying doesnt modify original file.
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cp 123.txt root/xyz
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cd xyz
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ cat 123.txt
blabla
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ds 123.txt
blabla
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ cd ..
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
aaaa

attempting to copy dir 
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cp xyz xyz
xyz is not supposed tobe a directory, please check usage of cp
command failed

6 Sym.H:\cs332\lab5_minh_zihao\Lab5\x64\Debug>Lab5.exe
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ sym 123.txt root/xyz
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
abc.img
xyz
123.txt

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cd xyz
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ls
xyzChild
xyzTxt.txt
xyzImg.img
123.txt

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ds 123.txt
aaaa
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ cat 123.txt
123123
:wq
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ds 123.txt
123123
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ cd ..
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
123123
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ rm 123.txt
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
abc.img
xyz

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ cd xyz
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ls
xyzChild
xyzTxt.txt
xyzImg.img
123.txt
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ds 123.txt
123123
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ rm 123.txt
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ ls
xyzChild
xyzTxt.txt
xyzImg.img

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root/xyz $ cd ..
To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $ ls
abc.img
xyz

To quit: q, For a list of commands: help, For information about a specific command: help <command name>
root $

