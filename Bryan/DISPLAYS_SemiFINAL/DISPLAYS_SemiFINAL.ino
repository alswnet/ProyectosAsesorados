int a1 = 25;
int b1 = 22;
int c1 = 23;
int d1 = 24;

int a2 = 13;
int b2 = 10;
int c2 = 11;
int d2 = 12;

int a3 = 6;
int b3 = 5;
int c3 = 4;
int d3 = 3;

int pin1 = 26;


int counter1 = 4;
int counter2 = 0;
int counter3 = 0;

int minusNum = 1;

boolean buttonState1 = LOW;

void setup()
{
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(c3, OUTPUT);
  pinMode(d3, OUTPUT);
    pinMode(7, OUTPUT);
  led2(counter2);
  led1(counter1);
  led3(counter3);
}

void loop()
{

  if (debounceButton1(buttonState1) == HIGH && buttonState1 == LOW)
  {
    buttonState1 = HIGH;
    counter1 -= minusNum;
    led1(counter1);
    led2(counter2);
    led3(counter3);



  }
  else if (debounceButton1(buttonState1) == LOW && buttonState1 == HIGH)
  {
    buttonState1 = LOW;
  }






{
  if (counter1 == 0 && counter2 == 0 && counter3 == 0)
    digitalWrite(7, LOW);
  else if (counter1 > 0 || counter2 > 0 || counter3 > 0)
  {
   digitalWrite(7, HIGH);
  }
}







  
}

void led1 (int i)
{
  if (counter1 == 0 && counter2 == 0 && counter3 == 0)
    counter3 = 0;
  else if (counter2 > 0 && counter1 < 0)
  {
    counter1 += 10;
    counter2 -= 1;
  }
  else if (counter3 > 0 && counter1 < 0 && counter2 == 0)
  {
    counter1 += 10;
    counter2 += 9;
    counter3 -= 1;
  }
  i = counter1;


  switch (i)
  {
    case 0:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 0);
        digitalWrite(c1, 0);
        digitalWrite(d1, 0);
        break;
      }
    case 1:
      {
        digitalWrite(a1, 1);
        digitalWrite(b1, 0);
        digitalWrite(c1, 0);
        digitalWrite(d1, 0);
        break;
      }
    case 2:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 1);
        digitalWrite(c1, 0);
        digitalWrite(d1, 0);
        break;
      }
    case 3:
      {
        digitalWrite(a1, 1);
        digitalWrite(b1, 1);
        digitalWrite(c1, 0);
        digitalWrite(d1, 0);
        break;
      }
    case 4:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 0);
        digitalWrite(c1, 1);
        digitalWrite(d1, 0);
        break;
      }
    case 5:
      {
        digitalWrite(a1, 1);
        digitalWrite(b1, 0);
        digitalWrite(c1, 1);
        digitalWrite(d1, 0);
        break;
      }
    case 6:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 1);
        digitalWrite(c1, 1);
        digitalWrite(d1, 0);
        break;
      }
    case 7:
      {
        digitalWrite(a1, 1);
        digitalWrite(b1, 1);
        digitalWrite(c1, 1);
        digitalWrite(d1, 0);
        break;
      }
    case 8:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 0);
        digitalWrite(c1, 0);
        digitalWrite(d1, 1);
        break;
      }
    case 9:
      {
        digitalWrite(a1, 1);
        digitalWrite(b1, 0);
        digitalWrite(c1, 0);
        digitalWrite(d1, 1);
        break;
      }
    default:
      {
        digitalWrite(a1, 0);
        digitalWrite(b1, 0);
        digitalWrite(c1, 0);
        digitalWrite(d1, 0);
        break;
      }

  }
}


void led2 (int j)
{

  j = counter2;


  switch (j)
  {
    case 0:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 0);
        digitalWrite(c2, 0);
        digitalWrite(d2, 0);
        break;
      }
    case 1:
      {
        digitalWrite(a2, 1);
        digitalWrite(b2, 0);
        digitalWrite(c2, 0);
        digitalWrite(d2, 0);
        break;
      }
    case 2:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 1);
        digitalWrite(c2, 0);
        digitalWrite(d2, 0);
        break;
      }
    case 3:
      {
        digitalWrite(a2, 1);
        digitalWrite(b2, 1);
        digitalWrite(c2, 0);
        digitalWrite(d2, 0);
        break;
      }
    case 4:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 0);
        digitalWrite(c2, 1);
        digitalWrite(d2, 0);
        break;
      }
    case 5:
      {
        digitalWrite(a2, 1);
        digitalWrite(b2, 0);
        digitalWrite(c2, 1);
        digitalWrite(d2, 0);
        break;
      }
    case 6:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 1);
        digitalWrite(c2, 1);
        digitalWrite(d2, 0);
        break;
      }
    case 7:
      {
        digitalWrite(a2, 1);
        digitalWrite(b2, 1);
        digitalWrite(c2, 1);
        digitalWrite(d2, 0);
        break;
      }
    case 8:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 0);
        digitalWrite(c2, 0);
        digitalWrite(d2, 1);
        break;
      }
    case 9:
      {
        digitalWrite(a2, 1);
        digitalWrite(b2, 0);
        digitalWrite(c2, 0);
        digitalWrite(d2, 1);
        break;
      }
    default:
      {
        digitalWrite(a2, 0);
        digitalWrite(b2, 0);
        digitalWrite(c2, 0);
        digitalWrite(d2, 0);
        break;
      }

  }
}

void led3 (int k)
{
  k = counter3;
  switch (k)
  {
    case 0:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 0);
        digitalWrite(c3, 0);
        digitalWrite(d3, 0);
        break;
      }
    case 1:
      {
        digitalWrite(a3, 1);
        digitalWrite(b3, 0);
        digitalWrite(c3, 0);
        digitalWrite(d3, 0);
        break;
      }
    case 2:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 1);
        digitalWrite(c3, 0);
        digitalWrite(d3, 0);
        break;
      }
    case 3:
      {
        digitalWrite(a3, 1);
        digitalWrite(b3, 1);
        digitalWrite(c3, 0);
        digitalWrite(d3, 0);
        break;
      }
    case 4:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 0);
        digitalWrite(c3, 1);
        digitalWrite(d3, 0);
        break;
      }
    case 5:
      {
        digitalWrite(a3, 1);
        digitalWrite(b3, 0);
        digitalWrite(c3, 1);
        digitalWrite(d3, 0);
        break;
      }
    case 6:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 1);
        digitalWrite(c3, 1);
        digitalWrite(d3, 0);
        break;
      }
    case 7:
      {
        digitalWrite(a3, 1);
        digitalWrite(b3, 1);
        digitalWrite(c3, 1);
        digitalWrite(d3, 0);
        break;
      }
    case 8:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 0);
        digitalWrite(c3, 0);
        digitalWrite(d3, 1);
        break;
      }
    case 9:
      {
        digitalWrite(a3, 1);
        digitalWrite(b3, 0);
        digitalWrite(c3, 0);
        digitalWrite(d3, 1);
        break;
      }
    default:
      {
        digitalWrite(a3, 0);
        digitalWrite(b3, 0);
        digitalWrite(c3, 0);
        digitalWrite(d3, 0);
        break;
      }

  }
}

boolean debounceButton1(boolean state1)
{
  boolean stateNow1 = digitalRead(pin1);
  if (state1 != stateNow1)
  {
    delay(30);
    stateNow1 = digitalRead(pin1);
  }
  return stateNow1;
}





