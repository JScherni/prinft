
# prnft

Concatenate FILES to standard output. Optinally arguments can be given to indicate the first and last printed line. Additionally the lines can be numbered.


## Demo


```bash
  ./prnft.o --help
```

Output

```bash
Usage: prnft [OPTION]... [FILE]... 
Concatenate FILES to standard output.

With no FILE, or when FILE is -, read standard input.

Parameter:
  -f n       first line which will be displayed
             if left blank start from beginning
  -t m       last line which will be displayed
             if left blank all lines till end will be displayed
  -n         number all output lines
  --help     display this help and exit
  --version  output version information and exit

Examples:
  prnft -f 10 -t 15 test.txt
    prints line 10 to 15 from file test.txt
  cat test.txt | prntf -t 15 -n
    data is read from stdin and printed from beginning to line 15
    lines are printed with associated linenumber

Full documentation <https://github.com/JScherni/prinft>
```



## Build it yourself

Clone the project

```bash
  git clone https://github.com/JScherni/prinft/
```

Go to the project directory

```bash
  cd prinft
```

compile the sourcecode

```bash
  gcc -o prnft.o main.c
```

execute 

```bash
  ./prnft.o -f 5 -t 10 readme.md
```


## Authors

- Jonas Schernthaner: [@JScherni](https://github.com/JScherni)
- David Gahleitner: [@dgahleitner](https://github.com/dgahleitner)

