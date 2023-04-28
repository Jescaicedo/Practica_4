#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <enrutador.h>
using namespace std;
void desdearchivo(map<string,Enrutador>&);

int main()
{
    int mov=0;
    cout<<"Bienvenido al modelador de red"<<endl;
    bool ban=true;
    map<string,Enrutador> red;
    while(ban){
        cout<<"Ingrese 1 para agregar enrutadores"<<endl<<"2 para cargar enrutadores del archivo"<<endl<<" y 3 para cerrar programa: ";
        cin>>mov;
        while(mov<1 || mov>3){
            cout<<"Ingrese un movimiento valido: ";
            cin>>mov;
        }
        if(mov==1){

        }
        else if(mov==2){
            desdearchivo(red);

        }
    }
}

void desdearchivo(map<string,Enrutador>& red)
{
    vector<string> venruta;
    ifstream arch;
    Enrutador er;
    string linea, enr;
    int cont=0;
    arch.open("Datosdeenrutadores.txt");
    getline(arch,linea);
    while(linea[cont]!='|'){
        cont+=1;
    }
    cont+=2;
    while(linea[cont]!='\r' && linea[cont]!='-'){
        while(linea[cont]!='|'){
            if(linea[cont]!=' '){
                enr.push_back(linea[cont]);
            }
            cont+=1;
        }
        venruta.push_back(enr);
        enr="";
        cont+=2;
    }
    cont=0;
    enr="";
    while (arch.good()){
        getline(arch,linea);
        if(linea[cont]!=' ' && linea[cont]!='-'){
            while(linea[cont]!=' '){
                enr.push_back(linea[cont]);
                cont+=1;
            }
            cont=0;
            er.setConexiones(linea,venruta);
            red[enr]=er;
            enr="";

        }
    }
    arch.close();
}
