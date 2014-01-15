/*
  Fade RGB LED Smoothly through 4 colours
  Fades an RGB LED using PWM smoothly through 4 different colours pausing for 1.5 seconds on each colour.
  Connect an common Cathode RGB LED with appropriate resistors on each anode to your Arduino Uno;
  Red to pin 11, Green to pin 10, Blue to pin 9, Cathode to GND.
  Developed for Arduino Uno by Joshua David - TechHelpBlog.com
  Please Feel Free to adapt and use this code in your projects.
 Contact me at techhelpblog.com and let me know how you've used it!
 */ // Assign LED Output PWM Pins 
int Red = 0; 
int Green = 2; 
int Blue = 1; 
//Set Initial Values 
int RedVal = 0; int
GreenVal = 0; 
int BlueVal = 0; 
int fade = 10; // Delay Time 

// Colour Value 1 as each colour intensity (0-255) 
int RedVal1 = 186; 
int GreenVal1 = 0; 
int BlueVal1 = 255; 
// Colour Value 2 
int RedVal2 = 9; 
int GreenVal2 = 239; 
int BlueVal2 = 26; 
//Colour Value 3 
int RedVal3 = 255; 
int GreenVal3 = 120; 
int BlueVal3 = 0; 
//Colour Value 4 
int RedVal4 = 0; 
int GreenVal4 = 255; 
int BlueVal4 = 78; 
//Set initial mode (Colour Value Mode) to Colour Value 1 
int mode = 1; 

void setup() {
 //----------------------- Assign outputs
   pinMode(Red, OUTPUT);
   pinMode(Green, OUTPUT);
   pinMode(Blue, OUTPUT);
 //----------------------- Write Initial Values of 0 to outputs
   analogWrite(Red, RedVal);
   analogWrite(Green, GreenVal);
   analogWrite(Blue, BlueVal);
}
void loop() // Begin Main Program Loop {
  while(mode == 1){
    if(RedVal < RedVal1){ // If RedVal is less than desired RedVal1
      RedVal ++; // increment RedVal
    } else if(RedVal > RedVal1){ // If RedVal is more than desired RedVal1
      RedVal --; // decrement RedVal
    } else if(RedVal == RedVal1){ // If RedVal is equal to desired RedVal1
      //Do Nothing
    }
                                       // Repeated as above for BlueVal
    if(BlueVal < BlueVal1){
      BlueVal ++;
    } else if(BlueVal > BlueVal1){
      BlueVal --;
    } else if(BlueVal == BlueVal1){
      //Do Nothing
    }
                                       // Repeated as above for GreenVal
    if(GreenVal < GreenVal1){
      GreenVal ++;
    } else if (GreenVal > GreenVal1){
      GreenVal --;
    } else if (GreenVal == GreenVal1){
      // Do Nothing
    }
                                       // Now we have a new set of values, we write them to the PWM Pins.
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade); // Implement a bit of delay to slow the change of colour down a bit
    if(RedVal == RedVal1 && GreenVal == GreenVal1 && BlueVal == BlueVal1){ // If RedVal & GreenVal & BlueVal are all 
at the desired values
      delay(1500); // Delay to hold this colour for a little while
      mode = 2; // Change the mode to the next colour. Exiting this while loop and into the next one
    }
  }
  while(mode == 2){
    if(RedVal < RedVal2){
      RedVal ++;
    } else if(RedVal > RedVal2){
      RedVal --;
    } else if(RedVal == RedVal2){
      //Do Nothing
    }
    if(BlueVal < BlueVal2){
      BlueVal ++;
    } else if(BlueVal > BlueVal2){
      BlueVal --;
    } else if(BlueVal == BlueVal2){
      //Do Nothing
    }
    if(GreenVal < GreenVal2){
      GreenVal ++;
    } else if (GreenVal > GreenVal2){
      GreenVal --;
    } else if (GreenVal == GreenVal2){
      // Do Nothing
    }
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);
    if(RedVal == RedVal2 && GreenVal == GreenVal2 && BlueVal == BlueVal2){
      delay(1500);
      mode = 3;
     //break;
    }
  }
  while(mode == 3){
    if(RedVal < RedVal3){
      RedVal ++;
    } else if(RedVal > RedVal3){
      RedVal --;
    } else if(RedVal == RedVal3){
      //Do Nothing
    }
    if(BlueVal < BlueVal3){
      BlueVal ++;
    } else if(BlueVal > BlueVal3){
      BlueVal --;
    } else if(BlueVal == BlueVal3){
      //Do Nothing
    }
    if(GreenVal < GreenVal3){
      GreenVal ++;
    } else if (GreenVal > GreenVal3){
      GreenVal --;
    } else if (GreenVal == GreenVal3){
      // Do Nothing
    }
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);
    if(RedVal == RedVal3 && GreenVal == GreenVal3 && BlueVal == BlueVal3){
      delay(1500);
      mode = 4;
      //break;
    }
  }
  while(mode == 4){
    if(RedVal < RedVal4){
      RedVal ++;
    } else if(RedVal > RedVal4){
      RedVal --;
    } else if(RedVal == RedVal4){
      //Do Nothing
    }
    if(BlueVal < BlueVal4){
      BlueVal ++;
    } else if(BlueVal > BlueVal4){
      BlueVal --;
    } else if(BlueVal == BlueVal4){
      //Do Nothing
    }
    if(GreenVal < GreenVal4){
      GreenVal ++;
    } else if (GreenVal > GreenVal4){
      GreenVal --;
    } else if (GreenVal == GreenVal4){
      // Do Nothing
    }
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);
    if(RedVal == RedVal4 && GreenVal == GreenVal4 && BlueVal == BlueVal4){
      delay(1500);
      mode = 1; // Set mode back to 1 to return to the original colour.
      //break;
    }
  }
}
