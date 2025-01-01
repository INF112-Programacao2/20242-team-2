#include <fstream>
#include <iostream>
#include <string>
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

//alteracoes a serem feitas: criar metodo para coleta, metodo para processar os dados, metodo para gravar.
//so depois chamar cadastrarUsuario. Melhor para manutencao
//trocar o formato para JSON

void Gestor::cadastrarUsuario(){
    std::string nome, email, tipo, senha;
    
    std::cout<<"Insira o nome do usuario: ";
    std::getline(std::cin, nome);
    std::cout<<"Insira o email do usuario: ";
    std::getline(std::cin, email);
    std::cout<<"Insira o tipo de usuario: ";
    std::getline(std::cin, tipo);
    std::cout<<"Insira a nova senha do usuario: ";
    std::getline(std::cin, senha);

    int id = ++totalUsuarios;
    std::ofstream fout("usuarios.txt");

    if(!fout.is_open()){
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    try {
        fout << id << std::endl 
             << nome << std::endl 
             << tipo << std::endl 
             << senha << std::endl; 
        fout.close();
        std::cout << "Usuario cadastrado com sucesso!" << std::endl;
    }
    catch(const std::ios_base::failure &e){
        std::cerr<< "Erro durante escrita do arquivo" << e.what() << std::endl;
    } 
    catch(...){
        std::cerr << "Um erro inesperado ocorreu durante o cadastro:" << std::endl;
    }
}