#include <LiquidCrystal_I2C.h>

// Definição dos pinos para cada botão
short int vermelho = 35, azul = 33, amarelo = 32, verde = 34;
unsigned long tempo = 0; 

// Inicialização do LCD
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

void setup(){
  // Configuração dos pinos como entrada
  pinMode(vermelho, INPUT);
  pinMode(azul, INPUT);
  pinMode(amarelo, INPUT);
  pinMode(verde, INPUT);
  // Inicialização da comunicação serial
  Serial.begin(9600);
  // Inicialização do LCD e ativação da luz de fundo
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Bem-vindo");
  delay(2000); // Aguarda 2 segundos para permitir a visualização da mensagem
}

void loop() {
  // Executa a primeira etapa e armazena o resultado em 'armazenar'
  short int armazenar = Prim_etapa();

  LCD.clear();
  
  // Com base no resultado da primeira etapa, executa uma das seguintes funções
  switch (armazenar) {
    case 1:
      Seg_etapa();
      break;

    case 2:
      Ter_etapa();
      break;

    case 3:
      Quart_etapa();
      break;
  }
}

// Função da primeira etapa
int Prim_etapa() {
  short int aux = 1, aux2 = 0;
  bool teste1 = 0, teste2 = 0;
  // Loop infinito para seleção da opção
  while(1) {
    // Verifica se o botão azul foi pressionado para incrementar a opção
    if (digitalRead(azul) == 1) {
      teste1 = 1;
    }
    if (digitalRead(azul) == 0 && teste1 == 1) {
      aux++;
      if(aux > 3)
        aux = 1;
      teste1 = 0;
    }

    // Verifica se o botão amarelo foi pressionado para decrementar a opção
    if (digitalRead(amarelo) == 1) {
      teste2 = 1;
    }
    if (digitalRead(amarelo) == 0 && teste2 == 1) {
      aux--;
      if(aux < 1)
        aux = 3;
      teste2 = 0;
    }

    // Verifica se o botão verde foi pressionado para confirmar a opção
    if (digitalRead(verde) == 1) 
      return aux;

    // Atualiza o LCD com a opção selecionada
    if(aux != aux2) {
        switch (aux)
        {
        case 1:
            LCD.clear();
            LCD.setCursor(0, 0);
            LCD.print("Opcao 1:");
            LCD.setCursor(0, 1);
            LCD.print("Contar ao Clicar");
            break;

        case 2:
            LCD.clear();
            LCD.setCursor(0, 0);
            LCD.print("Opcao 2:");
            LCD.setCursor(0, 1);
            LCD.print("Relogio");
            break;

        case 3:
            LCD.clear();
            LCD.setCursor(0, 0);
            LCD.print("Opcao 3:");
            LCD.setCursor(0, 1);
            LCD.print("Zerar Dados");
            break;
        }
    }

    // Atualiza o valor de 'aux2' para comparar com 'aux' na próxima iteração
    aux2 = aux;
    delay(10);
  }
}

// Função da segunda etapa
void Seg_etapa() {
  Serial.println("Etapa 1");
  int contar = 0;
  bool teste1 = 0;
  LCD.setCursor(0, 0);
  LCD.print("Contagem:");

  // Loop infinito para a contagem
  while(1) {
    LCD.setCursor(10, 0);
    LCD.print(contar);

    // Verifica se o botão azul foi pressionado para incrementar a contagem
    if (digitalRead(azul) == 1) {
      teste1 = 1;
    }
    if (digitalRead(azul) == 0 && teste1 == 1) {
      contar++;
      Serial.println(contar);
      teste1 = 0;
    }
    
    // Verifica se o botão amarelo foi pressionado para zerar a contagem
    if (digitalRead(amarelo) == 1) {
      contar = 0;
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Contagem:");
    }

    // Verifica se o botão vermelho foi pressionado para sair da função
    if (digitalRead(vermelho) == 1) {
      LCD.clear();
      return;
    }
  }
}

// Função da terceira etapa
void Ter_etapa() {
  unsigned long tempoAnterior = 0; // Variável para armazenar o tempo anterior
  short int relogio[6] = {0}, seg = 1000;
  LCD.setCursor(2, 0);
  LCD.print(":");
  LCD.setCursor(5, 0);
  LCD.print(":");
  // Loop infinito para o relógio
  while(1) {
    unsigned long tempoAtual = millis(); // Captura o tempo atual

    // Verifica se passou um segundo desde a última atualização do relógio
    if(tempoAtual - tempoAnterior >= seg) {
      // Atualiza o valor do relógio a cada segundo
      tempoAnterior = tempoAtual;

      relogio[5]++;
      if(relogio[5] > 9) {
        relogio[5] = 0;
        relogio[4]++;
      }
      if(relogio[4] > 5) {
        relogio[4] = 0;
        relogio[3]++;
      }
      if(relogio[3] > 9) {
        relogio[3] = 0;
        relogio[2]++;
      }
      if(relogio[2] > 5) {
        relogio[2] = 0;
        relogio[1]++;
      }
      if(relogio[1] > 9) {
        relogio[1] = 0;
        relogio[0]++;
      }
      if(relogio[0] == 2 && relogio[2] > 4) {
        relogio[1] = 0;
        relogio[0] = 0;
      }

      // Atualiza o LCD com o valor do relógio
      LCD.setCursor(7, 0);
      LCD.print(relogio[5]);

      LCD.setCursor(6, 0);
      LCD.print(relogio[4]);

      LCD.setCursor(4, 0);
      LCD.print(relogio[3]);

      LCD.setCursor(3, 0);
      LCD.print(relogio[2]);

      LCD.setCursor(1, 0);
      LCD.print(relogio[1]);

      LCD.setCursor(0, 0);
      LCD.print(relogio[0]);
    }

    // Verifica se o botão azul foi pressionado para alterar a velocidade do relógio
    if (digitalRead(azul) == 1) {
      seg = 250;
    }
    // Verifica se o botão amarelo foi pressionado para voltar à velocidade normal do relógio
    if (digitalRead(amarelo) == 1) {
      seg = 1000;
    }
    // Verifica se o botão vermelho foi pressionado para sair da função
    if (digitalRead(vermelho) == 1) {
      LCD.clear();
      return;
    }
  }
}

// Função da quarta etapa
void Quart_etapa() {
  LCD.setCursor(0, 0);
  LCD.print("zerar");
  LCD.setCursor(0, 1);
  LCD.print("todos os dados?");
  bool teste = 0;
  unsigned long tempo2 = 0; 

  // Loop infinito para confirmar a ação de zerar os dados
  while(1) {
    // Verifica se o botão verde foi pressionado para confirmar a ação
    if (digitalRead(verde) == 1) {
      tempo = millis();

      if(teste == 0) {
        tempo2 = tempo;
        teste = 1;
      }

      // Se o botão verde for mantido pressionado por 3 segundos, os dados são zerados
      if((tempo - tempo2) >= 3000) {
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("zerados");
        tempo2 = tempo;
      }
      continue;
    }
    // Verifica se o botão vermelho foi pressionado para sair da função
    if (digitalRead(vermelho) == 1) {
      LCD.clear();
      return;
    }
    teste = 0;
    tempo2 = tempo;
  }
}
