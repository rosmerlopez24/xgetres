# xgetres

xgetres is a simple utility which prints the value of an X resource.

## Example
```basg
$ cat .Xresources
first: 1
second: 2
$ xgetres first
1
$ xgetres second
2
```

## Build & installation

First make sure you have libx11.

In order to build, simply run:

```bash
$ make
```

Then in order to install, run:
```bash
$ make install
```
