#include <iostream>
#include <string>
#include <fstream>
#include "Usuario.hpp"
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

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

Usuario* Usuario::realizarLogin() {
    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        std::cerr << "Erro ao abrir o arquivo usuarios.txt" << std::endl;
        return nullptr;
    }

    Usuario *usuario;

    std::string emailInput, senhaInput;
    std::cout << "Insira o email: ";
    std::getline(std::cin, emailInput);
    std::cout << "Insira a senha: ";
    std::getline(std::cin, senhaInput);

    // Verifica se as credenciais inseridas são as do gestor padrão
    if (emailInput == "gestor@empresa.com" && senhaInput == "senha123") {
        std::cout << "Login como Gestor padrão realizado com sucesso!" << std::endl;
        acessarInterface(); // Acessa a interface do gestor diretamente
        fin.close();
        usuario=new Gestor();
        return usuario;
    }

    std::string linha, acharEmail, acharSenha, tipoUsuario, nome;
    bool usuarioEncontrado = false;

    while (std::getline(fin, nome) &&       // Lê o nome
           std::getline(fin, acharEmail) && // Lê o email
           std::getline(fin, tipoUsuario) && // Lê o tipo de usuário
           std::getline(fin, acharSenha)) {  // Lê a senha

        // Verifica se email e senha coincidem com algum usuário registrado
        if (acharEmail == emailInput && acharSenha == senhaInput) {
            usuarioEncontrado = true;

            if (tipoUsuario == "Gestor") {
                usuario = new Gestor();
                std::cout << "Login como Gestor realizado com sucesso!" << std::endl;
            }
            else if (tipoUsuario == "Vendedor") {
                usuario = new Vendedor();
                std::cout << "Login como Vendedor realizado com sucesso!" << std::endl;
            }
            else if (tipoUsuario == "Analista") {
                usuario = new Analista();
                std::cout << "Login como Analista realizado com sucesso!" << std::endl;
            }
            break;
        }
    }
    fin.close();
    return usuario;

    if (!usuarioEncontrado) {
        std::cout << "Email ou senha incorretos!" << std::endl;
    }
}

  
Usuario::Usuario() : _id(0), _nome(""), _email(""), _tipoUsuario(""), _senha("") {}




