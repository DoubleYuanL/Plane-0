
all: a.out b.out scoreHandle.cgi

scoreHandle.cgi: scoreHandle.c
	gcc $^ -o $@ -lsqlite3

a.out : a.c
	gcc $^ -o $@

b.out : b.c
	gcc $^ -o $@
