//
// Created by Pavel Konev on 11/15/20.
//

#pragma once

#include "Player.h"

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace avtools
{
    class OpenSLPlayer : public Player
    {
    public:
        OpenSLPlayer() = default;
        virtual ~OpenSLPlayer() override;

        ErrorCode init(std::string file_path);

    private:
        virtual ErrorCode start() override;
        virtual void stop() override;

    private:
        SLObjectItf m_engine_object = nullptr;
        SLEngineItf m_engine_engine;
        SLObjectItf m_output_mix_object = nullptr;
        SLEnvironmentalReverbItf m_output_mix_environmental_reverb = nullptr;
    };
}
