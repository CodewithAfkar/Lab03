//#include <Arduino_FreeRTOS.h>

TaskHandle_t mytaskHandle1 = NULL;
TaskHandle_t mytaskHandle2 = NULL;
static int taskcore1=0;
static int taskcore2=1;

void mytask1 (void *p1){
  for(;;){
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(500);
        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(500);
  }
  
}

void mytask2 (void *p2){
  for(;;){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(300);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(300);
  }
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  xTaskCreatePinnedToCore( mytask1, "Task1", 1000, (void*) 0, 0, &mytaskHandle1,taskcore1);
  xTaskCreatePinnedToCore( mytask2, "Task2", 1000, (void*) 0, 0, &mytaskHandle2,taskcore2);
  vTaskStartScheduler();
}

void loop(){
  
}
