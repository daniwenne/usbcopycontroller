


const uint8_t nums[]={0b11100111,0b10000100,0b11010011,0b11010110,0b10110100,0b01110110,0b01110111,0b11000100,0b11110111,0b11110110};

void set_display(uint8_t val)
{
  uint8_t state;
  uint8_t ind;
  for (ind = 0; ind < 8; ind++)
  {
    state =((1<<ind)&val)==0?HIGH:LOW;
    digitalWrite(ind+2,state);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  uint8_t i;
  for (uint8_t i = 2; i < 10; i++) 
  {
    pinMode (i , OUTPUT);
    digitalWrite(i,HIGH);
  }
  set_display(nums[1]);
  Serial.begin(9600);
}


bool alteracao=false;
uint8_t num=0;

const uint16_t delaytime=200;

void loop() 
{
  if((digitalRead(11)==LOW)&&!alteracao)
  {
    num = (num+1)%9;
    set_display(nums[num+1]);
    alteracao=true;
    delay(delaytime);
  }
  if((digitalRead(10)==LOW)&&!alteracao)
  {
    num = (num+8)%9;
    set_display(nums[num+1]); 
    alteracao=true;
    delay(delaytime);
  }
  if((digitalRead(12)==LOW)&&!alteracao)
  {
    Serial.print(num+1);
    num=0;
    set_display(0b01100011);
    uint8_t recievedbyte;
    for (uint8_t tries=0; tries<10;tries++)
    {
      recievedbyte=Serial.read();
      if (recievedbyte==83)
      {
        set_display(0b11110001);
        while(Serial.read()!=69)
        {
        }
        break;
      }
      delay(1000);
    }
    set_display(nums[1]);
    
  }
  if((digitalRead(10)==HIGH)&&(digitalRead(11)==HIGH))
  {
    alteracao=false;
  }
}
