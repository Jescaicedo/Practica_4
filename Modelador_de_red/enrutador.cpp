#include "enrutador.h"
#include <string>
#include <map>


map<string, int> Enrutador::getConexiones() const
{
    return conexiones;
}

void Enrutador::setConexiones(string linea, vector<string> enrutadores)
{
    int cont=0, conte=0, numero=0;
    map<string,int> auxconex;
    string snum;
    while(linea[cont]!='|'){
        cont+=1;
    }
    cont+=2;
    while(linea[cont]!='\r' && linea[cont]!='-'){
        while(linea[cont]!='|'){
            if(linea[cont]!=' '){
                snum+=linea[cont];
            }
            cont+=1;
        }
        cont+=2;
        if(snum!=""){
            numero=stoi(snum);
            auxconex[enrutadores[conte]]=numero;
        }
        conte+=1;
        snum="";
    }
    conexiones=auxconex;

}

Enrutador::Enrutador()
{

}

