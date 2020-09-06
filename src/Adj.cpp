#include "Adj.h"

Adj::Adj(std::string ms,std::string mp,std::string fs,std::string fp) : _ms(ms){
	_mp = (mp == "" ? ms : mp);
	_fs = (fs == "" ? ms : fs);
	_fp = (fp == "" ? mp : fp);
}

std::string Adj::getMs(){
	return _ms;
}

std::string Adj::getMp(){
	return _mp;
}

std::string Adj::getFs(){
	return _fs;
}

std::string Adj::getFp(){
	return _fp;
}

std::string Adj::get(Genre g){
	switch(g){
		case MS: return _ms;
		case MP: return _mp;
		case FS: return _fs;
		case FP: return _fp;
	}
	return _ms;
}

std::string Adj::operator[](Genre g){
	return get(g);
}