// Helper function for calibration of ADE9078 by Avinash Pai with contributions cited.
#include <math.h>                      
#define ARDBUFFER 16
#include <stdarg.h>
#include <Arduino.h>

const byte buffSize = 32;
char inputSeveral[buffSize]; // space for 31 chars and a terminator

byte maxChars = 12; // a shorter limit to make it easier to see what happens
                   //  if too many chars are entered




// https://forum.arduino.cc/index.php?topic=96292.0
// Fit Analysis By Least Squares 
double alog(double x)
{  return (x < 0) ? -log(-x) : ((x > 0) ? log(x) : 0);
}
// FABLS
void fabls(unsigned n,double *px,double *py)
{  byte mask='\x00',sign,sign2;
   unsigned i;
   int least=-1;
   double beta,d2,denom,dy,p,percent_error,r=(n-1),x,y,yc;
   double a1,a2,a3,s,s1,s2,s3,s4,s5,s6,s7,z[5];
   byte *f = "%f %f %f %f %f\n";
   byte *best[] = 
   { " linear"," quadratic","n exponential"," logarithmic"," power" };
// Linear
   s1 = s2 = s3 = s4 = s = 0;
   for (i=0; i<n; i++)
   {  x = px[i];
      y = py[i];
      s1 += x;
      s2 += x * x;
      s3 += y;
      s4 += x * y;
   }
   if (denom = n * s2 - s1 * s1)
   {  a1 = (s3 * s2 - s1 * s4) / denom;
      a2 = (n  * s4 - s3 * s1) / denom;
      for (i=0; i<n; i++)
      {  dy = py[i] - (a2 * px[i] + a1);
         s += dy * dy;
      }
      s = sqrt(s / r);
      sign = (a1 < 0) ? '-' : '+';
      ardprintf("Linear:      y = (%f) x %c %f; s = %f\n",a2,sign,fabs(a1),s);
      mask |= '\x01';
      z[0] = s;
   }
// Quadratic
   s1 = s2 = s3 = s4 = s5 = s6 = s7 = s = 0;
   for (i=0; i<n; i++)
   {  x = px[i];
      y = py[i];
      s1 += x;
      s2 += x * x;
      s3 += x * x * x;
      s4 += x * x * x * x;
      s5 += y;
      s6 += x * y;
      s7 += x * x * y;
   }
   if (denom = n  * (s2 * s4 - s3 * s3) -
               s1 * (s1 * s4 - s2 * s3) +
               s2 * (s1 * s3 - s2 * s2) )
   {  a1 = (s5 * (s2 * s4 - s3 * s3) -
            s6 * (s1 * s4 - s2 * s3) +
            s7 * (s1 * s3 - s2 * s2)) / denom;
      a2 = (n  * (s6 * s4 - s3 * s7) -
            s1 * (s5 * s4 - s7 * s2) +
            s2 * (s5 * s3 - s6 * s2)) / denom;
      a3 = (n  * (s2 * s7 - s6 * s3) -
            s1 * (s1 * s7 - s5 * s3) +
            s2 * (s1 * s6 - s5 * s2)) / denom;
      for (i=0; i<n; i++)
      {  x = px[i];
         dy = py[i] - (a3 * x * x + a2 * x + a1);
         s += dy * dy;
      }
      s = sqrt(s / r);
      sign  = (a1 < 0) ? '-' : '+';
      sign2 = (a2 < 0) ? '-' : '+';
      ardprintf("Quadratic:   y = (%f) x^2 %c (%f) x %c %f; s = %f\n",
             a3,sign2,fabs(a2),sign,fabs(a1),s);
      mask |= '\x02';
      z[1] = s;
   }
// Exponential
   s1 = s2 = s3 = s4 = s = 0;
   for (i=0; i<n; i++)
   {  x = px[i];
      y = alog(py[i]);
      s1 += x;
      s2 += x * x;
      s3 += y;
      s4 += x * y;
   }
   if (denom = n * s2 - s1 * s1)
   {  a1 = (s3 * s2 - s1 * s4) / denom;
      a2 = (n  * s4 - s3 * s1) / denom;
      for (i=0; i<n; i++)
      {  dy = alog(py[i]) - (a2 * px[i] + a1);
         s += dy * dy;
      }
      s = sqrt(s / r);
      sign = (a1 < 0) ? '-' : '+';
      ardprintf("Exponential: y = exp(%f x %c %f); s = %f\n",a2,sign,fabs(a1),s);
      mask |= '\x04';
      z[2] = s;
   }
// Logarithmic
   s1 = s2 = s3 = s4 = s = 0;
   for (i=0; i<n; i++)
   {  x = alog(px[i]);
      y = py[i];
      s1 += x;
      s2 += x * x;
      s3 += y;
      s4 += x * y;
   }
   if (denom = n  * s2 - s1 * s1)
   {  a1 = (s3 * s2 - s1 * s4) / denom;
      a2 = (n  * s4 - s3 * s1) / denom;
      for (i=0; i<n; i++)
      {  x = alog(px[i]);
         dy = py[i] - (x * a2 + a1);
         s += dy * dy;
      }
      s = sqrt(s / r);
      sign = (a1 < 0) ? '-' : '+';
      ardprintf("Logarithmic: y = (%f) ln(x) %c %f; s = %f\n",a2,sign,fabs(a1),s);
      mask |= '\x08';
      z[3] = s;
   }
// Power (points with x=0 are thrown out)
   s1 = s2 = s3 = s4 = s = 0;
   for (i=0; i<n; i++)
   {  if (!px[i]) goto NotPower;
      x = alog(px[i]);
      y = alog(py[i]);
      s1 += x;
      s2 += x * x;
      s3 += y;
      s4 += x * y;
   }
   if (denom = n  * s2 - s1 * s1)
   {  a1 = exp((s3 * s2 - s1 * s4) / denom);
      a2 = (n  * s4 - s3 * s1) / denom;
      for (i=0; i<n; i++)
      {  dy = py[i] - a1 * pow(px[i],a2);
         s += dy * dy;
      }
      s = sqrt(s / r);
      sign = (a1 < 0) ? '-' : '+';
      ardprintf("Power:       y = (%f) x ^ (%f); s = %f\n",a1,a2,s);
      mask |= '\x10';
      z[4] = s;
   }
NotPower:
   // Display function with least squared deviation
   if (mask)
   {  for (i=0; i<5; i++) if (mask && (1 << i)) 
      {  least = i;
         break;
      }
      if (least != -1)
      {  for (i=(1+least); i<5; i++) 
            if (mask && ('\x01' << i))
               if (z[i] < z[least])
                  least = i;
         ardprintf("The best fit is a%s function\n",best[least]);
      }
   }
   else ardprintf("Couldn't fit any of the five functions\n");
}




