import socket
import Huffman
from os.path import getsize

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = "127.0.0.1"
port = 3554
clientSocket.connect((ip, port))
print("Gniazdo polaczono z adresem", ip, ":", port)

def data_packages(data, n):
    chunks=[data[i:i + n] for i in range(0, len(data), n)]
    return chunks

file = open("wiadomosc.txt", "r")
DATA_SIZE= ''
data = ''
for line in file:
    DATA_SIZE=data
    data += line
chunked = (list(data_packages(data, 128)))
for i in range(len(chunked)):
    package = Huffman.coding(chunked[i]).encode("ascii")
    clientSocket.send(package)
    print('wyslano paczke numer: ',i+1,)
clientSocket.send("END".encode("ascii"))
dataFromServer = clientSocket.recv(1024).decode("ascii")
print(dataFromServer)
filename= 'wiadomosc.txt'
rozmiar_przeslane=round(len(DATA_SIZE)/ 1024, 2)
FILE_SIZE=round(getsize(filename) / 1024, 2)
kompresja=round((1 - rozmiar_przeslane / FILE_SIZE) * 100, 2)
print("Rozmiar przetransmitowanych danych:{}kB".format(rozmiar_przeslane))
print("Rozmiar pliku przed kompresją:     {}kB".format(FILE_SIZE))
print("Poziom kompresji:                  {}%".format(kompresja))