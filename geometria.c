/**
*	geometria.c
*
*	Cria uma nuvem de pontos no arquivo polygon.json e calcula os
*	pontos que formam os vertices do fecho convexo da nuvem
*
*	@autor <chinaglia.rafa@gmail.com> Rafael Chinaglia
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

// Modo automatico 
#define AUTO 1
//	Numero maximo de pontos a serem posicionados na tela
#define LIMITE_PONTOS 20
//	Limites do plano cartesiano
#define TOTAL_WIDTH 500
#define TOTAL_HEIGHT 500

int NUMERO_PONTOS = 0;

typedef enum { false, true } bool;

/**
*	Verifica, para cada ponto que nao compoe a reta, o lado em que ele esta
*	em relacao a reta. Se algum for encontrado de um lado diferente, a reta
*	e desaprovada, caso contrario, ela e parte do fecho convexo.
**/
bool validarPossivelLinha (int x1, int y1, int x2, int y2, int (*pontos)[NUMERO_PONTOS][2]) {
	
	int i;
	//	sinal da direcao do ponto ( d > 0 => um lado, d < 0 => lado oposto )
	int d = 0;
	//	coordenadas X e Y do ponto P
	int xp = 0, yp = 0;
	bool maiorQueZero = true;
	int anterior = -1;
	
	for (i = 0; i < NUMERO_PONTOS; i++) {
		xp = (*pontos)[i][0];
		yp = (*pontos)[i][1];
		//	se o ponto P for igual a um dos pontos que compôem o segmento, ignore-o
		if ((xp == x1 && yp == y1) || (xp == x2 && yp == y2)) continue;
		//	 TODO: Entender essa formula
		d = (xp - x1) * (y2 - y1) - (yp - y1) * (x2 - x1);
		if (d == 0) return false;
		if (d > 0) maiorQueZero = true; else maiorQueZero = false;
		if (maiorQueZero != anterior && anterior != -1) return false;
		anterior = maiorQueZero;
	}
	
	return true;
}

void main () {
	
	srand(time(NULL));
	
	int LOCK = 0;
	while (LOCK == 0) {
		NUMERO_PONTOS = rand() % LIMITE_PONTOS;
		int i, z;	//	contadores
		int pontos[NUMERO_PONTOS][2];
		FILE *fp;
		//	Arquivo usado para desenhar o poligono em javascript
		fp = fopen("polygon.json", "w");
		if (fp == NULL) {
			printf("Falha ao abrir arquivo.");
			exit(0);
		}
		
		fprintf(fp, "{\"pontos\": [");
		
		//	Geracao da nuvem de pontos
		for (i = 0; i < NUMERO_PONTOS; i++) {
			//	pontos[i][0] corresponde a abscissa
			pontos[i][0] = rand() % TOTAL_WIDTH;
			//	pontos[i][1] corresponde a ordenada
			pontos[i][1] = rand() % TOTAL_HEIGHT;
			
			printf("pontos[%d][0] = %d\n", i, pontos[i][0]);
			printf("pontos[%d][1] = %d\n", i, pontos[i][1]);
			printf("\n");
			//	Aqui sao gravadas as coordenadas dos pontos
			fprintf(fp, "{\"x\": %d, \"y\": %d}", pontos[i][0], pontos[i][1]);
			if (i < NUMERO_PONTOS - 1) {
				fprintf(fp, ",");
			}
		}
		
		fprintf(fp, "]");
		//	Combina todos os pontos em pares e testa se a linha e uma 
		//	borda valida para conter os outros elementos
		fprintf(fp, ",\"linhas\":[");
		for (i = 0; i < NUMERO_PONTOS; i++) {
			for (z = i+1; z < NUMERO_PONTOS; z++) {
				bool linhaValida = validarPossivelLinha(pontos[i][0], pontos[i][1], pontos[z][0], pontos[z][1], &pontos);
				if (linhaValida == true) {
					printf("(%d, %d) -> (%d, %d)\n", pontos[i][0], pontos[i][1], pontos[z][0], pontos[z][1]);
				}
				if (i > 0 || z > i+1) {
					fprintf(fp, ",");
				}
				//	Aqui sao gravados cada comparacao entre linhas. Note que e o no "valida" que indica
				//	quais segmentos de reta foram aprovados e quais nao foram
				fprintf(fp, "{\"x1\": %d, \"y1\": %d, \"x2\": %d, \"y2\": %d, \"valida\": %d}", pontos[i][0], pontos[i][1], pontos[z][0], pontos[z][1], linhaValida);
			}
		}
		fprintf(fp, "]");
		fprintf(fp, "}");
		fclose(fp);
		
		if (AUTO == 0) {
			printf("\n De novo? [sim 0 / nao 1] ");
			scanf("%d", &LOCK);
		} else {
			Sleep(900);
		}
//		LOCK = 1;
	}
	return;
}
