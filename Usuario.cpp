#include <iostream>
#include <string>
#include <fstream>
#include "Usuario.hpp"
#include "Gestor.hpp"

Usuario:: Usuario(int id, const std::string& nome, const std::string& email, const std::string& tipoUsuario, 
const std::string& senha): _id(id), _nome(nome), _email(email), _tipoUsuario(tipoUsuario), _senha(senha){}

Usuario::~Usuario(){}
int Usuario::totalUsuarios = 0;

//getters
int Usuario::getId() const{return _id;}
std::string Usuario::getNome() const{return _nome;}
std::string Usuario::getEmail() const{return _email;}
std::string Usuario::getTipoUsuario() const{return _tipoUsuario;}

//setters
void Usuario::setNome(const std::string& nome){_nome = nome;}
void Usuario::setEmail(const std::string& email){_email = email;}

void Usuario::realizarLogin(){
    std::ifstream fin("usuario.txt");
      if (!fin.is_open()) {
        std::cerr << "Erro ao abrir o arquivo usuarios.txt" << std::endl;
        return;
    }
    
    std::string emailInput, senhaInput;
    std::cout<< "insira o email: ";
    std::getline(std::cin, emailInput);
    std::cout<< "insira a senha: ";
    std::getline(std::cin, senhaInput);

    std::string linha, acharEmail, acharSenha;
    bool usuarioEncontrado = false;

    while (std::getline(fin, linha)) {
        // Leitura do ID (ignorado)
        std::getline(fin, linha); // Nome (ignorado)
        std::getline(fin, acharEmail); // Email
        std::getline(fin, linha); // Tipo de usuário (ignorado)
        std::getline(fin, acharSenha); // Senha

        // Verifica se email e senha coincidem
        if (acharEmail == emailInput && acharSenha == senhaInput) {
            usuarioEncontrado = true;
            break;
        }
    }
    fin.close();

    if (usuarioEncontrado) {
        std::cout << "Login realizado com sucesso!" << std::endl;
        // Aqui você pode chamar o método para acessar a interface, dependendo do tipo de usuário.
        acessarInterface();
    } else {
        std::cout << "Email ou senha incorretos!" << std::endl;
    }
}

Usuario::Usuario() : _id(0), _nome(""), _email(""), _tipoUsuario(""), _senha("") {}

int Usuario::acessarInterface(){
   //aqui sera feito a pagina de login - pedro

   //qualquer coisa aqui so pra ver funcionar:
   int x;
   std::cout<<"1 pra gestor, 2 pra vendedor,3 pra analista\n";       //TESTE!!!
   std::cin>>x;
   return x;

}


void Usuario::visualizarRelatorio(){
    //metodo a ser implementado futuramente
}

