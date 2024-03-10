import socket

class FTPClient:
    def __init__(self, host='127.0.0.1', port=21):
        self.host = host
        self.port = port
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def connect(self):
        self.client_socket.connect((self.host, self.port))
        print(self.client_socket.recv(1024).decode())

    def send_command(self, command):
        self.client_socket.send(command.encode())
        response = self.client_socket.recv(4096).decode()
        print(response)

    def login(self, username='anonymous', password=''):
        self.send_command('USER {}\r\n'.format(username))
        self.send_command('PASS {}\r\n'.format(password))

    def pwd(self):
        self.send_command('PWD\r\n')

    def cwd(self, directory):
        self.send_command('CWD {}\r\n'.format(directory))

    def list_files(self):
        self.send_command('LIST\r\n')

    def download_file(self, filename):
        self.send_command('RETR {}\r\n'.format(filename))

    def upload_file(self, filename):
        self.send_command('STOR {}\r\n'.format(filename))

    def delete_file(self, filename):
        self.send_command('DELE {}\r\n'.format(filename))

    def make_directory(self, directory):
        self.send_command('MKD {}\r\n'.format(directory))

    def remove_directory(self, directory):
        self.send_command('RMD {}\r\n'.format(directory))

    def rename_from(self, old_name):
        self.send_command('RNFR {}\r\n'.format(old_name))

    def rename_to(self, new_name):
        self.send_command('RNTO {}\r\n'.format(new_name))

    def system_info(self):
        self.send_command('SYST\r\n')

    def set_transfer_mode(self, mode):
        self.send_command('TYPE {}\r\n'.format(mode))

    def set_active_mode(self, host, port):
        self.send_command('PORT {}\r\n'.format(host, port))

    def quit(self):
        self.send_command('QUIT\r\n')
        self.client_socket.close()

if __name__ == "__main__":
    ftp_client = FTPClient()
    ftp_client.connect()
    ftp_client.login()
    ftp_client.pwd()
    ftp_client.cwd('/')
    ftp_client.list_files()
    ftp_client.download_file('example.txt')
    ftp_client.upload_file('example.txt')
    ftp_client.delete_file('example.txt')
    ftp_client.make_directory('test_directory')
    ftp_client.remove_directory('test_directory')
    ftp_client.rename_from('old_name.txt')
    ftp_client.rename_to('new_name.txt')
    ftp_client.system_info()
    ftp_client.set_transfer_mode('I')
    ftp_client.set_active_mode('127,0,0,1', 12345)
    ftp_client.quit()
