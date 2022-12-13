/*

Hotelli varaus ohjelma.

Tämä ohjelma on kurssin harjoitustyö ja se on tehty osoittamaan C++ ohjelmoinnin perusteiden osaamiseni.
Ohjelma täyttää korkeimman arvosanan vaatimat ominaisuudet.

Ohjelma arpoo alussa parillisen määrän hotellihuoneita väliltä 40-300, joista puolet (alkupuoli) on yhden hengen ja puolet (loppupuoli) on kahden hengen huoneita,
Ohjelma kysyy käyttäjältä halutaanko luoda varaus, vaiko tarkastella sellaista.
Jos käyttäjä valitsee varauksen luomisen, hänelle ilmoitetaan vapaat huoneet, sekä mitkä niistä ovat yhden- ja mitkä kahden hengen huoneita, sekä yhden yön hinnan kussakin huoneessa.
Tämän jälkeen käyttäjä voi valita yhden- tai kahden hengen huoneen.
Ohjelma kysyy haluaako käyttäjä itse päättää huoneen, ohjelma voi myös arpoa huoneen satunnaisesti.
Tämän jälkeen ohjelma kysyy montako yötä halutaan varata (Maksimiksi päätetty 11 yötä).
Seuraavaksi käyttäjää pyydetään syöttämään varaajan nimi.
Tämän jälkeen varaajalle näytetään varauksen tiedot ja annetaan mahdollisuus perua varaus, tai siirtyä maksamaan.
Tässä kohtaa kone arpoo 0%, 10% tai 20% alennuksen varaukseen, jos alennus on 0% käyttäjälle näytetään varausnumero ja muut varauksen tiedot.
Jos taas alennus on 10% tai 20%, käyttäjää onnitellaan ja saatu alennus ilmoitetaan. Tämän jälkeen käyttäjää pyydetään siirtymään maksamaan syöttämällä 1.
Kun käyttäjä syöttää numeron 1, häntä kiitetään varauksesta ja näytetään varausnumero, sekä varauksen tiedot.
Tässä kohtaa käyttäjä voi palata alkuun(1) tai sulkea ohjelman(2)
Jos käyttäjä palaa alkuun hän voi alkaa luomaan uutta varausta (varauksia voi luoda niin kauan kuin huoneita riittää), kun kaikki huoneet on varattu, ohjelma ilmoittaa hotellin olevan täynnä.
tai hän voi siirtyä tarkastelemaan, jo tehtyjä varauksia.
Varauksia voidaan hakea varausnumeron tai varaajan nimen perusteella.
Varausnumerolla näytetään numeroa vastaava varaus ja nimellä listataan kaikki, henkilön tekemät varaukset.

Ohjelma tarkistaa aina, että käyttäjän syötä on kelpuutettava arvo ja pitää huolen siitä, että samaa huonetta ei voi varata useaan kertaan, ja että varausnumero on aina eri.




Kurssi: C++ ohjelmoinnin perusteet
Tekijä: Petteri Laukkanen

*/




//Tuodaan ohjelman tarvitsemat kirjastot
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

//Määritetään käyttöön std nimiavaruus
using namespace std;


