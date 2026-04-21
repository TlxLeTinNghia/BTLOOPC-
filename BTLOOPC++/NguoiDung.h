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