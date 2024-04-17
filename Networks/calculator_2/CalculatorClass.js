class IpCalculator {
  constructor(ipAddress, subnetMask) {
    this.ipAddress = ipAddress;
    this.subnetMask = subnetMask;
  }

  // Метод для конвертации IP адреса в двоичную форму
  ipToBinary() {
    // Разделение IP адреса на октеты
    const octets = this.ipAddress.split(".");

    // Преобразование каждого октета в двоичное представление и объединение их в строку
    const binaryIp = octets
      .map((octet) => {
        // Преобразуем октет в двоичное представление и дополняем его нулями до 8 символов
        return parseInt(octet).toString(2).padStart(8, "0");
      })
      .join(".");

    return binaryIp;
  }

  // Метод для конвертации маски подсети в двоичную форму
  subnetMaskToBinary() {
    // Разделение маски подсети на октеты
    const octets = this.subnetMask.split(".");

    // Преобразование каждого октета в двоичное представление и объединение их в строку
    const binarySubnetMask = octets
      .map((octet) => {
        // Преобразуем октет в двоичное представление и дополняем его нулями до 8 символов
        return parseInt(octet).toString(2).padStart(8, "0");
      })
      .join(".");

    return binarySubnetMask;
  }

  // Метод для вычисления сетевого адреса
  calculateNetworkAddress() {
    // Разделение IP адреса и маски подсети на отдельные части
    const ipParts = this.ipAddress.split(".");
    const subnetParts = this.subnetMask.split(".");

    // Вычисление сетевого адреса
    const networkAddressParts = [];
    for (let i = 0; i < 4; i++) {
      networkAddressParts.push(parseInt(ipParts[i]) & parseInt(subnetParts[i]));
    }

    // Преобразование массива чисел в строку IP адреса
    const networkAddress = networkAddressParts.join(".");

    return networkAddress;
  }

  calculateBroadcastAddress() {
    // Разделение IP адреса и маски подсети на отдельные части
    const ipParts = this.ipAddress.split(".").map((part) => parseInt(part));
    const subnetParts = this.subnetMask
      .split(".")
      .map((part) => parseInt(part));

    // Вычисление широковещательного адреса
    const broadcastAddressParts = [];
    for (let i = 0; i < 4; i++) {
      broadcastAddressParts.push(ipParts[i] | (subnetParts[i] ^ 255));
    }

    // Преобразование массива чисел в строку IP адреса
    const broadcastAddress = broadcastAddressParts.join(".");

    return broadcastAddress;
  }

  // Метод для определения количества доступных хостов в подсети
  calculateAvailableHosts() {
    // Разделение маски подсети на отдельные части
    const subnetParts = this.subnetMask.split(".");

    // Вычисление числа единиц в обратной маске подсети
    const numOnes = subnetParts.reduce((total, part) => {
      const binaryPart = parseInt(part).toString(2);
      return total + binaryPart.split("1").length - 1;
    }, 0);

    // Вычисление числа доступных хостов
    const availableHosts = Math.pow(2, 32 - numOnes) - 2;

    return availableHosts;
  }

  // Метод для определения класса IP адреса
  determineIpClass() {
    // Разделение IP адреса на отдельные части
    const ipParts = this.ipAddress.split(".");

    // Получение первого октета
    const firstOctet = parseInt(ipParts[0]);

    // Проверка диапазона первого октета и определение класса IP адреса
    if (firstOctet >= 1 && firstOctet <= 126) {
      return "A";
    } else if (firstOctet >= 128 && firstOctet <= 191) {
      return "B";
    } else if (firstOctet >= 192 && firstOctet <= 223) {
      return "C";
    } else if (firstOctet >= 224 && firstOctet <= 239) {
      return "D";
    } else if (firstOctet >= 240 && firstOctet <= 255) {
      return "E";
    } else if (this.ipAddress == "127.0.0.1") {
      return "Local";
    } else {
      return "Unknown";
    }
  }

  // Метод для получения минимального хоста
  calculateMinimumHost() {
    // Разделение сетевого адреса на отдельные части
    const networkParts = this.calculateNetworkAddress().split(".");

    // Увеличение последнего октета сетевого адреса на 1
    networkParts[3] = parseInt(networkParts[3]) + 1;

    // Преобразование массива чисел в строку IP адреса
    const minHost = networkParts.join(".");

    return minHost;
  }

  // Метод для получения максимального хоста
  calculateMaximumHost() {
    // Разделение широковещательного адреса на отдельные части
    const broadcastParts = this.calculateBroadcastAddress().split(".");

    // Уменьшение последнего октета широковещательного адреса на 1
    broadcastParts[3] = parseInt(broadcastParts[3]) - 1;

    // Преобразование массива чисел в строку IP адреса
    const maxHost = broadcastParts.join(".");

    return maxHost;
  }


   // Метод для расчета подсетей
   calculateSubnets(numSubnets) {
    // Разделение маски подсети на отдельные части
    const subnetParts = this.subnetMask.split(".").map((part) => parseInt(part));

    // Вычисление числа единиц в обратной маске подсети
    const numOnes = subnetParts.reduce((total, part) => {
      const binaryPart = parseInt(part).toString(2);
      return total + binaryPart.split("1").length - 1;
    }, 0);

    // Расчет числа доступных подсетей
    const availableSubnets = Math.pow(2, numSubnets);

    // Вычисление новой длины префикса подсети
    const newPrefixLength = numOnes + numSubnets;

    // Вычисление размера каждой подсети
    const subnetSize = Math.pow(2, 32 - newPrefixLength);

    // Вычисление сетевых адресов для каждой подсети
    const subnets = [];
    let networkAddress = this.calculateNetworkAddress();
    for (let i = 0; i < availableSubnets; i++) {
      subnets.push({
        networkAddress: networkAddress,
        broadcastAddress: this.calculatesubBroadcastAddress(networkAddress, newPrefixLength),
        subnetMask: this.subnetMask,
        prefixLength: newPrefixLength
      });

      // Переход к следующему сетевому адресу
      networkAddress = this.incrementIpAddress(networkAddress, subnetSize);
    }

    return subnets;
  }

  // Метод для увеличения IP адреса на заданное количество хостов
  incrementIpAddress(ipAddress, numHosts) {
    const ipParts = ipAddress.split(".").map((part) => parseInt(part));
    let increment = numHosts;
    for (let i = ipParts.length - 1; i >= 0 && increment > 0; i--) {
      ipParts[i] += increment;
      increment = Math.floor(ipParts[i] / 256);
      ipParts[i] %= 256;
    }
    return ipParts.join(".");
  }

  // Метод для вычисления широковещательного адреса заданной подсети
  calculatesubBroadcastAddress(networkAddress, prefixLength) {
    // Разделение сетевого адреса на отдельные части
    const networkParts = networkAddress.split(".").map((part) => parseInt(part));

    // Вычисление широковещательного адреса
    const broadcastParts = [];
    for (let i = 0; i < 4; i++) {
      broadcastParts.push(networkParts[i] | (255 >> (32 - prefixLength)));
    }

    // Преобразование массива чисел в строку IP адреса
    const broadcastAddress = broadcastParts.join(".");

    return broadcastAddress;
  }
}

