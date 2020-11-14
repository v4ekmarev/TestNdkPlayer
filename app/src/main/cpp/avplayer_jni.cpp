//
// Created by Pavel Konev on 11/6/20.
//

#include <jni.h>
#include <cstdio>
#include <cassert>
#include <memory>

#include "CommonTypes.h"
#include "Player.h"

namespace avtools
{
    std::unique_ptr<avtools::Player> st_player;

    const char* error_code_name(avtools::ErrorCode error_code)
    {
        switch (error_code)
        {
            case avtools::ErrorCode::NoError:       return "NoError";
            case avtools::ErrorCode::UnknownFormat: return "UnknownFormat";
            case avtools::ErrorCode::InvalidArgs:   return "InvalidArgs";
            case avtools::ErrorCode::OutOfBounds:   return "OutOfBounds";
            case avtools::ErrorCode::NotSupported:  return "NotSupported";
            case avtools::ErrorCode::UnknownError:  return "UnknownError";
            default:                                return nullptr;
        }
    }

    jobject error_code_to_jni(JNIEnv *env, avtools::ErrorCode error_code)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,
                error_code_name(error_code), "Lcom/avtools/player/Player/ErrorCode;"));
    }

    const char* state_id_name(avtools::Player::StateId state_id)
    {
        switch (state_id)
        {
            case avtools::Player::StateId::Stopped: return "Stopped";
            case avtools::Player::StateId::Started: return "Started";
            case avtools::Player::StateId::Paused:  return "Paused";
            case avtools::Player::StateId::Error:   return "Error";
            default:                                return nullptr;
        }
    }

    jobject state_id_to_jni(JNIEnv *env, avtools::Player::StateId state_id)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$StateId");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,
                state_id_name(state_id), "Lcom/avtools/player/Player/StateId;"));
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_init(JNIEnv *env, jobject thiz, jstring file_path)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,"ResourceBusy", "Lcom/avtools/player/Player/ErrorCode;"));
    }

    jboolean isCopy;
    const char* const convertedValue = env->GetStringUTFChars(file_path, &isCopy);
    assert(convertedValue);

    auto error_code = avtools::ErrorCode::NoError;
    avtools::st_player = avtools::Player::create(convertedValue, error_code);

    fprintf(stdout, "%s: result = %s\n", __FUNCTION__, avtools::error_code_name(error_code));
    return avtools::error_code_to_jni(env, error_code);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_avtools_player_Player_uninit(JNIEnv *env, jobject thiz)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (avtools::st_player)
        avtools::st_player.reset();
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_start(JNIEnv *env, jobject thiz)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (!avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,"NotInitialized", "Lcom/avtools/player/Player/ErrorCode;"));
    }

    return avtools::error_code_to_jni(env, avtools::st_player->start());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_avtools_player_Player_stop(JNIEnv *env, jobject thiz)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (!avtools::st_player)
        return;

    avtools::st_player->stop();
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_setSpeed(JNIEnv *env, jobject thiz, jfloat speed)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (!avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,"NotInitialized", "Lcom/avtools/player/Player/ErrorCode;"));
    }

    return avtools::error_code_to_jni(env, avtools::st_player->set_speed(speed));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_setPosition(JNIEnv *env, jobject thiz, jfloat position)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (!avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,"NotInitialized", "Lcom/avtools/player/Player/ErrorCode;"));
    }

    return avtools::error_code_to_jni(env, avtools::st_player->set_position(position * 1000));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_setVolume(JNIEnv *env, jobject thiz, jfloat volume)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    if (!avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$ErrorCode");
        return env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls,"NotInitialized", "Lcom/avtools/player/Player/ErrorCode;"));
    }

    return avtools::error_code_to_jni(env, avtools::st_player->set_volume_level(volume));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_avtools_player_Player_getState(JNIEnv *env, jobject thiz)
{
    fprintf(stdout, "%s: called\n", __FUNCTION__ );

    jclass state_cls = env->FindClass("com/avtools/player/Player$State");
    jmethodID state_ctor = env->GetMethodID(state_cls, "<init>", "(Lcom/avtools/player/Player/StateId;FFFF)V");

    if (!avtools::st_player)
    {
        jclass id_cls = env->FindClass("com/avtools/player/Player$StateId");
        jobject not_initialized = env->GetStaticObjectField(id_cls, env->GetStaticFieldID(id_cls, "NotInitialized", "Lcom/avtools/player/Player/StateId;"));
        return env->NewObject(state_cls, state_ctor, not_initialized, 0.0f, 0.0f, 0.0f, 0.0f);
    }

    const auto state = avtools::st_player->get_state_id();
    return env->NewObject(state_cls, state_ctor, avtools::state_id_to_jni(env, state),
                          avtools::st_player->get_duration() / 1000.0f,
                          avtools::st_player->get_position() / 1000.0f, avtools::st_player->get_speed(),
                          avtools::st_player->get_volume_level());
}
