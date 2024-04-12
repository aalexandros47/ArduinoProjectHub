volatile bool buttonPressed = false; // flag to indicate button press
volatile bool isScrollingToRight = true; // flag to indicate button press
volatile unsigned long buttonPressStartTime = 0;
volatile unsigned long buttonPressDuration = 0;

//PIN ASSIGNEMTS 
#define R1 A0
#define R2 A1
#define R3 A2
#define R4 A3
#define R5 A4
#define R6 A5
#define R7 A6
#define R8 A7

#define C1 A8
#define C2 A9
#define C3 A10
#define C4 A11
#define C5 A12
#define C6 A13
#define C7 A14
#define C8 A15

#define  DS0 2
#define  DS1 3
#define  DS2 4
#define  DS3 5


#define PB1  18
//PIN ASSIGNMETS ENDS HERE 

//8x8 MATRIX ROW COLUM CONFIGURATION 

const byte rows[] = {
    R1, R2, R3, R4, R5, R6, R7, R8
};
const byte col[] = {
  C1,C2, C3, C4, C5, C6, C7, C8
};
//SELECTOR SWITH , 
const byte DS[] = {
    DS0,DS1, DS2, DS3
};

// 8x8 CHARACTERS 
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte N0[]={B01111000,B11001100,B11011100,B11111100,B11101100,B11001100,B01111100,B00000000}; // 0
byte N1[]={B00110000,B01110000,B00110000,B00110000,B00110000,B00110000,B11111100,B00000000}; // 1
byte N2[]={B01111000,B11001100,B00001100,B00111000,B01100000,B11001100,B11111100,B00000000}; // 2
byte N3[]={B01111000,B11001100,B00001100,B00111000,B00001100,B11001100,B01111000,B00000000}; // 3
byte N4[]={B00011100,B00111100,B01101100,B11001100,B11111110,B00001100,B00011110,B00000000}; // 4
byte N5[]={B11111100,B11000000,B11111000,B00001100,B00001100,B11001100,B01111000,B00000000}; // 5
byte N6[]={B00111000,B01100000,B11000000,B11111000,B11001100,B11001100,B01111000,B00000000}; // 6
byte N7[]={B11111100,B11001100,B00001100,B00011000,B00110000,B00110000,B00110000,B00000000}; // 7
byte N8[]={B01111000,B11001100,B11001100,B01111000,B11001100,B11001100,B01111000,B00000000}; // 8
byte N9[]={B01111000,B11001100,B11001100,B01111100,B00001100,B00011000,B01110000,B00000000}; // 9

