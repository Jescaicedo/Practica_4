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
void llenarvnenrutadores(map<string,Enrutador>, vector<vector<string>>&, vector<string>&);
void llenarmccostos(vector<vector<int>>&, map<string,Enrutador>, vector<string>);
void algfloydwarshall(vector<vector<int>>&, vector<vector<string>>&);
void encontrarcostos(vector<string>, vector<vector<int>>);
void encontrarcamino(vector<string>,vector<vector<string>>, vector<vector<int>>);


int main()
{
    int mov=0;
    vector<vector<string>> mcnombre;
    vector<vector<int>> mccostos;
    vector<string> nombrese;
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
        cout<<"Ingrese: "<<endl<<"1. para agregar enrutadores"<<endl<<"2. para eliminar enrutador"<<endl<<"3. para saber cual es el costo de un enrutador a otro"<<endl<<"4. para saber el camino mas eficiente de un enrutador a otro"<<endl<<"5. para cerrar el programa: ";
        cin>>mov;
        while(mov<1 || mov>5){
            cout<<"Ingrese un movimiento valido: ";
            cin>>mov;
        }
        if(mov==1){
            agregarenrutador(red);
        }
        else if(mov==2){
            eliminarenrutador(red);
        }
        else if(mov==3 || mov==4){
            llenarvnenrutadores(red,mcnombre, nombrese);
            llenarmccostos(mccostos,red,nombrese);
            algfloydwarshall(mccostos,mcnombre);
            if(mov==3){
                encontrarcostos(nombrese,mccostos);
            }
            else{
                encontrarcamino(nombrese,mcnombre, mccostos);
            }
            mccostos.clear();
            mcnombre.clear();
            nombrese.clear();
        }
        else{
            ban=false;
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
                    while(costo<=0){
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
                while(costo<=0){
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

void llenarvnenrutadores(map<string,Enrutador> red , vector<vector<string>>& mcn, vector<string>& nombres)
{
    string enr;
    auto inicio = red.begin();
    auto fin = red.end();
    while (inicio != fin){
        enr=inicio->first;
        nombres.push_back(enr);
        inicio++;
    }
    int lim=nombres.size();
    for(int i=0; i<lim; i++){
        mcn.push_back(nombres);
    }
}

void llenarmccostos(vector<vector<int>>& mccostos, map<string,Enrutador> red, vector<string>nombres)
{
    Enrutador enrutador;
    vector<int> costos;
    auto inicio = red.begin();
    auto fin = red.end();
    while (inicio != fin){
        enrutador=inicio->second;
        costos=enrutador.retornarcostosmc(nombres);
        mccostos.push_back(costos);
        inicio++;
    }
}
void algfloydwarshall(vector<vector<int>>& costos, vector<vector<string>>& Nombres)
{
    int contp=0, lim=costos.size(), conts=0, num1=0, num2, aux=1;
    while(contp<lim){
        conts=0;
        if(contp==conts){
            conts+=1;
        }
        while(aux<lim){
            while(conts<lim){
                num1=costos[contp][conts];
                num2=costos[aux][contp];
                if(num1!=0 && num2!=0 && aux!=conts){
                    if(costos[aux][conts]==0 || num1+num2<costos[aux][conts]){
                        costos[aux][conts]=num1+num2;
                        Nombres[aux][conts]=Nombres[contp][contp];
                    }
                }
                conts+=1;
            }
            aux+=1;
            conts=0;
        }
        aux=0;
        contp+=1;
    }

}

void encontrarcostos(vector<string> enr, vector<vector<int>> costos)
{
    bool ban=true;
    int lim= enr.size(), conte=0, contr=0, costo=0;
    string nome, nomr;
    cout<<"Ingrese el nombre del enrutador emisor: ";
    cin>>nome;
    for(int i=0; i<lim; i++){
        if(enr[i]==nome){
            ban=false;
            conte=i;
        }
    }
    while(ban){
        cout<<"El enrutador no existe"<<endl;
        cout<<"Ingrese un nombre valido: ";
        cin>>nome;
        for(int i=0; i<lim; i++){
            if(enr[i]==nome){
                ban=false;
                conte=i;
            }
        }
    }
    cout<<"Ingrese el nombre del enrutador receptor: ";
    cin>>nomr;
    ban=true;
    if(nomr!=nome){
        for(int i=0; i<lim; i++){
            if(enr[i]==nomr){
                ban=false;
                contr=i;
            }
        }
    }
    while(ban){
        if(nomr==nome){
            cout<<"No se puede enviar informacion de un enrutador a si mismo"<<endl;
        }
        else{
            cout<<"El enrutador no existe"<<endl;
        }
        cout<<"Ingrese un nombre valido: ";
        cin>>nomr;
        if(nomr!=nome){
            for(int i=0; i<lim; i++){
                if(enr[i]==nomr){
                    ban=false;
                    contr=i;
                }
            }
        }
    }
    if(costos[conte][contr]!=0){
        costo=costos[conte][contr];
        cout<<"El costo de enviar del enrutador "<<nome<<" a "<<nomr<<" es de "<<costo<<endl;
    }
    else{
        cout<<"No existe conxion con el enrutador"<<endl;
    }
}

void encontrarcamino(vector<string> enr,vector<vector<string>> caminos, vector<vector<int>> costos)
{
    bool ban=true;
    vector<string> cam;
    int lim= enr.size(), conte=0, contr=0, cont=0;
    string nome, nomr, auxc, aux2;
    cout<<"Ingrese el nombre del enrutador emisor: ";
    cin>>nome;
    for(int i=0; i<lim; i++){
        if(enr[i]==nome){
            ban=false;
            conte=i;
        }
    }
    while(ban){
        cout<<"El enrutador no existe"<<endl;
        cout<<"Ingrese un nombre valido: ";
        cin>>nome;
        for(int i=0; i<lim; i++){
            if(enr[i]==nome){
                ban=false;
                conte=i;
            }
        }
    }
    cout<<"Ingrese el nombre del enrutador receptor: ";
    cin>>nomr;
    ban=true;
    if(nomr!=nome){
        for(int i=0; i<lim; i++){
            if(enr[i]==nomr){
                ban=false;
                contr=i;
            }
        }
    }
    while(ban){
        if(nomr==nome){
            cout<<"No se puede enviar informacion de un enrutador a si mismo"<<endl;
        }
        else{
            cout<<"El enrutador no existe"<<endl;
        }
        cout<<"Ingrese un nombre valido: ";
        cin>>nomr;
        if(nomr!=nome){
            for(int i=0; i<lim; i++){
                if(enr[i]==nomr){
                    ban=false;
                    contr=i;
                }
            }
        }
    }
    if(costos[conte][contr]!=0){
        auxc=caminos[conte][contr];
        cam.push_back(nomr);
        aux2=nomr;
        while(auxc!=aux2){
            cam.insert(cam.begin(), auxc);
            for(int i=0; i<lim; i++){
                if(enr[i]==auxc){
                    contr=i;
                }
            }
            aux2=auxc;
            auxc=caminos[conte][contr];
        }
        cam.insert(cam.begin(), nome);
        cout<<"El camino que se debe recorrer es: "<<endl;
        cout<<cam[cont];
        lim=cam.size();
        while(cont<lim-1){
            cont+=1;
            cout<<"->"<<cam[cont];
        }
        cout<<endl;
    }
    else{
        cout<<"No existe conexion con este enrutador"<<endl;
    }

}
