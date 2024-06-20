#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

class Csinger
{
public:
	string Sname;
	string Scountry;
	int Idate;

	Csinger()
	{
		string Sname = "N/A";
		string Scountry = "N/A";
		int Idate = 0;
	}
	Csinger(const string SName, const string SCountry, const int IDate)
	{
		Sname = SName;
		Scountry = SCountry;
		Idate = IDate;
	}
	Csinger(const Csinger& p)
	{
		Sname = p.Sname;
		Scountry = p.Scountry;
		Idate = p.Idate;
	}

	int age(){
		time_t t = time(NULL);
		tm* Tinfo = localtime(&t);
		return (Tinfo->tm_year + 1900) - Idate;
	}

	friend ostream& operator<<(ostream& ostr, const Csinger& p)
	{
		ostr << p.Sname << endl << p.Scountry << endl << p.Idate << endl;
		return ostr;
	}
	friend istream& operator>>(istream& istr, Csinger& p)
	{
		if (&istr == &cin)
		{
			cout << "Enter name: ";
			getline(istr, p.Sname);
			cout << "Enter country: ";
			getline(istr, p.Scountry);
			cout << "Enter birth date: ";
			istr >> p.Idate;
		}
		else
		{
			istr.ignore(1, '\n');
			getline(istr, p.Sname);
			getline(istr, p.Scountry);
			istr >> p.Idate;
		}
		return istr;
	}

};
class CAlbum:public Csinger
{
public:
	string SnameAlbum;
	int Iyear;
	int Iedition;

	CAlbum()
	{
		SnameAlbum = "N/A";
		Iyear = 0;
		Iedition = 0;
	}
	CAlbum(const string SNameAlbum, const int IYear, const int IEdition)
	{
		SnameAlbum = SNameAlbum;
		Iyear = IYear;
		Iedition = IEdition;
	}
	CAlbum(const CAlbum& o) : Csinger(o)
	{
		SnameAlbum = o.SnameAlbum;
		Iyear = o.Iyear;
		Iedition = o.Iedition;
	}
	bool operator<(const CAlbum& p) const
	{
		if(Iedition < p.Iedition) return true;
		else return false;
	}
	friend ostream& operator<<(ostream& ostr, const CAlbum& p)
	{
		ostr << p.Sname << endl;
		ostr << p.Scountry << endl;
		ostr << p.Idate << endl;
		ostr << p.SnameAlbum << endl << p.Iyear << endl << p.Iedition << endl;
		return ostr;
	}
	friend istream& operator>>(istream& istr, CAlbum& p)
	{
		if (&istr == &cin)
		{
			cout << "Enter name: ";
			getline(istr, p.Sname);
			cout << "Enter country: ";
			getline(istr, p.Scountry);
			cout << "Enter birth date";
			istr >> p.Idate;
			cout << "Enter album name: ";
			getline(istr, p.SnameAlbum);
			cout << "Enter year: ";
			istr >> p.Iyear;
			cout << "Enter edition: ";
			istr >> p.Iedition;
		}
		else
		{
			getline(istr, p.Sname);
			getline(istr, p.Scountry);
			istr >> p.Idate;
			istr.ignore(1, '\n');
			getline(istr, p.SnameAlbum);
			istr >> p.Iyear >> p.Iedition;
			istr.ignore(1, '\n');
		}
		return istr;
	}
};
class CFonetika
{
public:
	string SnFonetik;
	vector<CAlbum> Valbums;
	CFonetika(const string Sfile)
	{
		ifstream fin(Sfile);
		getline(fin, SnFonetik);
		CAlbum p;
		while(fin >> p)
		{
			Valbums.push_back(p);
		}
	}
	void Sort()
	{
		sort(Valbums.begin(), Valbums.end());
		reverse(Valbums.begin(), Valbums.end());
	}
	int countSingers(const string Scountry)
	{
		int Icount = 0;
		for(vector<CAlbum>::iterator it = Valbums.begin(); it != Valbums.end(); it++)
		{
			if((*it).Scountry == Scountry) Icount++;
		}
		return Icount;
	}
	CAlbum latestAlbum(const string Sname)
	{
		CAlbum Cmax;
		int Imax = 0;
		for(vector<CAlbum>::iterator it = Valbums.begin(); it != Valbums.end(); it++)
		{
			if((*it).Sname == Sname)
				if((*it).Iyear > Imax)
				{
					Cmax = *it;
					Imax = (*it).Iyear;	
				}
		}
		return Cmax;
	}
	vector<Csinger> ageSingers(const int a, const int b)
	{
		vector<Csinger> Vsingers;
		for(vector<CAlbum>::iterator it = Valbums.begin(); it != Valbums.end(); it++)
		{
			if((*it).age() >= a && (*it).age() <= b) Vsingers.push_back((Csinger)*it);
		}
		return Vsingers;
	}
	Csinger bestSeller()
	{
		CAlbum max = Valbums.at(0);
		for(vector<CAlbum>::iterator it = Valbums.begin(); it != Valbums.end(); it++)
		{
			if((*it).Iedition > max.Iedition) max = *it;
		}
		return (Csinger)max;
	}
	friend ostream& operator<<(ostream& ostr, const CFonetika& p){
		ostr << p.SnFonetik << endl;
		for(vector<CAlbum>::const_iterator it = p.Valbums.begin(); it != p.Valbums.end(); it++) ostr << (*it);
		return ostr;
	}
};

int main(){
	CFonetika A("test.txt");
	cout << A;
	cout << endl;
	A.Sort();
	cout << A;
	cout << endl;
	cout << A.latestAlbum("Singer1") << endl;
	cout << A.countSingers("USA") << endl;
	cout << A.bestSeller() << endl;
	vector<Csinger> age = A.ageSingers(30, 50);
	for(vector<Csinger>::const_iterator it = age.begin(); it != age.end(); it++) cout << *it;

}