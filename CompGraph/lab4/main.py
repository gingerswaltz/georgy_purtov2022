import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

vertices = (
    (1, -1, -1),
    (1, 1, -1),
    (-1, 1, -1),
    (-1, -1, -1),
    (1, -1, 1),
    (1, 1, 1),
    (-1, -1, 1),
    (-1, 1, 1)
)

edges = (
    (0, 1),
    (0, 3),
    (0, 4),
    (2, 1),
    (2, 3),
    (2, 7),
    (6, 3),
    (6, 4),
    (6, 7),
    (5, 1),
    (5, 4),
    (5, 7)
)

colors = (
    (1, 0, 0),
    (0, 1, 0),
    (0, 0, 1),
    (1, 1, 0),
    (1, 0, 1),
    (0, 1, 1),
    (1, 1, 1),
    (0, 0, 0)
)

size = 1.0  # Размер куба
rotation_direction = (1, 1, 1)  # Направление вращения по умолчанию

def Cube():
    glBegin(GL_LINES)
    for edge in edges:
        for vertex in edge:
            glVertex3fv(tuple(v * size for v in vertices[vertex]))
    glEnd()

def render_text(text, position):
    font = pygame.font.Font(None, 36)
    text_surface = font.render(text, True, (255, 255, 255), (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = position
    return text_surface, text_rect

def main():
    global size, rotation_direction
    pygame.init()
    display = (800, 600)
    screen = pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    gluPerspective(45, (display[0] / display[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -5)

    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    size += 0.1
                elif event.key == pygame.K_DOWN:
                    size -= 0.1
                elif event.key == pygame.K_1:
                    rotation_direction = (1, 0, 0)
                elif event.key == pygame.K_2:
                    rotation_direction = (0, 1, 0)
                elif event.key == pygame.K_3:
                    rotation_direction = (0, 0, 1)

        glRotatef(1, *rotation_direction)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        Cube()

        screen.fill((0, 0, 0))
        text_surf1, text_rect1 = render_text(f"Size: {size:.2f}", (display[0] // 2, 50))
        text_surf2, text_rect2 = render_text(f"Rotation direction: {rotation_direction}", (display[0] // 2, 100))
        screen.blit(text_surf1, text_rect1)
        screen.blit(text_surf2, text_rect2)

        pygame.display.set_caption(f"Cube: Size {size:.2f}, Rotation {rotation_direction}")

        pygame.display.flip()
        clock.tick(60)

main()
