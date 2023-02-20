import random


def create_festival(name, month, ticket, artists):
    festival = dict(name=name, month=month, ticket=ticket, artists=artists)
    return festival


def get_name(festival):
    return festival["name"]


def get_month(festival):
    return festival["month"]


def get_ticket(festival):
    return festival["ticket"]


def get_artists(festival):
    return festival["artists"]


def generate_random():
    name = ["Untold", "Tomorrowland", "Saga", "Electric Castle", "Hustle", "Beach Please"]
    artists = ["Marshmello", "Martin Garrix", "Dj Snake", "Justin Bibber", "Selena Gomez"]
    artists_list = []
    i = random.randint(3, 5)
    for index in range(0, i):
        artists_list.append(random.choice(artists))
    festival = create_festival(random.choice(name), random.randint(1, 12), random.randint(50, 1000), artists_list)
    return festival


def to_str(festival):
    return "Name: " + festival["name"] + ", " + "Month: " + str(festival["month"]) + ", " + "Ticket Price: " + str(festival["ticket"]) + " RON , " + str(festival["artists"])


def add_festival(festival_list, festival):
    festival_list.append(festival)


def check_name(festival_list,name):
    for festival in festival_list:
        if get_name(festival) == name:
            return False
    return True


def show_by_artist(festival_list, artist):
    new_list = []
    for festival in festival_list:
        a_list = get_artists(festival)
        if artist in a_list:
            new_list.append(festival)
    return new_list