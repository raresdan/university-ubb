package domain;

public class Reservations {
    private final int id;
    private final String person;
    private final String date;
    private final String type;
    private final int idReservedResource;

    public Reservations(int id, String person, String date, String type, int idReservedResource) {
        this.id = id;
        this.person = person;
        this.date = date;
        this.type = type;
        this.idReservedResource = idReservedResource;
    }

    public int getId() {
        return id;
    }

    public String getPerson() {
        return person;
    }

    public String getDate() {
        return date;
    }

    public String getType() {
        return type;
    }

    public int getIdReservedResource() {
        return idReservedResource;
    }

    @Override
    public String toString() {
        return "ID: " + id + ", Person: " + person + ", Date: " + date + ", Type: " + type + ", ID Reserved Resource: " + idReservedResource;
    }
}
