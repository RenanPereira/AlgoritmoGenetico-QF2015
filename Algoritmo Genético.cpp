//MINIMIZAÇÃO DO CUSTO, DISTÂNCIA E TEMPO TOTAIS NUMA VIAGEM PLANEADA POR N CIDADES EUROPEIAS (0-14), ONDE A PRIMEIRA E ÚLTIMA CIDADES ESTÃO FIXAS UTILIZANDO O ALGORITMO GENÉTICO


//Para o problema em questão existem 15 cidades: 0-Amsterdam, 1-Athens, 2-Berlin, 3-Bern, 4-Brussels, 5-Copenhagen, 6-Edinburgh, 7-Lisbon, 8-London, 9-Luxembourg, 10-Madrid, 11-Paris, 12-Prague, 13-Rome, 14-Vienna
//A viagem deve começar em 7-Lisboa e acabar em 0-Amsterdão, mas qualquer outro ponto inicial e final funcionam apenas é necessário mudar as váriaveis N_inicial e N_final
//Para correr o código é necessário acrescentar a seguinte linha às opções do compilador: -std=gnu++11
//O número de indivíduos na população inicial e número de gerações influenciam os mínimos encontrados e o tempo de demora da convergência para um mínimo absoluto pelo que para valores pequenos destes parâmetros,
//o programa pode convergir para um mínimo local do sistema e não um mínimo absoluto, desta forma algumas tentativas, para valores diferentes de população inicial e gerações podem ser necessários para a confirmação
//de que os valores encontrados correspondem aos mínimos absolutos do sistema. Os valores população inicial=4000 e gerações= para cidade inicial=Lisboa e cidade final=Amsterdão parecem fornecer os minimos absolutos.


////////////////////////////////////////////////////
/////////////////ALGORITMO GENÉTICO/////////////////
////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;


//NÚMERO DE CIDADES//
int N=15;


//ESCOLHER CICADE INICIAL//
int N_inicial=7;


//ESCOLHER CIDADE FINAL//
int N_final=0;


//POPULAÇÃO INICIAL//
int populacao_inicial=4000;


//NÚMERO DE GERAÇÕES//
int geracao=2000;


//FUNÇÃO QUE CALCULA O CUSTO TOTAL DE UM PERCURSO ENTRE N-2 CIDADES, UMA VEZ QUE A CIDADE INICIAL E FINAL ESTÃO FIXAS (DAÍ A SUBTRACÇÃO DE DUAS CIDADES)//
double C(int cidade_inicial, int cidade_final, int* caminho){
	
	double custo=0;
	
	float matrixCost[15][15]={
        {
          0,256.83,46.36,109.38,20.9,150.67,84.29,255.56,82.33,53,148.5,103,74.85,166.82,119.6
        },
        {
            256.83,0,283.56,437.83,431.57,243.86,342.55,381.5,281.73,211.08,656.67,241.54,244.22,318.88,134.71
        },
        {
            46.36,283.56,0,89.64,86.89,92.88,143.92,316.5,88.25,127.83,315.88,91.17,32.18,112.36,66.6
        },
        {
            109.38,437.83,89.64,0,72.78,139.2,126.38,242.11,162.5,71.5,118.54,39.71,95.75,112.13,90.7
        },
        {
            20.9,431.57,86.89,72.780,73.93,90.55,160,54.67,17.92,312.4,32.67,130.14,323,87.23
        },
        {
            150.67,243.86,92.88,139.2,73.93,0,266.29,623,239.2,92.17,371,110.75,114.78,261.33,122.27
        },
        {
            84.29,342.55,143.92,126.38,90.55,266.29,0,575.8,82,201,197.67,120.22,144,176.21,161.38
        },
        {
            255.56,381.5,316.5,242.11,160,623,575.8,0,184.17,270.63,63.8,255.14,210.36,228.08,651
        },
        {
            82.33,281.73,88.25,162.5,54.67,239.2,82,184.17,0,76.86,121.71,41.4,200.67,299.83,94.85
        },
        {
            53,211.08,127.83,71.5,17.92,92.17,201,270.63,76.86,0,274.5,29.15,93.25,100,177
        },
        {
            148.5,656.67,315.88,118.54,312.4,371,197.67,63.8,121.71,274.5,0,97.54,209.73,174.92,237.91
        },
        {
            103,241.54,91.17,9.71,32.67,110.75,120.22,255.14,41.4,29.15,97.54,0,121.56,191.38,107.08
        },
        {
            74.85,244.22,32.18,95.75,130.14,114.78,144,210.36,200.67,93.25,209.73,121.56,0,152.22,34.67
        },
        {
            166.82,318.88,112.36,112.13,323,261.33,176.21,228.08,299.83,100,174.92,191.38,152.22,0,129.78
        },
        {
            119.6,134.71,66.6,90.7,87.23,122.27,161.38,651,94.85,177,237.91,107.08,34.67,129.78,0

        },
    };
	
	double soma=0;
	int a1=0;
	int a2=0;
	for(int i=1; i<=N-3; ++i){
		a1=caminho[i];
		a2=caminho[i+1];
		soma+=matrixCost[a1][a2];
	}
	int a3=0;
	int a4=0;
	a3=caminho[1];
	a4=caminho[N-2];
	custo=matrixCost[cidade_inicial][a3]+matrixCost[a4][cidade_final]+soma;
	
	return custo;	
}


