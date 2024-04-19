class IPv6Calculator {
  constructor(ip, subnetMask) {
    this.ip = ip;
    this.subnetMask = subnetMask;
    this.subnets = []; // Массив для хранения подсетей
  }

  // Метод для просмотра cжатой записи IPv6
  getCompressedIPv6() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Заменяем ведущие нули в каждой группе на пустую строку
    const compressedGroups = groups.map((group) => group.replace(/^0+/, ""));

    // Склеиваем группы с двоеточием
    const compressedIPv6 = compressedGroups.join(":");

    return compressedIPv6;
  }

  // Метод для просмотра полной записи IPv6
  getFullIPv6() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Дополняем каждую группу нулями до четырех символов
    const fullGroups = groups.map((group) => {
      const paddedGroup = ("0000" + group).slice(-4);
      return paddedGroup.toUpperCase(); // Преобразуем в верхний регистр
    });

    // Склеиваем группы с двоеточием
    const fullIPv6 = fullGroups.join(":");

    return fullIPv6;
  }

  // Метод для просмотра маски в битах
  getSubnetMaskBits() {
    // Разбиваем маску подсети на группы по два символа
    const groups = this.subnetMask.split(":");

    // Преобразуем каждую группу в двоичное представление
    const binaryGroups = groups.map((group) =>
      parseInt(group, 16).toString(2).padStart(16, "0")
    );

    // Склеиваем двоичные представления групп сетевой маски
    const binaryMask = binaryGroups.join("");

    // Подсчитываем количество установленных битов
    const subnetMaskBits = binaryMask.split("1").length - 1;

    return subnetMaskBits;
  }

  // Метод для просмотра полной маски
  getFullSubnetMask() {
    // Разбиваем маску подсети на группы по два символа
    const groups = this.subnetMask.split(":");

    // Дополняем каждую группу нулями до четырех символов
    const fullGroups = groups.map((group) => {
      const paddedGroup = ("0000" + group).slice(-4);
      return paddedGroup.toUpperCase(); // Преобразуем в верхний регистр
    });

    // Склеиваем группы с двоеточием
    const fullSubnetMask = fullGroups.join(":");

    return fullSubnetMask;
  }

  getAddressIdentifier() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Дополняем каждую группу нулями до четырех символов
    const fullGroups = groups.map((group) => {
      const paddedGroup = ("0000" + group).slice(-4);
      return paddedGroup.toUpperCase(); // Преобразуем в верхний регистр
    });

    // Берем последние 4 группы для идентификатора адреса
    const identifierGroups = fullGroups.slice(-4);

    // Склеиваем группы с двоеточием
    const addressIdentifier = identifierGroups.join(":");

    // Добавляем маску подсети к идентификатору адреса
    const subnetMaskBits = this.getSubnetMaskBits();
    const addressWithMask = addressIdentifier + "/" + subnetMaskBits;

    return addressWithMask;
  }

  // Методы для просмотра префикса подсети
  getSubnetPrefix() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Дополняем каждую группу нулями до четырех символов и преобразуем в верхний регистр
    const fullGroups = groups.map((group) => {
      // Если группа содержит меньше четырех символов, дополняем нулями
      while (group.length < 4) {
        group = "0" + group;
      }
      return group.toUpperCase();
    });

    // Склеиваем группы с двоеточием
    const addressIdentifier = fullGroups.join(":");

    // Добавляем маску подсети к идентификатору адреса
    const subnetMaskBits = this.getSubnetMaskBits();
    const subnetPrefix = addressIdentifier + "/" + subnetMaskBits;

    return subnetPrefix;
  }

  // Методы для просмотра типа адреса
  getAddressType() {
    // Проверяем, является ли адрес Loopback Address
    if (this.ip === "::1") {
      return "Loopback Address";
    }
    const globalPrefix = "2000";
    const localPrefixes = ["fe80", "fc00"];
    const multicastPrefix = "ff00";

    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Проверяем префикс для определения типа адреса
    const firstGroup = parseInt(groups[0], 16);
    if (
      firstGroup >= parseInt(globalPrefix, 16) &&
      firstGroup < parseInt(globalPrefix, 16) + 0x2000
    ) {
      return "Глобальный";
    } else if (localPrefixes.includes(groups[0])) {
      return "Локальный";
    } else if (groups[0].startsWith(multicastPrefix)) {
      return "Многоадресный";
    } else {
      return "Неопределенный";
    }
  }

  getRangeStart() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Получаем биты маски подсети
    const subnetMaskBits = this.getSubnetMaskBits();

    // Если маска подсети равна 128, возвращаем текущий адрес
    if (subnetMaskBits === 128) {
      return this.ip;
    }

    // Вычисляем количество полных групп, затем дополняем нулями остаточные группы
    const fullGroups = Math.floor(subnetMaskBits / 16);
    const remainderBits = subnetMaskBits % 16;
    const startGroups = groups.slice(0, fullGroups);
    if (remainderBits > 0) {
      // Дополняем последнюю группу нулями до длины 4 символа
      const lastGroup = ("0000" + groups[fullGroups]).slice(-4);
      startGroups.push(lastGroup.padEnd(4, "0"));
    }

    // Заполняем оставшиеся группы нулями
    while (startGroups.length < 8) {
      startGroups.push("0000");
    }

    // Склеиваем группы с двоеточием и возвращаем начало диапазона
    return startGroups.join(":");
  }

  getRangeEnd() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Получаем биты маски подсети
    const subnetMaskBits = this.getSubnetMaskBits();

    // Если маска подсети равна 128, возвращаем текущий адрес
    if (subnetMaskBits === 128) {
      return this.ip;
    }

    // Вычисляем количество полных групп, затем дополняем единицами остаточные группы
    const fullGroups = Math.floor(subnetMaskBits / 16);
    const remainderBits = subnetMaskBits % 16;
    const endGroups = groups.slice(0, fullGroups);
    if (remainderBits > 0) {
      // Дополняем последнюю группу единицами до длины 4 символа
      const lastGroup = ("0000" + groups[fullGroups]).slice(-4);
      endGroups.push(lastGroup.padEnd(4, "f"));
    }

    // Заполняем оставшиеся группы единицами
    while (endGroups.length < 8) {
      endGroups.push("ffff");
    }

    // Склеиваем группы с двоеточием и возвращаем конец диапазона
    return endGroups.join(":");
  }
  
  calculateVLSM(subnets) {
    // Проверяем, является ли подсеть входным параметром в формате числа или строкой
    const numSubnets = isNaN(subnets) ? parseInt(subnets) : subnets;

    // Проверяем, является ли numSubnets числом
    if (isNaN(numSubnets)) {
      return "Ошибка: Количество подсетей должно быть числом.";
    }

    // Получаем информацию об исходной подсети
    const originalPrefix = this.getSubnetPrefix();
    const originalPrefixBits = parseInt(originalPrefix.split('/')[1]);

    // Рассчитываем новый префикс подсети для каждой новой подсети
    let newPrefixBits = originalPrefixBits + Math.log2(numSubnets);
    newPrefixBits = Math.ceil(newPrefixBits); // Округляем до ближайшего целого числа

    if (newPrefixBits > 128) {
        return "Ошибка: Невозможно разделить подсеть на запрошенное количество подсетей.";
    }

    const newPrefix = originalPrefix.split('/')[0] + '/' + newPrefixBits;

    // Рассчитываем количество /64 подсетей в каждой новой подсети
    const subnetsCount = Math.pow(2, 128 - newPrefixBits);

    // Генерируем новые подсети
    const newSubnets = [];
    const baseAddressParts = this.ip.split(":");
    const baseAddressNum = parseInt(baseAddressParts[baseAddressParts.length - 1], 16);
    for (let i = 0; i < numSubnets; i++) {
        const newAddressNum = baseAddressNum + i * subnetsCount;
        const newAddress = baseAddressParts.slice(0, baseAddressParts.length - 1).join(":") + ":" + newAddressNum.toString(16);
        const subnet = newAddress + '/' + newPrefixBits;
        newSubnets.push(subnet);
    }

    // Генерируем HTML-код таблицы с результатами
    let output = "<table>";
    output += "<tr><th>New Subnets</th><th>Subnet</th></tr>";
    newSubnets.forEach((subnet, index) => {
        output += `<tr><td>Subnet ${index + 1}</td><td>${subnet}</td></tr>`;
    });
    output += "</table>";

    return output;

    return output;
}





}
