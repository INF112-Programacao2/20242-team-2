#ifndef GESTOR_HPP
#define GESTOR_HPP

#include <vector>
#include "Usuario.hpp"
#include "classeSemente.hpp"
#include "classeLote.hpp"

class Gestor: public Usuario{
private:
    std::vector<Semente> sementesRegistradas;       //vetor de semente registradas
    std::vector<Lote> lotesRegistrados;             //vetor de lotes registrados

    //metodos para sementes
    void registrarSemente();                        //ok
    void salvarSemente(Semente &semente);     //ok
    void excluirSemente();                          //ok

    //metodos para lote
    void registrarLote();                           //ok
    void salvarLote(const Lote &lote);              //ok
    void excluirLote();                             //ok
   
    // metodos para cadastro de usuarios
    void cadastrarUsuario();                        //ok
    void listarUsuarios();                          //ok
    void excluirUsuario();                          //ok


    void atividadesGestor(int opcao_menu);     //necessario para o menu -julia

    public:

    virtual int acessarInterface()override;   //abre o menu dos gestores -julia

};
#endif