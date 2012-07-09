/**
  Hello,Worldを表示するクラス
 */

#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

class CHelloWorld {
    public:
        CHelloWorld(int count);
        virtual ~CHelloWorld();
        
        void print();

        
    private:
        int count_;
};

#endif __HELLOWORLD_H__
