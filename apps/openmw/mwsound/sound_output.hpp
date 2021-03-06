#ifndef GAME_SOUND_SOUND_OUTPUT_H
#define GAME_SOUND_SOUND_OUTPUT_H

#include <string>
#include <memory>

#include "soundmanagerimp.hpp"

#include "../mwworld/ptr.hpp"

namespace MWSound
{
    class SoundManager;
    struct Sound_Decoder;
    class Sound;
    class Sound_Loudness;

    // An opaque handle for the implementation's sound buffers.
    typedef void *Sound_Handle;

    class Sound_Output
    {
        SoundManager &mManager;

        virtual std::vector<std::string> enumerate() = 0;
        virtual void init(const std::string &devname="") = 0;
        virtual void deinit() = 0;

        virtual Sound_Handle loadSound(const std::string &fname) = 0;
        virtual void unloadSound(Sound_Handle data) = 0;
        virtual size_t getSoundDataSize(Sound_Handle data) const = 0;

        /// @param offset Value from [0,1] meaning from which fraction the sound the playback starts.
        virtual MWBase::SoundPtr playSound(Sound_Handle data, float vol, float basevol, float pitch, int flags, float offset) = 0;
        /// @param offset Value from [0,1] meaning from which fraction the sound the playback starts.
        virtual MWBase::SoundPtr playSound3D(Sound_Handle data, const osg::Vec3f &pos,
                                             float vol, float basevol, float pitch, float min, float max, int flags, float offset) = 0;
        virtual MWBase::SoundPtr streamSound(DecoderPtr decoder, float basevol, float pitch, int flags) = 0;
        virtual MWBase::SoundPtr streamSound3D(DecoderPtr decoder, const osg::Vec3f &pos,
                                               float vol, float basevol, float pitch, float min, float max, int flags) = 0;

        virtual void startUpdate() = 0;
        virtual void finishUpdate() = 0;

        virtual void updateListener(const osg::Vec3f &pos, const osg::Vec3f &atdir, const osg::Vec3f &updir, Environment env) = 0;

        virtual void pauseSounds(int types) = 0;
        virtual void resumeSounds(int types) = 0;

        Sound_Output& operator=(const Sound_Output &rhs);
        Sound_Output(const Sound_Output &rhs);

    protected:
        bool mInitialized;
        osg::Vec3f mPos;

        Sound_Output(SoundManager &mgr)
          : mManager(mgr)
          , mInitialized(false)
          , mPos(0.0f, 0.0f, 0.0f)
        { }
    public:
        virtual ~Sound_Output() { }

        bool isInitialized() const { return mInitialized; }

        friend class OpenAL_Output;
        friend class SoundManager;
    };
}

#endif
