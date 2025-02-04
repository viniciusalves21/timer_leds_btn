# Este repositório contém um código em C para Raspberry Pi Pico que controla um LED RGB (vermelho, verde e azul) usando um botão e um temporizador. O código demonstra o uso de interrupções de temporizador (alarme) e controle de GPIO (pinos) no Pico SDK.

## Descrição
O código implementa um sistema de temporização one-shot (um disparo) para controlar o acendimento de um LED RGB. Ao pressionar um botão, o LED RGB acende em uma sequência específica:

Todos os LEDs (vermelho, verde e azul) acendem.
Após 3 segundos, dois LEDs (vermelho e verde) permanecem acesos.
Após mais 3 segundos, apenas um LED (vermelho) permanece aceso.
Após outros 3 segundos, todos os LEDs se apagam.
O botão só pode iniciar uma nova sequência de acendimento após o término da anterior, ou seja, quando todos os LEDs estiverem apagados.

## Observações
O código inclui um debounce de software para o botão, evitando leituras falsas devido a vibrações.
O temporizador está configurado para um atraso de 3 segundos entre cada mudança de estado dos LEDs. Este valor pode ser ajustado conforme necessário.
O código foi testado em um ambiente de desenvolvimento Raspberry Pi Pico e na placa BitDogLab.
