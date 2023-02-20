from functions import *


def menu():
    print("---------------MENU--------------")
    print("[add] - ADD A MUSIC FESTIVAL")
    print("[exit] - EXITS THE APP")
    print()


def run_menu():
    menu()
    festival_list = []
    for i in range(0, 10):
        x = generate_random()
        festival_list.append(x)
        print(f"#{i + 1} {to_str(x)}")
    option = 0
    while True:
        try:
            print()
            option = input("Enter your command: ")
            print()
        except ValueError:
            print("Invalid command")

        if option == "add":
            counter = 0
            try:
                name = input("Enter festival name:")
                if not check_name(festival_list, name.lower()):
                    print("There exists a festival with the same name already!")
            except ValueError:
                print("There exists a festival with the same name already!")

            try:
                month = input("Enter the month during the festival takes place:")
                if month.isnumeric():
                    if 1 > int(month) > 12:
                        print("Invalid input! Month must be in range [1,12]!")
                        break
                else:
                    print("Invalid input! Month must be integer")
                    break
            except ValueError:
                print("Invalid input! Month must be integer")
            try:
                ticket = input("Enter the price of the ticket:")
                if not ticket.isnumeric():
                    print("Invalid input! Price must be integer")
                    break
            except ValueError:
                print("Invalid input! Price must be integer")
            try:
                counter = input("How many artists does the festival have?")
                if not counter.isnumeric():
                    print("Invalid input! Number of artists must be integer")
                    break
            except ValueError:
                print("Invalid input! Number of artists must be integer")
            artist_list = []
            for i in range(0, int(counter)):
                artist = input(f"Enter the artist #{i + 1} name: ")
                artist_list.append(artist)
            new_festival = create_festival(name, month, ticket, artist_list)
            add_festival(festival_list, new_festival)
        if option == "list":
            for i in range(0, len(festival_list)):
                print(f"#{i+1} {to_str(x)}")
        if option == "exit":
            print("Menu exited successfully!")
            break


if __name__ == '__main__':
    run_menu()
