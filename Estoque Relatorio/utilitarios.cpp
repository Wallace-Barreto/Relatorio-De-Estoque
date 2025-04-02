// utilitarios.cpp - Implementa��o das fun��es utilit�rias

#include <windows.h>
#include "utilitarios.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <locale>
#include "produto.h"
#include "relatorio.h"
#include "tabelas.h"
#include <limits>
#include <locale>

using namespace std;

// Funcao para obter a data atual
string obter_data_atual()
{
    time_t t = time(nullptr);
    tm *timePtr = localtime(&t);

    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d",
            timePtr->tm_mday,
            timePtr->tm_mon + 1, // Mês comeca em 0
            timePtr->tm_year + 1900);

    return string(buffer);
}

// Funcao para obter a hora atual
string obter_hora_atual()
{
    time_t t = time(nullptr);
    tm *timePtr = localtime(&t);

    char buffer[6];
    sprintf(buffer, "%02d:%02d", timePtr->tm_hour, timePtr->tm_min);

    return string(buffer);
}

// Funcao para preencher manualmente os outros campos do relatorio
void preencher_campos_relatorio(Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Limpa o buffer do cin para evitar interferências com getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Insira o responsavel: ";
    getline(cin, rel.responsavel);

    cout << "Insira a localizacao: ";
    getline(cin, rel.localizacao);

    // Define a fonte de dados automaticamente
    rel.fonte_dados = "Controle de Estoque (Modulo 2)";

    // Preenche a data automaticamente
    rel.data = obter_data_atual();

    cout << "Campos do relatorio preenchidos com sucesso!" << endl;
}
// Funcao para escrever informacoes gerais
void escrever_informacoes_gerais(ofstream &arquivo, const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Cabecalho do Relatorio
    arquivo << "====================================================================================================\n";
    arquivo << "\t\t\t\t\t\tRELATORIO DE ESTOQUE\n";
    arquivo << "====================================================================================================\n";

    // Informacoes Gerais
    arquivo << "\n1. INFORMAcoES GERAIS\n";
    arquivo << "-------------------------------------------------------------------\n";
    arquivo << "  Data do Relatorio        : " << rel.data << "\n";
    arquivo << "  Responsavel              : " << rel.responsavel << "\n";
    arquivo << "  Localizacao do Estoque   : " << rel.localizacao << "\n";
    arquivo << "  Fonte dos Dados          : " << rel.fonte_dados << "\n";
    arquivo << "-------------------------------------------------------------------\n";

    // Informacoes Extras - Melhorando o Contexto
    arquivo << "\nObservacoes:\n";
    arquivo << "- Este relatorio é baseado em dados gerados automaticamente pelo sistema de controle de estoque.\n";
    arquivo << "- Certifique-se de revisar as informacoes antes de executar acoes relacionadas ao estoque.\n";
    arquivo << "- As analises e alertas estao baseadas em métricas pré-definidas pela equipe responsavel.\n";
    arquivo << "====================================================================================================\n\n";
}

// Funcao principal para gerar o relatorio
void gerar_relatorio(const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    cout << "[DEBUG] Iniciando geracao do relatorio." << endl;

    ofstream arquivo("relatorio_estoque.txt");
    if (!arquivo)
    {
        cerr << "[ERRO] Falha ao abrir o arquivo para escrita." << endl;
        return;
    }
    cout << "[DEBUG] Arquivo criado com sucesso." << endl;

    escrever_informacoes_gerais(arquivo, rel);
    cout << "[DEBUG] Informacoes gerais escritas." << endl;

    escrever_produtos(arquivo, rel);
    cout << "[DEBUG] Produtos escritos." << endl;

    escrever_alertas_e_observacoes(arquivo, rel);
    cout << "[DEBUG] Alertas e observacoes escritas." << endl;

    escrever_analise_financeira(arquivo, rel);
    cout << "[DEBUG] Analise financeira escrita." << endl;

    escrever_assinatura(arquivo, rel);
    cout << "[DEBUG] Assinatura escrita." << endl;

    arquivo.close();
    cout << "[DEBUG] Relatorio gerado com sucesso." << endl;
}