//Pääohjelman alku
int main() {



	//Asettaa ohjelman kieleksi suomen, mahdollistaen ääkkösien tulostuksen
	setlocale(LC_ALL, "finnish");



	int noppa(int, int);                                 //Aliohjelma, joka palauttaa satunnaisen luvun (int, int)=(minimiarvo, maksimiarvo)

	int huoneidenmaara = noppa(4, 4);                      //Arvotaan huoneiden määrä väliltä 40-300.
	int yhdenhengenhuoneet = huoneidenmaara / 2;              //Hotellissa olevien yhden hengen huoneiden määrä.
	int kahdenhengenhuoneet = huoneidenmaara / 2;             //Hotellissa olevien kahden hengen huoneiden määrä.
		kahdenhengenhuoneet++;
	int yhdenhengenhuoneettod = yhdenhengenhuoneet;     //Vapaana olevien yhden hengen huoneiden määrä.
	int kahdenhengenhuoneettod = kahdenhengenhuoneet;   //Vapaana olevien kahde nhengen huoneiden määrä.
		kahdenhengenhuoneettod--;
	//Muuttujat, joihin tallennetaan väliaikaisesti käynnissäolevan varauksen tiedot.
	//Näin ne on helppo ylikirjoittaa jos käyttäjä päättää keskeyttää varauksen
	int varausnmr = 1;                                  //Varausnumero
	int valikko;                                        //Valikko (1: valikon ensimmäinen vaihtoehto, 2:toinen vaihtoehto, jne.
	int aika;                                           //Öiden määrä
	int hinta;                                          //Hinta (Aluksi huoneen koon ja öiden määrän perusteella, mutta kun varaus on lukittu hinnasta poistetaan arvottu alennus)
	int alennus;                                        //Alennus (0:ei alennusta, 1:10% alennus, 2: 20% alennus)
	int huone;                                          //Valittu huone
	int tila;                                           //Huoneen koko (1:yhden hengen huone, 2:kahden hengen huone)
	string nimi;                                        //Varaajan nimi

	bool huoneet[300];                                  /*boolean taulukko, johon merkataan huoneen varauksen tila true / false arvona.
														Esim: huoneet[1]=true << huone 1 on varattu
														huoneet[2]=false << huone 2 on vapaa*/

	bool varausnumerot[99999];                          //Sama kuin bool huoneet, mutta varausnumeroille.
	bool loydetty = false;										//Boolean joka on true jos etsityllä varausnumerolla löytyi varaus



	//struct, joka toimii varauspohjana sisältäen muuttujat jotka jokainen varaus tarvitsee
	struct varaukset {
		string vnimi;       //Varaajan nimi
		int vhuone;         //Varattu huone
		int vnumero;        //Varausnumero
		int vtila;          //Huoneenkoko
		int vaika;          //Öiden määrä
		int vhinta;         //varauksen lopullinen hinta
	};

	varaukset varaaja[300]; //Määritellään taulukko varaaja, jossa on 300 varaukset tyyppistä muuttujaa
	//tänne voidaan tallentaa "varaukset" structissa esitellyt muuttujat vnimi, vhuone, jne. kullekkin eri varaukselle




	//Varausten tarkasteluun käytetyt muuttujat
	string etsittavavaraaja;    //Käyttäjän ilmoittama nimi, jonka varauksia halutaan etsiä
	int etsittavanumero;        //Käyttäjän ilmoittama varausnumero, jonka perusteella varausta halutaan etsiä


	int varaajat = 0;           //Pitää kirjaa siitä montako varausta on tehty

	int hintalaskuri(int, int); //Funktio, joka laskee huoneen koon ja öiden perusteella varauksen hinnan
	void viivat();              /*Funktio, jota kutsumalla voidaan tulostaa viivoja, ns. lataus animaationa
	(käytetään lukemisen selventämiseksi ja annetaan aikaa lukea näytön tekstejä ilman, että ohjelma näyttää pysähtyneen.*/
	void cls();                 /*Funktio, joka tulostaa rivejä siten, että aiemmat tekstit siirtyvät näytön ulkopuolelle ja kursori siirtyy vasempaan ylänurkkaan
	Käytetään auttamaan valikon luettavuutta*/


	Sleep(200);                 //Odoitus komento

	//Tulostetaan hotellin nimi ASCII art tyylillä
	cout << R"(  _______ _____ _______ ______   _    _  ____ _______ ______ _       _____ 
 |__   __|_   _|__   __|  ____| | |  | |/ __ \__   __|  ____| |     / ____|
    | |    | |    | |  | |__    | |__| | |  | | | |  | |__  | |    | (___  
    | |    | |    | |  |  __|   |  __  | |  | | | |  |  __| | |     \___ \ 
    | |   _| |_   | |  | |____  | |  | | |__| | | |  | |____| |____ ____) |
    |_|  |_____|  |_|  |______| |_|  |_|\____/  |_|  |______|______|_____/ 
							 Petteri Laukkanen 
                                        )";

	Sleep(10);

	cout << "\n TITE hotellit. Mahdollistamassa Terveen, Iloisen, sekä Täyden Elämän.\n\n\n\n"; //Hotellin slogan
	Sleep(100);

	viivat(); //aikaisemmin määritetty "lataus animaatio", jotta käyttäjä ehtii lukea nimen ja sloganin

	Sleep(1000);
