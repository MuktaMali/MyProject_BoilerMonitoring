CC=gcc
CFLAGS=-Wall -pthread

OBJ=main.o controller.o sensors.o ipc.o logger.o signal_handler.o

boiler: $(OBJ)
	$(CC) $(CFLAGS) -o boiler $(OBJ)

main.o: main.c
controller.o: controller.c
sensors.o: sensors.c
ipc.o: ipc.c
logger.o: logger.c
signal_handler.o: signal_handler.c

clean:
	rm -f *.o boiler
