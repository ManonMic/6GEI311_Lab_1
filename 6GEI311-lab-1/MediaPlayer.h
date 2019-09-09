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
	HRESULT hresult;
	LONGLONG *pCurrentPos;
	LONGLONG *pStopPos;
	enum STATE {
		play,
		pause
	};

	void InitCOMLib();
	void InitFilterGraphManager();
	void BuildGraph();
	void PlayVideo();
	void PauseVideo();
	void FastForwardVideo();
	void RestartVideo();
public:
	MediaPlayer();
	~MediaPlayer();
	bool ReadKey(char *);
	STATE state;
};

