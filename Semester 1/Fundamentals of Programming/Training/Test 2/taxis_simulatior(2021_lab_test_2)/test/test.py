from unittest import TestCase

from repository.repository import Repository
from service.service import Service


class TestRides(TestCase):
    def setUp(self) -> None:
        self.repository = Repository()
        self.service = Service(self.repository, 5)

    def test_add(self):
        repository = Repository()
        service = Service(repository, 5)
        ride, taxi = self.service.add_ride(10, 10, 25, 18)
        self.assertEqual(ride.get_starting_x(), 10)
        self.assertEqual(ride.get_starting_y(), 10)
        self.assertEqual(ride.get_ending_x(), 25)
        self.assertEqual(ride.get_ending_y(), 18)
        self.assertEqual(taxi.get_fare(), self.service.manhattan_distance(10, 10, 25, 18), 23)
        self.assertEqual(taxi.get_id(), ride.get_taxi_id())

    def tearDown(self) -> None:
        pass
