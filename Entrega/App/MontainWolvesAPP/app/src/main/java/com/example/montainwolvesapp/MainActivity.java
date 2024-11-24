package com.example.montainwolvesapp;
import static android.content.ContentValues.TAG;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import java.io.IOException;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

//Criação dos meus objetos
    Switch gps, leds, sound, smoke;
    Button sendConfig, setCoordinates;
    ImageButton playPause;
    ImageView teamLogo;
    MediaPlayer mediaPlayer = new MediaPlayer();
    EditText timeBomb, timeGame, numPlayers, bombCode;
    boolean musicSound;

    private BluetoothAdapter bluetoothAdapter;
    private BluetoothSocket bluetoothSocket;
    private BluetoothDevice bluetoothDevice;
    private OutputStream outputStream;

    private final String DEVICE_ADDRESS = "08:A6:F7:20:B3:1E"; // Coloque o endereço MAC do seu módulo Bluetooth
    private final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//Declaração dos meus objetos
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        bluetoothDevice = bluetoothAdapter.getRemoteDevice(DEVICE_ADDRESS);

        mediaPlayer = MediaPlayer.create(this, R.raw.intro);
        mediaPlayer.start();
        playPause = (ImageButton) findViewById(R.id.play_pause_intro);
        gps = (Switch) findViewById(R.id.sw_gps);
        leds = (Switch) findViewById(R.id.sw_leds);
        smoke = (Switch) findViewById(R.id.sw_smoke);
        sound = (Switch) findViewById(R.id.sw_sound);
        sendConfig = (Button) findViewById(R.id.btn_send_config);
        setCoordinates = (Button) findViewById(R.id.setCoordinates);
        timeGame = (EditText) findViewById(R.id.edit_text_time_game);
        timeBomb = (EditText) findViewById(R.id.edit_text_time_bomb);
        numPlayers = (EditText) findViewById(R.id.edit_text_players);
        bombCode = (EditText) findViewById(R.id.edit_text_bomb_Code);


//Envia o tempo de jogo
        timeGame.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = "TIMEG" + timeGame.getText().toString() + "\n";
                sendData(message);
            }
        });

//Envia o confirmação para configuração de coordenadas
        setCoordinates.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = "setCoordinates" + "\n";
                sendData(message);
            }
        });

//Envia o tempo da bomba
        timeBomb.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = "TIMEB" + timeGame.getText().toString() + "\n";
                sendData(message);
            }
        });

//Envia o número de jogadores
        numPlayers.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = "TEAM" + numPlayers.getText().toString() + "\n";
                sendData(message);
            }
        });


//Envia o código da bomba
        bombCode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (bombCode.length() == Integer.parseInt(numPlayers.getText().toString())){
                    String message = "CODE" + bombCode.getText().toString() + "\n";
                    sendData(message);
                }else{
                    Toast.makeText(MainActivity.this,
                            "Bomb Code Size let be the same of Players Number",
                            Toast.LENGTH_LONG).show();
                }
            }
        });


        playPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                introSound();
            }
        });


//Controla a activação ou desativação do gps
        gps.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (gps.isChecked()) {
                    String message = "gpsON\n";
                    sendData(message);
                } else {
                    String message = "gpsOFF\n";
                    sendData(message);
                }
            }
        });
//Controla a activação ou desativação dos leds
        leds.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message;
                if (leds.isChecked()) {
                    leds.setText(R.string.switch_leds_on);
                    message = "ledsON\n";
                } else {
                    leds.setText(R.string.switch_leds_off);
                    message = "ledsOFF\n";

                }
                sendData(message);
            }
        });
//Controla a activação ou desativação do fumo
        smoke.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message;
                if (smoke.isChecked()) {
                    smoke.setText(R.string.switch_smoke_on);
                    message = "smokeON\n";
                } else {
                    smoke.setText(R.string.switch_smoke_off);
                    message = "smokeOFF\n";
                }
                sendData(message);
            }
        });
//Controla a activação ou desativação do som da bomba
        sound.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message;
                if (sound.isChecked()) {
                    sound.setText(R.string.switch_sound_on);
                    message = "soundON\n";
                } else {
                    sound.setText(R.string.switch_sound_off);
                    message = "soundOFF\n";
                }
                sendData(message);
            }
        });
//Envia a confirmação da configuração
        sendConfig.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String message = "sendConfig";
                sendData(message);
            }
        });

        connectBluetooth();

    }
//Controlo do audio da aplicação
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
//conecta ao bluetooth do macAddress indicado
    private void connectBluetooth() {
        try {
            bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(MY_UUID);
            bluetoothSocket.connect();
            outputStream = bluetoothSocket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
//Envia a menssagem
    private void sendData(String message) {
        try {
            outputStream.write(message.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        try {
            bluetoothSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}