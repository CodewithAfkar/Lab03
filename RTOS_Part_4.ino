
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
// Some string to print
static const BaseType_t Task1priority = 1;
static const BaseType_t Task2priority = 1;
const char msg[] = "ABCD";
// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
//*****************************************************************************
// Tasks
// Task: print to Serial Terminal with lower priority
void startTask1(void *parameter) {
// Count number of characters in string
int msg_len = strlen(msg);
// Print string to Terminal
while (1) {
 Serial.println();
 for (int i = 0; i < msg_len; i++) {
 Serial.print(msg[i]);
 }
 Serial.println();
 vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}
// Task: print to Serial Terminal with higher priority
void startTask2(void *parameter) {
while (1) {
 Serial.print('*');
 vTaskDelay(100 / portTICK_PERIOD_MS);
}
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xTaskCreatePinnedToCore( startTask1, "Task1", 100000, (void*) 0, Task1priority, &task_1,app_cpu);
  xTaskCreatePinnedToCore( startTask2, "Task2", 100000, (void*) 0, Task2priority, &task_2,app_cpu);
  vTaskStartScheduler();

}

void loop() {
  // put your main code here, to run repeatedly:

}
