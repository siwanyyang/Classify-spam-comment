TARGET=trainer

trainer : trainer.o t_function.o
	gcc -o trainer trainer.o t_function.o

trainer.o : trainer.h trainer.c
	gcc -c trainer.c -o trainer.o

t_function.o : t_function.c trainer.h
	gcc -c t_function.c -o t_function.o

clean:
	rm -f *.o
	rm -f $(TARGET)