//FUNÇÃO QUE CALCULA A DISTANCIA TOTAL DE UM PERCURSO ENTRE N-2 CIDADES, UMA VEZ QUE A CIDADE INICIAL E FINAL ESTÃO FIXAS (DAÍ A SUBTRACÇÃO DE DUAS CIDADES)//
double D(int cidade_inicial, int cidade_final, int* caminho){
	
	double distancia=0;
	
	float matrixDistance[15][15]
    {
        {
            0,3082,649,875,209,904,1180,2300,494,371,1782,515,973,1835,1196
        },
        {
            3082,0,2552,2627,3021,3414,3768,4578,3099,2744,3940,3140,2198,2551,1886
        },
        {
            649,2552,0,986,782,743,1727,3165,1059,767,2527,1094,354,1573,666

        },
        {
            875,2627,986,0,655,1392,1643,2179,975,429,1541,556,766,897,907
        },
        {
            209,3021,782,655,0,1035,996,2080,328,233,1562,294,911,1615,1134
        },
        {
            904,3414,743,1392,1035,0,1864,3115,1196,1106,2597,1329,1033,2352,1345
        },
        {
            1180,3768,1727,1643,996,1864,0,2879,656,1206,2372,1082,1872,2467,2098
        },
        {
            2300,4578,3165,2179,2080,3115,2879,0,2210,2165,638,1786,2945,2737,3255
        },
        {
            494,3099,1059,975,328,1196,656,2210,0,538,1704,414,1204,1799,1233
        },
        {
            371,2744,767,429,233,1106,1206,2165,538,0,1647,379,746,1400,885
        },
        {
            1782,3940,2527,1541,1562,2597,2372,638,1704,1647,0,1268,2307,2099,2617
        },
        {
            515,3140,1094,556,294,1329,1082,1786,414,379,1268,0,1094,1531,1285
        },
        {
            973,2198,354,766,911,1033,1872,2945,1204,746,2307,1094,0,1370,312
        },
        {
            1835,2551,1573,897,1615,2352,2467,2737,1799,1400,2099,1531,1370,0,1168
        },
        {
            1196,1886,666,907,1134,1345,2098,3255,1233,885,2617,1285,312,1168,0
        },
    };
	
	double soma=0;
	int a1=0;
	int a2=0;
	for(int i=1; i<=N-3; ++i){
		a1=caminho[i];
		a2=caminho[i+1];
		soma+=matrixDistance[a1][a2];
	}
	int a3=0;
	int a4=0;
	a3=caminho[1];
	a4=caminho[N-2];
	distancia=matrixDistance[cidade_inicial][a3]+matrixDistance[a4][cidade_final]+soma;
	
	return distancia;	
}


