#ifndef REQUESTER_H
#define REQUESTER_H

#include <iostream>
#include <string>

class Requester {
private:
    std::string name;
    std::string role;
    std::string email;

public:
    Requester();
    Requester(const std::string& name, const std::string& role,
              const std::string& email);

    const std::string& getName() const;
    const std::string& getRole() const;
    const std::string& getEmail() const;
    void setName(const std::string& name);
    void setRole(const std::string& role);
    void setEmail(const std::string& email);

    friend std::ostream& operator<<(std::ostream& out,
                                    const Requester& requester);
};

#endif
