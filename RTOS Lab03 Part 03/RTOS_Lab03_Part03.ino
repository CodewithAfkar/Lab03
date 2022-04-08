//#include <Arduino_FreeRTOS.h>

TaskHandle_t mytask1Handle = NULL;
static int taskcore=0;

void mytask1 (void *p){
  for(;;){
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(500);
        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(500);
  }
  
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  xTaskCreatePinnedToCore( mytask1, "Task1", 1000, (void*) 0, 0, &mytask1Handle,taskcore);
  vTaskStartScheduler();
}

void loop(){
  
}
