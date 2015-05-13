
final int padding = 3;
final int screenWidth = 600;
final int screenHeight = 500;

final int edgesImageWidth = 160;
final int edgesImageHeight = 100;

final int baudRate = 115200;

import controlP5.*;
import processing.serial.*;

ControlP5  cp5;
Textarea   textFeed;
Textfield  inputFeed;

Serial myPort;
RadioButton r;
int mode = -1;

boolean[][] edgesImage = new boolean[edgesImageWidth][edgesImageHeight];
byte[] SerialBuffer = new byte[1024];

byte[] wiiData = new byte[16];

int serialCount = 0;

int x = 0;
int y = 0;

boolean collecting = false;

void setup()
{
  for(int i = 0; i < 16; i++)
  {
   wiiData[i] = (byte)0xFF; 
  }
  size(screenWidth,screenHeight);
  noStroke();
  
  cp5 = new ControlP5(this);
  
  r = cp5.addRadioButton("radioButton")
         .setPosition(120,375)
         .setSize(20,20)
         .setColorForeground(color(120))
         .setColorActive(color(100))
         .setColorLabel(color(128))
         .setItemsPerRow(5)
         .setSpacingColumn(50)
         .addItem("Pixy",1)
         .addItem("Wii",2)
         .addItem("FFT",3)
         .addItem("Sensors",4)
         .addItem("Raw Data",5)
         ;
     
     for(Toggle t:r.getItems()) 
     {
       t.captionLabel().setColorBackground(color(255,80));
       t.captionLabel().style().moveMargin(-7,0,0,-3);
       t.captionLabel().style().movePadding(7,0,0,3);
       t.captionLabel().style().backgroundWidth = 45;
       t.captionLabel().style().backgroundHeight = 13;
     }
  
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



void draw() 
{
  //textFeed.setText(textFeed.getText() + "\n" + millis());
  background(color(255,100));
  
  switch(mode)
  {
    case (1):    //Pixy Mode
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
      break;
      
    case (2):    //Wii Mode
 
    fill(color(244, 163,174));
      for(int i = 0; i < 4; i++)
      {
        if(wiiData[2*i] != 0xff || wiiData[2*i+1] != 0xff)
        {
          ellipse(27+wiiData[2*i], 27+wiiData[2*i+1], 20, 20);
        }
      }
      
      fill(color(201, 197, 232));
      for(int i = 0; i < 4; i++)
      {
        if(wiiData[2*i] != 0xff || wiiData[2*i+1] != 0xff)
        {
          ellipse(27+wiiData[2*i+8], 27+wiiData[2*i+9], 20, 20);
        }
      }
      break;
      
    case (3):    //FFT Mode
      break;
      
    case (4):    //Sensors Mode
      break;
      
    case (5):    //Raw Data Mode
      break;
      
    case (-1):   //No Mode selected
      break;
  }
}

void radioButton(int a) 
{
  myPort.clear();
  
  mode = a;
  
  switch(mode)
  {
    case (1):    //Pixy Mode
      myPort.bufferUntil(0x41);
      break;
      
    case (2):    // Wii Mode
      myPort.buffer(36);
      break;
      
    case (3):    //FFT Mode
      serialCount = 0;
      break;
      
    case (4):    //Sensors Mode
      serialCount = 0;
      break;
      
    case (5):    //Raw Data Mode
      serialCount = 0;
      break;
      
    case (-1):   //No Mode selected
      serialCount = 0;
      break;
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
    mode = 2;
    
    String portString = lowerText.substring(7);
    int portNum = Integer.parseInt(lowerText.substring(7));
    myPort = new Serial(this, Serial.list()[portNum], baudRate);
    myPort.clear();
    
    //myPort.bufferUntil(0x41);
    myPort.buffer(36);
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


void serialEvent(Serial input)
{   
  
  switch(mode)
  {
    case (1):/*
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
        break;
        */
      case (2):  //wii mode
        byte[] inBuffer = new byte[36];
        inBuffer = input.readBytes();
      input.readBytes(inBuffer);
        textFeed.setText(textFeed.getText() + "\nGot Data co");
        for(int x = 0; x < 36; x++)
        {
          textFeed.setText(textFeed.getText() + inBuffer[x] + " ");
        }
        textFeed.setText(textFeed.getText() + "\n\n\n");
        for(int i = 0; i < 20; i++)
        {
          if(inBuffer[i] == 42 && inBuffer[i+1] == 42) 
          {
            i += 2;
            textFeed.setText(textFeed.getText() + "\nFound Data");
        
            for(int j = 0; j < 16; j++)
            {
               wiiData[j] = inBuffer[i];
               i++;
            }
            i = 20;
          }
        }
        break;
        
      case (3):  //FFT mode
        break;
        
      case (4):  //Sensors
        break;
        
      case (5):  //Raw Data
        break;
        
      case (-1): //No Mode
        serialCount = 0;
        myPort.clear();
        break;
    }
  }



