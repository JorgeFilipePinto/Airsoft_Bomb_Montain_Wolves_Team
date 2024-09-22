package com.example.montainwolvesapp;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
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
            return true;
        }else if (item.getItemId() == R.id.settings) {
            Toast.makeText(this,item + " Selected!", Toast.LENGTH_SHORT).show();
            return true;
        } else if (item.getItemId() == R.id.contact_us) {
            Toast.makeText(this,item + " Selected!", Toast.LENGTH_SHORT).show();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    public void home(){

    }

    public void settings(){

    }
    
    public void contactUs(){

    }
}