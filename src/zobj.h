#ifndef _ZOBJ_H_
#define _ZOBJ_H_

class Z_Obj {
	
public:
	Z_Obj(long iz, unsigned long icreation, unsigned long itype, unsigned long iid);
	~Z_Obj();
	
	void set_z(long n);
	long get_z();
	unsigned long get_creation();
	unsigned long get_type();
	unsigned long get_id();

private:
	long z;
	unsigned long creation;
	unsigned long type;
	unsigned long id;
};

#endif