//FUNÇÃO QUE CALCULA O TEMPO TOTAL DE UM PERCURSO ENTRE N-2 CIDADES, UMA VEZ QUE A CIDADE INICIAL E FINAL ESTÃO FIXAS (DAÍ A SUBTRACÇÃO DE DUAS CIDADES)//
double T(int cidade_inicial, int cidade_final, int* caminho){
	
	double tempo=0;
	
	float matrixTime[15][15]{
    {
      0,26,6,11,1,7,10,25,5,3,21,4,9,14,11
    },
    {
        26,0,33,27,32,29,37,43,32,27,49,36,18,26,17
    },
    {
        6,33,0,8,7,8,14,38,8,7,21,10,3,18,8
    },
    {
      11,27,8,0,8,13,15,20,11,4,12,4,6,7,9
    },
    {
      1,32,7,8,0,13,10,17,3,2,12,2,10,14,9
    },
    {
        7,29,8,13,13,0,16,33,15,10,25,15,11,25,17
    },
    {
        10,37,14,15,10,16,0,24,5,12,25,14,18,23,23
    },
    {
      25,43,38,20,17,33,24,0,20,20,6,19,36,25,35
    },
    {
    5,32,8,11,3,15,5,20,0,6,19,5,10,15,13
    },
    {
     3,27,7,4,2,10,12,20,6,0,15,3,9,14,8
    },
    {
     21,49,21,12,12,25,25,6,19,15,0,13,22,27,21
    },
    {
     4,36,10,4,2,15,14,19,5,3,13,0,11,17,11
    },
    {
        9,18,3,6,10,11,18,36,10,9,22,11,0,13,2
    },
    {
      14,26,18,7,14,25,23,25,15,14,27,17,13,0,12
    },
    {
        11,17,8,9,9,17,23,35,13,8,21,11,2,12,0
    },
    };
	
	double soma=0;
	int a1=0;
	int a2=0;
	for(int i=1; i<=N-3; ++i){
		a1=caminho[i];
		a2=caminho[i+1];
		soma+=matrixTime[a1][a2];
	}
	int a3=0;
	int a4=0;
	a3=caminho[1];
	a4=caminho[N-2];
	tempo=matrixTime[cidade_inicial][a3]+matrixTime[a4][cidade_final]+soma;
	
	return tempo;	
}


int main(){


//CRIA FICHEIROS .txt ONDE SERÃO GURDADOS OS DADOS MINIMIZADOS//
FILE *f = fopen("dados_minimizados.txt", "w");
fprintf(f,"////////////////////////////////////////////////////\n/////////////////ALGORITMO GENÉTICO/////////////////\n////////////////////////////////////////////////////\n\n");
fprintf(f,"//MINIMIZAÇÃO DO CUSTO, DISTÂNCIA E TEMPO TOTAIS NUMA VIAGEM PLANEADA POR N CIDADES EUROPEIAS (0-14), ONDE A PRIMEIRA E ÚLTIMA CIDADES ESTÃO FIXAS UTILIZANDO O ALGORITMO GENÉTICO\n");
fprintf(f,"As cidades do percurso estão etiquetadas da seguinte forma:\n0-Amsterdam, 1-Athens, 2-Berlin, 3-Bern, 4-Brussels, 5-Copenhagen, 6-Edinburgh, 7-Lisbon, 8-London, 9-Luxembourg, 10-Madrid, 11-Paris, 12-Prague, 13-Rome, 14-Vienna\n\n");


//"SEMENTE" PARA FUNÇÕES ALEATÓRIAS//
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);


//CRIA NA MEMÓRIA OBJECTO COM DOIS INDICES, 1º=conjunto de cidades ("individuos"), 2º=conjunto aleatório ordenado de N-2 cidades("genes")//
double **individuo;
individuo=new double*[populacao_inicial];
for(int k=0; k<populacao_inicial; ++k){
    individuo[k]=new double[N-2];
}
	
	
//CRIA NA MEMÓRIA OBJECTO COM DOIS ÍNDICES (geração secundária=filhos), 1º=conjunto de cidades ("filhos"), 2º=conjunto aleatório ordenado de N-2 cidades("genes")//
double **filho;
filho=new double*[populacao_inicial];
for(int k=0; k<int(populacao_inicial/2); ++k){
    filho[k]=new double[N-2];
}	


