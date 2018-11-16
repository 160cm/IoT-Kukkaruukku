#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>

const char* ssid     = "TTLab";
const char* password = "a4fg72jk99l1mn";

const char* host = "172.20.240.56";

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void PostData() {
  String data = "30";
  String url = "http://172.20.240.56/test.php";
  HTTPClient http;
  http.setReuse(true);
  http.begin(url);
  http.addHeader("Host", "http://172.20.240.56/test.php");
  http.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0");
  http.addHeader("Accept-Language", " en-US,en;q=0.5");
  http.addHeader("Accept-Encoding", " gzip, deflate, br");
  http.addHeader("Content-Type", " application/x-www-form-urlencoded; charset=UTF-8");
  http.addHeader("X-Requested-With", " XMLHttpRequest");
  http.addHeader("Referer", " https://www.shippingmanager.dk/sh/?fb_source=shippingmanager.dk");
  http.addHeader("Connection", "keep-alive");
  http.addHeader("Pragma", " no-cache");
  http.addHeader("Cache-Control", " no-cache");

  int result = http.POST(data);
  http.writeToStream(&Serial);
  http.end();

}

void loop() {

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


 PostData();
 delay(1000);
}
//=======================================================================
