#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

fstream f ("medicament.txt",ios::out | ios::in | ios::app);
fstream g ("rezervari.txt",ios::out | ios::in | ios::app);

int numarfarm=-1;
int numarrez=-1;

class Farmacie{
public:
    Farmacie (string, int);
    virtual ~Farmacie ();
    string get_nume(){ return nume; }
    void set_nume(string nume){ this->nume=nume; }
    int get_cantitate(){ return cantitate; }
    void set_cantitate(int cantitate){ this->cantitate=cantitate; }
    void afisare(Farmacie** );
    void cautare(Farmacie** );
    void adaugare(Farmacie** );
    void stergere(Farmacie** );
    friend ostream& operator<<(ostream& , Farmacie* );
    friend class Rezervare;
private:
    string nume;
    int cantitate;
};

class Rezervare:public Farmacie{
public:
    Rezervare (string, int, string);
    virtual ~Rezervare();
    string get_numerez(){ return numerez; }
    void set_numerez(string numerez){ this->numerez=numerez; }
    friend ostream& operator<<(ostream& , Rezervare* );
    void rezervare (Rezervare** );
    void afisarere (Rezervare** );
private:
    string numerez;
};

Farmacie::Farmacie (string nume, int cantitate )
{
    this->cantitate = cantitate;
    this->nume = nume;
}

Rezervare::Rezervare (string nume, int cantitate, string numerez):Farmacie (nume,cantitate){
    this->numerez=numerez;
}

Farmacie::~Farmacie (){}

Rezervare::~Rezervare(){}

ostream& operator<<(ostream& os, Farmacie* farm){
    os<<farm->get_nume() << " " << farm->get_cantitate() << "buc.";
    return os;
}

ostream& operator<<(ostream& os, Rezervare* rez){
    os<< rez->get_numerez()<< " a rezervat "<< rez->get_cantitate()<< " buc. de "<< rez->get_nume();
    return os;
}

void afisare(Farmacie** farm){
    int inapoi,i=0;
    system("cls");
    cout<<"\n";

    cout<<"--------------"<<"\n";

    for (i=0 ; i<=numarfarm ; i++) {
        cout<<farm[i]<<endl;
    }
    cout<<"--------------"<<"\n"<<"\n";
    cout<<"0.Inapoi"<<"\n"<<"\n";

    do{
        cout<<"Introduceti optiunea dorita: ";
        cin>>inapoi;
    }while(inapoi!=0);

    system("cls");
}

void cautare(Farmacie** farm){
    int inapoi,i=0,ok=0;
    string nume;
    cout<<"\n";
    cout<<"Introdu numele produsului care doresti sa il cauti: ";
    cin.get();
    getline(cin, nume);
    cout<<"\n";

    while (i <= numarfarm){
        if (farm[i]->get_cantitate() != 0 && nume==farm[i]->get_nume()){
            cout<<"Exista"<<" "<<farm[i]->get_cantitate()<<" "<< "in stoc la momentul actual."<<"\n"<<"\n";
            ok=1;
        }
        i++;
    }
    if (ok==0)
        cout<<"Nu avem acest produs in baza de date."<<"\n"<<"\n";

    cout<<"0.Inapoi"<<"\n"<<"\n";
    do{
        cout<<"Introduceti optiunea dorita: ";
        cin>>inapoi;
    }while(inapoi!=0);

    system("cls");
}

void rezervare (Farmacie** farm, Rezervare** rez){
    string nume;
    int cantitate,cantitate_init;
    string numerez;
    int inapoi,i=0,ok;

    cout<<"\n"<<"--------------"<<"\n";
    cout<<"\n"<<"Introduceti numele medicamentului: ";
    cin.get();
    getline(cin, nume);
    cout<<"Introduceti numele dumneavoastra: ";
    getline(cin, numerez);
    cout<<"Introduceti cat doriti sa rezervati: ";
    cin>>cantitate;

    for (int i=0; i<=numarfarm; i++){
        if (nume == farm[i]->get_nume()){
            if (cantitate < farm[i]->get_cantitate()){
                farm[i]->set_cantitate(farm[i]->get_cantitate() - cantitate);
                ok=0;
                break;
            }
            else {
                cantitate_init=farm[i]->get_cantitate();
                farm[i]->set_cantitate(0);
                ok=1;
                break;
            }
        }
    }
    i=0;

    f.open("medicament.txt", ios::out);
    f<< farm[i]->get_nume()<< ","<< farm[i]->get_cantitate()<<"\n";
    f.close();
    f.open("medicament.txt", ios::app);
    for (i=1; i<=numarfarm; i++)
        f<< farm[i]->get_nume()<< ","<< farm[i]->get_cantitate()<< "\n";
    f.close();

    g.open("rezervari.txt", ios::app);
    numarrez++;
    if (ok==0){
        rez[numarrez] = new Rezervare (nume, cantitate, numerez);
        g<< rez[numarrez]->get_nume()<< ","<< rez[numarrez]->get_cantitate()<< ","<< rez[numarrez]->get_numerez()<<"\n";
        g.close();
    }
    else{
        rez[numarrez] = new Rezervare (nume, cantitate_init, numerez);
        g<< rez[numarrez]->get_nume()<< ","<< rez[numarrez]->get_cantitate()<< ","<< rez[numarrez]->get_numerez()<<"\n";
        g.close();
    }

    cout<<"Ati facut o rezervare cu succes"<<"\n"<<"Puteti sa reveniti la aceasi ora maine sa ridicati comanda"<<"\n"<<"\n";
    cout<<"0.Inapoi"<<"\n"<<"\n";
    do{
        cout<<"Introduceti optiunea dorita: ";
        cin>>inapoi;
    }while(inapoi!=0);

    system("cls");
}