void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Starting...");
}


void loop() {

  Serial.print("Input Zero Point: ");
  delay(2000);

  readSeveralChars();
  int zeroPoint = atoi(inputSeveral);
  Serial.println(zeroPoint);

  delay(3000);
  Serial.print("Input total points: ");
  delay(2000);

  readSeveralChars();
  unsigned int totalPoints = atoi(inputSeveral);
  Serial.println(totalPoints);

  delay(3000);
  double px[totalPoints];
  double py[totalPoints];
  for (unsigned int i = 0; i < totalPoints; ++i)
  {
    px[i] = i;
    ardprintf("Input point %d", i+1);
    delay(3000);
    readSeveralChars();
    py[i] = atof(inputSeveral);
    Serial.print(px[i]);
    Serial.print(" " );
    Serial.println(py[i]);
    delay(500);
  }
  delay(2000);

  fabls(totalPoints, px, py);

}



void readSeveralChars() {

  // this reads all the characters in the input buffer
  // if there are too many for the inputSeveral array the extra chars will be lost

  inputSeveral[0] = 0; // makes inputSeveral an empty string with just a terminator

  byte ndx = 0;        // the index position for storing the character

  if (Serial.available() > 0) {

    while (Serial.available() > 0) { // keep going until buffer is empty
      if (ndx > maxChars - 1) { // -1 because arrays count from 0
        ndx = maxChars;     // if there are too many chars the extra ones are
      }                     //   dumped into the last array element which will
      //   be overwritten by the string terminator
      inputSeveral[ndx] = Serial.read();
      ndx ++;

    }

    if (ndx > maxChars) {  // to make sure the terminator is not written beyond the array
      ndx = maxChars;
    }
    inputSeveral[ndx] = 0; // add a zero terminator to mark the end of the string
  }



}



// https://gist.github.com/asheeshr/9004783
// A printf function for serial communication from Arduino boards
int ardprintf(char *str, ...)
{
  int i, count=0, j=0, flag=0;
  char temp[ARDBUFFER+1];
  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++;

  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++)
  {
    if(str[i]=='%')
    {
      temp[j] = '\0';
      Serial.print(temp);
      j=0;
      temp[0] = '\0';

      switch(str[++i])
      {
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      };
    }
    else 
    {
      temp[j] = str[i];
      j = (j+1)%ARDBUFFER;
      if(j==0) 
      {
        temp[ARDBUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  };
  Serial.println();
  return count + 1;
}
