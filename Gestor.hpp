#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "Usuario.hpp"

class Gestor: public Usuario{
public: 
    //metodos para sementes e lotes
    void registrarSemente();
    void registrarLote();
   

    // metodos para cadastro de usuarios
    void cadastrarUsuario();
    void alterarSenhaUsuario();
    void associarId();                  // Atribui um ID ao usuário
    void excluirUsuario();
};
#endif