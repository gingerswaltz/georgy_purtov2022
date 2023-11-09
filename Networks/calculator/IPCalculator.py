import ipaddress
# Преобразования IP-адресов из десятичного формата в двоичный и наоборот. конвертирование как IPv4, так и IPv6 адреса.
def ip_convert(ip):
  ip = ipaddress.ip_address(ip)

  if ip.version == 4:
    # конвертируем IPv4
    if isinstance(ip, ipaddress.IPv4Address):
      return '{:08b}'.format(int(ip))
    else:
      return str(ipaddress.IPv4Address(int(ip, 2)))

  elif ip.version == 6:
    # конвертируем IPv6
    if isinstance(ip, ipaddress.IPv6Address):
      return '{:032b}'.format(int(ip))
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
  ip = ipaddress.ip_address(ip)
  network = ipaddress.ip_network(ip).supernet(new_prefix=prefix)
  
  network_address = str(network.network_address)
  subnet_mask = str(network.netmask)

  return network_address, subnet_mask

ip = "192.168.1.5"
prefix = 24

print(network_info(ip, prefix))

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
  
  broadcast_addr = str(ip_network.broadcast_address)
  local_addr = str(ip_network[-1])

  return broadcast_addr, local_addr

subnet = '192.168.1.0/24'

broadcast, local = get_subnet_addrs(subnet)

#Подсчет ч
# исла доступных хостов в сети на основе заданных IP адресов.
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