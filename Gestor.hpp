#ifndef GESTOR_HPP
#define GESTOR_HPP

#include<vector>
#include "Usuario.hpp"
#include "classeSemente.hpp"
#include "classeLote.hpp"

class Gestor: public Usuario{
private:
    std::vector<Semente> sementesRegistradas;       //vetor de semente registradas
    std::vector<Lote> lotesRegistrados;             // Vetor de lotes registrados

    void salvarSemente(const Semente &semente);     //ok
    void salvarLote(const Lote &lote);
public: 
    //metodos para sementes e lotes
    void registrarSemente();        //ok
    void excluirSemente();          //ok
    void registrarLote();           //ok
    void excluirLote();
   
    // metodos para cadastro de usuarios
    void cadastrarUsuario();        //ok
    void listarUsuarios();          //ok
    void excluirUsuario();          //ok
};
#endif