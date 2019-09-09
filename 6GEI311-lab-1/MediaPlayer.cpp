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
	LPCWSTR filePath = L"C:\\Example.avi";

	hresult = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not query the control.");
		return;
	}

	hresult = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not query the event.");
		return;
	}

	hresult = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not query the seek.");
		return;
	}

	
	hresult = pGraph->RenderFile(filePath, NULL);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not render the file.");
		return;
	}
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
				FastForwardVideo();
				valid = true;
				break;
			case 'R':
				RestartVideo();
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
	pSeek->GetRate(&rate);
	if (rate == 1.0)
	{
		hresult = pSeek->SetRate(2.0);
		if (FAILED(hresult))
		{
			printf("ERROR - Could not set rate to 2.0.");
		}
	}
	else
	{
		hresult = pSeek->SetRate(1.0);
		if (FAILED(hresult))
		{
			printf("ERROR - Could not set rate to 1.0.");
		}
	}
}

void MediaPlayer::GetPositions()
{
	hresult = pSeek->GetPositions(pCurrentPos, pStopPos);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not get current and stop positions.");
	}
}

void MediaPlayer::RestartVideo()
{
	REFERENCE_TIME start = 0;
	hresult = pSeek->SetPositions(
		&start, AM_SEEKING_AbsolutePositioning,
		NULL, AM_SEEKING_NoPositioning
	);
	if (FAILED(hresult))
	{
		printf("ERROR - Could not set positions.");
	}
	if (state == pause)
	{
		PauseVideo();
	}
	else
	{
		PlayVideo();
	}
}

MediaPlayer::MediaPlayer()
{
	pGraph = NULL;
	pControl = NULL;
	pEvent = NULL;
	pSeek = NULL;
	hresult = NULL;
	pCurrentPos = NULL;
	pStopPos = NULL;
	InitCOMLib();
	InitFilterGraphManager();
	BuildGraph();
	state = pause;
}

MediaPlayer::~MediaPlayer() {}
