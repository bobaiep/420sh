#ifndef VOICE_H
#define VOICE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "../cmd/shell.h"
#include <unistd.h>

typedef struct Response{
    char* transcript;
    char* confidence;
} Response;


void Tobase64();

int prepare_request();

//void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

int record();

void get_response(Response* new);

void addLink(char* recognized, char* to_recognize);

void addPhrase(char* phrase);

char* searchLink(char* recognized);

void learn(char* transcript);

#endif