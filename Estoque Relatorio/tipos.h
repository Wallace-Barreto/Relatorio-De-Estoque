#ifndef TIPOS_H
#define TIPOS_H

#include <ctime>

#define NOME_TAM 48

#define NOME_PRODUTO_TAM 32
#define TIPO_TAM 16

struct Produto
{
    int id;
    int Quantidade;
    char dia[3];
    char mes[3];
    char ano[5];
    float precoTotal;
    float preco;
    bool disponivel;
    char categoria[TIPO_TAM + 1];
    char TipoUnidade[TIPO_TAM + 1];
    char nome[NOME_PRODUTO_TAM + 1];
};

#endif // TIPOS_H
