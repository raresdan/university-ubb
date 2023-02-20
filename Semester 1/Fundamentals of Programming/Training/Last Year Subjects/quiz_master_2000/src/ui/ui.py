class Ui:
    def __init__(self, controller):
        self.__controller = controller

    def add(self, question):
        array = question[0].split(";")
        if not array[0].isnumeric():
            print("Id must be integer!")
            return
        question_id = int(array[0])
        text = array[1]
        ca = array[2]
        cb = array[3]
        cc = array[4]
        correct = array[5]
        difficulty = array[6]
        if correct.strip() != ca.strip() and correct.strip() != cb.strip() and correct.strip() != cc.strip():
            print("Correct answer must be one of the choices!")
            return
        try:
            self.__controller.add(question_id, text, ca, cb, cc, correct, difficulty)
        except ValueError as ve:
            print(ve)

    def run_menu(self):
        while True:
            while True:
                try:
                    option = input("Enter your option: ")
                    break
                except ValueError as ve:
                    print("Invalid option!", ve)
            option, delimiter, *array = option.partition(" ")
            if option == "add":
                self.add(array)
            elif option == "exit":
                print("Menu exited successfully!")
                break
            else:
                print("Invalid option!")
