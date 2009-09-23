#ifndef _OBJS_H_
#define _OBJS_H_

class Z_Obj {
        long z;
        unsigned long creation;
        unsigned long type;
        unsigned long id;
    public:
        Z_Obj() {};
        Z_Obj(long a, unsigned long b, unsigned long c, unsigned long d) {
            z = a;
            creation = b;
            type = c;
            id = d;
        };
        void set_z(long n) {z = n;};
        long get_z() {return z;};
        unsigned long get_creation() {return creation;};
        unsigned long get_type() {return type;};
        unsigned long get_id() {return id;};
};

#endif
