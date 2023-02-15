#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


#define ENTER 13
#define TAB 9
#define BCKSPC 8

char user_usuario_logado[30];
char nome_usuario_logado[30];
char tipo_usuario[5];



struct user{
	char tipo[5];
	char nome[40];
	char user[30];
	char senha[15];
};

struct data{
	char horas[5];
	char minutos[5];
	char dia[5];
	char mes[5];
	char ano[5];
};

struct estoque{
	char id[10];
	char nome[50];
	char valor_compra[10];  
	char valor_venda[10];
	char quantidade[5];
	};

struct relatorios{
	char documento[20];
	char valor[10];
	char total[10];  
};

struct clientes{
	char documento[20];
	char nome[50];
	char email[30];  
	char telefone[15];
};

struct fornecedores{
	char cnpj[20];
	char nome[50];
	char email[30];  
	char telefone[15];
};

//LIMPA A TELA
void clrscr(){
    system("@cls||clear");
}

//DESENHA UM CABEÇALHO SEMPRE QUE ABRIR UMA NOVA TELA
void desenhar_cabecalho(){
    printf("SISTEMA DE GESTÃO DE VENDAS E ESTOQUE\n");
    if (nome_usuario_logado[0] != '\0') {
    	printf("Olá, %s.\n", nome_usuario_logado);
	}
	printf("_____________________________________________\n\n");
}

//FORMATAR O INPUT DO USUÁRIO PARA STRING
char input_str(char input[50]){
	fflush(stdin);
	fgets(input, 50, stdin);
	input[strlen(input) - 1] = 0;

}

//FORMATAR O INPUT DO USUÁRIO PARA INT
int input_int() {
	char input_usuario[15];
	int numero_valido;
	
	while(1) {		
		fgets(input_usuario, 15, stdin);

		if(sscanf(input_usuario, "%d", &numero_valido) != 1) {
			printf("Opção Invalida! Digite outra opção: ");	
		}else{
			break;
		}
	}
	return numero_valido;
}

void mask(char senha[15]){
	char b;
	int j;
	while(1)
	{
		b=getch();
	
	if (b==ENTER)
	{
		senha[j]= '\0';
		break;
	}
	else if(b==TAB){
		continue;
	}
	else if(b==BCKSPC)
	{
		if(j>0)
		{
			j--;
			printf("\b \b");
		}
	}
	else{
	
		senha[j]=b;
		j++;
		printf("*");
	  }
   }
}



