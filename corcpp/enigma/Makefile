#ENIGMA
#this program is insist of two programs. one is enigma, the other order. anylyse is an asistant program.
#order is place in data/. and the file orders and key are also locate there.
#rotor.h is the class Rotor.
default:enigma data/order anylyse
enigma:enigma.o rotor.h
	g++ -o enigma enigma.o
enigma.o:enigma.c
	g++ -o enigma.o -c enigma.c
data/order:data/order.o
	g++ -o data/order data/order.o
data/order.o:data/order.c
	g++ -o data/order.o -c data/order.c
anylyse:anylyse.o
	g++ -o anylyse anylyse.o
anylyse.o:anylyse.c
	g++ -o anylyse.o -c anylyse.c
clean:
	@rm -f enigma.o data/order.o anylyse.o
cleanall:
	@rm -f enigma.o enigma data/order.o data/order anylyse.o anylyse

