#include <iostream>
#include <locale>
#include "gconio.h"
#include "utilitarios.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    gerador_relatorio();

    return 0;
}
