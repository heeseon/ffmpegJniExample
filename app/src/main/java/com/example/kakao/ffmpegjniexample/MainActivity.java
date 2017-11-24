package com.example.kakao.ffmpegjniexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.ButtonBarLayout;
import android.view.View;
import android.widget.Button;

import java.io.File;
import java.io.IOException;

import android.os.Environment;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button tempBtn = (Button) findViewById(R.id.button);

        tempBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String filepath = "";
                String filepath2 = "";

                try {
                    filepath = new File(Environment.getExternalStorageDirectory(), "example.mp4").getCanonicalPath();
                    filepath2 = new File(Environment.getExternalStorageDirectory(), "example_changed.mp4").getCanonicalPath();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                String commands[] = new String[8];

                commands[0] =  "ffmpeg";

                commands[1]  = "-i";

                commands[2]  = filepath;

                commands[3]  = "-vcodec";

                commands[4]  = "h264";

                commands[5]  = "-acodec";

                commands[6]  = "mp3";

                commands[7]  = filepath2;

                new NDK().run_ffmpeg(commands);

            }
        });

    }
}
