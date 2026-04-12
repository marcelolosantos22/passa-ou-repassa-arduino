# Passa ou Repassa com Arduino 🕹️

[cite_start]Sistema eletrônico interativo de baixo custo desenvolvido para mediação imparcial de jogos de perguntas e respostas, garantindo precisão milimétrica na identificação do competidor mais rápido[cite: 9, 11].

## 📋 Sobre o Projeto
[cite_start]Este dispositivo foi desenvolvido por estudantes do **Curso Técnico em Internet das Coisas (IoT)** do **SENAC Registro** sob orientação do Prof. Marcelo Lima[cite: 1, 6, 58]. [cite_start]O sistema utiliza um microcontrolador ATmega328P para monitorar os botões e gerenciar a lógica do jogo através de uma Máquina de Estados Finitos (FSM)[cite: 59, 136].

### Principais Funcionalidades
* [cite_start]**Precisão Temporal:** Detecta o primeiro acionamento e bloqueia imediatamente as entradas subsequentes[cite: 11, 60].
* [cite_start]**Interface Visual:** Exibe o placar em tempo real em um display LCD I2C e sinaliza o vencedor via LEDs[cite: 12, 133].
* [cite_start]**Estrutura Robusta:** Gabinete trapezoidal em MDF de 6 mm projetado para durabilidade e ergonomia[cite: 13, 62].
* [cite_start]**Debounce via Software:** Algoritmo baseado em `millis()` para evitar acionamentos falsos ou duplos[cite: 141, 142].

## 🛠️ Especificações Técnicas
* [cite_start]**Microcontrolador:** Arduino Uno ou Nano[cite: 124].
* [cite_start]**Comunicação:** Protocolo I2C (SDA no A4, SCL no A5)[cite: 133].
* [cite_start]**Lógica de Entrada:** Configuração `INPUT_PULLUP` (dispensa resistores externos nos botões)[cite: 96, 129].
* [cite_start]**Alimentação:** Fonte externa de 7V a 12V via conector P4[cite: 121, 124].

## 📂 Organização do Repositório
* [cite_start]**`/01_Codigo`**: Firmware (.ino) desenvolvido em C++[cite: 135].
* **`/02_Arquivos_STL`**: Modelos 3D para impressão dos botões de 29mm[cite: 124, 202].
* [cite_start]**`/03_Documentacao`**: Guia completo de montagem, esquemas elétricos e lista de materiais[cite: 4, 122].
* **`/04_Imagens`**: Fotos do protótipo finalizado e fluxogramas lógicos[cite: 174, 175].

## 🚀 Como Replicar
1. [cite_start]Monte a estrutura de MDF seguindo as dimensões do manual[cite: 112].
2. [cite_start]Realize as conexões eletrônicas conforme o mapeamento de pinos[cite: 133].
3. [cite_start]Instale a biblioteca `LiquidCrystal I2C` na Arduino IDE[cite: 231].
4. [cite_start]Carregue o código da pasta `01_Codigo` para o seu microcontrolador[cite: 236].

## 👥 Equipe de Desenvolvimento
Orientador: **Prof. [cite_start]Marcelo Lima Oliveira Santos**[cite: 6].
[cite_start]Equipe: Ana Carolina Corrêa Silva, Daniel De Lima Lopes, Diogo Damião Correa Silva, Francielly Cristina Pereira, Gabriel Lara dos Santos, Gustavo Stolarz Martins, Igor Gonçalves da Silva Oliveira, João Victor de Morais, Rafaela Costa e Silva, Túlio Cadilhac Zanella, Victor de França Sales, Vinicius André Pinheiro[cite: 5].

---
Registro – SP | [cite_start]2026 [cite: 7]