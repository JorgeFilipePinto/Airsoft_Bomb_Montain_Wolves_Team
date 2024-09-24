package com.example.montainwolvesapp;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Switch;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    Switch gps, leds, sound, smoke;
    Button sendConfig;
    ImageButton playPause;
    ImageView teamLogo;
    MediaPlayer mediaPlayer = new MediaPlayer();

    boolean musicSound, gpsEnable, ledsEnable, smokeEnable;

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
        sound = (Switch) findViewById(R.id.sw_sound);
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
                    gps.setText(R.string.switch_gps_on);

                }else{gps.setText(R.string.switch_gps_off); }
            }
        });

        leds.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(leds.isChecked()){
                    leds.setText(R.string.switch_leds_on);

                }else{leds.setText(R.string.switch_leds_off); }
            }
        });

        smoke.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(smoke.isChecked()){
                    smoke.setText(R.string.switch_smoke_on);

                }else{smoke.setText(R.string.switch_smoke_off); }
            }
        });

        sound.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(sound.isChecked()){
                    sound.setText(R.string.switch_sound_on);
                }else {
                    sound.setText(R.string.switch_sound_off);
                }
            }
        });


        sendConfig.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });


    }


    public void introSound(){
        if(musicSound){
            musicSound = false;
            playPause.setImageResource(R.drawable.ic_play);
        }else{
            musicSound = true;
            playPause.setImageResource(R.drawable.ic_pause);
        }

        if(musicSound) {
            mediaPlayer.start();
        }else{
            mediaPlayer.pause();
        }
    }

}