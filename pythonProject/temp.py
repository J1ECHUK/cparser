# import requests
#
# url = 'http://localhost:5000/'
# response = requests.get(url)
#
# print(response.text)



import socket

hostname = '127.0.0.1'
port = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((hostname, port))

    request = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\n\r\n"
    s.send(request.encode())



    while True:
            data = s.recv(1024)
            if not data:
                break
            print(data.decode(), end='')

    response = s.recv(1024)

    print(response.decode())
