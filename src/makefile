BUILD_DIR=../build/
EXECUTABLE_NAME=graph
CFLAGS=-Wall -Wextra -Wformat -Werror

all: $(BUILD_DIR)graph.o $(BUILD_DIR)calc.o $(BUILD_DIR)render.o $(BUILD_DIR)rpn.o $(BUILD_DIR)table.o $(BUILD_DIR)structs.o
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

$(BUILD_DIR)calc.o: calc.c calc.h defines.h
	$(CC) $(CFLAGS) -c calc.c -o $@

$(BUILD_DIR)render.o: render.c render.h defines.h
	$(CC) $(CFLAGS) -c render.c -o $@

$(BUILD_DIR)rpn.o: rpn.c rpn.h defines.h
	$(CC) $(CFLAGS) -c rpn.c -o $@

$(BUILD_DIR)table.o: table.c table.h defines.h
	$(CC) $(CFLAGS) -c table.c -o $@

$(BUILD_DIR)graph.o: graph.c defines.h
	$(CC) $(CFLAGS) -c graph.c -o $@

$(BUILD_DIR)structs.o: structs.c structs.h
	$(CC) $(CFLAGS) -c structs.c -o $@

clean:
	find ../build/ -name "*.o" -delete
	find ../build/ -name $(EXECUTABLE_NAME) -delete

rebuild: clean all