#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo2;
Servo myservo3;
Servo myservo4;
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define tolerance1 10
#define tolerance2 8
#define tolerance3 10
#define tolerance4 20

SoftwareSerial mySerial(10, 11); // RX, TX


#define INPUT_SIZE 30
char input[INPUT_SIZE + 1];

String incomingByte;
int iteration=1;
unsigned int newPosition1=1000;
int motor_number[4];
int anglee[4];
int ang;
int i;

void move_this_motor (int toPosition, int motorNumber, int iteration_number)
{ 
  char stop_here=0; 
  char notThePosition=1;
  
  if(motorNumber == 1)
  {
          if(iteration_number==1)
          {
              while(notThePosition)
                  {
                          if( (analogRead(A0) > toPosition) && (stop_here==0) )
                          {
                            myservo1.write(80);  //move in the CCW direction slowly  /*  270*/
                            delay(5);
                            //delayMicroseconds(500);
                            myservo1.write(90);  //stop at this position
                          }
                          else if( (analogRead(A0) < toPosition) && (stop_here==0) )
                          {
                              myservo1.write(100);  //move in the CW direction slowly   /*  295 */
                              
                              delay(5);//delayMicroseconds(500);
                              myservo1.write(90);  //stop at this position
                          }
                          else if(  (analogRead(A0) < (toPosition+tolerance1)) || (analogRead(A0) > (toPosition-tolerance1)) )
                          {
                            myservo1.write(90);  //stop at this position
                            stop_here=1;            //the motor is at the right position
                            notThePosition=0;       //is not it the right position? no it is the right position.
                          }

              
                  } 
                  // end of while loop
      
          }
          //end of if condition
    }

  
    else if (motorNumber == 2)
    {
            if(iteration_number==1)
                {
                    while(notThePosition)
                        {
                            if( (analogRead(A1) < toPosition) && (stop_here==0) )
                            {
                              myservo2.write(100); //move in the CW direction slowly
                              delay(5);//delayMicroseconds(800);
                              myservo2.write(90); //stop at this position 
                            }
                            else if( (analogRead(A1) > toPosition) && (stop_here==0) )
                            {
                                myservo2.write(85); //move in the CCW direction slowly
                                delay(5);//delayMicroseconds(800);
                                myservo2.write(90); //stop at this position 
                            }
                            else if(  (analogRead(A1 < (toPosition+tolerance2)) || (analogRead(A1) > (toPosition-tolerance2)) ))
                            {
                              myservo2.write(90);  //Stop now in this position:
                              stop_here=1;  //the motor is at the right position
                              notThePosition=0;  //it is not the right position? no it is the right position.
                            }
                    
                        } 
                        // end of while loop
            
                }
                //end of if condition
    }
    
    else if (motorNumber == 3)
    {
          if(iteration_number==1)
                {
                    while(notThePosition)
                        {
                            if( (analogRead(A2) < toPosition) && (stop_here==0) )
                            {
                              myservo3.write(105); //move in the CW direction slowly
                              delay(5);//delayMicroseconds(100);
                              myservo3.write(90); //stop at this position 
                            }
                            else if( (analogRead(A2) > toPosition) && (stop_here==0) )
                            {
                                myservo3.write(75);  //move in the CCW direction slowly
                                delay(5);//delayMicroseconds(100);
                                myservo3.write(90);  //stop at this position
                            }
                            else if(  (analogRead(A2) < (toPosition+tolerance3)) || (analogRead(A2) > (toPosition-tolerance3)) )
                            {
                              myservo3.write(90);  //Stop now in this position:
                              stop_here=1;  //the motor is at the right position
                              notThePosition=0;  //it is not the right position? no it is the right position.
                            }
                    
                        } 
                        // end of while loop
    
                   }
                   //end of if condition
          
    }
    else if(motorNumber == 4)
    {
      if(iteration_number==1)
                {
                    while(notThePosition)
                        {
                            if( (analogRead(A3) > toPosition) && (stop_here==0) )
                            {
                              myservo4.write(10); //move in the CCW direction slowly
                            
                              delay(5);//delayMicroseconds(500);
                              myservo4.write(6); //stop at this position 
                            }
                            else if( (analogRead(A3) < toPosition) && (stop_here==0) )
                            {
                                myservo4.write(0);  //move in the CW direction slowly
                                //delayMicroseconds(500);
                                delay(5);
                                myservo4.write(6);  //stop at this position
                            }
                            else if(  (analogRead(A3) < (toPosition+tolerance4)) || (analogRead(A3) > (toPosition-tolerance4)) )
                            {
                              myservo4.write(6);  //Stop now in this position:
                              stop_here=1;  //the motor is at the right position
                              notThePosition=0;  //it is not the right position? no it is the right position.
                            }
                    
                        } 
                        // end of while loop
    
                   }
                   //end of if condition
      
    }
} 
// *********************** end of (move_this_motor) function **********************************


//this function holds the motor at the given position:


