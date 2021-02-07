//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "NavigationController.h"

NavigationController::NavigationController(BaseViewController* rootViewController) {
    this->viewControllerStack = std::stack<BaseViewController *>();

    rootViewController->viewWillBePushed(this);
    this->viewControllerStack.push(rootViewController);
    rootViewController->viewWasPushed(this);
}

void NavigationController::push(BaseViewController* viewController) {
    BaseViewController* currentTop = this->viewControllerStack.top();

    currentTop->subviewWillBePushed(this, viewController);
    viewController->viewWillBePushed(this);
    this->viewControllerStack.push(viewController);
    viewController->viewWasPushed(this);
    currentTop->subviewWasPushed(this, viewController);
}

void NavigationController::pop() {
    BaseViewController* viewController = this->viewControllerStack.top();
    viewController->viewWillBePopped(this);
    this->viewControllerStack.pop();
    viewController->viewWasPopped(this);

    BaseViewController* superView = this->viewControllerStack.top();
    superView->subviewWasPopped(this, viewController);
}

BaseViewController* NavigationController::top() {
    return this->viewControllerStack.top();
}
