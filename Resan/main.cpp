#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

using namespace std;

const int MAX_KOMPISAR=6;
const int MAX_TRANSAKTIONER=10;

int  dubbelArray(string fil);

///////////////////////////////////////////////
////////Transaktion////////////////////////////
///////////////////////////////////////////////

 class Transaktion
 {
  private:
   string datum;
   string typ;
   string namn;
    double belopp;
   int ant_kompisar;
   string kompisar[MAX_KOMPISAR];

  public:
   Transaktion();
   ~Transaktion();
   string haemta_namn(string transaktionsBetalare);
   string haemta_datum(string transaktionsDatum);
   string haemta_typ(string transaktionsTyp);
   double haemta_belopp(string transaktionsBelopp);
   int haemta_ant_kompisar(string transaktionsAntal);
   bool finnsKompis( string namnet );
   bool laesEnTrans( istream &is );
   void skrivEnTrans( ostream &os );
   string allaKompisar[MAX_KOMPISAR]={"Eva","Paul","Bosse","Stina","Kristin","Torsten"};
//    ...eventuellt div. annat...
 };
///////////////////////////////////////////////
////////TransaktionsLista//////////////////////
///////////////////////////////////////////////
 class TransaktionsLista
{
 private:
   Transaktion trans[MAX_TRANSAKTIONER];
   int antalTrans;

 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void laesin( istream & is );
   void skrivut();
   void laggTill( Transaktion & t );
   double totalkostnad();
   double liggerUteMed( string namnet );
   double aerSkyldig( string namnet );
 //  PersonLista FixaPersoner();
    //...eventuellt div. annat...
 };




///////////////////////////////////////////////
///////////////MAIN////////////////////////////
///////////////////////////////////////////////
int main()
{
    int antalTransaktioner=0;
    int varjeTransCounter=1;
    string fileString;
    string line;
    string file = "trans.txt";
    string utfil = "utfil.txt";
    string varjeTrans[10];

    ifstream fin(file.c_str());
    if(!fin)
    {
        cout<<"Filen "<<file<<" kunde inte hittas."<<endl;
        exit( EXIT_FAILURE );
    }
    //cout<<"Transaktionsfil laddad."<<endl;
    cout<<"\n"<<endl;

    int p=0;
    while(getline(fin,line,'\n'))
    {
       fileString.append(line+"\n");
       varjeTrans[p].append(line+"\n");
       antalTransaktioner++;
       p++;
    }

    //cout<<fileString<<endl;

    Transaktion transaktion[antalTransaktioner];
    TransaktionsLista lista;

    cout<<"\n"<<endl;
    //cout<<"Antal transaktioner: "<<antalTransaktioner<<endl;

    for(int i=0;i<antalTransaktioner;i++)
    {
        transaktion[i].haemta_datum(varjeTrans[i]);
        transaktion[i].haemta_typ(varjeTrans[i]);
        transaktion[i].haemta_namn(varjeTrans[i]);
        transaktion[i].haemta_ant_kompisar(varjeTrans[i]);
        transaktion[i].haemta_belopp(varjeTrans[i]);
        lista.laggTill(transaktion[i]);
    }

    lista.totalkostnad();
    lista.skrivut();

    return 0;
}


///////////////////////////////////////////////
////////Transaktion////////////////////////////
///////////////////////////////////////////////
Transaktion::Transaktion()
{

}
Transaktion::~Transaktion()
{

}

