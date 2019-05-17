#include "Person.h"

using namespace std;

void Person::give_notification(std::string content){
    
    notification.push_back ( Notification(content));

}