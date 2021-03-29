#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include<time.h>
struct strpeca {
    int conteudo1;
    int conteudo2;
    int utilizador; //INDICA SE A PEÇA JÁ FOI UTILIZADA (0-Livre, 1-Jogador, 2-Computador, 5-Na Mesa)
};


typedef struct strpeca peca ;

//--------------Aula1:


peca pecas[27];





int inicializaPecas(){
	int x,y,cont=0;
	
	for(x=0;x<=6;x++){
		for(y=x;y<=6;y++){
			pecas[cont].conteudo1 = x;
			pecas[cont].conteudo2 = y;
			pecas[cont].utilizador = 0;//esta livre para pegar
			cont++;
		}
	}
	return 0;
}


int imprime(){
	int x,y,cont=0;
	
	for(x=0;x<=6;x++){
		for(y=x;y<=6;y++){
			printf("(%d, %d)Pertence: %d",pecas[cont].conteudo1,pecas[cont].conteudo2, pecas[cont].utilizador);
			cont++;
		}
		printf("\n");
	}
}


//--------------------Aula 2:


int geraRand(){//fica
	return rand() % 28;
}





//-------------- Parte 3 Renovando a parte 2 apos a aula do professor(foi excluido o feito antes pois estava dando erro de compilacao)


void setPecasJogadores(int jogador){//criar pecas para jogadores
	int cont = 0;
	int aux = 0;
	
	srand(time(NULL));
	
	while(cont < 7)
	{
		aux = geraRand();
		
		if(pecas[aux].utilizador == 0)
		{
			pecas[aux].utilizador = jogador;
			cont++;
		}		
	}
	
}


void printPecas(int tipo, int linha)
{
	int cont = 0;
	int l = linha;
	int c = 1;
	int x;
	
	for(x=0; x<28; x++)
	{
		if(pecas[x].utilizador == tipo)
		{
			//printf("%d",x);
			desenhaPeca(x, c, l);
			c = c + 8;
			cont++;
		}			
		
		if(cont > 7)
		{
			l = l + 9;
			c = 1;
			cont = 0;
		}		
	}	
}


int iniciarJogado(){
	int i;
	int inicial = 0;
	int repetidas = 0;
	for(i=0;i<28;i++){
		//se tiver pecas iguais e a soma delas forem maiores ou iguais a inicial 0/0 e pertence a um jogador
		//falamos que a posicao inicial agr vale a posicao analisada
		//colocamos na variavel repetidas que as pecas sao iguais
		if((pecas[i].conteudo1==pecas[i].conteudo2)&&((pecas[inicial].conteudo1+pecas[inicial].conteudo2)<=(pecas[i].conteudo1+pecas[i].conteudo2)&& ((pecas[i].utilizador==1) || (pecas[i].utilizador==2)))){
			inicial = i;
			repetidas=1;
			//printf("%d,%d\n",pecas[inicial].conteudo1, pecas[inicial].conteudo2);
		}
	}	
	
	//se tiver pecas iguais nao precisa fazer essa parte
	if(repetidas==0){
		//se nao tiver pecas iguais busca a soma de maior valor
		for(i=0;i<28;i++){	
			if(((pecas[i].conteudo1+pecas[i].conteudo2)>(pecas[inicial].conteudo1+pecas[inicial].conteudo2))&& ((pecas[i].utilizador==1) || (pecas[i].utilizador==2))){
				inicial = i;
				//printf("%d,%d\n",pecas[inicial].conteudo1, pecas[inicial].conteudo2);
			}	
		}
	}
	//printf("inicidou o jogador:%d , com a peca: (%d,%d)",pecas[inicial].utilizador, pecas[inicial].conteudo1, pecas[inicial].conteudo2);
	pecas[inicial].utilizador = 5;
	return inicial;
}




int escolherPeca(){
	int pecaCima;
	int pecaBaixo;
	int i;
	int pecaAchada = 30;
	
	printf("\nEscolha uma peca: (Para comprar basta escolher uma peca existente qualquer)\n");
	printf("Numero cima:");
	scanf("%d",&pecaCima);
	printf("Numero Baixo:");
	scanf("%d",&pecaBaixo);
	
	//printf("(%d,%d) pecas escolhidas",pecaCima,pecaBaixo);
	for(i=0;i<28;i++){
		if((pecas[i].conteudo1==pecaCima)&&(pecas[i].conteudo2==pecaBaixo)&&(pecas[i].utilizador==1)){
			pecaAchada = i;
		}	
	}
	if(pecaAchada==30){
		printf("\nPeca nao encontrada, tente novamente");
		escolherPeca();
	}else{
		return pecaAchada;
	}
}

void comprarPeca(int jogador){
	int cont = 0;
	int aux = 0;
	int i;
	int cont2 = 0;
	int cont3 = 0;
	
	//srand(time(NULL));
	
	while(cont < 1)
	{
		aux = geraRand();
		
		if(pecas[aux].utilizador == 0)
		{
			pecas[aux].utilizador = jogador;
			cont++;
		}
		cont2++;
		if(cont2==28){
			for(i=0;i<28;i++){
				if(pecas[aux].utilizador != 0){
					cont3++;
				}
				if(cont3==28){
					printf("Nao tem mais pessas para comprar");
					cont++;
				}
			}
		}		
	}
}