string Transaktion::haemta_datum(string transaktionsDatum)
{
    for(int i=0;i<6;i++)
    {
        datum+=transaktionsDatum[i];
    }
    return datum;
}
string Transaktion::haemta_typ(string transaktionsTyp)
{
    string transp, mat,boende;
    transp = "transp";
    mat = "mat";
    boende = "boende";
    if(transaktionsTyp.find(mat) != string::npos)
    {
        typ = mat;
        //cout<<"Typ satt till mat"<<endl;
    }
    else if(transaktionsTyp.find(transp) != string::npos)
    {
        typ = transp;
        //cout<<"Typ satt till transp"<<endl;
    }
    else if(transaktionsTyp.find(boende) != string::npos)
    {
        typ = boende;
        //cout<<"Typ satt till boende"<<endl;
    }
    //cout<<typ<<endl;
    return typ;
}
bool Transaktion::finnsKompis( string namnet )
{
    for(int i=0;i<MAX_KOMPISAR;i++)
    {
        if(namnet.find(allaKompisar[i]) != string::npos)
        {
            return true;
        }
    }
}
string Transaktion::haemta_namn(string transaktionsBetalare)
{
    int temp = 6+typ.length();
    string tempo;
    for(int i=temp;i<25;i++)
    {
        tempo+=transaktionsBetalare[i];
    }
    //cout<<tempo<<endl;

    for(int i=0;i<MAX_KOMPISAR;i++)
    {
        //cout<<"Kollar efter: "<<allaKompisar[i]<<endl;
        if(tempo.find(allaKompisar[i]) != string::npos)
        {
            namn = allaKompisar[i];
        }
    }
    //cout<<namn<<" betalade hela skiten!"<<endl;
    return namn;
}
int Transaktion::haemta_ant_kompisar(string transaktionsAntal)
{
    ant_kompisar = 0;
    for(int i=0;i<MAX_KOMPISAR;i++)
    {
        if(transaktionsAntal.find(allaKompisar[i]) != string::npos)
        {
            if(namn != allaKompisar[i])
            {
                kompisar[ant_kompisar] =  allaKompisar[i];
                ant_kompisar++;
            }
        }
    }
    // cout<<"Antal kompisar att dela: "<<ant_kompisar<<endl;
    return ant_kompisar;
}
double Transaktion::haemta_belopp(string transaktionsBelopp)
{
    std::string t = std::to_string(ant_kompisar);
    int pos = transaktionsBelopp.rfind(t);
    //cout<<pos<<endl;
    transaktionsBelopp.replace(pos,1,"n");
    //cout<<transaktionsBelopp<<endl;

    int temp = 16 + namn.length();
    string tempBelopp;
    for(int i=temp;i<temp+15;i++)
    {
        if(transaktionsBelopp[i] == '1'||transaktionsBelopp[i] =='2'||transaktionsBelopp[i] =='3'||
           transaktionsBelopp[i] =='4'||transaktionsBelopp[i] =='5'||transaktionsBelopp[i] =='6'||
           transaktionsBelopp[i] =='7'||transaktionsBelopp[i] =='8'||transaktionsBelopp[i] =='9'||transaktionsBelopp[i] =='0')
        {
            tempBelopp+=transaktionsBelopp[i];
        }
    }
    belopp = std::stod(tempBelopp);
    //cout<<belopp<<endl;
    return belopp;
}
void Transaktion::skrivEnTrans( ostream &os )
{
    os<<datum<<" "<<namn<<" projsa "<<belopp<<" for "<<typ<<"."<<endl;
    for(int i=0;i<ant_kompisar;i++)
    {
        os<<kompisar[i]<<" ska projsa."<<endl;
    }
}
bool Transaktion::laesEnTrans( istream &is )
{

}
/////////////////////////////////////////////////////
////////Transaktionslista////////////////////////////
/////////////////////////////////////////////////////
TransaktionsLista::TransaktionsLista()
{
    antalTrans = 0;
}

TransaktionsLista::~TransaktionsLista()
{

}
void TransaktionsLista::laggTill( Transaktion & t )
{
    trans[antalTrans] = t;
    antalTrans++;
    //cout<<"Antal Trans: "<<antalTrans<<endl;
}
double TransaktionsLista::totalkostnad()
{

    for(int i=0;i<antalTrans;i++)
    {

    }
}
void TransaktionsLista::skrivut()
{
    string utfil = "utfil.txt";
    for(int i=0;i<antalTrans;i++)
    {
            ofstream utfilen;
            utfilen.open ( utfil.c_str() );
            trans[i].skrivEnTrans( cout );
            cout<<"\n"<<endl;
    }
}

