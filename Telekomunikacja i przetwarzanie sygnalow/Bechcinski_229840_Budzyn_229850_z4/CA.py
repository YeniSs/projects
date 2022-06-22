import numpy as np
import soundcard as sc
from scipy.io.wavfile import read

class Odtwarzacz:
    def __init__(self, audio=None, probkowanie= None, kanaly=None):
        self.audio = audio
        if audio == None:
            self.audio = sc.default_speaker()
        self.probkowanie = probkowanie
        self.kanaly = kanaly

    def odtworzNagranie(self, data : np.ndarray):
        self.audio.play(data, self.probkowanie, self.kanaly)

    def odtworzPlik(self, src : str):
        data = read(src)
        probkowanie = data[0]
        data = np.float64(data[1]/np.max(abs(data[1])))
        kanaly = []
        for i in range(len(data[0])):
            kanaly.append(i)
        self.audio.play(data, probkowanie, kanaly)