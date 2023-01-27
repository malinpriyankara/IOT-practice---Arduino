#include <SPI.h>
#include <Ethernet.h>

byte mac[]={0xAA,0xBB,0xCC,0x0DE,0x02}; // mac address of the shield
IPAddress ip=(192,168,1,104); //IP address of the shield
EthernetServer server(80); // ethernet server is at the port 80
String readString; //will store the user respons
int LED1=2;
char c;

void setup() {
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  Ethernet.begin(mac,ip); //starting ethernet shield
  server.begin();
 /*if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }*/
}


void loop() {
  EthernetClient client=server.available(); //Assign a client
  if(client){
    while(client.connected()){
      if(client.available()){
         c=client.read();
        if(readString.length()<100){
          readString +=c;
          }
        }
        if(c=='\n'){
          Serial.println(readString);
          client.println("HTTP/1.1 200 OK");
          client.println("content-type:text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("ARDUINO PAGE");
          client.println("</head>");
          client.println("<title>");
          client.println("Arduio + Ethernet");
          client.println("</title>");
          client.println("<meta http-equiv=\"refresh\"content=\"4\">"); // this is for page refresh. (not important)
          client.println("<form>");
          client.println("<input type=button value=LED ON onclick=window.location='/?ledon1\'>"); // on button for led
          client.println("<input type=button value=LED OFF onclick=window.location='/?ledoff1\'>");// off button for led
          client.println("</form>");
          if (readString.indexOf("?ledon1")>0){ // check the user respons
            digitalWrite(LED1,1);
            }
          if(readString.indexOf("?ledoff1")>0){
            digitalWrite(LED1,0);
            }
          }
          readString="";
          client.stop(); // end of the session
      }
    }

}
