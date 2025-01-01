#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    int _id;                                        // Atributos comuns aos usuários          
    std::string _nome;           
    std::string _email;
    static int totalUsuarios;                       // Número total de usuários no sistema
    virtual void visualizarRelatorio() = 0;         // Método polimórfico para visualização de relatório

private:
    std::string _tipoUsuario;                       // Atributos privados 
    std::string _senha;                             // Senha do usuário (não deve ser exposta)

public:
    // Construtor e Destrutor
    Usuario(int id, const std::string& nome, const std::string& email, 
            const std::string& tipoUsuario, const std::string& senha);
    virtual ~Usuario() = default;

    // Getters
    int getId() const;                              // Retorna o ID (somente leitura)
    std::string getNome() const;                 
    std::string getEmail() const;                   
    std::string getTipoUsuario() const;             // Retorna o tipo de usuário (gestor, vendedor, etc.)

    // Setters
    void setNome(const std::string& nome);   
    void setEmail(const std::string& email); 

    // Métodos relacionados à segurança
    bool verificarSenha(const std::string& senha);              // Verifica se a senha está correta

    void realizarLogin();                                       // Metodos relacionados a parte visual  
    void acessarInterface();
};
#endif