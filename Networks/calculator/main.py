from IPCalculator import *

while True:

  ip = input("Введите IP: ")
  if not validate_ip(ip):
    print("Неверный IP, попробуйте еще раз")
    continue

  netmask = input("Введите маску: ")
  if not validate_netmask(netmask):
    print("Неверная маска, попробуйте еще раз")
    continue
    
  break # выходим, если данные корректны

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
