#include <iostream>
#include <string>
using namespace std;

struct TListenKnoten
{
    //* = pointer - & = adresse

    int data;
    TListenKnoten* next;
    TListenKnoten* prev; //a
};
void hinten_anfuegen(TListenKnoten*& anker, const int wert)
{
    TListenKnoten* neuer_eintrag = new TListenKnoten; //erstellen neuer pointer -> neuer eintrag
    neuer_eintrag->data = wert; 
    neuer_eintrag->next = nullptr; //nächster          (zeigt auf leerstelle)
    neuer_eintrag->prev = nullptr;//a //vorheriger

    if (anker == nullptr)//(noch nicht existent)
        anker = neuer_eintrag; //auf stelle des neuen listenknoten setzen
    else
    {
        TListenKnoten* ptr = anker; //anker = startzeiger
        while (ptr->next != nullptr) {//übergang ptr
            ptr = ptr->next;
        }
        neuer_eintrag->prev = ptr;//a //vorheriger wert vom neuen
        ptr->next = neuer_eintrag; //hinten angefügt //nächster vom alten
    }
}
string liste_als_string(TListenKnoten* anker)
{
    string resultat = "";

    if (anker == nullptr)//wenn nullptr
        return "Leere Liste.";

    else
    {
        resultat += "[ ";
        TListenKnoten* ptr = anker;//lokale variable start bei anker
        do
        {
            resultat += to_string(ptr->data); //kovertiert alles zu string

            if (ptr->next != nullptr) resultat += " , "; //komma zwischen zahlen solange nicht am ende
            else resultat += " "; //anfang und ende leerzeichen
            ptr = ptr->next;//nächster wert
        } while (ptr != nullptr);//bis prt = nullpointer-> bis ende erreicht,dann
        resultat += "]";//klammer zu am Ende
    }
    return resultat;
}

string liste_als_string_r(TListenKnoten* anker)
{
    string resultat = "";

    if (anker == nullptr)//wenn nullptr
        return "Leere Liste.";

    else
    {
        resultat += "[ ";
        TListenKnoten* ptr = anker;//lokale variable start bei anker
       
        while (ptr->next != nullptr) { ptr = ptr->next; }//durch liste gehen

        do
        {
            resultat += to_string(ptr->data); //kovertiert alles zu string

            if (ptr->prev != nullptr) resultat += " , "; //komma zwischen zahlen solange nicht am anfang
            else resultat += " "; //anfang und ende leerzeichen
            ptr = ptr->prev; //vorheriger wert
        } while (ptr != nullptr); //bis prt = nullpointer-> bis ende erreicht,dann weiter //am ende auf nullpointer setzen
        resultat += "]"; //klammer zu am Ende
    }
    return resultat;
}

void liste_ausgeben(TListenKnoten* anker)
{
    cout << liste_als_string(anker) << endl; //output
}

void liste_ausgeben_r(TListenKnoten* anker)
{
    cout << liste_als_string_r(anker) << endl; //output
}

//a

void in_liste_einfuegen(TListenKnoten*& anker, int wert_neu, int vor_wert) {

    TListenKnoten* ptr = anker;

    int temp_1 = wert_neu; //temporärer speicher
    int temp_2 = wert_neu;

    while (ptr != nullptr) {//bis ende durchgehen

        if (ptr->data == vor_wert) {
            while (ptr != nullptr) { //bis ende
                temp_2 = ptr->data; //auf momentanen datenwert 
                ptr->data = temp_1;//zwischenspeichern
                temp_1 = temp_2; //verschieben (im nächsten schritt wird 2 wieder verändert)
                ptr = ptr->next;//nächster schritt
            }
            break; //unterbrechen
        }
        else {
            ptr = ptr->next; //danach(while) auf next
        }
    }

    hinten_anfuegen(anker, temp_2); //letzten wert hinten anfügen
      
}

void aus_liste_loeschen(TListenKnoten*& anker, int wert) {//wert soll gelöscht werden

    TListenKnoten* ptr_1 = anker;
    TListenKnoten* ptr_2 = anker; //zwischenvariable

    while (ptr_1 != nullptr) { //liste durchgehen
        if (ptr_1->data == wert) { //wenn wert gefunden dann, ansosten else
            while (ptr_1->next != nullptr) {
                ptr_1->data = ptr_1->next->data; //momentanen wert durch nächsten ersetzen
                ptr_1 = ptr_1->next; //weiter gehen
            }

            if (ptr_1 == anker) { //(anker nicht löschen sondern auf nllptr)
                anker->next = nullptr;
                anker = nullptr;
            }
            else { //ende der liste 
                ptr_2 = ptr_1->prev;//adresse speichern
                ptr_1->prev = nullptr; //prev zurück setzen
                delete ptr_1; //löschen("falsches ende)
                ptr_1 = ptr_2->next = nullptr; //next(adresse) auf nll setzen
            }
            break;
        }
        else {
            ptr_1 = ptr_1->next;
        }
    }
}

void liste_loeschen(TListenKnoten*& anker) {
    TListenKnoten* ptr_1 = anker;
    TListenKnoten* ptr_2 = anker;

    if (ptr_1 != nullptr) { //druchgehen //solange noch was in liste drin ist

        if (ptr_1->next != nullptr) {//nächster = nullptr?

            while (ptr_1->next != nullptr) {
                ptr_1 = ptr_1->next;
            }

            ptr_2 = ptr_1; //ende abspeichern

            while (ptr_2 != anker) {//anker nicht-> von hintenaus löschen
                ptr_2 = ptr_2->prev; //vorheriger in ptr 2
                ptr_1->prev = nullptr;
                delete ptr_1; //löschen-> ende der liste
                ptr_1 = ptr_2->next = nullptr; //auf nullptr
                ptr_1 = ptr_2;
            }
            anker->next = nullptr;
        }
       
        anker = nullptr; //anker auf nullptr
    }
}

/*int main()
{
    const int laenge = 10;
    TListenKnoten* anker = nullptr;

    for (int i = 0; i < laenge; i++) // neu
        in_liste_einfuegen(anker, i * i, 9999); // neu //zahl wird quadriert //9999 vergleichswert

    liste_ausgeben(anker);
    liste_ausgeben_r(anker);

    int wert_neu = 0, vor_wert = 0; // neu
    cout << "Einzufuegender Wert: "; cin >> wert_neu; //neu
    cout << "Vor welchem Wert? "; cin >> vor_wert; // neu
    in_liste_einfuegen(anker, wert_neu, vor_wert); // neu

    liste_ausgeben(anker);
    liste_ausgeben_r(anker);

    system("PAUSE");
    return 0;
}*/

int main()
{
    const int laenge = 10;
    TListenKnoten* anker = nullptr;
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    liste_loeschen(anker);
    hinten_anfuegen(anker, 77);
    hinten_anfuegen(anker, 88);
    hinten_anfuegen(anker, 99);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    liste_loeschen(anker); // war: aus_liste_loeschen(anker, 99);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    for (int i = 0; i < laenge; i++)
        in_liste_einfuegen(anker, i * i, 9999);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    in_liste_einfuegen(anker, -1, 0);
    in_liste_einfuegen(anker, 24, 25);
    in_liste_einfuegen(anker, 80, 81);
    in_liste_einfuegen(anker, 99, 9999);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    aus_liste_loeschen(anker, 24);
    aus_liste_loeschen(anker, 80);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    liste_loeschen(anker);
    liste_ausgeben(anker);
    liste_ausgeben_r(anker);
    system("PAUSE");
    return 0;
}