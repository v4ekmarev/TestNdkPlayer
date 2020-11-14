package com.vladlen.testndkplayer;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import com.avtools.player.Player;
import com.getkeepsafe.relinker.ReLinker;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "TEST_NDK";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //тут загружать .so
        ReLinker.loadLibrary(this, "audioplayer-lib", new ReLinker.LoadListener() {
            @Override
            public void success() {
                Log.d(TAG, "success");
            }

            @Override
            public void failure(Throwable t) {
                Log.d(TAG, t.getMessage());
            }
        });

        Player player = new Player();

        //create
        findViewById(R.id.btn_create).setOnClickListener(v -> {
            player.init("foo.aac");
        });

        //destroy
        findViewById(R.id.btn_destroy).setOnClickListener(v -> {
            player.uninit();
        });

        //get duration
        findViewById(R.id.btn_get_duration).setOnClickListener(v -> {
            Log.d(TAG, "duration: " + player.getState().duration);
        });

        //get position
        findViewById(R.id.btn_get_position).setOnClickListener(v -> {
            Log.d(TAG, "position: " + player.getState().position);
        });

        //pause
        findViewById(R.id.btn_pause).setOnClickListener(v -> {
            player.setSpeed(0);
        });

        //resume
        findViewById(R.id.btn_resume).setOnClickListener(v -> {
            player.setSpeed(1);
        });

        //start
        findViewById(R.id.btn_start).setOnClickListener(v -> {
            player.setPosition(0);
            player.setSpeed(1);
        });

        //seek
        findViewById(R.id.btn_seek).setOnClickListener(v -> {
            player.setPosition(player.getState().duration / 2);
        });

        //get state
        findViewById(R.id.btn_get_state).setOnClickListener(v -> {
            Log.d(TAG, "state: " + player.getState().id);
        });

        //set volume
        findViewById(R.id.btn_volume).setOnClickListener(v -> {
            player.setVolume(0.5f);
        });
    }
}