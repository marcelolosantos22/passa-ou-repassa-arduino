# Passa ou Repassa com Arduino 🕹️

Sistema eletrônico interativo de baixo custo desenvolvido para mediação imparcial de jogos de perguntas e respostas, garantindo precisão milimétrica na identificação do competidor mais rápido.

## Sobre o Projeto
Este dispositivo foi desenvolvido por estudantes do **Curso Técnico em Internet das Coisas (IoT)** do **SENAC Registro** sob orientação do Prof. Marcelo Lima. O sistema utiliza um microcontrolador ATmega328P para monitorar os botões e gerenciar a lógica do jogo através de uma Máquina de Estados Finitos (FSM).

### Principais Funcionalidades
**Precisão Temporal:** Detecta o primeiro acionamento e bloqueia imediatamente as entradas subsequentes.  
**Interface Visual:** Exibe o placar em tempo real em um display LCD I2C e sinaliza o vencedor via LEDs.  
**Estrutura Robusta:** Gabinete trapezoidal em MDF de 6 mm projetado para durabilidade e ergonomia.  
**Debounce via Software:** Algoritmo baseado em `millis()` para evitar acionamentos falsos ou duplos.  

## Especificações Técnicas
**Microcontrolador:** Arduino Uno ou Nano.  
**Comunicação:** Protocolo I2C (SDA no A4, SCL no A5).  
**Lógica de Entrada:** Configuração `INPUT_PULLUP` (dispensa resistores externos nos botões).  
**Alimentação:** Fonte externa de 7V a 12V via conector P4.  

## Organização do Repositório
**01_Codigo:** Firmware (.ino) desenvolvido em C++.  
**02_Arquivos_STL:** Modelos 3D para impressão dos botões de 29mm.  
**03_Documentacao:** Guia completo de montagem, esquemas elétricos e lista de materiais.  
**04_Imagens:** Fotos do protótipo finalizado e fluxogramas lógicos.  

## Como Replicar
1. Monte a estrutura de MDF seguindo as dimensões do manual.  
2. Realize as conexões eletrônicas conforme o mapeamento de pinos.  
3. Instale a biblioteca `LiquidCrystal I2C` na Arduino IDE.  
4. Carregue o código da pasta `01_Codigo` para o seu microcontrolador.  

## Equipe de Desenvolvimento
**Orientador:** Prof. Marcelo Lima Oliveira Santos.  
  
**Equipe:** Ana Carolina Corrêa Silva, Daniel De Lima Lopes, Diogo Damião Correa Silva, Francielly Cristina Pereira, Gabriel Lara dos Santos, Gustavo Stolarz Martins, Igor Gonçalves da Silva Oliveira, João Victor de Morais, Rafaela Costa e Silva, Túlio Cadilhac Zanella, Victor de França Sales, Vinicius André Pinheiro.  

**Registro – SP | 2026**
