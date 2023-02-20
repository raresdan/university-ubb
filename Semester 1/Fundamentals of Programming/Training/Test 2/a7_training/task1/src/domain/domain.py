from dataclasses import dataclass


@dataclass
class Complex:
    real: int
    imaginary: int

    def get_real(self):
        return self.real

    def get_imaginary(self):
        return self.imaginary

    def set_real(self, new_value):
        self.real = new_value

    def set_imaginary(self, new_value):
        self.imaginary = new_value
