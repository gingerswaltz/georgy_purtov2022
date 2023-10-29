import ipaddress

def main():
    print("Добро пожаловать в калькулятор IP-адресов!")
    while True:
        choice = input("Выберите действие (1 - Рассчитать подсеть, 2 - Выход): ")
        if choice == '1':
            calculate_subnet()
        elif choice == '2':
            break
        else:
            print("Неправильный выбор. Пожалуйста, выберите 1 или 2.")

def calculate_subnet():
    ip = input("Введите IP-адрес (в формате x.x.x.x): ")
    netmask = input("Введите маску подсети (в формате x.x.x.x): ")
    
    try:
        network = ipaddress.IPv4Network(f"{ip}/{netmask}", strict=False)
        print(f"Сетевой адрес: {network.network_address}")
        print(f"Широковещательный адрес: {network.broadcast_address}")
        print(f"Количество хостов в подсети: {network.num_addresses - 2}")
    except ValueError:
        print("Неправильный IP-адрес или маска подсети. Пожалуйста, попробуйте снова.")

if __name__ == "__main__":
    main()
