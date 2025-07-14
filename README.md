# Voice-Controlled-Robot

This project is a speech-recognition robot that receives signals from your laptop's microphone through WiFi and is controlled through a specific set of voice commands.
It employs an ESP-WROOM-32 DEVKIT V1 board, your laptop's microphone and an L298N motor driver.

The Python script, (which is located in the server folder) accesses the user's mic and analyzes what is being said through the speech recognition library in Python via the Google Cloud Speech-to-Text API. This script converts audio to text, which is then relayed onto the ESP32 via WiFi as a string for further interpretation.

## Usage

The Python script for this project can be found in the ``server`` folder and the C++ code for ESP32 can be found in the ``src`` folder. 

1. Setting up ``credentials.h``.
   
   For this project to work, the ESP32 needs to be actively connected (as a client) to the same local WiFi access point as your laptop. To set up your credentials, create a file named ``credentials.h`` in the ``include`` folder. Include the following code:

   ```c++
    const char* ssid = "your_wifi_ssid";  
    const char* password = "your_wifi_password";
   ```
   Ensure to replace ``your_wifi_ssid`` and ``your_wifi_password`` with your unique credentials.

 2. Upload the C++ code (named ``VoiceBotReceivingEnd.cpp`` in the ``src`` folder) onto your ESP32.
    
    While still having your board connected to the serial COM port of your laptop, run the code. It should print out the IP address of the ESP32 on the serial monitor.

    When you go wireless, you can use your router's admin page to find the IP address of the board.

3. Set the IP address of your ESP32 in your Python script.
   You need to set the IP address of your ESP32 in your Python script to be able to enable wireless communication between your computer and robot

   Ensure to replace ``WiFi_IP = "192.168.137.225"`` with your IP address.

   You can then run this script.
   ```Python
   python .\VoiceBotClientEnd.py
   ```
 This script will then listen to your voice for the following commands:
 
 <ul><li>"Forward"</li>
 
 <li>"Backward"</li>

 <li>"Right"</li> 
 
 <li>"Left"</li>
 
 <li>"Exit</li></ul>

 The exit command will stop voice recognition if you wish to exit.

 4. One can also create their commands by either replacing a preexisting command or adding a new command to the _defaultCommands_ dictionary in ```server/VoiceBotClientEnd.py```

   
