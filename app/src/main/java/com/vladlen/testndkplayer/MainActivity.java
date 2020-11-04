package com.vladlen.testndkplayer;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import com.getkeepsafe.relinker.ReLinker;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "TEST_NDK";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //тут загружать .so
        ReLinker.loadLibrary(this, "fanplayer_jni", new ReLinker.LoadListener() {
            @Override
            public void success() {
                Log.d(TAG, "success");
            }

            @Override
            public void failure(Throwable t) {
                Log.d(TAG, t.getMessage());
            }
        });

        //create
        findViewById(R.id.btn_create).setOnClickListener(v -> {

        });

        //destroy
        findViewById(R.id.btn_destroy).setOnClickListener(v -> {

        });

        //get duration
        findViewById(R.id.btn_get_duration).setOnClickListener(v -> {

        });

        //get position
        findViewById(R.id.btn_get_position).setOnClickListener(v -> {

        });

        //pause
        findViewById(R.id.btn_pause).setOnClickListener(v -> {

        });

        //resume
        findViewById(R.id.btn_resume).setOnClickListener(v -> {

        });

        //start
        findViewById(R.id.btn_start).setOnClickListener(v -> {

        });

        //seek
        findViewById(R.id.btn_seek).setOnClickListener(v -> {

        });

        //get state
        findViewById(R.id.btn_get_state).setOnClickListener(v -> {

        });

        //set volume
        findViewById(R.id.btn_volume).setOnClickListener(v -> {

        });
    }
}