//IMPRIME TODOS OS PRODUTOS DISPONÍVEIS NO ESTOQUE
void print_estoque(){
	FILE *arquivo_estoque;	
	struct estoque produtos;
	char buffer[250];
	
	arquivo_estoque = fopen("estoque.txt", "a+");
	if (arquivo_estoque == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
		}
	printf("Produtos cadastrados: \n");
	while(fgets(buffer, 250, arquivo_estoque) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		printf("\nID: %s\t Nome: %s\nValor de venda: %s\nQuant. Disponível: %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		}
		
	fclose(arquivo_estoque);
	printf("_____________________________________________\n\n");
}

//IMPRIME TODOS OS CLIENTES CADASTRADOS
void print_clientes(){
	FILE *arquivo_clientes;	
	struct clientes cliente;
	char buffer[250];
	
	arquivo_clientes = fopen("clientes.txt", "a+");
	if (arquivo_clientes == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
		}
	printf("Clientes cadastrados: \n");
	while(fgets(buffer, 250, arquivo_clientes) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		printf("\nCPF: %s\t Nome: %s\nTelefone: %s\t Email: %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		}
		
	fclose(arquivo_clientes);
	printf("_____________________________________________\n\n");
}

//IMPRIME TODOS OS FORNECEDORES CADASTRADOS
void print_fornecedores(){
	FILE *arquivo_fornecedores;
	struct fornecedores fornecedor;
	char buffer[250];
	
	arquivo_fornecedores = fopen("fornecedores.txt", "a+");
	if (arquivo_fornecedores == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	printf("Fornecedores cadastrados: \n");
	while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		printf("\nCNPJ: %s\t Nome: %s\nTelefone: %s\t Email: %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		}
	fclose(arquivo_fornecedores);
	printf("_____________________________________________\n\n");
}

//REALIZA LOGIN
void tela_login(){
	clrscr();
	desenhar_cabecalho();
	printf("LOGIN\n");
	printf("_____\n\n");
	
    FILE *arquivo_login;       
	struct user login;
	char input_user[30], input_senha[15], buffer[250];
	
    printf("Digite o usuário de acesso: ");
    input_str(input_user);

    printf("Digite a senha: ");
    mask(input_senha);
	
	
	arquivo_login = fopen("users.txt", "a+");
	if (arquivo_login == NULL){
	    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
	    exit (1);
    };
	
	while(fgets(buffer, 250, arquivo_login) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", login.tipo, login.nome, login.user, login.senha);
		if (strcmp(input_user, login.user) == 0 && strcmp(input_senha, login.senha) == 0){
			fclose(arquivo_login);
			sscanf(login.nome, "%s", nome_usuario_logado);
			sscanf(login.user, "%s", user_usuario_logado);
			sscanf(login.tipo, "%s", tipo_usuario);
			printf("\nLogin realizado com sucesso! Bem vindo, %s.", nome_usuario_logado); 
			printf("\nPressione qualquer tecla para continuar.\n");
			getch();
			main();
		}
	}
    fclose(arquivo_login);
    printf("Usuário não encontrado! Pressione qualquer tecla para retornar ao menu inicial.\n");
    getch();
    main();
}


//CADASTRA NOVOS USUÁRIOS
void registrar_user(){
	clrscr();
	desenhar_cabecalho();
	printf("REGISTRO DE USUÁRIO\n");
	printf("___________________\n\n");
	
	void users();
	FILE *arquivo_users;
	char buffer[250], user_tipo[5], user_nome[40], user_usuario[30], user_senha[15], confirma_senha[15];
	int senha_confirmada, opcao_registrar_user = 0;
	struct user usuario;
	
	printf("1) - Administrador\n");
	printf("2) - Supervisor\n");
	printf("3) - Operador\n\n");
	printf("Escolha o nível de acesso que o usuário terá: ");
    input_str(user_tipo);
	
	printf("Digite o nome completo do usuário: ");
	input_str(user_nome);
	
    printf("Digite o usuário de acesso: ");
    input_str(user_usuario);
        

    while(!senha_confirmada){
    	printf("Digite a senha: ");
    	input_str(user_senha);
    
    	printf("Confirme a senha: ");
    	input_str(confirma_senha);
    	
    	if (user_senha[0] != '\0'){
	    	if (strcmp(user_senha, confirma_senha) == 0){
	    		senha_confirmada = 1;
			}
			else{
				printf("\nSenhas não conferem!\n\n");
			}	
		}
    	else{
    		printf("\nSenha vazia.\n\n");
		}
	}
    
    printf("\nTem certeza que deseja cadastrar este usuário?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_registrar_user = input_int();
	
	do{
		switch(opcao_registrar_user){
			case 1:
				arquivo_users = fopen("users.txt", "a+");
				if (arquivo_users == NULL)
			    {
			        printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			        exit (1);
			    }
			    while(fgets(buffer, 250, arquivo_users) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", usuario.tipo, usuario.user, usuario.user, usuario.senha);
					if (strcmp(user_nome, usuario.user) == 0){
						fclose(arquivo_users);
						printf("\nUsuário já cadastrado no sistema! Pressione qualquer tecla para retornar ao menu de usuários.\n\n");
						getch();
			    		users();
					}
				}
				fprintf(arquivo_users, "%s\t %s\t %s\t %s\n", user_tipo, user_nome, user_usuario, user_senha);
				fclose(arquivo_users);
				printf("\nUsuário cadastrado com sucesso! Pressione qualquer tecla para retornar ao menu de usuários.\n");
				getch();
			    users();
		    break;
		    
		    case 2:
		    	printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao menu de usuários.\n");
				getch();
				users();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_registrar_user = input_int();
			break; 
		}
	}while(opcao_registrar_user != 0);
}

//SALVA O REGISTRO DE COMPRA DE PRODUTO PELA EMPRESA COM DADOS COMO HORAS, QUANTIDADE E VALOR
void compras(char *id_produto, char *documento, float valor, int quantidade){
	int horas, minutos, dia, mes, ano;
	struct tm *data_hora_atual;  
	time_t segundos;
	time(&segundos);   
	data_hora_atual = localtime(&segundos);
	horas = data_hora_atual->tm_hour;
	minutos = data_hora_atual->tm_min;
	dia = data_hora_atual->tm_mday;
	mes = data_hora_atual->tm_mon +1;
	ano = data_hora_atual->tm_year+1900;
	
	struct data data;
	sprintf(data.horas, "%02d", horas);
	sprintf(data.minutos, "%02d", minutos);
	sprintf(data.dia, "%02d", dia);
	sprintf(data.mes, "%02d", mes);
	sprintf(data.ano, "%d", ano);
	
	FILE *arquivo_compras;
	float total;
	
	
	total = valor * quantidade;
	
	arquivo_compras = fopen("compras.txt", "a+");
	if (arquivo_compras == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
	}
	fprintf(arquivo_compras, "%s\t %s\t %s\t %.2f\t %d\t %.2f\t %s\t %s\t %s\t %s\t %s\n", user_usuario_logado, id_produto, documento, valor, quantidade, total, data.dia, data.mes, data.ano, data.horas, data.minutos);
	fclose(arquivo_compras);
}

//SALVA O REGISTRO DE VENDA DE PRODUTO PELA EMPRESA COM DADOS COMO HORAS, QUANTIDADE E VALOR
void vendas(char *id_produto, char *documento, float valor, int quantidade){
	int horas, minutos, dia, mes, ano;
	struct tm *data_hora_atual;  
	time_t segundos;
	time(&segundos);   
	data_hora_atual = localtime(&segundos);
	horas = data_hora_atual->tm_hour;
	minutos = data_hora_atual->tm_min;
	dia = data_hora_atual->tm_mday;
	mes = data_hora_atual->tm_mon +1;
	ano = data_hora_atual->tm_year+1900;
	
	struct data data;
	sprintf(data.horas, "%02d", horas);
	sprintf(data.minutos, "%02d", minutos);
	sprintf(data.dia, "%02d", dia);
	sprintf(data.mes, "%02d", mes);
	sprintf(data.ano, "%d", ano);
	
	FILE *arquivo_vendas;
	float total;
	
	
	quantidade = quantidade * -1;
	total = valor * quantidade;
	
	
	arquivo_vendas = fopen("vendas.txt", "a+");
	if (arquivo_vendas == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	
	fprintf(arquivo_vendas, "%s\t %s\t %s\t %.2f\t %d\t %.2f\t %s\t %s\t %s\t %s\t %s\n", user_usuario_logado, id_produto, documento, valor, quantidade, total, data.dia, data.mes, data.ano, data.horas, data.minutos);
	fclose(arquivo_vendas);
}


//REGISTRA A ENTRADA DE PRODUTOS NO ESTOQUE, ALTERANDO A QUANTIDADE SALVA NO ARQUIVO
void adicionar_produto_estoque(char id[10], char documento[20], int quant, float valor_gasto){
	FILE *arquivo_estoque, *arquivo_estoque_backup;
	struct estoque produtos;
	char buffer[250];
	int nova_quant, valor;
	
	arquivo_estoque = fopen("estoque.txt", "a+");
	if (arquivo_estoque == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	arquivo_estoque_backup = fopen("estoque_backup.txt", "w");
	if (arquivo_estoque_backup == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_estoque) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		if (strcmp(produtos.id, id) == 0){
			nova_quant = atoi(produtos.quantidade);
			nova_quant = nova_quant + quant;
			sprintf(produtos.quantidade, "%d", nova_quant);
			
			fprintf(arquivo_estoque_backup, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
			compras(id, documento, valor_gasto, quant);
		}
		else{
			fprintf(arquivo_estoque_backup, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		}
	}
	fclose(arquivo_estoque);
	fclose(arquivo_estoque_backup);
	
	
	
	arquivo_estoque_backup = fopen("estoque_backup.txt", "a+");
	if (arquivo_estoque_backup == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	arquivo_estoque = fopen("estoque.txt", "w");
	if (arquivo_estoque == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_estoque_backup) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
			fprintf(arquivo_estoque, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
	}
	fclose(arquivo_estoque);
	fclose(arquivo_estoque_backup);
	remove("estoque_backup.txt");
}

//REGISTRA A SAÍDA DO PRODUTO DO ESTOQUE QUANDO UMA VENDA É REALIZADA, ALTERANDO A QUANTIDADE DO PRODUTO NO ARQUIVO
void remover_produto_estoque(char id[10], char documento[20], int quant){
	
	FILE *arquivo_estoque, *arquivo_estoque_backup;
	struct estoque produtos;
	char buffer[250];
	int nova_quant, valor;
	
	arquivo_estoque = fopen("estoque.txt", "a+");
	if (arquivo_estoque == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	arquivo_estoque_backup = fopen("estoque_backup.txt", "w");
	if (arquivo_estoque_backup == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_estoque) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		if (strcmp(produtos.id, id) == 0){
			nova_quant = atoi(produtos.quantidade);
			nova_quant = nova_quant + quant;
			sprintf(produtos.quantidade, "%d", nova_quant);
			
			fprintf(arquivo_estoque_backup, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
			valor = atof(produtos.valor_venda);
			vendas(id, documento, valor, quant);
		}
		else{
			fprintf(arquivo_estoque_backup, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		}
	}
	fclose(arquivo_estoque);
	fclose(arquivo_estoque_backup);
	
	
	
	arquivo_estoque_backup = fopen("estoque_backup.txt", "a+");
	if (arquivo_estoque_backup == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	arquivo_estoque = fopen("estoque.txt", "w");
	if (arquivo_estoque == NULL)
		{
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_estoque_backup) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
			fprintf(arquivo_estoque, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
	}
	fclose(arquivo_estoque);
	fclose(arquivo_estoque_backup);
	remove("estoque_backup.txt");
}


//BUSCA POR COMPRAS E VENDAS REALIZADAS EM UM DIA ESPECIFICO 
void relatorios_dia(int escolha){
	clrscr();
	desenhar_cabecalho();

	
	float total, soma_total;
	char buffer[250], user_registro[30], dia_input[5], mes_input[5], ano_input[5];
	FILE *arquivo_relatorio;
	void venda_produtos();	
	void estoque();
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	

	
	if(escolha == 1){
		arquivo_relatorio = fopen("compras.txt", "a+");
		printf("HISTÓRICO DE COMPRA DE PRODUTOS POR DIA\n");
		printf("_______________________________________\n\n");
	}
	if(escolha == 2){
		arquivo_relatorio = fopen("vendas.txt", "a+");
		printf("HISTÓRICO DE VENDA DE PRODUTOS POR DIA\n");
		printf("______________________________________\n\n");
	}
	if (arquivo_relatorio == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		
	printf("Digite o dia (Ex.: 01, 02 etc.): ");
	input_str(dia_input);
	
	printf("Digite o mês (Ex.: 01, 02 etc.): ");
	input_str(mes_input);
	
	printf("Digite o ano (Ex.: 2020, 2021 etc.): ");
	input_str(ano_input);
	
	while(fgets(buffer, 250, arquivo_relatorio) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos); 
		if(strcmp(dia_input, data.dia) == 0 && strcmp(mes_input, data.mes) == 0 && strcmp(ano_input, data.ano) == 0){
			printf("\nID do produto: %s\nCPF/CNPJ: %s\nValor Un.: R$%s\t Quantidade: %s\t Total: R$%s\nData: %s/%s/%s às %s:%s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
			total = atof(relatorio.total);
			soma_total += total;
		}
	}
	fclose(arquivo_relatorio);
	printf("_____________________________________________\n\n");
	printf("Total: R$%.2f\n", soma_total);
	printf("_____________________________________________\n\n");
	printf("Pressione qualquer tecla para continuar.\n");
	
	getch();
	if(escolha == 1){
		estoque();
	}
	if(escolha == 2){
		venda_produtos();
	}
}

//IMPRIME NA TELA TODAS AS VENDAS SALVAS NO ARQUIVO
void todas_vendas(){
	clrscr();
	desenhar_cabecalho();
	printf("TODAS AS VENDAS / SAÍDA DE PRODUTOS\n");
	printf("___________________________________\n\n");
	
	void venda_produtos();
	float total, soma_total;
	char buffer[250], user_registro[30];
	FILE *arquivo_compras;	
	FILE *arquivo_vendas;
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	printf("Todas as vendas: \n");
	arquivo_vendas = fopen("vendas.txt", "a+");
	if (arquivo_vendas == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
	}
	while(fgets(buffer, 250, arquivo_vendas) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos); 
		printf("\nID do produto: %s\nDocumento do cliente: %s\nValor Un.: R$%s\t Quantidade: %s\t Total: R$%s\nData: %s/%s/%s às %s:%s\nRegistrado por: %s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos, user_registro);
		total = atof(relatorio.total);
		soma_total += total;
	}
	fclose(arquivo_vendas);
	
	printf("_____________________________________________\n\n");
	printf("Total: R$%.2f\n", soma_total);
	printf("_____________________________________________\n\n");
	printf("Pressione qualquer tecla para retornar ao menu de vendas.\n");
	getch();
	venda_produtos();
}


//REGISTRA NOVAS VENDAS
void registrar_venda(){
	clrscr();
	desenhar_cabecalho();
	
	char buffer[250], id_busca[10], documento[20];;
	int input_quant, nova_quant, quant_convert_int, opcao_registro_venda;
	struct estoque produtos;
	FILE *arquivo_estoque;  
	FILE *arquivo_clientes;	
	struct clientes cliente;
	
	void venda_produtos();
	
	printf("REGISTRAR NOVA VENDA: \n");
	printf("_____________________\n\n");
	
	print_clientes();
	
	printf("Digite o documento do cliente (CPF/CNPJ): ");
	input_str(documento);
	
	arquivo_clientes = fopen("clientes.txt", "a+");
	if (arquivo_clientes == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
		}
	while(fgets(buffer, 250, arquivo_clientes) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		if(strcmp(documento, cliente.documento) == 0){
			
			fclose(arquivo_clientes);
			printf("_______________________________________\n\n");
			arquivo_estoque = fopen("estoque.txt", "a+");
			if (arquivo_estoque == NULL){
				printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				exit (1);
			}
			printf("Produtos disponíveis: \n");
			while(fgets(buffer, 250, arquivo_estoque) != NULL){
				sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
				if (produtos.quantidade[0] != '0'){
					printf("\nID: %s\t Nome: %s\nValor de venda: %s\nQuant. Disponível: %s\n\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
				}
			}
			fclose(arquivo_estoque);
			printf("_______________________________________\n\n");
		    printf("Digite o ID do produto: ");
			input_str(id_busca);
						
			printf("Digite a quantidade: ");
			input_quant = input_int();
			
						
			printf("\nAs informações acima estão corretas?\n");
			printf("1) SIM / 2) NÃO\n");
			printf("Digite: ");
			opcao_registro_venda = input_int();
			
			arquivo_estoque = fopen("estoque.txt", "r");
			if (arquivo_estoque == NULL){
				printf("Erro ao abrir bancos de dados. Finalizando aplicação.\n");
				exit(1);
				}
			
			do{
				switch(opcao_registro_venda){
				case 1:
					while(fgets(buffer, 250, arquivo_estoque) != NULL){
						sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
						if (strcmp(id_busca, produtos.id) == 0){
							quant_convert_int = atoi(produtos.quantidade);
							nova_quant = quant_convert_int - input_quant;
						if (nova_quant < 0){
							printf("\nQuantidade de produtos indisponíveis. Pressione qualquer tecla para retornar ao menu.\n");
							fclose(arquivo_estoque);
							getch();
							venda_produtos();
							}
						else{
							input_quant = input_quant * -1;
							remover_produto_estoque(id_busca, documento, input_quant);
							printf("\nVenda registrada com sucesso. Pressione qualquer tecla para retornar ao menu.\n");
							fclose(arquivo_estoque);
							getch();
							venda_produtos();
							}
						}
					}
					fclose(arquivo_estoque);
					printf("Produto não encontrado.\n\n");
					getch();
					venda_produtos();
				break;
				
				case 2:
					printf("Operação cancelada com sucesso. Pressione qualquer tecla para continuar.\n");
					getch();
					venda_produtos();
				break;	
				
				default:
					printf("Opção Invalida! Digite outra opção: ");
					opcao_registro_venda = input_int();
				break;   
				}
			}while(opcao_registro_venda != 0);
		}
	}
	fclose(arquivo_clientes);
	printf("Cliente ainda não cadastrado no sistema. Pressione qualquer tecla para retornar ao menu de vendas.\n");
	getch();
	venda_produtos();
}

//MENU DE VENDAS
void venda_produtos(){
	clrscr();
	desenhar_cabecalho();
	printf("VENDA DE PRODUTOS\n");
	printf("_________________\n\n");
	
	int opcao_produtos = 0, escolha = 0;
	char buffer[250];
	struct estoque produtos;
	FILE *arquivo_estoque;  
	
	arquivo_estoque = fopen("estoque.txt", "a+");
	if (arquivo_estoque == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	printf("Produtos disponíveis: \n");
	while(fgets(buffer, 250, arquivo_estoque) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		if (produtos.quantidade[0] != '0'){
			printf("\nID: %s\t Nome: %s\nValor de venda: %s\nQuant. Disponível: %s\n\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		}
		}
	fclose(arquivo_estoque);
	printf("_______________________________________\n\n");
	
	printf("OPÇÕES: \n\n");
	printf("1) - NOVA VENDA\n");
	printf("2) - HISTÓRICO DE VENDAS / TODAS AS VENDAS\n");
	printf("3) - HISTÓRICO DE VENDAS / DIA/MÊS/ANO\n");
    printf("4) - RETORNAR AO MENU PRINCIPAL\n\n");    
    printf("Digite a opção desejada: ");
    opcao_produtos = input_int();
    do{ 
	switch (opcao_produtos){
		case 1:
			registrar_venda();
		break;
		
		case 2:
			todas_vendas();
		break;
		
		case 3:
			escolha = 2;
			relatorios_dia(escolha);
		break;
				
		case 4:
			main();
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao_produtos = input_int();
		break;    
		}
	}while (opcao_produtos != 0);       
}




//REGISTRA COMPRA DE PRODUTOS PELA EMPRESA QUE JÁ ESTÃO CADASTRADOS NO ESTOQUE
void adicionar_produto_cadastrado(){
	clrscr();
	desenhar_cabecalho();
	
	char buffer[250], id_busca[10], documento[20];
	int quantidade_adicionar, opcao_registro_estoque2;
	float valor_gasto;
	struct estoque produtos;
	FILE *arquivo_estoque; 
	FILE *arquivo_fornecedores;
	struct fornecedores fornecedor;
	
	void estoque();
	printf("ADICIONAR PRODUTOS: \n");
	printf("___________________\n\n");
	
	print_fornecedores();
	
	printf("Digite o CNPJ do fornecedor: ");
	input_str(documento);
	arquivo_fornecedores = fopen("fornecedores.txt", "a+");
	if (arquivo_estoque == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		if(strcmp(documento, fornecedor.cnpj) == 0){
			printf("_____________________________________________\n\n");
			print_estoque();

			printf("Digite o ID do produto: ");
			input_str(id_busca);
			
			printf("Digite a quantidade: ");
			quantidade_adicionar = input_int();
			
			printf("Digite o valor gasto por unidade do produto: ");
			input_str(produtos.valor_compra);
			valor_gasto = atof(produtos.valor_compra);
			
			
			
			printf("\nAs informações acima estão corretas?\n");
			printf("1) SIM / 2) NÃO\n");
			printf("Digite: ");
			opcao_registro_estoque2 = input_int();
			
			arquivo_estoque = fopen("estoque.txt", "r");
			if (arquivo_estoque == NULL){
				printf("Erro ao abrir bancos de dados. Finalizando aplicação.\n");
				exit(1);
			}
			
			do{
				switch(opcao_registro_estoque2){
				case 1:
					while(fgets(buffer, 250, arquivo_estoque) != NULL){
						sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
						if(strcmp(id_busca, produtos.id) == 0){
							fclose(arquivo_estoque);
							adicionar_produto_estoque(id_busca, documento, quantidade_adicionar, valor_gasto);
							printf("\nProdutos adicionados com sucesso. Pressione qualquer tecla para retornar ao menu do estoque.\n");
							getch();
							estoque();
						}
					}
					fclose(arquivo_estoque);
					printf("Produto não cadastrado no estoque. Pressione qualquer tecla para continuar.\n");
					getch();
					estoque();
				break;
				
				case 2:
					printf("Operação cancelada com sucesso. Pressione qualquer tecla para continuar.\n");
					getch();
					estoque();
				break;	
				
				default:
					printf("Opção Invalida! Digite outra opção: ");
					opcao_registro_estoque2 = input_int();
				break;   
				}
			}while(opcao_registro_estoque2 != 0);
		}
	}
	fclose(arquivo_fornecedores);
	printf("\nFornecedor não cadastrado no sistema. Pressione qualquer tecla para retornar ao menu de estoque.\n");
	getch();
	estoque();
}

//CRIA UM NOVO CADASTRO NO ESTOQUE PARA PRODUTOS COMPRADOS PELA EMPRESA
void registrar_produto_estoque(){
	clrscr();
	desenhar_cabecalho();
	
	FILE *arquivo_estoque;
	int opcao_estoque = 0, soma_id1, soma_id2;
	float valor_gasto, valor_venda;
	struct estoque produtos;
	char buffer[250], documento[20];
	int quantidade, opcao_registro_estoque;
	FILE *arquivo_fornecedores;
	struct fornecedores fornecedor;
	
	void estoque();
	
	printf("CADASTRAR NOVO PRODUTO: \n");
	printf("_______________________\n\n");
		
	print_fornecedores();
	
	printf("Digite o CNPJ do fornecedor: ");
	input_str(documento);
	
	arquivo_fornecedores = fopen("fornecedores.txt", "a+");
	if (arquivo_estoque == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		if(strcmp(documento, fornecedor.cnpj) == 0){
			fclose(arquivo_fornecedores);
			
			arquivo_estoque = fopen("estoque.txt", "a+");
			if (arquivo_estoque == NULL){
				printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				exit (1);
			}
			while(fgets(buffer, 250, arquivo_estoque) != NULL){
				sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_compra, produtos.valor_venda, produtos.quantidade);
			}
			soma_id1 = atoi(produtos.id);
			soma_id1 = soma_id1 + 1;
			sprintf(produtos.id, "%03d", soma_id1);
			
			printf("Digite o nome do produto: ");
			input_str(produtos.nome);
					
			printf("Digite o valor gasto por unidade do produto: ");
			input_str(produtos.valor_compra);
			valor_gasto = atof(produtos.valor_compra);
			sprintf(produtos.valor_compra, "%.2f", valor_gasto);
			
			printf("Digite o valor de venda por unidade do produto: ");
			input_str(produtos.valor_venda);
			valor_venda = atof(produtos.valor_venda);
			sprintf(produtos.valor_venda, "%.2f", valor_venda);
			
			printf("Digite a quantidade a ser registrada no estoque: ");
			input_str(produtos.quantidade);
			quantidade = atoi(produtos.quantidade);
			
			
			
			printf("\nAs informações acima estão corretas?\n");
			printf("1) SIM / 2) NÃO\n");
			printf("Digite: ");
			opcao_registro_estoque = input_int();
			
			do{
				switch(opcao_registro_estoque){
				case 1:
					fprintf(arquivo_estoque, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
					compras(produtos.id, documento, valor_gasto, quantidade);
					fclose(arquivo_estoque);
					printf("\nProdutos registrado no estoque com sucesso. Pressione qualquer tecla para continuar.\n");
					getch();
					estoque();
				break;
				
				case 2:
					printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para continuar.\n");
					getch();
					estoque();
				break;	
				
				default:
					printf("Opção Invalida! Digite outra opção: ");
					opcao_registro_estoque = input_int();
				break;   
				}
			}while(opcao_registro_estoque != 0);
		}
	}
	fclose(arquivo_fornecedores);
	printf("\nFornecedor não cadastrado no sistema. Pressione qualquer tecla para retornar ao menu de estoque.\n");
	getch();
	estoque();
}

//ALTERA O VALOR DE VENDA DE UM PRODUTO CADASTRADO NO ESTOQUE
void alterar_valor(){
	printf("______________________\n");
	printf("ALTERAR VALOR DE VENDA\n\n");
	
	void estoque();
	char buffer[250], id_busca[10], novo_valor[30];
	float valor;
	FILE *arquivo_estoque, *arquivo_estoque_temp;
	struct estoque produtos;
	int opcao_alt_valor_estoque = 0;
	
	printf("Digite o ID do produto: ");
	input_str(id_busca);
	
	printf("Digite o novo valor: ");
	input_str(novo_valor);
	valor = atof(novo_valor);
	sprintf(novo_valor, "%.2f", valor);
	
	printf("\nConfirma a alteração de valor?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_alt_valor_estoque = input_int();
	
	arquivo_estoque = fopen("estoque.txt", "a+");
		if (arquivo_estoque == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_estoque) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
		if(strcmp(id_busca, produtos.id) == 0){
			do{
				switch(opcao_alt_valor_estoque){
					case 1:
						fclose(arquivo_estoque);
						arquivo_estoque = fopen("estoque.txt", "a+");
						if (arquivo_estoque == NULL){
							printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
							exit (1);
						}
						arquivo_estoque_temp = fopen("estoque_temp.txt", "a+");
						if (arquivo_estoque_temp == NULL){
							printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
							exit (1);
						}
						while(fgets(buffer, 250, arquivo_estoque) != NULL){
							sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
							if(strcmp(id_busca, produtos.id) == 0){
								fprintf(arquivo_estoque_temp, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, novo_valor, produtos.quantidade);
							}
							else{
								fprintf(arquivo_estoque_temp, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
							}
						}
						fclose(arquivo_estoque_temp);
						fclose(arquivo_estoque);
						
						arquivo_estoque = fopen("estoque.txt", "w");
						if (arquivo_estoque == NULL){
							printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
							exit (1);
						}
						arquivo_estoque_temp = fopen("estoque_temp.txt", "a+");
						if (arquivo_estoque_temp == NULL){
							printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
							exit (1);
						}
						
						while(fgets(buffer, 250, arquivo_estoque_temp) != NULL){
							sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
							fprintf(arquivo_estoque, "%s\t %s\t %s\t %s\n", produtos.id, produtos.nome, produtos.valor_venda, produtos.quantidade);
						}
						fclose(arquivo_estoque_temp);
						fclose(arquivo_estoque);
						remove("estoque_temp.txt");
						printf("\nValor alterado com sucesso. Pressione qualquer tecla para retornar ao menu do estoque.\n");
						getch();
						estoque();
					break; 
					
					case 2: 
						printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao menu do estoque.\n");
						getch();
						estoque();
					break;
					
					default:
						printf("Opção Invalida! Digite outra opção: ");
						opcao_alt_valor_estoque = input_int();
					break;   
				}
			}while(opcao_alt_valor_estoque != 0);
		}
	}
	printf("Produto não cadastrado no estoque. Pressione qualquer tecla para retornar ao menu do estoque.");
	getch();
	estoque();
}


//IMPRIME TODAS AS COMPRAS DE PRODUTOS REALIZADOS PELA EMPRESA
void todas_compras(){
	clrscr();
	desenhar_cabecalho();
	printf("TODAS AS COMPRAS / ENTRADA DE PRODUTOS\n");
	printf("_____________________________\n\n");
	
	void estoque();
	
	float total, soma_total;
	char buffer[250], user_registro[30];
	FILE *arquivo_compras;	
	FILE *arquivo_vendas;
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	printf("Todas as compras: \n");
	arquivo_compras = fopen("compras.txt", "a+");
	if (arquivo_compras == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
	}
	while(fgets(buffer, 250, arquivo_compras) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
		printf("\nID do produto: %s\nCNPJ do fornecedor: %s\nValor Un.: R$%s\t Quantidade: %s\t Total gasto: R$%s\nData: %s/%s/%s às %s:%s\nRegistrado por: %s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos, user_registro);
		total = atof(relatorio.total);
		soma_total += total;
	}
	fclose(arquivo_compras);
	printf("_____________________________________________\n\n");
	printf("Total: R$%.2f\n", soma_total);
	printf("_____________________________________________\n\n");
	printf("Pressione qualquer tecla para retornar ao menu do estoque.\n");
	getch();
	estoque();
}


//MENU DO ESTOQUE
void estoque(){
	clrscr();
	desenhar_cabecalho();
	printf("ESTOQUE\n");
	printf("_______\n\n");
	
	int opcao_estoque = 0, escolha = 0;
	FILE *arquivo_estoque;	
	struct estoque produtos;
	char buffer[250], id_busca[10];
	
	print_estoque();
	
	
	printf("OPÇÕES: \n\n");
	printf("1) - CADASTRAR NOVO PRODUTO\n");
	printf("2) - REGISTRAR COMPRA DE PRODUTOS JÁ CADASTRADOS\n");
	printf("3) - ALTERAR VALOR DE VENDA DE PRODUTO\n");
	printf("4) - HISTÓRICO DE COMPRAS / TODAS AS COMPRAS\n");
	printf("5) - HISTÓRICO DE COMPRAS / DIA/MÊS/ANO\n");
    printf("6) - RETORNAR AO MENU PRINCIPAL\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_estoque = input_int();
    
    do{
    	switch(opcao_estoque){
    		case 1:
				registrar_produto_estoque();
			break;
			
			case 2:
				adicionar_produto_cadastrado();
			break;
			
			case 3:
				alterar_valor();
			break;
			
			case 4:
				todas_compras();
			break;
			
			case 5:
				escolha = 1;
				relatorios_dia(escolha);
			break;	
				
			case 6:
				main();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_estoque = input_int();
			break;   
		}
	}while(opcao_estoque != 0);
}


//IMPRIME NA TELA TODAS AS COMPRAS E VENDAS DE PRODUTOS DE FORNECEDORES E CLIENTES, BUSCANDO NO ARQUIVO PELO DOCUMENTO DOS MESMOS
void relatorios_documento(int escolha, char documento[20]){
	clrscr();
	desenhar_cabecalho();
	
	float total, soma_total;
	char buffer[250], user_registro[30];
	FILE *arquivo_relatorio, *arquivo_clientes, *arquivo_fornecedores;	
	void relatorios();
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	void perfil_fornecedor(char documento[20]);
	void perfil_cliente(char documento[20]);
	void fornecedores();
	void clientes();
	
	if(escolha == 1){

		
		arquivo_relatorio = fopen("compras.txt", "a+");
		if (arquivo_relatorio == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		
		printf("HISTÓRICO DE TRANSAÇÕES DO FORNECEDOR:\n");
		printf("______________________________________\n\n");
		
		while(fgets(buffer, 250, arquivo_relatorio) != NULL){
			sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos); 
			if(strcmp(documento, relatorio.documento) == 0){
				printf("\nID do produto: %s\t CPF/CNPJ: %s\nValor Un.: R$%s\t Quantidade: %s\t Total: R$%s\nData: %s/%s/%s às %s:%s\nRegistrado por: %s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos, user_registro);
				total = atof(relatorio.total);
				soma_total += total;
			}
		}
		printf("_____________________________________________\n\n");
		printf("Total: R$%.2f\n", soma_total);
		printf("_____________________________________________\n\n");
		
		fclose(arquivo_relatorio);

		printf("Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
		getch();
		perfil_fornecedor(documento);
	}
	if(escolha == 2){
		printf("HISTÓRICO DE TRANSAÇÕES DO CLIENTE\n");
		printf("__________________________________\n\n");
		
		arquivo_relatorio = fopen("vendas.txt", "a+");
	
		if (arquivo_relatorio == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		while(fgets(buffer, 250, arquivo_relatorio) != NULL){
			sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos); 
			if(strcmp(documento, relatorio.documento) == 0){
				printf("\nID do produto: %s\t CPF/CNPJ: %s\nValor Un.: R$%s\t Quantidade: %s\t Total: R$%s\nData: %s/%s/%s às %s:%s\nRegistrado por: %s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos, user_registro);
				total = atof(relatorio.total);
				soma_total += total;
			}
		}
		printf("_____________________________________________\n\n");
		printf("Total: R$%.2f\n", soma_total);
		printf("_____________________________________________\n\n");
		
		fclose(arquivo_relatorio);
		
		printf("Pressione qualquer tecla para retornar ao perfil do cliente.\n");
		getch();
		perfil_cliente(documento);
		
	}
	fclose(arquivo_relatorio);
	printf("Informações não encontradas. Pressione qualquer tecla para retornar ao menu principal.\n");
	getch();
	main();
}

//CADASTRA UM NOVO CLIENTE NO SISTEMA
void cadastrar_cliente(){
	clrscr();
	desenhar_cabecalho();
	
	void clientes();
	
	char buffer[250], input_documento[20], input_nome[50], input_telefone[15], input_email[30];
	int opcao_cadastro_clientes;
	FILE *arquivo_clientes;
	struct clientes cliente;
	
	
	printf("CADASTRAR NOVO CLIENTE:\n");
	printf("_______________________\n\n");
	
	arquivo_clientes = fopen("clientes.txt", "a+");
	if (arquivo_clientes == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
		}
	
	printf("Digite o CPF ou CNPJ: ");
	input_str(input_documento);
	
	printf("Digite o nome completo: ");
	input_str(input_nome);
	
	printf("Digite o telefone para contato: ");
	input_str(input_telefone);
	
	printf("Digite o email: ");
	input_str(input_email);
	
	while(fgets(buffer, 250, arquivo_clientes) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		if(strcmp(input_documento, cliente.documento) == 0){
			fclose(arquivo_clientes);
			printf("CPF já cadastrado. Pressione qualquer tecla para retornar ao menu de clientes.\n");
			getch();
			clientes();
		}
		if(strcmp(input_telefone, cliente.telefone)==0){
			fclose(arquivo_clientes);
			printf("Telefone já cadastrado. Pressione qualquer tecla para retornar ao menu de clientes.\n");
			getch();
			clientes();
		}
		if(strcmp(input_email, cliente.email)==0){
			fclose(arquivo_clientes);
			printf("Email já cadastrado. Pressione qualquer tecla para retornar ao menu de clientes.\n");
			getch();
			clientes();
		}
	}
	
	printf("\nAs informações acima estão corretas?\n");
	printf("1) SIM / 2) NÃO\n");
	printf("Digite: ");
	opcao_cadastro_clientes = input_int();
	
	do{
		switch(opcao_cadastro_clientes){
			case 1:
				fprintf(arquivo_clientes, "%s\t %s\t %s\t %s\n", input_documento, input_nome, input_telefone, input_email);
				fclose(arquivo_clientes);
				printf("\nCliente cadastrado com sucesso. Pressione qualquer tecla para retornar ao menu de clientes.\n");
				getch();
				clientes();
			break;
			case 2:
				printf("Operação cancelada com sucesso. Pressione qualquer tecla para continuar.\n");
				getch();
				clientes();
			break;	
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_cadastro_clientes = input_int();
			break;   
		}
	}while(opcao_cadastro_clientes != 0);
}





//ALTERA EMAIL DE CONTATO DO CLIENTE NO SISTEMA
void alterar_email_clientes(char documento[20]){
	printf("_____________\n");
	printf("ALTERAR EMAIL\n\n");
	
	void perfil_cliente(char documento[20]);
	void clientes();
	char buffer[250], novo_email[30];
	FILE *arquivo_clientes, *arquivo_clientes_temp;
	struct clientes cliente;
	int opcao_alt_email_clientes = 0;
	
	printf("Digite o novo endereço de email: ");
	input_str(novo_email);
	
	printf("\nO novo email está correto?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_alt_email_clientes = input_int();
	
	do{
		switch(opcao_alt_email_clientes){
			case 1:
				arquivo_clientes = fopen("clientes.txt", "a+");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_clientes) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					if(strcmp(documento, cliente.documento) == 0){
						fprintf(arquivo_clientes_temp, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, novo_email);
					}
					else{
						fprintf(arquivo_clientes_temp, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					}
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				
				arquivo_clientes = fopen("clientes.txt", "w");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_clientes_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					fprintf(arquivo_clientes, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				remove("clientes_temp.txt");
				
				printf("\nEmail alterado com sucesso. Pressione qualquer tecla para retornar ao perfil do cliente.\n");
				getch();
				perfil_cliente(documento);
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do cliente.\n");
				getch();
				perfil_cliente(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_alt_email_clientes = input_int();
			break;   
		}
	}while(opcao_alt_email_clientes != 0);
	
}

//ALTERA TELEFONE DE CONTATO DO CLIENTE NO SISTEMA
void alterar_tel_clientes(char documento[20]){
	printf("________________\n");
	printf("ALTERAR TELEFONE\n\n");
	
	void perfil_cliente(char documento[20]);
	void clientes();
	char buffer[250], novo_telefone[30];
	FILE *arquivo_clientes, *arquivo_clientes_temp;
	struct clientes cliente;
	int opcao_alt_tel_clientes = 0;
	
	printf("Digite o novo número de telefone: ");
	input_str(novo_telefone);
	
	printf("\nO novo número de telefone está correto?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_alt_tel_clientes = input_int();
	
	do{
		switch(opcao_alt_tel_clientes){
			case 1:
				arquivo_clientes = fopen("clientes.txt", "a+");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_clientes) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					if(strcmp(documento, cliente.documento) == 0){
						fprintf(arquivo_clientes_temp, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, novo_telefone, cliente.email);
					}
					else{
						fprintf(arquivo_clientes_temp, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					}
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				
				arquivo_clientes = fopen("clientes.txt", "w");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_clientes_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					fprintf(arquivo_clientes, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				remove("clientes_temp.txt");
				
				printf("\nTelefone alterado com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_cliente(documento);
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_cliente(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_alt_tel_clientes = input_int();
			break;   
		}
	}while(opcao_alt_tel_clientes != 0);
	
}

//EXCLUI O PERFIL DO CLIENTE NO SISTEMA
void excluir_cliente(char documento[20]){
	printf("___________________________\n");
	printf("EXCLUIR CADASTRO DO CLIENTE\n\n");

	void perfil_cliente(char documento[20]);
	void clientes();
	char buffer[250];
	FILE *arquivo_clientes, *arquivo_clientes_temp;
	struct clientes cliente;
	int opcao_excluir_cliente = 0;
	
	
	printf("\nTem certeza que deseja excluir este cadastro?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_excluir_cliente = input_int();
	
	do{
		switch(opcao_excluir_cliente){
			case 1:
				arquivo_clientes = fopen("clientes.txt", "a+");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_clientes) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					if(strcmp(documento, cliente.documento) != 0){
						fprintf(arquivo_clientes_temp, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					}
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				
				arquivo_clientes = fopen("clientes.txt", "w");
				if (arquivo_clientes == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_clientes_temp = fopen("clientes_temp.txt", "a+");
				if (arquivo_clientes_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_clientes_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					if(strcmp(documento, cliente.documento) != 0){
						fprintf(arquivo_clientes, "%s\t %s\t %s\t %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
					}
				}
				fclose(arquivo_clientes_temp);
				fclose(arquivo_clientes);
				remove("clientes_temp.txt");
				
				printf("\nFornecedor excluído com sucesso. Pressione qualquer tecla para retornar ao menu de clientes.\n");
				getch();
				clientes();
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do cliente.\n");
				getch();
				perfil_cliente(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_excluir_cliente = input_int();
			break;   
		}
	}while(opcao_excluir_cliente != 0);
	
}

//ABRE UM MENU PARA O PERFIL DO CLIENTE
void perfil_cliente(char documento[20]){
	clrscr();
	desenhar_cabecalho();
	printf("PERFIL DO CLIENTE\n");
	printf("_________________\n\n");
	
	void clientes();
	char buffer[250];
	int opcao_perfil_cliente = 0, escolha = 2;
	FILE *arquivo_clientes;	
	struct clientes cliente;
	
	
	arquivo_clientes = fopen("clientes.txt", "a+");
	if (arquivo_clientes == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	printf("Informações do cliente: \n");
	while(fgets(buffer, 250, arquivo_clientes) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		if(strcmp(documento, cliente.documento) == 0){
			printf("\nCNPJ: %s\t Nome: %s\nTelefone: %s\t Email: %s\n", cliente.documento, cliente.nome, cliente.telefone, cliente.email);
		}
	}
	fclose(arquivo_clientes);
	printf("_____________________________________________\n\n");
	printf("OPÇÕES: \n\n");
	printf("1) - HISTÓRICO DE TRANSAÇÕES\n");
	printf("2) - ALTERAR TELEFONE\n");
	printf("3) - ALTERAR EMAIL\n");
	printf("4) - EXCLUIR CADASTRO\n");
    printf("5) - RETORNAR AO MENU DE CLIENTE\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_perfil_cliente = input_int();
    
    do{
    	switch(opcao_perfil_cliente){
    		case 1:
				relatorios_documento(escolha, documento);
			break;
				
			case 2:	
				alterar_tel_clientes(documento);
			break;
				
			case 3:
				alterar_email_clientes(documento);
			break;	
				
			case 4:
				excluir_cliente(documento);
			break;
				
			case 5:
				clientes();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_perfil_cliente = input_int();
			break;   
		}
	}while(opcao_perfil_cliente != 0);
}


//MENU DE CLIENTES
void clientes(){
	clrscr();
	desenhar_cabecalho();
	printf("CLIENTES\n");
	printf("_______\n\n");
	
	char buffer[250], documento[20];
	int opcao_clientes = 0, escolha = 2;
	FILE *arquivo_clientes;	
	struct clientes cliente;
	
	print_clientes();
	
	printf("OPÇÕES: \n\n");
	printf("1) - CADASTRAR NOVO CLIENTE\n");
	printf("2) - ABRIR PERFIL DO CLIENTE\n");
    printf("3) - RETORNAR AO MENU PRINCIPAL\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_clientes = input_int();
    
    do{
    	switch(opcao_clientes){
    		case 1:
				cadastrar_cliente();
			break;
				
			case 2:
				printf("_______________________\n");
				printf("ABRIR PERFIL DO CLIENTE\n\n");
				printf("Digite o documento do cliente: ");
				input_str(documento);
				perfil_cliente(documento);
			break;	
				
			case 3:
				main();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_clientes = input_int();
			break;   
		}
	}while(opcao_clientes != 0);
}


//CADASTRA UM NOVO FORNECEDOR NO SISTEMA
void cadastrar_fornecedor(){
	clrscr();
	desenhar_cabecalho();
	
	void fornecedores();
	char buffer[250], input_cnpj[20], input_nome[50], input_telefone[15], input_email[30];
	int opcao_cadastro_fornecedores;
	FILE *arquivo_fornecedores;
	struct fornecedores fornecedor;
	
	
	printf("CADASTRAR NOVO FORNECEDOR:\n");
	printf("__________________________\n\n");
	
	arquivo_fornecedores = fopen("fornecedores.txt", "a+");
	if (arquivo_fornecedores == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
		}
	
	printf("Digite o CNPJ: ");
	input_str(input_cnpj);
	
	printf("Digite o nome: ");
	input_str(input_nome);
	
	printf("Digite o telefone para contato: ");
	input_str(input_telefone);
	
	printf("Digite o email: ");
	input_str(input_email);
	
	while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		if(strcmp(input_cnpj, fornecedor.cnpj) == 0){
			fclose(arquivo_fornecedores);
			printf("CNPJ já cadastrado. Pressione qualquer tecla para retornar ao menu de fornececdores.\n");
			getch();
			fornecedores();
		}
		if(strcmp(input_telefone, fornecedor.telefone)==0){
			fclose(arquivo_fornecedores);
			printf("Telefone já cadastrado. Pressione qualquer tecla para retornar ao menu de fornececdores.\n");
			getch();
			fornecedores();
		}
		if(strcmp(input_email, fornecedor.email)==0){
			fclose(arquivo_fornecedores);
			printf("Email já cadastrado. Pressione qualquer tecla para retornar ao menu de fornececdores.\n");
			getch();
			fornecedores();
		}
	}
	
	printf("\nAs informações acima estão corretas?\n");
	printf("1) Sim / 2) Não\n");
	printf("Digite: ");
	opcao_cadastro_fornecedores = input_int();
	
	do{
		switch(opcao_cadastro_fornecedores){
			case 1:
				fprintf(arquivo_fornecedores, "%s\t %s\t %s\t %s\n", input_cnpj, input_nome, input_telefone, input_email);
				fclose(arquivo_fornecedores);
				printf("\nFornecedor cadastrado com sucesso. Pressione qualquer tecla para retornar ao menu de fornecedores.\n");
				getch();
				fornecedores();
			break;
			case 2:
				printf("Operação cancelada com sucesso. Pressione qualquer tecla para continuar.\n");
				getch();
				fornecedores();
			break;	
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_cadastro_fornecedores = input_int();
			break;   
			}
		}while(opcao_cadastro_fornecedores != 0);
}

//ALTERA O EMAIL DE CONTATO DO FORNECEDOR
void alterar_email_fornecedores(char documento[20]){
	printf("_____________\n");
	printf("ALTERAR EMAIL\n\n");
	
	void perfil_fornecedor(char documento[20]);
	void fornecedores();
	char buffer[250], novo_email[30];
	FILE *arquivo_fornecedores, *arquivo_forn_temp;
	struct fornecedores fornecedor;
	int opcao_alt_email_forn = 0;
	
	printf("Digite o novo endereço de email: ");
	input_str(novo_email);
	
	printf("\nO novo email está correto?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_alt_email_forn = input_int();
	
	do{
		switch(opcao_alt_email_forn){
			case 1:
				arquivo_fornecedores = fopen("fornecedores.txt", "a+");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
					if(strcmp(documento, fornecedor.cnpj) == 0){
						fprintf(arquivo_forn_temp, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, novo_email);
					}
					else{
						fprintf(arquivo_forn_temp, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
					}
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				
				arquivo_fornecedores = fopen("fornecedores.txt", "w");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_forn_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
					fprintf(arquivo_fornecedores, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				remove("forn_temp.txt");
				
				printf("\nEmail alterado com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_fornecedor(documento);
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_fornecedor(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_alt_email_forn = input_int();
			break;   
		}
	}while(opcao_alt_email_forn != 0);
	
}


//ALTERA O TELEFONE DE CONTATO DO FORNECEDOR
void alterar_tel_fornecedores(char documento[20]){
	printf("________________\n");
	printf("ALTERAR TELEFONE\n\n");
	
	void perfil_fornecedor(char documento[20]);
	void fornecedores();
	char buffer[250], novo_telefone[30];
	FILE *arquivo_fornecedores, *arquivo_forn_temp;
	struct fornecedores fornecedor;
	int opcao_alt_tel_forn = 0;
	
	printf("Digite o novo número de telefone: ");
	input_str(novo_telefone);
	
	printf("\nO novo número de telefone está correto?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_alt_tel_forn = input_int();
	
	do{
		switch(opcao_alt_tel_forn){
			case 1:
				arquivo_fornecedores = fopen("fornecedores.txt", "a+");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone,  fornecedor.email);
					if(strcmp(documento, fornecedor.cnpj) == 0){
						fprintf(arquivo_forn_temp, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, novo_telefone, fornecedor.email);
					}
					else{
						fprintf(arquivo_forn_temp, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
					}
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				
				arquivo_fornecedores = fopen("fornecedores.txt", "w");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_forn_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
					fprintf(arquivo_fornecedores, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				remove("forn_temp.txt");
				
				printf("\nTelefone alterado com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_fornecedor(documento);
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_fornecedor(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_alt_tel_forn = input_int();
			break;   
		}
	}while(opcao_alt_tel_forn != 0);
	
}

//EXCLUI O CADASTRO DO FORNECEDOR
void excluir_fornecedores(char documento[20]){
	printf("______________________________\n");
	printf("EXCLUIR CADASTRO DE FORNECEDOR\n\n");

	void perfil_fornecedor(char documento[20]);
	void fornecedores();
	char buffer[250];
	FILE *arquivo_fornecedores, *arquivo_forn_temp;
	struct fornecedores fornecedor;
	int opcao_excluir_forn = 0;
	
	
	printf("\nTem certeza que deseja excluir este cadastro?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_excluir_forn = input_int();
	
	do{
		switch(opcao_excluir_forn){
			case 1:
				arquivo_fornecedores = fopen("fornecedores.txt", "a+");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.email, fornecedor.telefone);
					if(strcmp(documento, fornecedor.cnpj) != 0){
						fprintf(arquivo_forn_temp, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.email, fornecedor.telefone);
					}
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				
				arquivo_fornecedores = fopen("fornecedores.txt", "w");
				if (arquivo_fornecedores == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_forn_temp = fopen("forn_temp.txt", "a+");
				if (arquivo_forn_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_forn_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.email, fornecedor.telefone);
					if(strcmp(documento, fornecedor.cnpj) != 0){
						fprintf(arquivo_fornecedores, "%s\t %s\t %s\t %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.email, fornecedor.telefone);
					}
				}
				fclose(arquivo_forn_temp);
				fclose(arquivo_fornecedores);
				remove("forn_temp.txt");
				
				printf("\nFornecedor excluído com sucesso. Pressione qualquer tecla para retornar ao menu de fornecedores.\n");
				getch();
				fornecedores();
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao perfil do fornecedor.\n");
				getch();
				perfil_fornecedor(documento);
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_excluir_forn = input_int();
			break;   
		}
	}while(opcao_excluir_forn != 0);
	
}


//ABRE O PERFIL DO FORNECEDOR
void perfil_fornecedor(char documento[20]){
	clrscr();
	desenhar_cabecalho();
	printf("PERFIL DO FORNECEDOR\n");
	printf("____________________\n\n");
	
	void fornecedores();
	char buffer[250];
	int opcao_perfil_fornecedor = 0, escolha = 1;
	FILE *arquivo_fornecedores;	
	struct fornecedores fornecedor;
	
	
	arquivo_fornecedores = fopen("fornecedores.txt", "a+");
	if (arquivo_fornecedores == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	printf("Informações do fornecedor: \n");
	while(fgets(buffer, 250, arquivo_fornecedores) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		if(strcmp(documento, fornecedor.cnpj) == 0){
			printf("\nCNPJ: %s\t Nome: %s\nTelefone: %s\t Email: %s\n", fornecedor.cnpj, fornecedor.nome, fornecedor.telefone, fornecedor.email);
		}
	}
	fclose(arquivo_fornecedores);
	printf("_____________________________________________\n\n");
	printf("OPÇÕES: \n\n");
	printf("1) - HISTÓRICO DE TRANSAÇÕES\n");
	printf("2) - ALTERAR TELEFONE\n");
	printf("3) - ALTERAR EMAIL\n");
	printf("4) - EXCLUIR CADASTRO\n");
    printf("5) - RETORNAR AO MENU DE FORNECEDORES\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_perfil_fornecedor = input_int();
    
    do{
    	switch(opcao_perfil_fornecedor){
    		case 1:
				relatorios_documento(escolha, documento);
			break;
				
			case 2:	
				alterar_tel_fornecedores(documento);
			break;
				
			case 3:
				alterar_email_fornecedores(documento);
			break;	
				
			case 4:
				excluir_fornecedores(documento);
			break;
				
			case 5:
				fornecedores();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_perfil_fornecedor = input_int();
			break;   
		}
	}while(opcao_perfil_fornecedor != 0);
}


//MENU DE FORNCEDORES
void fornecedores(){
	clrscr();
	desenhar_cabecalho();
	printf("FORNECEDORES\n");
	printf("_____________\n\n");
	
	char buffer[250], documento[20];
	int opcao_fornecedores = 0, escolha = 1;
	FILE *arquivo_fornecedores;	
	struct fornecedores fornecedor;
	
	print_fornecedores();
	
	printf("OPÇÕES: \n\n");
	printf("1) - CADASTRAR NOVO FORNECEDOR\n");
	printf("2) - ABRIR PERFIL DO FORNECEDOR\n");
    printf("3) - RETORNAR AO MENU PRINCIPAL\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_fornecedores = input_int();
    
    do{
    	switch(opcao_fornecedores){
    		case 1:
				cadastrar_fornecedor();
			break;
				
			case 2:	
				printf("__________________________\n");
				printf("ABRIR PERFIL DO FORNECEDOR\n\n");
				printf("Digite o CNPJ do fornecedor: ");
				input_str(documento);
				perfil_fornecedor(documento);
			break;
				
			case 3:
				main();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_fornecedores = input_int();
			break;   
		}
	}while(opcao_fornecedores != 0);
}

//TOTAL DE VENDAS REGISTRADAS PELOS USUÁRIOS NO PERÍODO DE UM ANO ESPECIFICO
void users_vendas(int ano_busca){
	clrscr();
	desenhar_cabecalho();
	
	printf("TOTAL DE VENDAS POR USUÁRIO\n");
	printf("____________________________\n\n");
	
	void relatorios();
	char buffer[250], user_registro[20], mes_loop[10], ano_loop[10];
	float temp_float1, total_compras, total_vendas, total_geral;
	int opcao_relatorios = 0, escolha, i;
	FILE *arquivo_users;	
	FILE *arquivo_vendas;
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	struct user user;
	
	sprintf(ano_loop, "%d", ano_busca);
	printf("Ano: %s\n\n", ano_loop);
	i = 1;
	while (i <= 12){
		sprintf(mes_loop, "%02d", i);

		
		arquivo_users = fopen("users.txt", "a+");
		if (arquivo_users == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		
		printf("\nMês: %s\n", mes_loop);
		while(fgets(buffer, 250, arquivo_users) != NULL){
			sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
			
			total_vendas = 0;
			
			arquivo_vendas = fopen("vendas.txt", "a+");
			if (arquivo_vendas == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
			}	
			while(fgets(buffer, 250, arquivo_vendas) != NULL){
				sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
				if (strcmp(data.mes, mes_loop) == 0 && strcmp(data.ano, ano_loop) == 0 && strcmp(user.user, user_registro) == 0){
					temp_float1 = atof(relatorio.total);
					total_vendas = total_vendas + temp_float1;
				}		
			}
			fclose(arquivo_vendas);
			
			printf("Usuário: %s\t\tTotal de vendas: R$%.2f\n", user.user, total_vendas);
		}	
		fclose(arquivo_users);
		
		i++;
	}
	printf("_____________________________________________\n\n");
	printf("\nPressione qualquer tecla para retornar ao menu de relatórios.\n");
	getch();
	relatorios();
}


//RELATÓRIO ANUAL DE DESPESAS, FATURAMENTO E LUCRO
void relatorio_anual(int ano_busca){
	clrscr();
	desenhar_cabecalho();
	
	printf("RELATÓRIO ANUAL\n");
	printf("_______________\n\n");
	
	void relatorios();
	char buffer[250], user_registro[20], mes_loop[10], ano_loop[10];
	float temp_float1, total_compras, total_vendas, total_geral;
	int opcao_relatorios = 0, escolha, i;
	FILE *arquivo_compras;	
	FILE *arquivo_vendas;
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	sprintf(ano_loop, "%d", ano_busca);
	printf("Ano: %s\n\n", ano_loop);
	i = 1;
	while (i <= 12){
		sprintf(mes_loop, "%02d", i);
		total_compras = 0;
		total_vendas = 0;
		arquivo_compras = fopen("compras.txt", "a+");
		if (arquivo_compras == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		while(fgets(buffer, 250, arquivo_compras) != NULL){
			sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
			if (strcmp(data.mes, mes_loop) == 0 && strcmp(data.ano, ano_loop) == 0){
				temp_float1 = atof(relatorio.total);
				total_compras = total_compras + temp_float1;
			}	
		}
		
		arquivo_vendas = fopen("vendas.txt", "a+");
		if (arquivo_vendas == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
		while(fgets(buffer, 250, arquivo_vendas) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
			if (strcmp(data.mes, mes_loop) == 0 && strcmp(data.ano, ano_loop) == 0){
				temp_float1 = atof(relatorio.total);
				total_vendas = total_vendas + temp_float1;
			}		
		}
		fclose(arquivo_vendas);
		fclose(arquivo_compras);
		printf("Mês: %s\n", mes_loop);
		printf("Despesas: \tR$%.2f\n", total_compras);
		printf("Faturamento: \tR$%.2f\n", total_vendas);
		total_geral = total_vendas - total_compras;
		printf("Lucro: \t\tR$%.2f\n\n", total_geral);
		i++;
	}
	printf("_____________________________________________\n\n");
	printf("Pressione qualquer tecla para retornar ao menu de relatórios.\n");
	getch();
	relatorios();
}

//MENU DE RELATÓRIOS
void relatorios(){
	clrscr();
	desenhar_cabecalho();
	printf("RELATÓRIOS\n");
	printf("__________\n\n");
	
	char buffer[250], user_registro[20];
	float temp_float1, total_compras, total_vendas, total_geral;
	int opcao_relatorios = 0, escolha, ano_busca;
	FILE *arquivo_compras;	
	FILE *arquivo_vendas;
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	arquivo_compras = fopen("compras.txt", "a+");
	if (arquivo_compras == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	
	while(fgets(buffer, 250, arquivo_compras) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
		temp_float1 = atof(relatorio.total);
		total_compras = total_compras + temp_float1;
	}
	fclose(arquivo_compras);
	
	
	arquivo_vendas = fopen("vendas.txt", "a+");
	if (arquivo_vendas == NULL){
			printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
			exit (1);
		}
	while(fgets(buffer, 250, arquivo_vendas) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos);
		temp_float1 = atof(relatorio.total);
		total_vendas = total_vendas + temp_float1;
	}
	fclose(arquivo_vendas);

	
	
	
	total_geral = total_vendas - total_compras;
	
	printf("Movimentação financeira total: \n\n");
	printf("Despesas: \t%R$%.2f\n", total_compras);
	printf("Faturamento: \t%R$%.2f\n", total_vendas);
	printf("Lucro: \t\tR$%.2f\n", total_geral);
	
	printf("_____________________________________________\n\n");
	printf("OPÇÕES: \n\n");
	printf("1) - RELATÓRIO ANUAL\n");
	printf("2) - TOTAL DE VENDAS POR USUÁRIO\n");
    printf("3) - RETORNAR AO MENU PRINCIPAL\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_relatorios = input_int();

    do{
    	switch(opcao_relatorios){
    		case 1:
    			printf("\nRELATÓRIO ANUAL\n");
				printf("________________\n\n");
				printf("Digite o ano: ");
				ano_busca = input_int();
    			relatorio_anual(ano_busca);
			break;
				
			case 2:
				printf("\nTOTAL DE VENDAS POR USUÁRIO\n");
				printf("________________\n\n");
				printf("Digite o ano: ");
				ano_busca = input_int();
				users_vendas(ano_busca);
			break;
			
			case 3:
				main();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_relatorios = input_int();
			break;   
		}
	}while(opcao_relatorios != 0);
}

//TODAS AS INFORMAÇÕES DE VENDAS REGISTRADAS POR UM USUÁRIO ESPECIFICO 
void relatorios_user(char user_user[20]){
	clrscr();
	desenhar_cabecalho();
	
	float total, soma_total;
	char buffer[250], user_registro[30];
	FILE *arquivo_relatorio, *arquivo_clientes, *arquivo_fornecedores;	
	void relatorios();
	struct data data;
	struct estoque produtos;
	struct relatorios relatorio;
	struct fornecedores fornecedor;
	struct clientes cliente;
	
	void perfil_user(char user_user[20]);
	void fornecedores();
	void clientes();
	
	arquivo_relatorio = fopen("vendas.txt", "a+");
	if (arquivo_relatorio == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
		
	printf("HISTÓRICO DE VENDAS REGISTRADAS PELO USUÁRIO:\n");
	printf("______________________________________\n\n");
		
	while(fgets(buffer, 250, arquivo_relatorio) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %[^\n]", user_registro, produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos); 
		if(strcmp(user_user, user_registro) == 0){
			printf("\nID do produto: %s\t CPF/CNPJ: %s\nValor Un.: R$%s\t Quantidade: %s\t Total: R$%s\nData: %s/%s/%s às %s:%s\nRegistrado por: %s\n", produtos.id, relatorio.documento, relatorio.valor, produtos.quantidade, relatorio.total, data.dia, data.mes, data.ano, data.horas, data.minutos, user_registro);
			total = atof(relatorio.total);
			soma_total += total;
		}
	}
	printf("_____________________________________________\n\n");
	printf("Total: R$%.2f\n", soma_total);
	printf("_____________________________________________\n\n");
		
	fclose(arquivo_relatorio);

	printf("Pressione qualquer tecla para retornar ao perfil do usuário.\n");
	getch();
	perfil_user(user_user);
}


//ALTERA A SENHA DO USUÁRIO
void alterar_senha(char user_user[30]){
	printf("_____________\n");
	printf("ALTERAR SENHA\n\n");
	
	void perfil_user(char user_user[30]);
	void users();
	char buffer[250], nova_senha[15], nova_senha2[15];
	FILE *arquivo_users, *arquivo_users_temp;
	struct user user;
	int opcao_senha_users = 0;
	
	printf("Digite a nova senha: ");
	input_str(nova_senha);
	printf("Confirme a senha: ");
	input_str(nova_senha2);
	
	if(strcmp(nova_senha, nova_senha2) == 0){
		printf("\nTem certeza que deseja alterar a senha deste usuário?\n");
		printf("1) - SIM / 2) - NAO\n");
		printf("Sua escolha: ");
		opcao_senha_users = input_int();
		do{
			switch(opcao_senha_users){
				case 1:
					arquivo_users = fopen("users.txt", "a+");
					if (arquivo_users == NULL){
				    	printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				   		exit (1);
			    	}
				    arquivo_users_temp = fopen("users_temp.txt", "a+");
					if (arquivo_users == NULL){
					    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
					    exit (1);
				    }
			    
					while(fgets(buffer, 250, arquivo_users) != NULL){
						sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
						if(strcmp(user_user, user.user) == 0){
							fprintf(arquivo_users_temp, "%s\t %s\t %s\t %s\n", user.tipo, user.nome, user.user, nova_senha);
						}
						else{
							fprintf(arquivo_users_temp, "%s\t %s\t %s\t %s\n", user.tipo, user.nome, user.user, user.senha);
						}
					}
					fclose(arquivo_users_temp);
					fclose(arquivo_users);
					
					arquivo_users = fopen("users.txt", "w");
					if (arquivo_users == NULL){
					    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
					    exit (1);
				    }
				    arquivo_users_temp = fopen("users_temp.txt", "a+");
					if (arquivo_users == NULL){
					    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
					    exit (1);
				    }
					while(fgets(buffer, 250, arquivo_users_temp) != NULL){
						sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
						fprintf(arquivo_users, "%s\t %s\t %s\t %s\n", user.tipo, user.nome, user.user, user.senha);
					}
					fclose(arquivo_users_temp);
					fclose(arquivo_users);
					remove("users_temp.txt");
					
					printf("\nAlteração de senha realizada com sucesso. Pressione qualquer tecla para retornar ao perfil do usuário.\n");
					getch();
					perfil_user(user_user);
				break;
				
				case 2: 
					printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao menu de usuários.\n");
					getch();
					users();
				break;
				
				default:
					printf("Opção Invalida! Digite outra opção: ");
					opcao_senha_users = input_int();
				break; 
			}
		}while(opcao_senha_users != 0);
	}
	else{
		printf("Senhas não conferem. Pressione qualquer tecla para retornar ao perfil do usuário.\n");
		getch();
		perfil_user(user_user);
	}
}

//EXCLUI USUÁRIOS
void excluir_users(char user_user[30]){
	printf("_______________\n");
	printf("EXCLUIR USUÁRIO\n\n");

	
	void users();
	char buffer[250];
	FILE *arquivo_users, *arquivo_users_temp;
	struct user user;
	int opcao_excluir_users = 0;
	
	printf("\nTem certeza que deseja excluir este usuário?\n");
	printf("1) - SIM / 2) - NAO\n");
	printf("Sua escolha: ");
	opcao_excluir_users = input_int();
	
	do{
		switch(opcao_excluir_users){
			case 1:
				arquivo_users = fopen("users.txt", "a+");
				if (arquivo_users == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_users_temp = fopen("users_temp.txt", "a+");
				if (arquivo_users_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    
				while(fgets(buffer, 250, arquivo_users) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
					if(strcmp(user_user, user.user) != 0){
						fprintf(arquivo_users_temp, "%s\t %s\t %s\t %s\n", user.tipo, user.nome, user.user, user.senha);
					}
				}
				fclose(arquivo_users_temp);
				fclose(arquivo_users);
				
				arquivo_users = fopen("users.txt", "w");
				if (arquivo_users == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
			    arquivo_users_temp = fopen("users_temp.txt", "a+");
				if (arquivo_users_temp == NULL){
				    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
				    exit (1);
			    }
				while(fgets(buffer, 250, arquivo_users_temp) != NULL){
					sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
					if(strcmp(user_user, user.user) != 0){
						fprintf(arquivo_users, "%s\t %s\t %s\t %s\n", user.tipo, user.nome, user.user, user.senha);
					}
				}
				fclose(arquivo_users_temp);
				fclose(arquivo_users);
				remove("users_temp.txt");
				
				printf("\nUsuário deletado com sucesso. Pressione qualquer tecla para retornar ao menu de usuários.\n");
				getch();
				users();
			break; 
			
			case 2: 
				printf("\nOperação cancelada com sucesso. Pressione qualquer tecla para retornar ao menu de usuários.\n");
				getch();
				users();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_excluir_users = input_int();
			break;   
		}
	}while(opcao_excluir_users != 0);
	
}


//ABRE O PERFIL DO USUÁRIO
void perfil_user(char user_user[30]){
	clrscr();
	desenhar_cabecalho();
	printf("PERFIL DO USUÁRIO\n");
	printf("_________________\n\n");
	
	void users();
	char buffer[250];
	int opcao_perfil_user = 0, escolha = 1;
	FILE *arquivo_users;	
	struct user user;
	
	
	arquivo_users = fopen("users.txt", "a+");
	if (arquivo_users == NULL){
		printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
		exit (1);
	}
	printf("Informações do usuário: \n");
	while(fgets(buffer, 250, arquivo_users) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
		if(strcmp(user_user, user.user) == 0){
			printf("\nTipo de acesso: %s\t Nome completo: %s\nUsuário de acesso: %s\nSenha: %s\n", user.tipo, user.nome, user.user, user.senha);
		}
	}
	fclose(arquivo_users);
	
	printf("_____________________________________________\n\n");
	printf("OPÇÕES: \n\n");
	printf("1) - HISTÓRICO DE VENDAS\n");
	printf("2) - ALTERAR SENHA\n");
	printf("3) - EXCLUIR USUÁRIO\n");
    printf("4) - RETORNAR AO MENU DE USUÁRIOS\n\n");
    printf("\nDigite a opção desejada: ");
    opcao_perfil_user = input_int();
    
    do{
    	switch(opcao_perfil_user){
    		case 1:
				relatorios_user(user_user);
			break;
				
			case 2:	
				alterar_senha(user_user);
			break;
				
			case 3:
				excluir_users(user_user);
			break;	
				
			case 4:
				users();
			break;
			
			default:
				printf("Opção Invalida! Digite outra opção: ");
				opcao_perfil_user = input_int();
			break;   
		}
	}while(opcao_perfil_user != 0);
}
	


//MENU DE USUÁRIOS
void users(){
	clrscr();
	desenhar_cabecalho();
	printf("USUÁRIOS\n");
	printf("________\n\n");
	
	char buffer[250], user_user[30];
	FILE *arquivo_users;
	struct user user;
	int opcao_users = 0;
	
	arquivo_users = fopen("users.txt", "a+");
	if (arquivo_users == NULL){
	    printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
	    exit (1);
    };
	while(fgets(buffer, 250, arquivo_users) != NULL){
		sscanf(buffer, "%[^\t] %[^\t] %[^\t] %[^\n]", user.tipo, user.nome, user.user, user.senha);
		printf("\nTipo de acesso: %s\t Nome completo: %s\nUsuário de acesso: %s\nSenha: %s\n", user.tipo, user.nome, user.user, user.senha);

	}
	printf("_____________________________________________\n\n");
	
	printf("OPÇÕES: \n\n");
    printf("1) - CADASTRAR NOVO USUÁRIO\n");
    printf("2) - ABRIR PERFIL DO USUÁRIO\n");
    printf("3) - RETORNAR AO MENU PRINCIPAL\n\n"); 
    printf("Digite a opção desejada: ");
    opcao_users = input_int();
	do{ 
	switch (opcao_users){
		case 1:
			registrar_user();
		break;
		
		case 2:
			printf("__________________________\n");
			printf("ABRIR PERFIL DO USUÁRIO\n\n");
			printf("Digite o usuário de acesso: ");
			input_str(user_user);
			perfil_user(user_user);
		break;
		
		case 3: 
			main();
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao_users = input_int();
		break;    
		}
	}while (opcao_users != 0);    
	
}

//REALIZA O LOGOFF DO SISTEMA, ESVAZIANDO AS VARIAVEIS GLOBAIS
void logoff(){
	
    nome_usuario_logado[0] = '\0';
    user_usuario_logado[0] = '\0';
    tipo_usuario[0] = '\0';
    printf("\nLogoff realizado com sucesso! Pressione qualquer tecla para continuar.");
    getch();
    main();
}

//MENU PRINCIPAL PARA USUÁRIOS COM PRIVILÉGIOS ADMINISTRATIVOS
void menu_principal_1(){
	
	clrscr();
	desenhar_cabecalho();
	
	int opcao = 0;
	printf("MENU PRINCIPAL\n");
	printf("______________\n\n");
	printf("OPÇÕES: \n\n");
    printf("1) - VENDAS\n");
    printf("2) - ESTOQUE\n");
    printf("3) - CLIENTES\n");
    printf("4) - FORNECEDORES\n");
    printf("5) - RELATÓRIOS\n");
    printf("6) - USUÁRIOS\n");
    printf("7) - LOGOFF\n\n");    
    printf("Digite a opção desejada: ");
    opcao = input_int();
	do{ 
	switch (opcao){
		case 1:
			venda_produtos();
		break;
		
		case 2: 
			estoque();
		break;
				
		case 3:
			clientes();
		break;
		
		case 4:
			fornecedores();
		break;
		
		case 5:
			relatorios();
		break;
		
		case 6:
			users();
		break;
		
		case 7:
			logoff();
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao = input_int();
		break;    
		}
	}while (opcao != 0);       
}


//MENU PRINCIPAL PARA USUÁRIOS COM PRIVILÉGIOS FINANCEIROS
void menu_principal_2(){
	
	clrscr();
	desenhar_cabecalho();
	
	int opcao = 0;
	printf("MENU PRINCIPAL\n");
	printf("______________\n\n");
	printf("OPÇÕES: \n\n");
    printf("1) - VENDAS\n");
    printf("2) - ESTOQUE\n");
    printf("3) - CLIENTES\n");
    printf("4) - FORNECEDORES\n");
    printf("5) - RELATÓRIOS\n");
    printf("6) - LOGOFF\n\n");    
    printf("Digite a opção desejada: ");
    opcao = input_int();
	do{ 
	switch (opcao){
		case 1:
			venda_produtos();
		break;
		
		case 2: 
			estoque();
		break;
				
		case 3:
			clientes();
		break;
		
		case 4:
			fornecedores();
		break;
		
		case 5:
			relatorios();
		break;
		
		case 6:
			logoff();
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao = input_int();
		break;    
		}
	}while (opcao != 0);       
}


//MENU PRINCIPAL PARA USUÁRIOS COM PRIVILÉGIOS DE OPERADOR
void menu_principal_3(){
	
	clrscr();
	desenhar_cabecalho();
	
	int opcao = 0;
	printf("MENU PRINCIPAL\n");
	printf("______________\n\n");
	printf("OPÇÕES: \n\n");
    printf("1) - VENDAS\n");
    printf("2) - CLIENTES\n");
    printf("3) - LOGOFF\n\n");    
    printf("Digite a opção desejada: ");
    opcao = input_int();
	do{ 
	switch (opcao){
		case 1:
			venda_produtos();
		break;
			
		case 2:
			clientes();
		break;
				
		case 3:
			logoff();
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao = input_int();
		break;    
		}
	}while (opcao != 0);       
}

//MENU INICIAL DO SISTEMA
void menu_inicial(){
	int opcao_inicial;
	clrscr();
	desenhar_cabecalho();
	
	printf("MENU INICIAL\n");
	printf("____________\n\n");
	printf("OPÇÕES: \n\n");
    printf("1) - LOGIN\n");
    printf("2) - SAIR DO SISTEMA\n\n");    
    printf("Digite a opção desejada: ");
    opcao_inicial = input_int();
    do{
    	switch (opcao_inicial){
		case 1:
			tela_login();
		break;
		
		case 2:
			exit(1);
		break;
		
		default:
			printf("Opção Invalida! Digite outra opção: ");
			opcao_inicial = input_int();
		break;    
		}
	}while(nome_usuario_logado[0] == '\0');
}


//SE ARQUIVO DE USUÁRIOS ESTIVER VAZIO, CRIA USUÁRIO PADRÃO "admin" PARA ACESSO
void criar_user_admin(){
	FILE *arquivo_users;
	struct user users = {"1", "Administrador", "admin", "admin"};
	int size;
	
	arquivo_users = fopen("users.txt", "a+");
	if (arquivo_users == NULL){
        printf("\nErro ao acessar banco de dados. Finalizando aplicação.\n");
        exit (1);
    }
    
    fseek(arquivo_users, 0, SEEK_END);
    size = ftell(arquivo_users);
    
    if(size == 0){
    	fprintf(arquivo_users, "%s\t %s\t %s\t %s\n", users.tipo, users.nome, users.user, users.senha);
    	fclose(arquivo_users);
	}
}


//VERIFICAÇÕES INICIAIS ONDE O SISTEMA INICIA E PONTO DE ENCONTRO DAS DEMAIS FUNÇÕES
int main(){
	setlocale(LC_ALL, "");
	clrscr();
	
	criar_user_admin();
	
	if (tipo_usuario[0] == '\0'){
		menu_inicial();
	}
	while (tipo_usuario[0] != '\0'){
		if(tipo_usuario[0] == '1'){
			menu_principal_1();
		}
		if(tipo_usuario[0] == '2'){
			menu_principal_2();
		}	
		if(tipo_usuario[0] == '3'){
			menu_principal_3();
		}
	}
    return 0;
}