byte A[]={B00110000,B01111000,B11001100,B11001100,B11111100,B11001100,B11001100,B00000000}; // A
byte B[]={B11111100,B01100110,B01100110,B01111100,B01100110,B01100110,B11111100,B00000000}; // B
byte C[]={B00111100,B01100110,B11000000,B11000000,B11000000,B01100110,B00111100,B00000000}; // C
byte D[]={B11111000,B01101100,B01100110,B01100110,B01100110,B01101100,B11111000,B00000000}; // D
byte E[]={B11111110,B01100010,B01101000,B01111000,B01101000,B01100010,B11111110,B00000000}; // E
byte F[]={B11111110,B01100010,B01101000,B01111000,B01101000,B01100000,B11110000,B00000000}; // F
byte font[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

/*
byte font[16][8]= {
{B01111000,B11001100,B11011100,B11111100,B11101100,B11001100,B01111100,B00000000}, // 0
{B00110000,B01110000,B00110000,B00110000,B00110000,B00110000,B11111100,B00000000}, // 1
{B01111000,B11001100,B00001100,B00111000,B01100000,B11001100,B11111100,B00000000}, // 2
{B01111000,B11001100,B00001100,B00111000,B00001100,B11001100,B01111000,B00000000}, // 3
{B00011100,B00111100,B01101100,B11001100,B11111110,B00001100,B00011110,B00000000}, // 4
{B11111100,B11000000,B11111000,B00001100,B00001100,B11001100,B01111000,B00000000}, // 5
{B00111000,B01100000,B11000000,B11111000,B11001100,B11001100,B01111000,B00000000}, // 6
{B11111100,B11001100,B00001100,B00011000,B00110000,B00110000,B00110000,B00000000}, // 7
{B01111000,B11001100,B11001100,B01111000,B11001100,B11001100,B01111000,B00000000}, // 8
{B01111000,B11001100,B11001100,B01111100,B00001100,B00011000,B01110000,B00000000}, // 9

{B00110000,B01111000,B11001100,B11001100,B11111100,B11001100,B11001100,B00000000}, // A
{B11111100,B01100110,B01100110,B01111100,B01100110,B01100110,B11111100,B00000000}, // B
{B00111100,B01100110,B11000000,B11000000,B11000000,B01100110,B00111100,B00000000}, // C
{B11111000,B01101100,B01100110,B01100110,B01100110,B01101100,B11111000,B00000000}, // D
{B11111110,B01100010,B01101000,B01111000,B01101000,B01100010,B11111110,B00000000}, // E
{B11111110,B01100010,B01101000,B01111000,B01101000,B01100000,B11110000,B00000000}, // F
};
*/

//https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
//FOR TEST SCROLL 
byte ANIM[] ={B00000000,
B00000000,
B11000000,
B11000000,
B11000000,
B11000000,
B00000000,
B00000000};

int start=0;
int _end=8;

byte selector= 0b00000000;
unsigned long last_step=0;
int anim_speed[]={0, 500, 200, 100}; // speed of animation  , lower thw value higher the speed
int speed_select=0; //speed selector 

void setup() 
{
  // Open serial port
  Serial.begin(9600);
 
pinMode(R1, OUTPUT);
pinMode(R2, OUTPUT);
pinMode(R3, OUTPUT);
pinMode(R4, OUTPUT);
pinMode(R5, OUTPUT);
pinMode(R6, OUTPUT);
pinMode(R7, OUTPUT);
pinMode(R8, OUTPUT);

pinMode(C1, OUTPUT);
pinMode(C2, OUTPUT);
pinMode(C3, OUTPUT);
pinMode(C4, OUTPUT);
pinMode(C5, OUTPUT);
pinMode(C6, OUTPUT);
pinMode(C7, OUTPUT);
pinMode(C8, OUTPUT);

pinMode(DS0, INPUT_PULLUP);
pinMode(DS1, INPUT_PULLUP);
pinMode(DS2, INPUT_PULLUP);
pinMode(DS3, INPUT_PULLUP);

pinMode(PB1, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(PB1), buttonInterrupt, FALLING); // attach interrupt to button pin

}

void   loop() {

  if (buttonPressed) 
  { // if button is pressed
    buttonPressStartTime = millis(); // record the start time of button press
    while (digitalRead(PB1) == LOW) 
    { // wait until button is released
      delay(10);
    }
    buttonPressDuration = millis() - buttonPressStartTime; // calculate the duration of button press
    if (buttonPressDuration >= 500 && buttonPressDuration <= 2000) 
    { // if button is pressed for 0.5 to 2 seconds
      Serial.println("Short press detected"); // print 1 on the serial monitor
      isScrollingToRight = !isScrollingToRight;
    } 
    else if (buttonPressDuration >= 2500 && buttonPressDuration <= 4000) 
    { // if button is pressed for 2.5 to 4 seconds
      Serial.println("Long press detected"); // print 2 on the serial monitor
      speed_select++;
      speed_select=speed_select>3?0:speed_select;
      delay(200);
    }
    buttonPressed = false; // clear the flag
  }

  //Reads the selector switch 
  for ( byte count = 0; count < 4;count++ )
{
  bitWrite(selector, count, !digitalRead(DS[count] ));
//Serial.println(int(selector));
} 

  //Select Character based on the selector Switch 
switch(selector){
case 0:
drawfont(N0);
break;
case 1:
drawfont(N1);
break;
case 2:
drawfont(N2);
break;
case 3:
drawfont(N3);
break;
case 4:
drawfont(N4);
break;
case 5:
drawfont(N5);
break;
case 6:
drawfont(N6);
break;
case 7:
drawfont(N7);
break;
case 8:
drawfont(N8);
break;
case 9:
drawfont(N9);
break;
case 10:
drawfont(A);
break;
case 11:
drawfont(B);
break;
case 12:
drawfont(C);
break;
case 13:
drawfont(D);
break;
case 14:
drawfont(E);
break;
case 15:
drawfont(F);
break;
default:
drawfont(ALL);
break;
} 

//Scroll functon , sets where the colum stars to print 
  if(isScrollingToRight)
  {
  if(millis()-last_step>anim_speed[speed_select])
  {
    if(speed_select !=0)
    {
      start++;
      start=start==8?-6:start;
    }
    else
    {
      start=0;
    }

  last_step=millis();

  }
  }
  if(!isScrollingToRight)
  {
  if(millis()-last_step>anim_speed[speed_select])
  {
    if(speed_select !=0)
    {
      start--;
      start=start==-6?8:start;
    }
    else
    {
      start=0;
    }

  last_step=millis();

  }
  }

}

//function to draw the font 
 void  drawfont(byte font[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        //  next row
     {
         digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte   a = 0; a < 8-start; a++)    // count next row
        {
          //  use (font[i] >> a) for low 
          digitalWrite(col[a],(~font[i] >> a+start) & 0x01); // initiate whole column
           delayMicroseconds(100);        // speed of display
        for (byte   a = 0; a < 8; a++) 
           digitalWrite(col[a],1);      // reset columns
        }
        digitalWrite(rows[i], LOW);      // rese rows
        
    }
}
void buttonInterrupt() {
  buttonPressed = true; // set the flag to indicate button press
}