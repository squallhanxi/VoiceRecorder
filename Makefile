vr : main.o p_play.o init.o p_record.o p_save.o \
		func.o p_alive.o uart.o p_recv.o
	cc -l pthread -o vr main.o p_play.o init.o \
		p_record.o p_save.o func.o p_alive.o uart.o p_recv.o
	rm main.o p_play.o init.o p_record.o p_save.o \
		func.o p_alive.o uart.o p_recv.o

main.o : main.c
	cc -c main.c

p_play.o : p_play.c p_play.h
	cc -c p_play.c

init.o : init.c init.h
	cc -c init.c

p_record.o : p_record.c p_record.h
	cc -c p_record.c

p_save.o : p_save.c p_save.h
	cc -c p_save.c

func.o : func.c func.h
	cc -c func.c

p_alive.o : p_alive.c p_alive.h
	cc -c p_alive.c

uart.o : uart.c uart.h
	cc -c uart.c

p_recv.o : p_recv.c p_recv.h
	cc -c p_recv.c
	

