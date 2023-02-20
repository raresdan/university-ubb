from src.board.board import Board


class TextFileBoard(Board):
    def __init__(self, ):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\Semester 1\\Fundamentals of Programming\\Final Exam\\e1-913-raresdan\\src\\game"

    def load(self):
        with open(self.__file_name, "r") as f:
            i = 1
            for line in f:
                if '|' in line:
                    array = line.split("|")
                    for j in range(8):
                        if array[j].strip() == "X":
                            super().place(i, j)
                        else:
                            self.set_empty(i, j)
                    i += 1

    def save(self):
        with open(self.__file_name, "w") as f:
            f.write(self.__str__())

    def set_file_name(self, new_name):
        self.__file_name = new_name
