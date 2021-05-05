#ifndef VOICE_H
#define VOICE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

typedef struct Response{
    char* transcript;
    char* confidence;
} Response;


void Tobase64();

int prepare_request();

//void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

int record();

void get_response(Response* new);

#endif