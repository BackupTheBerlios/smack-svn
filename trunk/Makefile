CFLAGS=`pkg-config --cflags gtk+-2.0 liblo phat` -g -Wall -Werror
LIBS=`pkg-config --libs gtk+-2.0 liblo phat`
OFILES=gui.o gui-drum.o
gui: $(OFILES)
	gcc -o gui $(OFILES) $(LIBS)

gui-drum.o: gui-drum.c gui-drum.h
	gcc -c gui-drum.c $(CFLAGS)

gui.o: gui.c gui.h gui-drum.h
	gcc -c gui.c $(CFLAGS)
	
clean:
	touch foo
	rm -fr foo gui gui.tar.gz *.o

dist: clean
	cd ..; tar -czvpf gui.tar.gz gui; mv gui.tar.gz gui; cd -