void desenhaJogadorEMesa(){
	system("cls");
	printPecas(1, 1);
	printf("------\n");
	//printf("J2(PC):\n");
	//printPecas(2, 21);
	printPecas(5, 21);
	printf("Mesa.");
}


void jogar(){
	int j1 = 0;
	int j2 = 0;
	int fim = 0;
	int i;
	int vez;
	int ultimaPecaMesa = iniciarJogado();//faz primeira jogada e traz a peca
	int conteudoEsq = pecas[ultimaPecaMesa].conteudo1;
	int conteudoDir = pecas[ultimaPecaMesa].conteudo2;
	
	for(i=0;i<28;i++){//coloca quantas pecas estao sendo usadas
		if(pecas[i].utilizador == 1){
			j1 += 1;
		}
		if(pecas[i].utilizador==2){
			j2 += 1;
		}
	}
	
	if(j1>j2){//declara de quem é vez
		vez=1;
	}else{
		vez=2;
	}
	
	printf("num pecas j1:%d j2:%d vez:%d",j1,j2,vez);
	printf("\nValor peca esquerda: %d e direita:%d\n",conteudoEsq,conteudoDir);
	system("pause");
	
	while(fim==0){
		//desenhaJogadorEMesa();
		
		if(vez==2){//computador
			for(i=0;i<28;i++){
				if (pecas[i].utilizador==2){
					//vejo os numeros direta e esquerda e coloco as pecas de acordo com sua nescessidade
					if(pecas[i].conteudo1==conteudoEsq){
						conteudoEsq = pecas[i].conteudo2;
						vez = 1;
						pecas[i].utilizador=5;
						i=28;
						printf("\n esquerda %d\n ",conteudoEsq );
						j2 -= 1;
					}else{
						if(pecas[i].conteudo2==conteudoEsq){
							conteudoEsq = pecas[i].conteudo1;
							vez = 1;
							pecas[i].utilizador=5;
							i=28;
							printf("\n esquerda %d\n ",conteudoEsq );
							j2 -= 1;	
						}else{
							if(pecas[i].conteudo1==conteudoDir){
								conteudoDir = pecas[i].conteudo2;
								vez = 1;
								pecas[i].utilizador=5;
								i=28;
								printf("\n direita %d\n ",conteudoDir );
								j2 -= 1;
							}else{
								if(pecas[i].conteudo2==conteudoDir){
									conteudoDir = pecas[i].conteudo1;
									vez = 1;
									pecas[i].utilizador=5;
									i=28;
									printf("\n direita %d\n ",conteudoDir );
									j2 -= 1;	
								}
							}
						}
					}
							
				}
			}
		}
		if(vez==2){//compra peca se nao fez jogada
			vez = 1;
			comprarPeca(2);
			i=28;
			printf("\n comprou \n " );
			j2 += 1;
//			vez = 1; // so pra fazer o j1
//			printf("\nvez 2\n");
		}
		if(j2==0){//pra pula a vez do j1 se computador ganahar
			vez = 2;
		}
		
		//system("pause");	
		desenhaJogadorEMesa();
		printf("\nValor peca esquerda: %d e direita:%d\nNumero pecas computador:%d",conteudoEsq,conteudoDir,j2);
		
		
		
		if(vez==1){
			int posicaoEscolhida; 
			posicaoEscolhida = escolherPeca();
			//printf("posicao escolhida(%d,%d)",pecas[posicaoEscolhida].conteudo1, pecas[posicaoEscolhida].conteudo2);
			
				if (pecas[posicaoEscolhida].utilizador==1){
					//vejo os numeros direta e esquerda e coloco as pecas de acordo com sua nescessidade
					if(pecas[posicaoEscolhida].conteudo1==conteudoEsq){
						conteudoEsq = pecas[posicaoEscolhida].conteudo2;
						vez = 2;
						pecas[posicaoEscolhida].utilizador=5;
						printf("\n esquerda %d\n ",conteudoEsq );
						j1 -= 1;
					}else{
						if(pecas[posicaoEscolhida].conteudo2==conteudoEsq){
							conteudoEsq = pecas[posicaoEscolhida].conteudo1;
							vez = 2;
							pecas[posicaoEscolhida].utilizador=5;
							printf("\n esquerda %d\n ",conteudoEsq );
							j1 -= 1;	
						}else{
							if(pecas[posicaoEscolhida].conteudo1==conteudoDir){
								conteudoDir = pecas[posicaoEscolhida].conteudo2;
								vez = 2;
								pecas[posicaoEscolhida].utilizador=5;
								printf("\n direita %d\n ",conteudoDir );
								j1 -= 1;
							}else{
								if(pecas[posicaoEscolhida].conteudo2==conteudoDir){
									conteudoDir = pecas[posicaoEscolhida].conteudo1;
									vez = 2;
									pecas[posicaoEscolhida].utilizador=5;
									printf("\n direita %d\n ",conteudoDir );
									j1 -= 1;	
								}
							}
						}
					}
							
				}
			
			if(vez==1){
				vez = 2;
				comprarPeca(1);
				printf("\n comprou \n " );
				j1 += 1;
			}
			
			
			
			printf("\nvez 1\n");

			system("pause");
		}
		
		
		
		
		
		if(j1==0){//fim 
			system("cls");
			printf("Ganhou");
			fim = 1;
		}
		if(j2==0){//fim 
			system("cls");
			printf("Perdeu");
			fim = 1;
		}
	}
	//printf("saiu do while");
	
}








