#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <math.h>
#if __has_include("device_config.h")
#include "device_config.h"
#else
#include "device_config.example.h"
#endif
#include "logic.h"

WiFiClientSecure tls;
PubSubClient mqtt(tls);
unsigned long nextConnect=0, nextSample=0;
unsigned long backoff=1000;
float distanceCm(int trig,int echo) { digitalWrite(trig,LOW); delayMicroseconds(3); digitalWrite(trig,HIGH); delayMicroseconds(10); digitalWrite(trig,LOW); unsigned long us=pulseIn(echo,HIGH,30000); return us ? us*0.0343f/2.0f : -1.0f; }

Sample readSample() { Sample s{0,0,false}; s.value = distanceCm(25,26); s.aux = constrain((100.0f-s.value)*1.0f,0.0f,100.0f); s.valid = s.value > 0; return s; }

void connectNetwork() {
  if (WiFi.status()!=WL_CONNECTED) { WiFi.begin(WIFI_SSID,WIFI_PASSWORD); return; }
  if (time(nullptr)<1704067200) return; // Wait for SNTP before TLS validation.
  if (mqtt.connected()) return;
  String clientId=String("IoTWaterTankLevelMonitor-")+DEVICE_ID;
  if (mqtt.connect(clientId.c_str(),MQTT_USERNAME,MQTT_PASSWORD)) { backoff=1000; }
}

void setup() {
  Serial.begin(115200);
  pinMode(25,OUTPUT); pinMode(26,INPUT);
  WiFi.mode(WIFI_STA);
  configTime(0,0,"pool.ntp.org");
  tls.setCACert(MQTT_CA_CERT);
  mqtt.setServer(MQTT_HOST,8883);
  mqtt.setBufferSize(512);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
}

void loop() {
  unsigned long now=millis();
  if (WiFi.status()!=WL_CONNECTED || !mqtt.connected()) {

    if ((long)(now-nextConnect)>=0) {
      connectNetwork();
      nextConnect=now+backoff;
      backoff=backoff<30000 ? backoff*2 : 60000;
    }
  } else mqtt.loop();
  if ((long)(now-nextSample)<0) return;
  nextSample=now+5000;
  Sample s=readSample();
  bool alarm=isAlert(s);

  if (!mqtt.connected()) return;
  char topic[128], payload[256];
  snprintf(topic,sizeof(topic),"devices/%s/telemetry",DEVICE_ID);
  snprintf(payload,sizeof(payload),"{\"device_id\":\"%s\",\"measurement\":%.3f,\"secondary\":%.3f,\"valid\":%s,\"alert\":%s,\"uptime_ms\":%lu}",DEVICE_ID,s.value,s.aux,s.valid?"true":"false",alarm?"true":"false",now);
  mqtt.publish(topic,payload,false);
}
