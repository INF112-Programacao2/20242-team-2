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
    Usuario *usuario=new Usuario();
    int tipo_de_usuario;
    tipo_de_usuario=usuario->acessarInterface();     //realiza o login e retorna um inteiro pra identificar o tipo de usuario (PODE MUDAR SE QUISER!!!)
    //----------------------------------------------------//

    //selecionando menu referente a cada tipo de usuario

    if(tipo_de_usuario==1){
        delete usuario;
        usuario=new Gestor();
    }
    else if(tipo_de_usuario==2){
        delete usuario;
        usuario=new Vendedor();
    }
    else if(tipo_de_usuario==3){
        delete usuario;
        usuario=new Analista();
    }
    else{
    //tratar excessao
   }

   // cada usuario deve levar a um acessarInterface() e a um atividade() personalizados
   int menu_selecionado;
   menu_selecionado=usuario->acessarInterface();   //polimorfismo





  


  
   return 0;
}

