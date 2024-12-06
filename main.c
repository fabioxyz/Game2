#include <stdio.h>
#define TMAX 100

void interface() {
	int i;
	for (i = 0; i < 26; i++) {
		printf("*");
	}
	putchar('\n');
	printf("*"); printf("\t  M E N U \t"); printf(" *"); putchar('\n');
	printf("*"); printf("\tby:fabioxyz\t"); printf(" *"); putchar('\n');
	printf("*"); printf("\t\t\t *"); putchar('\n');
	printf("*"); printf(" (1) Comecar | (2) Sair "); printf("*"); putchar('\n');
	for (i = 0; i < 26; i++) {
		printf("*");
	}
	putchar('\n');
	putchar('\n');
}

int ler() {
	int e;
	printf("EU : ");
	scanf("%d", &e);
	return e;
}

int gerador() {
	int numero;
	numero = (rand() % 3) + 1;

	return numero;
}

char resultado(int jogador, int pc) {
	//jogador pedra
	if (jogador == pc) {
			return 'E';
	}
	if (jogador == 1 && pc == 2 ||
		jogador == 2 && pc == 3 ||
		jogador == 3 && pc == 1) {
		return 'D';
	}
	if (jogador == 1 && pc == 3 ||
		jogador == 2 && pc == 1 ||
		jogador == 3 && pc == 2) {
		return 'V';
	}
}

char *traducao(char res) {

	if (res == 'E') {
		return "Empate";
	}
	else if (res == 'V') {
		return "Vitoria";
	}
	else {
		return "Derrota";
	}
}

int w_ficheiro(int recorde) {
	FILE* fp;

	fp = fopen("recorde.bin", "wb");

	if (fp == NULL) {
		printf("Erro ao escrever o recorde.");
		return 1;
	}
	fwrite(&recorde, sizeof(recorde), 1, fp);

	fclose(fp);
	return 0;
}

int r_ficheiro() {
	int recorde;
	FILE* fp;

	fp = fopen("recorde.bin", "rb");

	if (fp == NULL) {
		fp = fopen("recorde.bin", "wb");
		return recorde = 0;
	}
	fread(&recorde, sizeof(recorde), 1, fp);

	fclose(fp);
	return recorde;
}

int main() {
	int e, jogador, pc, res, n = 0;
	int v, d, emp, r, recorde;
	srand(time(NULL));
		
	interface();
	do {
		e = ler();
		switch (e) {
		case 1:
			do {
				recorde = r_ficheiro();
				n=0, v = 0, d = 0, emp = 0;
				do {
					printf("Atual recorde : %d vitorias\n", recorde);
					do {
						printf("\n\t1)Pedra | 2)Papel | 3)Tesoura\n");
						jogador = ler();
					} while (jogador != 1 && jogador != 2 && jogador != 3);
					pc = gerador();
					printf("PC : %d\n\n", pc);
					n++;
					res = resultado(jogador, pc);
					if (res == 'V') v++;
					if (res == 'D') d++;
					if (res == 'E') emp++;
					printf("Resultado : %s\n\n", traducao(res));
				} while (n != 5);

				printf("Estatisticas (%d partidas) :\n", n);
				printf("\tVitorias(%.1f%%) : %d\n", ((float)v / n) * 100, v);
				printf("\tDerrotas(%.1f%%) : %d\n", ((float)d / n) * 100, d);
				printf("\tEmpates(%.1f%%) : %d\n\n", ((float)emp / n) * 100, emp);
				
				if (v > recorde) {
					recorde = v;
					printf("\tParabens novo recorde (%d vitorias) !!\n\n", v);
					w_ficheiro(recorde);
				}
				else {
					printf("Recorde : %d vitorias.\n\n", recorde);
				}

				do {
					printf("\n\t1)Reiniciar || 2)Sair\n\n");
					r = ler();
				}while(r != 1 && r!= 2);
				if (r == 2) printf("\n\nSaiu.\n\n");
			} while (r != 2);
			break;
		case 2: printf("\n\nSaiu.\n\n");
			return 1; break;
		default: printf("Opcao invalida!\n");
			break;
		}
	} while (e != 1 && e != 2);
}
