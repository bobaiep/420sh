#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json/json.h>


int main(int argc, char** argv)
{
  int res = system("gst-launch-1.0 -e alsasrc ! audioconvert ! vorbisenc ! wavenc ! filesink location = Audio/input2.wav");

  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that ishttps://github.com/bobafeet2000/420sh.git what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, "https://speech.googleapis.com/v1/speech:recognize");
    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}

int Jsoncreate(char* filename)
{
  json_object * config = json_object_new_object();
  json_object *config = json_object_new_string("Joys of Programming");


}