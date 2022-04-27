#define LED LED_BUILTIN

TaskHandle_t mytaskHandle1 = NULL;
TaskHandle_t mytaskHandle2 = NULL;
static int taskcore1=0;
static int taskcore2=1;
static int Input;

void mytask1 (void *p1){
  int Delay1=*((int*) p1);
  for(;;){
        digitalWrite(LED, HIGH);
        vTaskDelay(Delay1);
        digitalWrite(LED, LOW);
        vTaskDelay(Delay1);
  }
  
}

void mytask2 (void *p2){
  while (Serial.available() > 0){
      Input = Serial.parseInt();
      Serial.print(Input);
  }
  
}

void setup() {
  Serial.begin(9600);
  Serial.print("What is the delay you want to blink the LED?");
  pinMode(LED,OUTPUT);
  xTaskCreatePinnedToCore( mytask1, "Task1", 1000, (void*) 0, 0, &mytaskHandle1,taskcore1);
  xTaskCreatePinnedToCore( mytask2, "Task2", 1000, (void*) Input, 0, &mytaskHandle2,taskcore2);
  vTaskStartScheduler();
}

void loop(){
  
}
