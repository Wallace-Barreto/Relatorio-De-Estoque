#ifndef TABELAS_H
#define TABELAS_H

#include "tipos.h"
#define Produtos_DB "Produtos_DB.dat"  // Alterado para corresponder ao main.cpp

struct TabelaProduto {
    int qtd;
    Produto *dados;
};

void carregarTabelaCadsProduto(TabelaProduto &tabela);
void salvarTabelaCadsProduto(const TabelaProduto &tabela);
void cadspreco(Produto &produto, TabelaProduto &tabela);
void modificarProduto(TabelaProduto &tabela, int idProduto, const Produto &novoProduto);


#endif // TABELAS_H


