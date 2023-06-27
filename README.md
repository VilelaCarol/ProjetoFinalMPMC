# ProjetoFinalMPMC

- Controlador de luz ambiente

1. Introdução

Este relatório apresenta a proposta de um projeto para desenvolver um controlador de luz ambiente que atende aos requisitos técnicos estabelecidos. O objetivo é criar um sistema que leia a luminosidade do ambiente por meio do sensor LDR, exiba as informações em um display de LCD e permita ao usuário ajustar a luminosidade desejada por meio de um menu interativo. O sistema utilizará PWM para controlar a potência de uma lâmpada, garantindo que a luminosidade ambiente nunca seja inferior ao valor selecionado pelo usuário.

1. Componentes e Funcionalidades

O projeto proposto inclui os seguintes componentes e suas respectivas funcionalidades, organizados de acordo com os requisitos técnicos:

2.1. Entradas:

- Sensor LDR: Será utilizado como uma entrada analógica para medir a luminosidade do ambiente.
- Botão "Enter": Servirá como uma entrada digital com interrupção, permitindo o acesso ao menu e a confirmação de seleções.
- Botão "+": Atuará como uma entrada digital para aumentar a luminosidade desejada no menu.
- Botão "-": Servirá como uma entrada digital para diminuir a luminosidade desejada no menu.

  2.2. Saídas:

- Display LCD: Exibirá a luminosidade atual do ambiente e a luminosidade desejada selecionada pelo usuário. Além disso, possibilitará a navegação interativa no menu.
- Saída de Controle da Lâmpada: Utilizará PWM para controlar a potência da lâmpada, ajustando-a para alcançar a luminosidade desejada.
- LED de Indicação de Menu Ativo: Será uma saída digital que indicará visualmente quando o menu estiver ativo.
- LED de Indicação de Luminosidade Baixa: Servirá como uma saída digital para alertar quando a luminosidade ambiente estiver abaixo do mínimo desejado, indicando a necessidade de substituição da lâmpada.
- Buzzer Sonoro: Faz um som quando o ENTER for clicado para sair do menu e salvar as alterações na luminosidade desejada
- Linha de Leds sinalizando quantos % da potencia total da lampada esta sendo utilizada.
  - A saida será entregue à linha de led atraves de um demux para escrever a % nos leds:
    - 0 leds acesos = 0%
    - 8 leds acesos = 100%

1. Conversão da Leitura em Lux

   Para obter uma medida precisa da luminosidade do ambiente, é necessário converter a leitura digital do sensor LDR em unidades de lux. Apenas será feita uma conversão linear dos valores lidos segundo a seguinte escala:

   - 1000lux = 400 ohm
   - 10 lux = 9k ohm

2. Utilização de Timer e Watchdog

No projeto do controlador de luz ambiente, será utilizado o Watchdog Timer (WDT) para evitar travamentos do sistema.
O Timer1 será utilizado para a cada 50ms verificar a luminosidade do ambiente e compará-la com a luminosidade desejada. Caso seja menor aumenta o PWM e caso seja maior diminui o PWM.

3. Funcionamento do Controlador de Luz Ambiente

O controlador de luz ambiente proposto funcionará verificando a cada 50ms, utilizando o estouro do TIMER1, a luminosidade do ambiente e ajustando a potência da lâmpada para atingir a luminosidade desejada. O sistema buscará alcançar esse objetivo consumindo a menor quantidade de energia possível.

Ao iniciar o sistema, o controlador de luz ambiente realizará a leitura da luminosidade atual do ambiente por meio do sensor LDR. Essa leitura será convertida em unidades de lux, conforme descrito na seção 3 do relatório.

Em seguida, o valor da luminosidade atual será comparado com o valor da luminosidade desejada selecionada pelo usuário. Se a luminosidade atual for menor do que a desejada, o sistema aumentará gradualmente a potência da lâmpada. Para isso, será utilizado o controle por PWM (Pulse Width Modulation), que ajusta o ciclo de trabalho do sinal de controle da lâmpada.

No entanto, se a luminosidade atual for maior do que a desejada e a lâmpada estiver acesa, o sistema diminuirá a potência da lâmpada para alcançar a luminosidade desejada, evitando o desperdício de energia. O controle por PWM permitirá reduzir gradualmente o ciclo de trabalho do sinal de controle da lâmpada.

Durante todo o processo, as informações da luminosidade atual do ambiente e da luminosidade desejada serão exibidas no display de LCD. Além disso, o menu interativo permitirá ao usuário ajustar a luminosidade desejada utilizando os botões "+" e "-". O LED de Indicação de Menu Ativo fornecerá uma indicação visual quando o menu estiver em uso.

Complementando as informações do LCD, uma linha de LEDs informá ao usuário quantos porcento da energia total da lampada está sendo utilizada neste momento.

O controlador de luz ambiente também monitorará a luminosidade ambiente em relação ao mínimo desejado. Se a luminosidade ambiente estiver abaixo desse valor, o LED de Indicação de Luminosidade Baixa será acionado, alertando o usuário sobre a necessidade de substituição da lâmpada.

Para fornecer feedback sonoro ao usuário, o sistema utilizará o Buzzer Sonoro. Esse componente emitirá um som para indicar ao usuário que a alteração no valor da luminosidade desejada foi salvo.

Com esse funcionamento, o controlador de luz ambiente proporcionará um ambiente com a luminosidade desejada pelo usuário, ajustando a potência da lâmpada de forma eficiente e economizando energia.