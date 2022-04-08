TaskHandle_t mytaskHandle1 = NULL;
TaskHandle_t mytaskHandle2 = NULL;
static int taskcore1=0;
static int taskcore2=1;
const int LED1 = 5;
const int LED2 = 18;

void mytask1 (void *p1){
  for(;;){
        digitalWrite(LED1, HIGH);
        delay(500);
        digitalWrite(LED1, LOW);
        delay(500);
  }
  
}

void mytask2 (void *p2){
  for(;;){
    digitalWrite(LED2, HIGH);
    delay(300);
    digitalWrite(LED2, LOW);
    delay(300);
  }
}

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  xTaskCreatePinnedToCore( mytask1, "Task1", 10000, (void*)0, 1, &mytaskHandle1,taskcore1);
  xTaskCreatePinnedToCore( mytask2, "Task2", 10000, (void*)0, 1, &mytaskHandle2,taskcore2);
}

void loop(){
  
}
