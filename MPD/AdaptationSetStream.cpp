/*
 * AdaptationSetStream.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AdaptationSetStream.h"

using namespace libdash::framework::mpd;
using namespace dash::mpd;

AdaptationSetStream::AdaptationSetStream(viper::managers::StreamType type, MPDWrapper *mpdWrapper) :
    mpdWrapper			(mpdWrapper),
    type			(type)
//    period              (period),
//    adaptationSet       (adaptationSet)
{
    initialize();
}

AdaptationSetStream::~AdaptationSetStream()
{
    this->mpdWrapper->destroyAdaptationSetStream(type);
//    std::map<IRepresentation *, IRepresentationStream *>::iterator iter;
//    for (iter = representations.begin(); iter != representations.end(); ++iter)
//    {
//        delete(iter->second);
//    }
}

//IRepresentationStream* AdaptationSetStream::getRepresentationStream(IRepresentation *representation)
//{
//    return this->representations.find(representation)->second;
//}

//RepresentationStreamType AdaptationSetStream::determineRepresentationStreamType (IRepresentation *representation)
//{
//    /* check on Representation Level */
//    if (representation->GetSegmentList())
//        return libdash::framework::mpd::SegmentList;
//
//    if (representation->GetSegmentTemplate())
//        return libdash::framework::mpd::SegmentTemplate;
//
//    if (representation->GetSegmentBase() || representation->GetBaseURLs().size() > 0)
//        return libdash::framework::mpd::SingleMediaSegment;
//
//    /* check on AdaptationSet Level */
//    if (this->adaptationSet->GetSegmentList())
//        return libdash::framework::mpd::SegmentList;
//
//    if (this->adaptationSet->GetSegmentTemplate())
//        return libdash::framework::mpd::SegmentTemplate;
//
//    if (this->adaptationSet->GetSegmentBase())
//        return libdash::framework::mpd::SingleMediaSegment;
//
//    /* check on Period Level */
//    if (this->period->GetSegmentList())
//        return libdash::framework::mpd::SegmentList;
//
//    if (this->period->GetSegmentTemplate())
//        return libdash::framework::mpd::SegmentTemplate;
//
//    if (this->period->GetSegmentBase())
//        return libdash::framework::mpd::SingleMediaSegment;
//
//    return libdash::framework::mpd::UNDEFINED;
//}

void AdaptationSetStream::initialize()
{
    this->mpdWrapper->initializeAdaptationSetStream(type);
//    for (size_t i = 0; i < adaptationSet->GetRepresentation().size(); i++)
//    {
//        IRepresentation *representation = adaptationSet->GetRepresentation().at(i);
//        RepresentationStreamType type   = determineRepresentationStreamType(representation);
//        representations[representation] = RepresentationStreamFactory::create(type, mpd, period, adaptationSet, representation);
//    }
}