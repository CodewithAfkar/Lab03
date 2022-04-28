TaskHandle_t TaskA_Handler=NULL;
TaskHandle_t TaskB_Handler=NULL;

static int taskAcore=0;
static int taskBcore=1;

SemaphoreHandle_t xMutex;

void TaskA (void *p1){
    while(1){
      if (xSemaphoreTake(xMutex, 0) == pdTRUE) {
          Serial.print("I am Task A and I am running in core:");
          Serial.println(xPortGetCoreID());
          xSemaphoreGive(xMutex);
      }else{
        //do something
      }
  }
  vTaskDelay(100 / portTICK_PERIOD_MS);
  
}

void TaskB (void *p2){
  while(1){
    if (xSemaphoreTake(xMutex, 0) == pdTRUE) {
        Serial.print("I am Task B and I am running in core:");
        Serial.println(xPortGetCoreID());
        xSemaphoreGive(xMutex);
    }else {
      //do something
    }
  }
  vTaskDelay(100 / portTICK_PERIOD_MS);
  
}

void setup() {
  Serial.begin(9600);
  xMutex=xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore( TaskA, "TaskA", 1000, NULL, 1, &TaskA_Handler,taskAcore);
  xTaskCreatePinnedToCore( TaskB, "TaskB", 1000, NULL, 1, &TaskB_Handler,taskBcore);
  vTaskStartScheduler();

}

void loop() {
  // put your main code here, to run repeatedly:

}
