import socket
import Huffman

serverSocket = socket.socket()
ip = "127.0.0.1"
port = 3554
serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serverSocket.bind((ip, port))
print("Gniazdo ustawiono na adres", ip, ":", port)

serverSocket.listen()
while True:
    text = ''
    (clientConnection, clientAddress) = serverSocket.accept()
    while True:
        data = clientConnection.recv(1024).decode()
        if data == "END":
            msg = "Odpowiedz serwera:\nTransfer udany, zakanczanie polaczenia!"
            msgBytes = str.encode(msg)
            clientConnection.send(msgBytes)
            print("\nConnection closed.\n")
            break
        text += data

    serwer = Huffman.decoding(text)
    print(serwer)
    filename= 'serwer.txt'
    file = open("serwer.txt", "w")
    file.write(serwer)
    file.close()
    break
