#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

void Gestor::cadastrarUsuario() {
    std::string nome, email, tipo, senha;

    // Solicita as informações do usuário
    std::cout << "Insira o nome do usuario: ";
    std::getline(std::cin, nome);
    std::cout << "Insira o email do usuario: ";
    std::getline(std::cin, email);

    // Valida o email
    if (email.find('@') == std::string::npos) {
        std::cerr << "Erro: O email deve conter o caractere '@'!" << std::endl;
        return;
    }

    // Verifica se o email já existe no arquivo
    std::ifstream fin("usuarios.txt");
    if(!fin.is_open()){
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::string linha, emailExistente;
    while (std::getline(fin, linha)) {
        std::getline(fin, linha); // Pula nome
        std::getline(fin, emailExistente); // Lê email
        if (emailExistente == email) {
            std::cerr << "Erro: Este email já está cadastrado!" << std::endl;
            fin.close();
            return;
        }
        std::getline(fin, linha); // Pula tipo de usuário
        std::getline(fin, linha); // Pula senha
    }
    fin.close();

    // Solicita o tipo e senha
    std::cout << "Insira o tipo de usuario: ";
    std::getline(std::cin, tipo);
    std::cout << "Insira a nova senha do usuario: ";
    std::getline(std::cin, senha);

    // Valida a senha
    if (senha.length() < 5) {
        std::cerr << "Erro: A senha deve conter pelo menos 5 caracteres!" << std::endl;
        return;
    }

    // Atualiza ID e grava os dados no arquivo
    int id = ++totalUsuarios;
    std::ofstream fout("usuarios.txt", std::ios::app); // Modo de adição
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    fout << id << std::endl
         << nome << std::endl
         << email << std::endl
         << tipo << std::endl
         << senha << std::endl;
    fout.close();

    std::cout << "Usuario cadastrado com sucesso!" << std::endl;
}

void Gestor::listarUsuarios() {
    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::string linha;
    std::cout << "Lista de usuarios cadastrados:" << std::endl;
    while (std::getline(fin, linha)) {
        int id = std::stoi(linha); // Primeiro, lê o ID
        std::getline(fin, linha);
        std::string nome = linha; // Depois, lê o nome
        std::getline(fin, linha);
        std::string tipo = linha; // Depois, lê o tipo
        std::getline(fin, linha);
        std::string senha = linha; // Depois, lê a senha

        // Exibe os dados de forma organizada
        std::cout << "ID: " << id 
                  << ", Nome: " << nome 
                  << ", Tipo: " << tipo     
                  << std::endl;
    }
    fin.close();
}

void Gestor::excluirUsuario() {
    listarUsuarios();

    int idParaExcluir;
    std::cout << std::endl << "Insira o ID do usuario que deseja excluir: ";
    std::cin >> idParaExcluir;
    std::cin.ignore(); // Limpa o buffer para evitar problemas ao ler strings depois

    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::vector<std::string> usuariosRestantes;
    std::string linha;
    bool usuarioEncontrado = false;

    // Lê os usuários e armazena aqueles que não devem ser excluídos
    while (std::getline(fin, linha)) {
        std::stringstream ss(linha);
        int idAtual;
        ss >> idAtual;

        // Verifica se este é o ID a ser excluído
        if (idAtual == idParaExcluir) {
            usuarioEncontrado = true;
            // Ignora as próximas 3 linhas (nome, tipo, senha)
            std::getline(fin, linha); // Nome
            std::getline(fin, linha); // Tipo
            std::getline(fin, linha); // Senha
        } else {
            // Mantém os dados do usuário atual
            usuariosRestantes.push_back(std::to_string(idAtual));
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Nome
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Tipo
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Senha
        }
    }
    fin.close();

    if (!usuarioEncontrado) {
        std::cout << "Usuario com ID " << idParaExcluir << " nao encontrado." << std::endl;
        return;
    }

    // Reescreve o arquivo com os usuários restantes
    std::ofstream fout("usuarios.txt");
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt para escrita");
    }

    for (size_t i = 0; i < usuariosRestantes.size(); i++) {
        fout << usuariosRestantes[i] << std::endl;
    }
    fout.close();

    std::cout << "Usuario com ID " << idParaExcluir << " excluido com sucesso." << std::endl;
}

void Gestor::visualizarRelatorio(){
    // Metodo a ser implementado
}