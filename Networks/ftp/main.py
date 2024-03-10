import os
import socket
import time

class FTPServer:
    def __init__(self, host='127.0.0.1', port=21):
        self.host = host
        self.port = port
        self.server_socket = None
        self.data_socket = None
        self.data_port = 20  # Порт для передачи данных
        self.directory = '.'  # Изначально устанавливаем текущий каталог

    def start(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(1)
        print(f"FTP Server started on {self.host}:{self.port}")

        while True:
            client_socket, client_address = self.server_socket.accept()
            print(f"Connection established from {client_address[0]}:{client_address[1]}")
            self.handle_client(client_socket)

    def handle_client(self, client_socket):
        client_socket.send("220 Welcome to FTP Server\r\n".encode())

        while True:
            request = client_socket.recv(1024).decode().strip()
            if not request:
                break
            print(f"Received command: {request}")
            command = request.split()[0].upper()

            if command == "USER":
                self.handle_user(client_socket, request)
            elif command == "PASS":
                self.handle_pass(client_socket, request)
            elif command == "PWD":
                self.handle_pwd(client_socket)
            elif command == "CWD":
                self.handle_cwd(client_socket, request)
            elif command == "LIST": 
                self.handle_list(client_socket)
            elif command == "RETR":
                if len(request.split()) > 1:
                    self.handle_retr(client_socket, request)
                else:
                    client_socket.send("501 Syntax error in parameters or arguments.\r\n".encode())
            elif command == "STOR":
                if len(request.split()) > 1:
                    self.handle_stor(client_socket, request)
                else:
                    client_socket.send("501 Syntax error in parameters or arguments.\r\n".encode())
            elif command == "DELE":
                self.handle_dele(client_socket, request)
            elif command == "MKD":
                self.handle_mkd(client_socket, request)
            elif command == "RMD":
                self.handle_rmd(client_socket, request)
            elif command == "RNFR":
                self.handle_rnfr(client_socket, request)
            elif command == "RNTO":
                self.handle_rnto(client_socket, request)
            elif command == "SYST":
                self.handle_syst(client_socket)
            elif command == "TYPE":
                self.handle_type(client_socket, request)
            elif command == "PORT":
                self.handle_port(client_socket, request)
            elif command == "QUIT":
                client_socket.send("221 Goodbye.\r\n".encode())
                break
            else:
                client_socket.send("502 Command not implemented.\r\n".encode())


    def handle_type(self, client_socket, request):
        data_type = request.split(' ')[1].strip()
        if data_type.upper() == "A":
            # Установка ASCII режима передачи данных
            client_socket.send("200 Switching to ASCII mode.\r\n".encode())
        elif data_type.upper() == "I":
            # Установка Binary (или Image) режима передачи данных
            client_socket.send("200 Switching to Binary mode.\r\n".encode())
        else:
            # Неизвестный тип данных
            client_socket.send("504 Command not implemented for that parameter.\r\n".encode())

    def handle_user(self, client_socket, request):
        username = request.split(' ')[1].strip()
        if username.lower() == "anonymous":
            client_socket.send("331 Anonymous login allowed, send password.\r\n".encode())
        else:
            client_socket.send("530 Only anonymous login is allowed.\r\n".encode())

    def handle_pass(self, client_socket, request):
        # В случае анонимного доступа без пароля
        client_socket.send("230 Login successful.\r\n".encode())

    def handle_pwd(self, client_socket):
        current_directory = os.getcwd()
        client_socket.send(f"257 \"{current_directory}\" is the current directory.\r\n".encode())
    
    def handle_port(self, client_socket, request):
        # Извлечение IP-адреса и порта из команды PORT
        port_args = request.split(' ')[1].split(',')
        ip_address = '.'.join(port_args[:4])
        port_number = (int(port_args[4]) << 8) + int(port_args[5])

        # Установка активного соединения с клиентом
        data_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        data_socket.connect((ip_address, port_number))

        # Отправка клиенту сообщения о успешном установлении соединения
        client_socket.send("200 PORT command successful.\r\n".encode())

        return data_socket

    def handle_cwd(self, client_socket, request):
        try:
            directory = request.split(' ')[1].strip()
            # Проверяем, начинается ли путь с символа '/'
            if directory.startswith('/'):
                # Если начинается, удаляем его
                directory = directory[1:]
            if directory:
                os.chdir(directory)
                self.directory = directory  # Устанавливаем текущий каталог
                client_socket.send(f"250 Directory changed to {directory}\r\n".encode())
            else:
                client_socket.send("501 No directory specified.\r\n".encode())
        except FileNotFoundError:
            client_socket.send("550 Directory not found.\r\n".encode())
        except OSError as e:
            print(e)
            client_socket.send("550 Requested action not taken.\r\n".encode())


    def handle_list(self, client_socket):
        try:
            directory_list = os.listdir(self.directory)  # Получаем содержимое текущего каталога
            response = "150 Here comes the directory listing.\r\n"
            client_socket.send(response.encode())
            for item in directory_list:
                item_path = os.path.join(self.directory, item)  # Используем текущий каталог для формирования полного пути
                item_type = "d" if os.path.isdir(item_path) else "-"
                item_size = os.path.getsize(item_path) if os.path.isfile(item_path) else 0
                item_mtime = os.path.getmtime(item_path)
                item_time = time.strftime('%Y%m%d%H%M%S', time.gmtime(item_mtime))

                response_item = f"{item_type}{' '*8}{item_size}{' '*8}{item_time}{' '*8}{item}\r\n"
                client_socket.send(response_item.encode())
            client_socket.send("226 Directory send OK.\r\n".encode())
        except FileNotFoundError:
            client_socket.send("550 Directory not found.\r\n".encode())




    def handle_retr(self, client_socket, request):
        filename = request.split(' ')[1].strip()
        try:
            with open(filename, 'rb') as file:
                client_socket.send("150 Opening data connection.\r\n".encode())
                data = file.read(1024)
                while data:
                    client_socket.send(data)
                    data = file.read(1024)
            client_socket.send("226 Transfer complete.\r\n".encode())
        except FileNotFoundError:
            client_socket.send("550 File not found.\r\n".encode())

    def handle_stor(self, client_socket, request):
        filename = request.split(' ')[1].strip()
        try:
            with open(filename, 'wb') as file:
                client_socket.send("150 Opening data connection.\r\n".encode())
                data = client_socket.recv(1024)
                while data:
                    file.write(data)
                    data = client_socket.recv(1024)
            client_socket.send("226 Transfer complete.\r\n".encode())
        except Exception as e:
            print(e)
            client_socket.send("450 Requested file action not taken.\r\n".encode())

    def handle_dele(self, client_socket, request):
        filename = request.split(' ')[1].strip()
        try:
            os.remove(filename)
            client_socket.send(f"250 {filename} deleted successfully.\r\n".encode())
        except FileNotFoundError:
            client_socket.send(f"550 {filename}: No such file or directory.\r\n".encode())
        except Exception as e:
            print(e)
            client_socket.send("450 Requested file action not taken.\r\n".encode())

    def handle_mkd(self, client_socket, request):
        directory_name = request.split(' ')[1].strip()
        try:
            os.mkdir(directory_name)
            client_socket.send(f"257 \"{directory_name}\" created successfully.\r\n".encode())
        except FileExistsError:
            client_socket.send(f"521 \"{directory_name}\" already exists.\r\n".encode())
        except Exception as e:
            print(e)
            client_socket.send("550 Requested action not taken.\r\n".encode())

    def handle_rmd(self, client_socket, request):
        directory_name = request.split(' ')[1].strip()
        try:
            os.rmdir(directory_name)
            client_socket.send(f"250 \"{directory_name}\" removed successfully.\r\n".encode())
        except FileNotFoundError:
            client_socket.send(f"550 \"{directory_name}\": No such directory.\r\n".encode())
        except OSError as e:
            print(e)
            client_socket.send(f"550 \"{directory_name}\": Directory not empty or permission denied.\r\n".encode())

    def handle_rnfr(self, client_socket, request):
        old_name = request.split(' ')[1].strip()
        try:
            # Проверяем, существует ли файл или директория с указанным именем
            if os.path.exists(old_name):
                # Если существует, отправляем клиенту код "350 Requested file action pending further information."
                client_socket.send("350 File exists, ready for destination name.\r\n".encode())
                # Сохраняем старое имя для дальнейшего использования
                self.old_name = old_name
            else:
                # Если файл или директория не существует, отправляем клиенту код "550 Requested action not taken."
                client_socket.send(f"550 \"{old_name}\": No such file or directory.\r\n".encode())
        except Exception as e:
            print(e)
            client_socket.send("450 Requested file action not taken.\r\n".encode())

    def handle_rnto(self, client_socket, request):
        new_name = request.split(' ')[1].strip()
        try:
            # Проверяем, было ли установлено исходное имя для переименования
            if hasattr(self, 'old_name'):
                # Переименовываем файл или директорию
                os.rename(self.old_name, new_name)
                # Очищаем сохраненное старое имя
                delattr(self, 'old_name')
                # Отправляем клиенту код "250 Requested file action okay, completed."
                client_socket.send(f"250 \"{new_name}\" renamed successfully.\r\n".encode())
            else:
                # Если исходное имя не было установлено, отправляем клиенту код "503 Bad sequence of commands."
                client_socket.send("503 Bad sequence of commands.\r\n".encode())
        except FileNotFoundError:
            client_socket.send(f"550 \"{self.old_name}\": No such file or directory.\r\n".encode())
        except Exception as e:
            print(e)
            client_socket.send("450 Requested file action not taken.\r\n".encode())

    def handle_syst(self, client_socket):
        system_info = "215 UNIX Type: L8\r\n"  # Информация о системе на сервере
        client_socket.send(system_info.encode())

if __name__ == "__main__":
    ftp_server = FTPServer()
    ftp_server.start()
