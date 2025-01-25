#ifndef CLASSE_LOTE_HPP
#define CLASSE_LOTE_HPP

#include <iostream>
#include <string>
#include "classeSemente.hpp"
#include "classeLote.hpp"
#include <fstream>

class Lote{

    private:
        //atributos:
    
        int _id_lote; //identificador unico do lote de sementes
        int _id_sementeAssociada;
        std::string _nome_cientifico; //nome cientifico da semente
        std::string _geneIntroduzido;
        std::string _metodo_producao; 
        std::string _data_producao;  //formato DD/MM/AAAA
        std::string _pais_origem;
        int _quantidade_disponivel;  //kg de sementes disponiveis no lote
        float _preco_estimado;
        std::string _statusDisponibilidade;  //em estoque,vendido ou plantado


    public: 
    //metodos:

        Lote();  //construtor
        Lote(int id_semente);             //katrine provavelmente vai ter que adaptar o codigo quando eu apagar isso
        ~Lote(); //destrutor              //vazio por em quanto!!
    
        //funcao que vai pro vendedor
        void consumirSementes(int _id_lote,int quantidadeConsumida); //diminuir ou zerar a quantidade disponivel no lote
    
    
        //-----------------------gets e sets----------------//           //ok
        int getIdLote() const;
        void setIdLote(int idLote);
    
        int getIdSementeAssociada() const;
        void setIdSementeAssociada(int idSementeAssociada);
    
        std::string getNomeCientifico() const;
        void setNomeCientifico(const std::string& nomeCientifico);
    
        std::string getGeneIntroduzido() const;
        void setGeneIntroduzido(const std::string& geneIntroduzido);
    
        std::string getMetodoProducao() const;
        void setMetodoProducao(const std::string& metodoProducao);
    
        std::string getDataProducao() const;
        void setDataProducao(const std::string& dataProducao);
    
        std::string getPaisOrigem() const;
        void setPaisOrigem(const std::string& paisOrigem);
    
        int getQuantidadeDisponivel() const;
        void setQuantidadeDisponivel(int quantidadeDisponivel);
    
        float getPrecoEstimado() const;
        void setPrecoEstimado(float precoEstimado);
    
        std::string getStatusDisponibilidade() const;
        void setStatusDisponibilidade(const std::string& statusDisponibilidade);
};
#endif
