#include <conio.h>
#include "MediaPlayer.h"

void MediaPlayer::InitCOMLib()
{
	hresult = CoInitialize(NULL);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not initialize COM library.");
	}
}

void MediaPlayer::InitFilterGraphManager()
{
	hresult = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not create the Filter Graph Manager.");
	}
}

void MediaPlayer::BuildGraph()
{
	LPCWSTR filePath = L"C:\\Users\\labop2\\Downloads\\Example.avi";

	hresult = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hresult = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	hresult = pGraph->RenderFile(filePath, NULL);
}

bool MediaPlayer::ReadKey(char *c)
{
	bool valid = false;
	if (_kbhit())
	{
		*c = toupper(_getch());
		switch (*c)
		{
		case 'P':
				if (state == pause)
				{
					PlayVideo();
				}
				else
				{
					PauseVideo();
				}
				valid = true;
				break;
			case 'A':
				valid = true;
				break;
			case 'R':
				valid = true;
				break;
			case 'Q':
				valid = true;
				break;
		}
	}
	return valid;
}

void MediaPlayer::PlayVideo()
{
	hresult = pControl->Run();
	if (SUCCEEDED(hresult))
	{
		state = play;
		long evCode;
		pEvent->WaitForCompletion(1, &evCode);
	}
}

void MediaPlayer::PauseVideo()
{
	hresult = pControl->Pause();
	if (SUCCEEDED(hresult))
	{
		state = pause;
	}
}

void MediaPlayer::FastForwardVideo()
{
	double rate; 
	seek->GetRate(&rate);
	if (rate == 1.0)
	{
		hresult = seek->SetRate(2.0);
		if (FAILED(hresult))
		{
			printf("ERROR - Could not set rate to 2.0.");
		}
	}
	else
	{
		hresult = seek->SetRate(1.0);
		if (FAILED(hresult))
		{
			printf("ERROR - Could not set rate to 1.0.");
		}
	}
}

MediaPlayer::MediaPlayer()
{
	pGraph = NULL;
	pControl = NULL;
	pEvent = NULL;
	seek = NULL;
	hresult = NULL;

	InitCOMLib();
	InitFilterGraphManager();
	BuildGraph();
	state = pause;
}

MediaPlayer::~MediaPlayer()
{
}
