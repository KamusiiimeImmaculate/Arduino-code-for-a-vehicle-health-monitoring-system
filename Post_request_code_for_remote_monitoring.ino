#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

char ssid[] = "Kiira-Motors-Main";
char pass[] = "wifi@kmc20";


const char serverName[] = "kayoolaapi.pythonanywhere.com";  // server name
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient( wifi, serverName, port );
int status = WL_IDLE_STATUS;

void setup()
{
  Serial.begin( 9600 );
  while ( !Serial );

  while ( status != WL_CONNECTED )
  {
    Serial.print( "Attempting to connect to Network named: " );
    Serial.println( ssid );
    status = WiFi.begin( ssid, pass );
  }

  Serial.print( "SSID: " );
  Serial.println( WiFi.SSID() );

  IPAddress ip = WiFi.localIP();
  Serial.print( "IP Address: " );
  Serial.println( ip );
}

void loop()
{
  String title = "Vehicle Health Status";
  String description = "Along the Entebbe highway";
  String Battery_status = "State of Charge";
  String RPM = "Motor speed";
  float lat = 0;
  float lng = 0;
  String Battery_Pack = "Battery Pack Temperature";
  String VCU = "Temperature";
  String BatteryPack = "Health";
  String license_number = "UBG 985X";
  float Vehicle_speed = 0;
  String payload = String("{\"title\":\"" + title + "\",\"description\":\"" + description + "\",\"Battery_status\":\"" 
                      + Battery_status + "\",\"RPM\":\"" + RPM + "\",\"lat\":" + (String)lat + ",\"long\":" + (String)lng 
                      + ",\"Battery_Pack\":\"" + Battery_Pack + ",\"VCU\":\"" + VCU+ ",\"license_number\":\"" 
                      + license_number + ",\"BatteryPack\":\"" + BatteryPack + ",\"Vehicle_speed\":" + (String)Vehicle_speed + "}");
  VehicleHealthStatus(payload);
  Serial.println( "Wait 30 seconds" );
  delay( 30000 );
}

void VehicleHealthStatus(String payload) {
  String contentType = "application/json";

  client.post( "/health/raw-can-data/", contentType, payload );

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  Serial.print( "Status code: " );
  Serial.println( statusCode );
  String response = client.responseBody();
  Serial.print( "Response: " );
  Serial.println( response );
  }
