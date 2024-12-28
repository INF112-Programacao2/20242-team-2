#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    int _id;                     // Informacoes usuario
    std::string _nome;           
    std::string _email;          

    void cadastrarUsuario(); 
    void visualizarRelatorio();  // Exibe relatórios (baseado no tipo de usuario) -> talvez nao seja polimorfico

    //virtual void visualizarRelatorio();
private:           
    std::string _usuario;        // Tipo de usuário: "gestor", "vendedor", "analista"
    std::string _senha;     
    //int _nivel_acesso;     

public:
    void realizarLogin();        
    void acessarInterface();     // Acessa a interface apropriada ao tipo de usuário
};
#endif 

//O _nivel_acesso eh um atributo inutil -> qualquer verificacao de acesso pode ser feito com _usuario 