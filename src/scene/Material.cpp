#include "scene/Material.hpp"

namespace scene {
    Material(): ka(scene::Color()), kd(scene::Color()), ks(scene::Color()) shininess(0.2f){

    }

    scene::Color getKa() const{
        return this->ka;
    }
    scene::Color getKd() const{
        return this->kd;
    }
    scene::Color getKs() const{
        return this->ks;
    }
    int getShininess() const{
        return this->shininess;
    }

    void setShininess(int s){
        this->shininess = s;
    }
    void setKa(scene::Color col){
        this->ka = col;
    }
    void setKd(scene::Color col){
        this->kd = col;
    }
    void setKs(scene::Color col){
        this->ks = col;
    }
}