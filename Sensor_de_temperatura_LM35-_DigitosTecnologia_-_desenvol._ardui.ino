#include <SPI.h>
#include <Ethernet.h>

const int LM35 = A1;
float temp;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,7);   
byte gateway  = (192,168,1,1);
byte subnet = (255,255,255,0);
EthernetServer server(80);
String readString;


void setup() {
 Serial.begin(9600);
 Ethernet.begin(mac, ip);
 server.begin();
 EthernetClient client;
 }
 
void loop() {    
temp = ((float(analogRead(LM35))*5)/(1023))/0.01;

  EthernetClient client = server.available();
 if (client) {
   while (client.connected()){
    if (client.available()){
      char c = client.read();
   if (readString.length() < 100) {
    readString += c;
   }
   
   if (c == 'n') {

 client.println("<HTTP/1.1 200 OK>");
 client.println("<Content-Type: text/html>");
 client.println();
 client.println("<HTML>");
client.println("<BODY>");
client.println("<H1><center>LOCAL MONITORADO</center><H1>");
client.println("<ht/>");
client.println("<br/>");
client.println("<h2><center> Temperatura :");
client.println(temp);
client.println("ºC </center><h2>");
client.println("</BODY>");
client.println("</HTML>");
 
  delay (10000);
  
      }
     }
    }
   }
  }
