import pygame as pg
from matrix_functions import *

# Здесь мы описываем сущность Объект 3Д графики

class Object3D:
    def __init__(self, render):
        self.render = render  # Установка экземпляра рендеринга для объекта
        # Задание вершин объекта в виде массива
        self.vertexes = np.array([(0, 0, 0, 1), (0, 1, 0, 1), (1, 1, 0, 1), (1, 0, 0, 1),
                                  (0, 0, 1, 1), (0, 1, 1, 1), (1, 1, 1, 1), (1, 0, 1, 1)])
        # Задание граней объекта в виде массива
        self.faces = np.array([(0, 1, 2, 3), (4, 5, 6, 7), (0, 4, 5, 1), (2, 3, 7, 6), (1, 2, 6, 5), (0, 3, 7 ,4)])

    def draw(self):
        self.screen_projection()



    
    def movement(self, key):
        if key==1:
            self.rotate_x(pg.time.get_ticks() % 0.05)
        elif key==2:
            self.rotate_y(pg.time.get_ticks() % 0.05)
        elif key==3:
            self.rotate_z(pg.time.get_ticks() % 0.05)

    def screen_projection(self):
        # Перемножение вершин объекта на матрицу камеры
        vertexes = self.vertexes @ self.render.camera.camera_matrix()
        # Перемножение результата на матрицу проекции
        vertexes = vertexes @ self.render.projection.projection_matrix
        # Деление всех элементов по последнему столбцу для получения нормализованных координат
        vertexes /= vertexes[:, -1].reshape(-1, 1)
        # Обрезание координат, выходящих за границы экрана
        vertexes[(vertexes > 2) | (vertexes < -2)] = 0
        # Перемножение на матрицу перевода на экран
        vertexes = vertexes @ self.render.projection.to_screen_matrix
        # Оставляем только x и y координаты
        vertexes = vertexes[:, :2]


        # Отрисовка граней объекта
        for face in self.faces:
            polygon = vertexes[face]
            # Если грань не выходит за границы экрана, рисуем ее
            if not np.any((polygon == self.render.H_WIDTH) | (polygon == self.render.H_HEIGHT)):
                pg.draw.polygon(self.render.screen, pg.Color('blue'), polygon, 3)

        # Отрисовка вершин объекта
        for vertex in vertexes:
            # Если вершина не выходит за границы экрана, рисуем ее
            if not np.any((vertex == self.render.H_WIDTH) | (vertex == self.render.H_HEIGHT)):
                pg.draw.circle(self.render.screen, pg.Color('green'), vertex, 6)

    def translate(self, pos):
        # Трансляция (перемещение) объекта
        self.vertexes = self.vertexes @ translate(pos)

    def scale(self, scale_to):
        # Изменение масштаба объекта
        self.vertexes = self.vertexes @ scale(scale_to)

    def rotate_x(self, angle):
        # Вращение объекта вокруг оси X
        self.vertexes = self.vertexes @ rotate_x(angle)

    def rotate_y(self, angle):
        # Вращение объекта вокруг оси Y
        self.vertexes = self.vertexes @ rotate_y(angle)

    def rotate_z(self, angle):
        # Вращение объекта вокруг оси Z
        self.vertexes = self.vertexes @ rotate_z(angle)