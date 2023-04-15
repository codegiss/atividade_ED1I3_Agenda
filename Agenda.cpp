#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

class Data
{
	private:
		int dia;
		int mes;
		int ano;
    public:
    	Data(int dia, int mes, int ano) {
			this->dia = dia;
            this->mes = mes;
			this->ano = ano;			
		}
    	Data() {
			this->dia = 0;
            this->mes = 0;
			this->ano = 0;			
		}
		void setDia(int dia) {
			this->dia = dia;
		}
		void setMes(int mes) {
			this->mes = mes;
		}
		void setAno(int ano) {
			this->ano = ano;
		}
		int getDia() {
			return this->dia;
		}
		int getMes() {
			return this->mes;
		}
		int getAno() {
			return this->ano;
		}
		string getData()
        {
            return to_string(this->dia) + "/" +
                   to_string(this->mes) + "/" +
           		   to_string(this->ano);	  
        }        
        Data* dia_seguinte()
		{
			Data *d1;
			int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			d1 = new Data(this->dia, this->mes, this->ano);

			if (d1->ano%4==0)
			{
				diasNoMes[1]++;
			}

			d1->dia++;

			if(d1->dia > diasNoMes[d1->mes-1])
			{
				d1->dia = 1;

				if (++d1->mes > 12)
				{
					d1->mes = 1;
					d1->ano++;
				}
		}
		return d1;
	}
};

class Contato
{
	private:
		string nome;
		string email;
		int telefone;
		Data dtnasc;
	public:
		Contato(string nome, string email, int telefone, Data dtnasc) {
			this->nome = nome;
			this->email = email;
			this->telefone = telefone;
			this->dtnasc = dtnasc;
		} 
		void setNome(string nome){
			this->nome = nome;
		}
		void setEmail(string email){
			this->email = email;
		}
		void setTelefone(int telefone){
			this->telefone = telefone;
		}
		void setDtNasc(Data dtnasc){
			this->dtnasc = dtnasc;
		}
		string getNome(){
			return nome;
		}
		string getEmail(){
			return email;
		}
		int getTelefone(){
			return telefone;
		}
		Data getDtNasc(){
			return dtnasc;
		}
		int idade(Data nasc) {
			int dianasc = nasc.getDia();
			int mesnasc = nasc.getMes();
			int anonasc = nasc.getAno();

			int diahoje, meshoje, anohoje, idade;
			
			time_t agora = time(0);
			tm* ltm = localtime(&agora);
			
			diahoje = ltm->tm_mday;
			meshoje = 1 + ltm->tm_mon;
			anohoje = 1900 + ltm->tm_year;
			
			//calcular idade
			idade = anohoje - anonasc;

			if((meshoje == mesnasc && diahoje<dianasc) || meshoje<mesnasc)
			{
				return --idade;
			}
			
			return idade;
		}
};

bool validarEmail(string email) {

    if (email.empty() || email.find('@') == std::string::npos || email.find('.') == std::string::npos)
        return false;

    if (email.find('@') != email.rfind('@') || email.find('.') != email.rfind('.'))
        return false;

    if (email.find('@') > email.find('.'))
        return false;

    if (email.find('@') == 0 || email.find('.') == email.length() - 1 || email.find('.') - email.find('@') == 1)
        return false;

    return true;
}

int main(int argc, char** argv)
{
	/*
		Data *hoje = new Data();
		hoje->setDia(30);
		hoje->setMes(3);
		hoje->setAno(2023);
	*/
	
	int telefone, dia, mes, ano, dialimite = 31;
	bool valido;
	string nome, email;

	Contato* contatos[10];

	for(int i=0;i<10;i++)
	{
		cout << "Cadastro da "<< (i+1) <<"a. pessoa" << endl;
		
		cout << "Digite o nome: ";
		getline (cin, nome);
		
		cout << "Digite o telefone: ";
		cin >> telefone;
		
		do
		{
			//validar email
			cout << "Digite o email: ";
			cin >> email;
			
			valido = validarEmail(email);
		}
		while(!valido);
			
		do
		{
			cout << "Digite o ano de nascimento: ";
			cin >> ano;
		}
		while (ano<1);
			
		do
		{
			cout << "Digite o mes de nascimento: ";
			cin >> mes;
		}
		while (mes<1 || mes>12);
		
		switch (mes)
		{
			case 4:
			case 6:
			case 9:
			case 11:
				dialimite--;
				break;
			case 2:
				//ver se é ano bissexto
				if((ano % 4 ==0 && ano % 100 ==0) || (ano % 400 ==0))
				{
					dialimite = 29;
				}
				else
				{
					dialimite = 28;
				}
				break;
		}
		
		do
		{
			cout << "Digite o dia de nascimento: ";
			cin >> dia;
		}
		while (dia<1 || dia>dialimite);
		
		Data *nasc = new Data();
		nasc->setDia(dia);
		nasc->setMes(mes);
		nasc->setAno(ano);
		
		contatos[i] = new Contato(nome, email, telefone, nasc);
		
		cin.ignore();
		
		cout << "Contato " << nome << " criado." << endl;
		cout << endl;
	}
	
	cout << "==================================" << endl;
	
	for(int i=0; i<10; i++)
	{
		cout << endl;
		
		dt = contatos[i]->getDtNasc();
		
		cout << "CONTATO " << (i+1) << endl;
		cout << "Nome: " << contatos[i]->getNome() << endl;
		cout << "Telefone: " << contatos[i]->getTelefone() << endl;
		cout << "Email: " << contatos[i]->getEmail() << endl;
		cout << "Data de nasc.: " << contatos[i]->getDtNasc() << endl;
		cout << "Idade: " << contatos[i]->idade(dt) << " anos." << endl;
		
		cout << "----------------------------------" << endl;
		
		delete contatos[i];
	}
	
	return 0;
}