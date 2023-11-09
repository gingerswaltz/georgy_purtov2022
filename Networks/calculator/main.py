import IPCalculator

def main():

  while True:
    
    print("\nIP Calculator")
    print("1. Convert IP")
    print("2. Get network info")
    print("3. Check subnet") 
    print("4. Get broadcast and local IPs")
    print("5. Count available hosts")
    print("6. Get next/previous IP")
    print("7. Get IP address class")
    print("0. Exit")

    option = input("Enter your choice: ")

    if option == '1':
      ip = input("Enter IP address: ")
      print(IPCalculator.ip_convert(ip))

    elif option == '2':
       ip = input("Enter IP address: ")
       prefix = input("Enter prefix length: ")
       net, mask = IPCalculator.network_info(ip, int(prefix))  
       print(f"Network: {net}")
       print(f"Mask: {mask}")

    elif option == '3':
       ip = input("Enter IP address: ")
       subnet = input("Enter subnet in CIDR notation: ")
       print(IPCalculator.check_subnet(ip, subnet))

    elif option == '4':
       subnet = input("Enter subnet in CIDR notation: ")
       broadcast, local = IPCalculator.get_subnet_addrs(subnet)  
       print(f"Broadcast: {broadcast}")
       print(f"Local: {local}") 

    elif option == '5':
       ip = input("Enter IP address: ")
       mask = input ("Enter subnet mask: ")
       print(IPCalculator.count_hosts(ip, mask))

    elif option == '6':
       ip = input("Enter IP address: ")
       network = input("Enter network in CIDR notation: ")
       print(f"Next IP: {IPCalculator.next_ip(ip, network)}")
       print(f"Previous IP: {IPCalculator.prev_ip(ip, network)}")
    
    elif option == '7':
     ip = input("Enter IP address: ")
     print(IPCalculator.get_ip_class(ip))
    
    elif option == '0':
        break
    
    else:
       print("Invalid option")

if __name__ == '__main__':
   main()