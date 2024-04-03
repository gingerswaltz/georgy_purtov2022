import pygame as pg
from matrix_functions import *

class Camera:
    def __init__(self, render, position):
        self.render = render  # Установка рендера и позиции камеры
        self.position = np.array([*position, 1.0])  # Установка позиции камеры в пространстве
        self.forward = np.array([0, 0, 1, 1])  # Направление вперед
        self.up = np.array([0, 1, 0, 1])  # Направление вверх
        self.right = np.array([1, 0, 0, 1])  # Направление вправо
        self.h_fov = math.pi / 3  # Горизонтальный угол обзора
        self.v_fov = self.h_fov * (render.HEIGHT / render.WIDTH)  # Вертикальный угол обзора
        self.near_plane = 0.1  # Ближняя плоскость отсечения
        self.far_plane = 100  # Дальняя плоскость отсечения
        self.moving_speed = 0.02  # Скорость перемещения камеры
        self.rotation_speed = 0.01  # Скорость вращения камеры

    def control(self):
        key = pg.key.get_pressed()  # Получение нажатых клавиш
        # Перемещение камеры по осям XYZ
        if key[pg.K_a]:
            self.position -= self.right * self.moving_speed
        if key[pg.K_d]:
            self.position += self.right * self.moving_speed
        if key[pg.K_w]:
            self.position += self.forward * self.moving_speed
        if key[pg.K_s]:
            self.position -= self.forward * self.moving_speed
        if key[pg.K_q]:
            self.position += self.up * self.moving_speed
        if key[pg.K_e]:
            self.position -= self.up * self.moving_speed

        # Поворот камеры вокруг осей Y и X
        if key[pg.K_LEFT]:
            self.camera_yaw(-self.rotation_speed)
        if key[pg.K_RIGHT]:
            self.camera_yaw(self.rotation_speed)
        if key[pg.K_UP]:
            self.camera_pitch(-self.rotation_speed)
        if key[pg.K_DOWN]:
            self.camera_pitch(self.rotation_speed)

    def camera_yaw(self, angle):
        # Вращение камеры вокруг оси Y
        rotate = rotate_y(angle)
        self.forward = self.forward @ rotate
        self.right = self.right @ rotate
        self.up = self.up @ rotate
    
    def camera_pitch(self, angle):
        # Вращение камеры вокруг оси X
        rotate = rotate_x(angle)
        self.forward = self.forward @ rotate
        self.right = self.right @ rotate
        self.up = self.up @ rotate

    def translate_matrix(self):
        # Создание матрицы трансляции для камеры
        x, y, z, w = self.position
        return np.array([
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [-x, -y, -z, 1]
        ])
    
    def rotate_matrix(self):
        # Создание матрицы поворота для камеры
        rx, ry, rz, w = self.right
        fx, fy, fz, w = self.forward
        ux, uy, uz, w = self.up
        return np.array([
            [rx, ux, fx, 0],
            [ry, uy, fy, 0],
            [rz, uz, fz, 0],
            [0, 0, 0, 1]
        ])
    
    def camera_matrix(self):
        # Создание матрицы камеры путем объединения матриц трансляции и поворота
        return self.translate_matrix() @ self.rotate_matrix()
