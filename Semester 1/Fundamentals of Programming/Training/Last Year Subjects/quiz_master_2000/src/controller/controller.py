from src.domain.question import Question


class Controller:
    def __init__(self, repository):
        self.__repository = repository

    def return_all(self):
        return self.__repository.get_all()

    def add(self, question_id, text, choice_a, choice_b, choice_c, correct, difficulty):
        question = Question(question_id, text, choice_a, choice_b, choice_c, correct, difficulty)
        self.__repository.add(question)

    def create_quiz(self, difficulty, number, file):
        questions = self.return_all()
        with open(file, "w") as f:
            for i in range(number // 2):
                for question in questions:
                    if question.get_difficulty() == difficulty:
                        f.write(str(question.get_id()) + ";" + str(question.get_text()) + ";" + str(
                            question.get_choice_a()) + ";" + str(question.get_choice_b()) + ";" + str(
                            question.get_choice_c()) + ";" + str(question.get_correct_choice()) + ";" + str(
                            question.get_difficulty()) + "\n")
