#include "scene/Object.hpp"

namespace scene {
    Object::Object() : Entity() {

    }

    Object::Object(const maths::Point &point) : Entity(point) {

    }

    Material Object::getMaterial(const maths::Point &point) const {
        auto &material = this->materialProvider.getMaterial(*this, point);
        auto &texture = material.getTexture();
        if (texture.cols > 0 && texture.rows > 0) {
            auto texCoords = this->getTextureCoordinates(point);
            Material texMat = material;
            int y = (int)roundf(texCoords.y() * texture.rows) % texture.rows;
            int x = (int)roundf(texCoords.x() * texture.cols) % texture.cols;
            auto texPoint = texture.at<cv::Vec3b>(y, x);
            Color col(texPoint[2] / 255.0f, texPoint[1] / 255.0f, texPoint[0] / 255.0f);
            texMat.setKa(col);
            return texMat;
        }
        return material;
    }

    void Object::fromYaml(const YAML::Node &node) {
        Entity::fromYaml(node);
        this->materialProvider = node.as<MaterialProvider>();
    }
}
