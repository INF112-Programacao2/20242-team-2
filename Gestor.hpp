#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "Usuario.hpp"

class Gestor: public Usuario{
public: 
    //metodos para sementes e lotes
    void registrarSemente();
    void registrarLote();
    void visualizarRelatorio() override;
   
    // metodos para cadastro de usuarios
    void cadastrarUsuario();        //ok
    void listarUsuarios();          //ok
    void excluirUsuario();          //ok
};
#endif