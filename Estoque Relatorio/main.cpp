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

    // Verificar se h� produtos carregados
    if (relatorio->total_produtos == 0)
    {
        cout << "Nenhum produto encontrado no arquivo. Verifique se o arquivo existe e tem o formato correto." << endl;
        delete relatorio; // Liberar mem�ria corretamente
        return 1;
    }

    preencher_campos_relatorio(*relatorio); // Passando como refer�ncia
    gerar_relatorio(*relatorio);            // Passando como refer�ncia

    cout << "Relat�rio gerado com sucesso!" << endl;

    delete[] relatorio->objetos; // Liberar array din�mico
    delete relatorio;            // Liberar relat�rio corretamente

    return 0;
}
