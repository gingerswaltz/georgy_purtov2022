from object_3d import *
from camera import *
from projection import *
import pygame as pg

class SoftwareRender:
    def __init__(self):
        pg.init()
        self.RES = self.WIDTH, self.HEIGHT = 1600, 900
        self.H_WIDTH, self.H_HEIGHT = self.WIDTH // 2, self.HEIGHT // 2
        self.FPS = 30
        self.screen = pg.display.set_mode(self.RES)
        self.clock = pg.time.Clock()
        self.create_object()

    def create_object(self):
        self.camera = Camera(self, [0.5, 1, -4])
        self.projection = Projection(self)
        self.object = Object3D(self)
        self.object.translate([0.2, 0.4, 0.2])
        self.object.rotate_y(math.pi / 6)

    def get_object_from_file(self, filename):
        vertex, faces = [], []
        with open(filename) as f:
            for line in f:
                if line.startswith('v '):
                    vertex.append([float(i) for i in line.split()[1:]] + [1])
                elif line.startswith('f'):
                    faces_ = line.split()[1:]
                    faces.append([int(face_.split('/')[0]) -1 for face_ in faces_])
        return Object3D(self, vertex, faces)

    def draw(self):
        self.screen.fill(pg.Color('cyan'))
        self.object.draw()

    def run(self):
        while True:
            self.draw()
            self.camera.control()
            [exit() for i in pg.event.get() if i.type == pg.QUIT]
            pg.display.set_caption(str(self.clock.get_fps()))
            pg.display.flip()
            self.clock.tick(self.FPS)
            keys = pg.key.get_pressed()  # Получение нажатых клавиш
            if keys[pg.K_1]:  # Проверка нажатия клавиши "1"
                self.object.movement(1)  # Вызов метода movement с аргументом 1
            if keys[pg.K_2]:  # Проверка нажатия клавиши "2"
                self.object.movement(2)  # Вызов метода movement с аргументом 2
            if keys[pg.K_3]:  # Проверка нажатия клавиши "3"
                self.object.movement(3)  # Вызов метода movement с аргументом 3

if __name__ == "__main__":
    app = SoftwareRender()
    app.run()
    
