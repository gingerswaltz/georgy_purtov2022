import ipaddress
import math


# Преобразования IP-адресов из десятичного формата в двоичный и наоборот. конвертирование как IPv4, так и IPv6 адреса.
def ip_convert(ip):
    ip = ipaddress.ip_address(ip)

    if ip.version == 4:
        # конвертируем IPv4
        if isinstance(ip, ipaddress.IPv4Address):
            return '{:032b}'.format(int(ip))
        else:
            return str(ipaddress.IPv4Address(int(ip, 2)))

    elif ip.version == 6:
        # конвертируем IPv6
        if isinstance(ip, ipaddress.IPv6Address):
            return '{:0128b}'.format(int(ip))
        else:
            return str(ipaddress.IPv6Address(int(ip, 2)))



def get_ip_class(ip_addr):

  ip = ipaddress.ip_address(ip_addr)

  if ip.version == 4:
    return check_ipv4_class(ip_addr)
  else:
    return "IPv6 address"

def check_ipv4_class(ip_addr):

  octets = ip_addr.split('.')

  if int(octets[0]) in range(1,127): 
    return "Class A"
  elif int(octets[0]) in range(128,191):
    return "Class B"
  elif int(octets[0]) in range(192,223):
    return "Class C"
  elif int(octets[0]) in range(224,240):
    return "Class D"
  else:
    return "Class E"


# вычислениe сетевого адреса и маски подсети по заданному IP адресу и префиксу
def network_info(ip, prefix):
    try:
        ip = ipaddress.ip_address(ip)
        network = ipaddress.IPv4Network(f"{ip}/{prefix}", strict=False)
        network_address = str(network.network_address)
        subnet_mask = str(network.netmask)
        return network_address, subnet_mask
    except ValueError as e:
        return f"Ошибка: {e}"


# Подсчет числа доступных хостов в сети на основе заданных IP адресов.
def count_hosts(ip, mask):
  network = ipaddress.ip_network(f'{ip}/{mask}', strict=False)
  return network.num_addresses - 2

#Проверка принадлежности IP адреса к заданной подсети.#
def check_subnet(ip, subnet):
  try: 
    ipaddress.ip_address(ip) in ipaddress.ip_network(subnet, strict=False)
    return True
  except ValueError:
    return False

#Нахождение широковещательного и локального адресов подсети.

def get_subnet_addrs(subnet):
  ip_network = ipaddress.ip_network(subnet, strict=False)
  
  local_addr = str(ip_network.broadcast_address)
  broadcast_addr = str(ip_network[-1])

  return broadcast_addr, local_addr

#Подсчет числа доступных хостов в сети на основе заданных IP адресов.
def count_hosts(ip1, ip2):
  network = ipaddress.ip_network(ip1 + '/' + ip2, strict=False)
  hosts = network.num_addresses

  start_addr = int(network.network_address)
  end_addr = int(network.broadcast_address)

  used_addrs = end_addr - start_addr + 1

  return hosts - 2 - (used_addrs - 2)


# Вычисление следующего и предыдущего IP адресов в сети.

def next_ip(ip, network):
  ip = ipaddress.ip_address(ip)
  network = ipaddress.ip_network(network)

  if ip == network.broadcast_address:
    return None
  
  next_ip = ip + 1
  if next_ip not in network:
    return None

  return str(next_ip)

def prev_ip(ip, network):
  ip = ipaddress.ip_address(ip)
  network = ipaddress.ip_network(network)

  if ip == network.network_address:
    return None
  
  prev_ip = ip - 1
  if prev_ip not in network:
    return None
  
  return str(prev_ip)

# разбиение сети на подсети
def split_subnets(network, new_prefix):
  subnets = list(network.subnets(new_prefix=new_prefix))
  
  print(f"Split {network} into:")
  for subnet in subnets:
    print(subnet)


