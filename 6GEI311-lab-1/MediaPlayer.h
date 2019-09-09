#pragma once

#include <dshow.h>
#include <iostream>

class MediaPlayer
{
private:
	IGraphBuilder *pGraph;
	IMediaControl *pControl;
	IMediaEvent *pEvent;
	IMediaSeeking *pSeek;
	enum STATE {
		play,
		pause
	};

	HRESULT InitCOMLib();
	HRESULT RenderFile(LPCWSTR filePath);
	HRESULT SetControl();
	HRESULT SetEvent();
	HRESULT SetSeek();
	HRESULT InitFilterGraphManager();
	HRESULT BuildGraph();
	HRESULT PlayVideo();
	HRESULT PauseVideo();
	HRESULT FastForwardVideo();
	HRESULT RestartVideo();
public:
	MediaPlayer();
	~MediaPlayer();
	bool ReadKey(char *);
	STATE state;
};

