#include <iostream>
#include <string>
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
}
