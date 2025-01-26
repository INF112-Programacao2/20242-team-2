#include "classeNegociacao.hpp"
#include "classeArea_Plantio.hpp"
#include "classeLote.hpp"
#include "classeSemente.hpp"
#include "Usuario.hpp"
#include "Vendedor.hpp"
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"


#include <iostream>
#include <cstdlib> // Necessário para usar system()


/*
int main() {
   // Texto que você quer que seja falado
   std::string texto = "solo: arenoso, clima:tropical";


   // Usando o comando system para chamar o espeak e falar o texto
   std::string comando = "espeak -v pt \"" + texto + "\"";
   system(comando.c_str());


   return 0;
}
*/




int main(){
    //Realizando login
    Usuario *usuario = usuario->realizarLogin();
    usuario->acessarInterface();
    
   return 0;
}
 
