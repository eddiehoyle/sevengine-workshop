//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_ABSTRACTEXAMPLE_HH
#define SEVENGINE_WORKSHOP_ABSTRACTEXAMPLE_HH


class AbstractExample {

public:
    AbstractExample() {}
    virtual ~AbstractExample() {}

public:
    virtual void setup() {}
    virtual void paint() {}
    virtual void cleanup() {}
};


#endif //SEVENGINE_WORKSHOP_ABSTRACTEXAMPLE_HH