//CRIA NA MEMÓRIA OBJECTO "TENSORIAL" (ambas gerações) COM DOIS INDICES,1º=conjunto de cidades ("indivíduos+filhos"), 2º=conjunto aleatório ordenado de N-2 cidades("genes")//
double **nova_populacao;
nova_populacao=new double*[int(populacao_inicial+(populacao_inicial)/2)];
for(int k=0; k<int(populacao_inicial+(populacao_inicial)/2); ++k){
    nova_populacao[k]=new double[N-2];
}
	
	
//GERAR PARA CADA INDIVIDUO DA POPULAÇÃO INICIAL CONJUNTOS ALEATORIOS ORDENADOS DE N-2 CIDADES//
for(int k=0; k<populacao_inicial; ++k){
	int aux=0;
	for(int i=1; i<=N-2; ++i){
		if(aux==N_inicial || aux ==N_final){
			++aux;			
		}
		individuo[k][i]=aux;
		++aux;
	}
	std::uniform_int_distribution<> dis(1,N-2);
	aux=0;
	int aux2=0;
	int aux3=0;
	for(int i=1; i<=N-2; ++i){
		aux=dis(generator);
		aux2=individuo[k][i];
		aux3=individuo[k][aux];
		individuo[k][i]=aux3;
		individuo[k][aux]=aux2;
		
	}
}

////////////////////////////////////////////////////////
/////////////MINIMIZAÇÃO DO CUSTO DE VIAGEM/////////////
////////////////////////////////////////////////////////
//CICLO QUE CADA ITERAÇÃO CORRESPONDE A UMA GERAÇÃO//
for(int g=0; g<=geracao; ++g){
	
	
	//CROSSOVER (REPRODUÇÃO)//
	for(int i=0; i<int(populacao_inicial/2); ++i){
		
		
		//GERAR, ALEATORIAMENTE, CASAL QUE TROCA GENES, PERMITE-SE "POLIGAMIA"//
		std::uniform_int_distribution<> dis(0,populacao_inicial-1);
		int masculino=dis(generator);
		int feminino=dis(generator);
		//CONDIÇÃO QUE PROÍBE A REPRODUÇÃO ASSEXUADA//
		if(masculino==feminino){
			while(masculino==feminino){
				masculino=dis(generator);
				feminino=dis(generator);
			}
		}
		
		
		//O "FILHO" DO CASAL ESCOLHIDO ALEATORIAMENTE ACIMA RECEBE GENES DE UM DOS "PAIS" DE FORMA ALEATÓRIA//
		std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
		int masculino_ou_feminino=dis_masc_fem(generator);
		for(int a=1; a<=N-2; ++a){	
			if(masculino_ou_feminino==0){
				filho[i][a]=individuo[masculino][a];
			}
			else{
				filho[i][a]=individuo[feminino][a];
			}		
		}
		
		
		//TROCA ALEATÓRIA DE GENES DE UM DOS PAIS COM FILHO DEPOIS DA ATRIBUIÇÃO ALEATÓRIA ANTERIOR//
		//GERAR ALEATORIAMENTE NÚMERO DE "GENES" QUE SERÃO TROCADOS//
		std::uniform_int_distribution<> dis_numero_genes(1,N-2);
		int numero_genes=dis_numero_genes(generator);
		for(int j=1; j<=numero_genes; ++j){
			//SELECCIONA ALEATORIAMENTE O GENE QUE SERÁ TROCADO//
			std::uniform_int_distribution<> dis_gene(1,N-2);
			int gene=dis_gene(generator);
			//SELECCIONA ALEATORIAMENTE SE O GENE VEM DO INDIVIDUO MASCULINO OU DO FEMININO//
			std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
			int masculino_ou_feminino=dis_masc_fem(generator);
			if(masculino_ou_feminino==0){
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[masculino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[masculino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}
			else{
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[feminino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[feminino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}	
		}
	}
	

	//MUTATION (MUTAÇÃO)//
	//ESCOLHER ALEATORIAMENTE NUMERO DE MUTAÇÕES, O SISTEMA POSSUI pop_inicial*N*3 GENES PELO QUE OCORRERÃO: MUTAÇÕES=0.1*filhos=0.1*pop_inicial*0.5//
	int numero_mutacoes=0.1*populacao_inicial*0.5;
	for(int m=0; m<numero_mutacoes; ++m){
		//ESCOLHER ALEATORIAMENTE INDIVÍDUO QUE SOFRERÁ "MUTAÇÃO"//
		std::uniform_int_distribution<> dis_individuo(0,int((populacao_inicial/2)-1));
		int individuo_mutado=dis_individuo(generator);
		//ESCOLHER GENE QUE SERÁ MUTADO (troca de genes na cadeia ordenada)//
		std::uniform_int_distribution<> dis_gene(1,N-2);
		int gene_mutado1=dis_gene(generator);
		int gene_mutado2=dis_gene(generator);
		int aux7=0;
		int aux8=0;
		//TROCA DOS GENES//
		aux7=filho[individuo_mutado][gene_mutado1];
		aux8=filho[individuo_mutado][gene_mutado2];
		filho[individuo_mutado][gene_mutado1]=aux8;
		filho[individuo_mutado][gene_mutado2]=aux7;
	}
	
	
	//UNIR NOVOS INDIVIDUOS (FILHOS) E ANTIGOS (PAIS) NUM NOVO "OBJECTO", A NOVA POPULAÇÃO//
	for(int k=0; k<int(populacao_inicial); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[k][i]=individuo[k][i];
		}
	}
	for(int k=0; k<int(populacao_inicial/2); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[populacao_inicial+k][i]=filho[k][i];
		}
	}

	
	//GUARDA NUM VECTOR OS VALORES DE CUSTO TOTAL DE CADA INDIVIDUO PARA ESTA GERAÇÃO//
	double custos[int(populacao_inicial+populacao_inicial/2-1)];
	double aux_custos[int(populacao_inicial+populacao_inicial/2-1)];
	int A[N-2];
	double aux9=0;
	for(int k=0; k<int(populacao_inicial+populacao_inicial/2); ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=nova_populacao[k][i];
		}
		aux9=C(N_inicial,N_final,A);
		custos[k]=aux9;
		aux_custos[k]=aux9;
	}
	//ORGANIZA OS ELEMENTOS DO VECTOR POR ORDEM CRESCENTE DE CUSTO TOTAL//
	sort(custos, custos + int(populacao_inicial+(populacao_inicial/2)-1) );
	
	
	//SELECÇAO NATURAL: A POPULÇÃO INICIAL ANTERIOR (pop_inicial) É SUBSTITUÍDA PELOS INDIVIDUOS COM CUSTO TOTAL MENOR, APENAS OS PERCURSOS MAIS BARATOS "SOBREVIVEM"//
	int novos_individuos[populacao_inicial];
	int contagem=populacao_inicial;
	for(int i=0; i<populacao_inicial; ++i){
		for(int j=0; j<int(populacao_inicial+populacao_inicial/2); ++j){
			if(custos[i]==aux_custos[j]){
			
				for(int a=1; a<=N-2; ++a){
					individuo[i][a]=nova_populacao[j][a];
				}
			break;
			
			}
		}
	}


	//IMPRIME O CUSTO TOTAL E PERCURSO DOS "INDIVÍDUOS" MAIS APTOS//
	for(int k=0; k<populacao_inicial; ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=individuo[k][i];
		}
		if(g==geracao){
			if(k==populacao_inicial-1){
				fprintf(f,"Percurso cujo o custo é mínimo:\n");
				fprintf(f,"%i\t",int(N_inicial));
				for(int i=1; i<=N-2; ++i){
					fprintf(f,"%i\t",int(individuo[k][i]));
				}
				fprintf(f,"%i\t",int(N_final));
				fprintf(f,"\nPopulação inicial usada no algoritmo:\t%i\nNúmero de gerações usada no algoritmo:\t%i\nCusto total do percurso acima:\t%5.10f euros\n",populacao_inicial,g,C(N_inicial,N_final,A));
			}
		}
	}
}


