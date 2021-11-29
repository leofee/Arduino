#include <ESP8266WiFi.h>
#define led 2 //发光二极管连接在8266的GPIO2上
const char *ssid     = "Xiaomi_6DF0";//这里写入网络的ssid
const char *password = "kalawaqiao";//wifi密码
const char *host = "192.168.0.199";//修改为Server服务端的IP，即你电脑的IP，确保在同一网络之下。
WiFiClient client;//声明一个客户端对象，用于与服务器进行连接
const int tcpPort = 777;//修改为你建立的Server服务端的端口号，此端口号是创建服务器时指定的。
static String comdata = "";
static String val = "";
void setup()
{
    
    Serial.begin(115200);    
    pinMode(led,OUTPUT);
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");//会通过usb转tll模块发送到电脑，通过ide集成的串口监视器可以获取数据。
    Serial.println(ssid);
    WiFi.begin(ssid, password);//启动
     //在这里检测是否成功连接到目标网络，未连接则阻塞。
    while (WiFi.status() != WL_CONNECTED)
    {
    
        delay(500);
    }
 //几句提示
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void loop()
{
    
/******************串口接受数据************************/
  while (Serial.available() > 0) // 串口收到字符数大于零。
  {
       
  comdata += char(Serial.read());
  }
 /******************串口打印数据************************/ 
  if(comdata!="")//如果接受到数据
  {
    
    client.print(comdata);//向服务器发送数据 
   }
   comdata="";//清空数据
  if (client.connected()) //尝试访问目标地址，如果没连接上LED灯灭
    digitalWrite(led, LOW);
  else
    digitalWrite(led, HIGH);

  while (!client.connected())//若未连接到服务端，则客户端进行连接。
  {
    
    if (!client.connect(host, tcpPort))//实际上这一步就在连接服务端，如果连接上，该函数返回true
    {
    
       Serial.println("连接中....");
       delay(500);
    }    
  }
  while (client.available())//available()表示是否可以获取到数据
  {
     
    //char val = client.read();//read()表示从网络中读取数据。
     while (client.available() > 0) // 串口收到字符数大于零。
    {
       
    val += char(client.read());
    }
    client.print(val);    
 //   Serial.write(val);
    val="";//清空数据
   }
  delay(1);
}
