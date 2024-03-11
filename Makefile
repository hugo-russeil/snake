CC = gcc
CFLAGS = -Iinclude -O3
LDFLAGS = -lncurses
SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/snake: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	rm -f $(OBJECTS)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/* $(OBJ_DIR)/snake