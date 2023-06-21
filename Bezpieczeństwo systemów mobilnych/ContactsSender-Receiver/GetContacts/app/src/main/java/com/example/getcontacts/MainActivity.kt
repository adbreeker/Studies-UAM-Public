package com.example.getcontacts

import android.app.Activity
import android.content.Context
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Bundle
import android.telephony.SmsManager
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.async
import kotlinx.coroutines.launch
import java.util.*

class MainActivity : AppCompatActivity() {


    var gotContacts = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        if(ActivityCompat.checkSelfPermission(this, android.Manifest.permission.SEND_SMS) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, arrayOf(android.Manifest.permission.SEND_SMS), 1)
        }



        findViewById<Button>(R.id.bts_send).setOnClickListener{
            if(ActivityCompat.checkSelfPermission(this, android.Manifest.permission.SEND_SMS) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, arrayOf(android.Manifest.permission.SEND_SMS), 1)
            }
            else
            {
                val smsManager: SmsManager = SmsManager.getDefault()
                val number = findViewById<EditText>(R.id.number).text.toString()
                smsManager.sendTextMessage(number, null, "Give me contacts, secret code: okoń", null, null)
                Toast.makeText(this,"Request sent", Toast.LENGTH_SHORT).show()

                findViewById<Button>(R.id.bts_send).visibility = View.INVISIBLE
                findViewById<EditText>(R.id.number).visibility = View.INVISIBLE

                readLoop(this,this)
            }
        }
    }

    private fun setSmsMessage(uriString: String, selection: String?){
        val sms : SmsData
        val cursor = contentResolver.query(Uri.parse("content://sms/$uriString"),null,selection,null,null)

        if (cursor != null) {
            if(cursor.moveToFirst()){
                val nameID = cursor.getColumnIndex("address")
                val messageID = cursor.getColumnIndex("body")
                val dateID = cursor.getColumnIndex("date")


                val dateString = cursor.getString(dateID)
                sms = SmsData(cursor.getString(nameID), Date(dateString.toLong()).toString(),cursor.getString(messageID))

                if(sms.message.lines()[0] == "Contacts for you:\n" || sms.message.lines()[0] == "Contacts for you:"){
                    runOnUiThread {
                        findViewById<EditText>(R.id.contacts).setText(sms.message)
                    }
                    gotContacts = true
                }

            }
            cursor.close()
        }

    }

    private fun readLoop(con : Context, act : Activity){
        gotContacts = false
        CoroutineScope(IO).launch {
            async {
                while(!gotContacts)
                {
                    if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.READ_SMS) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.READ_SMS), 2)
                    }
                    else
                    {
                        if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                            ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.READ_CONTACTS), 3)
                        }
                        else
                        {
                            setSmsMessage("inbox", null)
                        }
                    }
                }
            }
        }
    }
}