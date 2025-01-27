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

int main(){

    //Realizando login
    Usuario *usuario = usuario->realizarLogin();
    if(usuario!=nullptr)
    usuario->acessarInterface();
    delete usuario;
    
   return 0;
}
 
