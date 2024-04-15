import pygame
import random

# Размеры окна и ячейки пламени
MX = 500
MY = 550
S_FIRE = 1

# Изменение размеров окна
SX = MX * S_FIRE
SY = MY * S_FIRE

# Палитра цветов для отображения пламени
palette = []

def initialize_fire():
    """Инициализация массива пламени."""
    scr = []  # Создание пустого массива для хранения интенсивности пламени
    for y in range(MY):
        line = []  # Создание пустой строки для текущей строки пламени
        for x in range(MX):
            # Задаем интенсивность пламени для нижней линии и областей вокруг центра
            if y == MY - 1 and MX // 2 - 1 <= x <= MX // 2 + 1:
                line.append(300)
            elif y >= MY - 1 and MX // 2 - 300 <= x <= MX // 2 + 300:
                distance_from_center = abs(x - MX // 2)  # Расстояние от текущей позиции до центра по горизонтали
                color_index = 350 - (MY - 1 - y) * 1 - distance_from_center * 1  # Вычисление индекса цвета для текущего пикселя
                line.append(color_index)
            else:
                line.append(0)  # Иначе устанавливаем интенсивность пламени в 0
        scr.append(line)  # Добавляем строку в массив пламени
    return scr  # Возвращаем инициализированный массив пламени

def update_fire(scr):
    """Обновление состояния пламени."""
    for y in range(MY - 2, 0, -1):  # Обходим каждую строку пламени сверху вниз, кроме последней
        for x in range(1, MX - 1):  # Обходим каждый пиксель в строке, кроме крайних
            below_pixel = scr[y + 1][x]  # Значение пикселя под текущим пикселем (внизу)
            left_pixel = scr[y + 1][x - 1]  # Значение пикселя слева от текущего пиксела
            right_pixel = scr[y + 1][x + 1]  # Значение пикселя справа от текущего пиксела
            decay = random.randint(-1, 10)  # Генерация случайного затухания огня
            random_offset = random.randint(-2, 4)  # Генерация случайного смещения пламени влево или вправо
            new_index = max(0, below_pixel - decay - random_offset)  # Расчет нового индекса пикселя пламени
            new_index = max(new_index, left_pixel - decay)  # Учет затухания огня влево
            new_index = max(new_index, right_pixel - decay)  # Учет затухания огня вправо
            scr[y][x] = new_index  # Обновление значения пикселя пламени


def initialize_palette():
    global palette
    for i in range(256):
        if i < 85:
            r = int(255 * (i / 85.0))
            g = 0
            b = 0
        elif i < 170:
            r = 255
            g = int(255 * ((i - 85) / 85.0))
            b = 0
        else:
            r = 255
            g = 255
            b = int(255 * ((i - 170) / 85.0))
        palette.append((r, g, b))


def draw_fire(screen, scr):
    surface = pygame.Surface((MX, MY))  # Создаем временную поверхность для рисования пламени
    for y in range(MY):
        for x in range(MX):
            color_index = scr[y][x]
            color_index = max(0, min(color_index, 255))  # Ограничиваем индекс в пределах от 0 до 255
            color = palette[color_index]
            surface.set_at((x, y), color)  # Заливаем пиксель временной поверхности цветом

    # Масштабируем временную поверхность до размеров экрана и отображаем на экране
    screen.blit(pygame.transform.scale(surface, (SX, SY)), (0, 0))

def main():
    pygame.init()
    screen = pygame.display.set_mode((SX, SY))
    pygame.display.set_caption("Burning Flame")

    scr = initialize_fire()
    initialize_palette()

    clock = pygame.time.Clock()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        update_fire(scr)
        screen.fill((0, 0, 0))  # Очищаем экран перед каждой перерисовкой
        draw_fire(screen, scr)
        pygame.display.flip()
        clock.tick(30)  # Ограничиваем FPS до 30 кадров в секунду

    pygame.quit()

if __name__ == "__main__":
    main()
