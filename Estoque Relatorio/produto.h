// produto.h - Definicao da classe Produto e funcoes relacionadas

#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <string>
#include "produto.h"
#include <unordered_map>
#include <fstream>

using namespace std;

extern unordered_map<int, int> dados_anteriores;

struct mercadorias
{
    int codigo;
    char nome[33];
    char categoria[17];
    int qtd_anterior;
    int qtd_atual;
    float preco_custo;
    float valor_total;
    string status_reabastecimento;
    string data_cadastro;
};
// Funcao para calcular o valor total de um produto
float calcular_valor_total(const mercadorias *produtos, int total);

// Funcao para determinar o status de reabastecimento
string determinar_status_reabastecimento(int qtd_atual, int estoque_minimo, int estoque_normal);

void carregarDadosAnteriores(const char *nomeArquivo);
void salvarDadosAnteriores(const char *nomeArquivo);
void verificarQtdAnterior(mercadorias &objeto);
#endif // PRODUTO_H
