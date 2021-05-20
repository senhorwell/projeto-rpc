#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "agenda.h"

using namespace std;

void parse_line(string line, string &name, string &address, string &phone);

//funcao CREATE
char** create_1_svc (contact *con, struct svc_req *rqstp) {
   static char* result = (char*) malloc(sizeof(char) * 100);

   string name, address, phone, line;

   printf("Recebi chamado: CREATE %s %s %s\n",con->name,con->address,con->phone);

   ofstream ofile;
   ifstream ifile;

   ifile.open("data.txt");

   if(ifile.is_open()) {

      while(getline(ifile, line)) {
        parse_line(line, name, address, phone);

        if(name.compare(string(con->name)) == 0) {
          sprintf(result, "ERRO: CONTATO COM O NOME %s JA EXISTE, VIOLACAO DA CHAVE PRIMARIA\n", con->name);
    			ifile.close();
    			return (&result);
    		}
    	}
   }

   ofile.open("data.txt", ofstream::app);
   
   if(ofile.is_open()) {
   		ofile << con->name << ',' << con->address << ',' << con->phone << '\n';
   		sprintf(result, "CONTATO INSERIDO COM SUCESSO\n");
   		ofile.close();
   } else
   		sprintf(result, "ERRO: PROBLEMAS AO INSERIR O CONTATO\n");

   return (&result);
}

//funcao READ
char** read_1_svc (contact *con, struct svc_req *rqstp) {
	static char* result = (char*) malloc(sizeof(char) * 100);
	
  string name, address, phone, line;

  printf("Recebi chamado: READ %s\n",con->name);

  ifstream ifile;
  ifile.open("data.txt");

  if(ifile.is_open()) {
  	while(getline(ifile, line)) {
      parse_line(line, name, address, phone);
  		if(name.compare(string(con->name)) == 0) {
        sprintf(result, "CONTATO ENCONTRADO: NOME: %s, ENDERECO: %s, TELEFONE: %s\n", name.c_str(), address.c_str(), phone.c_str());
        ifile.close();
        return (&result);
  		}
  	}
  	sprintf(result, "ERRO: CONTATO INEXISTENTE\n");
  	ifile.close();
  } else
  	sprintf(result, "ERRO: CONTATO INEXISTENTE\n");

  return (&result);
}

//funcao UPDATE
char** update_1_svc (contact *con, struct svc_req *rqstp) {
    static char* result = (char*) malloc(sizeof(char) * 100);
    
    string name;
    string address;
    string phone;
    string line;

    printf("Recebi chamado: UPDATE %s %s %s\n",con->name,con->address,con->phone);

    ifstream ifile;
    ofstream ofile;

    ifile.open("data.txt");

    if(ifile.is_open()) {

      vector<string> names;
      vector<string> addresses;
      vector<string> phones;

      while(getline(ifile, line)) {
        parse_line(line, name, address, phone);
        names.emplace_back(string(name));
        addresses.emplace_back(string(address));
        phones.emplace_back(string(phone));  
      }
      ifile.close();

      bool encontrado = false;

      for(int i = 0; i < names.size(); i++) {
        if(names[i].compare(string(con->name)) == 0){
          names.erase(names.begin() + i);
          addresses.erase(addresses.begin() + i);
          phones.erase(phones.begin() + i);
          
          names.emplace_back(string(con->name));
          addresses.emplace_back(string(con->address));
          phones.emplace_back(string(con->phone));
          
          encontrado = true;
          break; 
        }
      }
 
      if(encontrado) {
        ofile.open("data.txt", ofstream::trunc);
        for(int i = 0; i < names.size(); i++){
          ofile << names[i] << ',' << addresses[i] << ',' << phones[i] << '\n';
        }

        ofile.close();
        sprintf(result, "CONTATO ALTERADO COM SUCESSO\n");
      } else
        sprintf(result, "ERRO: CONTATO INEXISTENTE\n");
    } else
      sprintf(result, "ERRO: CONTATO INEXISTENTE\n");

    return (&result);
}

//funcao DELETE
char** delete_1_svc (contact *con, struct svc_req *rqstp) {
    static char* result = (char*) malloc(sizeof(char) * 100);
    
    string name;
    string address;
    string phone;
    string line;

    printf("Recebi chamado: DELETE %s\n",con->name);

    ifstream ifile;
    ofstream ofile;

    ifile.open("data.txt");

    if(ifile.is_open()) {

      vector<string> names;
      vector<string> addresses;
      vector<string> phones;

      while(getline(ifile, line)) {
        parse_line(line, name, address, phone);
        names.emplace_back(string(name));
        addresses.emplace_back(string(address));
        phones.emplace_back(string(phone));  
      }
      ifile.close();

      bool encontrado = false;

      for(int i = 0; i < names.size(); i++) {
        if(names[i].compare(string(con->name)) == 0) {
          names.erase(names.begin() + i);
          addresses.erase(addresses.begin() + i);
          phones.erase(phones.begin() + i);
          encontrado = true;
          break; 
        }
      }
 
      if(encontrado) {
        ofile.open("data.txt", ofstream::trunc);
        for(int i = 0; i < names.size(); i++){
          ofile << names[i] << ',' << addresses[i] << ',' << phones[i] << '\n';
        }

        ofile.close();
        sprintf(result, "CONTATO REMOVIDO COM SUCESSO\n");
      } else
        sprintf(result, "ERRO: CONTATO INEXISTENTE\n");
    } else
      sprintf(result, "ERRO: CONTATO INEXISTENTE\n");

    return (&result);
}

void parse_line(string line, string &name, string &address, string &phone) {
    name.clear();
    address.clear();
    phone.clear();

    int i;

    for(i = 0; line[i] != ','; i++)
      name.push_back(line[i]);
  
    for(i++; line[i] != ','; i++)
      address.push_back(line[i]);

    for(i++; i < line.size(); i++)
      phone.push_back(line[i]);
}