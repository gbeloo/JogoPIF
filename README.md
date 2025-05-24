# Fuga do Dogão

Em **Fuga do Dogão**, você é um cachorrinho esperto que encontrou uma brecha e escapou de casa. Agora começa uma corrida alucinante: desvie de obstáculos pelo caminho para não ser pego pelo seu dono e veja até onde consegue chegar!

Este jogo de console em C foi desenvolvido para demonstrar diversos conceitos de programação:

* **Estruturas (structs):** para representar obstáculos e entradas de pontuação.
* **Ponteiros:** tratamento de listas encadeadas e buffer de tela.
* **Alocação dinâmica de memória:** `malloc`/`free` para lista de obstáculos e matriz de tela.
* **Listas encadeadas:** para gestão dinâmica de obstáculos.
* **Matrizes:** buffer de tela bidimensional `char**` para demonstrar uso de array dinâmico.
* **Escrita e leitura em arquivo:** manutenção de Top 3 scores em `score.txt`.

---

## Tecnologias e Bibliotecas 

* **Linguagem:** C
* **Bibliotecas customizadas:**

  * `screen.h`, `keyboard.h`, `timer.h` (controle de tela, teclado em modo raw e temporização)
* **Terminal colorido:** uso de códigos ANSI
* **Controle de tempo:** `timerInit(100)` ajusta frames de 100 ms

---

## Como Rodar 🚀

1. **Clone** o repositório:

   ```bash
   git clone https://github.com/gbeloo/JogoPIF.git
   ```
2. **Entre** na pasta do projeto:

   ```bash
   cd Fuga-do-Dogao
   ```
3. **Compile** o jogo:

   ```bash
   make clean
   make all
   ```
4. **Execute**:

   ```bash
   make run
   ```

---

## Controles 

* **Espaço** Pular obstáculos
* **ESC:** Sair do jogo

---

## Gameplay 

1. Inicie e veja a arte em ASCII na tela de menu. Pressione qualquer tecla para começar.
2. Durante o jogo, conduza o doguinho, saltando cercas com espaço.
3. Desvie das cercas para acumular pontos.
4. Ao colidir ou pressionar ESC, o jogo exibe "GAME OVER" e sua pontuação final.
5. Se estiver no Top 3, digite seu nome para salvar o recorde.

---

