#include <python3.9/Python.h>
#include <stdio.h>
#include <sprec/sprec.h>

int createwav()
{
  return system("gst-launch-1.0 -e alsasrc ! audioconvert ! vorbisenc ! wavenc ! filesink location = Audio/input2.wav");
}
int request()
{
	system('curl -s -H "Content-Type: application/json"-H "Authorization: Bearer "$(gcloud auth application-default print-access-token) https://speech.googleapis.com/v1/speech:recognize -d @sync-request.json"');
}
