package domain;

public class Hotels {
    private final int hotelId;
    private final String hotelName;
    private final String date;
    private final String city;
    private final int availableRooms;

    public Hotels(int hotelId, String hotelName, String date, String city, int avaliableRooms) {
        this.hotelId = hotelId;
        this.hotelName = hotelName;
        this.date = date;

        this.city = city;
        this.availableRooms = avaliableRooms;
    }

    public int getHotelId() {
        return hotelId;
    }

    public String getHotelName() {
        return hotelName;
    }

    public String getDate() {
        return date;
    }

    public String getCity() {
        return city;
    }

    public int getAvailableRooms() {
        return availableRooms;
    }

    @Override
    public String toString() {
        return "Hotel ID: " + hotelId + ", Hotel Name: " + hotelName + ", Date: " + date + ", City: " + city + ", Avaliable Rooms: " + availableRooms;
    }
}
