/************************************************************************************
 * PROJETO: PASSA OU REPASSA ELETRÔNICO - INTERFACE I2C
 * DESENVOLVEDOR: Prof. Marcelo Lima
 * INSTITUIÇÃO: SENAC Registro - Curso Técnico em IoT
 * DATA: 08 de Abril de 2026
 * VERSÃO: 4.0 (Suporte a Display LCD 16x2 via I2C)
 * * DESCRIÇÃO:
 * Sistema de arbitragem para jogos de perguntas e respostas. 
 * Identifica o primeiro jogador a pressionar o botão, bloqueia entradas simultâneas,
 * gerencia pontuação e exibe os resultados em tempo real via LCD.
 * * HARDWARE:
 * - Microcontrolador: Arduino Uno/Nano
 * - Display: LCD 16x2 com Módulo I2C (Endereço 0x27)
 * - Lógica: INPUT_PULLUP (Botões conectados diretamente ao GND)
 * - Sinalização: LEDs indicadores com resistores de 150 Ohms
 ************************************************************************************/

// ===== BIBLIOTECAS =====
#include <Wire.h>                // Biblioteca nativa para comunicação I2C (SDA/SCL)
#include <LiquidCrystal_I2C.h>   // Biblioteca para controlar o display LCD via módulo I2C

// ===== CONFIGURAÇÃO DO LCD =====
// Cria o objeto 'lcd' definindo: endereço (0x27), colunas (16) e linhas (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== DEFINIÇÃO DOS PINOS =====
const int player1Button = 4;      // Botão de resposta do Jogador 1
const int player2Button = 8;      // Botão de resposta do Jogador 2
const int restartButton = 3;      // Botão para iniciar uma nova rodada após o ponto

const int pointPlayer1Button = 2; // Botão (juiz) que valida ponto para o Jogador 1
const int pointPlayer2Button = 5; // Botão (juiz) que valida ponto para o Jogador 2

const int player1LED = 6;         // LED indicador do Jogador 1
const int player2LED = 9;         // LED indicador do Jogador 2

const int generalResetButton = 7; // Botão para zerar o placar e reiniciar o jogo

// ===== VARIÁVEIS DE CONTROLE =====
bool roundInProgress = true;      // Controla se a rodada está ativa ou pausada
bool player1HasPressed = false;   // Registra se o J1 já pressionou o botão
bool player2HasPressed = false;   // Registra se o J2 já pressionou o botão
bool pointGiven = false;          // Garante que apenas um ponto seja dado por rodada

int player1Score = 0;             // Armazena a pontuação total do J1
int player2Score = 0;             // Armazena a pontuação total do J2

unsigned long lastPressTime = 0;  // Registra o tempo do último clique (para Debounce)
const int debounceDelay = 50;     // Tempo de espera (ms) para evitar ruído do botão

unsigned long roundStartTime = 0; // Armazena o tempo inicial da rodada
const int roundDuration = 3000;   // Duração prevista para intervalos

// ===== SETUP (Configurações Iniciais) =====
void setup() {
  // Configura os pinos como entrada usando o resistor PULLUP interno do Arduino
  // Isso dispensa o uso de resistores externos no protoboard
  pinMode(player1Button, INPUT_PULLUP);
  pinMode(player2Button, INPUT_PULLUP);
  pinMode(restartButton, INPUT_PULLUP);
  pinMode(pointPlayer1Button, INPUT_PULLUP);
  pinMode(pointPlayer2Button, INPUT_PULLUP);
  pinMode(generalResetButton, INPUT_PULLUP);

  // Configura os pinos dos LEDs como saída
  pinMode(player1LED, OUTPUT);
  pinMode(player2LED, OUTPUT);

  // Garante que os LEDs comecem desligados
  digitalWrite(player1LED, LOW);
  digitalWrite(player2LED, LOW);

  // Inicialização do LCD
  lcd.init();          // Inicializa o hardware do display
  lcd.backlight();     // Ativa a iluminação traseira do LCD

  welcomeMessage();    // Chama a função de boas-vindas
  delay(3000);         // Pausa de 3 segundos para leitura
  updateLCD();         // Exibe o placar inicial (0 a 0)
}

