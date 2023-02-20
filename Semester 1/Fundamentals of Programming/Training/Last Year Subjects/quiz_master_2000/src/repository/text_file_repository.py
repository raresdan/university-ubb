from src.domain.question import Question
from src.repository.repository import Repository


class TextFileRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Training\\Last Year Subjects\\quiz_master_2000\\src\\master_questions"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                line = line.strip()
                array = line.split(";")
                question = Question(int(array[0]), array[1], array[2], array[3], array[4], array[5], array[6])
                super().add(question)

    def add(self, question):
        super().add(question)
        with open(self.__file_name, "a") as f:
            f.write(str(question.get_id()) + ";" + str(question.get_text()) + ";" + str(
                question.get_choice_a()) + ";" + str(question.get_choice_b()) + ";" + str(
                question.get_choice_c()) + ";" + str(question.get_correct_choice()) + ";" + str(
                question.get_difficulty()) + "\n")
