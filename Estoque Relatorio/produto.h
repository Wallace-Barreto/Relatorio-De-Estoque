// produto.h - Defini��o da classe Produto e fun��es relacionadas

#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

extern unordered_map<int, int> dados_anteriores;

struct mercadorias
{
    int codigo;                    // Código do Produto
    char nome[33];                 // Nome do Produto
    char categoria[17];            // Categoria
    int qtd_anterior;              // Quantidade anterior
    int qtd_atual;                 // Quantidade atual
    float preco_custo;             // Preço unitário
    float valor_total;             // Valor total
    string status_reabastecimento; // Status de reabastecimento
    string data_cadastro;          // Data de cadastro do produto
};
// Fun��o para calcular o valor total de um produto
float calcular_valor_total(const mercadorias *produtos, int total);

// Fun��o para determinar o status de reabastecimento
string determinar_status_reabastecimento(int qtd_atual, int estoque_minimo, int estoque_normal);

void carregarDadosAnteriores(const char *nomeArquivo);
void salvarDadosAnteriores(const char *nomeArquivo);
void verificarQtdAnterior(mercadorias &objeto);
#endif // PRODUTO_H

