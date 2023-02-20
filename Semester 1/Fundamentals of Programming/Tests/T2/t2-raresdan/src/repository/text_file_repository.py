from src.domain.domain import Address
from src.repository.repository import Repository


class TextFileRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Tests\\T2\\t2-raresdan\\src\\entities"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                line = line.strip()
                array = line.split(",")
                address = Address(int(array[0]), array[1], int(array[2]), int(array[3]), int(array[4]))
                super().add(address)

    def add(self, address):
        super().add(address)
        with open(self.__file_name, "a") as f:
            f.write(str(address.get_id()) + "," + str(address.get_name()) + "," + str(address.get_number()) + "," + str(
                address.get_x()) + "," + str(address.get_y()) + "\n")
