import pygame


class Controller:
    def __init__(self, view, model):
        self.view = view
        self.model = model
        self.view.set_controller(self)

    def play_music(self):
        if not self.model.playing:
            pygame.mixer.init()
            pygame.mixer.music.load(self.model.root.find('music').text)
            pygame.mixer.music.play(start=self.model.position)
            self.model.playing = True
            self.model.paused = False

    def pause_music(self):
        if self.model.playing and not self.model.paused:
            self.model.position = pygame.mixer.music.get_pos()
            pygame.mixer.music.pause()
            self.model.paused = True

    def stop_music(self):
        if self.model.playing:
            pygame.mixer.music.stop()
            self.model.position = 0
            self.model.playing = False
            self.model.paused = False
