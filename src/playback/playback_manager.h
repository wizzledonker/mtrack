#pragma once
#include <gtkmm.h>

#ifndef PLAYBACK_MANAGER_H
#define PLAYBACK_MANAGER_H

class PlaybackSource;

class PlaybackManager {
public:
	PlaybackManager();
	PlaybackManager(PlaybackSource *source);

	bool isPlaying();
	bool hasSource();

	void play();
	void pause();
	void stop();
	void next();
	void prev();
	void first();
	void last();
	void gotoFrame(int num);
	void gotoTime(int msec);
	void setLoop(bool);
	void setSource(PlaybackSource *src);
	void clearSource();
	sigc::signal<void, bool> signal_source_changed();
	sigc::signal<void, bool> signal_playback();
protected:
	sigc::signal<void, bool> m_signal_source_changed;
	sigc::signal<void, bool> m_signal_playback;
private:
	bool update(int id);
	PlaybackSource *m_source;

	sigc::connection m_update_connection;
	bool playing = false;
	int timerId = 0;
	bool loop = false;
	bool source_loaded = false;
};

#endif