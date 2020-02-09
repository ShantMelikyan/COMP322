ALL: demo.c
	gcc -c demo.c
	gcc -o demo demo.c
clean:
	rm -f demo

