//
// Created by Pavel Konev on 11/15/20.
//

#include "OpenSLPlayer.h"

namespace avtools
{

#define CHECK_SL_ERROR() \
    if (SL_RESULT_SUCCESS != result) { \
        fprintf(stdout, "%s: SLresult = %d\n", __PRETTY_FUNCTION__, result); \
        return ErrorCode::UnknownError; \
    }

    OpenSLPlayer::~OpenSLPlayer()
    {
        // destroy output mix object, and invalidate all associated interfaces
        if (m_output_mix_object != nullptr)
        {
            (*m_output_mix_object)->Destroy(m_output_mix_object);
            m_output_mix_object = nullptr;
            m_output_mix_environmental_reverb = nullptr;
        }

        // destroy engine object, and invalidate all associated interfaces
        if (m_engine_object != nullptr)
        {
            (*m_engine_object)->Destroy(m_engine_object);
            m_engine_object = nullptr;
            m_engine_object = nullptr;
        }
    }

    ErrorCode OpenSLPlayer::init(std::string file_path)
    {
        assert(!file_path.empty());

        // create engine
        SLresult result = slCreateEngine(&m_engine_object, 0, nullptr, 0, nullptr, nullptr);
        CHECK_SL_ERROR();

        // realize the engine
        result = (*m_engine_object)->Realize(m_engine_object, SL_BOOLEAN_FALSE);
        CHECK_SL_ERROR();

        // get the engine interface, which is needed in order to create other objects
        result = (*m_engine_object)->GetInterface(m_engine_object, SL_IID_ENGINE, &m_engine_engine);
        CHECK_SL_ERROR();

        // create output mix, with environmental reverb specified as a non-required interface
        const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
        const SLboolean req[1] = { SL_BOOLEAN_FALSE };
        result = (*m_engine_engine)->CreateOutputMix(m_engine_engine, &m_output_mix_object, 1, ids, req);
        CHECK_SL_ERROR();

        // realize the output mix
        result = (*m_output_mix_object)->Realize(m_output_mix_object, SL_BOOLEAN_FALSE);
        CHECK_SL_ERROR();

        // get the environmental reverb interface
        // this could fail if the environmental reverb effect is not available,
        // either because the feature is not present, excessive CPU load, or
        // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
        result = (*m_output_mix_object)->GetInterface(m_output_mix_object, SL_IID_ENVIRONMENTALREVERB, &m_output_mix_environmental_reverb);
        if (SL_RESULT_SUCCESS == result)
        {
            // aux effect on the output mix, used by the buffer queue player
            static const SLEnvironmentalReverbSettings reverb_settings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
            result = (*m_output_mix_environmental_reverb)->SetEnvironmentalReverbProperties(m_output_mix_environmental_reverb, &reverb_settings);
            CHECK_SL_ERROR();
        }

        // TODO: implement playback from buffer
        return ErrorCode::NoError;
    }

    ErrorCode OpenSLPlayer::start()
    {
        return ErrorCode::NotSupported;
    }

    void OpenSLPlayer::stop()
    {
    }
}
