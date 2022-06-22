from typing import Optional
import soundcard as sc
import numpy as np
from scipy.io.wavfile import write

class Nagrywarka:
    def __init__(self, audio= None, probkowanie=None, kanaly=None):
        self.probkowanie = probkowanie
        self.kanaly = kanaly
        self.audio = audio if audio!=None else sc.default_microphone()
        self.zapiszAudio = None

    
    def record(self, seconds : int):
        if type(self.zapiszAudio) != np.ndarray:
            self.zapiszAudio = self.audio.record(int(seconds * self.probkowanie), self.probkowanie, self.kanaly)
        else:
            test = self.audio.record(int(seconds * self.probkowanie), self.probkowanie, self.kanaly)
            self.zapiszAudio = np.concatenate((self.zapiszAudio, test))

    def getAudio(self) -> np.ndarray:
        return self.zapiszAudio

    def zapisDoPliku(self, plik : str, bps : Optional[int] = 16):
        data = self.zapiszAudio
        if bps == 8:
            data = np.int8(data/np.max(abs(data)) * np.iinfo("int8").max)
        if bps == 16:
            data = np.int16(data/np.max(abs(data)) * np.iinfo("int16").max)
        if bps == 32:
            data = np.int32(data/np.max(abs(data)) * np.iinfo("int32").max)
        write("{}.wav".format(plik), self.probkowanie, data)