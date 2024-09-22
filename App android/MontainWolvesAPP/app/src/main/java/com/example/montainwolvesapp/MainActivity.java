package com.example.montainwolvesapp;

import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    Switch gps, leds, smoke;
    Button sendConfig;
    ImageButton playPause;
    ImageView teamLogo;
    MediaPlayer mediaPlayer = new MediaPlayer();
    boolean sound = true;
    boolean gpsEnable, ledsEnable, smokeEnable;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mediaPlayer = MediaPlayer.create(this,R.raw.intro);
        mediaPlayer.start();
        playPause = (ImageButton) findViewById(R.id.play_pause_intro);
        gps = (Switch) findViewById(R.id.sw_gps);
        leds = (Switch) findViewById(R.id.sw_leds);
        smoke = (Switch) findViewById(R.id.sw_smoke);
        sendConfig = (Button) findViewById(R.id.btn_send_config);

        
        playPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                introSound();
            }
        });

        gps.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(gps.isChecked()){
                    gps.setText("gps ON");

                }else{gps.setText("gps Off"); }
            }
        });

        leds.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(leds.isChecked()){
                    leds.setText("leds ON");

                }else{leds.setText("leds Off"); }
            }
        });

        smoke.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(smoke.isChecked()){
                    smoke.setText("smoke ON");

                }else{smoke.setText("smoke Off"); }
            }
        });

        sendConfig.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

    }


    public void introSound(){
        if(sound){
            sound = false;
            playPause.setImageResource(R.drawable.ic_play);
        }else{
            sound = true;
            playPause.setImageResource(R.drawable.ic_pause);
        }

        if(sound) {
            mediaPlayer.start();
        }else{
            mediaPlayer.pause();
        }
    }

}