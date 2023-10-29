#include "audio.hpp"
#include <unordered_map>
#include <vector>

std::unordered_map<SoundHandle, audio::Sound> sounds;
std::vector<audio::Sound> songs;

namespace audio {
    SoundHandle song_playing = -1;
}

void apply_dsp_firm(){
    std::filesystem::create_directory("/3ds");

    if(!std::filesystem::exists("/3ds/dspfirm.cdc")){
        FILE* file = fopen("/3ds/dspfirm.cdc", "w");
        fclose(file);
    }
}

// void playNextSong(){
// 	song_playing = (song_playing + 1) % NUMBER_OF_SONGS;
// 	Mix_FadeInMusic(songs[song_playing], 0, 300);
// }

void audio::init() {
    apply_dsp_firm(); // for sound to work in citra

    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
}


void audio::close() {
    SDL_Quit();
}

audio::Sound register_generic_audio(SoundHandle sound_handle, const std::string& file_name, bool is_music = false) {
    std::string file_location = is_music ? "romfs:/sound/music/" : "romfs:/sound/";
    std::stringstream s;		

    s << file_location << file_name;    
    const std::string file_path = s.str();
    audio::Sound sound_obj;

    if (file_name.ends_with(".mp3")){
        sound_obj.type = audio::Sound::Type::MUSIC;
        sound_obj.data = Mix_LoadMUS(file_path.c_str());
    }
    else {
        sound_obj.type = audio::Sound::Type::WAV_SOUND;
        sound_obj.data = Mix_LoadWAV(file_path.c_str());
    }

    return sound_obj;
}

void audio::register_sound(SoundHandle sound_handle, const std::string& file_name) {
    auto sound_obj = register_generic_audio(sound_handle, file_name);
	sounds.emplace(std::make_pair(sound_handle, sound_obj));
}

void audio::register_song(const std::string& file_name) {
    auto sound_obj = register_generic_audio(songs.size(), file_name, true);
	songs.emplace_back(sound_obj);
}

inline void play_generic_sound(SoundHandle sound) {
    auto audio = sounds[sound];

    if (audio.type == audio::Sound::Type::MUSIC){
        Mix_PlayMusic((Mix_Music*)audio.data, 0);
    } else {
        Mix_PlayChannel(-1, (Mix_Chunk*)audio.data, 0);
    }
}

void audio::play_sound(SoundHandle sound){
    play_generic_sound(sound);
}

void audio::start_playing_music() {
    if (songs.empty())
        return;

    if (audio::song_playing == -1) 
        audio::song_playing = 0;
    else {
        audio::song_playing = (song_playing + 1) % songs.size();
    }
	Mix_FadeInMusic((Mix_Music*)songs[song_playing].data, 0, 300);
}

void audio::stop_playing_music() {
    Mix_PauseMusic();
}

