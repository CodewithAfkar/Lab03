#include <WiFi.h>

static TaskHandle_t task1handler=NULL;
static TaskHandle_t task2handler=NULL;

const char* WIFI_NAME= "Shams Villa";  //my wifi name cannot be renamed to my en numer. My EN number is EN20416812
const char* WIFI_PASSWORD = "6076e7d1";
WiFiServer server(80);

String header;

String LED_ONE_STATE = "off";
String LED_TWO_STATE = "off";


const int GPIO_PIN_NUMBER_1 = 2;
const int GPIO_PIN_NUMBER_2 = 4;

void task_wifi(void * parameters){
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME); 
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect to Wifi Network");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi network");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void task_webserver(void* p2){
  while(1){
    WiFiClient client = server.available(); 
  if (client) { 
    Serial.println("New Client is requesting web page"); 
    String current_data_line = ""; 
    while (client.connected()) { 
      if (client.available()) { 
      char new_byte = client.read(); 
      Serial.write(new_byte); 
      header += new_byte;
      if (new_byte == '\n') { 
         
        if (current_data_line.length() == 0) {
            
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
            
          if (header.indexOf("LED0=ON") != -1) {
            Serial.println("GPIO2 LED is ON");
            LED_ONE_STATE = "on";
            digitalWrite(GPIO_PIN_NUMBER_1, HIGH);
          } 
          if (header.indexOf("LED0=OFF") != -1) {
            Serial.println("GPIO2 LED is OFF");
            LED_ONE_STATE = "off";
            digitalWrite(GPIO_PIN_NUMBER_1, LOW);
          } 
          if (header.indexOf("LED1=ON") != -1){
            Serial.println("GPIO4 LED is ON");
            LED_TWO_STATE = "on";
            digitalWrite(GPIO_PIN_NUMBER_2, HIGH);
          }
          if (header.indexOf("LED1=OFF") != -1) {
            Serial.println("GPIO4 LED is OFF");
            LED_TWO_STATE = "off";
            digitalWrite(GPIO_PIN_NUMBER_2, LOW);
          }
            
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #4CAF50; border: 2px solid #4CAF50;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"); 
 // Web Page Heading
          client.println("</style></head>");
          client.println("<body><center><h1>Controlling LED using Web Server and ESP32 (EN20416812)</h1></center>");
          client.println("<center><h2>Press on button to turn on led and off button to turn off LED</h3></center>");
          client.println("<form><center>");
          client.println("<p> LED one is " + LED_ONE_STATE + "</p>");
          // If the PIN_NUMBER_22State is off, it displays the ON button 
          client.println("<center> <button class=\"button\" name=\"LED0\" value=\"ON\" type=\"submit\">LED0 ON</button>") ;
          client.println("<button class=\"button\" name=\"LED0\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br>");
          client.println("<p>LED two is " + LED_TWO_STATE + "</p>");
          client.println("<button class=\"button\" name=\"LED1\" value=\"ON\" type=\"submit\">LED1 ON</button>");
          client.println("<button class=\"button\" name=\"LED1\" value=\"OFF\" type=\"submit\">LED1 OFF</button> <br><br>");
          client.println("</center></form></body></html>");
          client.println();
          break;
        } 
        else { 
          current_data_line = "";
        }
      } 
      else if (new_byte != '\r') { 
        current_data_line += new_byte; 
      }
    }
  }
// Clear the header variable
  header = "";
// Close the connection
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
  }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(GPIO_PIN_NUMBER_1, OUTPUT);
  pinMode(GPIO_PIN_NUMBER_2, OUTPUT);

  digitalWrite(GPIO_PIN_NUMBER_1, LOW);
  digitalWrite(GPIO_PIN_NUMBER_2, LOW);
  xTaskCreatePinnedToCore(task_wifi,
                          "WiFiConnecting",
                          5000,
                          NULL,
                          1,
                          NULL,
                          1);

  xTaskCreatePinnedToCore(task_webserver,
                          "Connectingwebserver",
                          10000,
                          NULL,
                          1,
                          &task2handler,
                          1);

}

void loop() {
  // put your main code here, to run repeatedly:

}
