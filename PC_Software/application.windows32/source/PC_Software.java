import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class PC_Software extends PApplet {


final int padding = 3;
final int screenWidth = 600;
final int screenHeight = 500;

final int edgesImageWidth = 160;
final int edgesImageHeight = 100;

final int baudRate = 921600;




ControlP5  cp5;
Textarea   textFeed;
Textfield  inputFeed;

Serial myPort;

boolean[][] edgesImage = new boolean[edgesImageWidth][edgesImageHeight];

int x = 0;
int y = 0;

boolean collecting = false;

public void setup()
{
  size(screenWidth,screenHeight);
  noStroke();
  
  cp5 = new ControlP5(this);
  
  textFeed = cp5.addTextarea("feed")
                  .setPosition(0+padding, screenHeight - 100 + padding)
                  .setSize(screenWidth - padding*2, 80 - padding*2)
                  .setFont(createFont("arial",12))
                  .setLineHeight(14)
                  .setColor(color(128))
                  .setColorBackground(color(0,100))
                  .setColorForeground(color(0,100))
                  .setScrollBackground(color(0,100))
                  .setScrollForeground(color(0,100))
                  .scroll(1)
                  ;
                  
  inputFeed = cp5.addTextfield("input")
                  .setPosition(0+padding, screenHeight - 20)
                  .setSize(screenWidth - padding*2 - 5, 20 - padding) 
                  .setFont(createFont("arial",12))
                  .setFocus(true)
                  .setColor(color(128))
                  .setColorBackground(color(0,45))
                  .setColorForeground(color(0,45))
                  .setColorActive(color(0,45))
                  ;
                  
}



public void draw() 
{
  //textFeed.setText(textFeed.getText() + "\n" + millis());
  background(color(255,100));
  
  if(true)
  {
    PImage edges = createImage(edgesImageWidth, edgesImageHeight, RGB);
    edges.loadPixels();
  
    for (int i = 0; i < edges.pixels.length; i++) 
    {
      if(edgesImage[i%edgesImageWidth][i/edgesImageWidth])
      {
          edges.pixels[i] = color(245, 245, 245); 
      }
      else
      {
          edges.pixels[i] = color(0, 0, 0); 
      }
    }
  
    edges.updatePixels();
    //image(edges, 17, 17);
    edges.resize(screenWidth - (17*2),0);
    image(edges, 17, 17);
    
  }
}

public void input(String text)
{
  String lowerText = text.toLowerCase();
  //this is where the input string needs to be decoded and spit out to the PIC
  //all commands are converted to lower case!!!!! 
  if(lowerText.equals("?") || lowerText.equals("help"))
  {
    textFeed.setText(textFeed.getText() + "\nHELP\n\nCommands-\nlist : Returns a list of the serial ports available\nconnect# : connects to comport #\ndisconnect: disconnects from com port");
  }
  else if(lowerText.equals("list"))
  { 
    for(int i = Serial.list().length; i > 0; i--)
    { 
      int j = Serial.list().length - i;
      textFeed.setText(textFeed.getText() + "#" + (j) + ": " + Serial.list()[j] + "\n"); 
    }
  }
  else if((lowerText.length() > 7) && (lowerText.substring(0,7).equals("connect")))
  {
    
    String portString = lowerText.substring(7);
    int portNum = Integer.parseInt(lowerText.substring(7));
    myPort = new Serial(this, Serial.list()[portNum], baudRate);
    myPort.clear();
    
    myPort.bufferUntil(0x41);
    //myPort.buffer(edgesImageWidth*edgesImageHeight/8);
    textFeed.setText(textFeed.getText() + "Connected to " + Serial.list()[portNum] + "\n");
  }
  else if(lowerText.equals("disconnect"))
  {
    if(myPort == null)
    {
      textFeed.setText(textFeed.getText() + "Not connected to comport, exiting command.\n");
    }
    else
    {
      myPort.stop();
      textFeed.setText(textFeed.getText() + "Disconnected from comport\n");
    }
  }
  else if(lowerText.equals("g"))
  {
    myPort.write(71);
  }
  else
  {
    textFeed.setText(textFeed.getText() + "\nDid not recognize command: " + text);
  }
}


public void serialEvent(Serial input)
{   
  if(collecting == false)
  {
    myPort.clear();
    //textFeed.setText(textFeed.getText() + "Found Beginning of Frame \n");
    myPort.buffer(edgesImageWidth*edgesImageHeight/8);
    collecting = true;
    return;
  }
  
  myPort.bufferUntil(0x41);
  
  byte[] inBuffer = new byte[edgesImageWidth*edgesImageHeight/8];
  inBuffer = input.readBytes();
  input.readBytes(inBuffer);
  
  myPort.clear();
    
    for(int y = 0; y < edgesImageHeight; y++)
    {
      for(int x = 1; x < (edgesImageWidth/8); x++)
      {
        //y*20+x gives index
        
        edgesImage[x*8+0][y] = (inBuffer[y*20+x-1] & 128) == 128;
        edgesImage[x*8+1][y] = (inBuffer[y*20+x-1] & 64) == 64;
        edgesImage[x*8+2][y] = (inBuffer[y*20+x-1] & 32) == 32;
        edgesImage[x*8+3][y] = (inBuffer[y*20+x-1] & 16) == 16;
        edgesImage[x*8+4][y] = (inBuffer[y*20+x-1] & 8) == 8;
        edgesImage[x*8+5][y] = (inBuffer[y*20+x-1] & 4) == 4;
        edgesImage[x*8+6][y] = (inBuffer[y*20+x-1] & 2) == 2;
        edgesImage[x*8+7][y] = (inBuffer[y*20+x-1] & 1) == 1;  
      }
    }
    
    //textFeed.setText(textFeed.getText() + "Recieved Frame\n" + inBuffer.length + " Bytes read\n" + input.available() + " bytes left in buffer\n");
    collecting = false;
  }



  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "PC_Software" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