#  функция для разбиения сети на подсети по заданному количеству узлов (хостов) в каждой подсети
def split_by_hosts(ip, prefix, hosts):
  
   # Преобразуем IP к виду сетевого адреса
  network = ipaddress.ip_network(f"{ip}/{prefix}", strict=False)
  ip = str(network.network_address)
 
  hosts = int(hosts)
  network = ipaddress.ip_network(f"{ip}/{prefix}")
  prefix = 32 - int(math.ceil(math.log2(hosts + 2)))
  
  subnets = list(network.subnets(new_prefix=prefix))

  print(f"Разбиение {network}, маска /{prefix} подсетей с {hosts} адресами:")

  for subnet in subnets:
    print(subnet)




# другие функции
def calculate_broadcast_addresses(ip, netmask):
    try:
        network = ipaddress.IPv4Network(f'{ip}/{netmask}', strict=False)
        return str(network.network_address + 1), str(network.broadcast_address)
    except ValueError as e:
        return f"Ошибка: {e}"

def calculate_host_number(ip, netmask):
    try:
        network = ipaddress.IPv4Network(f'{ip}/{netmask}', strict=False)
        ip_address = ipaddress.IPv4Address(ip)
        int_ip = int(ip_address) - int(network.network_address)
        return str(int_ip)
    except ValueError as e:
        return f"Ошибка: {e}"

def calculate_number_of_hosts(ip, netmask):
    try:
        network = ipaddress.IPv4Network(f'{ip}/{netmask}', strict=False)
        return network.num_addresses - 2  # Exclude network and broadcast addresses
    except ValueError as e:
        return f"Ошибка: {e}"

def calculate_ip_class(ip):
    try:
        ip_address = ipaddress.IPv4Address(ip)
        if ip_address.is_private:
            return 'Private'
        elif ip_address.is_reserved:
            return 'Reserved'
        elif ip_address.is_multicast:
            return 'Multicast'
        elif ip_address.is_loopback:
            return 'Loopback'
        elif ip_address.is_link_local:
            return 'Link Local'
        elif ip_address.is_unspecified:
            return 'Unspecified'
        else:
            return 'Public'
    except ValueError as e:
        return f"Ошибка: {e}"

def calculate_host_min(ip, netmask):
    try:
        network = ipaddress.IPv4Network(f'{ip}/{netmask}', strict=False)
        return str(network.network_address + 1)
    except ValueError as e:
        return f"Ошибка: {e}"

def calculate_host_max(ip, netmask):
    try:
        network = ipaddress.IPv4Network(f'{ip}/{netmask}', strict=False)
        return str(network.broadcast_address - 1)
    except ValueError as e:
        return f"Ошибка: {e}"



def split_network_by_hosts(ip, prefix, hosts_per_subnet):
  
  # Проверка входных данных
  try:
    ip = ipaddress.IPv4Address(ip) 
  except ValueError:
    print("Неверный IP адрес")
    return

  try:
    prefix = int(prefix)
    if not (0 <= prefix <= 32):
      print("Префикс должен быть в диапазоне 0-32")
      return
  except ValueError:
    print("Префикс должен быть числом")
    return

  # Расчет подсетей нужного размера
  subnets = list(ipaddress.ip_network(f"{ip}/{prefix}").subnets(prefixlen_diff=32-prefix))
  
  while len(subnets) > 0:
    subnet = subnets.pop(0)
    hosts = subnet.num_addresses - 2 # исключаем сетевой и широковещательный
    
    if hosts >= hosts_per_subnet:
      print(f"Подсеть /{subnet.prefixlen}:")
      print(f"Адрес сети: {subnet.network_address}") 
      print(f"Маска: {subnet.netmask}")
      print(f"Первый адрес хоста: {subnet.network_address + 1}")
      print(f"Последний адрес хоста: {subnet.broadcast_address - 1}")
      print(f"Всего хостов: {hosts}")
      print()

  if len(subnets) > 0:
    print(f"Невозможно разбить на /{prefix} подсети по {hosts_per_subnet} хостов")