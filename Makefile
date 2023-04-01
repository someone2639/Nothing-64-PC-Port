default: all

CFLAGS = -Os -fopenmp \
		$(shell pkg-config --libs glfw3)\
		$(shell pkg-config --libs gl) \
		$(shell pkg-config --libs glew)

PROGRAM := Nothing\ 64\ (PC\ Port).z64

all: $(PROGRAM)

C_FILES = $(wildcard *.c)
S_FILES = $(wildcard *.s)

FILES = $(C_FILES) $(S_FILES)

O_FILES = $(foreach file, $(C_FILES), $(file:.c=.o)) \
		  $(foreach file, $(S_FILES), $(file:.s=.o))

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	$(CC) -x assembler-with-cpp -c $(CFLAGS) -o $@ $<

$(PROGRAM): $(O_FILES)
	$(CC) $(CFLAGS) -o '$@' $^
	strip -s '$@'

test: $(PROGRAM)
	./$(PROGRAM)

clean: $(PROGRAM)
	rm '$<' $(O_FILES)


print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
