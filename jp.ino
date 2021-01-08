#include <Servo.h>
const int trigpin = 10;
const int echopin= 11;
int Calculate_Distance();
int i,p,j,a,l,f,cross;
long d,d1,d2;
double aux1,mat[50][4],mat1[15][3],x,y,Prom,Prom1,xan,yan;

Servo myServo; 

void setup() {
  pinMode(trigpin, OUTPUT); 
  pinMode(echopin, INPUT); 
  Serial.begin(9600);
  myServo.attach(8); 
}

  
void loop() {
for(p=180;p>15;p--)
{
      myServo.write(p);
      delay(15);
}
  for(p=15;p<=180;p++){ 
  myServo.write(p);
  delay(50);
  d = Calculate_Distance();
  if(d>0&&(p!=0))
  {  
    cross=0;
    f=p+1;
    d1=1;
    aux1=0;
    while(d1>0)
    {
      myServo.write(f);
      delay(200);
      d1 = Calculate_Distance();
      if(d1>(d+15)||d1<(d-15))
      {
        cross=-1;
        break;
      }
      else
      { 
        if (f>=180)
        {
          break;
        }
        else
        {
           f++;
        }
       
      }
    }
   a=0;
for(i=0;i<j;i++)
{
  if((p<(mat[i][0]+5))&&(p>(mat[i][0]-5)))
  {
    if((d<(mat[i][1]+5))&&(d>(mat[i][2]-5)))
    {
      if(((f<mat[i][2]+5))&&(f>(mat[i][2]-5)))
      {
        mat[i][3]=mat[i][3]+1;
        a=-1;
      }
    }
  }
 }

 if(a==0)
 {
  mat[j][0]=i;
  mat[j][1]=d;
  mat[j][2]=f;
  mat[j][3]=0;
  j++;
 }
for(i=0;i<j;i++)
{
  if(mat[i][3]==3)
  {
    mat1[l][0]=mat[i][0];
    mat1[l][1]=mat[i][1];
    mat1[l][2]=mat[i][2];
    l++;
  }
}  
 a=0;
for(i=0;i<l;i++)
{
 if(((mat1[i][0]<(p+5)))&&(mat1[i][0]>(p-5)))
 {
  if((d<(mat1[i][1]+5)&&(d>(mat1[i][1]-5))))
  {
    if((f<(mat1[i][2]+5))&&(f>(mat1[i][2]-5)))
    {
      a=-1;
    }
  }  
 }  
}

if(a==0)
{
  Prom=((f-15)+(p-15))/2;
  Prom1=Prom*3.1415/180;
  xan=cos(Prom1);
  yan=sin(Prom1);
  x=xan*d;
  y=yan*d;

  Serial.print("Coordinates: ");
   Serial.print("( ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(") ");
  Serial.print("\n");
}
    p=f;
    if(cross==0)
    {
       for(i=0;i<3;i++)
       {
         p++;
         myServo.write(p);
         delay(50);
       }
      
    }
  }
 }
}
int Calculate_Distance()
{ 
  long dist,tiempo;
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH); 
  delayMicroseconds(15);
  digitalWrite(trigpin, LOW);
  tiempo = pulseIn(echopin, HIGH); 
  dist= tiempo*0.01715;
  if(dist<1||dist>85)
  {
    dist=-1;
  }
  return dist;
}
