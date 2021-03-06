#ifndef ANDROID_SPEECH_DATA_PROCESSING_HANDLER_H
#define ANDROID_SPEECH_DATA_PROCESSING_HANDLER_H

#include <utils/threads.h>
#include <pthread.h>
#include <utils/List.h>

#include "AudioType.h"
#include "AudioLock.h"
#include "AudioUtility.h"
#include "MtkAudioSrc.h"
#include "SpeechDriverFactory.h"

namespace android
{
class SpeechDataProcessingHandler
{
    public:
        SpeechDataProcessingHandler();

        ~SpeechDataProcessingHandler();

        static SpeechDataProcessingHandler *getInstance();

        static void destoryInstanceSafely();

        /**
         * provide modem record data to capture data provider
         */
        status_t provideModemRecordDataToProvider(RingBuf modem_record_buf);

        /**
         * Get the stream attr of speech data
         */
        void getStreamAttributeSource(stream_attribute_t *streamAttributeSource);

        status_t recordOn(record_type_t type);

        status_t recordOff(record_type_t type);

    private:

        /**
         * singleton pattern
         */
        static SpeechDataProcessingHandler *mSpeechDataProcessingHandler;

        /**
         * Bli SRC
         */
        MtkAudioSrc *mBliSrcUL;

        MtkAudioSrc *mBliSrcDL;

        uint32_t mSrcSampleRateUL;

        uint32_t mSrcSampleRateDL;

        /**
         * Threading resources
         */
        pthread_t mSpeechDataProcessingThread;

        pthread_cond_t  mSpeechDataNotifyEvent;

        pthread_mutex_t mSpeechDataNotifyMutex;

        bool mStopThreadFlag;

        List<RingBuf *> mSpeechDataList;

        static void *threadLoop(void *arg);

        status_t processSpeechPacket(char *inputPacketBuf, uint32_t speechDataSize);

        /**
         * Maintain speech driver status
         */
        bool mSpeechRecordOn;
};

} // end namespace android

#endif // end of ANDROID_SPEECH_DATA_PROCESSING_HANDLER_H

