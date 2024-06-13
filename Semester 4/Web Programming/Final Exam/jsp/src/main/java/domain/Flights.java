package domain;

public class Flights {
    private final int flightId;
    private final String date;
    private final String destinationCity;
    private final int availableSeats;

    public Flights(int flightId, String date, String destinationCity, int availableSeats) {
        this.flightId = flightId;
        this.date = date;
        this.destinationCity = destinationCity;
        this.availableSeats = availableSeats;
    }

    public int getFlightId() {
        return flightId;
    }

    public String getDate() {
        return date;
    }

    public String getDestinationCity() {
        return destinationCity;
    }

    public int getAvailableSeats() {
        return availableSeats;
    }

    @Override
    public String toString() {
        return "Flight ID: " + flightId + ", Date: " + date + ", Destination City: " + destinationCity + ", Available Seats: " + availableSeats;
    }

}
