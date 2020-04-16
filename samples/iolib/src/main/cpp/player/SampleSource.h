/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _PLAYER_SAMPLESOURCE_
#define _PLAYER_SAMPLESOURCE_

#include <cstdint>

#include "DataSource.h"

#include "SampleBuffer.h"

namespace iolib {

/**
 * Defines an interface for audio data provided to a player object.
 * Concrete examples include OneShotSampleBuffer. One could imagine a LoopingSampleBuffer.
 * Supports stereo position via mPan member.
 */
class SampleSource: public DataSource {
public:
    // Pan position of the audio in a stereo mix
    // [left:-1.0f] <- [center: 0.0f] -> -[right: 1.0f]
    static constexpr float PAN_HARDLEFT = -1.0f;
    static constexpr float PAN_HARDRIGHT = 1.0f;
    static constexpr float PAN_CENTER = 0.0f;

    SampleSource(SampleBuffer *sampleBuffer, float pan)
     : mSampleBuffer(sampleBuffer), mCurFrameIndex(0), mIsPlaying(false), mPan(pan) {};
    virtual ~SampleSource() {};

    void setPlayMode() { mCurFrameIndex = 0; mIsPlaying = true; }
    void setStopMode() { mIsPlaying = false; mCurFrameIndex = 0; }

    bool isPlaying() { return mIsPlaying; }

    void setPan(float pan) {
        if (pan < PAN_HARDLEFT) {
            mPan = PAN_HARDLEFT;
        } else if (pan > PAN_HARDRIGHT) {
            mPan = PAN_HARDRIGHT;
        } else {
            mPan = pan;
        }
    }

protected:
    SampleBuffer    *mSampleBuffer;

    int32_t mCurFrameIndex;

    bool mIsPlaying;

    float mPan;
};

} // namespace wavlib

#endif //_PLAYER_SAMPLESOURCE_
