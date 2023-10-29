#pragma once
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>
#include <filesystem>

// handle to retreive the sound once registered
typedef unsigned int SoundHandle;

enum Sounds {
    LASER = 1,
};

namespace audio {

    extern SoundHandle song_playing;

    struct Sound {
        enum class Type {
            MUSIC, WAV_SOUND
        };

        Type type;
        void* data;
    };

    void init();
    void close();

    void register_sound(SoundHandle sound_handle, const std::string& file_name);
    void register_song(const std::string& file_name);

    void play_sound(SoundHandle sound);
    void play_song(SoundHandle song);
    
    void start_playing_music();
    void stop_playing_music();
}


void playNextSong();