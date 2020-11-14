//
// Created by Pavel Konev on 11/15/20.
//

#include "Player.h"

namespace avtools
{
    /*static*/ std::unique_ptr<Player> Player::create(std::string file_path, ErrorCode &error_code) {
        return std::unique_ptr<Player>();
    }

    Player::Player() {
    }

    Player::~Player() {

    }

    Player::StateId Player::get_state_id() const {
        return Player::StateId::Error;
    }

    FileDuration Player::get_duration() const {
        return 0;
    }

    PlaybackPosition Player::get_position() const {
        return 0;
    }

    PlaybackSpeed Player::get_speed() const {
        return 0;
    }

    VolumeLevel Player::get_volume_level() const {
        return 0;
    }

    ErrorCode Player::set_position(PlaybackPosition position) {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::set_speed(PlaybackSpeed speed) {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::set_volume_level(VolumeLevel volume_level) {
        return ErrorCode::NotSupported;
    }

    ErrorCode Player::start() {
        return ErrorCode::NotSupported;
    }

    void Player::stop() {

    }
}
