#include <WiFiNINA.h>  
#include <MQTT.h>  
#include "param.h" 
 

const char ssid[] = SSID;       
const char pass[] = PASS; 
const char mqtt_server[] = MQTT_SERVER
const int mqtt_port = MQTT_PORT 
const char mqtt_key[] = MQTT_KEY
const char mqtt_secure[] = MQTT_SECURE
const char mqtt_device[] = MQTT_DEVICE

int status = WL_IDLE_STATUS;
WiFiClient client_wifi;  
MQTTClient client_mqtt; 

void serial_setup(int rate=9600)
{
  Serial.begin(rate);
}

void connect_wifi()
{
  Serial.print("Connecting to wifi...");

  while ( status != WL_CONNECTED) 
  {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnection established\n");
}
  
void connect_mqtt()
{
  client_mqtt.begin(mqtt_server, mqtt_port, client_wifi);

  Serial.println("Connecting to broker...");
  while (!client_mqtt.connect(mqtt_device, mqtt_key, mqtt_secure)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Connected to MQTT");

  client_mqtt.onMessage(messageReceived);

  client_mqtt.subscribe("/relay1");
  client_mqtt.subscribe("/relay2");
  client_mqtt.subscribe("/relay3");
  client_mqtt.subscribe("/relay4");
  client_mqtt.subscribe("/relay5");
  client_mqtt.subscribe("/relay6");
  client_mqtt.subscribe("/relay7");
  client_mqtt.subscribe("/relay8");
  client_mqtt.subscribe("/relay9");
}

void messageReceived(String &topic, String &payload) 
{
  Serial.println("topic: " + topic + ": " + payload);

  if (topic=="/relay1")
  {
    if (payload=="ON") digitalWrite(0, LOW);
    else if (payload=="OFF") digitalWrite(0, HIGH);
  }
  else if (topic=="/relay2")
  {
    if (payload=="ON") digitalWrite(1, LOW);
    else if (payload=="OFF") digitalWrite(1, HIGH);
  }
  else if (topic=="/relay3")
  {
    if (payload=="ON") digitalWrite(2, LOW);
    else if (payload=="OFF") digitalWrite(2, HIGH);
  }
  else if (topic=="/relay4")
  {
    if (payload=="ON") digitalWrite(3, LOW);
    else if (payload=="OFF") digitalWrite(3, HIGH);
  }
  else if (topic=="/relay5")
  {
    if (payload=="ON") digitalWrite(4, LOW);
    else if (payload=="OFF") digitalWrite(4, HIGH);
  }
  else if (topic=="/relay6")
  {
    if (payload=="ON") digitalWrite(5, LOW);
    else if (payload=="OFF") digitalWrite(5, HIGH);
  }
  else if (topic=="/relay7")
  {
    if (payload=="ON") digitalWrite(6, LOW);
    else if (payload=="OFF") digitalWrite(6, HIGH);
  }
  else if (topic=="/relay8")
  {
    if (payload=="ON") digitalWrite(7, LOW);
    else if (payload=="OFF") digitalWrite(7, HIGH);
  }
  else if (topic=="/relay9")
  {
    if (payload=="ON") digitalWrite(8, LOW);
    else if (payload=="OFF") digitalWrite(8, HIGH);
  }
}

void setup_gpio()
{
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);

  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  for (int i=1 ; i<=9 ; i++)
  {
    String msg = "/relay";
    msg+=String(i);
    msg+="/state";
    Serial.println(msg);
    client_mqtt.publish(msg, "OFF");
  }

}

void setup() 
{
  serial_setup(9600);
  connect_wifi();
  connect_mqtt();
  setup_gpio();
}


void loop() 
{
  client_mqtt.loop();
  delay(1000);

  if (!client_wifi.connected()) {
    connect_wifi();
    connect_mqtt();
    delay(1000);
  }

}
