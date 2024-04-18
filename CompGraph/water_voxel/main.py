import numpy as np

class VoxelWater:
    def __init__(self, width, height, depth):
        self.width = width
        self.height = height
        self.depth = depth
        self.grid = np.zeros((width, height, depth))
        self.damping = 0.99  # коэффициент затухания
        self.gravity = 9.8   # ускорение свободного падения
        self.dt = 0.1        # временной шаг симуляции

    def apply_gravity(self):
        # Применяем гравитацию к каждому элементу массива независимо
        for x in range(self.width):
            for y in range(self.height):
                for z in range(self.depth):
                    self.grid[x, y, z] -= self.gravity * self.dt

    def apply_damping(self):
        self.grid *= self.damping

    def apply_diffusion(self):
        # Диффузия по вертикали
        for z in range(self.depth):
            for x in range(self.width):
                for y in range(1, self.height):
                    avg = (self.grid[x, y - 1, z] + self.grid[x, y, z]) / 2
                    self.grid[x, y - 1, z] = avg
                    self.grid[x, y, z] = avg

        # Диффузия по вертикали
        for z in range(self.depth):
            for y in range(1, self.height):
                for x in range(self.width):
                    avg = (self.grid[x, y - 1, z] + self.grid[x, y, z]) / 2
                    self.grid[x, y - 1, z] = avg
                    self.grid[x, y, z] = avg

    def simulate_step(self):
        self.apply_gravity()
        self.apply_damping()
        self.apply_diffusion()

    def splash(self, x, y, z, velocity):
        if 0 <= x < self.width and 0 <= y < self.height and 0 <= z < self.depth:
            # Добавляем скорость только в верхние слои воды (заданный z)
            for i in range(z, self.depth):
                self.grid[x][y][i] = velocity

    def __str__(self):
        return "VoxelWater[width={}, height={}, depth={}]".format(self.width, self.height, self.depth)

import pygame
import random

# Параметры окна
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
FPS = 60

# Параметры воды
WATER_WIDTH = 100
WATER_HEIGHT = 100
WATER_DEPTH = 20

# Цвета
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)

# Создание экземпляра класса VoxelWater
water = VoxelWater(WATER_WIDTH, WATER_HEIGHT, WATER_DEPTH)

# Инициализация Pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
clock = pygame.time.Clock()

running = True
splash_velocity = 20

# Цикл событий Pygame
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(WHITE)

    # Случайное стекание воды
    for x in range(WATER_WIDTH):
        for y in range(WATER_HEIGHT):
            for z in range(WATER_DEPTH):
                if water.grid[x][y][z] > 0:
                    rand_x = random.randint(-1, 1)
                    rand_y = random.randint(-1, 1)
                    rand_z = random.randint(-1, 1)
                    new_x = min(max(x + rand_x, 0), WATER_WIDTH - 1)
                    new_y = min(max(y + rand_y, 0), WATER_HEIGHT - 1)
                    new_z = min(max(z + rand_z, 0), WATER_DEPTH - 1)
                    water.grid[new_x][new_y][new_z] = water.grid[x][y][z]
                    water.grid[x][y][z] = 0

    # Шаг симуляции воды
    water.simulate_step()

    # Отображение воды
    for x in range(WATER_WIDTH):
        for y in range(WATER_HEIGHT):
            for z in range(WATER_DEPTH):
                if water.grid[x][y][z] > 0:
                    pygame.draw.rect(screen, BLUE, (x * (WINDOW_WIDTH // WATER_WIDTH),
                                                    y * (WINDOW_HEIGHT // WATER_HEIGHT),
                                                    WINDOW_WIDTH // WATER_WIDTH,
                                                    WINDOW_HEIGHT // WATER_HEIGHT))

    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
