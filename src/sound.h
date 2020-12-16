// Max Number of Sounds that can be played at once (8)
#define MAX_SOUND_CHANNELS      7

// Max Number of Sounds that can be Precached
#define MAX_PRECACHED_SOUNDS    32

#ifdef PSP
typedef OSL_SOUND       stream_t;
typedef OSL_SOUND       sound_t;
#endif

#ifdef DESKTOP
typedef sfMusic         stream_t;
typedef sfSound         sound_t;
typedef sfSoundBuffer   sndbuffer_t;
#endif

typedef struct {
    stream_t* Stream;
} streamelement_t;

typedef struct {
    sound_t* Sound;
#ifdef DESKTOP
    sndbuffer_t* SoundBuffer;
#endif
    char* File;
} soundelement_t;

#ifndef DESKTOP
extern void Sound_Initialize();
#endif

#ifdef PSP
extern sound_t*     Sound_LoadSound(char* Directory);
extern void         Sound_Delete(sound_t* Sound);
#endif

extern void         Sound_Stream(int Channel, char* Sound, boolean Loop, float Pitch, float Volume);
extern void         Sound_Clean();
extern void         Sound_Precache(char* Directory);
extern void         Sound_Play(int Channel, char* Directory, boolean Loop, float Pitch, float Volume);
extern void         Sound_StopStream(stream_t* Stream);
extern void         Sound_PlayStream(stream_t* Stream, int Channel);
extern stream_t*    Sound_StreamFromFile(char* File);
extern void         Sound_PlaySound(sound_t* Sound, int Channel);
extern void         Sound_StopSound(sound_t* Sound);

#ifdef DESKTOP
extern sndbuffer_t* Sound_LoadSound(char* Directory);
extern sound_t*     Sound_Create();
extern void         Sound_SetStreamLoop(stream_t* Stream, boolean Loop);
extern void         Sound_SetStreamPitch(stream_t* Stream, float Pitch);
extern void         Sound_SetStreamVolume(stream_t* Stream, float Volume);
extern void         Sound_BindSoundToBuffer(sound_t* Sound, sndbuffer_t* SoundBuffer);
extern void         Sound_SetSoundLoop(sound_t* Sound, boolean Loop);
extern void         Sound_SetSoundPitch(sound_t* Sound, float Pitch);
extern void         Sound_SetSoundVolume(sound_t* Sound, float Volume);
#endif