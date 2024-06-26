class IpCalculator {
  constructor(ipAddress, subnetMask) {
    this.ipAddress = ipAddress;
    this.subnetMask = subnetMask;
    this.subnets = []; // Добавляем массив для хранения информации о подсетях
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
    // Проверка на маску подсети 255.255.255.255
    if (this.subnetMask === "255.255.255.255") {
      return 0;
    }
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

  // Добавляем метод для добавления информации о подсети
  addSubnet(name, hosts) {
    this.subnets.push({ name, hosts });
  }

  // Метод для расчета подсетей по VLSM
  calculateVLSM() {
    // Разбиваем доступные хосты на подсети
    let remainingHosts = this.calculateAvailableHosts() + 2; // +2 для сетевого и широковещательного адреса
    let currentAddress = this.calculateNetworkAddress()
      .split(".")
      .map((part) => parseInt(part));

    this.subnets.forEach((subnet, index) => {
      const subnetHosts = subnet.hosts + 2; // +2 для сетевого и широковещательного адреса
      // Проверяем, не превышает ли количество хостов в данной подсети оставшееся количество доступных хостов
      if (subnetHosts > remainingHosts) {
        throw new Error(`Недостаточно хостов для подсети '${subnet.name}'`);
      }

      const subnetMask = 32 - Math.ceil(Math.log2(subnetHosts));
      const subnetMaskBinary = "1"
        .repeat(subnetMask)
        .padEnd(32, "0")
        .match(/.{1,8}/g)
        .map((bin) => parseInt(bin, 2));

      // Рассчитываем диапазон подсети
      const subnetStart = currentAddress.slice();
      subnetStart[3] += 1;
      const subnetEnd = currentAddress.slice();
      subnetEnd[3] += Math.pow(2, 8 - (subnetMask % 8)) - 2;
      const usableRange = `${subnetStart.join(".")} - ${subnetEnd.join(".")}`;

      // Рассчитываем широковещательный адрес
      const broadcastAddress = subnetEnd.slice();
      broadcastAddress[3] += 1;

      // Рассчитываем обратную маску
      const wildcard = subnetMaskBinary.map((part) => 255 - part).join(".");

      // Добавляем информацию о подсети
      this.subnets[index].networkAddress = currentAddress.join(".");
      this.subnets[index].subnetMask = subnetMaskBinary.join(".");
      this.subnets[index].usableRange = usableRange;
      this.subnets[index].broadcast = broadcastAddress.join("."); // Добавляем broadcast адрес
      this.subnets[index].wildcard = wildcard;

      // Обновляем текущий адрес для следующей подсети
      currentAddress[3] = broadcastAddress[3] + 1;

      remainingHosts -= subnetHosts;
    });
  }
}

function calculateSupernet(networks) {
  // Функция для преобразования IP-адреса и маски в двоичный формат
  function toBinary(ip) {
    return ip.split('.').map(part => parseInt(part, 10).toString(2).padStart(8, '0')).join('');
  }

  // Функция для определения общих битов у сетей
  function findCommonBits(networksBinary) {
    const firstNetwork = networksBinary[0];
    let commonBits = 0;
    for (let i = 0; i < firstNetwork.length; i++) {
      if (networksBinary.every(network => network[i] === firstNetwork[i])) {
        commonBits++;
      } else {
        break;
      }
    }
    return commonBits;
  }

  // Преобразование сетей в двоичный формат
  const networksBinary = networks.map(network => {
    const [ip, mask] = network.split('/');
    return toBinary(ip).slice(0, parseInt(mask));
  });

  // Определение общих битов
  const commonBits = findCommonBits(networksBinary);

  // Формирование суммированного адреса сети
  const summarizedNetwork = networksBinary[0].slice(0, commonBits).padEnd(32, '0');
  const summarizedMask = '1'.repeat(commonBits).padEnd(32, '0');

  // Преобразование двоичного адреса обратно в десятичный формат
  const summarizedIP = `${parseInt(summarizedNetwork.slice(0, 8), 2)}.${parseInt(summarizedNetwork.slice(8, 16), 2)}.${parseInt(summarizedNetwork.slice(16, 24), 2)}.${parseInt(summarizedNetwork.slice(24), 2)}`;
  const summarizedCIDR = `/${commonBits}`;

  return `${summarizedIP}${summarizedCIDR}`;
}
