#include <iostream>
#include <locale>
#include "gconio.h"
#include "utilitarios.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Relatorio *relatorio = new Relatorio; // Inicializa Relatorio corretamente
    const char *nomeArquivo = "Produtos_DB.dat";

    cout << "Carregando dados..." << endl;
    carregarRelatorio(relatorio, nomeArquivo);

    // Verificar se há produtos carregados
    if (relatorio->total_produtos == 0)
    {
        cout << "Nenhum produto encontrado no arquivo. Verifique se o arquivo existe e tem o formato correto." << endl;
        delete relatorio; // Liberar memória corretamente
        return 1;
    }

    preencher_campos_relatorio(*relatorio); // Passando como referência
    gerar_relatorio(*relatorio);            // Passando como referência

    cout << "Relatório gerado com sucesso!" << endl;

    delete[] relatorio->objetos; // Liberar array dinâmico
    delete relatorio;            // Liberar relatório corretamente

    return 0;
}
