#include "Song.h"
#include "UI.h"
#include <Windows.h>
#include <crtdbg.h>

using namespace std;

int main()
{
	system("color f4");

	// create a local scope to ensure the deallocation of variables and not have (inexistent) memory leaks reported
	{
		Repository repo{};

		// add some songs
		Song s1{ "Camila Cabello", "Havana", Duration{3, 38}, "https://www.youtube.com/watch?v=HCjNJDNzw8Y" };
		Song s2{ "Two Steps From Hell", "Heart of Courage", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
		Song s3{ "Pink Martini", "Splendor in the Grass", Duration{3, 47}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
		repo.addSong(s1);
		repo.addSong(s2);
		repo.addSong(s3);

		Service service{ repo };
		UI ui{ service };
		ui.run();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}