void check_the_position (int thisPosition,int MotorNum)
{   
    if(MotorNum == 1)
    {
          myservo1.write(90);
          myservo2.write(90);
          myservo3.write(90);  //Stop now in your position
          if ( (analogRead(A0) > (thisPosition + tolerance1)) || (analogRead(A0) < (thisPosition-tolerance1)) )
              {
                myservo1.write(90);  //Stop now in your position
                delay(5);//delayMicroseconds(40);
                if ( (analogRead(A0) > (thisPosition+tolerance1)) || (analogRead(A0) < (thisPosition-tolerance1)) )
                {
                  move_this_motor (thisPosition, 1,1);
                }
              }
    }

    
    else if (MotorNum==2){
          myservo1.write(90);
          myservo2.write(90);
          myservo3.write(90);  //Stop now in your position
          if ( (analogRead(A1) > (thisPosition+tolerance2)) || (analogRead(A1) < (thisPosition-tolerance2)) )
              {
                myservo2.write(90);  //Stop now in your position
                delay(5);//delayMicroseconds(40);
                if ( (analogRead(A1) > (thisPosition+tolerance2)) || (analogRead(A1) < (thisPosition-tolerance2)) )
                {
                  move_this_motor (thisPosition, 2,1);
                }
              }
    }
      else if (MotorNum==3){
          myservo1.write(90);
          myservo2.write(90);
          myservo3.write(90);  //Stop now in your position
          Serial.println(analogRead(A2));
          if ( (analogRead(A2) > (thisPosition+tolerance3)) || (analogRead(A2) < (thisPosition-tolerance3)) )
              {
                myservo3.write(90);  //Stop now in your position
                delay(5);//delayMicroseconds(40);
                if ( (analogRead(A2) > (thisPosition+tolerance3)) || (analogRead(A2) < (thisPosition-tolerance3)) )
                {
                  move_this_motor (thisPosition, 3,1);
                }
              }
    }
    else if (MotorNum==4){
          myservo4.write(6);
          if ( (analogRead(A3) > (thisPosition+tolerance4)) || (analogRead(A3) < (thisPosition-tolerance4)) )
              {
                myservo4.write(6);  //Stop now in your position
                delay(5);
                //delayMicroseconds(40);
                if ( (analogRead(A3) > (thisPosition+tolerance4)) || (analogRead(A3) < (thisPosition-tolerance4)) )
                {
                  move_this_motor (thisPosition, 4,1);
                }
              }
    }
}

// *********************** end of (check_the_position) function **********************************
int angle_1(int angle_)
{
  if(angle_<30)
  {
    angle_=30;
  }
  else if(angle_>300)
  {
    angle_=300;
  }
  return ((angle_+0.6343)/0.5186);
}

int angle_2(int angle_)
{
  /*
  if(angle_<30)
  {
    angle_=60;
  }
  else if(angle_>330)
  {
    angle_=330;
  }
  */
return (int)((float)((float)(-1*angle_)-235.21)/-0.518);
}

int angle_3(signed int angle_)
{
  if(angle_<0)
  {
    angle_=0;
  }
  else if(angle_>270)
  {
    angle_=270;
  }
  return (signed int)(((float)angle_-353.06)/(-0.5186));
}

int angle_4(int angle_)
{
  if(angle_<0)
  {
    angle_=0;
  }
  else if(angle_>110)
  {
    angle_=110;
  }
  return ((float)((float)angle_-4.5375)/0.2783);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);  
  myservo1.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);
  myservo3.attach(3);
  myservo4.attach(10);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.println("Starting Loop");
  
 
  

}// end of setup function

/* void move_this_motor (int toPosition, int motorNumber, int iteration_number) */
/* void check_the_position (int thisPosition,int MotorNum) */

void loop() 
{
  
    while(Serial.available())
    {
    char sizeOf = Serial.readBytes(input, INPUT_SIZE);
    input[sizeOf] = 0;
    mySerial.println(input);
    
    char* command = strtok(input, "&");
    i=0;
    while (command != 0)
    {
        // Split the command in two values
        char* separator = strchr(command, ':');
        if (separator != 0)
        {
            // Actually split the string in 2: replace ':' with 0
            *separator = 0;
            int servoId = atoi(command);
            motor_number[i]=servoId;
            ++separator;
            int angle_ = atoi(separator);
            anglee[i]=angle_;
            // Do something with servoId and position
            mySerial.print(servoId);
            mySerial.print(" : ");
            mySerial.println(angle_);
            iteration=1;
            
        }
        i++;
        // Find the next command in input string
        command = strtok(0, "&");
    }
    for(i=0;i<4;i++)
    {
      Serial.println(motor_number[i]);
      Serial.println(anglee[i]);
    }
    //while(1)
      {
    for(i=0;i<4;i++)
    {
      
      if(motor_number[i]==1)
      {
        ang=angle_1(anglee[i]);
        move_this_motor (ang, motor_number[i], iteration);
        check_the_position (ang,motor_number[i]);
      }
      if(motor_number[i]==2)
      {
        ang=angle_2(anglee[i]);
        move_this_motor (ang, motor_number[i], iteration);
        check_the_position (ang,motor_number[i]);
      }
      if(motor_number[i]==3)
      {
        ang=angle_3(anglee[i]);
        move_this_motor (ang, motor_number[i], iteration);
        check_the_position (ang,motor_number[i]);
      }
      if(motor_number[i]==4)
      {
        ang=angle_4(anglee[i]);
       // move_this_motor (ang, motor_number[i], iteration);
        check_the_position (ang,motor_number[i]);
      }
      iteration=0;
       
    }
      }
    iteration=0;
    
  }


 
  
  /*
  
  newPosition1=angle_3(90);
  move_this_motor (newPosition1, 3, iteration);
  check_the_position (newPosition1, 3);
  delay(1000);
*/

  //myservo4.write(10);

}
