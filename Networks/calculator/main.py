from IPCalculator import *

# def main():
#   menu = """
# 1. Конвертация  
# 2. Получить информацию о сети
# 3. Проверить маску
# 4. Получить broadcast и local
# 5. Подсчет числа доступных хостов в сети
# 6. Получить следующий/предыдущий адрес в сети
# 7. Класс IP адреса
# 8. Разбиение сети на подсети
# 9. Разбиение сети по заданному кол-ву хостов
# 0. Exit
# """
#   while True:

#     print("\nIP Calculator")
#     print(menu)
#     option = input("Choose an option: ")

#     match option:
#       case '1':
#         ip = input("Enter IP address: ")
#         print(IPCalculator.ip_convert(ip))
      
#       case '2':  
#         ip = input("Enter IP address: ")
#         prefix = input("Enter prefix length: ")
#         net, mask = IPCalculator.network_info(ip, int(prefix))
#         print(f"Network: {net}")
#         print(f"Mask: {mask}")
      
#       case '3':
#         ip = input("Enter IP address: ")
#         subnet = input("Enter subnet in CIDR notation: ")
#         print(IPCalculator.check_subnet(ip, subnet))
      
#       case '4':
#         subnet = input("Enter subnet in CIDR notation: ")
#         bcast, local = IPCalculator.get_subnet_addrs(subnet)
#         print(f"Broadcast: {bcast}")
#         print(f"Local: {local}")

#       case '5':
#         ip = input("Enter IP address: ")
#         mask = input("Enter subnet mask: ")
#         print(IPCalculator.count_hosts(ip, mask))  

#       case '6':
#         ip = input("Enter IP address: ")
#         network = input("Enter network in CIDR notation: ")
#         print(f"Next IP: {IPCalculator.next_ip(ip, network)}")
#         print(f"Prev IP: {IPCalculator.prev_ip(ip, network)}")

#       case '7':
#         ip = input("Enter IP address: ")
#         print(IPCalculator.get_ip_class(ip))
      
#       case '8':
#         network = input("Enter network in CIDR format: ")
#         prefix = int(input("Enter new prefix length: "))
#         IPCalculator.split_subnets(network, prefix)

#       case '9':
#         network = input("Enter network in CIDR format: ") 
#         num_hosts = int(input("Enter number of hosts per subnet: "))
#         IPCalculator.split_by_hosts(network, num_hosts)
      
      
#       case '0':
#         break
      
#       case _:
#         print("Invalid option")

# if __name__ == '__main__':
#   main()






# Пример использования:
ip = input("Введите IP: ")
netmask = input("Введите Netmask: ")
hosts_per_subnet = input("Введите хостов: ")

network_address, subnet_mask = network_info(ip, netmask)

print("\nАдрес сети:", network_address)
print("Маска подсети:", subnet_mask)
broadcast_start, broadcast_end = calculate_broadcast_addresses(ip, netmask)
print(f"Преобразованный IP: {ip_convert(ip)}")
print("Широковещательный диапазон:", broadcast_start, "до", broadcast_end)
print("Номер узла:", calculate_host_number(ip, netmask))
print("Количество узлов в сети:", calculate_number_of_hosts(ip, netmask))
print("Класс IP адреса:", get_ip_class(ip), "," ,calculate_ip_class(ip))
print("Минимальный адрес узла:", calculate_host_min(ip, netmask))
print("Максимальный адрес узла:", calculate_host_max(ip, netmask))

split_by_hosts(ip, netmask, hosts_per_subnet)
