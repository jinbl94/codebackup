TARGET=stars
OBJS=stars.o
CC=g++
FLAGS=-lGL -lGLU -lglut

defatult:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(FLAGS)
$(OBJS):%.o:%.cpp #%.h
	$(CC) -c $< -o $@ $(FLAGS)

.PHONY:clean cleanall
clean:
	@rm -r $(OBJS)

cleanall:
	@rm -r $(OBJS) $(TARGET)
