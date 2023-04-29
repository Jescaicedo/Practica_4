#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <enrutador.h>
using namespace std;
void desdearchivo(map<string,Enrutador>&);
void agregarenrutador(map<string,Enrutador>&);
void eliminarenrutador(map<string,Enrutador>&);

int main()
{
    int mov=0;
    cout<<"Bienvenido al modelador de red"<<endl;
    bool ban=true;
    map<string,Enrutador> red;
    cout<<"Desea cargar enrutadores del archivo, 1 para si, 2 para no: ";
    cin>>mov;
    while(mov<1 || mov>2){
        cout<<"Ingrese un movimiento valido: ";
        cin>>mov;
    }
    if(mov==1){
        desdearchivo(red);
    }
    while(ban){
        cout<<"Ingrese 1 para agregar enrutadores"<<endl<<"2 para eliminar enrutador"<<endl<<"3 para cerrar programa: ";
        cin>>mov;
        while(mov<1 || mov>3){
            cout<<"Ingrese un movimiento valido: ";
            cin>>mov;
        }
        if(mov==1){
            agregarenrutador(red);
        }
        else if(mov==2){
            eliminarenrutador(red);
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

void agregarenrutador(map<string,Enrutador>& red)
{
    string enr, cenr;
    bool ban=true, existe;
    int costo=0, mov=0;
    Enrutador enrutador;
    map<string,int> conex;
    cout<<"Ingrese el nombre del enrutador: ";
    cin>>enr;
    while(red.count(enr)>0){
        cout<<"Este enrutador ya existe"<<endl;
        cout<<"Ingrese el nombre del enrutador: ";
        cin>>enr;
    }
    cout<<"Ahora ingresaras sus conexiones"<<endl;
    while(ban){
        cout<<"Ingrese el nombre del enrutador: ";
        cin>>cenr;
        if(conex.count(cenr)==0){
            if(red.count(cenr)>0){
                enrutador=red[cenr];
                existe=enrutador.existeconexion(enr, &costo);
                if(existe){
                    cout<<"Costo encontrado"<<endl;
                }
                else{
                    cout<<"Ingrese el costo de la conexion: ";
                    cin>>costo;
                    while(costo<0){
                        cout<<"Ingrese un costo valido: ";
                        cin>>costo;
                    }
                    enrutador.enrutadorappend(enr,costo);
                    red[cenr]=enrutador;
                }
            }
            else{
                cout<<"Ingrese el costo de la conexion: ";
                cin>>costo;
                while(costo<0){
                    cout<<"Ingrese un costo valido: ";
                    cin>>costo;
                }
            }
            conex[cenr]=costo;
        }
        else{
            cout<<"La conexion ya existe"<<endl;
        }
        cout<<"Desea ingresar más conexiones 1 para si, 2 para no: ";
        cin>>mov;
        while(mov<1 || mov>2){
            cout<<"Ingrese un movimiento valido: ";
            cin>>mov;
        }
        if(mov==2){
            ban=false;
        }
    }
    enrutador.setConexiones(conex);
    red[enr]=enrutador;

}

void eliminarenrutador(map<string,Enrutador>& red)
{
    string enr, auxe;
    Enrutador enrutador;
    cout<<"Ingrese el nombre del enrutador: ";
    cin>>enr;
    if(red.count(enr)>0){
        red.erase(enr);
        auto inicio = red.begin();
        auto fin = red.end();
        while (inicio != fin){
            auxe=inicio->first;
            enrutador=inicio->second;
            enrutador.eliminarconexion(enr);
            red[auxe]=enrutador;
            inicio++;
        }
    }
    else{
        cout<<"El enrutador no existe"<<endl;
    }

}
