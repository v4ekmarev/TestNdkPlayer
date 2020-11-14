//
// Created by Pavel Konev on 11/15/20.
//

#include <array>
#include <algorithm>
#include <cassert>

#include "Player.h"
#include "OpenSLPlayer.h"

namespace avtools
{
    namespace
    {
        const std::array<std::string, 1> supported_audio_file_types = { "aac" };
        const std::array<std::string, 0> supported_video_file_types = { };
    }

    /*static*/ std::unique_ptr<Player> Player::create(std::string file_path, ErrorCode &error_code)
    {
        assert(!file_path.empty());
        Player* player = nullptr;
        error_code = ErrorCode::NoError;
        const auto extension = file_path.substr(file_path.find_last_of('.') + 1);
        const auto pred = [&](const std::string& type){ return type == extension; };
        if (std::any_of(supported_audio_file_types.begin(), supported_audio_file_types.end(), pred))
        {
            auto opensl_player = std::make_unique<OpenSLPlayer>();
            error_code = opensl_player->init(std::move(file_path));
            if (error_code == ErrorCode::NoError)
                player = opensl_player.release();
        }
        else if (std::any_of(supported_video_file_types.begin(), supported_video_file_types.end(), pred))
        {
            error_code = ErrorCode::NotSupported;
        }

        return std::unique_ptr<Player>(player);
    }

    Player::Player() = default;
    Player::~Player() = default;

    Player::StateId Player::get_state_id() const
    {
        return Player::StateId::Error;
    }

    FileDuration Player::get_duration() const
    {
        return 0;
    }

    PlaybackPosition Player::get_position() const
    {
        return 0;
    }

    PlaybackSpeed Player::get_speed() const
    {
        return 0;
    }

    VolumeLevel Player::get_volume_level() const
    {
        return 0;
    }

    ErrorCode Player::set_position(PlaybackPosition position)
    {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::set_speed(PlaybackSpeed speed)
    {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::set_volume_level(VolumeLevel volume_level)
    {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::start()
    {
        return ErrorCode::NotSupported;
    }

    void Player::stop()
    {
    }
}
