#ifndef RELATORIO_H
#define RELATORIO_H

#include <string>
#include "produto.h"
using namespace std;

struct Relatorio
{
    string data;
    string hora;
    string responsavel;
    string localizacao;
    string fonte_dados;
    mercadorias *objetos;
    int total_produtos;
    float valor_total_estoque;

    // Construtor: inicializa os ponteiros e vari�veis
    Relatorio()
        : objetos(nullptr),
          total_produtos(0),
          valor_total_estoque(0.0) {}

    // Destrutor: libera mem�ria dos arrays din�micos
    ~Relatorio()
    {
        if (objetos)
        {
            delete[] objetos;
            objetos = nullptr;
        }
    }
};

#endif // RELATORIO_H

