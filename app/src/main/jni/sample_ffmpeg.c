//
// Created by KAKAO on 2017. 11. 20..
//
#include <jni.h>
#include <android/log.h>

#include "libavformat/avformat.h"
#include "libavutil/error.h"

JNIEXPORT jint JNICALL Java_com_example_kakao_ffmpegjniexample_NDK_scanning
  (JNIEnv * env, jobject jobj, jstring filepath){

    __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  ffmpeg jni api called ------ %s \n\n\n\n\n\n\n\n\n\n\n", filepath);

     const char* nativeFilepath = (*env)->GetStringUTFChars( env, filepath , NULL ) ;

     //char* nativeFilepath = "/sdcard/1.mp4";


     AVFormatContext* avFormatContext = NULL;



     // muxer, demuxer, decoder, encoder 초기화

     av_register_all();



     // nativeFilepath로 avFormatContext 가져오기

     int ret = avformat_open_input(&avFormatContext, nativeFilepath, NULL, NULL) ;

     if(ret < 0)

     {
         __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  Can't open input file %s------ %d, %s  \n\n\n\n\n\n\n\n\n\n\n", nativeFilepath, ret, av_err2str(ret));
         (*env)->ReleaseStringUTFChars(env, filepath, nativeFilepath);
         return -1;

     }



     // 유효한 스트림 정보 찾기

     if(avformat_find_stream_info(avFormatContext, NULL) < 0)

     {


         __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  Failed to retrieve input stream information \n\n\n\n\n\n\n\n\n\n\n");


         (*env)->ReleaseStringUTFChars(env, filepath, nativeFilepath);

         return -2;

     }



     // avFormatContext->nb_streams : 비디오 파일의 전체 스트림 수

     for(unsigned int index = 0; index < avFormatContext->nb_streams; index++)

     {

         AVCodecParameters* avCodecParameters = avFormatContext->streams[index]->codecpar;

         if(avCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)

         {

            __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  ------- Video info ------- \n\n\n\n\n\n\n\n\n\n\n");
            __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  codec_id : %d \n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->codec_id);
            __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  bitrate : %lld \n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->bit_rate);
            __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  width : %d / height : %d \n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->width, avCodecParameters->height);

         }

         else if(avCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)

         {

             __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  ------- Audio info ------- \n\n\n\n\n\n\n\n\n\n\n");
             __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  codec_id : %d \n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->codec_id);
             __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  bitrate : %lld \n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->bit_rate);
             __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  sample_rate : %d\n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->sample_rate);
             __android_log_print(ANDROID_LOG_DEBUG, "........", "\n\n\n\n\n\n\n\n\n\n\n\n  number of channels : %d\n\n\n\n\n\n\n\n\n\n\n", avCodecParameters->channels);




         }

     }



     // release

     if(avFormatContext != NULL)

     {

         avformat_close_input(&avFormatContext);

     }



     // release

     (*env)->ReleaseStringUTFChars(env, filepath, nativeFilepath);



     return 0;


}
