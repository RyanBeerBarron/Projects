CC=gcc
BIN = cache
TEST_BIN = test_cache_util test_cache_func

HEADER_DIR = ./header
SRC_DIR = ./src
OBJ_DIR = ./src/obj

TEST_DIR = ./test
TEST_OBJ_DIR = ./test/obj

CFLAGS=-I $(HEADER_DIR)

_DEPS = cache.h cache_func.h cache_util.h
DEPS = $(patsubst %,$(HEADER_DIR)/%, $(_DEPS)) 

_OBJ = cache.o cache_func.o cache_util.o
OBJ = $(patsubst %,$(OBJ_DIR)/%, $(_OBJ))

_TEST_OBJ = test_cache_util.o test_cache_func.o
TEST_OBJ = $(patsubst %,$(TEST_OBJ_DIR)/%, $(_TEST_OBJ))

LIBS = -lm
TEST_LIBS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)  

test_% : $(OBJ_DIR)/%.o $(TEST_OBJ_DIR)/test_%.o 
	$(CC) -o $@ $^ $(TEST_LIBS)
	./$@	

${OBJ_DIR}/%.o : $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c $< -o $@  $(CFLAGS) 

${TEST_OBJ_DIR}/%.o : $(TEST_DIR)/%.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

${TEST_DIR}/%.c : ${TEST_DIR}/%.check
		checkmk $^ > $@	

test : $(TEST_BIN)

.PHONY : clean
clean :
	-rm $(BIN) $(TEST_BIN) $(OBJ_DIR)/*.o $(TEST_OBJ_DIR)/*.o	