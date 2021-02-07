//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_NAVIGATIONCONTROLLER_H
#define GRINDER_NAVIGATIONCONTROLLER_H

#include <stack>

class BaseViewController;

class NavigationController {
public:
    explicit NavigationController(BaseViewController* rootViewController);

    void push(BaseViewController*);
    void pop();
    BaseViewController* top();

private:
    std::stack<BaseViewController *> viewControllerStack;
};

#include "ViewControllers/BaseViewController.h"

#endif //GRINDER_NAVIGATIONCONTROLLER_H
