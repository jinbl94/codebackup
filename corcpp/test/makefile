TARGET=test
OBJS=test.o test1.o test2.o test3.o
CC=gcc

default:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
$(OBJS):%.o:%.c
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	@rm -f $(OBJS) $(TARGET)
