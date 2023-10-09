import matplotlib.pyplot as plt

# Функция для кодирования методом 2B1Q
def encode_2B1Q(data):
    encoded_data = []
    for i in range(0, len(data), 2):
        symbol1 = data[i]
        symbol2 = data[i + 1]
        if symbol1 == 0 and symbol2 == 0:
            encoded_data.append(-2.5)
        elif symbol1 == 0 and symbol2 == 1:
            encoded_data.append(-0.833)
        elif symbol1 == 1 and symbol2 == 0:
            encoded_data.append(2.5)
        elif symbol1 == 1 and symbol2 == 1:
            encoded_data.append(0.833)
    return encoded_data

# Функция для преобразования строки в бинарную последовательность
def string_to_binary(text):
    binary_data = []
    for char in text:
        binary_char = format(ord(char), '08b')  # Преобразуем символ в 8-битное двоичное число
        binary_data.extend(map(int, binary_char))
    return binary_data

# Входная строка
input_string = "hello world"

# Преобразуем строку в бинарную последовательность
binary_data = string_to_binary(input_string)

# Кодируем бинарные данные методом 2B1Q
encoded_data = encode_2B1Q(binary_data)

# Визуализируем процесс кодирования
plt.figure(figsize=(15, 4))
plt.plot(range(len(binary_data)), binary_data, marker='o', label='Бинарные данные')
plt.step(range(0, len(binary_data), 2), encoded_data, where='mid', marker='o', label='Кодированные данные')
plt.xlabel('Биты')
plt.ylabel('Амплитуда')
plt.title('Физическое кодирование методом 2B1Q для строки "{}"'.format(input_string))
plt.legend()
plt.grid(True)
plt.show()
