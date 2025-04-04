#ifndef RELATORIO_H
#define RELATORIO_H

#include <string>
#include "produto.h"

using namespace std;

struct Relatorio
{
    string data;               // Data do relat�rio
    string hora;               // Hora do relat�rio
    string responsavel;        // Respons�vel pelo relat�rio
    string localizacao;        // Localiza��o do estoque
    string fonte_dados;        // Fonte dos dados
    mercadorias *objetos;      // Array din�mico de produtos
    int total_produtos;        // Contador de produtos armazenados
    int total_movimentacoes;   // Contador de movimenta��es armazenadas
    float valor_total_estoque; // Valor total do estoque

    // Construtor: inicializa os ponteiros e vari�veis
    Relatorio()
        : objetos(nullptr),
          total_produtos(0),
          total_movimentacoes(0),
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

