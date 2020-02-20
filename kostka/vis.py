import pygame
import random
import sys


HEIGHT = 600
WIDTH = 800

COLOR_RED = (255, 0, 0)
COLOR_GREEN = (0, 255, 0)
COLOR_BLUE = (0, 0, 255)
COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)


def print_text(screen, text, pos):
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render(text, True, COLOR_WHITE, COLOR_BLACK)
    textRect = text.get_rect()
    textRect.center = pos
    screen.blit(text, textRect)


class Object(pygame.sprite.Sprite):
    def __init__(self, color, width, height):
            super().__init__()
            self.image = pygame.Surface([width, height])
            self.image.fill(color)
            self.rect = self.image.get_rect()


pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
all_sprites = pygame.sprite.Group()

for i in range(50):
    object = Object(COLOR_RED, 20, 15)
    object.rect.x = random.randrange(WIDTH)
    object.rect.y = random.randrange(HEIGHT)
    all_sprites.add(object)

last_click = None

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
             pygame.quit()
             sys.exit()
        if event.type == pygame.MOUSEBUTTONUP:
            clicked_pos = pygame.mouse.get_pos()
            if last_click is not None:
                pygame.draw.line(screen, COLOR_WHITE, last_click, clicked_pos)
            last_click = clicked_pos
            clicked_sprites = [s for s in all_sprites if s.rect.collidepoint(clicked_pos)]
            for clicked_sprite in clicked_sprites:
                clicked_sprite.image.fill(COLOR_GREEN)
    screen.fill((0, 0, 0))
    all_sprites.draw(screen)
    mouse_x, mouse_y = pygame.mouse.get_pos()
    print_text(screen, "Mouse position: X: %d, Y: %d" % (mouse_x, mouse_y), (WIDTH/2, 16))
    pygame.display.update()
