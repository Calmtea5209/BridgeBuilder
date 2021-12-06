TaskHandle_t Task1;   //宣告任務變數Task1
TaskHandle_t Task2;   //宣告任務變數Task2
 
void setup() {
  Serial.begin(115200); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
 
//建立Task1任務並指定在核心0中執行
  xTaskCreatePinnedToCore(
                    Task1code,   /* 任務函數 */
                    "Task1",     /* 任務名稱 */
                    10000,       /* 任務推疊大小 */
                    NULL,        /* 任務參數 */
                    1,           /* 任務優先權(0是最低優先權 */
                    NULL,      /* 欲追蹤處理的任務名稱 (可使用 &Task1 或 NULL) */
                    0);          /* 指定此任務的執行核心(0或1) */                  
 
//建立Task2任務並指定在核心1中執行
  xTaskCreatePinnedToCore(
                    Task2code,   /* 任務函數 */
                    "Task2",     /* 任務名稱 */
                    10000,       /* 任務推疊大小 */
                    NULL,        /* 任務參數 */
                    1,           /* 任務優先權(0是最低優先權 */
                    NULL,      /* 欲追蹤處理的任務名稱 (可使用 &Task2 或 NULL) */
                    1);          /* 指定此任務的執行核心(0或1) */ 
}
 
void Task1code( void * pvParameters ){
  for(;;){               //任務函數必須無限循環執行，如果離開函式會自動RESET
    //blablabla
  } 
}
 
//第2個任務LED2每隔 700 ms閃爍
void Task2code( void * pvParameters ){
  for(;;){               //任務函數必須無限循環執行，如果離開函式會自動RESET
    Serial.print("Task2 running on core ");
    //blablabla
  }
}
 
//預設核心0負責執行Loop函式中的程式
void loop() {}