// Funcao para escrever produtos (mantem alocacao dinâmica validada)
void escrever_produtos(ofstream &arquivo, const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    if (rel.objetos == nullptr)
    {
        cerr << "Erro: memoria dinâmica para produtos nao foi alocada." << endl;
        return;
    }

    // Cabecalho da secao
    arquivo << "2. Produtos em Estoque\n\n";
    arquivo << "=================================================================================================================================\n";
    arquivo << "| " << setw(3) << "Cod" << " | "
            << setw(20) << left << "Nome do Produto" << " | "
            << setw(12) << left << "Categoria" << " | "
            << setw(10) << left << "Data" << " | "
            << setw(10) << right << "Qtd. Ant." << " | "
            << setw(10) << right << "Qtd. Atual" << " | "
            << setw(12) << right << " Preço Custo" << " | "
            << setw(12) << right << "Valor Total" << " | "
            << setw(12) << left << "Reabastecer" << " |\n";
    arquivo << "=================================================================================================================================\n";

    for (int i = 0; i < rel.total_produtos; i++)
    {
        mercadorias &objetos = rel.objetos[i];

        rel.objetos[i].valor_total = calcular_valor_total(&rel.objetos[i], 1);

        // Determinar status de reabastecimento
        objetos.status_reabastecimento = determinar_status_reabastecimento(objetos.qtd_atual, 10, 20);

        arquivo << "| " << setw(3) << objetos.codigo << " | "
                << setw(20) << left << objetos.nome << " | "
                << setw(12) << left << objetos.categoria << " | "
                << setw(10) << left << objetos.data_cadastro << " | "
                << setw(10) << right << objetos.qtd_anterior << " | "
                << setw(10) << right << objetos.qtd_atual << " | "
                << setw(12) << right << fixed << setprecision(2) << objetos.preco_custo << " | "
                << setw(12) << right << fixed << setprecision(2) << objetos.valor_total << " | "
                << setw(12) << left << objetos.status_reabastecimento << " |\n";
    }
    arquivo << "=================================================================================================================================\n";

    arquivo << "\n\n=======================================================================================================================================================================\n";
    arquivo << "---------------------------------------- LEGENDA ----------------------------------------\n";
    arquivo << "Cod.            : Codigo do Produto\n";
    arquivo << "Nome do Produto : Identificacao do item no estoque\n";
    arquivo << "Categoria       : Tipo ou classificacao do produto\n";
    arquivo << "Data            : Data de cadastro ou ultima atualizacao do produto\n";
    arquivo << "Qtd. Ant.       : Quantidade existente anteriormente no estoque\n";
    arquivo << "Qtd. Atual      : Quantidade atual no estoque\n";
    arquivo << "Preco Custo     : Custo unitario de cada produto\n";
    arquivo << "Valor Total     : Produto da Qtd. Atual x Preco Custo\n";
    arquivo << "Reabastecer     : Status do reabastecimento, sendo:\n";
    arquivo << "                    - RC: Reabastecimento Critico\n";
    arquivo << "                    - RN: Reabastecimento Necessario\n";
    arquivo << "                    - NR: Nao Necessario Reabastecer\n";
    arquivo << "-----------------------------------------------------------------------------------------\n";
    arquivo << "===============================================================================================================\n\n\n";
}

