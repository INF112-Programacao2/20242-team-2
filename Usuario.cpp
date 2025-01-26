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

    Usuario* usuario = nullptr;
    std::string emailInput, senhaInput;
    bool loginBemSucedido = false;

    while (!loginBemSucedido) {
        std::cout << "Insira o email: ";
        std::getline(std::cin >> std::ws, emailInput); // Remove espaços em branco iniciais

        std::cout << "Insira a senha: ";
        std::getline(std::cin, senhaInput);

        // Verifica se as credenciais inseridas são as do gestor padrão
        if (emailInput == "gestor@empresa.com" && senhaInput == "senha123") {
            std::cout << "Login como Gestor padrão realizado com sucesso!" << std::endl;
            usuario = new Gestor();
            loginBemSucedido = true;
            acessarInterface();
            break;
        }

        std::string linha, acharEmail, acharSenha, tipoUsuario, nome;
        bool usuarioEncontrado = false;

        // Reiniciar a posição do arquivo para recomeçar a leitura
        fin.clear();
        fin.seekg(0, std::ios::beg);

        while (std::getline(fin, nome) &&       
               std::getline(fin, acharEmail) && 
               std::getline(fin, tipoUsuario) && 
               std::getline(fin, acharSenha)) {  

            if (acharEmail == emailInput && acharSenha == senhaInput) {
                usuarioEncontrado = true;
                loginBemSucedido = true;

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

        if (!usuarioEncontrado) {
            std::cout << "Email ou senha incorretos! Tente novamente.\n";
        }
    }
    fin.close();
    return usuario;
}


  
Usuario::Usuario() : _id(0), _nome(""), _email(""), _tipoUsuario(""), _senha("") {}




