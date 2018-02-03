default:time_c time_s
time_c:time_c.c socket.h
	gcc time_c.c -o time_c
time_s:time_s.c socket.h passivesocket.h
	gcc time_s.c -o time_s
clean:
	@rm time_c time_s
