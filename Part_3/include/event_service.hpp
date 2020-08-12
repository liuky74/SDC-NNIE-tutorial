//
// Created by liuky on 2020-08-12.
//

#ifndef NNIE_TUTORIAL_EVENT_SERVICE_HPP
#define NNIE_TUTORIAL_EVENT_SERVICE_HPP

#include "common.hpp"
#include "sdc.hpp"
#include "label_event.h"
class EventService {
private:
    int m_fd_event = -1;
    int m_fd_cache = -1;
    char *m_app_name;
public:
    explicit EventService(char *app_name);
    int service_register();
    int get_fd();

    int SDC_LabelEventDel(unsigned int baseid, unsigned int id);

};


#endif //NNIE_TUTORIAL_EVENT_SERVICE_HPP