void adaugare(Farmacie** farm){
    string nume;
    int cantitate;
    numarfarm++;

    cout<<"\n"<<"Introduceti numele medicamentului: ";
    cin.get();
    getline(cin, nume);
    cout<<"Introduceti cantitatea: ";
    cin>>cantitate;

    farm[numarfarm] = new Farmacie (nume , cantitate);
    f.open("medicament.txt",ios::app);
    f<< farm[numarfarm]->get_nume()<< ","<< farm[numarfarm]->get_cantitate()<< "\n";
    f.close();

    system("cls");
}

void stergere(Farmacie** farm){
    string nume;
    char i=0,j,ok=0,inapoi=0;
    cout<<"Introduceti numele: ";
    cin.get();
    getline(cin, nume);

    while (i<= numarfarm){
        if ((nume == farm[i]->get_nume()) && ok==0){
            for (int j=i; j<numarfarm ; j++){
                farm[j]= farm[j+1];
            }
            ok=1;
        }
        i++;
    }
    i=0;

    numarfarm--;
    f.open("medicament.txt", ios::out);
    f<< farm[i]->get_nume()<< ","<< farm[i]->get_cantitate()<<"\n";
    f.close();
    f.open("medicament.txt", ios::app);
    for (i=1; i<=numarfarm; i++)
        f<< farm[i]->get_nume()<< ","<< farm[i]->get_cantitate()<< "\n";
    f.close();

    system("cls");
}

void afisarere (Rezervare** rez){
    int inapoi,i=0;
    system("cls");
    cout<<"\n";

    cout<<"--------------"<<"\n";
    for (i=0 ; i<=numarrez ; i++) {
        cout<< rez[i]<< endl;
    }
    cout<<"--------------"<<"\n"<<"\n";
    cout<<"0.Inapoi"<<"\n"<<"\n";

    do{
        cout<<"Introduceti optiunea dorita: ";
        cin>>inapoi;
    }while(inapoi!=0);

    system("cls");
}


void iesire()
{
    system("cls");
    cout<<"\n";
    cout<<"Ati iesit din aplicatie!!!";
    cout<<"\n";
}

void meniu()
{
    system("Color 0A");
    cout<<"\n"<<"--------Farmacie--------"<<"\n";
    cout<<"1. Afiseaza produse disponibile."<<"\n";
    cout<<"2. Cauta un produs."<<"\n";
    cout<<"3. Rezerva medicamente."<<"\n";
    cout<<"4. Adauga medicament."<<"\n";
    cout<<"5. Sterge medicament."<<"\n";
    cout<<"6. Afiseaza produse rezervate."<<"\n";
    cout<<"0. Iesire"<<"\n"<<"\n";
}

void optiuni(int alegere , Farmacie** farm , Rezervare** rez)
{
    switch(alegere){
        case 1:
            afisare(farm);
            break;
        case 2:
            cautare(farm);
            break;
        case 3:
            rezervare(farm, rez);
            break;
        case 4:
            adaugare(farm);
            break;
        case 5:
            stergere(farm);
            break;
        case 6:
            afisarere(rez);
            break;
        case 0:
            iesire();
            break;
    }
}

int main ()
{
    int alegere,i=0;
    string linie,linie1;
    string delim = ",";
    string token, token1, token2;
    size_t pos = 0 , pos1=0 , pos2=0;
    Farmacie **farm = new Farmacie*[100];
    Rezervare **rez = new Rezervare*[100];

    while (getline(f,linie)){
        numarfarm++;
        pos = linie.find(delim);
        token = linie.substr(0, pos);
        linie.erase(0, pos + delim.length());
        farm[numarfarm] = new Farmacie (token , atoi(linie.c_str()));
    }
    f.close();

    while (getline(g,linie1)){
        numarrez++;
        pos1 = linie1.find(delim);
        token1 = linie1.substr(0, pos1);
        linie1.erase(0, pos1 + delim.length());
        pos2 = linie1.find(delim);
        token2 = linie1.substr(0, pos2);
        linie1.erase(0, pos2 + delim.length());
        rez[numarrez] = new Rezervare (token1 , atoi(token2.c_str()) , linie1);
    }
    g.close();
    do{
        meniu();
        cout<<"Introduceti optiunea dorita: ";
        cin>>alegere;
        optiuni(alegere, farm, rez);
    }while(alegere!=0);
}
