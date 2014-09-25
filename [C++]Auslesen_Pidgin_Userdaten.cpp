#include <iostream> /* Standardstream-Funktionaliät einbinden */
#include <fstream>  /* ofstream und ifstream einbinden */
#include <pwd.h>    /* Ermittlung der Benutzerdaten */
 
using namespace std;
 
void auslesen( string g )
{
    int i,j,h=0;
    string result = "";                 /* Der String enthält später die Daten*/
    string finalresult = "";            /* Der endgültige String der ausgegeben wird */
    string zeile = "";                  /* Steht für jede einzelne Zeile die eingelesen wird */
    string protocol = "<protocol>";     /* Die XML-Tags nach denen gesucht wird */
    string name = "<name>";
    string password = "<password>";
    ifstream pidgstream(g.c_str());     /* stream öffnen */
    if (pidgstream.is_open())
    {
        while(!(pidgstream.eof()))  /* eof() liefert 'true' wenn Dateiende erreicht */
        {
            /* Einlesen jeder einzelnen Zeile */
            getline(pidgstream, zeile, '\n');   
/* 1. Parameter: Eingabestrom, 2. Parameter: zu beschreibender String, 3. Parameter: Begrenzungszeichen */
 
            h = zeile.find(protocol);
            if( h > 0 )
            {
                result += "\n" + zeile + "\n";
                result.replace(result.find(protocol),protocol.length(),"Protokoll: ");
                result.replace(result.find("</protocol>"),protocol.length()+1,"");
            }
            i = zeile.find(name);
            if( i > 0 )
            {
                result += zeile + "\n";
                result.replace(result.find(name),name.length(),"Name/Nummer: ");
                result.replace(result.find("</name>"),name.length()+1,"");
            }
             j = zeile.find(password);
            if( j > 0 )
            {
                result += zeile;
                result.replace(result.find(password),protocol.length(),"Passwort: ");
                result.replace(result.find("</password>"),password.length()+1,"\n");
            }
 
 
 
 
        }
        pidgstream.close();
        /* entfernen der Tabulatorzeichen */
 
        for( size_t n = 0; n < result.length(); ++n)
            if( result[n] != '\t' ) finalresult += result[n];
        cout << finalresult << endl;
    }
    else
        cout << "Fehler beim Oeffnen der Datei!" << endl;
}
 
int main(void)
{
    /* Ermittlung des HOME-Ordners */
    struct passwd *p;
    uid_t uid;
 
    if(( p = getpwuid( uid = getuid())) == NULL)
        perror("getuid() Error");
    else
    {
        /* Ermittlung der Account-XML */
        string homepath = p->pw_dir;
        string pidginpath = "/.purple/accounts.xml";
        string fullpath = homepath + pidginpath;
 
        auslesen( fullpath );
    }
 
    return 0;
}
