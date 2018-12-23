CC=gcc
BIN = cache

HEADER_DIR = ./header
SRC_DIR = ./src
OBJ_DIR = ./src/obj

CFLAGS=-I $(HEADER_DIR)

_DEPS = cache.h cache_func.h cache_util.h
DEPS = $(patsubst %,$(HEADER_DIR)/%, $(_DEPS)) 

_OBJ = cache.o cache_func.o cache_util.o
OBJ = $(patsubst %,$(OBJ_DIR)/%, $(_OBJ))

LIBS = -lm

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)  

${OBJ_DIR}/%.o : $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c $< -o $@  $(CFLAGS) 

.PHONY : clean
clean :
	-rm $(BIN) $(OBJ_DIR)/*.o	