import requests
import speech_recognition as sr


#Voice to speech conversion via "speech_recognition" library
Recognizer = sr.Recognizer()
time_out_seconds = 3

defaultCommands = {"forward":"F","backward": "B", "right":"R", "left":"L"}
defaultCommands_Values = defaultCommands.values()

Bool = True
while Bool:
    with sr.Microphone() as source:
        
        print("Please speak into the microphone:")
        try:
            audio_text = Recognizer.listen(source, timeout = time_out_seconds)
            Audio_to_text = Recognizer.recognize_google(audio_text)
            command = defaultCommands.get(Audio_to_text, "Unknown Command!")

            if Audio_to_text == "exit":
                print("You have successfully exited the program.")

                Bool = False

            elif command in defaultCommands_Values:
                print("You said: " + Audio_to_text)   

                Bool = False
            
            elif command == "Unknown Command!":
                print("You said " + Audio_to_text + "," + " which is not a default command, please try again!")

        except sr.UnknownValueError:
            print("Sorry, I did not understand that, please try again")     
            
        except sr.RequestError:
            print("Ran into an error, please ensure you have a stable internet connection and try again")

            Bool = False

        except sr.WaitTimeoutError:
            print("Timeout reached. Please run the code again.")

            Bool = False




#Transmitting converted string to ESP32 via "requests" library
WiFi_IP = "192.168.137.225"  
WiFi_PORT = 80

def send_string_to_esp32(data):
    url = f"http://{WiFi_IP}:{WiFi_PORT}/"
    payload = data

    try:
        response = requests.post(url, data=payload)
        print(" ")
        print("Response from ESP32:", response.text)

    except requests.exceptions.RequestException as e:
        print("Error communicating with ESP32:", e)


#Relaying the string received after Speech to Text conversion onto ESP32
if __name__ == "__main__":
    send_string_to_esp32(command)   
