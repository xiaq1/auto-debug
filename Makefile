MYLIB := libdemo.a
BIN := main
CFLAG := -Wall -I../ -I./ -DTEST -DMULTI_THREAD -g
LIBFLAG := -L/usr/lib -lpthread

all: $(MYLIB) $(BIN)

$(BIN): main.o 
	gcc $(CFLAG) -o $@  $^ $(MYLIB) $(LIBFLAG) 
	#gcc $(CFLAG) -o $@  $^ $(MYLIB) -lpthread

$(MYLIB): demo.o
	ar -rcv $@ $^

%.o:%.c
	gcc $(CFLAG) $(LIBFLAG) -c -o $@ $<


.PHONY: clean
clean:
	rm -rf *.o $(BIN) $(MYLIB)

