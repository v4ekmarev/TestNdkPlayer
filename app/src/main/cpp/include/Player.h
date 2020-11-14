//
// Created by Pavel Konev on 11/15/20.
//

#pragma once

#include <string>
#include "CommonTypes.h"

namespace avtools
{
    class Player
    {
    public:
        enum class StateId
        {
            Stopped,
            Started,
            Paused,
            Error
        };

        static std::unique_ptr<Player> create(std::string file_path, ErrorCode& error_code /* out */);

        virtual ~Player();

        virtual ErrorCode start();
        virtual void stop();

        virtual StateId get_state_id() const;
        virtual FileDuration get_duration() const;
        virtual PlaybackPosition get_position() const;
        virtual PlaybackSpeed get_speed() const;
        virtual VolumeLevel get_volume_level() const;

        virtual ErrorCode set_position(PlaybackPosition position);
        virtual ErrorCode set_speed(PlaybackSpeed speed);
        virtual ErrorCode set_volume_level(VolumeLevel volume_level);

    protected:
        Player();
    };
}
