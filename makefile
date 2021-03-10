
.PHONY = all clean

cc = gcc

LINKERFLAGS = - Wall -Werror -Wpedantic -Wextra

all: main

main: main.o
	@echo "checking.."
	${CC} ${LINKERFLAG} $< -o $@

main.o: main.cpp
	@echo "Creating objekt.."
	${CC} -c $<

clean:
	@echo "cleaning up..."
	rm -rvf *.o jesus.exe
