TaskHandle_t mytaskHandle1 = NULL;
TaskHandle_t mytaskHandle2 = NULL;
static int taskcore1=0;
static int taskcore2=1;
static int LED1 = 5;
static int LED2 = 18;
static int Input1;
static int Input2;

void mytask1 (void *p1){
  int Delay1=*((int*) p1);
  for(;;){
        digitalWrite(LED1, HIGH);
        vTaskDelay(Delay1);
        digitalWrite(LED1, LOW);
        vTaskDelay(Delay1);
  }
  
}

void mytask2 (void *p2){
  int Delay2=*((int*) p2);
  for(;;){
    digitalWrite(LED2, HIGH);
    vTaskDelay(Delay2);
    digitalWrite(LED2, LOW);
    vTaskDelay(Delay2);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("At what delay do you need the first LED to blink (Give it in mS)");
  while (Serial.available()==0);
  Input1=Serial.parseInt();
  Serial.println("At what delay do you need the second LED to blink (Give it in mS)");
  while (Serial.available()==0);
  Input2=Serial.parseInt();
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  xTaskCreatePinnedToCore( mytask1, "Task1", 1000, (void*) Input1, 0, &mytaskHandle1,taskcore1);
  xTaskCreatePinnedToCore( mytask2, "Task2", 1000, (void*) Input2, 0, &mytaskHandle2,taskcore2);
  vTaskStartScheduler();
}

void loop(){
  
}