// Funcao para escrever alertas e observacoes
void escrever_alertas_e_observacoes(ofstream &arquivo, const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Cabecalho da secao
    arquivo << "3. Alertas e Observacoes\n";
    arquivo << "================================================================================\n";

    // Produtos com estoque abaixo do minimo
    arquivo << "\n- Produtos com estoque abaixo do minimo:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    bool encontrou_criticos = false;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &o = rel.objetos[i];
        if (o.status_reabastecimento == "RC")
        {
            arquivo << "  * Cod: " << o.codigo << " - " << o.nome << "\n";
            encontrou_criticos = true;
        }
    }
    if (!encontrou_criticos)
    {
        arquivo << "  Nenhum produto com reabastecimento critico.\n";
    }

    // Produtos com excesso de estoque
    arquivo << "\n- Produtos com excesso de estoque:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    bool encontrou_excesso = false;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &p = rel.objetos[i];
        if (p.status_reabastecimento == "NR")
        {
            arquivo << "  * Cod: " << p.codigo << " - " << p.nome << "\n";
            encontrou_excesso = true;
        }
    }
    if (!encontrou_excesso)
    {
        arquivo << "  Nenhum produto com excesso de estoque.\n";
    }

    // Produtos com estoque zerado
    arquivo << "\n- Produtos com estoque zerado:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    bool encontrou_zerados = false;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &z = rel.objetos[i];
        if (z.qtd_atual == 0)
        {
            arquivo << "  * Cod: " << z.codigo << " - " << z.nome << "\n";
            encontrou_zerados = true;
        }
    }
    if (!encontrou_zerados)
    {
        arquivo << "  Nenhum produto com estoque zerado.\n";
    }

    // Produtos com preco unitario elevado
    arquivo << "\n- Produtos com preco unitario elevado:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    bool encontrou_precos = false;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &pv = rel.objetos[i];
        if (pv.preco_custo > 50.0)
        {
            arquivo << "  * Cod: " << pv.codigo << " - " << pv.nome
                    << " (Preco Unitario: R$ " << fixed << setprecision(2) << pv.preco_custo << ")\n";
            encontrou_precos = true;
        }
    }
    if (!encontrou_precos)
    {
        arquivo << "  Nenhum produto com preco elevado.\n";
    }

    // Produtos com alto valor total no estoque
    arquivo << "\n- Produtos com alto valor total:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    bool encontrou_valores = false;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &vt = rel.objetos[i];
        if (vt.valor_total > 1000.0)
        {
            arquivo << "  * Cod: " << vt.codigo << " - " << vt.nome
                    << " (Valor Total: R$ " << fixed << setprecision(2) << vt.valor_total << ")\n";
            encontrou_valores = true;
        }
    }
    if (!encontrou_valores)
    {
        arquivo << "  Nenhum produto com alto valor total.\n";
    }

    // Resumo de Alertas
    int produtos_criticos = 0, produtos_excesso = 0, produtos_zerados = 0;
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &m = rel.objetos[i];
        if (m.status_reabastecimento == "RC")
            produtos_criticos++;
        if (m.status_reabastecimento == "NR")
            produtos_excesso++;
        if (m.qtd_atual == 0)
            produtos_zerados++;
    }

    arquivo << "\nResumo de Alertas\n";
    arquivo << "================================================================================\n";
    arquivo << "  Total de produtos com reabastecimento critico : " << produtos_criticos << "\n";
    arquivo << "  Total de produtos com excesso de estoque      : " << produtos_excesso << "\n";
    arquivo << "  Total de produtos com estoque zerado          : " << produtos_zerados << "\n";
    arquivo << "================================================================================\n";
}

// Funcao para escrever analise financeira
void escrever_analise_financeira(ofstream &arquivo, const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Cabecalho da secao
    arquivo << "\n\n4. Analise Financeira\n";
    arquivo << "================================================================================\n";

    // Valor total do estoque
    arquivo << "Valor total do estoque: R$ " << fixed << setprecision(2) << rel.valor_total_estoque << "\n";

    // Detalhamento por Categoria
    arquivo << "\nDetalhamento por Categoria:\n";
    arquivo << "--------------------------------------------------------------------------------\n";

    unordered_map<string, double> soma_por_categoria;

    // Iterar pelos produtos e calcular o valor por categoria
    for (int i = 0; i < rel.total_produtos; i++)
    {
        const mercadorias &produto = rel.objetos[i];
        soma_por_categoria[produto.categoria] += produto.qtd_atual * produto.preco_custo;
    }

    for (const auto &par : soma_por_categoria)
    {
        arquivo << "  - " << par.first << ": R$ "
                << fixed << setprecision(2) << par.second << "\n";
    }

    // Observacoes Financeiras
    arquivo << "\nObservacoes Financeiras:\n";
    arquivo << "--------------------------------------------------------------------------------\n";
    arquivo << "- A analise considera os valores baseados no preco unitario dos produtos.\n";
    arquivo << "- As categorias representam a distribuicao financeira no estoque.\n";
    arquivo << "================================================================================\n\n\n";
}

// Funcao para escrever assinatura
void escrever_assinatura(ofstream &arquivo, const Relatorio &rel)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    string hora_atual = obter_hora_atual(); // Funcao que retorna a hora atual

    // Cabecalho da secao
    arquivo << "===============================================================================================================";
    arquivo << "\n5. Assinatura e Validacao\n";
    arquivo << "===============================================================================================================\n";

    // Declaracao de validade
    arquivo << "Declaro que as informacoes contidas neste relatorio estao de acordo com o levantamento realizado em "
            << rel.data << ".\n\n";

    // Assinatura e informacoes do responsavel
    arquivo << "Assinatura:__________________________\n";
    arquivo << "Nome      : " << rel.responsavel << "\n";
    arquivo << "Cargo     : Gerente de Estoque\n";
    arquivo << "Data      : " << rel.data << " às " << hora_atual << "\n";
    arquivo << "===============================================================================================================\n";
}

