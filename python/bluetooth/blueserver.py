#! /usr/bin/python
"""
A simple Python script to receive messages from a client over
Bluetooth using Python sockets (with Python 3.3 or above).
"""

import bluetooth
import threading

name = "echo"
UUID = "00001101-0000-1000-8000-00805F9B34FB"
hostMACAddress = "" # The MAC address of a Bluetooth adapter on the server. The server might have multiple Bluetooth adapters.
port = 0x1009 # 3 is an arbitrary choice. However, it must match the port used by the client.
backlog = 1
size = 1024
#s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
s.bind((hostMACAddress,port))
s.listen(backlog)

bluetooth.advertise_service(s, name, UUID)

class echoThread(threading.Thread):
    def __init__ (self,sock,client_info):
        threading.Thread.__init__(self)
        self.sock = sock
        self.client_info = client_info
    def run(self):
        try:
            while True:
                data = self.sock.recv(1024)
                print(self.client_info, "check data length")
                if len(data) == 0: break
                print(self.client_info, ": received [%s]" % data)
                self.sock.send(data)
                print(self.client_info, ": sent [%s]" % data)
        except IOError:
            pass
        self.sock.close()
        print(self.client_info, ": disconnected")

print("Starting server")

while True:
	client_sock, client_info = s.accept()
	print("Connection accept")
	echo = echoThread(client_sock, client_info)
	echo.setDaemon(True)
	echo.start()

s.close()
print("Program terminated")