Alku:  //Määritetään piste "Alku" johon voidaan palata kun varaus on valmis tai käyttäjä keskeyttää varauksen

	int huoneitatod = yhdenhengenhuoneettod + kahdenhengenhuoneettod;   //Määritetään varaamattomien huoneiden kokonaismäärä laskemalla yhteen vapaiden yhden ja kahden hengen huoneiden määrät.
	//Alempana kuin muut määritelmät, jotta huoneidenmäärä päivittyy aina kun palataan alkuun

	cls();  //Käytetään aikaisemmin määritettyä cls funktiota konsolin "siistimiseen"

	//Tulostetaan ASCII art tyylillä tervetulo toivotus
	cout << R"(  
 _    _                   _   _   _   _             _   _   _           _   _   _   _   _ 
| |  | |                 (_) (_) (_) (_)           (_) (_) (_)         (_) (_) (_) (_) | |
| |__| |  _   _  __   __   __ _    __ _     _ __     __ _   _  __   __   __ _    __ _  | |
|  __  | | | | | \ \ / /  / _` |  / _` |   | '_ \   / _` | | | \ \ / /  / _` |  / _` | | |
| |  | | | |_| |  \ V /  | (_| | | (_| |   | |_) | | (_| | | |  \ V /  | (_| | | (_| | |_|
|_|  |_|  \__, |   \_/    \__,_|  \__,_|   | .__/   \__,_| |_|   \_/    \__,_|  \__,_| (_)
           __/ |                           | |                                            
          |___/                            |_|                                            )";


	//Ilmoitetaan päävalikossa tehtyjän varauksien määrä
	cout << "Varauksia: " << varaajat;

	//Kysytään käyttäjältä mitä he haluavat tehdä
	cout << "\n\nHaluaisitteko varata huoneen, vai tarkastella jo tehtyä varausta?\n";
	cout << "Uusi varaus: 1  Tarkastele varausta: 2     Jos haluatte poistua, syöttäkää: 3\n>>";
	cin >> valikko;

	//Luodaan tai tarkastellaan varauksia käyttäjän syötteen mukaan
	switch (valikko) {

	//Varauksenluominen
	case 1:
	Huoneenkoko:
		cls();

		//Jos uuden varauksen numero on suurempi kuin huoneidenmäärä, ilmoitetaan hotellin olevan täynnä
		if (varaajat == huoneidenmaara) {
			cout << "Hotellimme on valitettavasti täynnä. Voitte kuitenkin vielä tarkastella varauksia";
			Sleep(3000);
			goto Alku;
		}

		//Varaus valikko, joka ilmoittaa käyttäjälle mitä huoneita on vapaana.
		cout << "\nTällähetkellä vapaana on yhteensä: " << huoneitatod << " huonetta.\n";
		if (yhdenhengenhuoneettod > 0 && kahdenhengenhuoneettod < 1) {
			cout << "Kaikki Kahden hengen huoneemme ovat valitettavasti täynnä, voitte kuitenkin vielä varata Yhden hengen huoneita.\n";
			cout << "Yhden hengen huoneita on vapaana " << yhdenhengenhuoneettod;
			cout << "\nHinta 100 euroa/yö";
			cout << "\nHaluaisitteko varata kahden hengen huoneen?";
			cout << "\nKyllä 1		En 2 (Palaa alkuun)\n>>";
		}

		else if (yhdenhengenhuoneettod < 1 && kahdenhengenhuoneettod > 0) {
			cout << "Kaikki Yhden hengen huoneemme ovat valitettavasti täynnä, voitte kuitenkin vielä varata kahden hengen huoneita.\n";
			cout << "Kahden hengen huoneita on vapaana " << kahdenhengenhuoneettod;
			cout << "\nHinta 150 euroa/yö";
			cout << "\nHaluaisitteko varata yhden hengenhuoneen?";
			cout << "\nKyllä 1		En 2 (Palaa alkuun)";
		}

		else if (kahdenhengenhuoneettod > 0 && yhdenhengenhuoneettod > 0) {
			cout << "Yhden hengen huoneita on " << yhdenhengenhuoneettod << "	(100e/yö\nkahden hengen huoneita on " << kahdenhengenhuoneettod << "	(150e/yö);";
			cout << "\n\nHaluaisitteko varata yhden hengen huoneen: 1 Vaiko kahden hengen huoneen: 2	Poistu: 3\n>>";
		}
	
		cin >> valikko;

		if (yhdenhengenhuoneettod < 1 && valikko==2 || kahdenhengenhuoneettod < 1 && valikko==2) {
			goto Alku;
		}

		switch (valikko) {
		//Yhden hengen huoneen valitseminen
		case 1:
		Arpa1:

			//Kysytään käyttäjältä arvotaanko huoneen numero vai haluavatko he päättää itse
			tila = 1;
			cls();
			cout << "\n\nMikäli haluatte valita huoneenne itse, syöttäkää: 1\nVoimme myös valita huoneen sattumanvaraisesti puolestanne syöttämällä: 2	Poistu: 3\n>>";
			cin >> valikko;
			switch (valikko) {

			//Vaihtoehto 1: kerrotaan käyttäjälle huoneet joista voi valita ja tallennetaan syöte
			case 1:
				cls();
				cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMinkä huoneen haluaisitte?\n>>";
				cin >> huone;
				while (huone<1 || huone>yhdenhengenhuoneet) {
					cout << "\n\nSyöttämänne huone ei vastannu yhtäkään vapaista yhden hengen huoneistamme.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMinkä huoneen haluaisitte?\n>>";
					cin >> huone;
				}

				//Jos käyttäjä syöttää jo varatun huoneen pyydetään heitä syöttämään toinen huone
				while (huoneet[huone] == true) {
					cout << "\n\nSyöttämänne huone on valitettavasti jo varattu.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMinkä huoneen haluaisitte?\n>>";
					cin >> huone;
				}

				break;

			//Vaihtoehto 2: arvotaan käyttäjälle huone ja varmistetaan ettei sitä ole vielä varattu
			case 2:
				cls();
				huone = noppa(1, yhdenhengenhuoneet);
				while (huoneet[huone] == true) {
					huone = noppa(1, yhdenhengenhuoneet);
				}
				cout << "Huoneenne numero on: " << huone;
				break;

			//Vaihtoehto 3: palataan alkuvalikkoon
			case 3:
				cls();
				cout << "Palataan alkuun.";
				Sleep(2000);
				goto Alku;
				break;

			//Mikäli käyttäjän syötä ei ole 1 tai 2 palataan kohtaan "Huoneenkoko"
			default:
				cls();
				cout << "Syöttämänne luku ei ollut 1 tai 2;";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				goto Huoneenkoko;
				
			}
			break;
			
		//Kahden hengen huoneen valitseminen
		case 2:
		Arpa2:
			tila = 2;
			cls();

			//Kysytään käyttäjältä arvotaanko huoneen numero vai haluavatko he päättää itse
			cout << "\n\nMikäli haluatte valita huoneenne itse, syöttäkää: 1\nVoimme myös valita huoneen sattumanvaraisesti puolestanne syöttämällä: 2	Poistu: 3\n>>";
			cin >> valikko;
			switch (valikko) {

			//Vaihtoehto 1: kerrotaan käyttäjälle huoneet joista voi valita ja tallennetaan syöte
			case 1:
				cls();
				cout << "\n\nVapaat kahden hengen huoneemme ovat numeroilla: " << kahdenhengenhuoneet << " - " << huoneidenmaara << "\nMinkä huoneen haluaisitte ? \n >> ";
				cin >> huone;
				while (huone<kahdenhengenhuoneet || huone>huoneidenmaara) {
					cout << "\n\nSyöttämänne huone ei vastannu yhtäkään vapaista kahden hengen huoneistamme.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat kahden hengen huoneemme ovat numeroilla: " << kahdenhengenhuoneet+1 << " - " << huoneidenmaara << "\nMinkä huoneen haluaisitte ? \n >> ";
					cin >> huone;
				}

				//Jos käyttäjä syöttää jo varatun huoneen pyydetään heitä syöttämään toinen huone
				while (huoneet[huone] == true) {
					cout << "\n\nSyöttämänne huone on valitettavasti jo varattu.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMinkä huoneen haluaisitte?\n>>";
					cin >> huone;
				}
				break;

			//Vaihtoehto 2: arvotaan käyttäjälle huone ja varmistetaan ettei sitä ole vielä varattu
			case 2:
				cls();
				huone = noppa(kahdenhengenhuoneet, huoneidenmaara);
				while (huoneet[huone] == true) {
					huone = noppa(kahdenhengenhuoneet, huoneidenmaara);
				}
				cout << "Huoneenne numero on: " << huone;
				break;
			//Vaihtoehto 3: Palataan alkuvalikkoon
			case 3:
				cls();
				cout << "Palataan alkuun.";
				Sleep(2000);
				goto Alku;
				break;

			default:
				cls();
				cout << "Syöttämänne luku ei ollut 1 tai 2;";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				goto Arpa2;
			}
			break;
		case 3:
			cls();
			cout << "Palataan alkuun.";
			Sleep(2000);
			goto Alku;
			break;
		default:
			cls();
			cout << "\nSyöttämänne arvo ei ollut: 1 tai 2\n\n";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			goto Arpa1;
		}
		break;


	//Varauksen tarkastelu
	case 2:
		Tarkastelu:
		cls();
		cout << "Varauksen tarkastelu";
		cout << "\nVoitte hakea varauksia varausnumeron 1 tai varaajan 2 perusteella.\n>>";
		cin >> valikko;
		
		switch (valikko) {
		//Haku varausnumerolla
		case 1:

			cls();
			cout << "Syöttäkää varausnumero\n>> ";
			cin >> etsittavanumero;

			while (cin.fail()) {
				cout << "Syöttämänne arvo ei ollut numero!";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				cls();
				cout << "Syöttäkää varausnumero\n>> ";
				cin >> etsittavanumero;
			}

			cls();
			for (int etsintalaskuri = 0; etsintalaskuri <= 300; etsintalaskuri++) {
				if (varaaja[etsintalaskuri].vnumero == etsittavanumero) {
					cout << "Varaukset numerolla " << etsittavanumero;
					cout << "\n\nVaraaja: " << varaaja[etsintalaskuri].vnimi;
					cout << "\nHuoneen numero: " << varaaja[etsintalaskuri].vhuone;
					cout << "\nHuoneen koko: " << varaaja[etsintalaskuri].vtila << " hengenhuone";
					cout << "\nÖiden määrä: " << varaaja[etsintalaskuri].vtila << " yötä";
					cout << "\nHinta: " << varaaja[etsintalaskuri].vhinta << " euroa";
					cout << "\n\n";
					viivat();
					loydetty = true;
					
				}
			}
			
			break;
		//Haku varaajan nimellä
		case 2:
			cls();
			cout << "Syöttäkää varaajan nimi\n>> ";
			cin.clear();
			cin.ignore(100, '\n');
			getline(cin, etsittavavaraaja);
			cout << "Varaukset nimellä " << etsittavavaraaja;
			for (int etsintalaskuri = 0; etsintalaskuri <= 300; etsintalaskuri++) {
				if (varaaja[etsintalaskuri].vnimi == etsittavavaraaja) {
					cout << "\n\nVarausnumero: " << varaaja[etsintalaskuri].vnumero;
					cout << "\nHuoneen numero: " << varaaja[etsintalaskuri].vhuone;
					cout << "\nHuoneen koko: " << varaaja[etsintalaskuri].vtila << " hengenhuone";
					cout << "\nÖiden määrä: " << varaaja[etsintalaskuri].vtila << " yötä";
					cout << "\nHinta: " << varaaja[etsintalaskuri].vhinta << " euroa";
					cout << "\n\n";
					viivat();
					loydetty = true;

				}
			}
			break;
		default:
			cls();
			cout << "\nSyöttämänne arvo ei ollut: 1 tai 2\n\n";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			cls();
			goto Tarkastelu;

		}
		//Jos varauksia ei löydy tulostetaan sopiva teksti riippuen siitä, haettiinko varausta numerolla vai nimellä
		if (loydetty == false) {
			if (valikko == 1) {
				cout << "\nVarausnumerolla "<<etsittavanumero<<" ei valitettavasti löytynyt yhtäkään varausta.\n";
			}
			if (valikko == 2) {
				cout << "\nNimellä " << etsittavavaraaja << " ei valitettavasti löytynyt varauksia.";
			}
		}
		cout << "\nVoitte palata aloitukseen syöttämällä 1\n>>";
		cin >> valikko;
		goto Alku;
		break;

	case 3:
		cls();
		cout << "Kiitoksia asionnistanne kanssamme. Toivotamme teille oikein mukavaa päivänjatkoa!\n";
		cout << "Varaus ohjelma sulkeutuu itsestään 10 sekunnin kuluttua.";
		Sleep(10000);
		return 0;
		break;

	default:
		cls();
		cout << "\nSyöttämänne arvo ei ollut: 1 tai 2\n\n";
		cin.clear();
		cin.ignore(100, '\n');
		Sleep(2000);
		goto Alku;
		break;
	}

	//Kysytään käyttäjältä öiden määrä ja kerrotaan valitan huone tyypin hinta per yö
	cout << "\n\nKuinka monta yötä haluaisitte yöpyä? (Pisin aika 11 yötä)\n";
	if (tila == 1) {
		cout << "100e/yö\n>>";
	}
	else if (tila == 2) {
		cout << "150e/yö\n>>";
	}
	cin >> aika;
	while (aika < 1 || aika > 11) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nSyöttämänne öiden määrä ei ollu välillä 1-11.";
		Sleep(2000);
		cls();
		cout << "\n\nKuinka monta yötä haluaisitte yöpyä? (Pisin aika 11 yötä)\n>>";
		cin >> aika;
	}
	//Lähetetään huoneen koko ja öiden määrä funktiolle joka laskee hinnan
	hinta = hintalaskuri(aika, tila);
	cls();
	//Pyydetään varaajan nimi
	cout << "\n\nSyöttäkää vielä varaajan nimi: ";
	cin.clear();
	cin.ignore(100, '\n');
	getline(cin, nimi);



	cls();
	//Näytetään varauksen tiedot ja kysytään haluaako käyttäjä siirtyä maksamaan
	cout << "\nVarauksenne tiedot: \n";
	cout << "\nVaraaja: " << nimi;
	cout << "\nHuone:" << huone;
	if (tila == 1) {
		cout << "\nYhden hengen huone";
	}
	else if (tila == 2) {
		cout << "\nKahden hengen huone";
	}
	cout << "\nÖiden määrä: " << aika;
	cout << "\nHinta: " << hinta << " euroa";
	cout << "\n\n1: Maksa      2:Peruuta varaus\n\n";
	cout << "\n>>";
	cin >> valikko;

	switch (valikko) {

	case 1:
		//Arvotaan 0%, 10% tai 20% alennus hintaan ja tallennetaan tiedot varaaja taulukkoon
		alennus = noppa(1, 3);
		if (alennus == 2) {
			cls();
			cout << "Onneksi olkoon!!\n\nOlette saaneet 10% alennuksen varauksestanne!";
			hinta = hinta * 0.9;
			Sleep(2000);
		}
		else if (alennus == 3) {
			cls();
			cout << "Onneksi olkoon!!\n\nOlette saaneet 20% alennuksen varauksestanne!";
			hinta = hinta * 0.8;
			Sleep(2000);
		}
		varausnmr = noppa(10000, 99999);
		while (varausnumerot[varausnmr] == true) {
			varausnmr = noppa(10000, 99999);
		}
		varausnumerot[varausnmr] = true;
		varaaja[varaajat].vhinta = hinta;
		varaaja[varaajat].vaika = aika;
		varaaja[varaajat].vnimi = nimi;
		varaaja[varaajat].vhuone = huone;
		varaaja[varaajat].vnumero = varausnmr;
		varaaja[varaajat].vtila = tila;
		huoneet[varaaja[varaajat].vhuone] = true;
		if (tila == 1) {
			yhdenhengenhuoneettod--;
		}
		else if (tila == 2) {
			kahdenhengenhuoneettod--;
		}
	Tiedot:
		cls();

		//Kiitetään varauksesta ja näytetään vielä lopulliset tiedot
		cout << "Kiitoksia varauksestanne!\n\nVarausnumeronne on: ";
		cout << varausnmr;
		cout << "\n\n";
		cout << varaaja[varaajat].vnimi << "\n";
		cout << "Huone: " << varaaja[varaajat].vhuone;

		if (tila == 1) {
			cout << "\nYhden hengen huone";
		}
		else if (tila == 2) {
			cout << "\nKahden hengen huone";
		}
		cout << "\nÖiden määrä: " << aika;
		cout << "\nHinta: " << hinta << " euroa";
		varaajat++;


		cout << "\n\nVoitte palata alkuun syöttämällä 1 tai poistua ohjelmasta syöttämällä 2\n>>";
		cin >> valikko;
		while (cin.fail()) {
			cout << "Syöttämänne arvo ei ollut numero!";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			cls();
			cout << "\n\nVoitte palata alkuun syöttämällä 1 tai poistua ohjelmasta syöttämällä 2\n>>";
			cin >> valikko;
		}
		switch (valikko) {
		case 1:
			cout << "Palataan alkuun.";
			Sleep(2000);
			goto Alku;
			break;
		case 2:
			cls();
			cout << "Kiitoksia asionnistanne kanssamme. Toivotamme teille oikein mukavaa päivänjatkoa!\n";
			cout << "Varaus ohjelma sulkeutuu itsestään 10 sekunnin kuluttua.";
			Sleep(10000);
			return 0;
			break;
		default:
			cout << "Syöttämänne arvo ei ollu 1 tai 2";
			goto Tiedot;
			break;
		}
	case 2:
		cls();
		cout << "Palataan alkuun.";
		Sleep(2000);
		goto Alku;
		break;

	default:
		cout << "Syöttämänne arvo ei ollu 1 tai 2";
		goto Tiedot;
		break;
	}



}

//Funktio, joka laskee varauksen hinnan (ennen alennusta) öiden määrän ja huoneen koon perusteeella
int hintalaskuri(int aika, int tila) {
	if (tila == 1) {
		return aika * 100;
	}
	else if (tila == 2) {
		return aika * 150;
	}
}

//Funktio, joka kutsuttaessa tulostaa viivoja ns. lataus animaationa
void viivat() {
	string valiviivat = "------------------------------------------------------------------------------------------";
	for (int j = 0; j < valiviivat.size(); j++)
	{

		for (int i = 0; i <= 10000000; i++);
		cout << valiviivat[j];

	}
}

//Funktio, joka kutsuttaessa siirtää konsolin näkymää alaspäin siten, että se näyttää tyhjältä
void cls() {
	cout << "\x1B[2J\x1B[H";
}

//Funktio, joka arpoo luvun annetun minimi ja maximi arvon välistä
int noppa(int min, int max) {
	srand(time(0));
	return (rand() % ((max - min) + 1)) + min;
}