#include "zobj.h"

Z_Obj::Z_Obj(long iz, unsigned long icreation, unsigned long itype, unsigned long iid) {
	z = iz;
	creation = icreation;
	type = itype;
	id = iid;
}

Z_Obj::~Z_Obj() {
	
}

void Z_Obj::set_z(long nz) {
	z = nz;
}

long Z_Obj::get_z() {
	return z;
}

unsigned long Z_Obj::get_creation(){
	return creation;
}

unsigned long Z_Obj::get_type() {
	return type;
}

unsigned long Z_Obj::get_id() {
	return id;
}
