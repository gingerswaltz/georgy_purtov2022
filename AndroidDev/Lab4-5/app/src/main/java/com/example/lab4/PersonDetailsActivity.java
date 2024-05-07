package com.example.lab4;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class PersonDetailsActivity extends AppCompatActivity {

    public static final String EXTRA_PERSON_NAME = "extra_person_name";
    public static final String EXTRA_PERSON_PHONE = "extra_person_phone";
    public static final String EXTRA_PERSON_EMAIL = "extra_person_email";
    public static final String EXTRA_PERSON_ADDRESS = "extra_person_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_person_details);

        Intent intent = getIntent();
        if (intent != null && intent.hasExtra(EXTRA_PERSON_NAME)
                && intent.hasExtra(EXTRA_PERSON_PHONE)
                && intent.hasExtra(EXTRA_PERSON_EMAIL)
                && intent.hasExtra(EXTRA_PERSON_ADDRESS)) {
            String personName = intent.getStringExtra(EXTRA_PERSON_NAME);

            String personPhone = intent.getStringExtra(EXTRA_PERSON_PHONE);
            String phoneNumberLabel = getResources().getString(R.string.label_phone_number);
            String formattedPhoneNumber = String.format(phoneNumberLabel, personPhone);


            String personEmail = intent.getStringExtra(EXTRA_PERSON_EMAIL);
            String emailLabel = getResources().getString(R.string.label_email);
            String formattedEmail = String.format(emailLabel, personEmail);

            String personAddress = intent.getStringExtra(EXTRA_PERSON_ADDRESS);
            String addressLabel = getResources().getString(R.string.label_address);
            String formattedAddress = String.format(addressLabel, personAddress);

            TextView nameTextView = findViewById(R.id.nameTextView);
            TextView phoneNumberTextView = findViewById(R.id.phoneNumberTextView);
            TextView emailTextView = findViewById(R.id.emailTextView);
            TextView addressTextView = findViewById(R.id.addressTextView);

            nameTextView.setText(personName);
            phoneNumberTextView.setText(formattedPhoneNumber);
//            emailTextView.setText(personEmail);
            emailTextView.setText(formattedEmail);
            addressTextView.setText(formattedAddress);
        }
    }
}