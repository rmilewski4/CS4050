CFLAGS := -std=c11 -ggdb

homework1 : PA1.c main.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

.PHONY : clean
clean :
		-rm -f homework1