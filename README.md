# Fecho Convexo
Grava um arquivo .json contendo uma constelação de pontos e todas os segmentos de reta que ligam esses pontos, indicando quais segmentos compoem o fecho convexo da constelação de pontos.

## Como gerar:

Compile o arquivo **geometria.c** ou execute o arquivo _geometria.exe_. Note que no início do arquivo, algumas definições são úteis para personalizar a execução.
```C
// Modo automatico 
#define AUTO 1
//	Numero maximo de pontos a serem posicionados na tela
#define LIMITE_PONTOS 20
```
* **AUTO**: define se o programa gravará uma nova constelação a cada 900ms ou se ele perguntará ao usuário se ele deseja repetir o processo manualmente;
* **LIMITE_PONTOS**: representa a quantidade máxima de pontos que serão sorteadas para comporem a constelação;

## Como visualizar:

* **render_constellation.html**
    Renderiza uma constelação de pontos usando as informações do arquivo polygon.json _por segundo_. Para isso, o arquivo usa javascript e canvas.
* **animated.html**
    Renderiza uma constelação de forma animada, mostrando cada linha sendo posicionada com o tempo.
    
## Servidor local:

Para que o javascript consiga ler o arquivo polygon.json, são feitas requisições XHR sequenciais, e para tal é preciso usar o protocolo HTTP. Se você tem python, uma forma simples de criar um servidor HTTP rápido é através do comando abaixo, que deve ser executado na pasta onde os arquivos .html estão:
```
py -m SimpleHTTPServer
```
O endereço padrão para acessr os arquivos, após isso, é 
* http://127.0.0.1:8000/render_constellation.html
* http://127.0.0.1:8000/animated.html


# TO-DO

- [ ] Implementar novas versões de **geometria.c** com novas técnicas de cálculo de fecho convexo
- [ ] Compor um relatório comparativo entre as técnicas
- [ ] Encontrar a melhor técnica para calcular o fecho convexo de uma constelação com _milhões de pontos_.
