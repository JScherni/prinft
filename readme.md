
# prnft

Concatenate FILES to standard output. Optinally arguments can be given to indicate the first and last printed line. Additionally the lines can be numbered.


## Demo


```bash
  ./prnft.o -f 10 -t 15 readme.md
```

Output

```bash
  "Output omitted"
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
