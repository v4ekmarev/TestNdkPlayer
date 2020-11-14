//
// Created by Pavel Konev on 11/6/20.
//

package com.avtools.player;

public class Player
{
    public enum StateId
    {
        NotInitialized,
        Stopped,
        Started,
        Paused,
        Error
    };

    public enum ErrorCode
    {
        NoError,
        NotInitialized,
        UnknownFormat,
        InvalidArgs,
        OutOfBounds,
        ResourceBusy,
        NotSupported,
        UnknownError
    };

    public class State
    {
        private State(StateId idArg, float durationArg, float positionArg, float speedArg, float volumeArg)
        {
            id       = idArg;
            duration = durationArg;
            position = positionArg;
            speed    = speedArg;
            volume   = volumeArg;
        }

        public StateId id;
        public float   duration;
        public float   position;
        public float   speed;
        public float   volume;
    };

    /*
     * Initialize AV player.
     * @param filePath file path
     */
    public native ErrorCode init(String filePath);

    /*
     * Destroy AV player.
     */
    public native void uninit();

    /**
     * Start AV player.
     * @return error code
     */
    public native ErrorCode start();

    /**
     * Stop AV player.
     */
    public native void stop();

    /**
     * Set playback speed (1x supported only).
     * @return error code
     */
    public native ErrorCode setSpeed(float speed);

    /**
     * Set playback position (0-duration).
     * @return error code
     */
    public native ErrorCode setPosition(float position);

    /**
     * Set volume (0-1).
     * @return error code
     */
    public native ErrorCode setVolume(float volume);

    /**
     * Get player state.
     * @return state
     */
    public native State getState();
}
