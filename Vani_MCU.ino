/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "48e01a3730574131a2ce25b728900989";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Vaibhav iPhone";
char pass[] = "abcdefgh";

#define trigger D1

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  pinMode(trigger, INPUT);
}

void loop()
{
  Blynk.run();
  
  if (digitalRead(trigger) == HIGH) // You can write any condition to trigger e-mail sending
  {
    Serial.println("Email triggered"); // This can be seen in the Serial Monitor
    Blynk.email("vaibhav.grover18@gmail.com", "Subject: Help Me!!", "Help Me!! Urgently!! My location is: https://www.google.com/maps/place/26%C2%B049'26.4%22N+75%C2%B051'54.3%22E/@26.823997,75.8629023,17z/data=!3m1!4b1!4m9!1m2!7m1!2e1!3m5!1s0x0:0x0!7e2!8m2!3d26.8239971!4d75.8650907?hl=en");

    Blynk.notify("Help Me!! Urgently!! My location is: https://www.google.com/maps/place/26%C2%B049'26.4%22N+75%C2%B051'54.3%22E/@26.823997,75.8629023,17z/data=!3m1!4b1!4m9!1m2!7m1!2e1!3m5!1s0x0:0x0!7e2!8m2!3d26.8239971!4d75.8650907?hl=en");

    // Or, if you want to use the email specified in the App (like for App Export):
    //Blynk.email("Subject: Button Logger", "You just pushed the button...");
  }
}

