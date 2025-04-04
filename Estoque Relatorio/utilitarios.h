#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <string>
#include <fstream>
#include "relatorio.h"

using namespace std;

// Fun��es declaradas
string obter_data_atual();
string obter_hora_atual();
void preencher_campos_relatorio(Relatorio &rel);
void escrever_informacoes_gerais(ofstream &arquivo, const Relatorio &rel);
void escrever_produtos(ofstream &arquivo, const Relatorio &rel);
void escrever_alertas_e_observacoes(ofstream &arquivo, const Relatorio &rel);
void escrever_analise_financeira(ofstream &arquivo, const Relatorio &rel);
void escrever_assinatura(ofstream &arquivo, const Relatorio &rel);
void gerar_relatorio(const Relatorio &rel);
void carregarRelatorio(Relatorio *relatorio, const char *nomeArquivo);
void salvarRelatorioProdutos(const Relatorio &relatorio, const char *nomeArquivo);
void gerador_relatorio();
#endif // UTILITARIOS_H
