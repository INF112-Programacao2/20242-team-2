#include "classeNegociacao.hpp"
#include "classeArea_Plantio.hpp"
#include "classeLote.hpp"
#include "classeSemente.hpp"
#include <iostream>


#include "classeNegociacao.hpp"
#include "classeArea_Plantio.hpp"
#include "classeLote.hpp"
#include "classeSemente.hpp"
#include "Usuario.hpp"
#include "Vendedor.hpp"
#include "Gestor.hpp"
#include "Vendedor.hpp"


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
    //realizar login
   Usuario *usuario=new Usuario();
   int tipo_de_usuario;
   tipo_de_usuario=usuario->acessarInterface();
   if(tipo_de_usuario==1){
       delete usuario;
       usuario=new Gestor();
       usuario->acessarInterface();
   }
   else if(tipo_de_usuario==2){
       //... mesmo raciocinio mas para o vendedor
   }




  


  
   return 0;
}

