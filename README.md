# 📦 Sistema de Geração de Relatórios de Estoque

Sistema desenvolvido em C++ para gerar relatórios detalhados de estoque a partir de dados previamente registrados. Ele lê arquivos binários com informações dos produtos, realiza análises e gera um relatório em formato `.txt` com todas as informações organizadas.

---

## 🔄 Fluxo Principal do Programa

1. O processo inicia pela função `gerador_relatorio()`, chamada dentro da `main()`.
2. A função `carregarRelatorio()`:
   - Verifica a existência do arquivo `dados_anteriores.dat`, que armazena registros de execuções anteriores.
   - Acessa e carrega o conteúdo de `Produtos_DB.dat`, contendo os produtos cadastrados no sistema.
   - Converte e organiza os dados na estrutura adequada para o relatório.
3. A função `preencher_campos_relatorio()` coleta do usuário:
   - Nome do responsável pela solicitação do relatório.
   - Localização (associada a um estoque ou unidade específica).
4. Os dados são processados e analisados.
5. O relatório final é gerado e salvo no arquivo `relatorio_estoque_data_hora.txt`.
6. Ao final do processo, os dados alocados dinamicamente são liberados da memória.

---

## 🧱 Estruturas de Dados

### `Relatorio`
```cpp
struct Relatorio {
    string data;
    string hora;
    string responsavel;
    string localizacao;
    string fonte_dados;
    mercadorias* objetos;
    int total_produtos;
    int total_movimentacoes;
    float valor_total_estoque;
};
```

### `mercadorias`
```cpp
struct mercadorias {
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
```

### `Produto`
```cpp
struct Produto {
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
```

---

## 🗺️ Mapa Global de Histórico
```cpp
unordered_map<int, int> dados_anteriores;
```
Armazena os IDs dos produtos e suas respectivas quantidades de execuções anteriores.

---

## 💾 Alocação Dinâmica
```cpp
Relatorio* relatorio = new Relatorio;
relatorio->objetos = new mercadorias[quantidade_produtos];
delete relatorio;
```

---

## 🧮 Exemplo de Recursividade
Cálculo do valor total do estoque:
```cpp
float calcular_valor_total(const mercadorias* produtos, int total) {
    if (total == 0)
        return 0.0;
    return (produtos->qtd_atual * produtos->preco_custo) + calcular_valor_total(produtos + 1, total - 1);
}
```

---

## 📂 Funções Declaradas

### `utilitarios.h`
```cpp
string obter_data_atual();
string obter_hora_atual();
void preencher_campos_relatorio(Relatorio &rel);
void escrever_informacoes_gerais(ofstream &arquivo, const Relatorio &rel);
void escrever_produtos(ofstream &arquivo, const Relatorio &rel);
void escrever_alertas_e_observacoes(ofstream &arquivo, const Relatorio &rel);
void escrever_analise_financeira(ofstream &arquivo, const Relatorio &rel);
void escrever_assinatura(ofstream &arquivo, const Relatorio &rel);
void gerar_relatorio(const Relatorio &rel);
void carregarRelatorio(Relatorio* relatorio, const char* nomeArquivo);
void salvarRelatorioProdutos(const Relatorio& relatorio, const char* nomeArquivo);
void gerador_relatorio();
```

### `produto.h`
```cpp
float calcular_valor_total(const mercadorias* produtos, int total);
string determinar_status_reabastecimento(int qtd_atual, int estoque_minimo, int estoque_normal);
void carregarDadosAnteriores(const char* nomeArquivo);
void salvarDadosAnteriores(const char* nomeArquivo);
void verificarQtdAnterior(mercadorias &objeto);
```

---

## 📚 Bibliotecas Utilizadas
```cpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <limits>
#include <locale>

#include "produto.h"
#include "utilitarios.h"
#include "relatorio.h"
#include "tabelas.h"
```

---

## 📁 Arquivos Utilizados

### 📥 Entrada
- `Produtos_DB.dat`: Base de dados binária com os produtos cadastrados.

### 📤 Gerados
- `relatorio_estoque_data_hora.txt`: Relatório final com data e hora.
- `dados_anteriores.dat`: Arquivo auxiliar para comparação de quantidade anterior.

