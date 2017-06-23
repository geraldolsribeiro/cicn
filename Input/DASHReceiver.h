/*
 * DASHReceiver.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_INPUT_DASHRECEIVER_H_
#define LIBDASH_FRAMEWORK_INPUT_DASHRECEIVER_H_

#include "libdash.h"
#include "IMPD.h"
#include "../MPD/MPDWrapper.h"
#include "../Input/MediaObject.h"
#include "IDASHReceiverObserver.h"
#include "../MPD/AdaptationSetStream.h"
#include "../MPD/IRepresentationStream.h"
#include "../Portable/MultiThreading.h"
#include "../Buffer/Buffer.h"
#include <chrono>
#include "ICNConnectionConsumerApi.h"

namespace libdash
{
namespace framework
{
namespace mpd
{
class AdaptationSetStream;
}
namespace adaptation
{
class IAdaptationLogic;
}
namespace buffer
{
class MediaObjectBuffer;
template <class T>
class Buffer;
}
namespace input
{
class MediaObject;
class DASHReceiver
{
public:
    DASHReceiver(viper::managers::StreamType type, libdash::framework::mpd::MPDWrapper *mpdWrapper, IDASHReceiverObserver *obs, buffer::Buffer<MediaObject> *buffer, uint32_t bufferSize, bool icnEnabled, double icnAlpha, float beta, float drop);
    virtual ~DASHReceiver();

    bool Start();
    void Stop();
    input::MediaObject* GetNextSegment();
    input::MediaObject* GetSegment(uint32_t segmentNumber);
    input::MediaObject* GetInitSegment();
    input::MediaObject* GetInitSegmentWithoutLock();
//    input::MediaObject* FindInitSegment(dash::mpd::IRepresentation *representation);
    input::MediaObject* FindInitSegment(int representation);
    uint32_t GetPosition();
    void SetPosition(uint32_t segmentNumber);
    void SetLooping(bool isLoopinp);
    void SetPositionInMsecs(uint32_t milliSecs);
    dash::mpd::IRepresentation* GetRepresentation();
//    void SetRepresentation(dash::mpd::IPeriod *period,
//                                                         dash::mpd::IAdaptationSet *adaptationSet,
//                                                         dash::mpd::IRepresentation *representation);
    void SetRepresentation();
    void SetAdaptationLogic(adaptation::IAdaptationLogic *_adaptationLogic);
    libdash::framework::adaptation::IAdaptationLogic* GetAdaptationLogic();
    void NotifyQualityDownloading(uint32_t quality);
    void Notifybps(uint64_t bps);
    void NotifyDLTime(double time);
    void NotifyBitrateChange(dash::mpd::IRepresentation *representation);
    void OnSegmentBufferStateChanged(uint32_t fillstateInPercent, int maxC);
    bool IsICN();
    void ShouldAbort();
    void OnEOS(bool value);
    void SetTargetDownloadingTime(double);
    void NotifyCheckedAdaptationLogic();
    bool threadComplete;
    bool PushBack(MediaObject* media);
    bool CanPush();
    void SetBeta(float beta);
    void SetDrop(float drop);
    void updateMPD(dash::mpd::IMPD* mpd);

private:
    float                                               beta;
    float                                               drop;
    bool                                                withFeedBack;
    bool                                                isBufferBased;
//    std::map<dash::mpd::IRepresentation*, MediaObject*> initSegments;
    std::map<int, MediaObject*> initSegments;
    libdash::framework::buffer::Buffer<MediaObject>     *buffer;
    IDASHReceiverObserver                               *observer;
    libdash::framework::mpd::MPDWrapper			*mpdWrapper;
//    dash::mpd::IMPD                                     *mpd;
//    dash::mpd::IPeriod                                  *period;
//    dash::mpd::IAdaptationSet                           *adaptationSet;
//    dash::mpd::IRepresentation                          *representation;
    mpd::AdaptationSetStream                            *adaptationSetStream;
//    mpd::IRepresentationStream                          *representationStream;
    uint32_t                                            segmentNumber;
    uint32_t                                            positionInMsecs;
    uint32_t                                            segmentOffset;
    uint32_t                                            bufferSize;
    mutable CRITICAL_SECTION                            monitorMutex;
    mutable CRITICAL_SECTION                            monitorPausedMutex;
    mutable CONDITION_VARIABLE                          paused;
    bool                                            	isPaused;
    bool                                                isScheduledPaced;
    bool                                                isLooping;
    double                                          	targetDownload;
    double                                              downloadingTime;
    adaptation::IAdaptationLogic                        *adaptationLogic;
    IICNConnection                                      *conn;
    IICNConnection                                      *initConn;
    THREAD_HANDLE                                       bufferingThread;
    THREAD_HANDLE                                       mpdFetcherThread;
    bool                                                isBuffering;
    bool                                                icn;
    double                                              icnAlpha;
    int                                                 previousQuality;
    int                                                 bufferLevelAtUpdate;
    int                                                 readMax;
    uint8_t                                             *readBuffer;
    viper::managers::StreamType 			type;
    uint32_t CalculateSegmentOffset();
    void NotifySegmentDownloaded();
//    void DownloadInitSegment(dash::mpd::IRepresentation* rep);
    void DownloadInitSegment();
    void DownloadInitSegmentWithoutLock();
//    bool InitSegmentExists(dash::mpd::IRepresentation* rep);
    bool InitSegmentExists(int rep);
    static void* DoBuffering(void *receiver);
    static void* DoMPDFetching(void * data);
};
}
}
}

#endif /* LIBDASH_FRAMEWORK_INPUT_DASHRECEIVER_H_ */