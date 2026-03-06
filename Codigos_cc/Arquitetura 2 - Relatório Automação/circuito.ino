/*
Projeto da disciplina Arquitetura de Computadores II, 2025/2. Professora Rafaela
Alimentador de ração automático para pets. Arduino
Alunos: Alexandre M. do Carmo, Lucas Tozo Monção
*/

#include <Stepper.h>

const int motor_passos = 300;
const byte motor_pin1 = 8;
const byte motor_pin2 = 9;
const byte motor_pin3 = 10;
const byte motor_pin4 = 11;

Stepper motor = Stepper(2000, motor_pin1, motor_pin3, motor_pin2, motor_pin4);
// Stepper motor = Stepper(2000, motor_pin1, motor_pin2);

// -- DEFINIÇÃO DE PINOS DIGITAIS RESERVADOS PARA COMPONENTES --
const byte pin_botao_liga_desliga = 3;
const byte pin_botao_reset = 2;

// -- DEFINIÇÃO DE PINOS ANALÓGICOS RESERVADOS PARA COMPONENTES --
const byte pin_potenciometro = A0;

// -- DEFINIÇÃO DE CONSTANTES DO SISTEMA --
const float segundos_aberto = 0.5;
byte segundos_por_ciclo = 2;

unsigned long intervalo = (unsigned long)segundos_por_ciclo * 60UL * 60UL * 1000UL;

unsigned long ultimo_ciclo = 0;

bool botao_liga_desliga_anterior = LOW;
byte botao_liga_desliga_estado = 0;
bool botao_reset_estado_anterior = LOW;
byte botao_reset_estado = 0;
bool sistema_ligado = false;

/*
Rotina para pausar a máquina até que o botão seja apertado novamente.
*/
void desligar() {
  digitalWrite(LED_BUILTIN, LOW);
  reset();
}

/*
Rotina para resetar a máquina imediatamente e 
recomeçar a partir do momento que o botão foi apertado.
*/
void reset() {
  int potenciometro_valor_raw = analogRead(pin_potenciometro);
  int potenciometro_valor_normalizado = map(potenciometro_valor_raw, 0, 1023, 2, 12);
  Serial.println(potenciometro_valor_normalizado);
  intervalo = potenciometro_valor_normalizado * 1000;

  ultimo_ciclo = millis() - intervalo;

  delay(100);
}

/*
Rotina para liberar ração por X segundos e depois fechar.
*/
void alimentar() {
  motor.step(motor_passos);
  delay(segundos_aberto * 1000);
  motor.step(-motor_passos);
}

void setup() {
  motor.setSpeed(10);
  Serial.begin(9600);

  pinMode(pin_botao_liga_desliga, INPUT_PULLUP);
  pinMode(pin_botao_reset, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);

  reset();
}

void loop() {
  botao_liga_desliga_estado = digitalRead(pin_botao_liga_desliga);

  if (botao_liga_desliga_estado == LOW && botao_liga_desliga_anterior == HIGH) 
  {
    sistema_ligado = !sistema_ligado;

    if (!sistema_ligado) 
    {
      desligar();
    } 
    else 
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  botao_liga_desliga_anterior = botao_liga_desliga_estado;

  if (!sistema_ligado) 
  {
    return;
  }

  botao_reset_estado = digitalRead(pin_botao_reset);
  if (botao_reset_estado == LOW && botao_reset_estado_anterior == HIGH) 
  {
    reset();
  }
  botao_reset_estado_anterior = botao_reset_estado;
  
  unsigned long agora = millis();
  if (agora - ultimo_ciclo >= intervalo) {
    alimentar();
    ultimo_ciclo = millis();
  }
}