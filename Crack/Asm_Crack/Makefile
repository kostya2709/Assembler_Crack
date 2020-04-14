#.PHONY: all clean

FNAME=secret
TEST=test
CFLAGS= -f elf64
LFLAGS= -s -o

all: clean $(FNAME)

$(FNAME): $(FNAME).o
	@ld $(LFLAGS) $(FNAME) $(FNAME).o
#	@objdump -d security_plans
	@./$(FNAME)

$(FNAME).o:
#	@nasm $(CFLAGS) $(FNAME).asm
	@nasm $(CFLAGS) $(FNAME).asm

clean:
	@rm -rf $(FNAME) *.o

cedb: all
	@edb --run $(FNAME)
	@clear

edb:
	@edb --run $(FNAME)
	@clear