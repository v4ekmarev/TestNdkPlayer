//
// Created by Pavel Konev on 11/15/20.
//

#pragma once

namespace avtools
{
    enum class ErrorCode
    {
        NoError,
        UnknownFormat,
        InvalidArgs,
        OutOfBounds,
        NotSupported,
        UnknownError
    };

    using FileDuration     = uint32_t; // ms
    using PlaybackPosition = uint32_t; // ms
    using PlaybackSpeed    = float;
    using VolumeLevel      = float;
}
