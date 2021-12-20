# Trabalho 02 de Sistemas Operacionais: Projeto dos Trens

## Resumo
Segundo trabalho da matéria de Sistemas Operacionais do BTI. Implementação de conceitos de programação paralela e acesso à regiões compartilhadas. 

O trabalho consiste no desenvolvimento de uma malha ferroviária que comporta 5 trens, todos circulando no sentido horário. Cada trem deve circular em sua malha sem colidir com os demais trens. Além disso, se um trem pode se mover sem causar colisão ou deadlock, ele deve se mover.

## Solução
Para o tratamento foram criados mutexes para evitar colisões e semáforos para o tratamento dos deadlocks. Primeiramente há um mutex <i><b>regiaoCritica</i></b> para realizar as checagens se o trem pode entrar na devida <i><b>Zona geral, Área, Conjunto</b></i> e/ou <i><b>Região</b></i>.
### Regiões
Foram usados sete mutexes, um para cada trilho compartilhado (<i><b>regiao[7]</i></b>), para evitar as colisões, fazendo com que apareça os deadlocks. Estes deadlocks estão organizados em três tipos: deadlocks de área, deadlock de conjunto e deadlock geral.

### Seções da malha ferroviária
#### 1.Áreas
Primeiramente, a malha foi dividida em três áreas: área 1 (regiões 0, 2 e 3), área 2 (regiões 1, 2 e 5) e área 3 (regiões 3, 4 e 6). Em cada área ocorreu um deadlock quando três trens a acessou ao mesmo tempo, logo, esse deadlock foi tratado com três semáforos de dois acessos: <i><b>area1(2), area2(2)</i></b> e <i><b>area3(2)</i></b>.
#### 2.Conjuntos
Segundamente, a junção de duas áreas foi chamada de conjunto, o que resulta em dois conjuntos: conjunto 1 (áreas 1 e 2) e conjunto 2 (áreas 1 e 3). Em cada conjunto ocorriam dois tipos de deadlocks quando entravam quatro trens em cada conjunto, logo, esses deadlocks foram tratados com semáforos de três acessos para cada conjunto: <i><b>conjunto1(3)</i></b> e <i><b>conjunto2(3)</i></b>.
#### 3.Geral
Outrossim, a junção dos dois conjuntos gerou a zona geral, que inclui todas regiões compartilhadas pelos trens. Nesse caso ocorria um deadlock quando todos cincos trens acessavam a zona geralm, assim, esse deadlock foi tratado com um semáforo de quatro acessos: <i><b>geral(4)</i></b>.

## [Apresentação em vídeo](https://youtu.be/HlKdN1hH9tw)


## Autor

Angelo Gustavo Souza Marinho Morais de Sales -
[GitHub](https://github.com/AngeloGustavo)

## Contato

Angelo Gustavo Souza Marinho Morais de Sales -
*<angelo.sales.703@ufrn.edu.br>*