//-------------Do Professor:
void moveXY(int x, int y)//tenho que declarar antes de chamar
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x,y};
    SetConsoleCursorPosition(hStdout, position);
    return;
}

int desenhaPeca(int nrPeca, int nrColuna, int nrLinha)   
{
	char pUp[10] = {201,205,205,205,205,205,187};
	char pCenterA[10] = {186,32,32,32,32,32,186};
	char pCenterB[10] = {186,32,32,32,32,32,186};
	char pCenterC[10] = {186,32,32,32,32,32,186};
	char pCenterD[10] = {186,32,32,32,32,32,186};
	char pCenterE[10] = {186,32,32,32,32,32,186};
	char pCenterF[10] = {186,32,32,32,32,32,186};
	char pDown[10] = {200,205,205,205,205,205,188};
	char pDiv[10] = {204,205,205,205,205,205,185};

	if(pecas[nrPeca].conteudo1 == 6)
	{
		pCenterA[2] = 254;
		pCenterB[2] = 254;
		pCenterC[2] = 254;	
		pCenterA[4] = 254;
		pCenterB[4] = 254;
		pCenterC[4] = 254;	
	}else if(pecas[nrPeca].conteudo1 == 5){
		pCenterA[2] = 254;
		pCenterB[3] = 254;
		pCenterC[2] = 254;	
		pCenterA[4] = 254;
		pCenterC[4] = 254;		
	}else if(pecas[nrPeca].conteudo1 == 4){
		pCenterA[2] = 254;
		pCenterC[2] = 254;	
		pCenterA[4] = 254;
		pCenterC[4] = 254;		
	}else if(pecas[nrPeca].conteudo1 == 3){
		pCenterA[2] = 254;
		pCenterB[3] = 254;
		pCenterC[4] = 254;		
	}else if(pecas[nrPeca].conteudo1 == 2){
		pCenterA[2] = 254;
		pCenterC[4] = 254;		
	}else if(pecas[nrPeca].conteudo1 == 1){
		pCenterB[3] = 254;	
	}
	
	if(pecas[nrPeca].conteudo2 == 6)
	{
		pCenterD[2] = 254;
		pCenterE[2] = 254;
		pCenterF[2] = 254;	
		pCenterD[4] = 254;
		pCenterE[4] = 254;
		pCenterF[4] = 254;	
	}else if(pecas[nrPeca].conteudo2 == 5){
		pCenterD[2] = 254;
		pCenterE[3] = 254;
		pCenterF[2] = 254;	
		pCenterD[4] = 254;
		pCenterF[4] = 254;		
	}else if(pecas[nrPeca].conteudo2 == 4){
		pCenterD[2] = 254;
		pCenterF[2] = 254;	
		pCenterD[4] = 254;
		pCenterF[4] = 254;		
	}else if(pecas[nrPeca].conteudo2 == 3){
		pCenterD[2] = 254;
		pCenterE[3] = 254;
		pCenterF[4] = 254;		
	}else if(pecas[nrPeca].conteudo2 == 2){
		pCenterD[2] = 254;
		pCenterF[4] = 254;		
	}else if(pecas[nrPeca].conteudo2 == 1){
		pCenterE[3] = 254;	
	}	
	
	moveXY(nrColuna, nrLinha); 
	printf("%s", pUp);
	moveXY(nrColuna, nrLinha + 1);
	printf("%s", pCenterA);
	moveXY(nrColuna, nrLinha + 2);
	printf("%s", pCenterB);
	moveXY(nrColuna, nrLinha + 3);
	printf("%s", pCenterC);
	moveXY(nrColuna, nrLinha + 4);
	printf("%s", pDiv);
	moveXY(nrColuna, nrLinha + 5);
	printf("%s", pCenterD);
	moveXY(nrColuna, nrLinha + 6);
	printf("%s", pCenterE);
	moveXY(nrColuna, nrLinha + 7);
	printf("%s", pCenterF);
	moveXY(nrColuna, nrLinha + 8);
	printf("%s", pDown);

	printf ("\n");
}









int main(int argc, char *argv[]) {
	
	
	inicializaPecas();
	setPecasJogadores(1);
	setPecasJogadores(2);
	
	printf("J1:\n");
	printPecas(1, 1);
	//printf("J2(PC):");
	//printPecas(2, 11);
	
	
	
	printPecas(5, 21);
	
	
	jogar();
	
	
	

	

	
	
	
	return 0;
}
