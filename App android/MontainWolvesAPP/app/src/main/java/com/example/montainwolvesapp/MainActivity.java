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
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    ImageButton playPause;
    ImageView teamLogo;
    MediaPlayer mediaPlayer = new MediaPlayer();
    boolean sound = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mediaPlayer = MediaPlayer.create(this,R.raw.intro);
        mediaPlayer.start();
        playPause = (ImageButton) findViewById(R.id.play_pause_intro);


        playPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(sound){
                    sound = false;
                    playPause.setImageResource(R.drawable.ic_play);
                }else{
                    sound = true;
                    playPause.setImageResource(R.drawable.ic_pause);
                }
                introSound();
            }
        });

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.my_menu, menu);
        return true;
    }


    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        if(item.getItemId() == R.id.home){
            Toast.makeText(this,item + " Selected!", Toast.LENGTH_SHORT).show();
            home();
            return true;
        }else if (item.getItemId() == R.id.settings) {
            Toast.makeText(this, item + " Selected!", Toast.LENGTH_SHORT).show();
            settings();
            return true;
        }else if(item.getItemId() == R.id.team){
            Toast.makeText(this,item + " Selected!", Toast.LENGTH_SHORT).show();
            team();
            return true;
        } else if (item.getItemId() == R.id.contact_us) {
            Toast.makeText(this,item + " Selected!", Toast.LENGTH_SHORT).show();
            contactUs();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    public void introSound(){
        if(sound) {
            mediaPlayer.start();
        }else{
            mediaPlayer.pause();
        }
    }


    public void home(){
        mediaPlayer.start();
        setContentView(R.layout.activity_main);
    }


    public void settings(){
        mediaPlayer.pause();
        setContentView(R.layout.activity_settings);
    }


    public void team(){
        mediaPlayer.pause();
        setContentView(R.layout.team);
    }


    public void contactUs(){
        mediaPlayer.pause();
        setContentView(R.layout.activity_contact_us);
    }
}