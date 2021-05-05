#include "voice_recognition.h"
#define MINIAUDIO_IMPLEMENTATION
#include "./library/miniaudio.h"

#ifdef __APPLE__
#define MA_NO_RUNTIME_LINKING
#define AP 
#endif

void Tobase64(){
    #if defined(AP)
        system("base64 toSend.wav > toSend");
    #else
        system("base64 toSend.wav -w 0 > toSend");
    #endif
}

char *truncString(char *str, int pos)
{
    int len = strlen(str);

    if (len > abs(pos)) {
        if (pos > 0)
            str = str + pos;
        else
            str[len + pos] = 0;
    }

    return str;
}

int prepare_request(){
    Tobase64();
    char * buffer = 0;
    long length = 0;
    FILE * f = fopen ("toSend", "rb");

    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }
    
    FILE * template = fopen("sync-request-tpl.json", "r");
    FILE * new = fopen("sync-request.json", "w");
    if(template)
    {
        char newLine[length+512];
        buffer[strcspn(buffer, "\n")] = 0;
        snprintf(newLine,length+512,"      \"content\":\"%s\"\n", buffer);

        char readed[1000];
        int count = 0;
        while ((fgets(readed, 1000, template)) != NULL)
        {
            count++;

            if (count == 9)
                fputs(newLine, new);
            else{
                fputs(readed, new);
            }
        }
        fclose(new);
        fclose(template);
    }
    return 0;
}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){
    ma_encoder* pEncoder = (ma_encoder*)pDevice->pUserData;
    MA_ASSERT(pEncoder != NULL);

    ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount);

    (void)pOutput;
}

int record(){
    ma_result result;
    ma_encoder_config encoderConfig;
    ma_encoder encoder;
    ma_device_config deviceConfig;
    ma_device device;

    encoderConfig = ma_encoder_config_init(ma_resource_format_wav, ma_format_s16, 2, 44100);

    if (ma_encoder_init_file("toSend.wav", &encoderConfig, &encoder) != MA_SUCCESS) {
        printf("Failed to initialize output file.\n");
        return -1;
    }
    ma_context context;
    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        // Error.
    }

    ma_device_info* pPlaybackInfos;
    ma_uint32 playbackCount;
    ma_device_info* pCaptureInfos;
    ma_uint32 captureCount;

    if (ma_context_get_devices(&context, &pPlaybackInfos, &playbackCount, &pCaptureInfos, &captureCount) != MA_SUCCESS) {
        // Error.
    }

    // Loop over each device info and do something with it. Here we just print the name with their index. You may want
    // to give the user the opportunity to choose which device they'd prefer.
    int i = 0;
    if(captureCount != 1){
        for (ma_uint32 iDevice = 0; iDevice < captureCount; iDevice += 1) {
            printf("%d - %s\n", iDevice, pCaptureInfos[iDevice].name);
        }
        int i;
        printf("Choose the device from which the audio will be captured : ");
        scanf("%i", &i);
    }
    deviceConfig = ma_device_config_init(ma_device_type_capture);
    deviceConfig.capture.pDeviceID = &pCaptureInfos[i].id;
    deviceConfig.capture.format   = encoder.config.format;
    deviceConfig.capture.channels = encoder.config.channels;
    deviceConfig.sampleRate       = encoder.config.sampleRate;
    deviceConfig.dataCallback     = data_callback;
    deviceConfig.pUserData        = &encoder;

    result = ma_device_init(NULL, &deviceConfig, &device);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize capture device.\n");
        return -2;
    }

    result = ma_device_start(&device);
    if (result != MA_SUCCESS) {
        ma_device_uninit(&device);
        printf("Failed to start device.\n");
        return -3;
    }

    printf("Press Enter to stop recording...\n");
    getchar();
    
    ma_device_uninit(&device);
    ma_encoder_uninit(&encoder);

    return 0;
}

void get_response(Response* new){
    if (new != NULL){
        chdir("src/voice_recognition");

        if(record() != 0)
            err(2,"error record");

        if(prepare_request() != 0)
            err(1,"error parser");

        system("curl -s -H \"Content-Type: application/json\" -H \"Authorization: Bearer \"$(gcloud auth application-default print-access-token) https://speech.googleapis.com/v1/speech:recognize -d @sync-request.json > response.json");

        FILE* f = fopen("response.json","r");
        int i = 0;
        char *buff = malloc(sizeof(char)*1000);
        
        while((fgets(buff, 1000, f)) != NULL)
        {
            if (i == 1){
                if(strstr(buff,"results") == NULL)
                    err(1,"Response did not initialize");
            }

            else if (i == 5){
                strcpy(new->transcript,buff+25);
                new->transcript = truncString(new->transcript,-3);
            }
            else if (i >= 6 && strstr(buff,"confidence")){
                strcpy(new->confidence,buff+26);
                new->confidence[2] = '\0';
            }     
            i++;
        }

        free(buff);

        chdir(current->pwd);
    }
}