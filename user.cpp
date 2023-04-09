#include "user.h"

User::User(std::string name, std::string pass, unsigned id): _name_user(name), _pass_user(pass), _id_user(id) {}

std::string User::get_name() const {return _name_user;}

unsigned User::get_id() const {return _id_user;}
