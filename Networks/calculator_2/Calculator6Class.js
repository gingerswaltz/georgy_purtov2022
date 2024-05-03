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

  getFullIPv6() {
    // Разбиваем IPv6 адрес на группы по два символа
    const groups = this.ip.split(":");

    // Создаем массив для хранения полных групп адреса
    const fullGroups = [];

    // Переменная для отслеживания количества пустых групп
    let emptyGroupIndex = -1;

    // Проходим по каждой группе адреса
    for (let i = 0; i < groups.length; i++) {
      // Если текущая группа пустая
      if (groups[i] === "") {
        // Запоминаем индекс пустой группы
        emptyGroupIndex = i;
        // Пропускаем текущую итерацию цикла
        continue;
      }

      // Дополняем группу нулями до четырех символов
      const paddedGroup = ("0000" + groups[i]).slice(-4);

      // Преобразуем в верхний регистр и добавляем в массив полных групп
      fullGroups.push(paddedGroup.toUpperCase());
    }

    // Вставляем недостающие нули в пустую группу, если она есть
    if (emptyGroupIndex !== -1) {
      // Вставляем недостающие нули перед индексом пустой группы
      fullGroups.splice(
        emptyGroupIndex,
        0,
        ...Array(8 - fullGroups.length).fill("0000")
      );
    }

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

  getAddressType() {
    const ipv6 = this.ip.toLowerCase(); // Приводим адрес к нижнему регистру для унификации
    const compressedIPv6 = this.getCompressedIPv6().toLowerCase(); // Получаем сжатую запись IPv6 адреса

    // Проверяем типы адресов
    if (ipv6 === "::1" || compressedIPv6 === "::1") {
      return "Loopback";
    } else if (ipv6.startsWith("ff") || compressedIPv6.startsWith("ff")) {
      return "Multicast";
    } else if (ipv6.includes(":")) {
      if (ipv6.startsWith("fe80:") || compressedIPv6.startsWith("fe80:")) {
        return "Link-local";
      } else if (ipv6.startsWith("fc") || compressedIPv6.startsWith("fc")) {
        return "Unique Local";
      } else if (ipv6.startsWith("fd") || compressedIPv6.startsWith("fd")) {
        return "Unique Local";
      } else {
        return "Global";
      }
    } else if (ipv6 === "::" || compressedIPv6 === "::") {
      return "Unspecified";
    } else {
      return "Unicast";
    }
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

  calculateVLSM(subnetMaskLength) {
    const ipPrefix = this.getCompressedIPv6(); // Получаем сжатую запись IP префикса IP адреса

    const subnetsCount = 2 ** (subnetMaskLength - 32); // Исправление здесь
    const subnets = [];

    for (let i = 0; i < subnetsCount; i++) {
      // Генерируем номер подсети в формате шестнадцатеричного числа
      const subnetNumberHex = (i * 2 ** (64 - subnetMaskLength)).toString(16);

      // Дополняем номер подсети нулями до 8 символов (IPv6 имеет 8 групп)
      const paddedSubnetNumberHex = subnetNumberHex.padStart(8, "0");

      // Убираем лишние нули
      const trimmedSubnetNumberHex = paddedSubnetNumberHex.replace(
        /(^|:)0+/,
        "$1"
      );

      // Собираем подсеть
      const subnet = ipPrefix + trimmedSubnetNumberHex + "/" + subnetMaskLength;
      subnets.push(subnet);
    }

    // Создаем строку с результатами
    let resultString = "<table><tr><th>Subnet</th></tr>";
    subnets.forEach(
      (subnet) => (resultString += "<tr><td>" + subnet + "</td></tr>")
    );
    resultString += "</table>";

    return resultString;
  }

  static summarizeIPv6Routes(routes) {
    // Функция для преобразования шестнадцатеричного числа в двоичную строку
    const hexToBinary = (hex) =>
      parseInt(hex, 16).toString(2).padStart(16, "0");

    // Функция для нахождения общего префикса двух IPv6-адресов
    const findCommonPrefix = (address1, address2) => {
      const blocks1 = address1.split(":");
      const blocks2 = address2.split(":");
      let commonPrefix = "";

      for (let i = 0; i < Math.min(blocks1.length, blocks2.length); i++) {
        const binaryBlock1 = hexToBinary(blocks1[i]);
        const binaryBlock2 = hexToBinary(blocks2[i]);

        const minBinaryLength = Math.min(
          binaryBlock1.length,
          binaryBlock2.length
        );

        for (let j = 0; j < minBinaryLength; j++) {
          if (binaryBlock1[j] === binaryBlock2[j]) {
            commonPrefix += binaryBlock1[j];
          } else {
            break;
          }
        }

        // Если найдено несовпадение битов, прерываем цикл
        if (commonPrefix.length !== (i + 1) * 16) {
          break;
        }
      }

      return commonPrefix;
    };

    // Находим общий префикс всех адресов
    let commonPrefix = routes.reduce((prefix, route) => {
      const routePrefix = route.split("/")[0];
      if (!prefix) return routePrefix;
      return findCommonPrefix(prefix, routePrefix);
    }, "");

    console.log("Common Prefix (binary):", commonPrefix);

    // Находим самую короткую маску префикса
    const shortestPrefixLength = Math.max(
      ...routes.map((route) => parseInt(route.split("/")[1]))
    );

    console.log("Shortest Prefix Length:", shortestPrefixLength);
    // Учитываем маску префикса
    const maskLength = shortestPrefixLength;
    const maskLengthBlocks = Math.floor(maskLength / 16);
    const maskLengthBits = maskLength % 16;
    const maskedCommonPrefix =
      commonPrefix.slice(0, maskLengthBlocks * 16) + "0".repeat(maskLengthBits);

    console.log("Masked Common Prefix (binary):", maskedCommonPrefix);

    // Переводим общий префикс обратно в шестнадцатеричную форму
    let summarizedRoute = "";
    for (let i = 0; i < maskedCommonPrefix.length; i += 16) {
      const hexBlock = parseInt(
        maskedCommonPrefix.slice(i, i + 16),
        2
      ).toString(16);
      summarizedRoute += hexBlock + ":";
    }
    summarizedRoute = summarizedRoute.slice(0, -1); // Убираем лишний двоеточий

    console.log("Summarized Route (hexadecimal):", summarizedRoute);

    // Учитываем маску итогового результата
    summarizedRoute += `/${shortestPrefixLength}`;

    console.log("Summarized Route with prefix length:", summarizedRoute);

    return summarizedRoute;
  }
}

function summarizeIPv6Prefixes(prefixes) {
  // Если в массиве менее двух префиксов, нет необходимости выполнять суммирование
  if (prefixes.length < 2) {
    return prefixes;
  }

  // Функция для суммирования двух префиксов
  function summarize(prefix1, prefix2) {
    const parts1 = prefix1.split(":");
    const parts2 = prefix2.split(":");
    let commonBlocks = 0;
    for (let i = 0; i < 3; i++) {
      if (parts1[i] !== parts2[i]) {
        break;
      }
      commonBlocks++;
    }
    const lastBlock1 = parseInt(parts1[3], 16).toString(2).padStart(16, "0");
    const lastBlock2 = parseInt(parts2[3], 16).toString(2).padStart(16, "0");
    let matchingBits = 0;
    for (let i = 0; i < 16; i++) {
      if (lastBlock1[i] !== lastBlock2[i]) {
        break;
      }
      matchingBits++;
    }
    const summarizedBlock = lastBlock1.substr(0, matchingBits).padEnd(16, "0");
    const summarizedHex = parseInt(summarizedBlock, 2)
      .toString(16)
      .toUpperCase();
    const summarizedPrefix =
      parts1.slice(0, commonBlocks).join(":") +
      ":" +
      summarizedHex +
      "::/" +
      (commonBlocks * 16 + matchingBits);
    return summarizedPrefix;
  }

  // Суммируем каждую пару префиксов в массиве
  let summarizedPrefixes = [...prefixes];
  for (let i = 0; i < summarizedPrefixes.length; i++) {
    for (let j = i + 1; j < summarizedPrefixes.length; j++) {
      const summarized = summarize(
        summarizedPrefixes[i],
        summarizedPrefixes[j]
      );
      // Заменяем первый префикс в паре на суммарный результат, а второй удаляем из массива
      summarizedPrefixes[i] = summarized;
      summarizedPrefixes.splice(j, 1);
      // После удаления элемента из массива, нужно уменьшить счетчик j на 1
      j--;
    }
  }

  return summarizedPrefixes;
}
