// Phúc AN
#pragma once
#include <string>

class NguoiDung {
protected:
    std::string id;
    std::string name;
    std::string role;

private:
    std::string password;
    static int userCount;

public:
    NguoiDung();
    NguoiDung(std::string _id, std::string _name, std::string _password);
    virtual ~NguoiDung();

    std::string getId() const;
    std::string getName() const;
    std::string getPass() const;
    std::string getRole() const;

    void setName(const std::string& newName);
    void setPass(const std::string& newPass);
    void setRole(const std::string& newRole);

    bool operator==(const NguoiDung& other) const;
    virtual void displayMenu() const = 0;
};




//// phúc an viết
//#pragma once
//#include <iostream>
//#include <string>
//using namespace std;
//class NguoiDung
//{
//protected:
//	string id; // tìm cách viết sinh id bằng biến static : vd dụ static = 1 ; id = ND001
//	string name;
//	string passWord;
//public:
//	NguoiDung(string _id, string _name, string _pass) :id(_id), name(_name), passWord(_pass) {};
//	string getId();
//	string getName();
//	string getPassword();
//	virtual void displayMenu() const;  
//	virtual void displayProfile()const ;
//	//bool login();
//	//bool logout();
//	//bool newAccount();  không nên để ở đay 
//};