////////////////////////////////////////////////////////////
/////////////MINIMIZAÇÃO DA DISTÂNCIA DE VIAGEM/////////////
////////////////////////////////////////////////////////////
//CICLO QUE CADA ITERAÇÃO CORRESPONDE A UMA GERAÇÃO//
for(int g=0; g<=geracao; ++g){
	
	
	//CROSSOVER (REPRODUÇÃO)//
	for(int i=0; i<int(populacao_inicial/2); ++i){
		
		
		//GERAR, ALEATORIAMENTE, CASAL QUE TROCA GENES, PERMITE-SE "POLIGAMIA"//
		std::uniform_int_distribution<> dis(0,populacao_inicial-1);
		int masculino=dis(generator);
		int feminino=dis(generator);
		//CONDIÇÃO QUE PROÍBE A REPRODUÇÃO ASSEXUADA//
		if(masculino==feminino){
			while(masculino==feminino){
				masculino=dis(generator);
				feminino=dis(generator);
			}
		}
		
		
		//O "FILHO" DO CASAL ESCOLHIDO ALEATORIAMENTE ACIMA RECEBE GENES DE UM DOS "PAIS" DE FORMA ALEATÓRIA//
		std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
		int masculino_ou_feminino=dis_masc_fem(generator);
		for(int a=1; a<=N-2; ++a){	
			if(masculino_ou_feminino==0){
				filho[i][a]=individuo[masculino][a];
			}
			else{
				filho[i][a]=individuo[feminino][a];
			}		
		}
		
		
		//TROCA ALEATÓRIA DE GENES DE UM DOS PAIS COM FILHO DEPOIS DA ATRIBUIÇÃO ALEATÓRIA ANTERIOR//
		//GERAR ALEATORIAMENTE NÚMERO DE "GENES" QUE SERÃO TROCADOS//
		std::uniform_int_distribution<> dis_numero_genes(1,N-2);
		int numero_genes=dis_numero_genes(generator);
		for(int j=1; j<=numero_genes; ++j){
			//SELECCIONA ALEATORIAMENTE O GENE QUE SERÁ TROCADO//
			std::uniform_int_distribution<> dis_gene(1,N-2);
			int gene=dis_gene(generator);
			//SELECCIONA ALEATORIAMENTE SE O GENE VEM DO INDIVIDUO MASCULINO OU DO FEMININO//
			std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
			int masculino_ou_feminino=dis_masc_fem(generator);
			if(masculino_ou_feminino==0){
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[masculino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[masculino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}
			else{
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[feminino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[feminino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}	
		}
	}
	

	//MUTATION (MUTAÇÃO)//
	//ESCOLHER ALEATORIAMENTE NUMERO DE MUTAÇÕES, O SISTEMA POSSUI pop_inicial*N*3 GENES PELO QUE OCORRERÃO: MUTAÇÕES=0.1*filhos=0.1*pop_inicial*0.5//
	int numero_mutacoes=0.1*populacao_inicial*0.5;
	for(int m=0; m<numero_mutacoes; ++m){
		//ESCOLHER ALEATORIAMENTE INDIVÍDUO QUE SOFRERÁ "MUTAÇÃO"//
		std::uniform_int_distribution<> dis_individuo(0,int((populacao_inicial/2)-1));
		int individuo_mutado=dis_individuo(generator);
		//ESCOLHER GENE QUE SERÁ MUTADO (troca de genes na cadeia ordenada)//
		std::uniform_int_distribution<> dis_gene(1,N-2);
		int gene_mutado1=dis_gene(generator);
		int gene_mutado2=dis_gene(generator);
		int aux7=0;
		int aux8=0;
		//TROCA DOS GENES//
		aux7=filho[individuo_mutado][gene_mutado1];
		aux8=filho[individuo_mutado][gene_mutado2];
		filho[individuo_mutado][gene_mutado1]=aux8;
		filho[individuo_mutado][gene_mutado2]=aux7;
	}
	
	
	//UNIR NOVOS INDIVIDUOS (FILHOS) E ANTIGOS (PAIS) NUM NOVO "OBJECTO", A NOVA POPULAÇÃO//
	for(int k=0; k<int(populacao_inicial); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[k][i]=individuo[k][i];
		}
	}
	for(int k=0; k<int(populacao_inicial/2); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[populacao_inicial+k][i]=filho[k][i];
		}
	}

	
	//GUARDA NUM VECTOR OS VALORES DA DISTANCIA TOTAL DE CADA INDIVIDUO PARA ESTA GERAÇÃO//
	double distancias[int(populacao_inicial+populacao_inicial/2-1)];
	double aux_distancias[int(populacao_inicial+populacao_inicial/2-1)];
	int A[N-2];
	double aux9=0;
	for(int k=0; k<int(populacao_inicial+populacao_inicial/2); ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=nova_populacao[k][i];
		}
		aux9=D(N_inicial,N_final,A);
		distancias[k]=aux9;
		aux_distancias[k]=aux9;
	}
	//ORGANIZA OS ELEMENTOS DO VECTOR POR ORDEM CRESCENTE DE DISTANCIA TOTAL//
	sort(distancias, distancias + int(populacao_inicial+(populacao_inicial/2)-1) );
	
	
	//SELECÇAO NATURAL: A POPULÇÃO INICIAL ANTERIOR (pop_inicial) É SUBSTITUÍDA PELOS INDIVIDUOS COM DISTANCIA TOTAL MENOR, APENAS OS PERCURSOS MAIS CURTOS "SOBREVIVEM"//
	int novos_individuos[populacao_inicial];
	int contagem=populacao_inicial;
	for(int i=0; i<populacao_inicial; ++i){
		for(int j=0; j<int(populacao_inicial+populacao_inicial/2); ++j){
			if(distancias[i]==aux_distancias[j]){
			
				for(int a=1; a<=N-2; ++a){
					individuo[i][a]=nova_populacao[j][a];
				}
			break;
			
			}
		}
	}


	//IMPRIME A DISTÂNCIA TOTAL E PERCURSO DOS "INDIVÍDUOS" MAIS APTOS//
	for(int k=0; k<populacao_inicial; ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=individuo[k][i];
		}
		if(g==geracao){
			if(k==populacao_inicial-1){
				fprintf(f,"\nPercurso cujo a distância é mínima:\n");
				fprintf(f,"%i\t",int(N_inicial));
				for(int i=1; i<=N-2; ++i){
					fprintf(f,"%i\t",int(individuo[k][i]));
				}
				fprintf(f,"%i\t",int(N_final));
				fprintf(f,"\nPopulação inicial usada no algoritmo:\t%i\nNúmero de gerações usada no algoritmo:\t%i\nDistância total do percurso acima:\t%5.10f Km\n",populacao_inicial,g,D(N_inicial,N_final,A));
			}
		}
	}
}


