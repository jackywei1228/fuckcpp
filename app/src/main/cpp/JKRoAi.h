//
// Created by 25810 on 2018/12/22.
//

#ifndef FUCKCPP_JKROAI_H
#define FUCKCPP_JKROAI_H


class JKRoAi {
public:
    // CATEGORY: AI state constants
    static const int OFF = 0;
    static const int MANUAL = 1;
    static const int AUTO = 2;
    void login();
private:
    int mState;
};


#endif //FUCKCPP_JKROAI_H
