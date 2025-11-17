#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FUNCIONARIOS 50

// Estrutura para guardar informações de cada funcionário
typedef struct {
    char nome[50];
    int horasTrabalhadas;
    int horasExtras;
    float valorHora;
    int aprovado; // 0 = pendente, 1 = aprovado, -1 = rejeitado
} Funcionario;

Funcionario lista[MAX_FUNCIONARIOS];
int total = 0;

// Função para registrar novo funcionário
void registrarFuncionario() {
    if (total >= MAX_FUNCIONARIOS) {
        printf("Limite de funcionarios atingido!\n");
        return;
    }

    Funcionario f;
    printf("\n--- Registro de Funcionario ---\n");
    printf("Nome: ");
    getchar(); // limpar buffer
    fgets(f.nome, 50, stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0'; // remover quebra de linha
    printf("Horas trabalhadas: ");
    scanf("%d", &f.horasTrabalhadas);
    printf("Horas extras: ");
    scanf("%d", &f.horasExtras);
    printf("Valor da hora (R$): ");
    scanf("%f", &f.valorHora);
    f.aprovado = 0; // inicia como pendente

    lista[total++] = f;
    printf("Funcionario registrado com sucesso!\n");
}

// Função para calcular o valor total das horas extras
float calcularExtras(Funcionario f) {
    return f.horasExtras * (f.valorHora * 1.5); // hora extra = 150% da hora normal
}

// Função para aprovar ou rejeitar
void validarHoras() {
    int i, opcao;
    printf("\n--- Validacao de Horas Extras ---\n");
    for (i = 0; i < total; i++) {
        printf("%d. %s - Horas Extras: %d - Status: %s\n", i + 1, lista[i].nome,
               lista[i].horasExtras,
               lista[i].aprovado == 0 ? "PENDENTE" :
               lista[i].aprovado == 1 ? "APROVADO" : "REJEITADO");
    }

    printf("Escolha o funcionario (numero): ");
    scanf("%d", &i);
    i--;

    if (i < 0 || i >= total) {
        printf("Funcionario invalido!\n");
        return;
    }

    printf("1 - Aprovar | 2 - Rejeitar: ");
    scanf("%d", &opcao);
    lista[i].aprovado = (opcao == 1) ? 1 : -1;
    printf("Status atualizado com sucesso!\n");
}

// Função para mostrar relatório final
void gerarRelatorio() {
    printf("\n--- Relatorio de Horas Extras ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s\n", lista[i].nome);
        printf("Horas Trabalhadas: %d\n", lista[i].horasTrabalhadas);
        printf("Horas Extras: %d\n", lista[i].horasExtras);
        printf("Valor Hora: R$%.2f\n", lista[i].valorHora);
        printf("Total Extras: R$%.2f\n", calcularExtras(lista[i]));
        printf("Status: %s\n\n",
               lista[i].aprovado == 0 ? "PENDENTE" :
               lista[i].aprovado == 1 ? "APROVADO" : "REJEITADO");
    }
}

// Menu principal
int main() {
    int opcao;
    do {
        printf("\n===== CONTROLE DE HORAS EXTRAS =====\n");
        printf("1 - Registrar funcionario\n");
        printf("2 - Validar horas extras\n");
        printf("3 - Gerar relatorio\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: registrarFuncionario(); break;
            case 2: validarHoras(); break;
            case 3: gerarRelatorio(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}