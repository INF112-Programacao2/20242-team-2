#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    int _id;                                        // Atributos comuns aos usuários          
    std::string _nome;           
    std::string _email;
    static int totalUsuarios;                       // Número total de usuários no sistema
    virtual void gerarRelatorio()=0;  
                        

private:
    std::string _tipoUsuario;                       // Atributos privados 
    std::string _senha;                             // Senha do usuário (não deve ser exposta)

public:
    // Construtor e Destrutor
    Usuario();
    Usuario(int id, const std::string& nome, const std::string& email,  //ok
            const std::string& tipoUsuario, const std::string& senha);
    virtual ~Usuario();                                       //defalt?                         

    // Getters
    int getId() const;                      //ok                    // Retorna o ID (somente leitura)
    std::string getNome() const;            //ok              
    std::string getEmail() const;           //ok              
    std::string getTipoUsuario() const;     //ok            // Retorna o tipo de usuário (gestor, vendedor, etc.)

    // Setters
    void setNome(const std::string& nome);      //ok
    void setEmail(const std::string& email);    //ok

    // Métodos relacionados à segurança
    void realizarLogin();       //ok                                 // Metodos relacionados a parte visual  
    virtual int acessarInterface()=0;    
    
};
#endif