// ===== LOOP PRINCIPAL =====
void loop() {
  // Captura o tempo atual de funcionamento do Arduino
  unsigned long currentMillis = millis();

  // ===== LÓGICA DE VELOCIDADE (QUEM APERTOU PRIMEIRO) =====
  if (roundInProgress && !pointGiven) {

    // Verifica Jogador 1 (LOW pois o INPUT_PULLUP inverte o sinal)
    if (digitalRead(player1Button) == LOW && !player1HasPressed && (currentMillis - lastPressTime > debounceDelay)) {
      lastPressTime = currentMillis;  // Atualiza tempo do debounce

      digitalWrite(player1LED, HIGH); // Acende LED do J1
      digitalWrite(player2LED, LOW);  // Garante que o J2 fique apagado

      player1HasPressed = true;       // Trava a escolha
      roundInProgress = false;        // Bloqueia novas pressões até o reset
      updateLCD();
    }

    // Verifica Jogador 2
    if (digitalRead(player2Button) == LOW && !player2HasPressed && (currentMillis - lastPressTime > debounceDelay)) {
      lastPressTime = currentMillis;

      digitalWrite(player2LED, HIGH); // Acende LED do J2
      digitalWrite(player1LED, LOW);

      player2HasPressed = true;
      roundInProgress = false;
      updateLCD();
    }
  }

  // ===== ATRIBUIÇÃO DE PONTO (JOGADOR 1) =====
  if (digitalRead(pointPlayer1Button) == LOW && (currentMillis - lastPressTime > debounceDelay) && !pointGiven) {
    lastPressTime = currentMillis;

    if (!roundInProgress) {           // Só permite dar ponto se alguém tiver apertado antes
      player1Score++;                 // Incrementa pontuação
      pointGiven = true;              // Registra que o ponto da rodada foi entregue
      updateLCD();                    // Atualiza o display
    }
    delay(500);
  }

  // ===== ATRIBUIÇÃO DE PONTO (JOGADOR 2) =====
  if (digitalRead(pointPlayer2Button) == LOW && (currentMillis - lastPressTime > debounceDelay) && !pointGiven) {
    lastPressTime = currentMillis;

    if (!roundInProgress) {
      player2Score++;
      pointGiven = true;
      updateLCD();
    }
    delay(500);
  }

  // ===== REINICIAR RODADA (MANTÉM PLACAR) =====
  if (!roundInProgress && pointGiven && digitalRead(restartButton) == LOW && (currentMillis - lastPressTime > debounceDelay)) {
    lastPressTime = currentMillis;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nova rodada!");
    lcd.setCursor(0, 1);
    lcd.print("Aguarde...");
    delay(3000);

    // Reseta as flags de controle para a próxima pergunta
    roundInProgress = true;
    pointGiven = false;
    player1HasPressed = false;
    player2HasPressed = false;

    // Apaga os indicadores luminosos
    digitalWrite(player1LED, LOW);
    digitalWrite(player2LED, LOW);

    updateLCD();
    delay(500);
  }

  // ===== RESET GERAL (ZERA TUDO) =====
  if (digitalRead(generalResetButton) == LOW && (currentMillis - lastPressTime > debounceDelay)) {
    lastPressTime = currentMillis;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reiniciando...");
    lcd.setCursor(0, 1);
    lcd.print("Aguarde...");
    delay(3000);

    player1Score = 0;        // Zera pontos J1
    player2Score = 0;        // Zera pontos J2
    pointGiven = false;
    roundInProgress = true;
    player1HasPressed = false;
    player2HasPressed = false;

    digitalWrite(player1LED, LOW);
    digitalWrite(player2LED, LOW);

    updateLCD();
    delay(500);
  }
}

// ===== FUNÇÃO: MENSAGEM INICIAL =====
void welcomeMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);           // Posiciona na coluna 0, linha 0
  lcd.print("Bem-vindos");
  lcd.setCursor(0, 1);           // Posiciona na coluna 0, linha 1
  lcd.print("TI Senac Reg");
}

// ===== FUNÇÃO: ATUALIZA EXIBIÇÃO DO PLACAR =====
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogador 1: ");
  lcd.print(player1Score);       // Exibe o valor da variável de pontuação

  lcd.setCursor(0, 1);
  lcd.print("Jogador 2: ");
  lcd.print(player2Score);
}