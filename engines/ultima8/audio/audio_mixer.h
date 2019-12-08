/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ULTIMA8_AUDIO_AUDIOMIXER_H
#define ULTIMA8_AUDIO_AUDIOMIXER_H

#include "audio/mixer.h"
#include "audio/mididrv.h"
#include "common/array.h"

namespace Ultima8 {

#define SAMPLE_RATE 22050
#define CHANNEL_COUNT 8

namespace Pentagram {
class AudioChannel;
class AudioSample;

class AudioMixer {
private:
	static AudioMixer *the_audio_mixer;
	Audio::Mixer *_mixer;
	::MidiDriver *_midiDriver;
	Common::Array<AudioChannel *> _channels;

/*
	bool            audio_ok;
	uint32          sample_rate;
	bool            stereo;
	MidiDriver     *midi_driver;
	int             midi_volume;

	int             num_channels;
	AudioChannel    **channels;

	void            init_midi();
	static void     sdlAudioCallback(void *userdata, uint8 *stream, int len);

	void            MixAudio(int16 *stream, uint32 bytes);
*/
	void            Lock();
	void            Unlock();
public:
	AudioMixer(Audio::Mixer *mixer);
	~AudioMixer();

	::MidiDriver *getMidiDriver() const {
		return _midiDriver;
	}

	static AudioMixer  *get_instance() {
		return the_audio_mixer;
	}

	void            reset();
	void            createProcesses();

	int             playSample(AudioSample *sample, int loop, int priority, bool paused, uint32 pitch_shift, int lvol, int rvol);
	bool            isPlaying(int chan);
	void            stopSample(int chan);

	void            setPaused(int chan, bool paused);
	bool            isPaused(int chan);

	void            setVolume(int chan, int lvol, int rvol);
	void            getVolume(int chan, int &lvol, int &rvol);

	void            openMidiOutput();
	void            closeMidiOutput();
};

} // End of namespace Pentagram
} // End of namespace Ultima8

#endif