void salvarRelatorioProdutos(const Relatorio &relatorio, const char *nomeArquivo)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    ofstream arquivo(nomeArquivo, ios::binary); // Abrir o arquivo no modo binario
    if (!arquivo)
    {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
    }

    // Salvar numero total de produtos
    arquivo.write(reinterpret_cast<const char *>(&relatorio.total_produtos), sizeof(int));

    // Iterar sobre os produtos e salvar cada um
    for (int i = 0; i < relatorio.total_produtos; ++i)
    {
        const mercadorias &objetos = relatorio.objetos[i];

        // Salvar os dados de cada produto no arquivo
        arquivo.write(reinterpret_cast<const char *>(&objetos.codigo), sizeof(int));
        arquivo.write(objetos.nome, sizeof(objetos.nome));
        arquivo.write(objetos.categoria, sizeof(objetos.categoria));
        arquivo.write(reinterpret_cast<const char *>(&objetos.qtd_anterior), sizeof(int));
        arquivo.write(reinterpret_cast<const char *>(&objetos.qtd_atual), sizeof(int));
        arquivo.write(reinterpret_cast<const char *>(&objetos.preco_custo), sizeof(float));
        arquivo.write(reinterpret_cast<const char *>(&objetos.valor_total), sizeof(float));

        // Salvar o status de reabastecimento como string
        const char *status = objetos.status_reabastecimento.c_str();
        arquivo.write(status, objetos.status_reabastecimento.size());
        const char *data = objetos.data_cadastro.c_str();
        arquivo.write(data, objetos.data_cadastro.size());
    }

    arquivo.close();
    cout << "Relatorio salvo com sucesso!" << endl;
}

void carregarRelatorio(Relatorio *relatorio, const char *nomeArquivo)
{
    setlocale(LC_ALL, "Portuguese");

    if (!relatorio)
    {
        std::cerr << "Erro: Relatório inválido (null)!" << std::endl;
        return;
    }

    const char *arquivoDadosAnteriores = "dados_anteriores.dat";
    carregarDadosAnteriores(arquivoDadosAnteriores); // Carregar dados anteriores

    std::ifstream arquivo(nomeArquivo, std::ios::binary);
    if (!arquivo)
    {
        std::cerr << "Erro ao abrir o arquivo binário: " << nomeArquivo << std::endl;
        relatorio->total_produtos = 0;
        relatorio->objetos = nullptr;
        relatorio->valor_total_estoque = 0.0;
        return;
    }

    int quantidade_produtos;
    arquivo.read(reinterpret_cast<char *>(&quantidade_produtos), sizeof(int));

    if (arquivo.fail() || quantidade_produtos <= 0)
    {
        std::cerr << "Arquivo vazio ou corrompido." << std::endl;
        arquivo.close();
        relatorio->total_produtos = 0;
        relatorio->objetos = nullptr;
        relatorio->valor_total_estoque = 0.0;
        return;
    }

    relatorio->total_produtos = quantidade_produtos;
    relatorio->objetos = new mercadorias[quantidade_produtos];
    relatorio->valor_total_estoque = 0.0;

    Produto produto_temp;
    for (int i = 0; i < quantidade_produtos; ++i)
    {
        arquivo.read(reinterpret_cast<char *>(&produto_temp), sizeof(Produto));

        if (arquivo.fail())
        {
            std::cerr << "Erro ao ler o produto #" << i + 1 << " do arquivo." << std::endl;
            continue;
        }

        mercadorias &objeto = relatorio->objetos[i];
        objeto.codigo = produto_temp.id;

        strncpy(objeto.nome, produto_temp.nome, sizeof(objeto.nome) - 1);
        objeto.nome[sizeof(objeto.nome) - 1] = '\0';

        strncpy(objeto.categoria, produto_temp.categoria, sizeof(objeto.categoria) - 1);
        objeto.categoria[sizeof(objeto.categoria) - 1] = '\0';

        objeto.qtd_atual = produto_temp.Quantidade;
        objeto.preco_custo = produto_temp.preco;
        objeto.valor_total = produto_temp.Quantidade * produto_temp.preco;

        objeto.data_cadastro = std::string(produto_temp.dia) + "/" +
                               std::string(produto_temp.mes) + "/" +
                               std::string(produto_temp.ano);

        if (strlen(produto_temp.dia) != 2 || strlen(produto_temp.mes) != 2 || strlen(produto_temp.ano) != 4)
        {
            objeto.data_cadastro = "Data Inválida";
        }

        if (objeto.qtd_atual < 10)
            objeto.status_reabastecimento = "RC";
        else if (objeto.qtd_atual < 20)
            objeto.status_reabastecimento = "RN";
        else
            objeto.status_reabastecimento = "NR";

        relatorio->valor_total_estoque += objeto.valor_total;

        verificarQtdAnterior(objeto);
    }

    arquivo.close();
    salvarDadosAnteriores(arquivoDadosAnteriores);
    std::cout << "Relatório carregado e salvo com sucesso!" << std::endl;
}
