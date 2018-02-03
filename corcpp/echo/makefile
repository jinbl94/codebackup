default:echo_c echo_s
echo_c:echo_c.c socket.h
	gcc echo_c.c -o echo_c
echo_s:echo_s.c socket.h passivesocket.h
	gcc echo_s.c -o echo_s
clean:
	@rm echo_c echo_s

