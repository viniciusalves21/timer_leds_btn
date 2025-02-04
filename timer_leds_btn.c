#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Define os pinos dos LEDs e do botão
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_PIN 5


// Variáveis globais
bool leds_ligados = false; // Indica se os LEDs estão ligados
bool botao_pressionado = false; // Flag para controlar o botão
int estado_led = 1; // 0: todos ligados, 1: dois ligados, 2: um ligado
int a = 1;// controle interno

// Função para configurar os LEDs de acordo com o estado
void configurar_leds() {
  switch (estado_led) {

    case 0: // Todos ligados
      gpio_put(LED_PIN_RED, true);
      gpio_put(LED_PIN_GREEN, true);
      gpio_put(LED_PIN_BLUE, true);
      printf("TODOS LIGADOS\n");
      break;
    case 1: // Dois ligados (vermelho e verde)
      gpio_put(LED_PIN_RED, true);
      gpio_put(LED_PIN_GREEN, true);
      gpio_put(LED_PIN_BLUE, false);
      printf("VERMELHO E VERDE LIGADOS\n");
      break;
    case 2: // Um ligado (vermelho)
      gpio_put(LED_PIN_RED, true);
      gpio_put(LED_PIN_GREEN, false);
      gpio_put(LED_PIN_BLUE, false);
      printf("VERMELHO LIGADO\n");
      break;
    default: // Desligados
      gpio_put(LED_PIN_RED, false);
      gpio_put(LED_PIN_GREEN, false);
      gpio_put(LED_PIN_BLUE, false);
      printf("TODOS DESLIGADOS\n\n");

      printf("Acionamento %d finalizado\n", a++);//controle interno pra identificar quantas vezes passou por esse ciclo 
      break;
  }
}

// Função de callback do temporizador
int64_t timer_callback(alarm_id_t id, void *user_data) {
  if (leds_ligados) {
    estado_led++; // Avança para o próximo estado
    configurar_leds(); // Atualiza os LEDs

    if (estado_led > 2) { // Se chegou ao último estado
      leds_ligados = false;
      botao_pressionado = false; // Libera o botão
      estado_led = 0; // Reinicia o estado dos LEDs
    } else {
      add_alarm_in_ms(3000, timer_callback, NULL, false); // Agenda o próximo alarme
    }
  }
  return 0;
}

int main() {
  stdio_init_all();

  // Configura os pinos dos LEDs como saída
  gpio_init(LED_PIN_GREEN);
  gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
  gpio_init(LED_PIN_BLUE);
  gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
  gpio_init(LED_PIN_RED);
  gpio_set_dir(LED_PIN_RED, GPIO_OUT);

  // Configura o pino do botão como entrada com pull-up interno
  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_PIN);

  while (true) {
    // Verifica se o botão foi pressionado e se os LEDs não estão ligados
    if (gpio_get(BUTTON_PIN) == 0 && !leds_ligados && !botao_pressionado) {
      sleep_ms(50); // Debounce
      if (gpio_get(BUTTON_PIN) == 0) {
        botao_pressionado = true;
        leds_ligados = true;
        estado_led = 0; // Inicializa o estado dos LEDs
        configurar_leds(); // Liga todos os LEDs
        add_alarm_in_ms(3000, timer_callback, NULL, false); // Agenda o primeiro alarme
      }
    }
    sleep_ms(10); // Delay para reduzir o uso da CPU
  }

  return 0;
}