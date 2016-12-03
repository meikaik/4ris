//
//  main.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "readconsole.hpp"
#include "score.hpp"
#include <OpenAl/al.h>
#include <OpenAL/alc.h>
using namespace std;


void func(){
    FILE* fp = NULL;
    
    fp = fopen("tet.wav", "rb");
    
    char type[4];
    unsigned int size, chunkSize;
    short formatType, channels;
    unsigned int sampleRate, avgBytesPerSec;
    short bytesPerSample, bitsPerSample;
    unsigned int dataSize;
    
    fread(type, sizeof(char), 4, fp);

    fread(&size, sizeof(unsigned int), 1, fp);
    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
        cout << "OpenAL Error: Not a WAVE file";
    
    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
        cout << "OpenAL Error: Not a fmt";
    
    fread(&chunkSize, sizeof(unsigned int), 1, fp);
    fread(&formatType, sizeof(short), 1, fp);
    fread(&channels, sizeof(short), 1, fp);
    fread(&sampleRate, sizeof(unsigned int), 1, fp);
    fread(&avgBytesPerSec, sizeof(unsigned int), 1, fp);
    fread(&bytesPerSample, sizeof(short), 1, fp);
    fread(&bitsPerSample, sizeof(short), 1, fp);
    
    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
        cout << "OpenAL Error: Missing DATA";
    
    fread(&dataSize, sizeof(unsigned int), 1, fp);
    
    ALCdevice* device;
    ALCcontext* context;
    
    device = alcOpenDevice(NULL);
    if (!device)
        cout << "OpenAL Error: No sound device detected";
    
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    if (!context)
        cout<< "OpenAL Error: No sound context";
    
    unsigned char* buf = new unsigned char[dataSize];
    fread(buf, sizeof(char), dataSize, fp);
    
    ALuint source;
    ALuint buffer;
    ALuint frequency = sampleRate;
    ALenum format = 0;
    
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    
    if (bitsPerSample == 8)
    {
        if (channels == 1)
            format = AL_FORMAT_MONO8;
        else if (channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if (bitsPerSample == 16)
    {
        if (channels == 1)
            format = AL_FORMAT_MONO16;
        else if (channels == 2)
            format = AL_FORMAT_STEREO16;
    }
    
    alBufferData(buffer, format, buf, dataSize, frequency);
    
    ALfloat SourcePos[] = { 0.0f, 0.0f, 0.0f };
    ALfloat SourceVel[] = { 0.0f, 0.0f, 0.0f };
    ALfloat ListenerPos[] = { 0.0f, 0.0f, 0.0f };
    ALfloat ListenerVel[] = { 0.0f, 0.0f, 0.0f };
    ALfloat ListenerOri[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
    
    // Listener
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    
    // Source
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcefv(source, AL_POSITION, SourcePos);
    alSourcefv(source, AL_VELOCITY, SourceVel);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(source);

}

int main(int argc, const char *argv[]) { //program takes cmd arguments
    int seed = 783478378; //random seed val generates the same sequence
    int startLevel = 0; //default level
    bool textMode = false; // default display
    string scriptFile{"sequence.txt"}; //following code initilizes the prior 3 vars.
    string argInput;
    for (int i = 0; i < argc; i++) {
        argInput = argv[i];
        if (argInput == "-text") {
            textMode = true;
        }
        else if (argInput == "-seed") {
            istringstream iss(argv[++i]);
            iss >> seed;
        }
        else if (argInput == "-scriptfile") {
            scriptFile = argv[++i];
        }
        else if (argInput == "-startlevel") {
            istringstream iss(argv[++i]);
            iss >> startLevel;
        }
    }
    
    func();
    Score *indefiniteScore = new Score(); //defualt score pointer
    srand(seed); //creates a random order for subsequent rands based on seed
    ReadConsole rc (indefiniteScore, startLevel, scriptFile, textMode); //Readconsole's ctor
    rc.startRead(nullptr); //startRead is initilized to take in commands.
    return 0;
}


