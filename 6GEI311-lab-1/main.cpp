#include "MediaPlayer.h"
#include <string>

void main(void)
{
	MediaPlayer *player = new MediaPlayer();

	char key = ' ';

	while (key != 'Q')
	{
		while (!player->ReadKey(&key))
		{
			
		}
	}
	std::cout << "End of program." << std::endl;
	return;
}
