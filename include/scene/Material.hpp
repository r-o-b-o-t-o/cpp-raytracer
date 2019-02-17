#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <opencv2/opencv.hpp>

#include "scene/Color.hpp"

namespace scene {
    class Material {
    public:
        Material();
        Material(Color ka, Color kd, Color ks);
        Material(Color ka, Color kd, Color ks, float shininess);
        Material& operator=(const Material &rhs) = default;

        Color getKa() const;
        Color getKd() const;
        Color getKs() const;
        float getShininess() const;

        void setShininess(float s);
        void setKa(Color);
        void setKd(Color);
        void setKs(Color);

        const cv::Mat &getTexture() const;
        void setTexture(const cv::Mat &texture);

    private:
        Color ka;
        Color kd;
        Color ks;
        float shininess;
        cv::Mat texture;
    };
}

#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>
namespace YAML {
    template<>
    class convert<scene::Material> {
    public:
        static bool decode(const Node &node, scene::Material &rhs) {
            auto ambiant = node["ambiant"];
            auto diffuse = node["diffuse"];
            auto specular = node["specular"];
            auto shininess = node["shininess"];
            auto texture = node["texture"];

            if (ambiant) {
                rhs.setKa(ambiant.as<scene::Color>());
            }
            if (diffuse) {
                rhs.setKd(diffuse.as<scene::Color>());
            }
            if (specular) {
                rhs.setKs(specular.as<scene::Color>());
            }
            if (shininess) {
                rhs.setShininess(shininess.as<float>());
            }
            if (texture) {
                auto path = texture.as<std::string>();
                if (boost::filesystem::path(path).is_relative()) {
                    path = SCENES_DIR + path;
                }
                if (boost::filesystem::exists(path)) {
                    cv::Mat mat = cv::imread(path, CV_LOAD_IMAGE_COLOR);
                    rhs.setTexture(mat);
                }
            }
            return true;
        }
    };
}

#endif // MATERIAL_HPP