////////////////////////////////////////////////////////
/////////////MINIMIZAÇÃO DO TEMPO DE VIAGEM/////////////
////////////////////////////////////////////////////////
//CICLO QUE CADA ITERAÇÃO CORRESPONDE A UMA GERAÇÃO//
for(int g=0; g<=geracao; ++g){
	
	
	//CROSSOVER (REPRODUÇÃO)//
	for(int i=0; i<int(populacao_inicial/2); ++i){
		
		
		//GERAR, ALEATORIAMENTE, CASAL QUE TROCA GENES, PERMITE-SE "POLIGAMIA"//
		std::uniform_int_distribution<> dis(0,populacao_inicial-1);
		int masculino=dis(generator);
		int feminino=dis(generator);
		//CONDIÇÃO QUE PROÍBE A REPRODUÇÃO ASSEXUADA//
		if(masculino==feminino){
			while(masculino==feminino){
				masculino=dis(generator);
				feminino=dis(generator);
			}
		}
		
		
		//O "FILHO" DO CASAL ESCOLHIDO ALEATORIAMENTE ACIMA RECEBE GENES DE UM DOS "PAIS" DE FORMA ALEATÓRIA//
		std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
		int masculino_ou_feminino=dis_masc_fem(generator);
		for(int a=1; a<=N-2; ++a){	
			if(masculino_ou_feminino==0){
				filho[i][a]=individuo[masculino][a];
			}
			else{
				filho[i][a]=individuo[feminino][a];
			}		
		}
		
		
		//TROCA ALEATÓRIA DE GENES DE UM DOS PAIS COM FILHO DEPOIS DA ATRIBUIÇÃO ALEATÓRIA ANTERIOR//
		//GERAR ALEATORIAMENTE NÚMERO DE "GENES" QUE SERÃO TROCADOS//
		std::uniform_int_distribution<> dis_numero_genes(1,N-2);
		int numero_genes=dis_numero_genes(generator);
		for(int j=1; j<=numero_genes; ++j){
			//SELECCIONA ALEATORIAMENTE O GENE QUE SERÁ TROCADO//
			std::uniform_int_distribution<> dis_gene(1,N-2);
			int gene=dis_gene(generator);
			//SELECCIONA ALEATORIAMENTE SE O GENE VEM DO INDIVIDUO MASCULINO OU DO FEMININO//
			std::uniform_int_distribution<> dis_masc_fem(0,1);//0=masculino;1=feminino//
			int masculino_ou_feminino=dis_masc_fem(generator);
			if(masculino_ou_feminino==0){
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[masculino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[masculino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}
			else{
				int aux4=0;
				int aux5=0;
				int aux6=0;
				aux4=individuo[feminino][gene];
				aux6=filho[i][gene];
				for(int k=1; k<=N-2; ++k){
					if(filho[i][k]==individuo[feminino][gene]){
						aux5=k;
					}
				}
				filho[i][gene]=aux4;
				filho[i][aux5]=aux6;
			}	
		}
	}
	

	//MUTATION (MUTAÇÃO)//
	//ESCOLHER ALEATORIAMENTE NUMERO DE MUTAÇÕES, O SISTEMA POSSUI pop_inicial*N*3 GENES PELO QUE OCORRERÃO: MUTAÇÕES=0.1*filhos=0.1*pop_inicial*0.5//
	int numero_mutacoes=0.1*populacao_inicial*0.5;
	for(int m=0; m<numero_mutacoes; ++m){
		//ESCOLHER ALEATORIAMENTE INDIVÍDUO QUE SOFRERÁ "MUTAÇÃO"//
		std::uniform_int_distribution<> dis_individuo(0,int((populacao_inicial/2)-1));
		int individuo_mutado=dis_individuo(generator);
		//ESCOLHER GENE QUE SERÁ MUTADO (troca de genes na cadeia ordenada)//
		std::uniform_int_distribution<> dis_gene(1,N-2);
		int gene_mutado1=dis_gene(generator);
		int gene_mutado2=dis_gene(generator);
		int aux7=0;
		int aux8=0;
		//TROCA DOS GENES//
		aux7=filho[individuo_mutado][gene_mutado1];
		aux8=filho[individuo_mutado][gene_mutado2];
		filho[individuo_mutado][gene_mutado1]=aux8;
		filho[individuo_mutado][gene_mutado2]=aux7;
	}
	
	
	//UNIR NOVOS INDIVIDUOS (FILHOS) E ANTIGOS (PAIS) NUM NOVO "OBJECTO", A NOVA POPULAÇÃO//
	for(int k=0; k<int(populacao_inicial); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[k][i]=individuo[k][i];
		}
	}
	for(int k=0; k<int(populacao_inicial/2); ++k){
		for(int i=0; i<N; ++i){
				nova_populacao[populacao_inicial+k][i]=filho[k][i];
		}
	}

	
	//GUARDA NUM VECTOR OS VALORES DE TEMPO TOTAL DE CADA INDIVIDUO PARA ESTA GERAÇÃO//
	double tempos[int(populacao_inicial+populacao_inicial/2-1)];
	double aux_tempos[int(populacao_inicial+populacao_inicial/2-1)];
	int A[N-2];
	double aux9=0;
	for(int k=0; k<int(populacao_inicial+populacao_inicial/2); ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=nova_populacao[k][i];
		}
		aux9=T(N_inicial,N_final,A);
		tempos[k]=aux9;
		aux_tempos[k]=aux9;
	}
	//ORGANIZA OS ELEMENTOS DO VECTOR POR ORDEM CRESCENTE DO TEMPO DE VIAGEM TOTAL//
	sort(tempos, tempos + int(populacao_inicial+(populacao_inicial/2)-1) );
	
	
	//SELECÇAO NATURAL: A POPULÇÃO INICIAL ANTERIOR (pop_inicial) É SUBSTITUÍDA PELOS INDIVIDUOS COM TEMPO TOTAL MENOR, APENAS OS PERCURSOS MAIS RÁPIDOS "SOBREVIVEM"//
	int novos_individuos[populacao_inicial];
	int contagem=populacao_inicial;
	for(int i=0; i<populacao_inicial; ++i){
		for(int j=0; j<int(populacao_inicial+populacao_inicial/2); ++j){
			if(tempos[i]==aux_tempos[j]){
			
				for(int a=1; a<=N-2; ++a){
					individuo[i][a]=nova_populacao[j][a];
				}
			break;
			
			}
		}
	}


	//IMPRIME O TEMPO TOTAL E PERCURSO DOS "INDIVÍDUOS" MAIS APTOS//
	for(int k=0; k<populacao_inicial; ++k){
		for(int i=1; i<=N-2; ++i){
			A[i]=individuo[k][i];
		}
		if(g==geracao){
			if(k==populacao_inicial-1){
				fprintf(f,"\nPercurso cujo o tempo é mínimo:\n");
				fprintf(f,"%i\t",int(N_inicial));
				for(int i=1; i<=N-2; ++i){
					fprintf(f,"%i\t",int(individuo[k][i]));
				}
				fprintf(f,"%i\t",int(N_final));
				fprintf(f,"\nPopulação inicial usada no algoritmo:\t%i\nNúmero de gerações usada no algoritmo:\t%i\nTempo total do percurso acima:\t%5.10f horas\n",populacao_inicial,g,T(N_inicial,N_final,A));
			}
		}
	}
}


}

