#include <NewPing.h> // для ультразвукового датчика дальности
#include <Servo.h>
#define PIN_TRIG_ULTR 12
#define PIN_ECHO_ULTR 11
#define MAX_DISTANCE 200 // Константа для определения максимального расстояния, которое мы будем считать корректным.

#define PIN_INF_OBST 10 // пин инфракрасного датчика
#define PIN_SERVO 9

byte obstacle_found;
Servo servo;
int tick = 0;

// В качестве параметров передаем номера пинов, к которым подключены выходы ECHO и TRIG датчика
NewPing sonar(PIN_TRIG_ULTR, PIN_ECHO_ULTR, MAX_DISTANCE);
void setup() {
  // Инициализируем взаимодействие по последовательному порту на скорости 9600
  pinMode(PIN_INF_OBST, INPUT);
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
}

void loop() {
  delay(50);

  if(tick % 2 == 0){
    servo.write(180);
  } else {
    servo.write(0);
  }
  Serial.println("-------------------");
  delay(1000);
  
  unsigned int distance_ultr = sonar.ping_cm(); // расстояние ультразвуковым
  Serial.print(distance_ultr);
  Serial.println("см (ультразвуковой)");

  obstacle_found = digitalRead(PIN_INF_OBST);
  if(obstacle_found == HIGH)
    Serial.println("Инфракрасный датчик ничего не видит");
  else
    Serial.println("Инфракрасный датчик видит препятствие");
  delay(5000);
  tick += 1;
}
