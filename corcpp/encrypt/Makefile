default:encrypt anylyse adjust
encrypt:encrypt.o
	g++ -o encrypt encrypt.o
encrypt.o:encrypt.c
	g++ -c encrypt.c
anylyse:anylyse.o
	g++ -o anylyse anylyse.o
anylyse.o:anylyse.c
	g++ -c anylyse.c
adjust:adjust.o
	g++ -o adjust adjust.o
adjust.o:adjust.c
	g++ -c adjust.c
clean:
	@rm -f encrypt.o anylyse.o adjust.o
cleanall:
	@rm -f encrypt.o encrypt anylyse.o anylyse adjust.o adjust
